# E2: EDA Algorithms, Interview-Grade

> Each algorithm: **the idea in one line → how it works → complexity → the follow-up they'll ask.**
> Practice: `06-Practice/day3.cpp` (`levelize`, `worstSlack`, `criticalPath`, `leeRoute`, `hpwl`), `day2.cpp` (geometry).
> Priority for R1: §1–§3 and §8 (graphs + geometry) ★★; the rest ★ (recognize and explain at a high level).

---

## 1. Representing a netlist
| Model | Nodes | Edges | Use |
|---|---|---|---|
| **Hypergraph** | cells | nets (hyperedges, many pins) | partitioning, placement (HPWL) |
| **Pin graph / timing graph** | pins | cell arcs (input pin → output pin) + net arcs (driver → each sink) | STA, levelization |
| **Clique/star expansion** | cells | a net becomes a clique or a star to a virtual node | quadratic placement |
| **Routing-resource graph** (FPGA) | wires / pins | programmable switches (PIPs) | routing |

Storage at scale: **CSR** (`netPinOffset[net]`, `netPins[]`), 32-bit ids, SoA (see E3 and C4).

## 2. Levelization & combinational loops ★★
- **Idea:** assign `level(v) = 1 + max(level(pred))`, with sources (primary inputs, FF outputs) at level 0. It's Kahn's topological sort, recording the depth.
- **Loop:** if Kahn finishes with unprocessed nodes, there's a combinational loop → find it with **SCC** (Tarjan) → report the minimal loops to the user.
- **Why levels:** nodes in the same level are independent → **parallel** evaluation per level (barrier between levels); simulation and STA order.
- Complexity O(V + E).
- **Follow-up:** "The netlist has 50M nodes and recursion overflows the stack" → iterative Tarjan with an explicit stack.

## 3. Static timing: arrival, required, slack, critical paths ★★
- **Forward (arrival):** in topo order, `AT[v] = max over u→v of (AT[u] + d(u,v))`. (Also min for hold, and rise/fall separately.)
- **Backward (required):** in reverse topo order, `RT[u] = min over u→v of (RT[v] − d(u,v))`, starting with `RT[endpoint] = T_clk − setup`.
- **Slack** = `RT − AT` (per pin). WNS = min slack over the endpoints.
- **Critical path extraction:** from the worst endpoint, walk back through the predecessor that gave the max arrival.
- **Top-K worst paths:** a best-first search on (path slack) with a heap. Or the "k longest paths in a DAG" via deviations from the critical path (Eppstein-like). Report K paths without enumerating exponentially many.
- **Incremental STA** (after an ECO or a placement move changes a delay): mark the changed arc dirty → propagate arrival **forward** only through the fanout cone, in **level order** (a min-heap or bucket queue by level, so each node is recomputed once) → stop when a node's arrival doesn't change (**early termination**) → required times backward in the fanin cone. Lazy variant: only recompute on query.
- **Parallel STA:** level-by-level parallel for, or task graph (Taskflow/OpenTimer style).

## 4. Logic synthesis data structures ★
### AIG + structural hashing
- An **AIG** (And-Inverter Graph) has only 2-input AND nodes and complemented edges. Any logic → AIG.
- **Strash** = hash-consing: before creating `AND(a,b)`, normalize (`a < b`), then look up `(a,b)` in a hash table → reuse the existing node. This gives a canonical-ish structure and is free CSE (common subexpression elimination).
- **Balancing:** rebuild AND-trees as balanced trees → lower depth (delay).
- **Rewriting:** replace small cuts (4-input) with precomputed optimal subgraphs.
### BDD (ROBDD)
- A canonical DAG for a boolean function under a fixed variable order: **reduced** (no redundant tests, isomorphic nodes shared via the **unique table**) and **ordered**.
- Operations via `ITE(f, g, h)` with a **computed table** (memoization = DP!).
- Canonical → equivalence check is O(1) (pointer compare). **Size depends heavily on the variable order** (a multiplier's BDD is exponential in any order → why SAT dominates datapath checking).
### SAT (CDCL), which you know from formal
- DPLL + **unit propagation** (two-watched-literal scheme) + **conflict analysis** (learn a clause at the 1-UIP) + **non-chronological backjumping** + **VSIDS** decision heuristic + restarts + clause deletion.
- EDA uses: equivalence checking (miter + SAT), BMC, ATPG, SAT sweeping (merging equivalent AIG nodes).
### Technology mapping to K-LUTs
- **K-feasible cut** of node v: a set of ≤ K nodes such that every path from the PIs to v passes through the set. Each cut becomes one LUT.
- **Cut enumeration** bottom-up: `cuts(v) = { c1 ∪ c2 : c1 ∈ cuts(a), c2 ∈ cuts(b), |c1 ∪ c2| ≤ K } ∪ {{v}}`. Keep only the top-N **priority cuts** to bound the blow-up.
- **Depth-optimal** (FlowMap: polynomial via max-flow) → then **area recovery** (area flow, exact local area) on non-critical nodes.

## 5. Partitioning ★
- **Goal:** split the cells into k balanced parts minimizing the cut nets (the SLR crossings in FPGA, the parallel work split in your DPV partitioning).
- **Kernighan–Lin:** swap pairs with the best gain, O(n² log n) per pass.
- **Fiduccia–Mattheyses:** move single cells; **gain buckets** (array of lists indexed by gain) give O(1) best-move selection; lock the moved cells; take the best prefix of moves; **O(pins) per pass**. Handles hyperedges and balance.
- **Multilevel (hMETIS/KaHyPar):** **coarsen** (cluster/match connected cells) → **partition** the small graph → **uncoarsen + FM refine** at each level. The state of the art in quality and speed.
- Related: spectral partitioning (Fiedler vector), min-cut/max-flow for 2-way with terminals.

## 6. Placement ★
- **Objective:** minimize total (weighted) **HPWL** = Σ_nets (max x − min x + max y − min y) subject to legality (no overlap, the right site types) + timing (weight the critical nets) + congestion/density.
- **Simulated annealing** (VPR, classic FPGA): random swaps/moves; accept worse moves with probability e^(−Δ/T); cool T; a range limiter shrinks the move window. Incremental ΔHPWL: recompute only the nets touching the moved cells (keep per-net bounding boxes + edge counts for O(1) updates).
- **Analytic/quadratic:** minimize Σ w·(xi − xj)² → a sparse linear system (conjugate gradient); cells clump → spreading forces or density penalties. **ePlace/RePlAce/DREAMPlace**: an electrostatic density model solved with FFT + Nesterov; DREAMPlace uses a deep-learning toolkit on the GPU.
- **Legalization** (Tetris, Abacus) → **detailed placement** (local swaps, reordering, sliding windows).
- **FPGA specifics:** packing LUT+FF into slices (control sets!), discrete columns for DSP/BRAM, SLR-crossing cost, clock region constraints.

## 7. Routing ★★ (Lee is a likely coding question)
- **Lee's maze router:** a BFS wavefront on the grid from the source until the target is reached, then **backtrace**. Guarantees the shortest path; O(grid cells) time and memory.
- **A\***: Dijkstra with priority `g + h`, h = Manhattan distance to the target (admissible) → far fewer expansions.
- **Multi-pin nets:** a Steiner tree. The RSMT is NP-hard; heuristics: MST-based (≤ 1.5× the optimum), iterated 1-Steiner, **FLUTE** (lookup tables), or route sink by sink growing from the existing tree (Prim-Dijkstra).
- **Global vs detailed:** global routing assigns nets to coarse GCells with capacities (minimizing overflow); detailed routing assigns exact tracks/vias (ASIC) or exact wires/PIPs (FPGA).
- **PathFinder (negotiated congestion), the FPGA workhorse:**
  node cost = `(b(n) + h(n)) × p(n)`. b = base delay/cost, **h = history cost** (grows every iteration a node stays overused), **p = present congestion penalty** (grows with current overuse, and its multiplier increases each iteration). Each iteration rips up and reroutes (all or only the congested) nets. Nets "negotiate" until no resource is overused. Timing-driven: `cost = crit·delay + (1 − crit)·congestion`.
- **Parallel routing:** route nets with disjoint bounding boxes concurrently; deterministic batch scheduling; merge the congestion updates at the batch boundaries.

## 8. Geometry & spatial data structures ★★ (common EDA coding round topic)
| Need | Structure | Cost |
|---|---|---|
| Rect/segment overlap test | coordinate comparisons (P06 Card D) | O(1) |
| All overlapping pairs among n rects | **sweep line** over x + an **interval tree** (or a set) over the active y-intervals | O((n + k) log n) |
| Count H–V wire crossings | sweep x + **Fenwick tree** over compressed y | O(n log n) |
| Union area / coverage of rects | sweep + **segment tree** (count, covered length) | O(n log n) |
| Nearest cell / window query ("which shapes are in this box?") | uniform **grid bins** (simple, fast when uniform), **quadtree**, **k-d tree**, **R-tree** (bulk-loaded: STR) | ~O(log n + k) |
| Point in polygon | ray casting (count crossings) / winding number | O(edges) |
| Rectilinear polygon boolean ops (DRC, fill) | scanline with edge events | O(n log n) |

Lead tip: *"For DRC-like queries on a mostly uniform layout, I'd start with a grid bin structure: cache-friendly and trivially parallel. Switch to an R-tree when the density is very skewed."*

## 9. Other classics to recognize
Event-driven vs cycle-based **simulation** · **graph coloring** (register allocation, double-patterning masks) · **bipartite matching / Hungarian** (pin assignment, IO placement) · **max-flow/min-cut** · **ILP/SAT formulations** for small exact subproblems · **retiming** (Leiserson–Saxe) · **clock tree synthesis** (H-tree, DME: deferred merge embedding).

---

## Problems (hint ladders), EDA-flavoured

### E2-1 · Levelize a netlist; report failure on a combinational loop ★★ · `levelize`
Input: n nodes, directed edges. Output: `level[v]` for all v, or empty if a cycle exists.
<details><summary>Hint 1</summary>Which traversal processes a node only after all its predecessors?</details>
<details><summary>Approach check</summary>Kahn; when you pop u, for each successor v: `level[v] = max(level[v], level[u] + 1)`; count the processed nodes. O(V+E).</details>

### E2-2 · Worst slack & critical path ★★ · `worstSlack`, `criticalPath` (P08-7)

### E2-3 · Lee maze routing on a grid ★★ · `leeRoute`
Grid with blocked cells; return the shortest path length from S to T (4-neighbour), or −1. Then also return the path cells.
<details><summary>Hint 1</summary>Which traversal gives the fewest steps on unweighted edges?</details>
<details><summary>Hint 2</summary>How do you recover the path after reaching T?</details>
<details><summary>Approach check</summary>BFS with a parent array (or distance labels + backtrace from T choosing any neighbour with dist−1). O(RC). Follow-ups: A* (Manhattan heuristic), weighted cells → Dijkstra, multi-pin nets → grow from the whole existing tree (multi-source BFS), multiple nets → rip-up & reroute / PathFinder.</details>

### E2-4 · HPWL, and ΔHPWL after swapping two cells ★★ · `hpwl`
Given the cell (x,y) and the nets as lists of cell ids: compute the total HPWL. Then: two cells swap positions. Compute the new total **without** recomputing every net.
<details><summary>Hint 1</summary>Which nets can change when cells a and b swap?</details>
<details><summary>Approach check</summary>Only the nets incident to a or b. Keep a cell→nets index; recompute those nets' bounding boxes. With per-net bbox + "count of pins on each boundary", many updates become O(1). This is exactly the annealing inner loop.</details>

### E2-5 · Structural hashing ★ · (discussion / whiteboard)
Design `int mkAnd(int a, int b)` for an AIG where literals are `2*node + complemented`. Avoid duplicates, simplify the trivial cases.
<details><summary>Approach check</summary>Trivial rules: a==b → a; a==¬b → const0; a==0 → 0; a==1 → b. Normalize a<b. Look up `unordered_map<uint64_t,int>` with key `(uint64_t)a<<32|b`, create the node if missing. Discuss: hash quality, memory (millions of nodes → a custom open-addressing table), deterministic node ids.</details>

### E2-6 · All overlapping pairs among n rectangles ★ · (discussion + optional code)
<details><summary>Hint</summary>Sort the x-events; keep the active rectangles' y-intervals in a structure that answers "which intervals overlap [y1,y2]?"</details>
<details><summary>Approach check</summary>Sweep x; on start: query the active set for overlapping y-intervals (interval tree → O(log n + k)), then insert; on end: remove. For uniform layouts: grid binning + dedupe pairs.</details>

### E2-7 · Count crossings between n horizontal and m vertical wires ★ · (stretch)
<details><summary>Approach check</summary>Events: H-start(x1, +y), V(x, query [y1,y2]), H-end(x2, −y), ordered at equal x as start < query < end if touching counts. Fenwick over compressed y. O((n+m) log(n+m)).</details>

### E2-8 · Explain FM's gain bucket structure ★ (whiteboard)
<details><summary>Approach check</summary>The gain range is [−pmax, +pmax], where pmax = the max nets per cell → an array of doubly-linked lists indexed by gain + a max-gain pointer. Moving a cell updates the gains of only its neighbours on critical nets, each an O(1) relink. So one pass is O(total pins).</details>

---

## Recall check
1. Levelization = which algorithm + what extra line? 2. The STA forward op, backward op, slack. 3. How is incremental STA kept O(affected cone)?
4. What makes strash canonical and cheap? 5. BDD vs SAT for multipliers? 6. FM vs KL. 7. PathFinder's two cost terms and why history matters.
8. Which spatial structure for "which shapes are inside this window?" and why?
