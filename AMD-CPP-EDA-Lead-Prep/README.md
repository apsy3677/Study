# AMD — Lead Software Development Engineer (C++/EDA): 4-Day Course

Built for **Anuj**: about 11 years of experience (Synopsys DPV/formal, Microsoft, Adobe), not writing much C++ day to day right now, and last did DSA in Mar–Apr 2023 (Striver).
Goal: **clear AMD round 1**, then keep the mental models for later rounds and future interviews.

> **Where this role most likely sits.** AMD's Hyderabad "C++/EDA" openings are the **Vivado FPGA toolchain**: logic synthesis and optimization, place and route, timing. The Lead JD says to *"lead a team to improve the performance of key applications and benchmarks using C++ and Linux"*, and it asks for concurrent programming, threading APIs, debuggers and profilers.
> Expect **C++ depth, performance, concurrency, DSA in C++, and your projects**. Your formal-verification and EDA background is an asset, so use it.
> The evidence is in [00-Intel/AMD-Interview-Intel.md](00-Intel/AMD-Interview-Intel.md).

---

## 1. How the course works (3 modes)

| Mode | When | How |
|---|---|---|
| **Read** (solo, phone/laptop) | Commute, low energy, last night | Read the **Mental Model** box, **Triggers**, **Template** and **Traps** in each file. Skip the problems. |
| **Test** (solo) | Most of your time | Quizzes in `05-Tests/` have the answers in a separate folder. Practice problems in `06-Practice/` come with **tests you compile and run**. Hints sit in folded `<details>` blocks, so open one level at a time. |
| **Coach** (with Claude) | When you can | Open this folder in Claude Code (or paste [05-Tests/Coach-Prompt.md](05-Tests/Coach-Prompt.md) into any Claude chat). Then say: *"Quiz me on Day 2"*, *"I want to solve P04-3, here's my approach…"*, *"Run Mock 1"*, *"Review my code in 06-Practice/day2.cpp"*. Claude gives **hints only**, grades you, and logs weak spots in [PROGRESS.md](PROGRESS.md). |

**The rule for every problem:** *say the approach out loud → write the invariant → then code.* You're practising the interview, not just the answer.

---

## 2. The 4-day plan

Every day has a **MUST** core of about 5–6 hours, and **SHOULD** blocks if you have the time. Start each morning with a **15-minute spaced review** of the day before.

### Day 1: C++ reload + speed + array patterns
| Block | Time | What | File |
|---|---|---|---|
| MUST | 30m | **Diagnostic test**: find your rust before you study | [05-Tests/00-Diagnostic.md](05-Tests/00-Diagnostic.md) |
| MUST | 90m | C++ object model, vtable, special members, slicing, UB | [03-Cpp-Deep/C1-Object-Model.md](03-Cpp-Deep/C1-Object-Model.md) |
| MUST | 60m | Modern C++: move, smart pointers, RAII, STL internals | [03-Cpp-Deep/C2-Modern-Cpp-and-STL.md](03-Cpp-Deep/C2-Modern-Cpp-and-STL.md) |
| MUST | 60m | **Speed playbook**, then type the toolkit from memory | [01-Speed-Cpp/Speed-Coding-Playbook.md](01-Speed-Cpp/Speed-Coding-Playbook.md) |
| MUST | 30m | Pattern map (the decision tree) | [02-Patterns/00-Pattern-Map.md](02-Patterns/00-Pattern-Map.md) |
| MUST | 90m | P01 Arrays/Hashing/Prefix, P02 Two-pointer/Window, P03 Binary Search | `02-Patterns/P01..P03` |
| MUST | 60m | Code the ★ problems in `06-Practice/day1.cpp` (timed: 12–15 min each) | [06-Practice](06-Practice/README.md) |
| SHOULD | 30m | Tricky snippets 1–13 | [03-Cpp-Deep/C6-Tricky-Snippets.md](03-Cpp-Deep/C6-Tricky-Snippets.md) |
| MUST | 20m | Day 1 quiz | [05-Tests/Day1-Quiz.md](05-Tests/Day1-Quiz.md) |

### Day 2: data structures that AMD asks + concurrency
| Block | Time | What | File |
|---|---|---|---|
| MUST | 15m | Spaced review: Day 1 flashcards (C++ + P01–P03) | [07-Revision/Flashcards.md](07-Revision/Flashcards.md) |
| MUST | 60m | P04 Linked List (AMD asks these **a lot**) | `02-Patterns/P04` |
| MUST | 45m | P05 Stack / Monotonic, P06 Heap / Intervals / Sweep | `02-Patterns/P05, P06` |
| MUST | 60m | P07 Trees & BST | `02-Patterns/P07` |
| MUST | 45m | P12 Design DS: **LRU**, ring buffer, `shared_ptr`, pool allocator | `02-Patterns/P12` |
| MUST | 90m | Concurrency + memory model; code a thread-safe queue from memory | [03-Cpp-Deep/C3-Concurrency.md](03-Cpp-Deep/C3-Concurrency.md) |
| MUST | 60m | Code the ★ problems in `06-Practice/day2.cpp` | |
| SHOULD | 30m | Tricky snippets 14–28 | C6 |
| MUST | 20m | Day 2 quiz | [05-Tests/Day2-Quiz.md](05-Tests/Day2-Quiz.md) |

### Day 3: graphs, DP, EDA algorithms
| Block | Time | What | File |
|---|---|---|---|
| MUST | 15m | Spaced review: Day 2 flashcards, plus Day 1 quiz misses | |
| MUST | 90m | P08 Graphs: BFS/DFS/Topo/Dijkstra/DSU/Bipartite/SCC | `02-Patterns/P08` |
| MUST | 75m | P10 DP (coin change, LIS, LCS, knapsack, edit distance) | `02-Patterns/P10` |
| SHOULD | 30m | P09 Backtracking, P11 Trie/Bits/Math | `02-Patterns/P09, P11` |
| MUST | 45m | EDA/FPGA/Vivado primer (the vocabulary) | [04-EDA-Domain/E1-EDA-FPGA-Vivado-Primer.md](04-EDA-Domain/E1-EDA-FPGA-Vivado-Primer.md) |
| MUST | 75m | EDA algorithms: STA on DAG, partitioning, placement, routing, geometry | [04-EDA-Domain/E2-EDA-Algorithms.md](04-EDA-Domain/E2-EDA-Algorithms.md) |
| MUST | 60m | Code the ★ problems in `06-Practice/day3.cpp` | |
| MUST | 20m | Day 3 quiz | [05-Tests/Day3-Quiz.md](05-Tests/Day3-Quiz.md) |

### Day 4: performance, Linux, design, lead signals, mocks
| Block | Time | What | File |
|---|---|---|---|
| MUST | 15m | Spaced review: Day 3 flashcards + all quiz misses so far | |
| MUST | 75m | Performance, profiling, Linux, debugging war stories | [03-Cpp-Deep/C4-Performance-Linux-Debugging.md](03-Cpp-Deep/C4-Performance-Linux-Debugging.md) |
| MUST | 45m | OS fundamentals (fast pass) | [03-Cpp-Deep/C5-OS-Fundamentals.md](03-Cpp-Deep/C5-OS-Fundamentals.md) |
| MUST | 60m | EDA system design (netlist DB, incremental timing, parallel router) | [04-EDA-Domain/E3-EDA-System-Design.md](04-EDA-Domain/E3-EDA-System-Design.md) |
| MUST | 45m | Lead / behavioral + project deep-dive prep | [08-Lead-and-Projects/Lead-Behavioral-and-Projects.md](08-Lead-and-Projects/Lead-Behavioral-and-Projects.md) |
| MUST | 60m | **Mock 1** (Round-1 screen simulation) | [05-Tests/Mock-Interviews.md](05-Tests/Mock-Interviews.md) |
| SHOULD | 60m | Code `06-Practice/day4.cpp` (systems coding) + Mock 2 | |
| MUST | 20m | Day 4 quiz, then read the **one-page recall sheet** | [07-Revision/One-Page-Recall.md](07-Revision/One-Page-Recall.md) |

**Interview morning:** follow [07-Revision/Interview-Day-Checklist.md](07-Revision/Interview-Day-Checklist.md). It takes 30 minutes and has no new material.

> **Only 3 days?** Merge Day 4 into the evenings: do C4 and E3 on Day 3 evening, and Mock 1 plus Lead prep on the interview eve.

---

## 3. The retention system (so this sticks after the interview)

Every pattern and concept is written in the same **5-part card**. Your brain stores the *card*, not the text:

1. **Hook**: a one-line image or metaphor ("monotonic stack = a waiting room; a taller person resolves everyone shorter").
2. **Triggers**: words in a problem that should fire this pattern.
3. **Invariant**: the *one* sentence that stays true inside your loop. If you can say it, you can code it.
4. **Skeleton**: the 8–15 line C++ template you type without thinking.
5. **Traps**: the 3–5 bugs you'll make under pressure.

**Spaced review schedule** (active recall means close the file and answer from memory):

| When | What |
|---|---|
| Next morning | That day's flashcards + quiz misses |
| +3 days | Pattern Map + Recall Sheet |
| +1 week | 1 problem per pattern (just approach + invariant, no code) |
| +1 month | Diagnostic test again |

Import [07-Revision/flashcards_anki.tsv](07-Revision/flashcards_anki.tsv) into **Anki** (or AnkiDroid on your phone) to automate this.

---

## 4. Folder map

```
AMD-CPP-EDA-Lead-Prep/
├── README.md                ← you are here (plan)
├── CLAUDE.md                ← makes Claude a hint-only coach when opened in this folder
├── PROGRESS.md              ← your tracker (Claude updates it too)
├── 00-Intel/                ← what AMD asks: sourced question bank, ranked by probability
├── 01-Speed-Cpp/            ← speed playbook + cpp_toolkit.cpp (type-from-memory reference)
├── 02-Patterns/             ← P01..P12 DSA patterns as 5-part cards + hint-ladder problems
├── 03-Cpp-Deep/             ← C1..C6 theory: object model, modern C++, concurrency, perf/Linux, OS, tricky snippets
├── 04-EDA-Domain/           ← E1 primer, E2 algorithms, E3 EDA system design
├── 05-Tests/                ← diagnostic, daily quizzes (answers separate), mocks, coach prompt
├── 06-Practice/             ← compile-and-run problem files with tests (+ spoiler solutions)
├── 07-Revision/             ← flashcards (+Anki), one-page recall, interview-day checklist
└── 08-Lead-and-Projects/    ← lead/behavioral + project deep-dive (secondary)
```

## 5. Map to your old Striver notes (`..\Striver-Notes-DSA`)

| Pattern here | Re-read in Striver (only if the card here isn't enough) |
|---|---|
| P07 Trees/BST | `Trees-BT-BST.pdf` (LCA, views, BST ops) |
| P08 Graphs | `Graphs.pdf` (topo, Dijkstra, DSU, SCC/Kosaraju, bridges) |
| P09 Backtracking | `Recursion.pdf` |
| P10 DP | `DP-Problems.pdf` (DP on stocks, LIS, partitions, MCM) |
| P11 Trie | `Trie.pdf` |
| All | `Striver-SDE-Sheet.pdf`: use as a problem pool **after** this course |

The PDFs are 10–70 MB of slides. Use them as a **lookup**, not a re-read. This course compresses them into recall cards.
