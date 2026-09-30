# Diagnostic Test (Day 1 morning, 30 minutes, no notes)

**Purpose:** find the rust *before* studying, so your hours go to the weak spots.
**How:** answer each in 1–3 lines (on paper or in a text file). Don't look anything up. Grade yourself with [answers/00-Diagnostic-Answers.md](answers/00-Diagnostic-Answers.md):
**0** = blank or wrong · **1** = vague · **2** = correct · **3** = correct plus a lead-level insight. Max **120**.
With Claude: *"Run the diagnostic, one question at a time."*

Record the score in `PROGRESS.md` and **list every question you scored ≤ 1**. Those are your priority list.

---

### A. C++ language (12)
1. What exactly happens (memory + instructions) when you call a virtual function through a base pointer?
2. Why should a polymorphic base class have a virtual destructor? What happens without it?
3. What does `std::move` actually do? What state is a moved-from `std::string` in?
4. State the Rule of 0/3/5 in one line each.
5. `unique_ptr` vs `shared_ptr`: the size of each, and what `shared_ptr` allocates besides the object.
6. What is object slicing? Give a one-line example.
7. When does `std::vector` invalidate iterators? Why does `noexcept` on a move constructor matter to `vector`?
8. `std::map` vs `std::unordered_map`: the data structure behind each, complexities, and when you'd pick `map`.
9. What is RAII? Give two examples from the standard library.
10. `const int* p` vs `int* const p` vs `const int& r`: what can't change in each?
11. Name 5 kinds of undefined behaviour.
12. Templates vs virtual functions for polymorphism: one advantage of each.

### B. Concurrency & OS (8)
13. Mutex vs semaphore: the key difference.
14. Data race vs race condition.
15. Why must `condition_variable::wait` be given a predicate?
16. Four conditions for deadlock, and the most practical prevention.
17. Process vs thread: three differences.
18. What does `fork()` return, and what is copy-on-write?
19. What is false sharing?
20. User mode vs kernel mode: how does a program enter the kernel?

### C. DSA patterns: name the technique + complexity (12)
21. Count subarrays with sum exactly k (negatives allowed).
22. Longest substring without repeating characters.
23. Minimum speed to finish the tasks within H hours.
24. Next greater element for every array element.
25. k-th largest element in a stream.
26. Minimum meeting rooms.
27. Reverse a linked list in groups of k: which pointers do you track?
28. Detect the start of a cycle in a linked list.
29. LCA of two nodes in a binary tree (not a BST).
30. Order tasks with prerequisites; detect when impossible.
31. Number of combinations of coins to make an amount: the loop order and why.
32. O(1) get/put cache with LRU eviction: which two structures?

### D. EDA & performance (8)
33. Setup slack vs hold slack: what does each check?
34. How do you compute arrival times on a timing graph? Why must it be a DAG?
35. What is HPWL?
36. Name one algorithm each for: partitioning, placement, routing.
37. Approximate latency of an L1 hit vs a DRAM access.
38. Array-of-Structs vs Struct-of-Arrays: when is SoA faster?
39. Which tool finds a data race? A memory leak? A CPU hotspot?
40. Why would an EDA tool use 32-bit indices instead of pointers for netlist objects?
