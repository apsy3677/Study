# 329. Longest Increasing Path in a Matrix

[Problem](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/) · Hard · DP: Grid / 2D → Memoized DFS on grid

LeetCode tags: array, dynamic-programming, depth-first-search, breadth-first-search, graph, topological-sort, memoization, matrix, directed-acyclic-graph

Attempts since Mar 2023: 8 · accepted: 4 · failed before first AC: 1

## Attempt 1 · 2023-03-25 17:01 IST · Time Limit Exceeded · C++

[submission 921813513](https://leetcode.com/submissions/detail/921813513/) · tests 135/138

Failing input:

```text
[[0,1,2,3,4,5,6,7,8,9],[19,18,17,16,15,14,13,12,11,10],[20,21,22,23,24,25,26,27,28,29],[39,38,37,36,35,34,33,32,31,30],[40,41,42,43,44,45,46,47,48,49],[59,58,57,56,55,54,53,52,51,50],[60,61,62,63,64,65,66,67,68,69],[79,78,77,76,75,74,73,72,71,70],[80,81,82,83,84,85,86,87,88,89],[99,98,97,96,95,94,93,92,91,90],[100,101,102,103,104,105,106,107,108,109],[119,118,117,116,115,114,113,112,111,110],[120, ... [101 more chars]
```

Expected:

```text
140
```

```cpp
class Solution {
    vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int m,n;
public:

    int dfsBruteForce(int i, int j, vector<vector<int>>& matrix){
        int ans  = 0;
        for(auto d: dirs){
            int x = i +d[0], y = j + d[1];
            if(x<0 || x>=n || y<0 || y>=m)
                continue;
            if(matrix[x][y] > matrix[i][j]) // condition to call dfs if val > exiting val 
                ans = max(ans, dfsBruteForce(x, y, matrix));
        }
        ans++;
        return ans;
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if(matrix.size() == 0)
            return 0;
        n = matrix.size();
        m = matrix[0].size();

        int ans =0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                ans = max(ans, dfsBruteForce(i,j, matrix));
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-03-25 17:05 IST · Accepted · C++

[submission 921815109](https://leetcode.com/submissions/detail/921815109/) · tests 138/138 · runtime 196 ms (beats 5.7%)

```cpp
class Solution {
    vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int m,n;
    vector<vector<int>> dp;
public:

    int dfsBruteForce(int i, int j, vector<vector<int>>& matrix){
        // O(2 Power (m+n))

        // memoization
        if(dp[i][j] != -1){
            return dp[i][j];
        }
        int ans  = 0;
        for(auto d: dirs){
            int x = i +d[0], y = j + d[1];
            if(x<0 || x>=n || y<0 || y>=m)
                continue;
            if(matrix[x][y] > matrix[i][j]) // condition to call dfs if val > exiting val 
                ans = max(ans, dfsBruteForce(x, y, matrix));
        }
        ans++;
        dp[i][j] = ans;
        return ans;
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if(matrix.size() == 0)
            return 0;
        n = matrix.size();
        m = matrix[0].size();

        int ans =0;
        dp.resize(n+1, vector<int>(m+1, -1));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                ans = max(ans, dfsBruteForce(i,j, matrix));
            }
        }
        return ans;
    }
};
```

## Attempt 3 · 2023-03-25 17:07 IST · Accepted · C++

[submission 921815666](https://leetcode.com/submissions/detail/921815666/) · tests 138/138 · runtime 195 ms (beats 5.8%)

```cpp
class Solution {
    vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int m,n;
    vector<vector<int>> dp;
public:

    int dfsBruteForce(int i, int j, vector<vector<int>>& matrix){
        // O(2 Power (m+n))

        // memoization
        if(dp[i][j] != -1){
            return dp[i][j];
        }
        int ans  = 0;
        for(auto d: dirs){
            int x = i +d[0], y = j + d[1];
            if(x<0 || x>=n || y<0 || y>=m)
                continue;
            if(matrix[x][y] > matrix[i][j]) // condition to call dfs if val > exiting val 
                ans = max(ans, dfsBruteForce(x, y, matrix));
        }
        ans++;
        dp[i][j] = ans;
        return ans;
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if(matrix.size() == 0)
            return 0;
        n = matrix.size();
        m = matrix[0].size();

        int ans =0;
        dp.resize(n+1, vector<int>(m+1, -1));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                ans = max(ans, dfsBruteForce(i,j, matrix));
            }
        }
        return ans;
    }
};
```

## Attempt 4 · 2023-12-11 03:13 IST · Accepted · Python3

[submission 1116748603](https://leetcode.com/submissions/detail/1116748603/) · tests 138/138 · runtime 329 ms (beats 5.0%)

```python
class Solution:
    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        """
        for each cell save the value of longest path from this as the starting point and go on keeping track of max so far
        """
        if not matrix:
            return 0

        m, n = len(matrix), len(matrix[0])
        memo = [[-1]*n for _ in range(m)]

        def dfs(x,y):
            # base condition of quantization
            if memo[x][y] != -1:
                return memo[x][y]

            # defualt path length
            longest = 1

            # memoization recusion call
            for nx, ny in [(x+1,y),(x,y+1),(x-1,y),(x,y-1)]:
                if 0<=nx<m and 0<=ny<n and matrix[nx][ny] > matrix[x][y]:
                    longest = max(longest, 1+ dfs(nx,ny))

            # assign value for this call
            memo[x][y] = longest

            # return value for this cell
            return longest

        result = 0
        for i in range(m):
            for j in range(n):
                result = max(result, dfs(i,j))

        return result
```

## Attempt 5 · 2023-12-28 20:08 IST · Wrong Answer · Python3

[submission 1130607430](https://leetcode.com/submissions/detail/1130607430/) · tests 30/138

Failing input:

```text
[[7,7,5],[2,4,6],[8,2,0]]
```

Expected:

```text
4
```

Your output:

```text
3
```

```python
class Solution:
    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        """
        for each cell save the value of longest path from this as the starting point and go on keeping track of max so far
        """
        if not matrix:
            return 0

        m, n = len(matrix), len(matrix[0])
        memo = [[-1]*n for _ in range(m)]

        def dfs(x,y):
            # base condition of quantization
            if memo[x][y] != -1:
                return memo[x][y]

            # defualt path length
            longest = 1

            # memoization recusion call
            for nx, ny in [(x+1,y),(x,y+1),(x-1,y),(x,y-1)]:
                if 0<=nx<m and 0<=ny<n and matrix[nx][ny] > matrix[x][y]:
                    longest = max(longest, 1+ dfs(nx,ny))

            # assign value for this call
            memo[x][y] = longest

            # return value for this cell
            return longest

        result = 0
        for i in range(m):
            for j in range(n):
                result = max(result, dfs(i,j))

        return result

    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        '''
        1. the longest sequence can start from any cell in the matrix

        approach 1 - for each cell, go and find the increasing path and update longest
        optimization - all the cell which come on the visited path - can be ignore on the next run because we would have already discovered the longest path which uses this cells
        '''
        def dfs(r,c):
            path = 1

            for nr,nc in [(r,c+1),(r+1,c),(r-1,c),(r,c-1)]:
                if 0<=nr<len(matrix) and 0<=nc<len(matrix[0]) and matrix[nr][nc]> matrix[r][c]:
                    path = 1 + dfs(nr,nc)
            
            return path

        longestPath = 0
        for r in range(len(matrix)):
            for c in range(len(matrix[0])):
                longestPath = max(longestPath, dfs(r,c))
        return longestPath
```

## Attempt 6 · 2023-12-28 20:13 IST · Time Limit Exceeded · Python3

[submission 1130610793](https://leetcode.com/submissions/detail/1130610793/) · tests 135/138

Failing input:

```text
[[0,1,2,3,4,5,6,7,8,9],[19,18,17,16,15,14,13,12,11,10],[20,21,22,23,24,25,26,27,28,29],[39,38,37,36,35,34,33,32,31,30],[40,41,42,43,44,45,46,47,48,49],[59,58,57,56,55,54,53,52,51,50],[60,61,62,63,64,65,66,67,68,69],[79,78,77,76,75,74,73,72,71,70],[80,81,82,83,84,85,86,87,88,89],[99,98,97,96,95,94,93,92,91,90],[100,101,102,103,104,105,106,107,108,109],[119,118,117,116,115,114,113,112,111,110],[120, ... [101 more chars]
```

Expected:

```text
140
```

```python
class Solution:
    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        """
        for each cell save the value of longest path from this as the starting point and go on keeping track of max so far
        """
        if not matrix:
            return 0

        m, n = len(matrix), len(matrix[0])
        memo = [[-1]*n for _ in range(m)]

        def dfs(x,y):
            # base condition of quantization
            if memo[x][y] != -1:
                return memo[x][y]

            # defualt path length
            longest = 1

            # memoization recusion call
            for nx, ny in [(x+1,y),(x,y+1),(x-1,y),(x,y-1)]:
                if 0<=nx<m and 0<=ny<n and matrix[nx][ny] > matrix[x][y]:
                    longest = max(longest, 1+ dfs(nx,ny))

            # assign value for this call
            memo[x][y] = longest

            # return value for this cell
            return longest

        result = 0
        for i in range(m):
            for j in range(n):
                result = max(result, dfs(i,j))

        return result

    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        '''
        1. the longest sequence can start from any cell in the matrix

        approach 1 - for each cell, go and find the increasing path and update longest
        optimization - all the cell which come on the visited path - can be ignore on the next run because we would have already discovered the longest path which uses this cells
        '''
        def dfs(r,c):
            path = 1

            for nr,nc in [(r,c+1),(r+1,c),(r-1,c),(r,c-1)]:
                if 0<=nr<len(matrix) and 0<=nc<len(matrix[0]) and matrix[nr][nc]> matrix[r][c]:
                    path = max(path, 1 + dfs(nr,nc))
            
            return path

        longestPath = 0
        for r in range(len(matrix)):
            for c in range(len(matrix[0])):
                longestPath = max(longestPath, dfs(r,c))
        return longestPath
```

## Attempt 7 · 2023-12-28 20:14 IST · Time Limit Exceeded · Python3

[submission 1130611844](https://leetcode.com/submissions/detail/1130611844/) · tests 135/138

Failing input:

```text
[[0,1,2,3,4,5,6,7,8,9],[19,18,17,16,15,14,13,12,11,10],[20,21,22,23,24,25,26,27,28,29],[39,38,37,36,35,34,33,32,31,30],[40,41,42,43,44,45,46,47,48,49],[59,58,57,56,55,54,53,52,51,50],[60,61,62,63,64,65,66,67,68,69],[79,78,77,76,75,74,73,72,71,70],[80,81,82,83,84,85,86,87,88,89],[99,98,97,96,95,94,93,92,91,90],[100,101,102,103,104,105,106,107,108,109],[119,118,117,116,115,114,113,112,111,110],[120, ... [101 more chars]
```

Expected:

```text
140
```

```python
class Solution:
    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        """
        for each cell save the value of longest path from this as the starting point and go on keeping track of max so far
        """
        if not matrix:
            return 0

        m, n = len(matrix), len(matrix[0])
        memo = [[-1]*n for _ in range(m)]

        def dfs(x,y):
            # base condition of quantization
            if memo[x][y] != -1:
                return memo[x][y]

            # defualt path length
            longest = 1

            # memoization recusion call
            for nx, ny in [(x+1,y),(x,y+1),(x-1,y),(x,y-1)]:
                if 0<=nx<m and 0<=ny<n and matrix[nx][ny] > matrix[x][y]:
                    longest = max(longest, 1+ dfs(nx,ny))

            # assign value for this call
            memo[x][y] = longest

            # return value for this cell
            return longest

        result = 0
        for i in range(m):
            for j in range(n):
                result = max(result, dfs(i,j))

        return result

    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        '''
        1. the longest sequence can start from any cell in the matrix

        approach 1 - for each cell, go and find the increasing path and update longest
        optimization - all the cell which come on the visited path - can be ignore on the next run because we would have already discovered the longest path which uses this cells
        '''
        def dfs(r,c):
            path = 1

            for nr,nc in [(r,c+1),(r+1,c),(r-1,c),(r,c-1)]:
                if 0<=nr<len(matrix) and 0<=nc<len(matrix[0]) and matrix[nr][nc]> matrix[r][c]:
                    visited.add((nr,nc))
                    path = max(path, 1 + dfs(nr,nc))
            
            return path

        longestPath = 0
        visited = set()
        for r in range(len(matrix)):
            for c in range(len(matrix[0])):
                if (r,c) not in visited:
                    visited.add((r,c))
                    longestPath = max(longestPath, dfs(r,c))
        return longestPath
```

## Attempt 8 · 2024-01-15 22:54 IST · Accepted · Python3

[submission 1147068669](https://leetcode.com/submissions/detail/1147068669/) · tests 138/138 · runtime 348 ms (beats 5.0%)

```python
class Solution:
    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        """
        for each cell save the value of longest path from this as the starting point and go on keeping track of max so far
        """
        if not matrix:
            return 0

        m, n = len(matrix), len(matrix[0])

        # 1. intialization - table with equal number of cells
        # set any default value 
        memo = [[-1]*n for _ in range(m)]

        def dfs(x,y):
            # base condition of memoization
            # if it is solved
            if memo[x][y] != -1:
                return memo[x][y]

            # defualt path length
            longest = 1

            # memoization recusion call
            for nx, ny in [(x+1,y),(x,y+1),(x-1,y),(x,y-1)]:
                if 0<=nx<m and 0<=ny<n and matrix[nx][ny] > matrix[x][y]:
                    longest = max(longest, 1+ dfs(nx,ny))

            # assign value for this call
            memo[x][y] = longest

            # return value for this cell
            return longest

        result = 0
        for i in range(m):
            for j in range(n):
                result = max(result, dfs(i,j))

        return result

    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        '''
        1. the longest sequence can start from any cell in the matrix

        approach 1 - for each cell, go and find the increasing path and update longest
        optimization - all the cell which come on the visited path - can be ignore on the next run because we would have already discovered the longest path which uses this cells
        '''
        def dfs(r,c):
            # initial distance either zero or 1
            path = 1

            # for each choices from this cell
            for nr,nc in [(r,c+1),(r+1,c),(r-1,c),(r,c-1)]:
                # if it is a valid move
                if 0<=nr<len(matrix) and 0<=nc<len(matrix[0]) and matrix[nr][nc]> matrix[r][c]:
                    path = max(path, 1 + dfs(nr,nc))
            
            return path

        longestPath = 0
        visited = set()
        for r in range(len(matrix)):
            for c in range(len(matrix[0])):
                    longestPath = max(longestPath, dfs(r,c))
        return longestPath

    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        memo = {}
        def dfs(r,c):
            '''
            within this traversal - visited is not required because 
            it is increasing path and cna;t go back from where we came
            if we can visit 1->1 same numbers then may be we need
            '''
            if (r,c) in memo:
                return memo[(r,c)]

            path = 1

            for nr,nc in [(r,c+1),(r+1,c),(r-1,c),(r,c-1)]:
                # if it is a valid move
                if 0<=nr<len(matrix) and 0<=nc<len(matrix[0]) and matrix[nr][nc] > matrix[r][c]:
                    path = max(path, 1+ dfs(nr,nc))
            memo[(r,c)] = path 
            return path

        longest_path = 0
        for r in range(len(matrix)):
            for c in range(len(matrix[0])):
                longest_path = max(longest_path, dfs(r,c))
        return longest_path
```
