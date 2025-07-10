# Finding Strongly Connected Components (SCCs) and Minimum Edges to Make a Directed Graph Strongly Connected

This document explains the concepts of Strongly Connected Components (SCCs) in directed graphs and the algorithm for finding the minimum number of edges to make a directed graph strongly connected.

## Key Concepts

### Strongly Connected Component (SCC)
A Strongly Connected Component (SCC) is a maximal subset of vertices in a directed graph where every vertex is reachable from every other vertex in the subset.

### Condensation Graph
The condensation graph is formed by contracting each SCC into a single vertex. This results in a Directed Acyclic Graph (DAG).

## Visual Representations

### Example 1: Graph with Two SCCs

```
    [0] → [1] → [2]
     ↑     |
     └─────┘     
             ↓
            [3] → [4]
```

SCCs: [0,1,2], [3,4]

Condensation Graph:
```
    [0,1,2] → [3,4]
```

- Source SCCs (in-degree = 0): 1 ([0,1,2])
- Sink SCCs (out-degree = 0): 1 ([3,4])
- Minimum edges to add: max(1,1) = 1

### Example 2: Already an SCC

```
    [0] → [1]
     ↑     ↓
     └─── [2]
```

SCCs: [0,1,2]

- This graph is already strongly connected, so minimum edges to add = 0

### Example 3: Multiple SCCs

```
    [0] → [1] → [2]      [3] → [4] → [5]
     ↑     ↓              ↑     ↓
     └─────┘              └─────┘
                           ↑
                          [6]
```

SCCs: [0,1,2], [3,4,5], [6]

Condensation Graph:
```
                [0,1,2]
                   
                [3,4,5] ← [6]
```

- Source SCCs (in-degree = 0): 2 ([0,1,2], [6])
- Sink SCCs (out-degree = 0): 2 ([0,1,2], [3,4,5])
- Minimum edges to add: max(2,2) = 2

## Kosaraju's Algorithm for Finding SCCs

Kosaraju's algorithm uses two passes of Depth-First Search (DFS) to find all SCCs in a directed graph:

1. First DFS pass: Perform DFS on the original graph and push vertices to a stack in the order of their finishing times.
2. Transpose the graph (reverse all edges).
3. Second DFS pass: Process vertices in the order defined by the stack on the transposed graph.

### First DFS Pass
The first pass creates an ordering of vertices based on their finishing times. This ordering helps in identifying SCCs in the second pass.

### Transposing the Graph
Reversing all edges ensures that during the second DFS, we stay within the same SCC.

### Second DFS Pass
Processing vertices in the order of their finishing times ensures that we process SCCs in reverse topological order.

## Algorithm for Minimum Edges to Add

1. Find all SCCs in the graph using Kosaraju's algorithm.
2. If there's only one SCC, the graph is already strongly connected, so return 0.
3. Construct the condensation graph where each SCC becomes a node.
4. Count the number of source SCCs (in-degree = 0) and sink SCCs (out-degree = 0).
5. The minimum number of edges to add equals max(number of sources, number of sinks).

### Why max(sources, sinks) is the answer?
- To make the graph strongly connected, we need to ensure there are paths between all pairs of SCCs.
- Each source SCC needs at least one incoming edge, and each sink SCC needs at least one outgoing edge.
- We can connect all sources and sinks with max(sources, sinks) edges by creating a cycle:
  - If sources ≥ sinks: Connect each sink to a distinct source, and connect remaining sources in a cycle.
  - If sinks > sources: Connect each source to a distinct sink, and connect remaining sinks in a cycle.

## Time and Space Complexity

- Time Complexity: O(V + E) for finding SCCs and O(V + E) for finding minimum edges, so overall O(V + E).
- Space Complexity: O(V + E) for storing the graph and its transpose.

## Implementation Details

The C++ implementation includes:

1. A `Graph` class with methods for graph operations
2. `findSCCs()` method implementing Kosaraju's algorithm
3. `minEdgesToMakeSCC()` method calculating the minimum edges to add
4. Example usage with three different graph configurations
