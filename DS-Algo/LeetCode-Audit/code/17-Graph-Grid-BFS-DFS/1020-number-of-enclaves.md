# 1020. Number of Enclaves

[Problem](https://leetcode.com/problems/number-of-enclaves/) · Medium · Graph: Grid BFS/DFS → Border flood fill

LeetCode tags: array, depth-first-search, breadth-first-search, union-find, matrix

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-04-29 10:34 IST · Accepted · C++

[submission 941390538](https://leetcode.com/submissions/detail/941390538/) · tests 58/58 · runtime 222 ms (beats 5.0%)

```cpp
class Solution {
    vector<vector<int>> diff = {{0,1}, {0,-1}, {1,0}, {-1,0}};

    void dfs(int x, int y, vector<vector<int>>& grid, vector<vector<int>>& vis){
        int m = grid.size();
        int n = grid[0].size();
        vis[x][y] =1;

        for(auto d: diff){
            int newX = x + d[0];
            int newY = y + d[1];
            if(newX<0 || newX>=m || newY<0 ||newY>=n || vis[newX][newY] || grid[newX][newY] == 0){
            // out of bound and previosuly visited
                continue;
            }
                dfs(newX, newY, grid, vis);
        }
    }
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> vis(m, vector<int>(n, 0));

        for(int i=0;i<m;i++){
            if(grid[i][0] == 1 && vis[i][0] == 0){
                dfs(i,0, grid, vis);
            }
            if( grid[i][n-1] == 1 && vis[i][n-1] == 0){
                dfs(i,n-1, grid, vis);
            }
        }
        for(int i=0;i<n;i++){
            if(grid[0][i] == 1 && vis[0][i] == 0){
                dfs(0,i, grid, vis);
            }
            if( grid[m-1][i] == 1 && vis[m-1][i] == 0){
                dfs(m-1,i, grid, vis);
            }
        }
        int ans =0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j] == 1 && vis[i][j] ==0){
                    ans++;
                }
            }
        }
        return ans;
    }
};
```
