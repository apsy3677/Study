# 1192. Critical Connections in a Network

[Problem](https://leetcode.com/problems/critical-connections-in-a-network/) · Hard · Graph: General BFS/DFS → Tarjan bridges

LeetCode tags: depth-first-search, graph, biconnected-component, bridge-graph

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-05-01 11:29 IST · Accepted · C++

[submission 942448003](https://leetcode.com/submissions/detail/942448003/) · tests 17/17 · runtime 674 ms (beats 5.0%)

```cpp
class Solution {
    int timer =0;
    void dfs(int node, int parent, vector<int> &vis, vector<int> adj[], vector<int> &time, vector<int> &low, vector<vector<int>> & bridges){

        vis[node] =1;
        time[node] = low[node] = timer;
        timer++;

        for(auto it: adj[node]){
            if(it == parent) continue;
            if(!vis[it]){
                // traverse next
                dfs(it, node, vis, adj,time,low, bridges);
                // check if we cnaa

                low[node] = min(low[node], low[it]);
                // node --- it is a bridge ?

                if(low[it] > time[node]){
                    bridges.push_back({it, node});
                }

            }
            else{
                low[node] = min(low[node], low[it]);
            }
        }
    }

public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<int> adj[n], time(n,0), low(n, 1e9), vis(n,0);

        for(auto it: connections){
            adj[it[1]].push_back(it[0]);
            adj[it[0]].push_back(it[1]);
        }
        vector<vector<int>> bridges;
        dfs(0, -1, vis, adj, time, low, bridges);

        return bridges;
    }
};
```

## Attempt 2 · 2023-05-01 11:32 IST · Accepted · C++

[submission 942449111](https://leetcode.com/submissions/detail/942449111/) · tests 17/17 · runtime 682 ms (beats 5.0%)

```cpp
class Solution {
    int timer =0;
    void dfs(int node, int parent, vector<int> &vis, vector<int> adj[], vector<int> &time, vector<int> &low, vector<vector<int>> & bridges){

        vis[node] = 1;
        time[node] = low[node] = timer;
        timer++;

        for(auto it: adj[node]){
            if(it == parent) continue;
            if(!vis[it]){
                // traverse next
                dfs(it, node, vis, adj,time,low, bridges);

                // check if we can update the low time for current node
                low[node] = min(low[node], low[it]);
                
                // node --- it is a bridge ?
                // low[it] <= time[node] it means even if we remove edge node to it, it can be reached via some other path as low[it] is smaller than low[node]
                if(low[it] > time[node]){
                    bridges.push_back({it, node});
                }

            }
            else{
                low[node] = min(low[node], low[it]);
            }
        }
    }

public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<int> adj[n], time(n,0), low(n, 1e9), vis(n,0);

        for(auto it: connections){
            adj[it[1]].push_back(it[0]);
            adj[it[0]].push_back(it[1]);
        }
        vector<vector<int>> bridges;
        dfs(0, -1, vis, adj, time, low, bridges);

        return bridges;
    }
};
```

## Attempt 3 · 2023-05-01 11:44 IST · Accepted · C++

[submission 942454714](https://leetcode.com/submissions/detail/942454714/) · tests 17/17 · runtime 717 ms (beats 5.0%)

```cpp
class Solution {
    // int timer =0;
    void dfs(int node, int parent, vector<int> &vis, vector<int> adj[], vector<int> &time, vector<int> &low, vector<vector<int>> & bridges, int timer){

        vis[node] = 1;
        time[node] = low[node] = timer;
        // timer++;

        for(auto it: adj[node]){
            if(it == parent) continue;
            if(!vis[it]){
                // traverse next
                dfs(it, node, vis, adj,time,low, bridges, timer+1);

                // check if we can update the low time for current node
                low[node] = min(low[node], low[it]);
                
                // node --- it is a bridge ?
                // low[it] <= time[node] it means even if we remove edge node to it, it can be reached via some other path as low[it] is smaller than low[node]
                if(low[it] > time[node]){
                    bridges.push_back({it, node});
                }

            }
            else{
                low[node] = min(low[node], low[it]);
            }
        }
    }

public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<int> adj[n], time(n,0), low(n, 1e9), vis(n,0);

        for(auto it: connections){
            adj[it[1]].push_back(it[0]);
            adj[it[0]].push_back(it[1]);
        }
        vector<vector<int>> bridges;
        // calling only once as connected component
        // TC O(v + 2E)
        dfs(0, -1, vis, adj, time, low, bridges, 1);

        return bridges;
    }
};
```
