"""
Finding Strongly Connected Components (SCCs) and Minimum Edges to Make a Directed Graph Strongly Connected

This module implements:
1. Kosaraju's algorithm to find all SCCs in a directed graph
2. A function to calculate the minimum number of edges to add to make the graph strongly connected
"""
from collections import defaultdict


class Graph:
    def __init__(self, vertices):
        """Initialize the graph with given number of vertices."""
        self.V = vertices
        self.graph = defaultdict(list)  # Dictionary to store the graph

    def add_edge(self, u, v):
        """Add edge from vertex u to v."""
        self.graph[u].append(v)

    def _dfs_util(self, v, visited, stack=None):
        """DFS utility function for Kosaraju's algorithm."""
        visited[v] = True

        # Visit all adjacent vertices
        for i in self.graph[v]:
            if not visited[i]:
                self._dfs_util(i, visited, stack)
        
        # Push current vertex to stack (used only in first DFS)
        if stack is not None:
            stack.append(v)

    def _get_transpose(self):
        """Return the transpose of the graph (reverse all edges)."""
        g_transpose = Graph(self.V)
        
        # For each vertex and its adjacency list
        for i in range(self.V):
            for j in self.graph[i]:
                g_transpose.add_edge(j, i)  # Add edge in reverse direction
        
        return g_transpose

    def find_sccs(self):
        """Find all strongly connected components using Kosaraju's algorithm."""
        # Step 1: Fill vertices in stack according to their finishing times
        stack = []
        visited = [False] * self.V
        
        for i in range(self.V):
            if not visited[i]:
                self._dfs_util(i, visited, stack)
        
        # Step 2: Create a reversed graph
        gr = self._get_transpose()
        
        # Step 3: Process all vertices in order defined by stack
        visited = [False] * self.V
        sccs = []
        
        while stack:
            i = stack.pop()
            if not visited[i]:
                # Start a new SCC
                scc = []
                gr._collect_scc(i, visited, scc)
                sccs.append(scc)
        
        return sccs

    def _collect_scc(self, v, visited, scc):
        """Collect vertices in a SCC."""
        visited[v] = True
        scc.append(v)
        
        # Visit all adjacent vertices
        for i in self.graph[v]:
            if not visited[i]:
                self._collect_scc(i, visited, scc)

    def min_edges_to_make_scc(self):
        """
        Calculate minimum edges to add to make the graph strongly connected.
        
        Returns:
            int: Minimum number of edges to add
        """
        # Find all SCCs
        sccs = self.find_sccs()
        
        # If there's only one SCC, the graph is already strongly connected
        if len(sccs) == 1:
            return 0
        
        # Create a condensed graph where each SCC is a node
        condensed_graph = defaultdict(set)  # Using sets to avoid duplicate edges
        scc_mapping = {}  # Maps vertex to its SCC index
        
        # Map each vertex to its SCC index
        for i, scc in enumerate(sccs):
            for vertex in scc:
                scc_mapping[vertex] = i
        
        # Build the condensed graph
        for u in range(self.V):
            u_scc = scc_mapping[u]
            for v in self.graph[u]:
                v_scc = scc_mapping[v]
                if u_scc != v_scc:  # If not in same SCC
                    condensed_graph[u_scc].add(v_scc)
        
        # Count sources (in-degree = 0) and sinks (out-degree = 0)
        in_degree = defaultdict(int)
        out_degree = defaultdict(int)
        
        for u_scc in range(len(sccs)):
            out_degree[u_scc] = len(condensed_graph[u_scc])
            for v_scc in condensed_graph[u_scc]:
                in_degree[v_scc] += 1
        
        # Count sources and sinks
        sources = 0
        sinks = 0
        
        for scc_idx in range(len(sccs)):
            if in_degree[scc_idx] == 0:
                sources += 1
            if out_degree[scc_idx] == 0:
                sinks += 1
        
        # The answer is max(sources, sinks)
        return max(sources, sinks)


# Example usage
if __name__ == "__main__":
    # Example 1: Two SCCs
    g1 = Graph(5)
    g1.add_edge(0, 1)
    g1.add_edge(1, 2)
    g1.add_edge(2, 0)
    g1.add_edge(1, 3)
    g1.add_edge(3, 4)
    
    print("Example 1:")
    print("SCCs:", g1.find_sccs())
    print("Minimum edges to add:", g1.min_edges_to_make_scc())
    
    # Example 2: Already an SCC
    g2 = Graph(3)
    g2.add_edge(0, 1)
    g2.add_edge(1, 2)
    g2.add_edge(2, 0)
    
    print("\nExample 2:")
    print("SCCs:", g2.find_sccs())
    print("Minimum edges to add:", g2.min_edges_to_make_scc())
    
    # Example 3: Multiple SCCs
    g3 = Graph(7)
    g3.add_edge(0, 1)
    g3.add_edge(1, 2)
    g3.add_edge(2, 0)
    g3.add_edge(3, 4)
    g3.add_edge(4, 5)
    g3.add_edge(5, 3)
    g3.add_edge(6, 5)
    
    print("\nExample 3:")
    print("SCCs:", g3.find_sccs())
    print("Minimum edges to add:", g3.min_edges_to_make_scc())
