# 417. Pacific Atlantic Water Flow

[Problem](https://leetcode.com/problems/pacific-atlantic-water-flow/) · Medium · Graph: Grid BFS/DFS → Reverse multi-source DFS

LeetCode tags: array, depth-first-search, breadth-first-search, matrix

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-16 13:35 IST · Accepted · C++

[submission 916138421](https://leetcode.com/submissions/detail/916138421/) · tests 113/113 · runtime 43 ms (beats 9.1%)

```cpp
class Solution {
public:
    vector<pair<int,int>> diff = {{0,-1}, {0,1},{-1,0}, {1,0}};
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();

        vector<vector<bool>> AO(n, vector<bool>(m, false)), PO(n, vector<bool>(m, false));

        for(int i=0;i<m;i++){
            dfs(0, i, grid, PO);
            dfs(n-1, i, grid, AO);
        }

        for(int i=0;i<n;i++){
            dfs(i, 0, grid, PO);
            dfs(i, m-1, grid, AO);
        }
        vector<vector<int>> ans;

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(PO[i][j] && AO[i][j]){
                    ans.push_back({i,j});
                }
            }
        }
        return ans;
    }

    void dfs(int i, int j, vector<vector<int>>& grid, vector<vector<bool>> & visited){
        int n = grid.size(), m =grid[0].size();
        visited[i][j] = true;

        for(int child=0;child<diff.size();child++){
            int x = i + diff[child].first;
            int y = j + diff[child].second;

            if(x<0 || x>=n || y<0 || y>=m){
                continue;
            }
            if(!visited[x][y] && grid[x][y] >= grid[i][j])
                dfs(x,y,grid,visited);
        }
    }
};
```
