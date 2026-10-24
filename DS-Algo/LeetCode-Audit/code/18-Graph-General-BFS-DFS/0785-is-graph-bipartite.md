# 785. Is Graph Bipartite?

[Problem](https://leetcode.com/problems/is-graph-bipartite/) · Medium · Graph: General BFS/DFS → Two-colouring

LeetCode tags: depth-first-search, breadth-first-search, union-find, graph, graph-coloring, bipartite-graph

Attempts since Mar 2023: 3 · accepted: 2 · failed before first AC: 1

## Attempt 1 · 2023-04-29 12:32 IST · Wrong Answer · C++

[submission 941428205](https://leetcode.com/submissions/detail/941428205/) · tests 66/81

Failing input:

```text
[[1,4],[0,2],[1],[4],[0,3]]
```

Expected:

```text
true
```

Your output:

```text
false
```

```cpp
class Solution {
public:
    bool bfs(int u, vector<vector<int>>& graph, vector<int> &color){
        queue<int> qu;

        qu.push(u);
        bool col = 0;
        color[u] = col;
        while(!qu.empty()){
            int node = qu.front();
            qu.pop();

            for(auto it: graph[node]){
                if(color[it] == -1){
                    color[it] = !col;
                    qu.push(it);
                }
                else if(color[it] == color[node]){
                    return false;
                }
            }
            col = !col;
        }
        return true;
    }
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();

        vector<int> color(n,-1);
        queue<int> qu;

        for(int i=0;i<n;i++){
            if(color[i] == -1){
                bool isValid = bfs(i,graph,color);
                if(!isValid) return isValid;
            }
        }
        return true;
    }
};
```

## Attempt 2 · 2023-04-29 12:35 IST · Accepted · C++

[submission 941429243](https://leetcode.com/submissions/detail/941429243/) · tests 81/81 · runtime 19 ms (beats 5.2%)

```cpp
class Solution {
public:
    bool bfs(int u, vector<vector<int>>& graph, vector<int> &color){
        queue<int> qu;

        qu.push(u);
        color[u] = 0;
        while(!qu.empty()){
            int node = qu.front();
            qu.pop();

            for(auto it: graph[node]){
                if(color[it] == -1){
                    color[it] = !color[node];
                    qu.push(it);
                }
                else if(color[it] == color[node]){
                    return false;
                }
            }
        }
        return true;
    }
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();

        vector<int> color(n,-1);
        queue<int> qu;

        for(int i=0;i<n;i++){
            if(color[i] == -1){
                if(!bfs(i,graph,color)) return false;
            }
        }
        return true;
    }
};
```

## Attempt 3 · 2023-04-29 12:43 IST · Accepted · C++

[submission 941431927](https://leetcode.com/submissions/detail/941431927/) · tests 81/81 · runtime 25 ms (beats 5.2%)

```cpp
class Solution {
public:
    bool dfs(int u, int col, vector<vector<int>>& graph, vector<int> &color){
        color[u] = col;

        for(auto it : graph[u]){
            if(color[it] == -1){
                if(!dfs(it, !col, graph, color)) return false;
            }
            else if(color[it] == color[u])
                return false;       
        }
        return true;
    }
    bool bfs(int u, vector<vector<int>>& graph, vector<int> &color){
        queue<int> qu;

        qu.push(u);
        color[u] = 0;
        while(!qu.empty()){
            int node = qu.front();
            qu.pop();

            for(auto it: graph[node]){
                if(color[it] == -1){
                    color[it] = !color[node];
                    qu.push(it);
                }
                else if(color[it] == color[node]){
                    return false;
                }
            }
        }
        return true;
    }
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();

        vector<int> color(n,-1);
        queue<int> qu;

        for(int i=0;i<n;i++){
            if(color[i] == -1){
                if(!dfs(i,0,graph,color)) return false;
                // if(!bfs(i,graph,color)) return false;
            }
        }
        return true;
    }
};
```
