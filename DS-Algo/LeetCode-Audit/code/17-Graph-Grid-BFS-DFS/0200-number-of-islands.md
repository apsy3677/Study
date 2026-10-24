# 200. Number of Islands

[Problem](https://leetcode.com/problems/number-of-islands/) · Medium · Graph: Grid BFS/DFS → Flood fill

LeetCode tags: array, depth-first-search, breadth-first-search, union-find, matrix

Attempts since Mar 2023: 16 · accepted: 12 · failed before first AC: 0

## Attempt 1 · 2023-03-19 12:07 IST · Accepted · C++

[submission 917948684](https://leetcode.com/submissions/detail/917948684/) · tests 49/49 · runtime 36 ms (beats 12.2%)

```cpp
class Solution {
public:
    // vector<pair<int,int>> diff = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    // void dfs(int u, int v, vector<vector<bool>> &visited, vector<vector<char>>& grid){
    //     int m = grid.size();
    //     int n = grid[0].size();
    //     visited[u][v] = true;

    //     for(int i = 0;i<diff.size();i++){
    //         int x = u + diff[i].first;
    //         int y = v + diff[i].second;

    //         if(x<0 && x>=m && y<0 && y>=n){
    //             continue;
    //         }
    //         if(!visited[x][y] && grid[x][y] == '1'){
    //             dfs(x,y, visited, grid);
    //         }
    //     }
    // }
    // int numIslands(vector<vector<char>>& grid) {
    //     int m = grid.size();
    //     int n = grid[0].size();
    //     vector<vector<bool>> visited(m, vector<bool>(n, false));

    //     int islands =0;
    //     for(int i = 0;i<m;i++){
    //         for(int j=0;j<n;j++){
    //             if(!visited[i][j] && grid[i][j] == '1'){
    //                 dfs(i,j, visited, grid);
    //                 islands++;
    //             }
    //         }
    //     }

    //     return islands;
    // }

    void DFS(vector<vector<char>>& grid, int i, int j) {
        // boundary checking
        if(i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size())
            return;
        // return if current position is of water or is already visited
        if(grid[i][j] == '2' || grid[i][j] == '0')
            return;
        
        // mark the current as visited
        grid[i][j] = '2';
        
        // do DFS in all 4 directions
        DFS(grid, i+1, j);
        DFS(grid, i, j-1);
        DFS(grid, i-1, j);
        DFS(grid, i, j+1);
    }
    
    int numIslands(vector<vector<char>>& grid) {
        // We can treat the matrix grid as a grid. Each Island is a
        // connected component. The task is to find no. of disconnectedd components
        // in the graph.
        
        int islands = 0;
        // We make each 1 as 2 in when it is visited
        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[0].size(); j++) {
                // do DFS in case has not been visited and there is land
                if(grid[i][j] == '1') {
                    DFS(grid, i, j);
                    ++islands;
                } 
            }
        }
        return islands;
    }
};
```

## Attempt 2 · 2023-03-22 22:01 IST · Compile Error · C++

[submission 920225256](https://leetcode.com/submissions/detail/920225256/)

Your output:

```text
{"compile_error": "Line 82: Char 28: error: no member named 'numIslands' in 'Solution'\n      int ret = Solution().numIslands(param_1); return ret;\n                ~~~~~~~~~~ ^\n1 error generated."}
```

Compile error:

```text
Line 82: Char 28: error: no member named 'numIslands' in 'Solution'
      int ret = Solution().numIslands(param_1); return ret;
                ~~~~~~~~~~ ^
1 error generated.
```

```cpp
class Solution {
public:
    // vector<pair<int,int>> diff = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    // void dfs(int u, int v, vector<vector<bool>> &visited, vector<vector<char>>& grid){
    //     int m = grid.size();
    //     int n = grid[0].size();
    //     visited[u][v] = true;

    //     for(int i = 0;i<diff.size();i++){
    //         int x = u + diff[i].first;
    //         int y = v + diff[i].second;

    //         if(x<0 && x>=m && y<0 && y>=n){
    //             continue;
    //         }
    //         if(!visited[x][y] && grid[x][y] == '1'){
    //             dfs(x,y, visited, grid);
    //         }
    //     }
    // }
    // int numIslands(vector<vector<char>>& grid) {
    //     int m = grid.size();
    //     int n = grid[0].size();
    //     vector<vector<bool>> visited(m, vector<bool>(n, false));

    //     int islands =0;
    //     for(int i = 0;i<m;i++){
    //         for(int j=0;j<n;j++){
    //             if(!visited[i][j] && grid[i][j] == '1'){
    //                 dfs(i,j, visited, grid);
    //                 islands++;
    //             }
    //         }
    //     }

    //     return islands;
    // }

    void DFS(vector<vector<char>>& grid, int i, int j) {
        // boundary checking
        if(i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size())
            return;
        // return if current position is of water or is already visited
        if(grid[i][j] == '2' || grid[i][j] == '0')
            return;
        
        // mark the current as visited
        grid[i][j] = '2';
        
        // do DFS in all 4 directions
        DFS(grid, i+1, j);
        DFS(grid, i, j-1);
        DFS(grid, i-1, j);
        DFS(grid, i, j+1);
    }
    
    // int numIslands(vector<vector<char>>& grid) {
    //     // We can treat the matrix grid as a grid. Each Island is a
    //     // connected component. The task is to find no. of disconnectedd components
    //     // in the graph.
        
    //     int islands = 0;
    //     // We make each 1 as 2 in when it is visited
    //     for(int i = 0; i < grid.size(); i++) {
    //         for(int j = 0; j < grid[0].size(); j++) {
    //             // do DFS in case has not been visited and there is land
    //             if(grid[i][j] == '1') {
    //                 DFS(grid, i, j);
    //                 ++islands;
    //             } 
    //         }
    //     }
    //     return islands;
    // }
};
```

## Attempt 3 · 2023-03-22 22:10 IST · Compile Error · C++

[submission 920230273](https://leetcode.com/submissions/detail/920230273/)

Your output:

```text
{"compile_error": "Line 82: Char 28: error: no member named 'numIslands' in 'Solution'\n      int ret = Solution().numIslands(param_1); return ret;\n                ~~~~~~~~~~ ^\n1 error generated."}
```

Compile error:

```text
Line 82: Char 28: error: no member named 'numIslands' in 'Solution'
      int ret = Solution().numIslands(param_1); return ret;
                ~~~~~~~~~~ ^
1 error generated.
```

```cpp
class Solution {
public:
    // vector<pair<int,int>> diff = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    // void dfs(int u, int v, vector<vector<bool>> &visited, vector<vector<char>>& grid){
    //     int m = grid.size();
    //     int n = grid[0].size();
    //     visited[u][v] = true;

    //     for(int i = 0;i<diff.size();i++){
    //         int x = u + diff[i].first;
    //         int y = v + diff[i].second;

    //         if(x<0 && x>=m && y<0 && y>=n){
    //             continue;
    //         }
    //         if(!visited[x][y] && grid[x][y] == '1'){
    //             dfs(x,y, visited, grid);
    //         }
    //     }
    // }
    // int numIslands(vector<vector<char>>& grid) {
    //     int m = grid.size();
    //     int n = grid[0].size();
    //     vector<vector<bool>> visited(m, vector<bool>(n, false));

    //     int islands =0;
    //     for(int i = 0;i<m;i++){
    //         for(int j=0;j<n;j++){
    //             if(!visited[i][j] && grid[i][j] == '1'){
    //                 dfs(i,j, visited, grid);
    //                 islands++;
    //             }
    //         }
    //     }

    //     return islands;
    // }

    void DFS(vector<vector<char>>& grid, int i, int j) {
        // boundary checking
        if(i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size())
            return;
        // return if current position is of water or is already visited
        if(grid[i][j] == '2' || grid[i][j] == '0')
            return;
        
        // mark the current as visited
        grid[i][j] = '2';
        
        // do DFS in all 4 directions
        DFS(grid, i+1, j);
        DFS(grid, i, j-1);
        DFS(grid, i-1, j);
        DFS(grid, i, j+1);
    }
    
    // int numIslands(vector<vector<char>>& grid) {
    //     // We can treat the matrix grid as a grid. Each Island is a
    //     // connected component. The task is to find no. of disconnectedd components
    //     // in the graph.
        
    //     int islands = 0;
    //     // We make each 1 as 2 in when it is visited
    //     for(int i = 0; i < grid.size(); i++) {
    //         for(int j = 0; j < grid[0].size(); j++) {
    //             // do DFS in case has not been visited and there is land
    //             if(grid[i][j] == '1') {
    //                 DFS(grid, i, j);
    //                 ++islands;
    //             } 
    //         }
    //     }
    //     return islands;
    // }
};
```

## Attempt 4 · 2023-03-22 22:11 IST · Accepted · C++

[submission 920230965](https://leetcode.com/submissions/detail/920230965/) · tests 49/49 · runtime 40 ms (beats 9.6%)

```cpp
class Solution {
public:
    // vector<pair<int,int>> diff = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    // void dfs(int u, int v, vector<vector<bool>> &visited, vector<vector<char>>& grid){
    //     int m = grid.size();
    //     int n = grid[0].size();
    //     visited[u][v] = true;

    //     for(int i = 0;i<diff.size();i++){
    //         int x = u + diff[i].first;
    //         int y = v + diff[i].second;

    //         if(x<0 && x>=m && y<0 && y>=n){
    //             continue;
    //         }
    //         if(!visited[x][y] && grid[x][y] == '1'){
    //             dfs(x,y, visited, grid);
    //         }
    //     }
    // }
    // int numIslands(vector<vector<char>>& grid) {
    //     int m = grid.size();
    //     int n = grid[0].size();
    //     vector<vector<bool>> visited(m, vector<bool>(n, false));

    //     int islands =0;
    //     for(int i = 0;i<m;i++){
    //         for(int j=0;j<n;j++){
    //             if(!visited[i][j] && grid[i][j] == '1'){
    //                 dfs(i,j, visited, grid);
    //                 islands++;
    //             }
    //         }
    //     }

    //     return islands;
    // }

    void DFS(vector<vector<char>>& grid, int i, int j) {
        // boundary checking
        if(i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size())
            return;
        // return if current position is of water or is already visited
        if(grid[i][j] == '2' || grid[i][j] == '0')
            return;
        
        // mark the current as visited
        grid[i][j] = '2';
        
        // do DFS in all 4 directions
        DFS(grid, i+1, j);
        DFS(grid, i, j-1);
        DFS(grid, i-1, j);
        DFS(grid, i, j+1);
    }
    
    int numIslands(vector<vector<char>>& grid) {
        // We can treat the matrix grid as a grid. Each Island is a
        // connected component. The task is to find no. of disconnectedd components
        // in the graph.
        
        int islands = 0;
        // We make each 1 as 2 in when it is visited
        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[0].size(); j++) {
                // do DFS in case has not been visited and there is land
                if(grid[i][j] == '1') {
                    DFS(grid, i, j);
                    ++islands;
                } 
            }
        }
        return islands;
    }
};
```

## Attempt 5 · 2023-03-22 22:12 IST · Accepted · C++

[submission 920231136](https://leetcode.com/submissions/detail/920231136/) · tests 49/49 · runtime 40 ms (beats 9.6%)

```cpp
class Solution {
public:
    // vector<pair<int,int>> diff = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    // void dfs(int u, int v, vector<vector<bool>> &visited, vector<vector<char>>& grid){
    //     int m = grid.size();
    //     int n = grid[0].size();
    //     visited[u][v] = true;

    //     for(int i = 0;i<diff.size();i++){
    //         int x = u + diff[i].first;
    //         int y = v + diff[i].second;

    //         if(x<0 && x>=m && y<0 && y>=n){
    //             continue;
    //         }
    //         if(!visited[x][y] && grid[x][y] == '1'){
    //             dfs(x,y, visited, grid);
    //         }
    //     }
    // }
    // int numIslands(vector<vector<char>>& grid) {
    //     int m = grid.size();
    //     int n = grid[0].size();
    //     vector<vector<bool>> visited(m, vector<bool>(n, false));

    //     int islands =0;
    //     for(int i = 0;i<m;i++){
    //         for(int j=0;j<n;j++){
    //             if(!visited[i][j] && grid[i][j] == '1'){
    //                 dfs(i,j, visited, grid);
    //                 islands++;
    //             }
    //         }
    //     }

    //     return islands;
    // }

    void DFS(vector<vector<char>>& grid, int i, int j) {
        // boundary checking
        if(i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size())
            return;
        // return if current position is of water or is already visited
        if(grid[i][j] == '2' || grid[i][j] == '0')
            return;
        
        // mark the current as visited
        grid[i][j] = '2';
        
        // do DFS in all 4 directions
        DFS(grid, i+1, j);
        DFS(grid, i, j-1);
        DFS(grid, i-1, j);
        DFS(grid, i, j+1);
    }
    
    int numIslands(vector<vector<char>>& grid) {
        // We can treat the matrix grid as a grid. Each Island is a
        // connected component. The task is to find no. of disconnectedd components
        // in the graph.
        
        int islands = 0;
        // We make each 1 as 2 in when it is visited
        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[0].size(); j++) {
                // do DFS in case has not been visited and there is land
                if(grid[i][j] == '1') {
                    DFS(grid, i, j);
                    ++islands;
                } 
            }
        }
        return islands;
    }
};
```

## Attempt 6 · 2023-11-16 01:03 IST · Accepted · Python

[submission 1099593783](https://leetcode.com/submissions/detail/1099593783/) · tests 49/49 · runtime 228 ms (beats 55.7%)

```python
class Solution(object):
    def numIslands(self, grid):
        """
        :type grid: List[List[str]]
        :rtype: int
        """
        m = len(grid)
        n = len(grid[0])
        count =0

        def dfs(r,c):
            grid[r][c] = '0'
            for nr, nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]:
                if 0 <= nr < m and 0 <= nc < n and grid[nr][nc] == '1':
                    dfs(nr,nc)
        
            
        for r in range(m):
            for c in range(n):
                if grid[r][c] =='1':
                    count+=1
                    dfs(r,c)
        
        return count
```

## Attempt 7 · 2023-11-24 05:14 IST · Accepted · Python3

[submission 1105137836](https://leetcode.com/submissions/detail/1105137836/) · tests 49/49 · runtime 272 ms (beats 16.6%)

```python
class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:

        N = len(grid)
        M = len(grid[0])
        
        def mark(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<M and grid[nr][nc]=='1':
                    grid[nr][nc] = '2'
                    mark(nr,nc)
        
        count = 0
        for i in range(N):
            for j in range(M):
                if grid[i][j]=='1':
                    count +=1
                    mark(i,j)

        return count
```

## Attempt 8 · 2023-11-24 05:22 IST · Accepted · Python3

[submission 1105140025](https://leetcode.com/submissions/detail/1105140025/) · tests 49/49 · runtime 292 ms (beats 7.4%)

```python
class Solution:
    def numIslands1(self, grid: List[List[str]]) -> int:

        N = len(grid)
        M = len(grid[0])
        
        def mark(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<M and grid[nr][nc]=='1':
                    grid[nr][nc] = '2'
                    mark(nr,nc)
        
        count = 0
        for i in range(N):
            for j in range(M):
                if grid[i][j]=='1':
                    count +=1
                    mark(i,j)

        return count

    def numIslands(self, grid: List[List[str]]) -> int:
        N = len(grid)
        M = len(grid[0])
        
        count = 0
        for i in range(N):
            for j in range(M):
                if grid[i][j]=='1':
                    count+=1
                    queue = deque([(i,j)])
                    grid[i][j]='2'
                    while queue:
                        r,c = queue.popleft()
                        print(r,c)
                        for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                            if 0<=nr<N and 0<=nc<M and grid[nr][nc]=='1':
                                grid[nr][nc] = '2'
                                queue.append((nr,nc))
        return count
```

## Attempt 9 · 2023-11-24 05:22 IST · Accepted · Python3

[submission 1105140056](https://leetcode.com/submissions/detail/1105140056/) · tests 49/49 · runtime 257 ms (beats 32.5%)

```python
class Solution:
    def numIslands1(self, grid: List[List[str]]) -> int:

        N = len(grid)
        M = len(grid[0])
        
        def mark(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<M and grid[nr][nc]=='1':
                    grid[nr][nc] = '2'
                    mark(nr,nc)
        
        count = 0
        for i in range(N):
            for j in range(M):
                if grid[i][j]=='1':
                    count +=1
                    mark(i,j)

        return count

    def numIslands(self, grid: List[List[str]]) -> int:
        N = len(grid)
        M = len(grid[0])
        
        count = 0
        for i in range(N):
            for j in range(M):
                if grid[i][j]=='1':
                    count+=1
                    queue = deque([(i,j)])
                    grid[i][j]='2'
                    while queue:
                        r,c = queue.popleft()
                        #print(r,c)
                        for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                            if 0<=nr<N and 0<=nc<M and grid[nr][nc]=='1':
                                grid[nr][nc] = '2'
                                queue.append((nr,nc))
        return count
```

## Attempt 10 · 2023-12-25 03:48 IST · Accepted · Python3

[submission 1127722455](https://leetcode.com/submissions/detail/1127722455/) · tests 49/49 · runtime 227 ms (beats 91.1%)

```python
class Solution:
    def numIslands1(self, grid: List[List[str]]) -> int:
        '''
        dfs - because you only visit each cell once and mark it zero and don't visit again
        time - MN
        space - in worst if all are ones it will be MN

        bfs -
        space - min(M,N) - diagonal 
        '''

        N = len(grid)
        M = len(grid[0])
        
        def mark(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<M and grid[nr][nc]=='1':
                    grid[nr][nc] = '2'
                    mark(nr,nc)
        
        count = 0
        for i in range(N):
            for j in range(M):
                if grid[i][j]=='1':
                    count +=1
                    mark(i,j)

        return count

    def numIslands(self, grid: List[List[str]]) -> int:
        N = len(grid)
        M = len(grid[0])
        
        count = 0
        for i in range(N):
            for j in range(M):
                if grid[i][j]=='1':
                    count+=1
                    # 1. intiialize queue and set visited
                    queue = deque([(i,j)])
                    grid[i][j]='2'


                    # while queue
                    while queue:
                        r,c = queue.popleft()
                        #print(r,c)
                        for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                            if 0<=nr<N and 0<=nc<M and grid[nr][nc]=='1':
                                
                                # set isited and add to queue
                                grid[nr][nc] = '2'
                                queue.append((nr,nc))
        return count
```

## Attempt 11 · 2023-12-31 08:43 IST · Wrong Answer · Python3

[submission 1132674438](https://leetcode.com/submissions/detail/1132674438/) · tests 21/49

Failing input:

```text
[["1","1","0","0","0"],["1","1","0","0","0"],["0","0","1","0","0"],["0","0","0","1","1"]]
```

Expected:

```text
3
```

Your output:

```text
1
```

```python
class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        def dfs(r,c,visited):
            if (r,c) in visited:
                return 
            
            visited.add((r,c))
            count = 1
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc <len(grid[0]) and grid[nr][nc] ==1:
                    count += dfs(nr,nc,visited)
                    
            return count
        
        return dfs(0,0,set())
```

## Attempt 12 · 2023-12-31 08:50 IST · Accepted · Python3

[submission 1132681858](https://leetcode.com/submissions/detail/1132681858/) · tests 49/49 · runtime 390 ms (beats 5.0%)

```python
class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        def mark(r,c):
            
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc] =="1":
                    grid[nr][nc] = "0"
                    mark(nr,nc)
        
        count =0
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] == "1":
                    count +=1
                    mark(r,c)
                    
        return count
```

## Attempt 13 · 2024-01-05 09:23 IST · Accepted · Python3

[submission 1137248532](https://leetcode.com/submissions/detail/1137248532/) · tests 49/49 · runtime 219 ms (beats 95.7%)

```python
class Solution:
    def numIslands1(self, grid: List[List[str]]) -> int:
        '''
        dfs - because you only visit each cell once and mark it zero and don't visit again
        time - MN
        space - in worst if all are ones it will be MN

        bfs -
        space - min(M,N) - diagonal 
        '''

        N = len(grid)
        M = len(grid[0])
        
        def mark(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<M and grid[nr][nc]=='1':
                    grid[nr][nc] = '2'
                    mark(nr,nc)
        
        count = 0
        for i in range(N):
            for j in range(M):
                if grid[i][j]=='1':
                    count +=1
                    mark(i,j)

        return count

    def numIslands(self, grid: List[List[str]]) -> int:
        N = len(grid)
        M = len(grid[0])
        
        count = 0
        for i in range(N):
            for j in range(M):
                if grid[i][j]=='1':
                    count+=1
                    # 1. intiialize queue and set visited
                    queue = deque([(i,j)])
                    grid[i][j]='2'


                    # while queue
                    while queue:
                        r,c = queue.popleft()
                        #print(r,c)
                        for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                            if 0<=nr<N and 0<=nc<M and grid[nr][nc]=='1':
                                
                                # set isited and add to queue
                                grid[nr][nc] = '2'
                                queue.append((nr,nc))
        return count

    def numIslands(self, grid: List[List[str]]) -> int:
        N = len(grid)
        M = len(grid[0])

        def mark(r,c):
            
            # mark visited
            grid[r][c] ='0'

            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]:
                if 0<=nr<N and 0<=nc<M and grid[nr][nc] == '1':
                    mark(nr,nc)

        island_count =0       
        for r in range(N):
            for c in range(M):
                if grid[r][c] == '1':
                    island_count +=1
                    mark(r,c)

        return island_count
```

## Attempt 14 · 2024-01-05 09:29 IST · Output Limit Exceeded · Python3

[submission 1137252497](https://leetcode.com/submissions/detail/1137252497/) · tests 48/49

Failing input:

```text
[["0","0","0","1","1","0","1","1","0","1","1","1","1","0","1","1","1","1","1","0","0","1","0","1","0","1","1","1","1","0","0","1","0","0","1","0","1","1","1","1","1","1","1","1","0","1","1","1","1","1","0","1","1","1","0","1","0","0","1","1","0","1","1","1","1","1","1","0","0","1","1","1","0","0","0","0","1","0","1","0","0","0","1","1","1","0","1","0","0","1","1","0","0","0","0","1","0","0","1","0 ... [360201 more chars]
```

Expected:

```text
6121
```

```python
class Solution:
    def numIslands1(self, grid: List[List[str]]) -> int:
        '''
        dfs - because you only visit each cell once and mark it zero and don't visit again
        time - MN
        space - in worst if all are ones it will be MN

        bfs -
        space - min(M,N) - diagonal 
        '''

        N = len(grid)
        M = len(grid[0])
        
        def mark(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<M and grid[nr][nc]=='1':
                    grid[nr][nc] = '2'
                    mark(nr,nc)
        
        count = 0
        for i in range(N):
            for j in range(M):
                if grid[i][j]=='1':
                    count +=1
                    mark(i,j)

        return count

    def numIslands(self, grid: List[List[str]]) -> int:
        N = len(grid)
        M = len(grid[0])
        
        count = 0
        for i in range(N):
            for j in range(M):
                if grid[i][j]=='1':
                    count+=1
                    # 1. intiialize queue and set visited
                    queue = deque([(i,j)])
                    grid[i][j]='2'


                    # while queue
                    while queue:
                        r,c = queue.popleft()
                        #print(r,c)
                        for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                            if 0<=nr<N and 0<=nc<M and grid[nr][nc]=='1':
                                
                                # set isited and add to queue
                                grid[nr][nc] = '2'
                                queue.append((nr,nc))
        return count

    def numIslands(self, grid: List[List[str]]) -> int:
        N = len(grid)
        M = len(grid[0])
        visited = set()
        def mark1(r,c):
            # 1. check visited

            # 2. mark visited
            grid[r][c] ='0'

            #3. process neighbors
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]: 
                if 0<=nr<N and 0<=nc<M and grid[nr][nc] == '1':
                    mark(nr,nc)

        def mark(r,c):
            # 1. check visited
            if (r,c) in visited:
                return 

            # 2. mark visited
            visited.add((r,c))

            #3. process neighbors
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]: 
                if 0<=nr<N and 0<=nc<M and grid[nr][nc] == '1':
                    mark(nr,nc)

        island_count =0       
        for r in range(N):
            for c in range(M):
                if grid[r][c] == '1' and (r,c) not in visited:
                    island_count +=1
                    mark(r,c)
                    print(visited)

        return island_count
```

## Attempt 15 · 2024-01-05 09:29 IST · Accepted · Python3

[submission 1137252595](https://leetcode.com/submissions/detail/1137252595/) · tests 49/49 · runtime 266 ms (beats 22.1%)

```python
class Solution:
    def numIslands1(self, grid: List[List[str]]) -> int:
        '''
        dfs - because you only visit each cell once and mark it zero and don't visit again
        time - MN
        space - in worst if all are ones it will be MN

        bfs -
        space - min(M,N) - diagonal 
        '''

        N = len(grid)
        M = len(grid[0])
        
        def mark(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<M and grid[nr][nc]=='1':
                    grid[nr][nc] = '2'
                    mark(nr,nc)
        
        count = 0
        for i in range(N):
            for j in range(M):
                if grid[i][j]=='1':
                    count +=1
                    mark(i,j)

        return count

    def numIslands(self, grid: List[List[str]]) -> int:
        N = len(grid)
        M = len(grid[0])
        
        count = 0
        for i in range(N):
            for j in range(M):
                if grid[i][j]=='1':
                    count+=1
                    # 1. intiialize queue and set visited
                    queue = deque([(i,j)])
                    grid[i][j]='2'


                    # while queue
                    while queue:
                        r,c = queue.popleft()
                        #print(r,c)
                        for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                            if 0<=nr<N and 0<=nc<M and grid[nr][nc]=='1':
                                
                                # set isited and add to queue
                                grid[nr][nc] = '2'
                                queue.append((nr,nc))
        return count

    def numIslands(self, grid: List[List[str]]) -> int:
        N = len(grid)
        M = len(grid[0])
        visited = set()
        def mark1(r,c):
            # 1. check visited

            # 2. mark visited
            grid[r][c] ='0'

            #3. process neighbors
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]: 
                if 0<=nr<N and 0<=nc<M and grid[nr][nc] == '1':
                    mark(nr,nc)

        def mark(r,c):
            # 1. check visited
            if (r,c) in visited:
                return 

            # 2. mark visited
            visited.add((r,c))

            #3. process neighbors
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]: 
                if 0<=nr<N and 0<=nc<M and grid[nr][nc] == '1':
                    mark(nr,nc)

        island_count =0       
        for r in range(N):
            for c in range(M):
                if grid[r][c] == '1' and (r,c) not in visited:
                    island_count +=1
                    mark(r,c)
                    # print(visited)

        return island_count
```

## Attempt 16 · 2024-02-04 10:05 IST · Accepted · Python3

[submission 1165506805](https://leetcode.com/submissions/detail/1165506805/) · tests 49/49 · runtime 272 ms (beats 16.6%)

```python
class Solution:
    def numIslands1(self, grid: List[List[str]]) -> int:
        '''
        dfs - because you only visit each cell once and mark it zero and don't visit again
        time - MN
        space - in worst if all are ones it will be MN

        bfs -
        space - min(M,N) - diagonal 
        '''

        N = len(grid)
        M = len(grid[0])
        
        def mark(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<M and grid[nr][nc]=='1':
                    grid[nr][nc] = '2'
                    mark(nr,nc)
        
        count = 0
        for i in range(N):
            for j in range(M):
                if grid[i][j]=='1':
                    count +=1
                    mark(i,j)

        return count

    def numIslands(self, grid: List[List[str]]) -> int:
        N = len(grid)
        M = len(grid[0])
        
        count = 0
        for i in range(N):
            for j in range(M):
                if grid[i][j]=='1':
                    count+=1
                    # 1. intiialize queue and set visited
                    queue = deque([(i,j)])
                    grid[i][j]='2'
                    
                    # while queue
                    while queue:
                        r,c = queue.popleft()
                        #print(r,c)
                        for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                            if 0<=nr<N and 0<=nc<M and grid[nr][nc]=='1':
                                
                                # set isited and add to queue
                                grid[nr][nc] = '2'
                                queue.append((nr,nc))
        return count

    def numIslands(self, grid: List[List[str]]) -> int:
        N = len(grid)
        M = len(grid[0])
        visited = set()
        def mark1(r,c):
            # 1. check visited

            # 2. mark visited
            grid[r][c] ='0'

            #3. process neighbors
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]: 
                if 0<=nr<N and 0<=nc<M and grid[nr][nc] == '1':
                    mark(nr,nc)

        def mark(r,c):
            # 1. check visited
            if (r,c) in visited:
                return 

            if not(0<=r<N and 0<=c<M and grid[r][c] == '1'):
                return

            # 2. mark visited
            visited.add((r,c))

            #3. process neighbors
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]: 
                mark(nr,nc)

        island_count =0       
        for r in range(N):
            for c in range(M):
                if grid[r][c] == '1' and (r,c) not in visited:
                    island_count +=1
                    mark(r,c)
                    # print(visited)

        return island_count
```
