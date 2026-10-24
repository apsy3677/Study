# 2101. Detonate the Maximum Bombs

[Problem](https://leetcode.com/problems/detonate-the-maximum-bombs/) · Medium · Graph: General BFS/DFS → DFS reachability

LeetCode tags: array, math, depth-first-search, breadth-first-search, graph, geometry

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-24 18:17 IST · Accepted · C++

[submission 921287381](https://leetcode.com/submissions/detail/921287381/) · tests 160/160 · runtime 465 ms (beats 5.1%)

```cpp
class Solution {
public:
    int reachable(int u, int v, vector<vector<int>>& bombs){
        long long x1 = bombs[u][0], y1=bombs[u][1], r1 = bombs[u][2];
        long long x2 = bombs[v][0], y2=bombs[v][1], r2 = bombs[v][2];

        return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) <= r1*r1;
    }
    void dfs(int u, vector<vector<int>>& bombs, vector<bool> &vis, int &count){

        if(vis[u])
            return ;
        // int ans = 1;
        count++;
        vis[u] =true;
        for(int i=0;i<bombs.size();i++){
            if(i!=u && !vis[i] && reachable(u, i, bombs)){
                dfs(i, bombs, vis, count);
                // ans++;
            }
        }
        // vis[u] =false ;
    }
    int maximumDetonation(vector<vector<int>>& bombs) {
        int count = 0, ans =1;;
        
        for(int i=0;i<bombs.size();i++){
            // if(!vis[i]){
                count =0;
                vector<bool> vis(bombs.size(), false);
                dfs(i, bombs, vis, count);
                ans = max(ans, count);
            // }
        }
        return ans;
    }
};
```
