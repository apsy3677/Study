# Pattern Map: from problem statement to technique in 60 seconds

> Read this **before** every practice session for the next 4 days. After that, it should be automatic.
> Method: underline the **input shape** and the **ask**, then walk the tree.

## 1. The decision tree

```
What is the INPUT?
│
├── Array / String
│   ├── Sorted (or can I sort without losing the answer)?
│   │     ├── find pair/triplet with target ................ TWO POINTERS (opposite ends)      [P02]
│   │     ├── find position / boundary ..................... BINARY SEARCH                     [P03]
│   │     └── intervals (start,end) ........................ SORT + SWEEP / HEAP of ends       [P06]
│   ├── "contiguous subarray / substring" ?
│   │     ├── with a condition that grows/shrinks monotonically (all positives, ≤k distinct)
│   │     │                                   ............... SLIDING WINDOW                    [P02]
│   │     ├── sum == k with negatives ....................... PREFIX SUM + HASH MAP             [P01]
│   │     ├── max/min in every window ....................... MONOTONIC DEQUE                   [P05]
│   │     └── max subarray sum .............................. KADANE (DP)                       [P01]
│   ├── "next greater / previous smaller / span / histogram"  MONOTONIC STACK                   [P05]
│   ├── "seen before? count? complement?" ................... HASH MAP / SET                    [P01]
│   ├── "k-th largest / top k / median stream" .............. HEAP (size k) / TWO HEAPS         [P06]
│   ├── "minimize the max / maximize the min / min capacity"  BINARY SEARCH ON ANSWER           [P03]
│   ├── "all subsets / permutations / combinations" ......... BACKTRACKING                      [P09]
│   ├── "number of ways / min cost / longest ... with choices" DP                               [P10]
│   └── bits, "without extra space", "appears once" ......... XOR / BIT TRICKS                  [P11]
│
├── Linked list ............ dummy head, slow/fast, reverse-in-place, merge                     [P04]
├── Matrix / grid .......... BFS (shortest, spread) · DFS (regions) · DP (paths) · simulation   [P01/P08/P10]
├── Tree ................... "what do I need from children?" → postorder; constraints → preorder [P07]
│     BST? ................. inorder is sorted; go left/right by value
├── Graph / dependencies
│   ├── fewest edges ................................ BFS
│   ├── weighted shortest (non-negative) ............ DIJKSTRA
│   ├── order with prerequisites / DAG .............. TOPOLOGICAL SORT (Kahn)
│   ├── longest path in DAG (critical path, STA) .... TOPO + DP
│   ├── connected groups / dynamic merging .......... UNION-FIND
│   ├── 2-colorable / conflict-free split ........... BIPARTITE (BFS coloring)
│   └── cycles in directed graph / loops ............ DFS 3-color or SCC (Tarjan/Kosaraju)      [P08]
├── Strings with shared prefixes, dictionary ......... TRIE                                     [P11]
└── "Design a data structure" ........................ HASH MAP + (DLL | HEAP | DEQUE)          [P12]
```

## 2. Keyword → pattern cheat table

| If you read… | Think… |
|---|---|
| "subarray sum equals k", negatives allowed | prefix sum + `unordered_map<sum,count>` |
| "sum/count over **all** subarrays (substrings, pairs) of min / max / something one element decides" | **flip (contribution)**: per element, count the objects it decides = left choices × right choices; blockers via monotonic stack ([MM03](MM03-Stuck-At-Brute-Force.md)) |
| "longest/shortest substring with …" | sliding window (expand right, shrink left while invalid) |
| "sorted array", "find pair", "3sum" | two pointers after sort |
| "in O(log n)", "rotated", "peak", "first/last occurrence" | binary search (boundary of a predicate) |
| "minimum capacity/speed/days such that …" | binary search on the answer + greedy check |
| "next greater", "stock span", "daily temperatures", "largest rectangle" | monotonic stack |
| "maximum in each window of size k" | monotonic deque of indices |
| "top k", "k closest", "kth largest" | heap of size k (min-heap for largest) |
| "merge k sorted" | min-heap of heads |
| "intervals", "meetings", "overlap", "rooms" | sort by start; heap of ends or +1/-1 sweep |
| "islands", "regions", "flood fill" | DFS/BFS on grid |
| "shortest path unweighted", "minimum steps" | BFS |
| "prerequisites", "build order", "dependency" | topological sort |
| "connected?", "redundant edge", "groups merge over time" | union-find |
| "two groups with no edge inside a group" | bipartite check |
| "number of ways", "min coins", "can we reach" | DP (state = what's left) |
| "LCS/edit distance/two strings" | 2D DP over prefixes |
| "all combinations/permutations", n ≤ 20 | backtracking |
| "cache with eviction", O(1) get/put | hash map + doubly linked list |
| "reverse / merge / cycle" in a list | pointer surgery, dummy node, slow/fast |
| "without extra space", "single number" | XOR / in-place index marking |
| "prefix", "dictionary", "autocomplete" | trie |

## 3. Five universal questions before you code
1. **Brute force**: what is it and what's its complexity? (Say it. It anchors the discussion.)
2. **What repeated work** does brute force do? (That's what the pattern removes.)
3. **What's my invariant?** (One sentence that stays true each iteration.)
4. **What's the state** for DP or search? (The minimum info that makes the future independent of the past.)
5. **Edge cases**: empty, one element, all same, negatives, overflow, duplicates, disconnected graph.

## 4. Complexity quick reference

| Operation | Cost |
|---|---|
| sort | O(n log n) |
| `unordered_map` op | O(1) avg, O(n) worst |
| `map`/`set`/heap op | O(log n) |
| BFS / DFS | O(V + E) |
| Dijkstra (binary heap) | O((V + E) log V) |
| Topological sort | O(V + E) |
| Union-find (path compression + by size) | ~O(α(n)) ≈ O(1) |
| Binary search on answer | O(log(range) · check) |
| Backtracking subsets / permutations | O(2ⁿ · n) / O(n! · n) |
| Building a trie | O(total chars) |

## 5. Recall check (close the file)
- Name the pattern for: "min number of platforms at a station" · "longest substring with ≤ 2 distinct chars" · "subarray sum divisible by k" · "detect deadlock among lock-wait graph" · "k-th smallest in a sorted matrix" · "timing: latest arrival at each gate of a circuit".

<details><summary>Answers</summary>

Heap of end times / sweep · sliding window with count map · prefix-sum mod + hash map · cycle detection in a directed graph (DFS colors) · min-heap of row heads **or** binary search on value · topological order + longest-path DP (STA).
</details>
