# 802. Find Eventual Safe States

[Problem](https://leetcode.com/problems/find-eventual-safe-states/) · Medium · Graph: Topological Sort → Reverse Kahn

LeetCode tags: depth-first-search, breadth-first-search, graph, topological-sort, kosarajus-algorithm, tarjans-scc-algorithm

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-04-29 13:25 IST · Accepted · C++

[submission 941444983](https://leetcode.com/submissions/detail/941444983/) · tests 112/112 · runtime 167 ms (beats 5.0%)

```cpp
class Solution {
public:
    bool dfs(int node, vector<vector<int>>& graph, vector<int> &visited, vector<int> &pathVisited, vector<int> &safe){
        visited[node] = 1;
        pathVisited[node] =1;

        for(auto it : graph[node]){
            if(!visited[it] && !pathVisited[it]){
                if(dfs(it, graph, visited, pathVisited, safe)){
                    return true;
                }
            }
            else if(pathVisited[it]){
                return true;
            }
        }
        pathVisited[node] = 0;
        safe[node] = 1;
        return false;
    }
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> visited(n, 0), pathVisited(n, 0), safeNodes(n,0), ans;
        for(int i=0;i<n;i++){
            if(!visited[i]){
                dfs(i, graph, visited, pathVisited, safeNodes);
            }
        }
        for(int i=0;i<safeNodes.size();i++)
            if(safeNodes[i]) ans.push_back(i);
        return ans;
    }
};
```
