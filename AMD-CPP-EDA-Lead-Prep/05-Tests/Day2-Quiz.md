# Day 2 Quiz: lists, stacks, heaps, trees, design DS, concurrency (20 min)
Grade 0–3 with [answers/Day2-Answers.md](answers/Day2-Answers.md). Max 60.

1. Write (in words or code) the 4 steps inside the loop of an iterative list reversal.
2. Reverse in k-groups: what do you initialize `prev` to when reversing a group, and why does that remove a reconnection step?
3. Why does the Floyd cycle-start trick work? (The distance argument.)
4. Palindrome linked list in O(1) space: the 3 primitives, and the lead-level extra step.
5. Why do linked lists usually lose to vectors in real performance, even for middle insertions?
6. Monotonic stack for "next greater": what's in the stack, in what order, and why is it O(n)?
7. Largest rectangle in a histogram: when bar j is popped at index i, what's its width?
8. Meeting rooms: how do you handle a meeting ending at 10 and another starting at 10 (half-open intervals) in the heap version and the sweep version?
9. Running median: which heaps, and what's the balancing invariant?
10. Tree recursion: give one "bottom-up" and one "top-down" problem, and say what flows in which direction.
11. Why is checking `left->val < node->val < right->val` at each node NOT enough to validate a BST? Give a counterexample.
12. `std::map` is an RB tree. Why RB instead of AVL?
13. LRU cache: what exactly is stored in the hash map, and which `std::list` operation makes "move to front" O(1)?
14. Ring buffer: three ways to distinguish full from empty.
15. What's inside a `shared_ptr` control block? Which operations are atomic, and with which memory order is the decrement done?
16. Why must a `condition_variable` wait be in a loop/predicate, and why use two condvars in a bounded queue?
17. What is the ABA problem, and where does it bite?
18. **(debug)** `for (auto it = m.begin(); it != m.end(); ++it) if (it->second == 0) m.erase(it);`: what's wrong? Fix it.
19. **(transfer)** Design a data structure for O(1) insert, delete and getRandom.
20. **(transfer)** Given a binary tree, return the maximum sum of any path (it can start and end anywhere). State the recursion's return value vs the global update.
