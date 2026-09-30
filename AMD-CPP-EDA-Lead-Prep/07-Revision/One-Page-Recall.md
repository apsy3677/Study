# One-Page Recall (the night before + 30 minutes before the interview)

## Live-coding protocol
**Clarify** (size, sorted?, dups, negatives, empty, return on failure) → **examples as comments** → **brute force + complexity** → **better idea + invariant + target complexity** → *"shall I code it?"* → **code top-down** → **dry-run** → **edge cases** → **complexity recap** → **scale/thread-safety remark**.

## Pattern triggers
| Signal | Pattern | Invariant / key line |
|---|---|---|
| subarray sum = k, negatives | prefix + hash | `ans += cnt[s-k]; ++cnt[s];` seed `{0:1}` |
| longest/shortest contiguous with a monotone rule | sliding window | expand right; `while(invalid) shrink` / `while(valid){record; shrink}` |
| sorted, pair/triplet | two pointers | each move discards a loser |
| "min X such that feasible" | binary search on answer | `if(ok(mid)) hi=mid; else lo=mid+1;` |
| next greater / span / histogram | monotonic stack | stack = waiting indices, decreasing |
| window max | monotonic deque | expire front, evict smaller back |
| top-k / k-th | heap of size k | min-heap for largest |
| intervals / rooms | sort + heap of ends / sweep | ends before starts at ties (half-open) |
| list surgery | dummy + save-cut-rewire-advance | slow/fast for the middle/cycle |
| tree | "ask children / tell parent" | postorder returns + global best |
| dependencies / DAG | Kahn topo | output < n ⇒ cycle; level = max(pred)+1 |
| shortest path | BFS / Dijkstra (stale skip) | mark visited on push |
| connectivity | DSU | path compression + by size |
| 2 groups, no inner edge | bipartite BFS coloring | every component |
| ways / min cost | DP | state in words; coins outer = combinations |
| O(1) cache | map + list | map → iterator; splice to front |

## C++ must-says
- **vtable:** per class, vptr per object, set by the ctor; a virtual call = 2 loads + an indirect call; no inlining; ctor/dtor dispatch = the current class.
- **Virtual dtor** for polymorphic delete (else UB). `shared_ptr` from `Derived*` still calls the right dtor.
- **Move:** `std::move` = cast; moved-from = valid but unspecified; **noexcept moves** or vector copies; don't `return std::move(local)`.
- **Rule of 0/3/5**; a user-declared dtor kills the implicit moves.
- **Smart ptrs:** unique = 1 ptr, move-only. shared = 2 ptrs + control block (atomic strong/weak), `make_shared` = 1 allocation; weak breaks cycles; refcount atomic, the pointee not.
- **STL:** vector ×2 growth, reallocation invalidates all; map = RB tree; unordered_map = chaining, rehash invalidates iterators; `sort` = introsort (unstable).
- **UB list:** signed overflow, OOB, UAF, data race, uninitialized read, strict aliasing, bad shift.

## Concurrency must-says
Data race (UB) ≠ race condition · mutex (owner) vs semaphore (count) · `cv.wait(lk, pred)` always · 2 condvars in a bounded queue + close() · deadlock = circular wait → lock ordering / `scoped_lock` · acquire/release publishing · false sharing → `alignas(64)` · Amdahl · TSan · determinism: sort by ID, fixed-order merge/reduction.

## Performance must-says
Numbers: L1 1 ns · L3 ~12 ns · DRAM ~100 ns · line 64 B. Method: **measure → profile (where, why) → change → A/B → CI guard**. Tools: perf (stat/record/flame/c2c), AMD uProf, VTune, valgrind/callgrind/massif, heaptrack, ASan/UBSan/TSan, gdb (`thread apply all bt`, watch, core). Data layout: **32-bit ids, SoA, CSR, arenas, string interning**.

## EDA must-says
Flow: synth → opt → place → phys_opt → route → STA → bitstream (+ DCP checkpoints). Setup = max-delay check, hold = min-delay check; slack = required − arrival; WNS/TNS. STA = topo-order longest path (forward max, backward min). Incremental = the cone in level order with early stop. Partition FM/multilevel · place SA/analytic + legalize · route Lee/A* + PathFinder (history + present cost) · AIG/strash, SAT for datapaths, K-LUT cut mapping. Scale + NP-hard + determinism + incrementality = why EDA is hard.

## Lead must-says
Stories ready (STAR + numbers): **perf win** · **cross-team change (the decoupling)** · **ambiguous program you drove (licensing)** · **customer-facing ownership (coverage)** · **conflict/disagreement** · **mentoring** · **failure + lesson**. The AI-tools answer: concrete use + verification + confidentiality + team enablement.

## Your 2 questions for them
1. "What are the biggest runtime/QoR bottlenecks the team is attacking this year, and how is performance tracked?"
2. "What would success look like for this Lead role in the first 6 months?"
