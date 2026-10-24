# 947. Most Stones Removed with Same Row or Column

[Problem](https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/) · Medium · Graph: Union-Find → Row/column union

LeetCode tags: hash-table, depth-first-search, union-find, graph, bipartite-graph

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-04-02 01:23 IST · Accepted · C++

[submission 926163506](https://leetcode.com/submissions/detail/926163506/) · tests 69/69 · runtime 273 ms (beats 5.0%)

```cpp
class Solution {
public:
    int shareSameRowOrColumn(vector<int>& a, vector<int>& b) {
        return a[0] == b[0] || a[1] == b[1];
    }
    void dfs(vector<vector<int>>& stones, vector<int> adj[], vector<int>& visited, int src) {
        // Mark the stone as visited
        visited[src] = 1;
        
        // Iterate over the adjacent, and iterate over it if not visited yet
        for (int adjacent : adj[src]) {
            if (visited[adjacent] == 0) {
                dfs(stones, adj, visited, adjacent);
            }
        }
    }
    int removeStones(vector<vector<int>>& stones) {
        // Adjacency list to store edges
        vector<int> adj[stones.size()];
        for (int i = 0; i < stones.size(); i++) {
            for (int j = i + 1; j < stones.size(); j++) {
                if (shareSameRowOrColumn(stones[i], stones[j])) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
        // Array to mark visited stones
        vector<int> visited(stones.size(), 0);
        // Counter for connected components
        int componentCount = 0;
        for (int i = 0; i < stones.size(); i++) {
            if (visited[i] == 0) {
                // If the stone is not visited yet,
                // Start the DFS and increment the counter
                componentCount++;
                dfs(stones, adj, visited, i);
            }
        }
        // Return the maximum stone that can be removed
        return stones.size() - componentCount;
    }
};
```

## Attempt 2 · 2023-05-01 10:06 IST · Accepted · C++

[submission 942413101](https://leetcode.com/submissions/detail/942413101/) · tests 69/69 · runtime 48 ms (beats 29.7%)

```cpp
class DisjointSet {
public:
    vector<int> rank, parent, size;
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
public:
    int shareSameRowOrColumn(vector<int>& a, vector<int>& b) {
        return a[0] == b[0] || a[1] == b[1];
    }
    void dfs(vector<vector<int>>& stones, vector<int> adj[], vector<int>& visited, int src) {
        // Mark the stone as visited
        visited[src] = 1;
        
        // Iterate over the adjacent, and iterate over it if not visited yet
        for (int adjacent : adj[src]) {
            if (visited[adjacent] == 0) {
                dfs(stones, adj, visited, adjacent);
            }
        }
    }
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        int total=n;
        int mrow=0, mcol=0;
        for(auto it : stones){
            mrow = max(mrow, it[0]);
            mcol = max(mcol, it[1]);
        }
        DisjointSet ds(mrow + mcol+5);
        unordered_map<int,int> nodes;
        for(auto it : stones){
            int r = it[0];
            int c = it[1] + mrow + 1;
            if(ds.findUPar(r) != ds.findUPar(c)){
                ds.unionBySize(r,c);
                n--;
            }
            nodes[r]=1;
            nodes[c]=1;
        }
        int cnt =0;
        for(auto it: nodes){
            if(ds.findUPar(it.first) == it.first){
                cnt++;
            }
        }
        int ans = stones.size() - cnt;
        return ans;
    }
    int removeStones1(vector<vector<int>>& stones) {
        // Adjacency list to store edges
        vector<int> adj[stones.size()];
        for (int i = 0; i < stones.size(); i++) {
            for (int j = i + 1; j < stones.size(); j++) {
                if (shareSameRowOrColumn(stones[i], stones[j])) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
        // Array to mark visited stones
        vector<int> visited(stones.size(), 0);
        // Counter for connected components
        int componentCount = 0;
        for (int i = 0; i < stones.size(); i++) {
            if (visited[i] == 0) {
                // If the stone is not visited yet,
                // Start the DFS and increment the counter
                componentCount++;
                dfs(stones, adj, visited, i);
            }
        }
        // Return the maximum stone that can be removed
        return stones.size() - componentCount;
        // O(N*N) N= Size of Stones
    }
};
```
