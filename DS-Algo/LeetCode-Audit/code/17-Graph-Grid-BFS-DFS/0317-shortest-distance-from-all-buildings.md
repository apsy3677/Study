# 317. Shortest Distance from All Buildings

[Problem](https://leetcode.com/problems/shortest-distance-from-all-buildings/) · Hard · Graph: Grid BFS/DFS → BFS from each building

LeetCode tags: array, breadth-first-search, matrix

Attempts since Mar 2023: 11 · accepted: 5 · failed before first AC: 2

## Attempt 1 · 2023-11-26 21:49 IST · Output Limit Exceeded · Python3

[submission 1106862429](https://leetcode.com/submissions/detail/1106862429/) · tests 62/85

Failing input:

```text
[[0,2,2,0,0,0,0,2,0,0,2,2,0,2,2,0,0,0,0,0,0,0,2,0,0,0,2,0,2,2,0,0,0,2,0,0,2,0,0,0,2,0,0,2,2,0],[2,2,0,0,0,2,0,0,0,0,0,2,0,2,2,0,2,2,2,2,0,0,0,2,0,0,0,0,0,0,0,0,2,2,0,2,2,0,0,0,0,0,2,2,2,0],[0,0,0,0,2,0,0,0,0,0,1,2,2,0,1,0,0,2,0,0,0,0,2,0,0,0,0,1,2,2,0,1,2,0,0,0,1,0,0,0,0,0,0,2,0,0],[2,0,0,2,0,0,2,0,0,1,2,0,2,2,0,2,0,0,0,0,2,0,0,2,0,0,0,2,2,0,0,2,0,2,0,1,2,0,0,0,0,0,2,2,2,0],[2,0,2,0,1,0,0,0,2,0,0, ... [3549 more chars]
```

Expected:

```text
-1
```

```python
class Solution:
    def shortestDistance(self, grid: List[List[int]]) -> int:

        def bfs(r,c, totalHouses):
            queue = deque([(r,c)])
            visited = set({(r,c)})
            distance_total = 0
            houses_reached = 0
            steps = 0
            while queue and houses_reached < totalHouses:

                size = len(queue)

                for i in range(size):
                    r,c  = queue.popleft()
                    print(r,c)

                    if grid[r][c] == 1:
                        houses_reached+=1
                        distance_total +=steps
                        continue

                    for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                        if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in visited and grid[nr][nc] !=2:
                            visited.add((nr,nc))
                            queue.append((nr,nc))
                steps+=1

            if houses_reached != totalHouses:
                return 2**31 -1


            return distance_total

        totalHouses = 0
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] ==1:
                    totalHouses+=1

        minDistance = 2**31 -1
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] ==0:
                    print('calling',i,j)
                    minDistance = min(minDistance, bfs(i,j,totalHouses))
        
        if minDistance == 2**31 -1:
            return -1
        return minDistance
```

## Attempt 2 · 2023-11-26 21:49 IST · Time Limit Exceeded · Python3

[submission 1106862624](https://leetcode.com/submissions/detail/1106862624/) · tests 78/85

Failing input:

```text
[[0,2,0,0,0,2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,2,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,2,1,0,0,1,0,0,0,0,1,0],[0,2,1,0,0,0,0,0,2,0,1,1,1,2,0,0,0,0,0,1,0,0,0,2,0,0,1,0,0,0,0,0,0,1,0,2,0,1,0,0,0,2,0,0,0,0,0],[0,0,0,0,0,2,0,2,1,0,0,0,2,0,2,0,0,1,1,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,1,0,0,0,0,0,0,2,0,0,0,0,0],[1,0,0,0,1,2,0,0,0,0,2,0,0,0,1,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,1,0,0,0,1],[0,0,0,2,1,0,2, ... [4209 more chars]
```

Expected:

```text
6267
```

```python
class Solution:
    def shortestDistance(self, grid: List[List[int]]) -> int:

        def bfs(r,c, totalHouses):
            queue = deque([(r,c)])
            visited = set({(r,c)})
            distance_total = 0
            houses_reached = 0
            steps = 0
            while queue and houses_reached < totalHouses:

                size = len(queue)

                for i in range(size):
                    r,c  = queue.popleft()
                    #print(r,c)

                    if grid[r][c] == 1:
                        houses_reached+=1
                        distance_total +=steps
                        continue

                    for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                        if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in visited and grid[nr][nc] !=2:
                            visited.add((nr,nc))
                            queue.append((nr,nc))
                steps+=1

            if houses_reached != totalHouses:
                return 2**31 -1


            return distance_total

        totalHouses = 0
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] ==1:
                    totalHouses+=1

        minDistance = 2**31 -1
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] ==0:
                    #print('calling',i,j)
                    minDistance = min(minDistance, bfs(i,j,totalHouses))
        
        if minDistance == 2**31 -1:
            return -1
        return minDistance
```

## Attempt 3 · 2023-11-26 22:56 IST · Accepted · Python3

[submission 1106900347](https://leetcode.com/submissions/detail/1106900347/) · tests 85/85 · runtime 4237 ms (beats 26.5%)

```python
class Solution:
    def shortestDistance1(self, grid: List[List[int]]) -> int:

        def bfs(r,c, totalHouses):
            queue = deque([(r,c)])
            visited = set({(r,c)})
            distance_total = 0
            houses_reached = 0
            steps = 0
            while queue and houses_reached < totalHouses:

                size = len(queue)

                for i in range(size):
                    r,c  = queue.popleft()
                    #print(r,c)

                    if grid[r][c] == 1:
                        houses_reached+=1
                        distance_total +=steps
                        continue

                    for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                        if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in visited and grid[nr][nc] !=2:
                            visited.add((nr,nc))
                            queue.append((nr,nc))
                steps+=1

            if houses_reached != totalHouses:
                return 2**31 -1


            return distance_total

        totalHouses = 0
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] ==1:
                    totalHouses+=1

        minDistance = 2**31 -1
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] ==0:
                    #print('calling',i,j)
                    minDistance = min(minDistance, bfs(i,j,totalHouses))
        
        if minDistance == 2**31 -1:
            return -1
        return minDistance


    def shortestDistance(self, grid: List[List[int]]) -> int:
        if not grid or not grid[0]:
            return -1

        rows, cols = len(grid), len(grid[0])
        total_distance = [[0]*cols for _ in range(rows)]
        reach = [[0]*cols for _ in range(rows)]
        building_count = sum(val ==1 for row in grid for val in row)

        def bfs(r,c):
            visited = [[False]*cols for _ in range(rows)]
            visited[r][c] =True
            queue = deque([(r,c,0)])

            while queue:
                row, col, dist = queue.popleft()
                for dr, dc in [(1,0),(-1,0),(0,1),(0,-1)]:
                    r,c = row +dr , col+dc
                    if 0<=r<rows and 0<=c<cols and not visited[r][c] and grid[r][c]==0:
                        visited[r][c] = True
                        queue.append((r,c,dist+1))
                        total_distance[r][c] += dist +1
                        reach[r][c] +=1

        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 1:
                    bfs(r,c)

        min_distance = math.inf
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 0 and reach[r][c] == building_count:
                    min_distance = min(min_distance, total_distance[r][c])

        return min_distance if min_distance!= math.inf else -1
```

## Attempt 4 · 2023-12-03 04:37 IST · Time Limit Exceeded · Python3

[submission 1111109010](https://leetcode.com/submissions/detail/1111109010/) · tests 78/85

Failing input:

```text
[[0,2,0,0,0,2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,2,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,2,1,0,0,1,0,0,0,0,1,0],[0,2,1,0,0,0,0,0,2,0,1,1,1,2,0,0,0,0,0,1,0,0,0,2,0,0,1,0,0,0,0,0,0,1,0,2,0,1,0,0,0,2,0,0,0,0,0],[0,0,0,0,0,2,0,2,1,0,0,0,2,0,2,0,0,1,1,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,1,0,0,0,0,0,0,2,0,0,0,0,0],[1,0,0,0,1,2,0,0,0,0,2,0,0,0,1,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,1,0,0,0,1],[0,0,0,2,1,0,2, ... [4209 more chars]
```

Expected:

```text
6267
```

```python
class Solution:
    def shortestDistance(self, grid: List[List[int]]) -> int:

        def bfs(r,c, totalHouses):
            queue = deque([(r,c,0)])
            visited = set({(r,c)})
            distance_total = 0
            houses_reached = 0
            while queue and houses_reached < totalHouses:
                r,c, steps  = queue.popleft()
                    #print(r,c)

                if grid[r][c] == 1:
                    houses_reached+=1
                    distance_total +=steps
                    continue

                for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in visited and grid[nr][nc] !=2:
                        visited.add((nr,nc))
                        queue.append((nr,nc, steps+1))
                
            if houses_reached != totalHouses:
                return 2**31 -1

            return distance_total

        totalHouses = sum (val==1 for row in grid for val in row)
        
        minDistance = 2**31 -1
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] ==0:
                    #print('calling',i,j)
                    minDistance = min(minDistance, bfs(i,j,totalHouses))
        
        if minDistance == 2**31 -1:
            return -1
        return minDistance


    def shortestDistance2(self, grid: List[List[int]]) -> int:
        if not grid or not grid[0]:
            return -1

        rows, cols = len(grid), len(grid[0])
        total_distance = [[0]*cols for _ in range(rows)]
        reach = [[0]*cols for _ in range(rows)]
        building_count = sum(val ==1 for row in grid for val in row)

        def bfs(r,c):
            visited = [[False]*cols for _ in range(rows)]
            visited[r][c] =True
            queue = deque([(r,c,0)])

            while queue:
                row, col, dist = queue.popleft()
                for dr, dc in [(1,0),(-1,0),(0,1),(0,-1)]:
                    r,c = row +dr , col+dc
                    if 0<=r<rows and 0<=c<cols and not visited[r][c] and grid[r][c]==0:
                        visited[r][c] = True
                        queue.append((r,c,dist+1))
                        total_distance[r][c] += dist +1
                        reach[r][c] +=1

        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 1:
                    bfs(r,c)

        min_distance = math.inf
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 0 and reach[r][c] == building_count:
                    min_distance = min(min_distance, total_distance[r][c])

        return min_distance if min_distance!= math.inf else -1
```

## Attempt 5 · 2023-12-03 04:40 IST · Accepted · Python3

[submission 1111109853](https://leetcode.com/submissions/detail/1111109853/) · tests 85/85 · runtime 4289 ms (beats 25.2%)

```python
class Solution:
    def shortestDistance2(self, grid: List[List[int]]) -> int:

        def bfs(r,c, totalHouses):
            queue = deque([(r,c,0)])
            visited = set({(r,c)})
            distance_total = 0
            houses_reached = 0
            while queue and houses_reached < totalHouses:
                r,c, steps  = queue.popleft()
                    #print(r,c)

                if grid[r][c] == 1:
                    houses_reached+=1
                    distance_total +=steps
                    continue

                for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in visited and grid[nr][nc] !=2:
                        visited.add((nr,nc))
                        queue.append((nr,nc, steps+1))
                
            if houses_reached != totalHouses:
                return 2**31 -1

            return distance_total

        totalHouses = sum (val==1 for row in grid for val in row)
        
        minDistance = 2**31 -1
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] ==0:
                    #print('calling',i,j)
                    minDistance = min(minDistance, bfs(i,j,totalHouses))
        
        if minDistance == 2**31 -1:
            return -1
        return minDistance


    def shortestDistance(self, grid: List[List[int]]) -> int:
        if not grid or not grid[0]:
            return -1

        rows, cols = len(grid), len(grid[0])
        total_distance = [[0]*cols for _ in range(rows)]
        reach = [[0]*cols for _ in range(rows)]
        building_count = sum(val ==1 for row in grid for val in row)

        def bfs(r,c):
            visited = [[False]*cols for _ in range(rows)]
            visited[r][c] =True
            queue = deque([(r,c,0)])

            while queue:
                row, col, dist = queue.popleft()
                total_distance[row][col] += dist 
                for dr, dc in [(1,0),(-1,0),(0,1),(0,-1)]:
                    r,c = row +dr , col+dc
                    if 0<=r<rows and 0<=c<cols and not visited[r][c] and grid[r][c]==0:
                        visited[r][c] = True
                        queue.append((r,c,dist+1))
                        
                        reach[r][c] +=1

        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 1:
                    bfs(r,c)

        min_distance = math.inf
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 0 and reach[r][c] == building_count:
                    min_distance = min(min_distance, total_distance[r][c])

        return min_distance if min_distance!= math.inf else -1
```

## Attempt 6 · 2023-12-03 04:40 IST · Wrong Answer · Python3

[submission 1111110057](https://leetcode.com/submissions/detail/1111110057/) · tests 75/85

Failing input:

```text
[[1],[0]]
```

Expected:

```text
1
```

Your output:

```text
-1
```

```python
class Solution:
    def shortestDistance2(self, grid: List[List[int]]) -> int:

        def bfs(r,c, totalHouses):
            queue = deque([(r,c,0)])
            visited = set({(r,c)})
            distance_total = 0
            houses_reached = 0
            while queue and houses_reached < totalHouses:
                r,c, steps  = queue.popleft()
                    #print(r,c)

                if grid[r][c] == 1:
                    houses_reached+=1
                    distance_total +=steps
                    continue

                for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in visited and grid[nr][nc] !=2:
                        visited.add((nr,nc))
                        queue.append((nr,nc, steps+1))
                
            if houses_reached != totalHouses:
                return 2**31 -1

            return distance_total

        totalHouses = sum (val==1 for row in grid for val in row)
        
        minDistance = 2**31 -1
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] ==0:
                    #print('calling',i,j)
                    minDistance = min(minDistance, bfs(i,j,totalHouses))
        
        if minDistance == 2**31 -1:
            return -1
        return minDistance


    def shortestDistance(self, grid: List[List[int]]) -> int:
        if not grid or not grid[0]:
            return -1

        rows, cols = len(grid), len(grid[0])
        total_distance = [[0]*cols for _ in range(rows)]
        reach = [[0]*cols for _ in range(rows)]
        building_count = sum(val ==1 for row in grid for val in row)

        def bfs(r,c):
            visited = [[False]*cols for _ in range(rows)]
            visited[r][c] =True
            queue = deque([(r,c,0)])

            while queue:
                row, col, dist = queue.popleft()
                
                total_distance[row][col] += dist 
                reach[r][c] +=1

                for dr, dc in [(1,0),(-1,0),(0,1),(0,-1)]:
                    r,c = row +dr , col+dc
                    if 0<=r<rows and 0<=c<cols and not visited[r][c] and grid[r][c]==0:
                        visited[r][c] = True
                        queue.append((r,c,dist+1))
                        
                        

        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 1:
                    bfs(r,c)

        min_distance = math.inf
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 0 and reach[r][c] == building_count:
                    min_distance = min(min_distance, total_distance[r][c])

        return min_distance if min_distance!= math.inf else -1
```

## Attempt 7 · 2023-12-03 04:41 IST · Accepted · Python3

[submission 1111110446](https://leetcode.com/submissions/detail/1111110446/) · tests 85/85 · runtime 4187 ms (beats 28.1%)

```python
class Solution:
    def shortestDistance2(self, grid: List[List[int]]) -> int:

        def bfs(r,c, totalHouses):
            queue = deque([(r,c,0)])
            visited = set({(r,c)})
            distance_total = 0
            houses_reached = 0
            while queue and houses_reached < totalHouses:
                r,c, steps  = queue.popleft()
                    #print(r,c)

                if grid[r][c] == 1:
                    houses_reached+=1
                    distance_total +=steps
                    continue

                for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in visited and grid[nr][nc] !=2:
                        visited.add((nr,nc))
                        queue.append((nr,nc, steps+1))
                
            if houses_reached != totalHouses:
                return 2**31 -1

            return distance_total

        totalHouses = sum (val==1 for row in grid for val in row)
        
        minDistance = 2**31 -1
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] ==0:
                    #print('calling',i,j)
                    minDistance = min(minDistance, bfs(i,j,totalHouses))
        
        if minDistance == 2**31 -1:
            return -1
        return minDistance


    def shortestDistance(self, grid: List[List[int]]) -> int:
        if not grid or not grid[0]:
            return -1

        rows, cols = len(grid), len(grid[0])
        total_distance = [[0]*cols for _ in range(rows)]
        reach = [[0]*cols for _ in range(rows)]
        building_count = sum(val ==1 for row in grid for val in row)

        def bfs(r,c):
            visited = [[False]*cols for _ in range(rows)]
            visited[r][c] =True
            queue = deque([(r,c,0)])

            while queue:
                row, col, dist = queue.popleft()
                total_distance[row][col] += dist 
                
                
                for dr, dc in [(1,0),(-1,0),(0,1),(0,-1)]:
                    r,c = row +dr , col+dc
                    if 0<=r<rows and 0<=c<cols and not visited[r][c] and grid[r][c]==0:
                        visited[r][c] = True
                        queue.append((r,c,dist+1))
                        reach[r][c] +=1
                        
                        

        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 1:
                    bfs(r,c)

        min_distance = math.inf
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 0 and reach[r][c] == building_count:
                    min_distance = min(min_distance, total_distance[r][c])

        return min_distance if min_distance!= math.inf else -1
```

## Attempt 8 · 2023-12-03 04:42 IST · Wrong Answer · Python3

[submission 1111110689](https://leetcode.com/submissions/detail/1111110689/) · tests 75/85

Failing input:

```text
[[1],[0]]
```

Expected:

```text
1
```

Your output:

```text
-1
```

```python
class Solution:
    def shortestDistance2(self, grid: List[List[int]]) -> int:

        def bfs(r,c, totalHouses):
            queue = deque([(r,c,0)])
            visited = set({(r,c)})
            distance_total = 0
            houses_reached = 0
            while queue and houses_reached < totalHouses:
                r,c, steps  = queue.popleft()
                    #print(r,c)

                if grid[r][c] == 1:
                    houses_reached+=1
                    distance_total +=steps
                    continue

                for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in visited and grid[nr][nc] !=2:
                        visited.add((nr,nc))
                        queue.append((nr,nc, steps+1))
                
            if houses_reached != totalHouses:
                return 2**31 -1

            return distance_total

        totalHouses = sum (val==1 for row in grid for val in row)
        
        minDistance = 2**31 -1
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] ==0:
                    #print('calling',i,j)
                    minDistance = min(minDistance, bfs(i,j,totalHouses))
        
        if minDistance == 2**31 -1:
            return -1
        return minDistance


    def shortestDistance(self, grid: List[List[int]]) -> int:
        if not grid or not grid[0]:
            return -1

        rows, cols = len(grid), len(grid[0])
        total_distance = [[0]*cols for _ in range(rows)]
        reach = [[0]*cols for _ in range(rows)]
        building_count = sum(val ==1 for row in grid for val in row)

        def bfs(r,c):
            visited = [[False]*cols for _ in range(rows)]
            visited[r][c] =True
            queue = deque([(r,c,0)])

            while queue:
                row, col, dist = queue.popleft()
                total_distance[row][col] += dist 
                reach[r][c] +=1
                
                for dr, dc in [(1,0),(-1,0),(0,1),(0,-1)]:
                    r,c = row +dr , col+dc
                    if 0<=r<rows and 0<=c<cols and not visited[r][c] and grid[r][c]==0:
                        visited[r][c] = True
                        queue.append((r,c,dist+1))
                        

        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 1:
                    bfs(r,c)

        min_distance = math.inf
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 0 and reach[r][c] == building_count:
                    min_distance = min(min_distance, total_distance[r][c])

        return min_distance if min_distance!= math.inf else -1
```

## Attempt 9 · 2023-12-03 04:43 IST · Wrong Answer · Python3

[submission 1111110993](https://leetcode.com/submissions/detail/1111110993/) · tests 75/85

Failing input:

```text
[[1],[0]]
```

Expected:

```text
1
```

Your output:

```text
-1
```

```python
class Solution:
    def shortestDistance2(self, grid: List[List[int]]) -> int:

        def bfs(r,c, totalHouses):
            queue = deque([(r,c,0)])
            visited = set({(r,c)})
            distance_total = 0
            houses_reached = 0
            while queue and houses_reached < totalHouses:
                r,c, steps  = queue.popleft()
                    #print(r,c)

                if grid[r][c] == 1:
                    houses_reached+=1
                    distance_total +=steps
                    continue

                for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in visited and grid[nr][nc] !=2:
                        visited.add((nr,nc))
                        queue.append((nr,nc, steps+1))
                
            if houses_reached != totalHouses:
                return 2**31 -1

            return distance_total

        totalHouses = sum (val==1 for row in grid for val in row)
        
        minDistance = 2**31 -1
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] ==0:
                    #print('calling',i,j)
                    minDistance = min(minDistance, bfs(i,j,totalHouses))
        
        if minDistance == 2**31 -1:
            return -1
        return minDistance


    def shortestDistance(self, grid: List[List[int]]) -> int:
        if not grid or not grid[0]:
            return -1

        rows, cols = len(grid), len(grid[0])
        total_distance = [[0]*cols for _ in range(rows)]
        reach = [[0]*cols for _ in range(rows)]
        building_count = sum(val ==1 for row in grid for val in row)

        def bfs(r,c):
            visited = [[False]*cols for _ in range(rows)]
            visited[r][c] =True
            queue = deque([(r,c,0)])

            while queue:
                row, col, dist = queue.popleft()
                total_distance[row][col] += dist 
                reach[r][c] +=1
                
                for dr, dc in [(1,0),(-1,0),(0,1),(0,-1)]:
                    r,c = row +dr , col+dc
                    if 0<=r<rows and 0<=c<cols and not visited[r][c] and grid[r][c]==0:
                        visited[r][c] = True
                        queue.append((r,c,dist+1))
                        
        
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 1:
                    bfs(r,c)
        print(reach)
        min_distance = math.inf
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 0 and reach[r][c] == building_count:
                    min_distance = min(min_distance, total_distance[r][c])

        return min_distance if min_distance!= math.inf else -1
```

## Attempt 10 · 2023-12-03 04:44 IST · Accepted · Python3

[submission 1111111381](https://leetcode.com/submissions/detail/1111111381/) · tests 85/85 · runtime 4298 ms (beats 25.0%)

```python
class Solution:
    def shortestDistance2(self, grid: List[List[int]]) -> int:

        def bfs(r,c, totalHouses):
            queue = deque([(r,c,0)])
            visited = set({(r,c)})
            distance_total = 0
            houses_reached = 0
            while queue and houses_reached < totalHouses:
                r,c, steps  = queue.popleft()
                    #print(r,c)

                if grid[r][c] == 1:
                    houses_reached+=1
                    distance_total +=steps
                    continue

                for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in visited and grid[nr][nc] !=2:
                        visited.add((nr,nc))
                        queue.append((nr,nc, steps+1))
                
            if houses_reached != totalHouses:
                return 2**31 -1

            return distance_total

        totalHouses = sum (val==1 for row in grid for val in row)
        
        minDistance = 2**31 -1
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] ==0:
                    #print('calling',i,j)
                    minDistance = min(minDistance, bfs(i,j,totalHouses))
        
        if minDistance == 2**31 -1:
            return -1
        return minDistance


    def shortestDistance(self, grid: List[List[int]]) -> int:
        if not grid or not grid[0]:
            return -1

        rows, cols = len(grid), len(grid[0])
        total_distance = [[0]*cols for _ in range(rows)]
        reach = [[0]*cols for _ in range(rows)]
        building_count = sum(val ==1 for row in grid for val in row)

        def bfs(r,c):
            visited = [[False]*cols for _ in range(rows)]
            visited[r][c] =True
            queue = deque([(r,c,0)])

            while queue:
                row, col, dist = queue.popleft()
                total_distance[row][col] += dist 
                reach[row][col] +=1
                
                for dr, dc in [(1,0),(-1,0),(0,1),(0,-1)]:
                    r,c = row +dr , col+dc
                    # print(r,c)
                    if 0<=r<rows and 0<=c<cols and not visited[r][c] and grid[r][c]==0:
                        visited[r][c] = True
                        queue.append((r,c,dist+1))
                        
        
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 1:
                    bfs(r,c)
        print(reach)
        min_distance = math.inf
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 0 and reach[r][c] == building_count:
                    min_distance = min(min_distance, total_distance[r][c])

        return min_distance if min_distance!= math.inf else -1
```

## Attempt 11 · 2023-12-03 04:44 IST · Accepted · Python3

[submission 1111111437](https://leetcode.com/submissions/detail/1111111437/) · tests 85/85 · runtime 4341 ms (beats 24.4%)

```python
class Solution:
    def shortestDistance2(self, grid: List[List[int]]) -> int:

        def bfs(r,c, totalHouses):
            queue = deque([(r,c,0)])
            visited = set({(r,c)})
            distance_total = 0
            houses_reached = 0
            while queue and houses_reached < totalHouses:
                r,c, steps  = queue.popleft()
                    #print(r,c)

                if grid[r][c] == 1:
                    houses_reached+=1
                    distance_total +=steps
                    continue

                for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in visited and grid[nr][nc] !=2:
                        visited.add((nr,nc))
                        queue.append((nr,nc, steps+1))
                
            if houses_reached != totalHouses:
                return 2**31 -1

            return distance_total

        totalHouses = sum (val==1 for row in grid for val in row)
        
        minDistance = 2**31 -1
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] ==0:
                    #print('calling',i,j)
                    minDistance = min(minDistance, bfs(i,j,totalHouses))
        
        if minDistance == 2**31 -1:
            return -1
        return minDistance


    def shortestDistance(self, grid: List[List[int]]) -> int:
        if not grid or not grid[0]:
            return -1

        rows, cols = len(grid), len(grid[0])
        total_distance = [[0]*cols for _ in range(rows)]
        reach = [[0]*cols for _ in range(rows)]
        building_count = sum(val ==1 for row in grid for val in row)

        def bfs(r,c):
            visited = [[False]*cols for _ in range(rows)]
            visited[r][c] =True
            queue = deque([(r,c,0)])

            while queue:
                row, col, dist = queue.popleft()
                total_distance[row][col] += dist 
                reach[row][col] +=1
                
                for dr, dc in [(1,0),(-1,0),(0,1),(0,-1)]:
                    r,c = row +dr , col+dc
                    # print(r,c)
                    if 0<=r<rows and 0<=c<cols and not visited[r][c] and grid[r][c]==0:
                        visited[r][c] = True
                        queue.append((r,c,dist+1))
                        
        
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 1:
                    bfs(r,c)
        # print(reach)
        min_distance = math.inf
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 0 and reach[r][c] == building_count:
                    min_distance = min(min_distance, total_distance[r][c])

        return min_distance if min_distance!= math.inf else -1
```
