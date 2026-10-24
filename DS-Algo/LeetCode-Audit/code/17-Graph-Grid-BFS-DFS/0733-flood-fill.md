# 733. Flood Fill

[Problem](https://leetcode.com/problems/flood-fill/) · Easy · Graph: Grid BFS/DFS → Flood fill

LeetCode tags: array, depth-first-search, breadth-first-search, matrix

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2025-05-01 10:28 IST · Accepted · C++

[submission 1622484431](https://leetcode.com/submissions/detail/1622484431/) · tests 278/278 · runtime 1 ms (beats 28.9%)

```cpp
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int m = image.size();
        int n = image[0].size();

        vector<vector<int>> vis(m, vector<int>(n, 0));
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};
        queue< pair<int,int>> qu;
        qu.push({sr, sc});
        int origCol = image[sr][sc];
        image[sr][sc] = color;
        while(!qu.empty()) {
            int sz = qu.size();
            while(sz--) {
                auto [r, c] = qu.front(); qu.pop();
                for(int i=0;i<4;i++){
                    int nr = r + dx[i];
                    int nc = c + dy[i];
                    if (nr >=0 && nr <m &&
                        nc >=0 && nc <n && vis[nr][nc] == 0 && 
                        image[nr][nc] == origCol) {
                        vis[nr][nc] = 1;
                        qu.push({nr, nc});
                        image[nr][nc] = color;
                    }
                }
            }
        }
        return image;
    }
};
```
