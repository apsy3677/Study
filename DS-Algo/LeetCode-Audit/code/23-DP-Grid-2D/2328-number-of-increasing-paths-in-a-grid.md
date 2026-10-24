# 2328. Number of Increasing Paths in a Grid

[Problem](https://leetcode.com/problems/number-of-increasing-paths-in-a-grid/) · Hard · DP: Grid / 2D → Memoized DFS on grid

LeetCode tags: array, dynamic-programming, depth-first-search, breadth-first-search, graph, topological-sort, memoization, matrix

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2024-02-10 15:44 IST · Runtime Error · Python3

[submission 1171312145](https://leetcode.com/submissions/detail/1171312145/) · tests 34/36

Failing input:

```text
[[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100],[200,199,198,197,196,195,194,193,192,191,190,189,188,187,186,185,184,183,182,181,180,179,178,177,176,175, ... [590496 more chars]
```

Expected:

```text
367051581
```

Runtime error:

```text
TypeError: 94455425209234309876102631060563696769834063587235954008294414366719453713283247565066340238306069892162472348881781114580504442359949202812921524022102931985316089034098001283845486429682533106859144633258766335144072814507530984020117833359077826144497324616587311057856499780292723960676145816043006293286378688852928801457327560064413185158716814529002851570213516375243549471164161548 ... [3912 more chars]
```

```python
class Solution:
    def countPaths(self, grid: List[List[int]]) -> int:
        memo = {}
        rows, cols = len(grid), len(grid[0])
        
        def dfs(r, c):
            # Return the cached result if it exists
            if (r, c) in memo:
                return memo[(r, c)]
            
            # Initialize paths from this cell as 1 (itself)
            paths = 1
            
            # Explore all four directions
            for nr, nc in [(r+1, c), (r, c+1), (r, c-1), (r-1, c)]:
                if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] > grid[r][c]:
                    # Add paths from the neighbor cell
                    paths += dfs(nr, nc)
            
            # Cache and return the result
            memo[(r, c)] = paths
            return paths

        total_paths = 0
        for r in range(rows):
            for c in range(cols):
                total_paths += dfs(r, c)
                
        return total_paths
```

## Attempt 2 · 2024-02-10 15:47 IST · Accepted · Python3

[submission 1171314082](https://leetcode.com/submissions/detail/1171314082/) · tests 36/36 · runtime 1638 ms (beats 5.1%)

```python
class Solution:
    def countPaths(self, grid: List[List[int]]) -> int:
        memo = {}
        rows, cols = len(grid), len(grid[0])
        
        def dfs(r, c):
            # Return the cached result if it exists
            if (r, c) in memo:
                return memo[(r, c)]
            
            # Initialize paths from this cell as 1 (itself)
            paths = 1
            
            # Explore all four directions
            for nr, nc in [(r+1, c), (r, c+1), (r, c-1), (r-1, c)]:
                if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] > grid[r][c]:
                    # Add paths from the neighbor cell
                    paths += dfs(nr, nc)
            
            # Cache and return the result
            memo[(r, c)] = paths
            return paths

        total_paths = 0
        for r in range(rows):
            for c in range(cols):
                total_paths += dfs(r, c)
                
        return total_paths % (pow(10,9) + 7)
```
