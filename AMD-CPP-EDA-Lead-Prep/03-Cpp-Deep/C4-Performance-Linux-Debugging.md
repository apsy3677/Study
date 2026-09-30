# C4: Performance Engineering, Linux Tooling, Debugging

> **This is the core of the JD:** *"lead a team to improve the performance of key applications and benchmarks using C++ and Linux"*, plus debuggers and profilers.
> Prepare **two measured performance stories** from your own work (see section 7) before the interview.

---

## 1. Numbers every performance engineer knows (approximate, modern x86 / AMD Zen)
| Event | Latency |
|---|---|
| L1 hit | ~1 ns (4–5 cycles) |
| L2 hit | ~3–4 ns (~14 cycles) |
| L3 hit | ~10–15 ns (~40–50 cycles) |
| DRAM (local) | ~80–100 ns |
| Remote NUMA / other CCD | +30–100 ns more |
| Branch mispredict | ~15–20 cycles |
| Mutex lock/unlock uncontended | ~20–25 ns |
| Context switch / syscall | ~1–5 µs / ~100 ns–1 µs |
| `malloc`/`free` small | ~20–100 ns |
| Cache line | **64 bytes**; page 4 KB (huge pages 2 MB / 1 GB) |

**Mental model:** "Memory is the bottleneck. A cache miss costs ~100 instructions of work. Fast code is code that touches **less memory**, **contiguously**, **predictably**."

## 2. The performance methodology (say this as your framework)
1. **Define the benchmark and metric** (wall time, peak RSS, QoR) with representative designs, and pin the variance (warm cache, fixed threads, `taskset`, repeat N times).
2. **Profile, don't guess**: find where the time goes (CPU sampling), then *why* (hardware counters: cache misses, branch misses, IPC).
3. **Hypothesis → smallest change → measure** (A/B, statistically meaningful).
4. **Guard it**: add a perf regression test to CI (runtime and memory budgets per design).
5. **Communicate**: the before/after table, the trade-offs (memory vs time, determinism, code complexity).

Optimization ladder (biggest wins first): **algorithm/complexity** → **data layout and memory traffic** → **avoid work** (caching, incrementality, early exit) → **parallelism** → micro-optimizations (branchless, SIMD, intrinsics) → compiler flags (`-O3`, `-march`, LTO, **PGO**).

## 3. Data-oriented design for EDA-scale data ★★
| Technique | Why |
|---|---|
| **Index handles** (`uint32_t` ids) instead of pointers | half the size of 64-bit pointers, stable across reallocation, serializable (save/restore!), usable as array indices |
| **Struct-of-Arrays** vs Array-of-Structs | loops that touch 1–2 fields stream only those fields → fewer cache lines. The timing engine iterates arrival times, not whole pin objects |
| **CSR adjacency** (`offsets[]`, `edges[]`) | contiguous neighbour lists, one allocation instead of millions of vectors |
| **Arena / pool allocation** | no per-object malloc cost or header; objects allocated together sit together |
| **String interning** | 100M hierarchical names → store each unique string once, keep 32-bit ids; hash-consing |
| **Hot/cold splitting** | keep frequently used fields in a compact struct, rarely used ones elsewhere |
| **Avoid virtual calls in hot loops** | homogeneous arrays + a switch on a type tag, or templates |
| **Bit-packing** | flags in bitfields/bitsets; small enums in `uint8_t` |
| **Sort work for locality** | process nets/cells in spatial or topological order (fewer misses) |

`sizeof` discipline: shrinking a 100M-object struct from 48 → 32 bytes saves **1.6 GB**, and memory **is** runtime at that scale.

## 4. Linux performance tools (what each tells you)
| Tool | Use | Key commands |
|---|---|---|
| **perf** | CPU sampling profiler + HW counters | `perf stat -e cycles,instructions,cache-misses,branch-misses ./tool` · `perf record -g ./tool` → `perf report` · flame graphs (`perf script \| stackcollapse \| flamegraph`) · `perf c2c` (false sharing) · `perf top` |
| **AMD uProf** | AMD's own profiler (IBS: precise instruction-level sampling on Zen), power, threading | say you know it exists and what IBS is. **AMD-specific credibility** |
| Intel VTune | hotspots, microarchitecture analysis, threading | |
| **valgrind** | memcheck (leaks, invalid reads, uninitialized), **callgrind** (exact call counts → kcachegrind), cachegrind, **massif** (heap over time), helgrind (races) | 20–50× slowdown |
| **heaptrack** | allocation hotspots, leaks, temporary allocations; much faster than massif | |
| **Sanitizers** | ASan (OOB, UAF, double free, leaks: ~2×), UBSan (UB), TSan (races), MSan (uninit, clang) | `-fsanitize=address,undefined -fno-omit-frame-pointer -g` |
| **gprof** | old instrumentation profiler (`-pg`) | mention only |
| `strace` / `ltrace` | syscalls / library calls (I/O storms, `mmap` churn) | `strace -c -f` |
| `/usr/bin/time -v` | wall time, **max RSS**, page faults, context switches | |
| `numactl`, `taskset`, `lscpu`, `hwloc` | NUMA/affinity | |
| `pmap`, `/proc/<pid>/status\|smaps` | memory breakdown | |

**Build flags to mention:** `-O2 -g` (always keep symbols) · `-fno-omit-frame-pointer` (usable stacks in perf) · `-march=native` (careful with distribution builds: target a baseline like `x86-64-v3`) · `-flto` · `-fprofile-generate`/`-fprofile-use` (**PGO**: 5–15% for branchy code) · `-ffast-math` (breaks IEEE semantics and determinism, so be careful in EDA).

## 5. gdb essentials (debugger fluency)
```
gdb --args ./tool -f run.tcl        run / bt / bt full / frame N / info locals / p expr / p *obj / ptype obj
break file.cpp:120 if n==42         watch var (hardware watchpoint: who corrupts this?)   rwatch / awatch
catch throw                          stop where an exception is thrown
thread apply all bt                  every thread's stack (deadlocks)
gdb ./tool core                      post-mortem on a core dump (ulimit -c unlimited; coredumpctl)
gdb -p <pid>                         attach to a hung process
set print pretty on; finish; until; tbreak; display
```
Plus: `rr record/replay` (reverse debugging), `addr2line`, `c++filt` (demangle), `nm -C`, `objdump -d`, `ldd`, `readelf`.

## 6. Debugging scenarios (they may ask "how would you approach…")
| Scenario | Approach |
|---|---|
| **Crashes only in the release build** | Almost always UB (uninitialized variable, OOB, lifetime, strict aliasing, signed overflow) that the optimizer exploited, or a timing race. Build release with `-g`, run ASan/UBSan builds, check compiler warnings (`-Wall -Wextra -Wuninitialized`), bisect by optimization level or by object files, use `valgrind` on release, and check the core dump. |
| **Memory grows over a 12-hour run** | Distinguish a **leak** (unreachable memory: ASan/LSan, valgrind), **unbounded caches/containers** (reachable: heaptrack/massif snapshots over time), and **fragmentation** (RSS ≫ live bytes: try jemalloc, `malloc_trim`, pools). Track peak RSS per phase. |
| **Non-deterministic results between runs** | Hash-order iteration, pointer-based ordering, races, uninitialized reads, FP reduction order, time-based seeds. Run the same input N times with different thread counts, diff the intermediate dumps, and bisect by phase. |
| **10× slowdown after a refactor** | `perf diff` between versions. Look for accidental copies (pass-by-value, `auto` vs `auto&`), lost inlining (a virtual/`std::function` in a hot loop), O(n²) sneaking in (`std::find` in a loop, `erase` from the front of a vector), and lock contention. |
| **Deadlock/hang at a customer site** | Ask for a core dump or `gstack`/`gdb -p` backtraces of all threads; find the lock cycle; fix the lock ordering. Add a lock hierarchy checker and watchdog logs. |
| **Tool slower on AMD EPYC than expected** | NUMA placement (first touch, interleave), thread pinning, cross-CCD traffic, memory bandwidth saturation. Check `perf stat` IPC and cache misses per core. |
| **Stack overflow in a deep recursion** (e.g. DFS on a 10M-node netlist) | Convert to an iterative DFS with an explicit stack; or raise `ulimit -s` / thread stack size as a stop-gap. |

## 7. Your perf stories: fill these in before the interview (STAR + numbers)
Candidates from your background (verify the numbers against your own records; never invent):
1. **DPV partitioning + multiprocessing for massive designs.** Problem (runtime or memory wall on huge designs) → how you partitioned → processes vs threads choice → load balancing → result (runtime/memory numbers) → determinism handling.
2. **"One Percent Solution" header decoupling (~75% reduction in includes: 132 → 34).** Build-time/compile-performance story: dependency analysis, pimpl/forward declarations, measured build-time delta, pattern adopted by others.
3. **Adobe lazy loading for large files (−60% load time).** Classic "avoid work" optimization.
4. **Coverage subsystem at scale** (if you have runtime/memory numbers for coverage computation or save/restore).

Template: *"The metric was X on benchmark Y. The profile showed Z% in A. My hypothesis was B. I changed C. It went from P to Q, and here is how we guarded it in CI. The trade-off was D."*

## 8. Build & compile-time performance (your strongest lead story)
Include hygiene (forward declarations, pimpl, IWYU), precompiled headers, unity/jumbo builds, `ccache`/`sccache`, distributed builds (distcc/icecc), `extern template`, reducing template bloat, modules (C++20), link time (`lld`/`mold`, `-gsplit-dwarf`), static vs shared libraries (symbol visibility `-fvisibility=hidden`).

---

## Self-test
1. The latency of L1, L3 and DRAM, and why that makes a linked list slow.
2. Your 5-step perf methodology.
3. AoS vs SoA: when is SoA better? Give an EDA example.
4. Which tool for: a hotspot · false sharing · a leak · heap growth over time · a data race · an uninitialized read?
5. "Crashes only in release": walk through your approach.
6. Why use 32-bit indices instead of pointers in a netlist DB? Three reasons.
7. What is PGO, and when does it help?
