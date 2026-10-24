# 2360. Longest Cycle in a Graph

[Problem](https://leetcode.com/problems/longest-cycle-in-a-graph/) · Hard · Graph: General BFS/DFS → Cycle in functional graph

LeetCode tags: depth-first-search, breadth-first-search, graph, topological-sort, kosarajus-algorithm, tarjans-scc-algorithm

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-03-26 19:19 IST · Accepted · C++

[submission 922455988](https://leetcode.com/submissions/detail/922455988/) · tests 76/76 · runtime 434 ms (beats 7.9%)

```cpp
class Solution {
public:
    int longestCycle(vector<int>& edges) {
        int n = edges.size();
        vector<vector<int>> graph(n+1);// not required most probably

        vector<int> inDegree(n+1, 0);
        vector<int> visited(n+1,0);

        for(int i=0;i<n;i++){
            // graph[i].push_back(edges[i]);
            if(edges[i] != -1)
                inDegree[edges[i]]++, graph[i].push_back(edges[i]);
        }

        queue<int> qu;
    
        for(int i=0;i<n;i++) if(inDegree[i] == 0) qu.push(i);
        int visitedNodes = 0;
        while(!qu.empty()){
            int sz  = qu.size();

            while(sz--){
                int top = qu.front();
                qu.pop();
                visitedNodes++;
                visited[top] =true;

                for(auto end : graph[top]){
                    if(inDegree[end] > 0)
                    inDegree[end]--;
                    if(inDegree[end] ==0) qu.push(end);
                }
            }
        }
        if(visitedNodes == n) return -1;
        // remaining nodes are left have cycles
        // traverse each node for finding cycle and return last one
        int longestCycle = 0;
        for(int i=0;i<n;i++){
            if(!visited[i]){
                int len =0;
                dfs(graph, i, i, visited, len);
                longestCycle = max(longestCycle, len);
            }
        }
        return longestCycle;
        

    }
    int dfs(vector<vector<int>> &graph, int u, int source, vector<int> &visited, int& len){

        visited[u] = true;
        int ans = 1;
        len++;
        for(auto x: graph[u]){
            if(x == source){
                // cycle
                return 0;
            }
            if(!visited[x]){
                dfs(graph, x, source, visited, len);
            }
                
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-03-26 19:21 IST · Accepted · C++

[submission 922457026](https://leetcode.com/submissions/detail/922457026/) · tests 76/76 · runtime 399 ms (beats 9.2%)

```cpp
class Solution {
public:
    int longestCycle(vector<int>& edges) {
        int n = edges.size();
        vector<vector<int>> graph(n+1);// not required most probably

        vector<int> inDegree(n+1, 0);
        vector<int> visited(n+1,0);

        for(int i=0;i<n;i++){
            // graph[i].push_back(edges[i]);
            if(edges[i] != -1)
                inDegree[edges[i]]++, graph[i].push_back(edges[i]);
        }

        queue<int> qu;
    
        for(int i=0;i<n;i++) if(inDegree[i] == 0) qu.push(i);
        int visitedNodes = 0;
        while(!qu.empty()){
            int sz  = qu.size();

            while(sz--){
                int top = qu.front();
                qu.pop();
                visitedNodes++;
                visited[top] =true;

                for(auto end : graph[top]){
                    // if(inDegree[end] > 0)
                    inDegree[end]--;
                    if(inDegree[end] ==0) qu.push(end);
                }
            }
        }
        if(visitedNodes == n) return -1;
        // remaining nodes are left have cycles
        // traverse each node for finding cycle and return last one
        int longestCycle = 0;
        for(int i=0;i<n;i++){
            if(!visited[i]){
                int len =0;
                int count = dfs(graph, i, i, visited, len);
                longestCycle = max(longestCycle, count);
            }
        }
        return longestCycle;
        
    }
    int dfs(vector<vector<int>> &graph, int u, int source, vector<int> &visited, int& len){

        visited[u] = true;
        int ans = 1;
        len++;
        for(auto x: graph[u]){
            if(x == source){
                // cycle
                return ans;
            }
            if(!visited[x]){
                ans += dfs(graph, x, source, visited, len);
            }
                
        }
        return ans;
    }
};
```
