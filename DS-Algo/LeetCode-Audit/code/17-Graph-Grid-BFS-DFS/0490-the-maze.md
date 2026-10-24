# 490. The Maze

[Problem](https://leetcode.com/problems/the-maze/) · Medium · Graph: Grid BFS/DFS → Rolling BFS

LeetCode tags: array, depth-first-search, breadth-first-search, matrix

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2023-11-19 20:40 IST · Wrong Answer · Python3

[submission 1102135899](https://leetcode.com/submissions/detail/1102135899/) · tests 39/78

Failing input:

```text
[[0,0,1,0,0],[0,0,0,0,0],[0,0,0,1,0],[1,1,0,1,1],[0,0,0,0,0]]
[0,4]
[1,2]
```

Expected:

```text
true
```

Your output:

```text
false
```

```python
class Solution:
    def hasPath(self, maze: List[List[int]], start: List[int], destination: List[int]) -> bool:
        def dfs(x,y):

            # 1. check visited
            if (x,y) in visited:
                return False 

            
            if [x,y] == destination:
                return True

            #2. set visited
            visited.add((x,y))


            #3. explore neighbors
            for dx, dy in directions:
                nx, ny = x, y
                
                # roll ball until it hits wall
                while  0 <= nx +dx < len(maze) and 0<= ny+dy < len(maze[0]):
                    nx+=dx
                    ny+=dy

                if dfs(nx,ny):
                    return True

            return False

        directions = [(-1,0),(1,0),(0,1),(0,-1)]
        visited=set()
        return dfs(start[0],start[1])
```

## Attempt 2 · 2023-11-19 20:46 IST · Accepted · Python3

[submission 1102138705](https://leetcode.com/submissions/detail/1102138705/) · tests 78/78 · runtime 239 ms (beats 5.2%)

```python
class Solution:
    def hasPath(self, maze: List[List[int]], start: List[int], destination: List[int]) -> bool:
        def dfs(x,y):
            # print('start position', x, y)
            # 1. check visited
            if (x,y) in visited:
                return False 

            
            if [x,y] == destination:
                return True

            #2. set visited
            visited.add((x,y))


            #3. explore neighbors
            for dx, dy in directions:
                nx, ny = x, y
                # print('checking', nx +dx, ny+dy)
                # roll ball until it hits wall
                while  0 <= nx +dx < len(maze) and 0<= ny+dy < len(maze[0]) and maze[nx+dx][ny+dy] == 0:
                    nx+=dx
                    ny+=dy
                

                if (nx,ny) not in visited and dfs(nx,ny):
                    return True

            return False

        directions = [(-1,0),(1,0),(0,1),(0,-1)]
        visited=set()
        
        return dfs(start[0],start[1])
```
