# P08: Graphs (the EDA pattern: netlists are graphs)

> Practice file: `06-Practice/day3.cpp` · Striver: `Graphs.pdf`
> AMD reports: **Number of Islands**, **bipartite graph exercise**, DFS/BFS (Xilinx), topological sort (dependency / levelization in EDA), shortest paths.
> EDA mapping: netlist = directed graph (cells = nodes, nets = hyperedges) · **timing = longest path on a DAG** · combinational loop = **cycle / SCC** · routing = shortest path on a grid graph · clustering = union-find.

---

## Card A: Every graph problem = (state, transition, frontier order)
| Frontier order | Algorithm | Guarantees |
|---|---|---|
| FIFO queue | **BFS** | fewest edges (unweighted shortest path), level by level |
| LIFO / recursion | **DFS** | reachability, components, cycle detection, topological order (postorder) |
| min-heap by distance | **Dijkstra** | least total weight, **non-negative** weights |
| deque (0 → front, 1 → back) | **0-1 BFS** | shortest path with 0/1 weights |
| indegree-0 queue | **Kahn topo sort** | a valid dependency order; detects cycles |
| none (edge relaxation ×(V−1)) | **Bellman-Ford** | negative weights, detects negative cycles, O(VE) |
| all pairs, n ≤ 400 | **Floyd–Warshall** | O(V³) |

**Representation:** `vector<vector<int>> adj` (or `vector<pair<int,int>>` for weights). For huge static graphs (EDA): **CSR** (`offsets[]` + `targets[]`), contiguous and cache-friendly.

## Card B: BFS / DFS templates
- **Mark visited when you push** (BFS). Multi-source BFS: push all sources at distance 0 (rotting oranges, distance to the nearest X).
- DFS on a grid: recursion is fine up to ~10⁴ depth. Beyond that use an explicit stack (a 1000×1000 grid can overflow the stack!).

## Card C: Bipartite = "2-color with BFS"
| | |
|---|---|
| **Hook** | Paint the start red; neighbours must be blue; neighbours of blue must be red. A conflict means an **odd cycle** → not bipartite. |
| **Traps** | **Disconnected graph**: loop over all nodes and start a BFS from each uncolored one. |
| **Uses** | two-team split, conflict graphs, **double-patterning / mask assignment** in lithography (an EDA use), matching problems. |
| **Deep dive** | picture, BFS layers, uses, code, follow-ups: [MM04 §10](MM04-SCC-Kosaraju-Mental-Model.md#10-bipartite-two-teams-of-rivals) · [the bipartite trainer](../07-Revision/visualizers/bipartite-trainer.html) |

## Card D: Topological sort (Kahn) = "take whoever has no pending prerequisites"
| | |
|---|---|
| **Invariant** | The queue holds exactly the nodes whose predecessors are all already output. |
| **Cycle** | if `output.size() < n`, the remaining nodes are on or behind a cycle. |
| **EDA** | **levelization** of a netlist: level(v) = 1 + max level(pred). Simulation and STA evaluate in this order. Combinational loops break levelization; report them via SCC. |
| **DFS alternative** | reverse postorder; 3-color (white/gray/black), a gray→gray edge = back edge = cycle. |

## Card E: Longest / critical path on a DAG = "STA in 10 lines"
Topo order, then relax **forward** with `max`:
```
arrival[src] = 0
for u in topo:  for (v, delay) in out(u):  arrival[v] = max(arrival[v], arrival[u] + delay)
```
Backward for **required times**: `required[u] = min over v of (required[v] − delay(u,v))`, starting from `required[sink] = clock period`. **Slack = required − arrival.** Negative slack = timing violation. The critical path is traced by following the predecessors that achieved the max.
(Longest path in a general graph is NP-hard. On a DAG it's linear. That's why timing graphs must be acyclic: loops are broken at registers.)

## Card F: Dijkstra = "BFS with a priority queue"
Push `(dist, node)`; on pop, skip if stale (`d != dist[u]`); relax the neighbours. O((V+E) log V). Fails with negative edges.
**A\*** = Dijkstra with priority `g + h`, where h is an admissible heuristic (Manhattan distance on a routing grid). This is maze routing in EDA.

## Card G: Union-Find = "who's your boss's boss?"
Path compression + union by size/rank gives near O(1). Use it for dynamic connectivity, Kruskal MST, redundant connection, clustering, "accounts merge", **connectivity extraction** (which shapes/pins are electrically connected).

## Card H: SCC (Kosaraju / Tarjan) = "Finish, Flip, Flood"
> **Read first:** [MM04: the SCC mental model](MM04-SCC-Kosaraju-Mental-Model.md) (why it works, in one picture), then step through [the Kosaraju trainer](../07-Revision/visualizers/kosaraju-trainer.html) in predict mode.

| | |
|---|---|
| **Picture** | SCCs are neighborhoods of one-way streets; the map of neighborhoods is a DAG. A DFS floods downhill, so only a flood that starts at the **bottom** collects exactly one SCC. |
| **Kosaraju** | **Finish:** DFS, write each node down when it finishes. **Flip:** reverse every edge. **Flood:** latest finisher first, DFS on the flipped graph; each flood = one SCC. |
| **Why** | The last finisher is in the top SCC; the flip makes it the bottom; a flood from the bottom can't leak. |
| **Tarjan** | One DFS with `disc`/`low` + a stack; `low == disc` → pop one SCC. Update `low` from `disc[v]` only if v is **on the stack**. |
| **EDA** | **combinational loops** (an SCC of size > 1, or a self-loop) → report them to the user / break them for timing. |
| **Also** | bridges and articulation points (Tarjan `low`), which find single points of failure. |

## Card I: MST
Kruskal (sort edges + DSU) or Prim (heap). EDA: **the MST approximates the Steiner tree** for net wirelength estimation (RSMT ≤ MST ≤ 1.5 × RSMT in the rectilinear metric).

---

## Problems (hint ladders)

### P08-1 · Rotting Oranges (LC 994) ★★ · `orangesRotting`
<details><summary>Hint</summary>All rotten oranges spread at the same time. What does that do to your BFS start?</details>
<details><summary>Approach check</summary>Multi-source BFS by levels; count the fresh ones; if any remain → −1. O(RC).</details>

### P08-2 · Is Graph Bipartite? (LC 785) ★★★ · `isBipartite`
Adjacency list; the graph may be disconnected.
<details><summary>Hint</summary>Colors 0/1 with −1 = uncolored. What makes it fail?</details>
<details><summary>Approach check</summary>BFS from every uncolored node; neighbour with the same color → false. O(V+E). Follow-up: "Possible Bipartition" (LC 886) = build the graph from dislikes (**MM04-5** in `day3.cpp`). Follow-up 2: return the odd cycle as proof (**MM04-6**).</details>

### P08-3 · Course Schedule II / build order (LC 210) ★★★ · `findOrder`
<details><summary>Approach check</summary>Kahn. Return empty if a cycle exists. Edge direction: prerequisite → course. Follow-up: "minimum semesters" = BFS levels = **levelization**.</details>

### P08-4 · Network Delay Time (LC 743) ★★ · `networkDelayTime`
Signal from k; time for all nodes to receive it (or −1).
<details><summary>Approach check</summary>Dijkstra; the answer is the max dist; any INF → −1. O(E log V).</details>

### P08-5 · Number of Connected Components / Redundant Connection (LC 323/684) ★★ · `countComponents`, `findRedundantConnection`
<details><summary>Approach check</summary>DSU. Components = n − successful unions. Redundant edge = the first edge whose endpoints are already connected.</details>

### P08-6 · Detect a cycle in a directed graph (combinational loop) ★★ · `hasCycleDirected`
<details><summary>Hint</summary>Why doesn't the undirected "visited" check work here?</details>
<details><summary>Approach check</summary>3-color DFS (a gray neighbour means a back edge) or Kahn (count < n). O(V+E). For reporting the loops themselves → SCC.</details>

### P08-7 · Mini-STA: worst slack & critical path on a DAG ★★ (EDA) · `worstSlack`, `criticalPath`
Given a DAG with edge delays, primary inputs (indegree 0) arriving at t=0, and a required time `T` at every primary output (outdegree 0): return the worst (minimum) slack over all nodes, and the list of nodes on one critical (longest) path.
<details><summary>Hint 1</summary>Arrival times need all predecessors to be done. Which order guarantees that?</details>
<details><summary>Hint 2</summary>Required times propagate backwards with `min`. Slack = required − arrival.</details>
<details><summary>Approach check</summary>Topo order; forward max pass storing `pred[v]`; backward min pass; worst slack = min over nodes (= T − the longest path). Critical path: start at the PO with max arrival and follow pred back. O(V+E). Lead follow-up: **incremental** update when one delay changes → only re-propagate the fanout cone (forward) and the fanin cone (backward), using a level-ordered priority queue so each node is processed once.</details>

### P08-8 · Number of Islands (LC 200) ★★★ (in the toolkit: re-type it blind in < 6 min)
Follow-up: "the grid is 100k × 100k and streamed row by row" → union-find with only 2 rows in memory.

### P08-9 · Word Ladder (LC 127) ★
<details><summary>Approach check</summary>BFS over words; neighbours via changing each char a..z and checking a set. Bidirectional BFS for speed.</details>

### P08-10 · Kosaraju SCC count ★ · `countSCC`
<details><summary>Approach check</summary>Finish, Flip, Flood. Pass 1: DFS, push nodes in finish order. Pass 2: on the flipped graph, DFS from the latest finisher first; count the floods. O(V+E). Use iterative DFS for big graphs.</details>

More SCC practice in `day3.cpp`: **MM04-1** labels in topological order, **MM04-2** combinational-loop nodes (EDA), **MM04-3** fewest edges to make the graph strongly connected, **MM04-4** Tarjan. Hints: [MM04 §12](MM04-SCC-Kosaraju-Mental-Model.md#12-practice-predict-then-verify-the-trainer-has-these-graphs-as-presets).

---

## Recall check
1. Frontier order → algorithm table from memory. 2. Why mark visited on push? 3. Bipartite failure condition + the disconnected trap. 3b. Kosaraju in three words, and why the flip plus "latest finisher first" stops the flood from leaking.
4. Kahn's cycle detection. 5. STA: forward pass op, backward pass op, slack formula. 6. Why is longest path easy on a DAG but NP-hard in general?
7. CSR representation: what arrays, and why is it faster than `vector<vector<int>>`?
