# 1730. Shortest Path to Get Food

[Problem](https://leetcode.com/problems/shortest-path-to-get-food/) · Medium · Graph: Grid BFS/DFS → BFS

LeetCode tags: array, breadth-first-search, matrix

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-24 02:35 IST · Accepted · C++

[submission 920961036](https://leetcode.com/submissions/detail/920961036/) · tests 85/85 · runtime 267 ms (beats 5.2%)

```cpp
class Solution {
public:
    int getFood(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> visited(n, vector<int>(m,-1));
        
        queue<vector<int>> qu;
        // push 0,0, currlen, k
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j] == '*'){
                    qu.push({i,j,0});
                }
            }
        }
        // qu.push({0,0,0});
        while(!qu.empty()){
            auto t = qu.front();
            qu.pop();
            int x = t[0];
            int y = t[1];
            int len = t[2];
            // int rem = t[3];

            if(x<0 || x>=n || y<0 || y>=m || grid[x][y] == 'X'){
                continue;
            }
            
            if(grid[x][y] == '#'){
                return len;
            }
            // check if this cell is already visited
            if(visited[x][y] != -1 ){
                continue;
            }
            visited[x][y] = 1;
            qu.push({x+1, y, len+1});
            qu.push({x-1, y, len+1});
            qu.push({x, y+1, len+1});
            qu.push({x, y-1, len+1});
        }
        return -1;
    }
};
```
