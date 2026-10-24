# 684. Redundant Connection

[Problem](https://leetcode.com/problems/redundant-connection/) · Medium · Graph: Union-Find → Cycle edge

LeetCode tags: depth-first-search, breadth-first-search, union-find, graph

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-04-30 17:14 IST · Accepted · C++

[submission 942082217](https://leetcode.com/submissions/detail/942082217/) · tests 39/39 · runtime 9 ms (beats 15.5%)

```cpp
//User function Template for C++
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
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        DisjointSet disjointSet(edges.size() +1 );
        vector<int> ans;
        for(auto edge : edges){
            int u = edge[0];
            int v = edge[1];

            if(disjointSet.findUPar(u) == disjointSet.findUPar(v)){
                ans = {u,v};
            }
            else{
                disjointSet.unionBySize(u, v);
            }
        }
        return ans;
    }
};
```
