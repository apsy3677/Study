# 695. Max Area of Island

[Problem](https://leetcode.com/problems/max-area-of-island/) · Medium · Graph: Grid BFS/DFS → Flood fill with area

LeetCode tags: array, depth-first-search, breadth-first-search, union-find, matrix

Attempts since Mar 2023: 9 · accepted: 6 · failed before first AC: 1

## Attempt 1 · 2023-03-23 01:13 IST · Compile Error · C++

[submission 920335475](https://leetcode.com/submissions/detail/920335475/)

Your output:

```text
{"compile_error": "Line 34: Char 23: error: use of undeclared identifier 'x'\n                cout<<x<<\":\"<<y<<\"dfs ||\";\n                      ^"}
```

Compile error:

```text
Line 34: Char 23: error: use of undeclared identifier 'x'
                cout<<x<<":"<<y<<"dfs ||";
                      ^
```

```cpp
class Solution {
public:
    vector<vector<int>> diff = {{0,-1},{0,1},{1,0},{-1,0}};
    int dfs(int u, int v, vector<vector<int>>& grid, vector<vector<bool>>& visited){
        visited[u][v] = true;
        int sz = 1; 

        int m = grid.size();
        int n = grid[0].size();

        for(int i=0;i<diff.size();i++){
            int x = u + diff[i][0];
            int y = v = diff[i][1];
            cout<<x<<":"<<y<<"|";
            if(x<0 || x>=m || y<0 || y>=n || grid[x][y]==0){
                continue;
            }
            if(!visited[x][y] && grid[x][y] == 1){
                cout<<x<<":"<<y<<"|";
                sz = sz + dfs(x,y,grid,visited);
            }
        }
        return sz;
    }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        if(m==0)
            return 0;
        int n = grid[0].size();
        vector<vector<bool>> visited(m+1, vector<bool> (n+1, false));
        int ans =0, islandSize=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                cout<<x<<":"<<y<<"dfs ||";
                if(!visited[i][j] && grid[i][j]==1){
                    islandSize = dfs(i,j,grid, visited);
                    cout<<islandSize<< "dfs end ";
                    ans = max(ans, islandSize);
                }
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-03-23 01:17 IST · Accepted · C++

[submission 920337329](https://leetcode.com/submissions/detail/920337329/) · tests 728/728 · runtime 271 ms (beats 5.2%)

```cpp
class Solution {
public:
    vector<vector<int>> diff = {{0,-1},{0,1},{1,0},{-1,0}};
    int dfs(int u, int v, vector<vector<int>>& grid, vector<vector<bool>>& visited){
        visited[u][v] = true;
        int sz = 1; 

        int m = grid.size();
        int n = grid[0].size();

        for(int i=0;i<diff.size();i++){
            int x = u + diff[i][0];
            int y = v + diff[i][1];
            cout<<x<<":"<<y<<"|";
            if(x<0 || x>=m || y<0 || y>=n || grid[x][y]==0){
                continue;
            }
            if(!visited[x][y] && grid[x][y] == 1){
                cout<<x<<":"<<y<<"|";
                sz = sz + dfs(x,y,grid,visited);
            }
        }
        return sz;
    }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        if(m==0)
            return 0;
        int n = grid[0].size();
        vector<vector<bool>> visited(m+1, vector<bool> (n+1, false));
        int ans =0, islandSize=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                
                if(!visited[i][j] && grid[i][j]==1){
                    cout<<i<<":"<<j<<"dfs ||";
                    islandSize = dfs(i,j,grid, visited);
                    cout<<islandSize<< "dfs end ";
                    ans = max(ans, islandSize);
                }
            }
        }
        return ans;
    }
};
```

## Attempt 3 · 2023-03-23 01:19 IST · Accepted · C++

[submission 920338040](https://leetcode.com/submissions/detail/920338040/) · tests 728/728 · runtime 40 ms (beats 5.2%)

```cpp
class Solution {
public:
    vector<vector<int>> diff = {{0,-1},{0,1},{1,0},{-1,0}};
    int dfs(int u, int v, vector<vector<int>>& grid, vector<vector<bool>>& visited){
        visited[u][v] = true;
        int sz = 1; 

        int m = grid.size();
        int n = grid[0].size();

        for(int i=0;i<diff.size();i++){
            int x = u + diff[i][0];
            int y = v + diff[i][1];
            // cout<<x<<":"<<y<<"|";
            if(x<0 || x>=m || y<0 || y>=n || grid[x][y]==0){
                continue;
            }
            if(!visited[x][y] && grid[x][y] == 1){
                // cout<<x<<":"<<y<<"|";
                sz = sz + dfs(x,y,grid,visited);
            }
        }
        return sz;
    }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        if(m==0)
            return 0;
        int n = grid[0].size();
        vector<vector<bool>> visited(m+1, vector<bool> (n+1, false));
        int ans =0, islandSize=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                
                if(!visited[i][j] && grid[i][j]==1){
                    // cout<<i<<":"<<j<<"dfs ||";
                    islandSize = dfs(i,j,grid, visited);
                    // cout<<islandSize<< "dfs end ";
                    ans = max(ans, islandSize);
                }
            }
        }
        return ans;
    }
};
```

## Attempt 4 · 2023-11-30 08:09 IST · Accepted · Python3

[submission 1109267250](https://leetcode.com/submissions/detail/1109267250/) · tests 728/728 · runtime 134 ms (beats 5.4%)

```python
class Solution:
    def maxAreaOfIsland1(self, grid: List[List[int]]) -> int:
        N = len(grid)
        M = len(grid[0])
        visited = set()

        def area(row, col):
            if not (0<=row<N and 0<=col<M and (row,col) not in visited and grid[row][col]==1):
                return 0
            
            #set to visited
            visited.add((row,col))
            return 1 +  area(row-1,col) + area(row+1,col)  + area(row, col-1) + area(row, col+1)


        return max(area(row,col) for row in range(N)
            for col in range(M))
    





    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        seen = set()
        def area(r,c):
            if not( (r,c) not in seen and 0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]):
                return 0
            
            seen.add((r,c))

            return 1+ area(r,c+1) + area(r+1,c) + area(r,c-1) + area(r-1,c)

        maxArea = 0
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] ==1:
                    dfsArea = area(i,j)
                    #print(dfsArea)
                    maxArea = max(maxArea, dfsArea)

        return maxArea
```

## Attempt 5 · 2024-01-05 10:43 IST · Accepted · Python3

[submission 1137302813](https://leetcode.com/submissions/detail/1137302813/) · tests 728/728 · runtime 110 ms (beats 5.4%)

```python
class Solution:
    def maxAreaOfIsland1(self, grid: List[List[int]]) -> int:
        N = len(grid)
        M = len(grid[0])
        visited = set()

        def area(row, col):
            if not (0<=row<N and 0<=col<M and (row,col) not in visited and grid[row][col]==1):
                return 0
            
            #set to visited
            visited.add((row,col))
            return 1 +  area(row-1,col) + area(row+1,col)  + area(row, col-1) + area(row, col+1)


        return max(area(row,col) for row in range(N)
            for col in range(M))


    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        visited = set()
        def get_area(r,c):
            if (r,c) in visited:
                return 0

            visited.add((r,c))
            area = 1
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc]==1:
                    area += get_area(nr,nc)

            return area
        max_area=0

        # print(get_area(0,2))
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==1:
                    max_area = max(max_area, get_area(r,c))
        return max_area




    





    def maxAreaOfIsland3(self, grid: List[List[int]]) -> int:
        seen = set()
        def area(r,c):
            if not( (r,c) not in seen and 0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]):
                return 0
            
            seen.add((r,c))

            return 1+ area(r,c+1) + area(r+1,c) + area(r,c-1) + area(r-1,c)

        maxArea = 0
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] ==1:
                    dfsArea = area(i,j)
                    #print(dfsArea)
                    maxArea = max(maxArea, dfsArea)

        return maxArea
```

## Attempt 6 · 2024-01-05 10:49 IST · Accepted · Python3

[submission 1137306766](https://leetcode.com/submissions/detail/1137306766/) · tests 728/728 · runtime 105 ms (beats 5.4%)

```python
class Solution:
    def maxAreaOfIsland1(self, grid: List[List[int]]) -> int:
        N = len(grid)
        M = len(grid[0])
        visited = set()

        def area(row, col):
            if not (0<=row<N and 0<=col<M and (row,col) not in visited and grid[row][col]==1):
                return 0
            
            #set to visited
            visited.add((row,col))
            return 1 +  area(row-1,col) + area(row+1,col)  + area(row, col-1) + area(row, col+1)


        return max(area(row,col) for row in range(N)
            for col in range(M))


    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        visited = set()
        def get_area(r,c):
            if (r,c) in visited:
                return 0

            visited.add((r,c))
            area = 1
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc]==1:
                    area += get_area(nr,nc)

            return area
        max_area=0

        # print(get_area(0,2))
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==1:
                    max_area = max(max_area, get_area(r,c))
        return max_area




    





    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        seen = set()
        ans = 0
        for r0, row in enumerate(grid):
            for c0, val in enumerate(row):
                if val and (r0, c0) not in seen:
                    queue =deque([(r0,c0)])
                    seen.add((r0,c0))
                    shape =0
                    while queue:
                        r,c = queue.popleft()
                        shape +=1

                        for nr, nc in ((r-1, c), (r+1, c), (r, c-1), (r, c+1)):
                            if (0 <= nr < len(grid) and 0 <= nc < len(grid[0])
                                    and grid[nr][nc] and (nr, nc) not in seen):
                                queue.append((nr, nc))
                                seen.add((nr, nc))
                    ans = max(ans, shape)
        return ans
```

## Attempt 7 · 2024-01-26 04:27 IST · Time Limit Exceeded · Python3

[submission 1156900767](https://leetcode.com/submissions/detail/1156900767/) · tests 727/728

Failing input:

```text
[[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, ... [4701 more chars]
```

Expected:

```text
2500
```

```python
class Solution:
    def maxAreaOfIsland1(self, grid: List[List[int]]) -> int:
        N = len(grid)
        M = len(grid[0])
        visited = set()

        def area(row, col):
            if not (0<=row<N and 0<=col<M and (row,col) not in visited and grid[row][col]==1):
                return 0
            
            #set to visited
            visited.add((row,col))
            return 1 +  area(row-1,col) + area(row+1,col)  + area(row, col-1) + area(row, col+1)


        return max(area(row,col) for row in range(N)
            for col in range(M))


    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        visited = set()
        def get_area(r,c):
            if (r,c) in visited:
                return 0

            visited.add((r,c))
            area = 1
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc]==1:
                    area += get_area(nr,nc)

            return area
        max_area=0

        # print(get_area(0,2))
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==1:
                    max_area = max(max_area, get_area(r,c))
        return max_area




    





    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        seen = set()
        ans = 0
        for r0, row in enumerate(grid):
            for c0, val in enumerate(row):
                if val and (r0, c0) not in seen:
                    queue =deque([(r0,c0)])
                    seen.add((r0,c0))
                    shape =0
                    while queue:
                        r,c = queue.popleft()
                        shape +=1

                        for nr, nc in ((r-1, c), (r+1, c), (r, c-1), (r, c+1)):
                            if (0 <= nr < len(grid) and 0 <= nc < len(grid[0])
                                    and grid[nr][nc] and (nr, nc) not in seen):
                                queue.append((nr, nc))
                                seen.add((nr, nc))
                    ans = max(ans, shape)
        return ans


    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        def dfs(r,c):
            if (r,c) in visited:
                return 0
            visited.add((r,c))
            
            area = 1

            for nr, nc in ((r-1, c), (r+1, c), (r, c-1), (r, c+1)):
                if 0 <= nr < len(grid) and 0 <= nc < len(grid[0]) and grid[nr][nc]:
                    area += dfs(nr,nc)

            return area

        visited = set()
        max_area = 0
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c]:
                    area = dfs(r,c)
                    max_area = max(max_area,area)

        return max_area

    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        # visited = 
        def get_area(r,c, visited):
            if (r,c) in visited:
                return 0
            
            visited.add((r,c))
            area = 1
            for nr, nc in ((r-1, c), (r+1, c), (r, c-1), (r, c+1)):
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc]:
                    area += get_area(nr,nc, visited)
            return area

        max_area = 0
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c]:
                    max_area = max(max_area, get_area(r,c, set()))

        return max_area
```

## Attempt 8 · 2024-01-26 04:28 IST · Accepted · Python3

[submission 1156900936](https://leetcode.com/submissions/detail/1156900936/) · tests 728/728 · runtime 125 ms (beats 5.4%)

```python
class Solution:
    def maxAreaOfIsland1(self, grid: List[List[int]]) -> int:
        N = len(grid)
        M = len(grid[0])
        visited = set()

        def area(row, col):
            if not (0<=row<N and 0<=col<M and (row,col) not in visited and grid[row][col]==1):
                return 0
            
            #set to visited
            visited.add((row,col))
            return 1 +  area(row-1,col) + area(row+1,col)  + area(row, col-1) + area(row, col+1)


        return max(area(row,col) for row in range(N)
            for col in range(M))


    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        visited = set()
        def get_area(r,c):
            if (r,c) in visited:
                return 0

            visited.add((r,c))
            area = 1
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc]==1:
                    area += get_area(nr,nc)

            return area
        max_area=0

        # print(get_area(0,2))
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==1:
                    max_area = max(max_area, get_area(r,c))
        return max_area




    





    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        seen = set()
        ans = 0
        for r0, row in enumerate(grid):
            for c0, val in enumerate(row):
                if val and (r0, c0) not in seen:
                    queue =deque([(r0,c0)])
                    seen.add((r0,c0))
                    shape =0
                    while queue:
                        r,c = queue.popleft()
                        shape +=1

                        for nr, nc in ((r-1, c), (r+1, c), (r, c-1), (r, c+1)):
                            if (0 <= nr < len(grid) and 0 <= nc < len(grid[0])
                                    and grid[nr][nc] and (nr, nc) not in seen):
                                queue.append((nr, nc))
                                seen.add((nr, nc))
                    ans = max(ans, shape)
        return ans


    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        def dfs(r,c):
            if (r,c) in visited:
                return 0
            visited.add((r,c))
            
            area = 1

            for nr, nc in ((r-1, c), (r+1, c), (r, c-1), (r, c+1)):
                if 0 <= nr < len(grid) and 0 <= nc < len(grid[0]) and grid[nr][nc]:
                    area += dfs(nr,nc)

            return area

        visited = set()
        max_area = 0
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c]:
                    area = dfs(r,c)
                    max_area = max(max_area,area)

        return max_area

    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        visited = set()
        def get_area(r,c):
            if (r,c) in visited:
                return 0
            
            visited.add((r,c))
            area = 1
            for nr, nc in ((r-1, c), (r+1, c), (r, c-1), (r, c+1)):
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc]:
                    area += get_area(nr,nc)
            return area

        max_area = 0
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c]:
                    max_area = max(max_area, get_area(r,c))

        return max_area
```

## Attempt 9 · 2024-01-26 04:31 IST · Time Limit Exceeded · Python3

[submission 1156902497](https://leetcode.com/submissions/detail/1156902497/) · tests 727/728

Failing input:

```text
[[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, ... [4701 more chars]
```

Expected:

```text
2500
```

```python
class Solution:
    def maxAreaOfIsland1(self, grid: List[List[int]]) -> int:
        N = len(grid)
        M = len(grid[0])
        visited = set()

        def area(row, col):
            if not (0<=row<N and 0<=col<M and (row,col) not in visited and grid[row][col]==1):
                return 0
            
            #set to visited
            visited.add((row,col))
            return 1 +  area(row-1,col) + area(row+1,col)  + area(row, col-1) + area(row, col+1)


        return max(area(row,col) for row in range(N)
            for col in range(M))


    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        visited = set()
        def get_area(r,c):
            if (r,c) in visited:
                return 0

            visited.add((r,c))
            area = 1
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc]==1:
                    area += get_area(nr,nc)

            return area
        max_area=0

        # print(get_area(0,2))
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==1:
                    max_area = max(max_area, get_area(r,c))
        return max_area




    





    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        seen = set()
        ans = 0
        for r0, row in enumerate(grid):
            for c0, val in enumerate(row):
                if val and (r0, c0) not in seen:
                    queue =deque([(r0,c0)])
                    seen.add((r0,c0))
                    shape =0
                    while queue:
                        r,c = queue.popleft()
                        shape +=1

                        for nr, nc in ((r-1, c), (r+1, c), (r, c-1), (r, c+1)):
                            if (0 <= nr < len(grid) and 0 <= nc < len(grid[0])
                                    and grid[nr][nc] and (nr, nc) not in seen):
                                queue.append((nr, nc))
                                seen.add((nr, nc))
                    ans = max(ans, shape)
        return ans


    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        def dfs(r,c):
            if (r,c) in visited:
                return 0
            visited.add((r,c))
            
            area = 1

            for nr, nc in ((r-1, c), (r+1, c), (r, c-1), (r, c+1)):
                if 0 <= nr < len(grid) and 0 <= nc < len(grid[0]) and grid[nr][nc]:
                    area += dfs(nr,nc)

            return area

        visited = set()
        max_area = 0
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c]:
                    area = dfs(r,c)
                    max_area = max(max_area,area)

        return max_area

    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        # mistake 1 set instead of hashmap
        # visited = set()
        def get_area(r,c, visited):
            if (r,c) in visited:
                # mistake 2 return 0 instead of None
                return 0
            

            visited.add((r,c))
            area = 1
            for nr, nc in ((r-1, c), (r+1, c), (r, c-1), (r, c+1)):
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc]:
                    area += get_area(nr,nc, visited)
            return area

        max_area = 0
        for r in range(len(grid)):
            for c in range(len(grid[0])):

                # mistake 3 - only run for 1
                if grid[r][c]:
                    max_area = max(max_area, get_area(r,c, set()))

        return max_area
```
