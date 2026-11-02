# 09 · Drill code (C++ interview practice)

Every file compiles on its own and has a `main()` that checks itself (expected output in a comment, or an OK / mismatch
line). These are the reference answers that `../../Candidate-Mode-Prompt.md` (study mode) points to.

**Build and run:** `g++ -std=c++20 -O2 -Wall -pthread file.cpp -o x && ./x`
**Race check:** `g++ -std=c++20 -g -O1 -pthread -fsanitize=thread file.cpp -o x_tsan && ./x_tsan`
(on WSL2 run it as `setarch x86_64 -R ./x_tsan`, otherwise TSan stops with "unexpected memory mapping").

## Concurrency (read `CONCURRENCY-SUMMARY.md` first: one board + one waiting room, the 4 K's, the bug table)
| File | What it shows | Self-check |
|---|---|---|
| `blocking_queue.cpp` | bounded queue: mutex + 2 CVs, predicate waits, notify on every put/take; 10 producers → 1 writer | 50/50 lines |
| `foobar.cpp` | LC 1115 with a `turn` flag + 1 CV; print → flip → notify under the lock | bar-first run + 100k rounds OK, TSan clean |
| `foobar_semaphore.cpp` | the same with 2 `binary_semaphore` jars (one baton); POSIX `sem_t` fallback in a comment | 100k rounds OK |
| `dining_philosophers.cpp` | LC 1226: lower-numbered fork first; `./x naive` shows the left-first deadlock | 10k meals, 0 clashes, TSan clean |
| `lru_threadsafe.cpp` | one-mutex wrapper + 16-shard LRU; `./x race` runs the unguarded cache so TSan reports the race | 8 × 20k ops TSan clean |
| `shared_ptr.cpp` | SharedPtr from scratch: the 4 verbs, atomic count, self-assign, move | copy/move/assign trace + 8 × 100k copies |

## DSA
| File | Problem(s) | Key line to remember |
|---|---|---|
| `lru_cache.cpp` | LC 146 LRU | `dll.splice(dll.begin(), dll, it)`: where, from, which; the node keeps its key for eviction |
| `lfu_cache.cpp` | LC 460 LFU (+ 200k random ops vs O(n) brute: 0 mismatches) | count → list bucket + `minFreq`; `to.splice(to.begin(), from, it)` moves a node between buckets; a new key resets `minFreq = 1` |
| `zombie_demo.cpp` | zombie / wait / orphan (`./x zombie\|wait\|orphan`, then `ps -o pid,ppid,stat,cmd`) | the row stays until the parent `waitpid`s |
| `splice_demo.cpp` | how `splice` moves a node (same address) vs erase + insert | |
| `sliding_window.cpp` | LC 3, LC 76 (missing + formed versions) | longest: shrink while bad, then record · shortest: record while good, then shrink |
| `spiral.cpp` | LC 54 | check `top <= bot` / `l <= r` before going back |
| `rotate_image.cpp` | LC 48 (two flips, and rings) | transpose with `j = i + 1`, then reverse each row |
| `islands.cpp` | LC 200 (DFS + BFS); `./x bigdfs` shows the recursion segfault | BFS: mark when pushing |
| `top_k_frequent.cpp` | LC 347 (min-heap of size k, bucket by count) | top k largest → min-heap |
| `tree_path.cpp` | LC 236 LCA + path between two nodes (2 ways) | "found below on both sides → me" |

## Notes still to come (the prompt already links them; until they exist, use `../03-Cpp-Deep/C4` and `C5`)
| File | Topic |
|---|---|
| `LINUX-PROCESSES.md` | fork/exec, zombies + SIGCHLD, SIGTERM vs SIGKILL, signal handlers, daemons, gdb attach, core dumps, strace, /proc |
| `BUILD-SYSTEMS.md` | wrong-way includes (find / prevent / CI guard), dependency cycles, `.d` files, ccache / PCH, make vs ninja, measuring build time |
