# AMD Interview Intel: Lead SDE C++/EDA (researched 30 Sep 2026)

> **Honesty note.** Very few public reports exist for this *exact* title. I combined four sources:
> (a) AMD's C++/EDA job descriptions (Hyderabad, Vivado),
> (b) AMD C++ and senior SWE interview reports from mid-2024 to 2026 (LeetCode Discuss, AmbitionBox, Glassdoor snippets, aggregators),
> (c) peer EDA-company rounds (including **your own Cadence R1 notes** in `..\I-2025\Cadence-R1.txt`),
> (d) what a Lead/perf-focused C++ JD implies.
> Everything is tagged with its source, so you can judge the weight yourself.

---

## 1. The role, decoded

| JD phrase | What they will actually probe |
|---|---|
| "Lead a team to improve the **performance** of key applications and benchmarks using **C++ and Linux**" | Profiling (perf, VTune/**AMD uProf**, valgrind), cache-friendly data layout, allocation cost, multithreading speedups, how you *measured* a win. **Have 2 perf stories ready.** |
| Vivado: "core **logic synthesis and optimization** … performance, scalability and **QoR** of the FPGA implementation software" | EDA vocabulary (synth → opt → place → route → timing), graph algorithms on netlists, scale (millions of cells), determinism. |
| "Modern **concurrent programming** and threading APIs" | `std::thread`/mutex/condvar/atomics, thread-safe queue, thread pool, deadlock, data race vs race condition, false sharing, memory model. |
| "Debuggers, source control, **profilers**" | gdb war stories, core dumps, sanitizers, bisecting regressions. |
| "Lead … drive sophisticated issues to resolution … work across teams" | Behavioral: ownership, mentoring, cross-team conflict, technical decisions, prioritization. |

## 2. What round 1 probably looks like (60 min, Teams/Zoom, shared editor)

Based on several reports ("panel of two engineers, 15 min background, then technical"; "R1 easy+medium LeetCode + CV emphasis"):

```
 0–15  Intro + resume walk-through → they pick 1 project and drill (perf, design choices, your role)
15–35  C++ / OS / concurrency rapid-fire (vtable, smart pointers, move, mutex vs semaphore, …)
35–60  1–2 coding problems in C++ (LeetCode easy–medium, often linked list / array / DP / design like LRU)
```
**Lead-level twist:** expect follow-ups like "how would this behave with 100M elements?", "make it thread-safe", "how would you test it?".

---

## 3. Reported questions (sourced)

### 3.1 AMD, C++ roles, 2025–2026
| Source (date) | Role | Questions |
|---|---|---|
| LeetCode Discuss #6837239 (Jun 2025) | C++ Developer | **R1:** 3 DSA: array logic, string manipulation, **Coin Change (DP)**. **R2:** OOP concepts, SQL queries, *stock price "sell first then buy"*, **multithreading & concurrency**. **R3:** OS (scheduling, memory, threads), networks (protocols/layers), OOP design/real-world modeling, project ownership & design choices |
| LeetCode Discuss #7569749 (via search summary, 2025–26) | Senior SWE, uProf (profiler) team | **R1:** easy+medium LeetCode, CV focus. **R2:** OS: mutex, semaphore, child process, `fork`, kernel vs user mode, process states, threading; **caches, LRU cache** |
| LeetCode Discuss #7577981 (Feb 2026) | Sr. Software System Designer, Hyderabad | 3 rounds: **DSA in C++**, current work, architecture-level topics |
| TechPrep AMD guide (2026) | SWE (various) | Spiral Matrix, Rotate Image, **Trapping Rain Water**, matrix & **bit manipulation**, Coin Change, **segment tree**; **ring buffer, custom memory allocator**; **debugging buggy code / race conditions**; virtual functions, RAII, smart pointers; design **multi-level cache**, **virtual memory**; behavioral on **how you use AI tools (Copilot/LLMs)** |
| AmbitionBox AMD (2025–26) | SDE / System SWE | **How are smart pointers implemented internally**; virtual function + example; remove duplicates from sorted LL; remove element from LL; **reverse LL in groups of K**; rotate list by k; **merge two sorted lists without extra space**; middle of LL; mirror a BST; implement stack/queue; LL using stack; kernel vs user mode; **implement file sorting in C++**; **allocate n×m matrix dynamically using pointers**; blocking vs non-blocking |
| Glassdoor snippets (2024–25) | SDE, Hyderabad | C++ core + **bit masking** + DSA; project explanation; vtable/vptr internals; smart pointers, lambdas, move semantics, Rule of 3/5; mutex vs semaphore; **thread-safe queue**; **bipartite graph** exercise; BST that degrades on a sorted stream → AVL/Red-Black; rain water; height-balanced tree |
| Aggregators (CodeJeet/LeetCode tag) | all | Two Sum, Roman↔Integer, **Number of Islands**, **Spiral Matrix**, **Merge Intervals**, Merge Sorted Array, **Longest Substring w/o Repeating**, Climbing Stairs, **Subarray Sum = K**, **LRU Cache**, Palindrome Number, **3Sum**, Middle of LL, Move Zeroes, **Top K Frequent**, Palindrome LL |

### 3.2 Peer EDA companies (the same interviewer pool moves between AMD/Xilinx, Synopsys, Cadence, Siemens)
| Source | Questions |
|---|---|
| **Your Cadence R1** (`I-2025/Cadence-R1.txt`) | **Print path between two nodes in a binary tree (LCA)**; **min meeting rooms (heap)**; **do two rectilinear segments intersect / rectilinear polygon edges** |
| Synopsys/Cadence reports (2025–26) | Reverse words in string; `a^b % c` (fast power); merge sort / quick sort; add two numbers (LL); `atoi`; `printf`/UNIX signals/multithreading in C; STA basics (setup/hold, slack); DEF/LEF, congestion |
| Xilinx (pre-merger, Hyderabad) | C/C++ written test; DSA (trees, graphs, DFS/BFS); OOD; scripting (Tcl/Python/shell); puzzles |

---

## 4. The probability-ranked list (study in this order)

★★★ = very likely in R1 · ★★ = likely in some round · ★ = possible / lead-level follow-up

### C++ language (03-Cpp-Deep C1, C2, C6)
- ★★★ Virtual functions: how `vtable`/`vptr` work, cost, what happens in constructor/destructor, virtual destructor
- ★★★ Smart pointers: `unique_ptr` vs `shared_ptr` vs `weak_ptr`, **how `shared_ptr` is implemented** (control block, atomic refcount), cycles, `make_shared`
- ★★★ Move semantics, `std::move` vs `std::forward`, Rule of 0/3/5, copy elision
- ★★★ RAII (and why it matters for exceptions and locks)
- ★★ Object slicing, diamond / virtual inheritance, `sizeof` of classes (padding, vptr, empty class)
- ★★ STL internals: `vector` growth and iterator invalidation, `map` (RB tree) vs `unordered_map` (buckets/rehash), when each wins
- ★★ Lambdas (capture semantics, closure type), templates vs virtual (static vs dynamic polymorphism, CRTP)
- ★★ `const` correctness, references vs pointers, `static`, `inline`, `volatile` (and why it's **not** for threads)
- ★★ "Find the bug / predict the output" without running (C6)
- ★ UB catalogue, `new` vs `malloc`, placement new, custom allocators, `noexcept` and move in `vector` growth

### Concurrency & OS (C3, C5)
- ★★★ Mutex vs semaphore vs spinlock; deadlock conditions and prevention
- ★★★ **Implement a thread-safe (bounded) queue** / producer–consumer with `condition_variable`
- ★★★ Process vs thread; `fork` (+ copy-on-write); user vs kernel mode; process states
- ★★ Atomics & memory ordering (acquire/release), data race vs race condition, false sharing
- ★★ Virtual memory, paging, TLB, page faults; stack vs heap; memory layout of a process
- ★★ Thread pool design; parallelizing a loop; determinism in parallel algorithms
- ★ Scheduling algorithms; IPC; TCP vs UDP / OSI layers (reported once for a C++ role)

### Performance / Linux / debugging (C4), which is the JD's core
- ★★★ "How did you improve performance?" Tell a measured story: profile → hypothesis → change → numbers
- ★★ Cache-friendly design (AoS vs SoA, contiguous memory), allocation overhead, avoiding copies
- ★★ perf / valgrind / gdb / sanitizers: what each finds
- ★ Debug scenarios: crash only in release, memory growth, non-deterministic results

### DSA (02-Patterns, 06-Practice)
- ★★★ **Linked lists**: reverse (whole / k-group), merge sorted, middle, cycle, rotate, remove duplicates, palindrome
- ★★★ **LRU Cache** (hash map + DLL)
- ★★★ Arrays: Two Sum, Subarray Sum = K, 3Sum, Merge Intervals, Spiral / Rotate matrix, Trapping Rain Water, Move Zeroes, stock buy-sell
- ★★★ Strings: longest substring without repeat, reverse words, atoi, Roman numerals
- ★★ Trees: LCA + path between nodes, balanced check, BST validate / kth / mirror, level order
- ★★ Graphs: islands, **bipartite**, topological sort, Dijkstra, union-find
- ★★ DP: Coin Change (min coins / #ways), climbing stairs, LIS, knapsack
- ★★ Heaps / intervals: Top-K, meeting rooms, merge k lists
- ★★ Bits: count bits, power of two, swap without temp, set/clear/toggle, masks
- ★ Segment tree / Fenwick (range queries), trie

### Systems coding (P12, day4.cpp)
- ★★★ LRU cache · ★★ ring buffer · ★★ `shared_ptr`/`unique_ptr` from scratch · ★★ pool / arena allocator · ★ 2D matrix with raw pointers · ★ external sort ("sort a file bigger than RAM")

### EDA (04-EDA-Domain)
- ★★ Walk the flow: RTL → synthesis → place → route → STA → bitstream; what is slack / WNS / TNS / setup / hold
- ★★ Netlist as a graph: topological/levelized traversal, detect combinational loops (SCC), longest path = critical path
- ★ Partitioning (FM/KL), placement (SA/analytic, HPWL), routing (Lee/A*/PathFinder), geometry (interval / segment trees, sweep line)
- ★ Design: netlist database for 100M cells; incremental timing; deterministic parallel router

### Lead / behavioral (08-Lead-and-Projects)
- ★★★ Deep-dive on your top project (they WILL drill)
- ★★★ Why AMD / why leave Synopsys / why this role
- ★★ Mentoring, conflict, disagreement with manager/architect, a failure, handling ambiguity
- ★★ **How you use AI tools in daily engineering** (explicitly reported for AMD in 2025–26)

---

## 5. Sources
- [LeetCode Discuss: AMD C++ Developer interview experience (Jun 2025)](https://leetcode.com/discuss/post/6837239/)
- [LeetCode Discuss: AMD Sr Software System Designer, Hyderabad (Feb 2026)](https://leetcode.com/discuss/post/7577981/)
- [LeetCode Discuss: AMD interview experience, uProf team (post 7569749)](https://leetcode.com/discuss/post/7569749/)
- [TechPrep: AMD interview process (2026)](https://www.techprep.app/blog/amd-interview-process)
- [AmbitionBox: AMD interview questions](https://www.ambitionbox.com/interviews/advanced-micro-devices-interview-questions)
- [CodeJeet: AMD LeetCode problems](https://codejeet.com/company/amd)
- [Interview Query: AMD Software Engineer guide](https://www.interviewquery.com/interview-guides/amd-software-engineer)
- [AMD careers: LEAD C++ EDA Software Developer, Hyderabad](https://careers.amd.com/careers-home/jobs/81237?lang=en-us) (listing now expired; JD text via search snippets)
- [Glassdoor: AMD Software Engineer interview questions](https://www.glassdoor.com/Interview/AMD-Software-Engineer-Interview-Questions-EI_IE15.0,3_KO4,21.htm)
- [Interview Query: Synopsys SWE guide](https://www.interviewquery.com/interview-guides/synopsys-software-engineer)
- Your own notes: `D:\Git\Study\I-2025\Cadence-R1.txt`
