# 994. Rotting Oranges

[Problem](https://leetcode.com/problems/rotting-oranges/) · Medium · Graph: Grid BFS/DFS → Multi-source BFS

LeetCode tags: array, breadth-first-search, matrix

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-04-29 09:07 IST · Accepted · C++

[submission 941367397](https://leetcode.com/submissions/detail/941367397/) · tests 306/306 · runtime 8 ms (beats 5.3%)

```cpp
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        queue<pair<int,int>> qu;
        vector<vector<int>> visited(n, vector<int>(m, 0));

        int fresh=0;
        int minTime=0;

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j] == 2){
                    visited[i][j]  = 2;
                    qu.push({i,j});
                }
                else if(grid[i][j] == 1){
                    visited[i][j] =1;
                    fresh++;
                }
            }
        }
        vector<int> dx = {0,1,0,-1};
        vector<int> dy = {1,0,-1,0};
        while(!qu.empty() && fresh>0){
            int sz = qu.size();
            // cout<<"qu size "<<sz<<" ";
            while(sz--){
                int x = qu.front().first;
                int y = qu.front().second;
                qu.pop();
                for(int i=0;i<dx.size();i++){
                    int r = x+ dx[i];
                    int c = y+ dy[i];

                    if(r>=0 && r<n && c>=0 && c<m &&
                        visited[r][c] == 1 && grid[r][c] == 1){
                            // orange will rot now
                            visited[r][c] = 2;
                            fresh--;
                            qu.push({r,c});
                        }
                }
            }
            minTime++;
        }
        return fresh==0 ? minTime : -1;
    }
};
```

## Attempt 2 · 2025-05-01 10:19 IST · Accepted · C++

[submission 1622478711](https://leetcode.com/submissions/detail/1622478711/) · tests 307/307 · runtime 1 ms (beats 40.7%)

```cpp
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m  = grid.size();
        int n = grid[0].size();

        vector<vector<int>> vis(m, vector<int> (n, 0));
        queue <pair<int,int>> qu;
        int fresh = 0;
        for (int r= 0; r<m; r++) {
            for(int c=0; c<n;c++) {
                if (grid[r][c] == 2) {
                    // rotten
                    qu.push({r,c});
                    vis[r][c] = 2;
                } else if(grid[r][c] == 1){
                    fresh++;
                    vis[r][c] = 1;
                }
            }
        }
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};
        int time = 0;
        while(!qu.empty() && fresh > 0) {
            int sz = qu.size();
            time ++;
            while (sz--) {
                auto [x,y] = qu.front(); qu.pop();

                for(int i=0;i<4;i++) {
                    int nr = x + dx[i];
                    int nc = y + dy[i];

                    if (nr >=0 && nr <m &&
                        nc >=0 && nc <n && vis[nr][nc] == 1) {
                        vis[nr][nc] = 2;
                        qu.push({nr, nc});
                        fresh--;
                    }
                }
            }
        }
        if (fresh != 0) {
            return -1;
        }
        return time;
    }
};
```
