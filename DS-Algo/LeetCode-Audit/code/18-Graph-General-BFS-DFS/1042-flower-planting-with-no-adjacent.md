# 1042. Flower Planting With No Adjacent

[Problem](https://leetcode.com/problems/flower-planting-with-no-adjacent/) · Medium · Graph: General BFS/DFS → Greedy colouring

LeetCode tags: depth-first-search, breadth-first-search, graph, graph-coloring

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2024-10-29 10:04 IST · Accepted · C++

[submission 1436888279](https://leetcode.com/submissions/detail/1436888279/) · tests 51/51 · runtime 42 ms (beats 63.8%)

```cpp
class Solution {
public:
    bool possible(int node, int n, vector<vector<int>>& graph, int color, vector<int> &ans) {
        for (int child : graph[node]) {
            if (ans[child] == color) {
                return false;
            }
        }
        return true;
    }
    bool assignFlower(int node, int n, vector<vector<int>>& graph, vector<int> &ans) {
        if(node == n+1) {
            // All colored
            return true;
        }
        for (int color= 1; color<=4;color++) {
            if (possible(node, n, graph, color, ans)) {
                ans[node] = color;
                if (assignFlower(node + 1, n, graph, ans)) {
                    return true;
                }
                ans[node] = 0;
            }
        }
        return false;
    }
    vector<int> gardenNoAdj(int n, vector<vector<int>>& paths) {
        vector<vector<int>> graph(n+1);
        for(auto path : paths) {
            graph[path[0]].push_back(path[1]);
            graph[path[1]].push_back(path[0]);
        }
        vector<int> color(n+1,0);
        bool assigned = assignFlower(1, n, graph, color);
        return {color.begin()+1, color.end()};
    }
};
```

## Attempt 2 · 2024-10-29 10:05 IST · Accepted · C++

[submission 1436889483](https://leetcode.com/submissions/detail/1436889483/) · tests 51/51 · runtime 53 ms (beats 41.8%)

```cpp
class Solution {
public:
    bool possible(int node, int n, vector<vector<int>>& graph, int color, vector<int> &ans) {
        for (auto child : graph[node]) {
            if (child != node && ans[child] == color) {
                return false;
            }
        }
        return true;
    }
    bool assignFlower(int node, int n, vector<vector<int>>& graph, vector<int> &ans) {
        if(node == n) {
            // All colored
            return true;
        }
        for (int color= 1; color<=4;color++) {
            if (possible(node, n, graph, color, ans)) {
                ans[node] = color;
                if (assignFlower(node + 1, n, graph, ans)) {
                    return true;
                }
                ans[node] = 0;
            }
        }
        return false;
    }
    vector<int> gardenNoAdj(int n, vector<vector<int>>& paths) {
        vector<vector<int>> graph(n);
        for(auto path : paths) {
            // For converting it to 0 based indexing
            graph[path[0]-1].push_back(path[1]-1);
            graph[path[1]-1].push_back(path[0]-1);
        }
        vector<int> color(n,0);
        bool assigned = assignFlower(0, n, graph, color);
        return color;
    }
};
```
