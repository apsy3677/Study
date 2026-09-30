# Day 3 Quiz: graphs, DP, bits, EDA (20 min)
Grade 0–3 with [answers/Day3-Answers.md](answers/Day3-Answers.md). Max 60.

1. BFS vs Dijkstra vs 0-1 BFS vs Bellman-Ford: when do you use each?
2. Why mark a node visited when you *push* it in BFS rather than when you pop it?
3. Bipartite check: the algorithm, the failure condition, and the classic trap.
4. Directed cycle detection: why does a simple `visited` array give false positives? What's the fix?
5. Kahn's algorithm: how do you detect a cycle, and how do you get levelization for free?
6. Union-Find: the two optimizations, and the resulting complexity.
7. When would you use SCC in an EDA tool?
8. DP recipe: the 5 steps. Which step causes most wrong answers?
9. Coin change "number of ways": show the two loop orders and what each counts.
10. 0/1 knapsack 1D: why iterate capacity downward?
11. LIS in O(n log n): what does `tails[k]` mean, and why is `tails` sorted?
12. Edit distance recurrence and base cases.
13. Five bit tricks from memory, including "isolate the lowest set bit" and "is a power of two".
14. STA: the forward and backward propagation formulas and the slack formula. What is WNS?
15. Setup vs hold: which gets worse with more clock skew toward the capture flop? (Positive skew = capture clock arrives later.)
16. Incremental timing: a delay of one arc changes. Which nodes need recomputation, and in what order?
17. Explain the PathFinder cost function and why the history term exists.
18. Simulated annealing placement: the move, the acceptance rule, and how you compute ΔHPWL cheaply.
19. **(transfer)** In a netlist graph with 50M nodes, your recursive DFS crashes with a segfault. Why, and what do you do?
20. **(transfer)** You must find the K most critical paths (worst slack) in a timing DAG without enumerating all paths. Outline an approach.
