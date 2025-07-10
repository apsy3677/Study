/**
 * Finding Strongly Connected Components (SCCs) and Minimum Edges to Make a Directed Graph Strongly Connected
 *
 * This program implements:
 * 1. Kosaraju's algorithm to find all SCCs in a directed graph
 * 2. A function to calculate the minimum number of edges to add to make the graph strongly connected
 */
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Graph {
private:
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list
    
    // DFS utility function for Kosaraju's algorithm
    void dfsUtil(int v, vector<bool>& visited, stack<int>* stk = nullptr) {
        visited[v] = true;
        
        // Visit all adjacent vertices
        for (int i : adj[v]) {
            if (!visited[i]) {
                dfsUtil(i, visited, stk);
            }
        }
        
        // Push current vertex to stack (used only in first DFS)
        if (stk != nullptr) {
            stk->push(v);
        }
    }
    
    // DFS to collect vertices in a SCC
    void collectSCC(int v, vector<bool>& visited, vector<int>& scc) {
        visited[v] = true;
        scc.push_back(v);
        
        // Visit all adjacent vertices
        for (int i : adj[v]) {
            if (!visited[i]) {
                collectSCC(i, visited, scc);
            }
        }
    }
    
    // Get transpose of the graph (reverse all edges)
    Graph getTranspose() {
        Graph gr(V);
        
        // For each vertex and its adjacency list
        for (int v = 0; v < V; v++) {
            for (int u : adj[v]) {
                // Add edge in reverse direction
                gr.addEdge(u, v);
            }
        }
        
        return gr;
    }

public:
    // Constructor
    Graph(int vertices) : V(vertices) {
        adj.resize(vertices);
    }
    
    // Add edge from vertex u to v
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    // Find all strongly connected components using Kosaraju's algorithm
    vector<vector<int>> findSCCs() {
        vector<vector<int>> sccs;
        
        // Step 1: Fill vertices in stack according to their finishing times
        stack<int> stack;
        vector<bool> visited(V, false);
        
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfsUtil(i, visited, &stack);
            }
        }
        
        // Step 2: Create a reversed graph
        Graph gr = getTranspose();
        
        // Step 3: Process all vertices in order defined by stack
        fill(visited.begin(), visited.end(), false);
        
        while (!stack.empty()) {
            int v = stack.top();
            stack.pop();
            
            if (!visited[v]) {
                // Start a new SCC
                vector<int> scc;
                gr.collectSCC(v, visited, scc);
                sccs.push_back(scc);
            }
        }
        
        return sccs;
    }
    
    // Calculate minimum edges to add to make the graph strongly connected
    int minEdgesToMakeSCC() {
        // Find all SCCs
        vector<vector<int>> sccs = findSCCs();
        
        // If there's only one SCC, the graph is already strongly connected
        if (sccs.size() == 1) {
            return 0;
        }
        
        // Map each vertex to its SCC index for quick lookup
        unordered_map<int, int> sccMapping;
        for (int i = 0; i < sccs.size(); i++) {
            for (int vertex : sccs[i]) {
                sccMapping[vertex] = i;
            }
        }
        
        // Directly calculate in-degree and out-degree of each SCC without building the condensed graph
        vector<bool> hasOutgoingEdge(sccs.size(), false);
        vector<bool> hasIncomingEdge(sccs.size(), false);
        
        // Check all edges to determine inter-SCC connections
        for (int u = 0; u < V; u++) {
            int u_scc = sccMapping[u];
            for (int v : adj[u]) {
                int v_scc = sccMapping[v];
                if (u_scc != v_scc) { // If edge is between different SCCs
                    hasOutgoingEdge[u_scc] = true;
                    hasIncomingEdge[v_scc] = true;
                }
            }
        }
        
        // Count sources and sinks
        int sources = 0;
        int sinks = 0;
        
        for (int scc_idx = 0; scc_idx < sccs.size(); scc_idx++) {
            if (!hasIncomingEdge[scc_idx]) {
                sources++;
            }
            if (!hasOutgoingEdge[scc_idx]) {
                sinks++;
            }
        }
        
        // The answer is max(sources, sinks)
        return max(sources, sinks);
    }
    
    // Print the graph (for debugging)
    void printGraph() {
        for (int v = 0; v < V; v++) {
            cout << "Vertex " << v << " -> ";
            for (int u : adj[v]) {
                cout << u << " ";
            }
            cout << endl;
        }
    }
};

// Utility function to print SCCs
void printSCCs(const vector<vector<int>>& sccs) {
    cout << "SCCs: ";
    for (const auto& scc : sccs) {
        cout << "[ ";
        for (int v : scc) {
            cout << v << " ";
        }
        cout << "] ";
    }
    cout << endl;
}

int main() {
    // Example 1: Two SCCs
    cout << "Example 1:" << endl;
    Graph g1(5);
    g1.addEdge(0, 1);
    g1.addEdge(1, 2);
    g1.addEdge(2, 0);
    g1.addEdge(1, 3);
    g1.addEdge(3, 4);
    
    vector<vector<int>> sccs1 = g1.findSCCs();
    printSCCs(sccs1);
    cout << "Minimum edges to add: " << g1.minEdgesToMakeSCC() << endl;
    
    // Example 2: Already an SCC
    cout << "\nExample 2:" << endl;
    Graph g2(3);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 0);
    
    vector<vector<int>> sccs2 = g2.findSCCs();
    printSCCs(sccs2);
    cout << "Minimum edges to add: " << g2.minEdgesToMakeSCC() << endl;
    
    // Example 3: Multiple SCCs
    cout << "\nExample 3:" << endl;
    Graph g3(7);
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.addEdge(2, 0);
    g3.addEdge(3, 4);
    g3.addEdge(4, 5);
    g3.addEdge(5, 3);
    g3.addEdge(6, 5);
    
    vector<vector<int>> sccs3 = g3.findSCCs();
    printSCCs(sccs3);
    cout << "Minimum edges to add: " << g3.minEdgesToMakeSCC() << endl;
    
    return 0;
}
