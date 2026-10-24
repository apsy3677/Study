# 1926. Nearest Exit from Entrance in Maze

[Problem](https://leetcode.com/problems/nearest-exit-from-entrance-in-maze/) · Medium · Graph: Grid BFS/DFS → BFS

LeetCode tags: array, breadth-first-search, matrix

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2024-03-18 23:47 IST · Accepted · C++

[submission 1207498449](https://leetcode.com/submissions/detail/1207498449/) · tests 194/194 · runtime 102 ms (beats 7.1%)

```cpp
class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int rows = int(maze.size()), cols = int(maze[0].size());
        vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        
        // Mark the entrance as visited since its not a exit.
        int startRow = entrance[0], startCol = entrance[1];
        maze[startRow][startCol] = '+';
        
        // Start BFS from the entrance, and use a queue `queue` to store all 
        // the cells to be visited.
        queue<array<int, 3>> queue;
        queue.push({startRow, startCol, 0});
        
        while (!queue.empty()) {
            auto [currRow, currCol, currDistance] = queue.front();
            queue.pop();
            
            // For the current cell, check its four neighbor cells.
            for (auto dir : dirs) {
                int nextRow = currRow + dir.first, nextCol = currCol + dir.second;

                // If there exists an unvisited empty neighbor:
                if (0 <= nextRow && nextRow < rows && 0 <= nextCol && nextCol < cols \
                   && maze[nextRow][nextCol] == '.') {
                    
                    // If this empty cell is an exit, return distance + 1.
                    if (nextRow == 0 || nextRow == rows - 1 || nextCol == 0 || nextCol == cols - 1)
                        return currDistance + 1;
                    
                    // Otherwise, add this cell to 'queue' and mark it as visited.
                    maze[nextRow][nextCol] = '+';
                    queue.push({nextRow, nextCol, currDistance + 1});
                    
                }
            }
        }
        
        // If we finish iterating without finding an exit, return -1.
        return -1;
    }
};
```

## Attempt 2 · 2024-03-18 23:59 IST · Accepted · C++

[submission 1207510837](https://leetcode.com/submissions/detail/1207510837/) · tests 194/194 · runtime 86 ms (beats 8.7%)

```cpp
class Solution {

private:

    bool isValidCoordinate(int x, int y, int n, int m) {
        return x >= 0 && x < n && y >= 0 && y < m;
    }

    bool isExit(int x, int y, int n, int m) {
        return x == 0 || x == n-1 || y == 0 || y == m-1;
    }
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        queue<pair<pair<int,int>, int>> q;
        int tRow = maze.size();
        int tCol = maze[0].size();
        vector<vector<int>> visited(tRow, vector<int> (tCol, 0));
        q.push({{entrance[0], entrance[1]}, 0});
        visited[entrance[0]][entrance[1]] = 1;

        while(!q.empty()) {
            int row = q.front().first.first;
            int col = q.front().first.second;
            int distance = q.front().second;
            q.pop();
            int delRow[] = {-1, 0, 1, 0};
            int delCol[] = {0, 1, 0, -1};
            for(int i=0; i<4; i++) {
                int nRow = row + delRow[i];
                int nCol = col + delCol[i];
                if(isValidCoordinate(nRow, nCol, tRow, tCol) && visited[nRow][nCol] == 0 && maze[nRow][nCol] == '.') {
                    if(isExit(nRow, nCol, tRow, tCol)) {
                        return distance + 1;
                    }
                    q.push({{nRow, nCol}, distance + 1});
                    visited[nRow][nCol] = 1;
                }
            }
        }
        return -1;
    }
};
```
