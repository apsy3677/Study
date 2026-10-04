# 06-Practice: compile, run, get feedback, no spoilers

Each `dayN.cpp` has **stubs** (function signatures that return dummy values) and pulls in its tests from `tests/dayN_tests.h`.
Implement a stub → compile → the test run tells you **got vs expected** per case. Hints are in the pattern files (`02-Patterns/…`, inside `<details>`).
`solutions/` holds verified reference solutions. **Open them only after your version passes, or after all hints plus 10 minutes stuck.**

| File | Problems | Pattern files |
|---|---|---|
| `day1.cpp` | 21: arrays, hashing, prefix sums, two pointers, sliding window, binary search | P01, P02, P03 |
| `day2.cpp` | 34: linked lists, stacks, heaps/intervals, **geometry**, trees, LRU, **sum of subarray minimums / ranges** | P04–P07, P12, MM03 |
| `day3.cpp` | 28: graphs, **EDA (levelize, slack/critical path, Lee router, HPWL)**, DP, trie/bits | P08, P10, P11, E2 |
| `day4.cpp` | 10: ring buffer, UniquePtr/SharedPtr, pool allocator, MyVector, blocking queue, alternating threads, parallel sum, thread pool, raw matrix | P12, C3 |

Every reference solution was compiled and run with **GCC 14 and Clang 19** under AddressSanitizer + UBSan (day4 also under ThreadSanitizer): 483/483 checks pass.

---

## 1. Get a compiler (pick one, 5 minutes)

**A. WSL Ubuntu (you already have it installed):**
```bash
sudo apt update && sudo apt install -y build-essential gdb
```
Then from Windows Terminal: `wsl`, `cd /mnt/d/Git/Study/AMD-CPP-EDA-Lead-Prep/06-Practice`.

**B. Online (zero setup, closest to the interview editor):** paste into https://godbolt.org (add `-std=c++20`, enable "Execute") or https://www.onlinegdb.com (language C++20).
Online you'll need to paste `test.h` + `dayN.cpp` + `tests/dayN_tests.h` into one file, so WSL is easier.

## 2. Build & run
```bash
g++ -std=c++20 -O1 -g -fsanitize=address,undefined day1.cpp -o day1 && ./day1
```
Run just one problem with a filter (any substring of the test name):
```bash
./day1 trap
```
```bash
./day2 LRU
```
Day 4 needs threads:
```bash
g++ -std=c++20 -O1 -g -pthread -fsanitize=address,undefined day4.cpp -o day4 && ./day4 Queue
```
Race-check your threaded code (a different sanitizer, so build separately):
```bash
g++ -std=c++20 -O1 -g -pthread -fsanitize=thread day4.cpp -o day4t && ./day4t Queue
```

Output looks like:
```
-- t_trap
   FAIL line 379: trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1})
        got:      0
        expected: 6
   [FAIL] t_trap  2/5
```
The sanitizers catch out-of-bounds reads, use-after-free, leaks, UB and races. Treat a sanitizer report as a failed test.

## 3. The drill (this is what builds interview speed)
1. **Timer on.** Read the stub comment. Say the approach, invariant and complexity **out loud** (or type them to Claude) in < 3 min.
2. Write the code **without autocomplete** (plain editor, like CoderPad). Target 10–15 min.
3. Before compiling, **dry-run one example by hand**. Interviewers watch for this.
4. Compile, run the filter, fix. Log `time + bug` in `PROGRESS.md` (the bug log is gold for the night before).
5. After passing, compare with `solutions/` for **idioms** (shorter STL, better names), not just logic.

**Priority order if short on time:** the ★ items in each file. Then, per day, the ones marked ★★★ in `00-Intel/AMD-Interview-Intel.md`.

## 4. Getting hints from Claude (coach mode)
Open this repo folder in Claude Code and say, for example:
- *"P02-3 trap: my approach is prefix max arrays, O(n) space. Is it OK? How do I get O(1)?"*
- *"Review my `reverseKGroup` in day2.cpp. Don't give me the answer, just tell me what's wrong."*
- *"My BlockingQueue test hangs. Give me a level-1 hint."*

Claude follows `CLAUDE.md`: approach check first, then hints one level at a time (L1 nudge → L2 pattern → L3 insight → L4 pseudocode), and full solutions only when you type `reveal`.

## 5. Notes
- **Linked-list tests own the nodes**: relink only, don't `delete` removed nodes (mention deletion in the interview).
- Day 4 stubs leak on purpose until implemented, so a LeakSanitizer report at exit is expected at first.
- A threaded test that **hangs** = a lost wakeup / missing `notify` / missing `close()` handling. Find it before looking at the solution.
