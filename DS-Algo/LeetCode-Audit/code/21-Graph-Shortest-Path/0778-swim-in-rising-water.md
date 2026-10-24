# 778. Swim in Rising Water

[Problem](https://leetcode.com/problems/swim-in-rising-water/) · Hard · Graph: Shortest Path → Minimax Dijkstra

LeetCode tags: array, binary-search, depth-first-search, breadth-first-search, union-find, minimax-algorithm, heap-priority-queue, matrix, dijkstra

Attempts since Mar 2023: 6 · accepted: 2 · failed before first AC: 3

## Attempt 1 · 2023-12-31 07:45 IST · Wrong Answer · Python3

[submission 1132617566](https://leetcode.com/submissions/detail/1132617566/) · tests 2/43

Failing input:

```text
[[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
```

Expected:

```text
16
```

Your output:

```text
20
```

```python
class Solution:
    def swimInWater(self, grid: List[List[int]]) -> int:
        # keep a queue of distance and 
        queue = deque([(0,0,0)])
        visited = set({(0,0)})
        
        while queue:
            r,c,depth = queue.popleft()
            
            if r==len(grid)-1 and c == len(grid[0])-1:
                return depth
            
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc < len(grid[0]):
                    ele_diff =grid[nr][nc] - grid[r][c] if grid[r][c] < grid[nr][nc] else 0
                    
                    queue.append((nr,nc,ele_diff+depth))
                    visited.add((nr,nc))
                    
        return -1
```

## Attempt 2 · 2023-12-31 08:06 IST · Time Limit Exceeded · Python3

[submission 1132632572](https://leetcode.com/submissions/detail/1132632572/) · tests 1/43

Failing input:

```text
[[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
```

Expected:

```text
16
```

```python
class Solution:
    def swimInWater(self, grid: List[List[int]]) -> int:
        # 
        # keep a queue of distance and 
        heap = [(grid[0][0],0,0)]
        effort_to = {}
        
        while heap:
            depth,r,c = heapq.heappop(heap)
            
            if r==len(grid)-1 and c == len(grid[0])-1:
                return depth
            
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc < len(grid[0]):
                    ele_diff =grid[nr][nc] - grid[r][c] if grid[r][c] < grid[nr][nc] else 0
                    
                    # if if   ele_diff+depth < effort_to[n]
                    heapq.heappush(heap, (ele_diff+depth,nr,nc))
                    
                    
        return -1
```

## Attempt 3 · 2023-12-31 08:06 IST · Time Limit Exceeded · Python3

[submission 1132632863](https://leetcode.com/submissions/detail/1132632863/) · tests 1/43

Failing input:

```text
[[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
```

Expected:

```text
16
```

```python
class Solution:
    def swimInWater(self, grid: List[List[int]]) -> int:
        # 
        # keep a queue of distance and 
        heap = [(0,0,0)]
        effort_to = {}
        
        while heap:
            depth,r,c = heapq.heappop(heap)
            
            if r==len(grid)-1 and c == len(grid[0])-1:
                return depth
            
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc < len(grid[0]):
                    ele_diff =grid[nr][nc] - grid[r][c] if grid[r][c] < grid[nr][nc] else 0
                    
                    # if if   ele_diff+depth < effort_to[n]
                    heapq.heappush(heap, (ele_diff+depth,nr,nc))
                    
                    
        return -1
```

## Attempt 4 · 2023-12-31 08:14 IST · Accepted · Python3

[submission 1132641819](https://leetcode.com/submissions/detail/1132641819/) · tests 43/43 · runtime 266 ms (beats 5.0%)

```python
class Solution:
    def swimInWater(self, grid: List[List[int]]) -> int:
        N = len(grid)

        def dfs(t, x, y, visited):
            if x == y == N - 1:
                return True
            visited.add((x, y))
            for nx, ny in ((x-1, y), (x+1, y), (x, y-1), (x, y+1)):
                if 0 <= nx < N and 0 <= ny < N and (nx, ny) not in visited and grid[nx][ny] <= t:
                    if dfs(t, nx, ny, visited):
                        return True
            return False

        left, right = grid[0][0], max(max(row) for row in grid)
        while left < right:
            mid = (left + right) // 2
            if dfs(mid, 0, 0, set()):
                right = mid
            else:
                left = mid + 1

        return left
```

## Attempt 5 · 2024-01-27 09:23 IST · Time Limit Exceeded · Python3

[submission 1157922059](https://leetcode.com/submissions/detail/1157922059/) · tests 21/43

Failing input:

```text
[[26,99,80,1,89,86,54,90,47,87],[9,59,61,49,14,55,77,3,83,79],[42,22,15,5,95,38,74,12,92,71],[58,40,64,62,24,85,30,6,96,52],[10,70,57,19,44,27,98,16,25,65],[13,0,76,32,29,45,28,69,53,41],[18,8,21,67,46,36,56,50,51,72],[39,78,48,63,68,91,34,4,11,31],[97,23,60,17,66,37,43,33,84,35],[75,88,82,20,7,73,2,94,93,81]]
```

Expected:

```text
81
```

```python
class Solution:
    def swimInWater(self, grid: List[List[int]]) -> int:
        N = len(grid)

        def dfs(t, x, y, visited):
            if x == y == N - 1:
                return True
            visited.add((x, y))
            for nx, ny in ((x-1, y), (x+1, y), (x, y-1), (x, y+1)):
                if 0 <= nx < N and 0 <= ny < N and (nx, ny) not in visited and grid[nx][ny] <= t:
                    if dfs(t, nx, ny, visited):
                        return True
            visited.remove((x, y))
            return False

        left, right = grid[0][0], max(max(row) for row in grid)
        while left < right:
            mid = (left + right) // 2
            if dfs(mid, 0, 0, set()):
                right = mid
            else:
                left = mid + 1

        return left
```

## Attempt 6 · 2024-01-27 09:24 IST · Accepted · Python3

[submission 1157922288](https://leetcode.com/submissions/detail/1157922288/) · tests 43/43 · runtime 166 ms (beats 5.0%)

```python
class Solution:
    def swimInWater(self, grid: List[List[int]]) -> int:
        N = len(grid)

        def dfs(t, x, y, visited):
            if x == y == N - 1:
                return True
            visited.add((x, y))
            for nx, ny in ((x-1, y), (x+1, y), (x, y-1), (x, y+1)):
                if 0 <= nx < N and 0 <= ny < N and (nx, ny) not in visited and grid[nx][ny] <= t:
                    if dfs(t, nx, ny, visited):
                        return True
            
            return False

        left, right = grid[0][0], max(max(row) for row in grid)
        while left < right:
            mid = (left + right) // 2
            if dfs(mid, 0, 0, set()):
                right = mid
            else:
                left = mid + 1

        return left
```
