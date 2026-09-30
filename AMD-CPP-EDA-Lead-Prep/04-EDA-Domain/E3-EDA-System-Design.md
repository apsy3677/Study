# E3: System Design for EDA Tools (Lead-level)

> A Lead C++/EDA loop usually has **one design discussion**: an EDA component, a multi-level cache, a virtual-memory system (AMD-reported), or "how would you make X 5× faster".
> Unlike web system design, the axes are **memory layout, algorithms, incrementality, determinism, parallelism, persistence, APIs (Tcl), testing/QoR**.

---

## 0. The answer framework (use it every time, ~45 min)
| Step | Min | What to cover |
|---|---|---|
| 1. **Requirements & scale** | 5 | Operations (read/write mix), sizes (10⁸ cells? 10⁹ edges?), latency vs throughput, memory budget, incremental or batch, determinism, threads/hosts |
| 2. **Data model** | 10 | Entities, ids, relationships, layout (SoA/CSR), names, back-of-envelope memory |
| 3. **Core algorithms** | 10 | The main operations with complexity, and the incremental path |
| 4. **Concurrency** | 5 | What's parallel, synchronization model (phases, single writer), determinism |
| 5. **API & persistence** | 5 | C++ API + Tcl/Python binding, checkpoint format, versioning, backward compatibility |
| 6. **Quality** | 5 | Testing (unit, golden, fuzz, QoR regression), observability (logs, message IDs, perf counters), rollout |
| 7. **Trade-offs & evolution** | 5 | What you'd do first, what you'd defer, the risks |

**Back-of-envelope habit:** always compute memory. `100M objects × 32 B = 3.2 GB`. Pointers are 8 B, ids 4 B.

---

## D1. Design an in-memory netlist database for 100M+ cells ★★
**Requirements:** load in minutes; fast traversal (cell→pins→net→sinks); ECO edits; hierarchical names; Tcl queries (`get_cells -hier -filter …`); save/restore checkpoints; many engines (timing, placement) observe it; thread-safe reads.

**Data model (SoA, integer handles):**
```
CellTable:  type[]  (uint32 → LibCell)   name[] (uint32 → NameTable)   parentInst[] (hierarchy)   flags[] (uint8)   pinBegin[] (CSR into PinTable)
PinTable:   cell[]  (uint32)   net[] (uint32, NONE)   libPin[] (uint16)   dir[] (uint8)
NetTable:   name[]  pinBegin[] + pins[] (CSR: driver first, then sinks)
NameTable:  interned strings; hierarchical path = parent id + leaf id (a trie of path segments)
LibCell:    shared master data (pins, timing arcs, area), stored once
```
- **Why ids:** 4 B vs 8 B, stable under reallocation, mmap/serialization-friendly, usable as array indices by the side engines (`vector<float> arrival(pinCount)`).
- **Memory estimate:** 100M cells × ~4 pins = 400M pins. Pin row ≈ 4+4+2+1 ≈ 11 B (SoA) → **~4.4 GB for the pins**. Cells ≈ 100M × ~17 B ≈ 1.7 GB. Names are the silent killer, so interning plus hierarchical compression is mandatory.
- **Hierarchy:** definitions (modules) vs occurrences (instances in context). Keep it **hierarchical** for memory (a module instantiated 10k times is stored once) and **flatten lazily** / uniquify only where an edit needs it.
- **Edits (ECO):** tombstones + free lists; **generation counters** in the handles (`id | gen`) to catch stale handles; periodic compaction. CSR is rebuilt in bulk or kept as a CSR base + an overflow delta per net.
- **Observers:** engines register callbacks (`onNetConnect`, `onCellMoved`) → they mark their data dirty (incremental timing). Batch the notifications per command.
- **Undo/redo:** a command journal of inverse operations (or snapshots of the touched rows).
- **Concurrency:** phase model: many parallel readers, a single writer during edits (a global epoch or a RW lock at command granularity). Per-thread scratch buffers indexed by ids. No fine-grained locks on objects.
- **Persistence:** a versioned binary checkpoint (like a DCP): a header + tables written as flat arrays (fast `fread`/mmap) + compression (zstd) + a checksum. A schema version with forward migration. Your **save/restore XML → binary** experience goes here: discuss XML vs binary (readability vs speed/size).
- **Tcl API:** thin wrappers returning lightweight object handles; filters are compiled into predicates; results are lazy iterators to avoid materializing 100M-element lists.
- **Testing:** golden netlists, round-trip save/restore equality, fuzzed ECO sequences checked by invariants (every pin's net contains that pin), memory/runtime budgets in CI.

## D2. Incremental static timing engine ★★
- **Graph:** pins as nodes; cell arcs from LibCell timing tables (NLDM: delay = f(slew, load)); net arcs from interconnect estimates (placement → wirelength → RC; post-route extracted RC).
- **Storage:** per pin `AT/RT/slew × {rise, fall} × {min, max}` → 8 floats = 32 B/pin → 400M pins ≈ 12.8 GB. Store only what's needed (maybe max only in placement), use `float` not `double`, or compute on demand.
- **Full update:** levelize once; propagate forward per level (parallel within a level); backward for required times.
- **Incremental:** a changed arc → dirty set → forward propagation through the fanout cone in **level order** (a bucket queue by level), early-stop when unchanged. Required times backward only if the endpoints are affected. **Lazy**: defer until someone queries a slack.
- **Queries:** worst slack per endpoint (a heap/tournament tree for WNS), top-K paths, per-net criticality for the placer/router (`crit = 1 − slack/Dmax`).
- **Determinism:** fixed level order, no FP reductions that depend on the thread order (per-level results are written to per-node slots, so there are no shared accumulators).
- **Trade-offs:** accuracy (full RC/SI) vs speed (a quick estimator during placement). Many tools have **two** timers: a fast one inside optimization loops and a signoff-accurate one.

## D3. Parallel, deterministic router ★
- Inputs: the routing-resource graph (FPGA: billions of edges → **don't materialize**; store per-**tile-type** templates and compute the global node ids arithmetically), the nets with criticality.
- **Algorithm:** PathFinder iterations. Each iteration: order the nets (deterministic: by criticality, then id), route each with A* over the RR graph using the current costs, update the occupancy; increase the present and history costs; repeat until no overuse.
- **Parallelism:** group the nets into batches with **non-overlapping bounding boxes** (or partition the device into regions + a boundary pass); route a batch in parallel with thread-local occupancy deltas; merge them in a fixed order at the barrier → deterministic.
- **Memory:** per-node occupancy (uint8/uint16), history cost (float), and the per-thread A* scratch (dist/visited arrays reset via a **timestamp trick** instead of clearing).
- **Metrics:** overuse count per iteration (should converge), runtime per iteration, WNS after routing, memory.
- **Failure modes:** oscillation (the history cost fixes it), unroutable hotspots (report the congestion map, feed back to placement).

## D4. QoR/regression infrastructure for a team (Lead signal) ★★
- 500 designs × nightly × several flows → a farm (LSF/Slurm), containerized builds, a results DB (runtime, peak memory, WNS/TNS, utilization, routed-or-not).
- **Gating:** statistically aware thresholds (noise bands per design), bisect automation to the offending commit, dashboards per metric.
- Flaky-test handling, determinism checks (run twice, diff the checkpoints), sanitizer and TSan nightly builds.
- AI-assisted triage (your personal tooling: log clustering, first-failure diffing). Say how you'd make it a **team** tool: adoption, docs, measuring the time saved.

## D5. Multi-level cache (AMD-reported design question) ★
- Clarify: hardware-like (CPU cache simulator) or software (a cache in front of a slow store)?
- **Software version:** L1 in-process LRU (hash map + list, sharded locks), L2 larger (local SSD / shared memory / remote), backing store. `get`: L1 → L2 → store, **promote** on hit. Policies: inclusive vs exclusive, write-through vs write-back (+ dirty tracking), TTL/invalidation, negative caching, a single-flight guard against thundering herds.
- **Hardware version:** sets/ways, tag/index/offset split of the address, pseudo-LRU, a write-back + write-allocate policy, MESI/MOESI coherence for multi-core, inclusive L3 as a snoop filter.
- Metrics: hit rate per level, latency percentiles, memory overhead, contention.

## D6. Virtual memory system (AMD-reported) ★
Page tables (multi-level radix to save space for sparse address spaces) · a TLB (a small fully-associative cache of translations; ASIDs/PCIDs to avoid flushes) · page faults → allocate/load, COW, swap · the replacement policy (clock) · huge pages · the kernel/user split · permissions (R/W/X, user bit) · `mmap` of files · IOMMU for devices (GPU/DMA, a nice AMD touch).

## D7. "Make our tool 5× faster" (an open-ended lead question) ★★
1. Establish the benchmark suite and the baseline (runtime and peak memory per phase).
2. Profile the phase breakdown → find the top 3 hotspots (perf / uProf / VTune).
3. Categorize: algorithmic (O(n²) somewhere), memory layout (cache misses), allocation churn, serial phases (Amdahl), I/O.
4. Plan quick wins (flags, allocator swap, obvious copies) vs structural work (SoA refactor, incremental algorithms, parallelization).
5. Protect correctness: QoR-neutral checks, determinism, equivalence of the outputs.
6. Make it stick: perf gates in CI, dashboards, team guidelines (no per-object `new` in hot loops, etc.).
7. **Lead signal:** split the work across engineers by phase, define the measurable goals per milestone, and report the progress weekly with data.

---

## Self-test (answer as if in the interview)
1. Estimate the memory for the pins of a 100M-cell netlist in SoA with 32-bit ids.
2. Why are integer handles better than pointers for an EDA database? Give 4 reasons.
3. How do you keep the parallel propagation in timing deterministic?
4. Incremental STA: which cone gets updated for a delay change, and in what order?
5. In PathFinder, why does the history cost prevent oscillation?
6. Design the cache hierarchy: what are the inclusive/exclusive and write-through/write-back trade-offs?
7. Walk through your "make it 5× faster" plan in 90 seconds.
