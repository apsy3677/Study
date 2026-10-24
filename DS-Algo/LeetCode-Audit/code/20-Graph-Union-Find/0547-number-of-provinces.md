# 547. Number of Provinces

[Problem](https://leetcode.com/problems/number-of-provinces/) · Medium · Graph: Union-Find → Components

LeetCode tags: depth-first-search, breadth-first-search, union-find, graph

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2025-05-01 09:58 IST · Accepted · C++

[submission 1622466737](https://leetcode.com/submissions/detail/1622466737/) · tests 114/114 · runtime 0 ms (beats 100%)

```cpp
class Solution {
    int n;
public:
    void dfs(int node, vector<int> &vis, vector<vector<int>>& isConnected) {
        vis[node] = 1;
        for(int child=0; child<n ;child++) {
            if (node != child && isConnected[node][child] && !vis[child]) {
                dfs(child, vis, isConnected);
            }
        }
    }
    int findCircleNum(vector<vector<int>>& isConnected) {
        n = isConnected.size();
        int ans = 0;
        vector<int> vis(n, 0);
        for (int i = 0 ; i<n ; i++) {
            if (!vis[i]) {
                dfs(i, vis, isConnected);
                ans ++;
            }
        }
        return ans;
    }
};
```
