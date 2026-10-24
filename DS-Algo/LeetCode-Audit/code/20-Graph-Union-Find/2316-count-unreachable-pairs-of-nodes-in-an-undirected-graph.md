# 2316. Count Unreachable Pairs of Nodes in an Undirected Graph

[Problem](https://leetcode.com/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/) · Medium · Graph: Union-Find → Component sizes

LeetCode tags: depth-first-search, breadth-first-search, union-find, graph

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2023-03-25 20:37 IST · Runtime Error · C++

[submission 921905288](https://leetcode.com/submissions/detail/921905288/) · tests 56/66

Failing input:

```text
100000
[[57043,0],[2,67814],[3,22237],[8240,4],[6,68194],[28065,7],[8,6459],[87642,9],[11,11034],[35746,12],[15,36233],[16,50931],[17,73571],[18,27174],[19,55370],[79005,20],[80924,21],[24,4170],[25,22447],[28,91618],[5890,29],[19485,31],[33,47798],[34,5845],[84061,35],[36,47893],[37,60975],[74509,38],[39,72555],[40,99060],[41,66565],[31261,42],[83799,43],[44,20296],[99637,46],[97286,47],[49,56878 ... [1039183 more chars]
```

Expected:

```text
4999756275
```

Runtime error:

```text
Line 28: Char 21: runtime error: signed integer overflow: 2147467630 + 453150 cannot be represented in type 'int' (solution.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:37:21
```

```cpp
class Solution {
public:
    int dfs(int u, vector<vector<int>>& graph, vector<bool> & visited){
        int count =1;
        visited[u] = true;

        for(auto x: graph[u]){
            if(!visited[x]){
                count += dfs(x, graph,visited);
            }
        }
        return count;
    }
    long long countPairs(int n, vector<vector<int>>& edges) {

        vector<vector<int>> graph(n);
        vector<bool> visited(n, false);

        for(auto edge : edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        int ans = 0, remain =n;
        for(int i=0;i<n;i++){
            if(!visited[i]){
                int sz = dfs(i, graph, visited);
                ans += sz *(remain - sz);
                remain -= sz;
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-03-25 20:38 IST · Accepted · C++

[submission 921905561](https://leetcode.com/submissions/detail/921905561/) · tests 66/66 · runtime 609 ms (beats 5.1%)

```cpp
class Solution {
public:
    int dfs(int u, vector<vector<int>>& graph, vector<bool> & visited){
        int count =1;
        visited[u] = true;

        for(auto x: graph[u]){
            if(!visited[x]){
                count += dfs(x, graph,visited);
            }
        }
        return count;
    }
    long long countPairs(int n, vector<vector<int>>& edges) {

        vector<vector<int>> graph(n);
        vector<bool> visited(n, false);

        for(auto edge : edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        long long ans = 0, remain =n;
        for(int i=0;i<n;i++){
            if(!visited[i]){
                int sz = dfs(i, graph, visited);
                ans += sz *(remain - sz);
                remain -= sz;
            }
        }
        return ans;
    }
};
```
