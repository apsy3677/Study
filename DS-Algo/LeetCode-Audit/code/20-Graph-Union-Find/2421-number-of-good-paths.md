# 2421. Number of Good Paths

[Problem](https://leetcode.com/problems/number-of-good-paths/) · Hard · Graph: Union-Find → Sort by value + DSU

LeetCode tags: array, hash-table, tree, union-find, graph, sorting

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-23 23:09 IST · Accepted · C++

[submission 920861130](https://leetcode.com/submissions/detail/920861130/) · tests 134/134 · runtime 684 ms (beats 5.1%)

```cpp
class UnionFind {
private:
    vector<int> parent, rank;

public:
    UnionFind(int size) {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void union_set(int x, int y) {
        int xset = find(x), yset = find(y);
        if (xset == yset) {
            return;
        } else if (rank[xset] < rank[yset]) {
            parent[xset] = yset;
        } else if (rank[xset] > rank[yset]) {
            parent[yset] = xset;
        } else {
            parent[yset] = xset;
            rank[xset]++;
        }
    }
};

class Solution {
public:
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size();
        vector<vector<int>> graph(n);

        for(auto &edge:edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        map<int, vector<int>> valuesToNodes;
        for(int node =0;node<n;node++){
            valuesToNodes[vals[node]].push_back(node);
        }

        UnionFind uf(n);
        int ans =0;
        // iterate all values in sorted order
        for(auto& [value, nodes] : valuesToNodes){
            for(int node: nodes){
                for(int child : graph[node]){
                    if(vals[node] >= vals[child]){
                        uf.union_set(node, child);
                    }
                }
            }
            // groups of connected components in with size
            map<int,int> group;
            for(int u:nodes){
                // fill groups nodes of (value)
                group[uf.find(u)]++;
            }
            for(auto &[_,size] : group){
                ans += (size* (size+1)/2);
            }
        }
        return ans;
        
        return ans;
    }
};
```
