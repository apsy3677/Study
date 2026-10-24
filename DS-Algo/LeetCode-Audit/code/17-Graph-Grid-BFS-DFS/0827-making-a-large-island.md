# 827. Making A Large Island

[Problem](https://leetcode.com/problems/making-a-large-island/) · Hard · Graph: Grid BFS/DFS → Label islands + merge

LeetCode tags: array, depth-first-search, breadth-first-search, union-find, matrix

Attempts since Mar 2023: 28 · accepted: 5 · failed before first AC: 3

## Attempt 1 · 2023-11-12 23:43 IST · Time Limit Exceeded · Python3

[submission 1097380291](https://leetcode.com/submissions/detail/1097380291/) · tests 70/75

Failing input:

```text
[[0,1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,1,1,0,1,0,0,1,0,1,0,1,1,0,1,1,1,0,1,0,0,0,0,1,1,0,1,1,1,0,0,0,1,1,0,1,0,0,1,1,1,0,0,1,0,1,0,1,0,1,1,1,1,1,0,0,0,1,1,0,1,0,1,1,1,1,0,0,0,1,1,1,0,1,0,1,1,0,1,1,0,0,1,0,1,1,0,1,0,0,1,1,0,0,1,1,1,1,1,0,1,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0,1,1,0,1,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,1,0,0,1,0,1,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,0,1,0,0,1,0,0,0, ... [348213 more chars]
```

Expected:

```text
737
```

```python
class Solution:
    def largestIsland(self, grid: List[List[int]]) -> int:
        N = len(grid)

        has_zero = 0
        islandSize = 0

        def check(r,c):
            stack = [(r,c)]
            seen = {(r,c)}
            while stack:
                r,c = stack.pop()
                for nr, nc in ((r-1,c), (r,c-1), (r+1,c), (r,c+1)):
                    if 0<=nr<N and 0<=nc<N and  grid[nr][nc] == 1 and (nr,nc) not in seen:
                        stack.append((nr,nc))
                        seen.add((nr,nc)) 
            return len(seen)



        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                if val ==0:
                    has_zero = True
                    grid[r][c] = 1
                    islandSize = max(islandSize, check(r,c))
                    grid[r][c] = 0

        return islandSize if has_zero else N*N
```

## Attempt 2 · 2023-11-13 00:36 IST · Runtime Error · Python3

[submission 1097406476](https://leetcode.com/submissions/detail/1097406476/) · tests 3/75

Failing input:

```text
[[0,0],[0,0]]
```

Expected:

```text
1
```

Runtime error:

```text
ValueError: max() arg is an empty sequence
    ans = max(islands.values())
Line 29 in largestIsland (Solution.py)
    ret = Solution().largestIsland(param_1)
Line 55 in _driver (Solution.py)
    _driver()
Line 66 in <module> (Solution.py)
```

```python
class Solution:
    def largestIsland(self, grid: List[List[int]]) -> int:
        N = len(grid)
       
        def neighbors(r,c):
            for nr,nc in ((r+1, c), (r, c+1), (r-1,c), (r,c-1)):
                if 0<=nr<N and 0<=nc<N:
                    yield nr, nc


        
        def dfs(r,c,index):
            ans = 1
            grid[r][c] = index
            for nr,nc in neighbors(r,c):
                if grid[nr][nc] ==1:
                    ans += dfs(nr,nc, index)
            return ans

        islands = {}
        index = 2
        # find island sizes
        for r in range(N):
            for c in range(N):
                if grid[r][c] == 1:
                    islands[index] = dfs(r,c, index) 
                    index +=1

        ans = max(islands.values())
        
        for r in range(N):
            for c in range(N):
                if grid[r][c] == 0:
                    seenIslands = {grid[nr][nc] for nr,nc in neighbors(r,c) if grid[nr][nc] > 0}
                    ans = max(ans, 1+ sum(islands[i] for i in seenIslands))
        return ans
```

## Attempt 3 · 2023-11-13 00:37 IST · Runtime Error · Python3

[submission 1097406644](https://leetcode.com/submissions/detail/1097406644/) · tests 3/75

Failing input:

```text
[[0,0],[0,0]]
```

Expected:

```text
1
```

Runtime error:

```text
ValueError: max() arg is an empty sequence
    ans = max(islands.values())
Line 29 in largestIsland (Solution.py)
    ret = Solution().largestIsland(param_1)
Line 55 in _driver (Solution.py)
    _driver()
Line 66 in <module> (Solution.py)
```

```python
class Solution:
    def largestIsland(self, grid: List[List[int]]) -> int:
        N = len(grid)
       
        def neighbors(r,c):
            for nr,nc in ((r+1, c), (r, c+1), (r-1,c), (r,c-1)):
                if 0<=nr<N and 0<=nc<N:
                    yield nr, nc


        
        def dfs(r,c,index):
            ans = 1
            grid[r][c] = index
            for nr,nc in neighbors(r,c):
                if grid[nr][nc] ==1:
                    ans += dfs(nr,nc, index)
            return ans

        islands = {}
        index = 2
        # find island sizes
        for r in range(N):
            for c in range(N):
                if grid[r][c] == 1:
                    islands[index] = dfs(r,c, index) 
                    index +=1

        ans = max(islands.values())
        
        for r in range(N):
            for c in range(N):
                if grid[r][c] == 0:
                    seenIslands = {grid[nr][nc] for nr,nc in neighbors(r,c) if grid[nr][nc] > 1}
                    ans = max(ans, 1+ sum(islands[i] for i in seenIslands))
        return ans
```

## Attempt 4 · 2023-11-13 00:37 IST · Accepted · Python3

[submission 1097406988](https://leetcode.com/submissions/detail/1097406988/) · tests 75/75 · runtime 2828 ms (beats 5.0%)

```python
class Solution:
    def largestIsland(self, grid: List[List[int]]) -> int:
        N = len(grid)
       
        def neighbors(r,c):
            for nr,nc in ((r+1, c), (r, c+1), (r-1,c), (r,c-1)):
                if 0<=nr<N and 0<=nc<N:
                    yield nr, nc


        
        def dfs(r,c,index):
            ans = 1
            grid[r][c] = index
            for nr,nc in neighbors(r,c):
                if grid[nr][nc] ==1:
                    ans += dfs(nr,nc, index)
            return ans

        islands = {}
        index = 2
        # find island sizes
        for r in range(N):
            for c in range(N):
                if grid[r][c] == 1:
                    islands[index] = dfs(r,c, index) 
                    index +=1

        ans = max(islands.values() or [0])
        
        for r in range(N):
            for c in range(N):
                if grid[r][c] == 0:
                    seenIslands = {grid[nr][nc] for nr,nc in neighbors(r,c) if grid[nr][nc] > 1}
                    ans = max(ans, 1+ sum(islands[i] for i in seenIslands))
        return ans
```

## Attempt 5 · 2023-12-30 22:22 IST · Wrong Answer · Python3

[submission 1132338413](https://leetcode.com/submissions/detail/1132338413/) · tests 37/75

Failing input:

```text
[[0,0,0,0,0,0,0],[0,1,1,1,1,0,0],[0,1,0,0,1,0,0],[1,0,1,0,1,0,0],[0,1,0,0,1,0,0],[0,1,0,0,1,0,0],[0,1,1,1,1,0,0]]
```

Expected:

```text
18
```

Your output:

```text
16
```

```python
class Solution:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()


        def area(r,c):
            count = 1
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in seen and grid[nr][nc]==1:
                    # print(nr,nc)
                    seen.add((nr,nc))

                    # within loop if you do 
                    # count = 1 + area(nr,nc)
                    # each neighbor iteration will overwrite the count
                    # you want to add counts of each neighbors
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero= True
                    seen.add((r,c))
                    ans = max(ans, area(r,c))

        return ans if has_zero else len(grid)* len(grid[0])
```

## Attempt 6 · 2023-12-30 22:24 IST · Wrong Answer · Python3

[submission 1132340043](https://leetcode.com/submissions/detail/1132340043/) · tests 37/75

Failing input:

```text
[[0,0,0,0,0,0,0],[0,1,1,1,1,0,0],[0,1,0,0,1,0,0],[1,0,1,0,1,0,0],[0,1,0,0,1,0,0],[0,1,0,0,1,0,0],[0,1,1,1,1,0,0]]
```

Expected:

```text
18
```

Your output:

```text
16
```

```python
class Solution:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()


        def area(r,c):
            count = 1
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in seen and grid[nr][nc]==1:
                    # print(nr,nc)
                    seen.add((nr,nc))

                    # within loop if you do 
                    # count = 1 + area(nr,nc)
                    # each neighbor iteration will overwrite the count
                    # you want to add counts of each neighbors
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero= True
                    seen.add((r,c))
                    grid[r][c] = 1
                    ans = max(ans, area(r,c))
                    grid[r][c] = 0

        return ans if has_zero else len(grid)* len(grid[0])
```

## Attempt 7 · 2023-12-30 22:25 IST · Time Limit Exceeded · Python3

[submission 1132340830](https://leetcode.com/submissions/detail/1132340830/) · tests 62/75

Failing input:

```text
[[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],[1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, ... [4701 more chars]
```

Expected:

```text
1276
```

```python
class Solution:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()


        def area(r,c):
            count = 1
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in seen and grid[nr][nc]==1:
                    # print(nr,nc)
                    seen.add((nr,nc))

                    # within loop if you do 
                    # count = 1 + area(nr,nc)
                    # each neighbor iteration will overwrite the count
                    # you want to add counts of each neighbors
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                seen = set()
                if grid[r][c] ==0:
                    has_zero= True
                    seen.add((r,c))
                    grid[r][c] = 1
                    ans = max(ans, area(r,c))
                    grid[r][c] = 0

        return ans if has_zero else len(grid)* len(grid[0])
```

## Attempt 8 · 2023-12-30 22:29 IST · Wrong Answer · Python3

[submission 1132342888](https://leetcode.com/submissions/detail/1132342888/) · tests 37/75

Failing input:

```text
[[0,0,0,0,0,0,0],[0,1,1,1,1,0,0],[0,1,0,0,1,0,0],[1,0,1,0,1,0,0],[0,1,0,0,1,0,0],[0,1,0,0,1,0,0],[0,1,1,1,1,0,0]]
```

Expected:

```text
18
```

Your output:

```text
16
```

```python
class Solution:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()


        def area(r,c):
            count = 1
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in seen and grid[nr][nc]==1:
                    # print(nr,nc)
                    seen.add((nr,nc))

                    # within loop if you do 
                    # count = 1 + area(nr,nc)
                    # each neighbor iteration will overwrite the count
                    # you want to add counts of each neighbors
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    seen.add((r,c))
                    ans = max(ans ,area(r,c))


        return ans if has_zero else len(grid)* len(grid[0])
```

## Attempt 9 · 2023-12-30 22:32 IST · Wrong Answer · Python3

[submission 1132345249](https://leetcode.com/submissions/detail/1132345249/) · tests 37/75

Failing input:

```text
[[0,0,0,0,0,0,0],[0,1,1,1,1,0,0],[0,1,0,0,1,0,0],[1,0,1,0,1,0,0],[0,1,0,0,1,0,0],[0,1,0,0,1,0,0],[0,1,1,1,1,0,0]]
```

Expected:

```text
18
```

Your output:

```text
16
```

```python
class Solution:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()

        
        def area(r,c):
            count = 1
            
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in seen and grid[nr][nc]==1:
                    # print(nr,nc)
                    seen.add((nr,nc))

                    # within loop if you do 
                    # count = 1 + area(nr,nc)
                    # each neighbor iteration will overwrite the count
                    # you want to add counts of each neighbors
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    ans = max(ans ,area(r,c))


        return ans if has_zero else len(grid)* len(grid[0])
```

## Attempt 10 · 2023-12-30 22:32 IST · Wrong Answer · Python3

[submission 1132345564](https://leetcode.com/submissions/detail/1132345564/) · tests 37/75

Failing input:

```text
[[0,0,0,0,0,0,0],[0,1,1,1,1,0,0],[0,1,0,0,1,0,0],[1,0,1,0,1,0,0],[0,1,0,0,1,0,0],[0,1,0,0,1,0,0],[0,1,1,1,1,0,0]]
```

Expected:

```text
18
```

Your output:

```text
16
```

```python
class Solution:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()

        
        def area(r,c):
            count = 1
            
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in seen and grid[nr][nc]==1:
                    # print(nr,nc)
                    seen.add((nr,nc))

                    # within loop if you do 
                    # count = 1 + area(nr,nc)
                    # each neighbor iteration will overwrite the count
                    # you want to add counts of each neighbors
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])
```

## Attempt 11 · 2023-12-30 22:33 IST · Wrong Answer · Python3

[submission 1132346295](https://leetcode.com/submissions/detail/1132346295/) · tests 37/75

Failing input:

```text
[[0,0,0,0,0,0,0],[0,1,1,1,1,0,0],[0,1,0,0,1,0,0],[1,0,1,0,1,0,0],[0,1,0,0,1,0,0],[0,1,0,0,1,0,0],[0,1,1,1,1,0,0]]
```

Expected:

```text
18
```

Your output:

```text
16
```

```python
class Solution:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()

        
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0
            
            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                
                    
                    # within loop if you do 
                    # count = 1 + area(nr,nc)
                    # each neighbor iteration will overwrite the count
                    # you want to add counts of each neighbors
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])
```

## Attempt 12 · 2023-12-30 22:37 IST · Time Limit Exceeded · Python3

[submission 1132348827](https://leetcode.com/submissions/detail/1132348827/) · tests 72/75

Failing input:

```text
[[0,1,0,1,1,0,1,1,1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,1,0,1,1,0,0,1,0,0,0,0,1,0,0,1,0,1,1,1,1,1,1,0,1,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0,1,1,0,1,1,0,0,0,0,0,0,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,1,1,0,1,1,0,1,0,1,0,0,1,0,0,0,0,0,1,0,1,1,1,0,0,1,1,0,1,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,0,1,1,0,0,0,0,1,1,0,0,0,1,0,1,1,0,0,1,0,0,1,0,1,1,0,0,0,0, ... [472965 more chars]
```

Expected:

```text
808
```

```python
class Solution1:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()

        
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0
            
            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])

class Solution(object):
    def largestIsland(self, grid):
        N = len(grid)

        def check(r, c):
            seen = {(r, c)}
            stack = [(r, c)]
            while stack:
                r, c = stack.pop()
                for nr, nc in ((r-1, c), (r, c-1), (r+1, c), (r, c+1)):
                    if (nr, nc) not in seen and 0 <= nr < N and 0 <= nc < N and grid[nr][nc]:
                        stack.append((nr, nc))
                        seen.add((nr, nc))
            return len(seen)

        ans = 0
        has_zero = False
        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                if val == 0:
                    has_zero = True
                    grid[r][c] = 1
                    ans = max(ans, check(r, c))
                    grid[r][c] = 0

        return ans if has_zero else N*N
```

## Attempt 13 · 2023-12-30 22:41 IST · Wrong Answer · Python3

[submission 1132351712](https://leetcode.com/submissions/detail/1132351712/) · tests 37/75

Failing input:

```text
[[0,0,0,0,0,0,0],[0,1,1,1,1,0,0],[0,1,0,0,1,0,0],[1,0,1,0,1,0,0],[0,1,0,0,1,0,0],[0,1,0,0,1,0,0],[0,1,1,1,1,0,0]]
```

Expected:

```text
18
```

Your output:

```text
16
```

```python
class Solution1:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()

        
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0
            
            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])

class Solution(object):
    def largestIsland(self, grid):
        N = len(grid)

        def check(r, c):
            seen = {(r, c)}
            stack = [(r, c)]
            while stack:
                r, c = stack.pop()
                for nr, nc in ((r-1, c), (r, c-1), (r+1, c), (r, c+1)):
                    if (nr, nc) not in seen and 0 <= nr < N and 0 <= nc < N and grid[nr][nc]:
                        stack.append((nr, nc))
                        seen.add((nr, nc))
            return len(seen)


        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0
            
            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        seen = set()
        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                if val == 0:
                    
                    has_zero = True
                    grid[r][c] = 1
                    ans = max(ans, area(r, c))
                    grid[r][c] = 0

        return ans if has_zero else N*N
```

## Attempt 14 · 2023-12-30 22:44 IST · Time Limit Exceeded · Python3

[submission 1132353241](https://leetcode.com/submissions/detail/1132353241/) · tests 62/75

Failing input:

```text
[[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],[1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, ... [4701 more chars]
```

Expected:

```text
1276
```

```python
class Solution1:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()

        
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0
            
            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])

class Solution(object):
    def largestIsland(self, grid):
        N = len(grid)

        def check(r, c):
            seen = {(r, c)}
            stack = [(r, c)]
            while stack:
                r, c = stack.pop()
                for nr, nc in ((r-1, c), (r, c-1), (r+1, c), (r, c+1)):
                    if (nr, nc) not in seen and 0 <= nr < N and 0 <= nc < N and grid[nr][nc]:
                        stack.append((nr, nc))
                        seen.add((nr, nc))
            return len(seen)


        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0
            
            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        
        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                seen = set()
                if val == 0:
                    has_zero = True
                    grid[r][c] = 1
                    ans = max(ans, area(r, c))
                    grid[r][c] = 0

        return ans if has_zero else N*N
```

## Attempt 15 · 2023-12-30 22:48 IST · Time Limit Exceeded · Python3

[submission 1132356169](https://leetcode.com/submissions/detail/1132356169/) · tests 62/75

Failing input:

```text
[[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],[1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, ... [4701 more chars]
```

Expected:

```text
1276
```

```python
class Solution1:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()

        
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0
            
            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])

class Solution(object):
    def largestIsland(self, grid):
        N = len(grid)

        def check(r, c):
            seen = {(r, c)}
            stack = [(r, c)]
            while stack:
                r, c = stack.pop()
                for nr, nc in ((r-1, c), (r, c-1), (r+1, c), (r, c+1)):
                    if (nr, nc) not in seen and 0 <= nr < N and 0 <= nc < N and grid[nr][nc]:
                        stack.append((nr, nc))
                        seen.add((nr, nc))
            return len(seen)


        def area(r,c):
            
            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if  0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in seen and grid[nr][nc]==1:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        
        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                seen = set()
                if val == 0:
                    has_zero = True
                    grid[r][c] = 1
                    ans = max(ans, area(r, c))
                    grid[r][c] = 0

        return ans if has_zero else N*N
```

## Attempt 16 · 2023-12-30 22:48 IST · Time Limit Exceeded · Python3

[submission 1132356332](https://leetcode.com/submissions/detail/1132356332/) · tests 62/75

Failing input:

```text
[[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],[1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, ... [4701 more chars]
```

Expected:

```text
1276
```

```python
class Solution1:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()

        
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0
            
            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])

class Solution(object):
    def largestIsland(self, grid):
        N = len(grid)

        def check(r, c):
            seen = {(r, c)}
            stack = [(r, c)]
            while stack:
                r, c = stack.pop()
                for nr, nc in ((r-1, c), (r, c-1), (r+1, c), (r, c+1)):
                    if (nr, nc) not in seen and 0 <= nr < N and 0 <= nc < N and grid[nr][nc]:
                        stack.append((nr, nc))
                        seen.add((nr, nc))
            return len(seen)


        def area(r,c):
            
            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if  0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in seen and grid[nr][nc]==1:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        
        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                seen = set()
                if val == 0:
                    has_zero = True
                    # grid[r][c] = 1
                    ans = max(ans, area(r, c))
                    # grid[r][c] = 0

        return ans if has_zero else N*N
```

## Attempt 17 · 2023-12-30 22:51 IST · Time Limit Exceeded · Python3

[submission 1132358230](https://leetcode.com/submissions/detail/1132358230/) · tests 63/75

Failing input:

```text
[[1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0],[1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0],[1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0],[1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0, ... [4701 more chars]
```

Expected:

```text
1276
```

```python
class Solution1:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        If you use seen/visited with dfs - you need to reset/initialize seen outside the dfs method and when you do that you need to add initial ()
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()

        
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0
            
            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])

class Solution(object):
    def largestIsland(self, grid):
        N = len(grid)

        def check(r, c):
            seen = {(r, c)}
            stack = [(r, c)]
            while stack:
                r, c = stack.pop()
                for nr, nc in ((r-1, c), (r, c-1), (r+1, c), (r, c+1)):
                    if (nr, nc) not in seen and 0 <= nr < N and 0 <= nc < N and grid[nr][nc]:
                        stack.append((nr, nc))
                        seen.add((nr, nc))
            return len(seen)


        def area(r,c):
            
            count = 1
        
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if  0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in seen and grid[nr][nc]==1:
                    seen.add((nr,nc))
                    count  += area(nr,nc)
                    
                    
            return count

        ans = 0
        has_zero = False
        
        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                seen = set({(r,c)})
                if val == 0:
                    has_zero = True
                    # grid[r][c] = 1
                    ans = max(ans, area(r, c))
                    # grid[r][c] = 0

        return ans if has_zero else N*N
```

## Attempt 18 · 2023-12-31 00:35 IST · Runtime Error · Python3

[submission 1132430006](https://leetcode.com/submissions/detail/1132430006/) · tests 0/75

Failing input:

```text
[[1,0],[0,1]]
```

Expected:

```text
3
```

Runtime error:

```text
UnboundLocalError: cannot access local variable 'nr' where it is not associated with a value
                ^^
    if not(grid[nr][nc]==1):
Line 100 in area (Solution.py)
                        ^^^^^^^^^^^^^^^^^^^^
    areas[island_num] = area(r,c,island_num)
Line 118 in largestIsland (Solution.py)
          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    ret = Solution().largestIsland(param_1)
Line 196 i ... [72 more chars]
```

```python
class Solution1:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        If you use seen/visited with dfs - you need to reset/initialize seen outside the dfs method and when you do that you need to add initial ()
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()

        
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0
            
            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])

class Solution(object):
    def largestIsland(self, grid):

        # calculate area of the island 
        # update island_num

        def neighbors(r,c):
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]):
                    yield nr,nc

        def area(r,c, island_num):
            if not(grid[nr][nc]==1):
                return 0
            
            island_area = 1

            for nr,nc in neighbors(r,c):
                grid[nr][nc] = island_num
                island_area += area(nr,nc, island_num)
            
            return island_area

        # get island areas
        island_num = 2
        areas = {}
        # max_area = 0
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==1:
                    areas[island_num] = area(r,c,island_num)
                    # print(areas[island_num])
                    # max_area = max(max_area, areas[island_num])

        max_area = max(areas.values(), default=0)

        # join nei island areas
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    # nei_islands = set()
                    nei_islands = { grid[nr][nc] for nr,nc in neighbors(r,c) if grid[nr][nc]>1}

                    # add areas 
                    max_area =  max(max_area, 1 + sum(areas[i] for i in nei_islands))

        return max_area

                    


        




    def largestIsland3(self, grid):
        N = len(grid)

        def check(r, c):
            seen = {(r, c)}
            stack = [(r, c)]
            while stack:
                r, c = stack.pop()
                for nr, nc in ((r-1, c), (r, c-1), (r+1, c), (r, c+1)):
                    if (nr, nc) not in seen and 0 <= nr < N and 0 <= nc < N and grid[nr][nc]:
                        stack.append((nr, nc))
                        seen.add((nr, nc))
            return len(seen)


        def area(r,c):
            count = 1
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if  0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in seen and grid[nr][nc]==1:
                    seen.add((nr,nc))
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                seen = set({(r,c)})
                if val == 0:
                    has_zero = True
                    ans = max(ans, area(r, c))

        return ans if has_zero else N*N
```

## Attempt 19 · 2023-12-31 00:39 IST · Accepted · Python3

[submission 1132432728](https://leetcode.com/submissions/detail/1132432728/) · tests 75/75 · runtime 4595 ms (beats 5.0%)

```python
class Solution1:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        If you use seen/visited with dfs - you need to reset/initialize seen outside the dfs method and when you do that you need to add initial ()
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()

        
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0
            
            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])

class Solution(object):
    def largestIsland(self, grid):

        # calculate area of the island 
        # update island_num

        def neighbors(r,c):
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]):
                    yield nr,nc

        def area(r,c, island_num):
            if not (0 <= r < len(grid) and 0 <= c < len(grid[0]) and grid[r][c] == 1):
                return 0
            
            grid[r][c] = island_num
            island_area = 1

            for nr,nc in neighbors(r,c):
                island_area += area(nr,nc, island_num)
            
            return island_area

        # get island areas
        island_num = 2
        areas = {}
        # max_area = 0
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==1:
                    areas[island_num] = area(r,c,island_num)
                    island_num+=1
                    # print(areas[island_num])
                    # max_area = max(max_area, areas[island_num])

        max_area = max(areas.values(), default=0)

        # join nei island areas
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    # nei_islands = set()
                    nei_islands = { grid[nr][nc] for nr,nc in neighbors(r,c) if grid[nr][nc]>1}

                    # add areas 
                    max_area =  max(max_area, 1 + sum(areas[i] for i in nei_islands))

        return max_area

                    


        




    def largestIsland3(self, grid):
        N = len(grid)

        def check(r, c):
            seen = {(r, c)}
            stack = [(r, c)]
            while stack:
                r, c = stack.pop()
                for nr, nc in ((r-1, c), (r, c-1), (r+1, c), (r, c+1)):
                    if (nr, nc) not in seen and 0 <= nr < N and 0 <= nc < N and grid[nr][nc]:
                        stack.append((nr, nc))
                        seen.add((nr, nc))
            return len(seen)


        def area(r,c):
            count = 1
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if  0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in seen and grid[nr][nc]==1:
                    seen.add((nr,nc))
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                seen = set({(r,c)})
                if val == 0:
                    has_zero = True
                    ans = max(ans, area(r, c))

        return ans if has_zero else N*N
```

## Attempt 20 · 2024-01-05 10:58 IST · Time Limit Exceeded · Python3

[submission 1137313177](https://leetcode.com/submissions/detail/1137313177/) · tests 70/75

Failing input:

```text
[[0,1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,1,1,0,1,0,0,1,0,1,0,1,1,0,1,1,1,0,1,0,0,0,0,1,1,0,1,1,1,0,0,0,1,1,0,1,0,0,1,1,1,0,0,1,0,1,0,1,0,1,1,1,1,1,0,0,0,1,1,0,1,0,1,1,1,1,0,0,0,1,1,1,0,1,0,1,1,0,1,1,0,0,1,0,1,1,0,1,0,0,1,1,0,0,1,1,1,1,1,0,1,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0,1,1,0,1,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,1,0,0,1,0,1,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,0,1,0,0,1,0,0,0, ... [348213 more chars]
```

Expected:

```text
737
```

```python
class Solution1:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        If you use seen/visited with dfs - you need to reset/initialize seen outside the dfs method and when you do that you need to add initial ()
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()

        
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0
            
            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])

class Solution(object):
    def largestIsland(self, grid):

        # calculate area of the island 
        # update island_num

        def neighbors(r,c):
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]):
                    yield nr,nc

        def area(r,c, island_num):
            if not (0 <= r < len(grid) and 0 <= c < len(grid[0]) and grid[r][c] == 1):
                return 0
            
            grid[r][c] = island_num
            island_area = 1

            for nr,nc in neighbors(r,c):
                island_area += area(nr,nc, island_num)
            
            return island_area

        # get island areas
        island_num = 2
        areas = {}
        # max_area = 0
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==1:
                    areas[island_num] = area(r,c,island_num)
                    island_num+=1
                    # print(areas[island_num])
                    # max_area = max(max_area, areas[island_num])

        max_area = max(areas.values(), default=0)

        # join nei island areas
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    # nei_islands = set()
                    nei_islands = { grid[nr][nc] for nr,nc in neighbors(r,c) if grid[nr][nc]>1}

                    # add areas 
                    max_area =  max(max_area, 1 + sum(areas[i] for i in nei_islands))

        return max_area

                    


        




    def largestIsland3(self, grid):
        N = len(grid)

        def check(r, c):
            seen = {(r, c)}
            stack = [(r, c)]
            while stack:
                r, c = stack.pop()
                for nr, nc in ((r-1, c), (r, c-1), (r+1, c), (r, c+1)):
                    if (nr, nc) not in seen and 0 <= nr < N and 0 <= nc < N and grid[nr][nc]:
                        stack.append((nr, nc))
                        seen.add((nr, nc))
            return len(seen)


        def area(r,c):
            count = 1
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if  0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in seen and grid[nr][nc]==1:
                    seen.add((nr,nc))
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                seen = set({(r,c)})
                if val == 0:
                    has_zero = True
                    ans = max(ans, area(r, c))

        return ans if has_zero else N*N

    def largestIsland(self, grid):
        def get_area(r,c):
            if (r,c) in visited:
                return 0

            visited.add((r,c))

            area = 1

            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc]==1:
                    area += get_area(nr,nc)

            return area

        max_area = 0
        has_zero = False
        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                if grid[r][c]==0:
                    has_zero = True
                    visited = set()
                    max_area = max(max_area, get_area(r,c))
        return max_area if has_zero else len(grid)*len(grid[0])
```

## Attempt 21 · 2024-01-13 23:18 IST · Accepted · Python3

[submission 1145240930](https://leetcode.com/submissions/detail/1145240930/) · tests 75/75 · runtime 2870 ms (beats 5.0%)

```python
class Solution1:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        If you use seen/visited with dfs - you need to reset/initialize seen outside the dfs method and when you do that you need to add initial ()
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()

        
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0
            
            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])

class Solution(object):
    def largestIsland(self, grid):

        # calculate area of the island 
        # update island_num

        def neighbors(r,c):
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]):
                    yield nr,nc

        def area(r,c, island_num):
            if not (0 <= r < len(grid) and 0 <= c < len(grid[0]) and grid[r][c] == 1):
                return 0
            
            grid[r][c] = island_num
            island_area = 1

            for nr,nc in neighbors(r,c):
                island_area += area(nr,nc, island_num)
            
            return island_area

        # get island areas
        island_num = 2
        areas = {}
        # max_area = 0
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==1:
                    areas[island_num] = area(r,c,island_num)
                    island_num+=1
                    # print(areas[island_num])
                    # max_area = max(max_area, areas[island_num])

        max_area = max(areas.values(), default=0)

        # join nei island areas
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    # nei_islands = set()
                    nei_islands = { grid[nr][nc] for nr,nc in neighbors(r,c) if grid[nr][nc]>1}

                    # add areas 
                    max_area =  max(max_area, 1 + sum(areas[i] for i in nei_islands))

        return max_area

                    


        




    def largestIsland3(self, grid):
        N = len(grid)

        def check(r, c):
            seen = {(r, c)}
            stack = [(r, c)]
            while stack:
                r, c = stack.pop()
                for nr, nc in ((r-1, c), (r, c-1), (r+1, c), (r, c+1)):
                    if (nr, nc) not in seen and 0 <= nr < N and 0 <= nc < N and grid[nr][nc]:
                        stack.append((nr, nc))
                        seen.add((nr, nc))
            return len(seen)


        def area(r,c):
            count = 1
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if  0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in seen and grid[nr][nc]==1:
                    seen.add((nr,nc))
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                seen = set({(r,c)})
                if val == 0:
                    has_zero = True
                    ans = max(ans, area(r, c))

        return ans if has_zero else N*N

    def largestIsland(self, grid):
        # dfs call to get area for a cell
        def get_area(r,c):
            # 1. check if visited or any other condition which makes it invalid cell
            if (r,c) in visited:
                return 0
            
            # 2. set to visited and process
            visited.add((r,c))

            #3. default value
            # should be 1 that is the value for a cell
            area = 1

            #3. for each choice- neighbors
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]:

                #4. if valid move
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc]==1:
                    #4. add area for all neighbors
                    area += get_area(nr,nc)

            return area


        max_area = 0
        has_zero = False

        # for each cell 
        for r, row in enumerate(grid):
            for c, val in enumerate(row):

                # if it can be visited 
                if grid[r][c]==0:

                    # if you go any zero or else all 1 
                    has_zero = True

                    # visited for each traversal from this cell
                    visited = set()
                    max_area = max(max_area, get_area(r,c))
        return max_area if has_zero else len(grid)*len(grid[0])

    
    def largestIsland(self, grid: List[List[int]]) -> int:

        island_areas = {} # islandnum:area
        visited=set()
        # save area for each islands
        island_num = 2
        neighbors = lambda r, c: [(r,c+1),(r+1,c),(r-1,c),(r,c-1)]
        N = len(grid)
        def get_area(r,c, island_num):
            # if (r,c) in visited:
            #     return 0
            
            # visited.add((r,c))
            grid[r][c] = island_num
            area = 1

            for nr,nc in neighbors(r,c):
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc] == 1:
                    area += get_area(nr,nc, island_num)
            
            return area

        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] == 1:# and (r,c) not in visited:
                    island_areas[island_num] = get_area(r,c, island_num)
                    island_num +=1

        # for each zero add neigbor areas
        max_area = -1
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    neighbor_islands = { grid[nr][nc] for nr,nc in neighbors(r,c) if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc] >1}
                    print(neighbor_islands)
                    max_area = max(max_area, 1+ sum(island_areas[neighbor_island] for neighbor_island in neighbor_islands))
        
        return N*N if max_area<0 else max_area
```

## Attempt 22 · 2024-02-05 02:19 IST · Wrong Answer · Python3

[submission 1166193482](https://leetcode.com/submissions/detail/1166193482/) · tests 37/75

Failing input:

```text
[[0,0,0,0,0,0,0],[0,1,1,1,1,0,0],[0,1,0,0,1,0,0],[1,0,1,0,1,0,0],[0,1,0,0,1,0,0],[0,1,0,0,1,0,0],[0,1,1,1,1,0,0]]
```

Expected:

```text
18
```

Your output:

```text
16
```

```python
class Solution1:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        If you use seen/visited with dfs - you need to reset/initialize seen outside the dfs method and when you do that you need to add initial ()
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()
  
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0  

            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])

class Solution(object):
    def largestIsland(self, grid):

        # calculate area of the island 
        # update island_num

        def neighbors(r,c):
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]):
                    yield nr,nc

        def area(r,c, island_num):
            if not (0 <= r < len(grid) and 0 <= c < len(grid[0]) and grid[r][c] == 1):
                return 0
            
            grid[r][c] = island_num
            island_area = 1

            for nr,nc in neighbors(r,c):
                island_area += area(nr,nc, island_num)
            
            return island_area

        # get island areas
        island_num = 2
        areas = {}
        # max_area = 0
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==1:
                    areas[island_num] = area(r,c,island_num)
                    island_num+=1
                    # print(areas[island_num])
                    # max_area = max(max_area, areas[island_num])

        max_area = max(areas.values(), default=0)

        # join nei island areas
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    # nei_islands = set()
                    nei_islands = { grid[nr][nc] for nr,nc in neighbors(r,c) if grid[nr][nc]>1}

                    # add areas 
                    max_area =  max(max_area, 1 + sum(areas[i] for i in nei_islands))

        return max_area

                    


        




    def largestIsland3(self, grid):
        N = len(grid)

        def check(r, c):
            seen = {(r, c)}
            stack = [(r, c)]
            while stack:
                r, c = stack.pop()
                for nr, nc in ((r-1, c), (r, c-1), (r+1, c), (r, c+1)):
                    if (nr, nc) not in seen and 0 <= nr < N and 0 <= nc < N and grid[nr][nc]:
                        stack.append((nr, nc))
                        seen.add((nr, nc))
            return len(seen)


        def area(r,c):
            count = 1
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if  0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in seen and grid[nr][nc]==1:
                    seen.add((nr,nc))
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                seen = set({(r,c)})
                if val == 0:
                    has_zero = True
                    ans = max(ans, area(r, c))

        return ans if has_zero else N*N

    def largestIsland(self, grid):
        # dfs call to get area for a cell
        def get_area(r,c):
            # 1. check if visited or any other condition which makes it invalid cell
            if (r,c) in visited:
                return 0
            
            # 2. set to visited and process
            visited.add((r,c))

            #3. default value
            # should be 1 that is the value for a cell
            area = 1

            #3. for each choice- neighbors
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]:

                #4. if valid move
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc]==1:
                    #4. add area for all neighbors
                    area += get_area(nr,nc)

            return area


        max_area = 0
        has_zero = False

        # for each cell 
        for r, row in enumerate(grid):
            for c, val in enumerate(row):

                # if it can be visited 
                if grid[r][c]==0:

                    # if you go any zero or else all 1 
                    has_zero = True

                    # visited for each traversal from this cell
                    visited = set()
                    max_area = max(max_area, get_area(r,c))
        return max_area if has_zero else len(grid)*len(grid[0])

    
    def largestIsland(self, grid: List[List[int]]) -> int:

        island_areas = {} # islandnum:area
        # save area for each islands
        island_num = 2
        neighbors = lambda r, c: [(r,c+1),(r+1,c),(r-1,c),(r,c-1)]
        N = len(grid)
        def get_area(r,c, island_num):
            grid[r][c] = island_num
            area = 1
            for nr,nc in neighbors(r,c):
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc] == 1:
                    area += get_area(nr,nc, island_num)
            
            return area

        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] == 1:# and (r,c) not in visited:
                    island_areas[island_num] = get_area(r,c, island_num)
                    island_num +=1

        # for each zero add neigbor areas
        max_area = -1
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    neighbor_islands = { grid[nr][nc] for nr,nc in neighbors(r,c) if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc] >1}
                    print(neighbor_islands)
                    max_area = max(max_area, 1+ sum(island_areas[neighbor_island] for neighbor_island in neighbor_islands))
        
        return N*N if max_area<0 else max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()
  
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0  
                   
            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])
```

## Attempt 23 · 2024-02-05 02:20 IST · Wrong Answer · Python3

[submission 1166193965](https://leetcode.com/submissions/detail/1166193965/) · tests 37/75

Failing input:

```text
[[0,0,0,0,0,0,0],[0,1,1,1,1,0,0],[0,1,0,0,1,0,0],[1,0,1,0,1,0,0],[0,1,0,0,1,0,0],[0,1,0,0,1,0,0],[0,1,1,1,1,0,0]]
```

Expected:

```text
18
```

Your output:

```text
16
```

```python
class Solution1:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        If you use seen/visited with dfs - you need to reset/initialize seen outside the dfs method and when you do that you need to add initial ()
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()
  
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0  

            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])

class Solution(object):
    def largestIsland(self, grid):

        # calculate area of the island 
        # update island_num

        def neighbors(r,c):
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]):
                    yield nr,nc

        def area(r,c, island_num):
            if not (0 <= r < len(grid) and 0 <= c < len(grid[0]) and grid[r][c] == 1):
                return 0
            
            grid[r][c] = island_num
            island_area = 1

            for nr,nc in neighbors(r,c):
                island_area += area(nr,nc, island_num)
            
            return island_area

        # get island areas
        island_num = 2
        areas = {}
        # max_area = 0
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==1:
                    areas[island_num] = area(r,c,island_num)
                    island_num+=1
                    # print(areas[island_num])
                    # max_area = max(max_area, areas[island_num])

        max_area = max(areas.values(), default=0)

        # join nei island areas
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    # nei_islands = set()
                    nei_islands = { grid[nr][nc] for nr,nc in neighbors(r,c) if grid[nr][nc]>1}

                    # add areas 
                    max_area =  max(max_area, 1 + sum(areas[i] for i in nei_islands))

        return max_area

                    


        




    def largestIsland3(self, grid):
        N = len(grid)

        def check(r, c):
            seen = {(r, c)}
            stack = [(r, c)]
            while stack:
                r, c = stack.pop()
                for nr, nc in ((r-1, c), (r, c-1), (r+1, c), (r, c+1)):
                    if (nr, nc) not in seen and 0 <= nr < N and 0 <= nc < N and grid[nr][nc]:
                        stack.append((nr, nc))
                        seen.add((nr, nc))
            return len(seen)


        def area(r,c):
            count = 1
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if  0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in seen and grid[nr][nc]==1:
                    seen.add((nr,nc))
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                seen = set({(r,c)})
                if val == 0:
                    has_zero = True
                    ans = max(ans, area(r, c))

        return ans if has_zero else N*N

    def largestIsland(self, grid):
        # dfs call to get area for a cell
        def get_area(r,c):
            # 1. check if visited or any other condition which makes it invalid cell
            if (r,c) in visited:
                return 0
            
            # 2. set to visited and process
            visited.add((r,c))

            #3. default value
            # should be 1 that is the value for a cell
            area = 1

            #3. for each choice- neighbors
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]:

                #4. if valid move
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc]==1:
                    #4. add area for all neighbors
                    area += get_area(nr,nc)

            return area


        max_area = 0
        has_zero = False

        # for each cell 
        for r, row in enumerate(grid):
            for c, val in enumerate(row):

                # if it can be visited 
                if grid[r][c]==0:

                    # if you go any zero or else all 1 
                    has_zero = True

                    # visited for each traversal from this cell
                    visited = set()
                    max_area = max(max_area, get_area(r,c))
        return max_area if has_zero else len(grid)*len(grid[0])

    
    def largestIsland(self, grid: List[List[int]]) -> int:

        island_areas = {} # islandnum:area
        # save area for each islands
        island_num = 2
        neighbors = lambda r, c: [(r,c+1),(r+1,c),(r-1,c),(r,c-1)]
        N = len(grid)
        def get_area(r,c, island_num):
            grid[r][c] = island_num
            area = 1
            for nr,nc in neighbors(r,c):
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc] == 1:
                    area += get_area(nr,nc, island_num)
            
            return area

        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] == 1:# and (r,c) not in visited:
                    island_areas[island_num] = get_area(r,c, island_num)
                    island_num +=1

        # for each zero add neigbor areas
        max_area = -1
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    neighbor_islands = { grid[nr][nc] for nr,nc in neighbors(r,c) if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc] >1}
                    print(neighbor_islands)
                    max_area = max(max_area, 1+ sum(island_areas[neighbor_island] for neighbor_island in neighbor_islands))
        
        return N*N if max_area<0 else max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()
  
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0  

            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])
```

## Attempt 24 · 2024-02-05 02:22 IST · Time Limit Exceeded · Python3

[submission 1166194969](https://leetcode.com/submissions/detail/1166194969/) · tests 70/75

Failing input:

```text
[[0,1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,1,1,0,1,0,0,1,0,1,0,1,1,0,1,1,1,0,1,0,0,0,0,1,1,0,1,1,1,0,0,0,1,1,0,1,0,0,1,1,1,0,0,1,0,1,0,1,0,1,1,1,1,1,0,0,0,1,1,0,1,0,1,1,1,1,0,0,0,1,1,1,0,1,0,1,1,0,1,1,0,0,1,0,1,1,0,1,0,0,1,1,0,0,1,1,1,1,1,0,1,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0,1,1,0,1,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,1,0,0,1,0,1,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,0,1,0,0,1,0,0,0, ... [348213 more chars]
```

Expected:

```text
737
```

```python
class Solution1:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        If you use seen/visited with dfs - you need to reset/initialize seen outside the dfs method and when you do that you need to add initial ()
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()
  
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0  

            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])

class Solution(object):
    def largestIsland(self, grid):

        # calculate area of the island 
        # update island_num

        def neighbors(r,c):
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]):
                    yield nr,nc

        def area(r,c, island_num):
            if not (0 <= r < len(grid) and 0 <= c < len(grid[0]) and grid[r][c] == 1):
                return 0
            
            grid[r][c] = island_num
            island_area = 1

            for nr,nc in neighbors(r,c):
                island_area += area(nr,nc, island_num)
            
            return island_area

        # get island areas
        island_num = 2
        areas = {}
        # max_area = 0
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==1:
                    areas[island_num] = area(r,c,island_num)
                    island_num+=1
                    # print(areas[island_num])
                    # max_area = max(max_area, areas[island_num])

        max_area = max(areas.values(), default=0)

        # join nei island areas
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    # nei_islands = set()
                    nei_islands = { grid[nr][nc] for nr,nc in neighbors(r,c) if grid[nr][nc]>1}

                    # add areas 
                    max_area =  max(max_area, 1 + sum(areas[i] for i in nei_islands))

        return max_area

                    


        




    def largestIsland3(self, grid):
        N = len(grid)

        def check(r, c):
            seen = {(r, c)}
            stack = [(r, c)]
            while stack:
                r, c = stack.pop()
                for nr, nc in ((r-1, c), (r, c-1), (r+1, c), (r, c+1)):
                    if (nr, nc) not in seen and 0 <= nr < N and 0 <= nc < N and grid[nr][nc]:
                        stack.append((nr, nc))
                        seen.add((nr, nc))
            return len(seen)


        def area(r,c):
            count = 1
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if  0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in seen and grid[nr][nc]==1:
                    seen.add((nr,nc))
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                seen = set({(r,c)})
                if val == 0:
                    has_zero = True
                    ans = max(ans, area(r, c))

        return ans if has_zero else N*N

    def largestIsland(self, grid):
        # dfs call to get area for a cell
        def get_area(r,c):
            # 1. check if visited or any other condition which makes it invalid cell
            if (r,c) in visited:
                return 0
            
            # 2. set to visited and process
            visited.add((r,c))

            #3. default value
            # should be 1 that is the value for a cell
            area = 1

            #3. for each choice- neighbors
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]:

                #4. if valid move
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc]==1:
                    #4. add area for all neighbors
                    area += get_area(nr,nc)

            return area


        max_area = 0
        has_zero = False

        # for each cell 
        for r, row in enumerate(grid):
            for c, val in enumerate(row):

                # if it can be visited 
                if grid[r][c]==0:

                    # if you go any zero or else all 1 
                    has_zero = True

                    # visited for each traversal from this cell
                    visited = set()
                    max_area = max(max_area, get_area(r,c))
        return max_area if has_zero else len(grid)*len(grid[0])

    
    def largestIsland(self, grid: List[List[int]]) -> int:

        island_areas = {} # islandnum:area
        # save area for each islands
        island_num = 2
        neighbors = lambda r, c: [(r,c+1),(r+1,c),(r-1,c),(r,c-1)]
        N = len(grid)
        def get_area(r,c, island_num):
            grid[r][c] = island_num
            area = 1
            for nr,nc in neighbors(r,c):
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc] == 1:
                    area += get_area(nr,nc, island_num)
            
            return area

        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] == 1:# and (r,c) not in visited:
                    island_areas[island_num] = get_area(r,c, island_num)
                    island_num +=1

        # for each zero add neigbor areas
        max_area = -1
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    neighbor_islands = { grid[nr][nc] for nr,nc in neighbors(r,c) if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc] >1}
                    print(neighbor_islands)
                    max_area = max(max_area, 1+ sum(island_areas[neighbor_island] for neighbor_island in neighbor_islands))
        
        return N*N if max_area<0 else max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()
  
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0  

            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    seen.clear()
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])
```

## Attempt 25 · 2024-02-05 02:23 IST · Time Limit Exceeded · Python3

[submission 1166195328](https://leetcode.com/submissions/detail/1166195328/) · tests 72/75

Failing input:

```text
[[0,1,0,1,1,0,1,1,1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,1,0,1,1,0,0,1,0,0,0,0,1,0,0,1,0,1,1,1,1,1,1,0,1,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0,1,1,0,1,1,0,0,0,0,0,0,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,1,1,0,1,1,0,1,0,1,0,0,1,0,0,0,0,0,1,0,1,1,1,0,0,1,1,0,1,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,0,1,1,0,0,0,0,1,1,0,0,0,1,0,1,1,0,0,1,0,0,1,0,1,1,0,0,0,0, ... [472965 more chars]
```

Expected:

```text
808
```

```python
class Solution1:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        If you use seen/visited with dfs - you need to reset/initialize seen outside the dfs method and when you do that you need to add initial ()
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()
  
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0  

            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])

class Solution(object):
    def largestIsland(self, grid):

        # calculate area of the island 
        # update island_num

        def neighbors(r,c):
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]):
                    yield nr,nc

        def area(r,c, island_num):
            if not (0 <= r < len(grid) and 0 <= c < len(grid[0]) and grid[r][c] == 1):
                return 0
            
            grid[r][c] = island_num
            island_area = 1

            for nr,nc in neighbors(r,c):
                island_area += area(nr,nc, island_num)
            
            return island_area

        # get island areas
        island_num = 2
        areas = {}
        # max_area = 0
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==1:
                    areas[island_num] = area(r,c,island_num)
                    island_num+=1
                    # print(areas[island_num])
                    # max_area = max(max_area, areas[island_num])

        max_area = max(areas.values(), default=0)

        # join nei island areas
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    # nei_islands = set()
                    nei_islands = { grid[nr][nc] for nr,nc in neighbors(r,c) if grid[nr][nc]>1}

                    # add areas 
                    max_area =  max(max_area, 1 + sum(areas[i] for i in nei_islands))

        return max_area

                    


        




    def largestIsland3(self, grid):
        N = len(grid)

        def check(r, c):
            seen = {(r, c)}
            stack = [(r, c)]
            while stack:
                r, c = stack.pop()
                for nr, nc in ((r-1, c), (r, c-1), (r+1, c), (r, c+1)):
                    if (nr, nc) not in seen and 0 <= nr < N and 0 <= nc < N and grid[nr][nc]:
                        stack.append((nr, nc))
                        seen.add((nr, nc))
            return len(seen)


        def area(r,c):
            count = 1
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if  0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in seen and grid[nr][nc]==1:
                    seen.add((nr,nc))
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                seen = set({(r,c)})
                if val == 0:
                    has_zero = True
                    ans = max(ans, area(r, c))

        return ans if has_zero else N*N

    def largestIsland(self, grid):
        # dfs call to get area for a cell
        def get_area(r,c):
            # 1. check if visited or any other condition which makes it invalid cell
            if (r,c) in visited:
                return 0
            
            # 2. set to visited and process
            visited.add((r,c))

            #3. default value
            # should be 1 that is the value for a cell
            area = 1

            #3. for each choice- neighbors
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]:

                #4. if valid move
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc]==1:
                    #4. add area for all neighbors
                    area += get_area(nr,nc)

            return area


        max_area = 0
        has_zero = False

        # for each cell 
        for r, row in enumerate(grid):
            for c, val in enumerate(row):

                # if it can be visited 
                if grid[r][c]==0:

                    # if you go any zero or else all 1 
                    has_zero = True

                    # visited for each traversal from this cell
                    visited = set()
                    max_area = max(max_area, get_area(r,c))
        return max_area if has_zero else len(grid)*len(grid[0])

    
    def largestIsland(self, grid: List[List[int]]) -> int:

        island_areas = {} # islandnum:area
        # save area for each islands
        island_num = 2
        neighbors = lambda r, c: [(r,c+1),(r+1,c),(r-1,c),(r,c-1)]
        N = len(grid)
        def get_area(r,c, island_num):
            grid[r][c] = island_num
            area = 1
            for nr,nc in neighbors(r,c):
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc] == 1:
                    area += get_area(nr,nc, island_num)
            
            return area

        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] == 1:# and (r,c) not in visited:
                    island_areas[island_num] = get_area(r,c, island_num)
                    island_num +=1

        # for each zero add neigbor areas
        max_area = -1
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    neighbor_islands = { grid[nr][nc] for nr,nc in neighbors(r,c) if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc] >1}
                    print(neighbor_islands)
                    max_area = max(max_area, 1+ sum(island_areas[neighbor_island] for neighbor_island in neighbor_islands))
        
        return N*N if max_area<0 else max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()
  
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0  

            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    seen.clear()
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])

class Solution(object):
    def largestIsland(self, grid):
        N = len(grid)

        def check(r, c):
            seen = {(r, c)}
            stack = [(r, c)]
            while stack:
                r, c = stack.pop()
                for nr, nc in ((r-1, c), (r, c-1), (r+1, c), (r, c+1)):
                    if (nr, nc) not in seen and 0 <= nr < N and 0 <= nc < N and grid[nr][nc]:
                        stack.append((nr, nc))
                        seen.add((nr, nc))
            return len(seen)

        ans = 0
        has_zero = False
        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                if val == 0:
                    has_zero = True
                    grid[r][c] = 1
                    ans = max(ans, check(r, c))
                    grid[r][c] = 0

        return ans if has_zero else N*N
```

## Attempt 26 · 2024-02-05 02:34 IST · Time Limit Exceeded · Python3

[submission 1166202010](https://leetcode.com/submissions/detail/1166202010/) · tests 70/75

Failing input:

```text
[[0,1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,1,1,0,1,0,0,1,0,1,0,1,1,0,1,1,1,0,1,0,0,0,0,1,1,0,1,1,1,0,0,0,1,1,0,1,0,0,1,1,1,0,0,1,0,1,0,1,0,1,1,1,1,1,0,0,0,1,1,0,1,0,1,1,1,1,0,0,0,1,1,1,0,1,0,1,1,0,1,1,0,0,1,0,1,1,0,1,0,0,1,1,0,0,1,1,1,1,1,0,1,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0,1,1,0,1,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,1,0,0,1,0,1,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,0,1,0,0,1,0,0,0, ... [348213 more chars]
```

Expected:

```text
737
```

```python
class Solution1:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        If you use seen/visited with dfs - you need to reset/initialize seen outside the dfs method and when you do that you need to add initial ()
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()
  
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0  

            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])

class Solution(object):
    def largestIsland(self, grid):

        # calculate area of the island 
        # update island_num

        def neighbors(r,c):
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]):
                    yield nr,nc

        def area(r,c, island_num):
            if not (0 <= r < len(grid) and 0 <= c < len(grid[0]) and grid[r][c] == 1):
                return 0
            
            grid[r][c] = island_num
            island_area = 1

            for nr,nc in neighbors(r,c):
                island_area += area(nr,nc, island_num)
            
            return island_area

        # get island areas
        island_num = 2
        areas = {}
        # max_area = 0
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==1:
                    areas[island_num] = area(r,c,island_num)
                    island_num+=1
                    # print(areas[island_num])
                    # max_area = max(max_area, areas[island_num])

        max_area = max(areas.values(), default=0)

        # join nei island areas
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    # nei_islands = set()
                    nei_islands = { grid[nr][nc] for nr,nc in neighbors(r,c) if grid[nr][nc]>1}

                    # add areas 
                    max_area =  max(max_area, 1 + sum(areas[i] for i in nei_islands))

        return max_area

                    


        




    def largestIsland3(self, grid):
        N = len(grid)

        def check(r, c):
            seen = {(r, c)}
            stack = [(r, c)]
            while stack:
                r, c = stack.pop()
                for nr, nc in ((r-1, c), (r, c-1), (r+1, c), (r, c+1)):
                    if (nr, nc) not in seen and 0 <= nr < N and 0 <= nc < N and grid[nr][nc]:
                        stack.append((nr, nc))
                        seen.add((nr, nc))
            return len(seen)


        def area(r,c):
            count = 1
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if  0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in seen and grid[nr][nc]==1:
                    seen.add((nr,nc))
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                seen = set({(r,c)})
                if val == 0:
                    has_zero = True
                    ans = max(ans, area(r, c))

        return ans if has_zero else N*N

    def largestIsland(self, grid):
        # dfs call to get area for a cell
        def get_area(r,c):
            # 1. check if visited or any other condition which makes it invalid cell
            if (r,c) in visited:
                return 0
            
            # 2. set to visited and process
            visited.add((r,c))

            #3. default value
            # should be 1 that is the value for a cell
            area = 1

            #3. for each choice- neighbors
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]:

                #4. if valid move
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc]==1:
                    #4. add area for all neighbors
                    area += get_area(nr,nc)

            return area


        max_area = 0
        has_zero = False

        # for each cell 
        for r, row in enumerate(grid):
            for c, val in enumerate(row):

                # if it can be visited 
                if grid[r][c]==0:

                    # if you go any zero or else all 1 
                    has_zero = True

                    # visited for each traversal from this cell
                    visited = set()
                    max_area = max(max_area, get_area(r,c))
        return max_area if has_zero else len(grid)*len(grid[0])

    
    def largestIsland(self, grid: List[List[int]]) -> int:

        island_areas = {} # islandnum:area
        # save area for each islands
        island_num = 2
        neighbors = lambda r, c: [(r,c+1),(r+1,c),(r-1,c),(r,c-1)]
        N = len(grid)
        def get_area(r,c, island_num):
            grid[r][c] = island_num
            area = 1
            for nr,nc in neighbors(r,c):
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc] == 1:
                    area += get_area(nr,nc, island_num)
            
            return area

        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] == 1:# and (r,c) not in visited:
                    island_areas[island_num] = get_area(r,c, island_num)
                    island_num +=1

        # for each zero add neigbor areas
        max_area = -1
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    neighbor_islands = { grid[nr][nc] for nr,nc in neighbors(r,c) if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc] >1}
                    print(neighbor_islands)
                    max_area = max(max_area, 1+ sum(island_areas[neighbor_island] for neighbor_island in neighbor_islands))
        
        return N*N if max_area<0 else max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()
  
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0  

            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    seen.clear()
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])
    
    def largestIsland(self, grid: List[List[int]]) -> int:
        max_area = 0
        found_zero = False
        visited = set()
        def get_area(r,c):
            if (r,c) in visited:
                return 0
            
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0

            visited.add((r,c))
            area = 1
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                area+= get_area(nr,nc)
            
            return area

        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] == 0:
                    visited.clear()
                    found_zero = True
                    grid[r][c] = 1
                    max_area = max(max_area, get_area(r,c))
                    grid[r][c]= 0

        return max_area if found_zero else len(grid) * len(grid[0])
```

## Attempt 27 · 2024-02-05 04:36 IST · Accepted · Python3

[submission 1166264777](https://leetcode.com/submissions/detail/1166264777/) · tests 75/75 · runtime 2842 ms (beats 5.0%)

```python
class Solution1:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        If you use seen/visited with dfs - you need to reset/initialize seen outside the dfs method and when you do that you need to add initial ()
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()
  
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0  

            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])

class Solution(object):
    def largestIsland(self, grid):

        # calculate area of the island 
        # update island_num

        def neighbors(r,c):
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]):
                    yield nr,nc

        def area(r,c, island_num):
            if not (0 <= r < len(grid) and 0 <= c < len(grid[0]) and grid[r][c] == 1):
                return 0
            
            grid[r][c] = island_num
            island_area = 1

            for nr,nc in neighbors(r,c):
                island_area += area(nr,nc, island_num)
            
            return island_area

        # get island areas
        island_num = 2
        areas = {}
        # max_area = 0
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==1:
                    areas[island_num] = area(r,c,island_num)
                    island_num+=1
                    # print(areas[island_num])
                    # max_area = max(max_area, areas[island_num])

        max_area = max(areas.values(), default=0)

        # join nei island areas
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    # nei_islands = set()
                    nei_islands = { grid[nr][nc] for nr,nc in neighbors(r,c) if grid[nr][nc]>1}

                    # add areas 
                    max_area =  max(max_area, 1 + sum(areas[i] for i in nei_islands))

        return max_area

                    


        




    def largestIsland3(self, grid):
        N = len(grid)

        def check(r, c):
            seen = {(r, c)}
            stack = [(r, c)]
            while stack:
                r, c = stack.pop()
                for nr, nc in ((r-1, c), (r, c-1), (r+1, c), (r, c+1)):
                    if (nr, nc) not in seen and 0 <= nr < N and 0 <= nc < N and grid[nr][nc]:
                        stack.append((nr, nc))
                        seen.add((nr, nc))
            return len(seen)


        def area(r,c):
            count = 1
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if  0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in seen and grid[nr][nc]==1:
                    seen.add((nr,nc))
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                seen = set({(r,c)})
                if val == 0:
                    has_zero = True
                    ans = max(ans, area(r, c))

        return ans if has_zero else N*N

    def largestIsland(self, grid):
        # dfs call to get area for a cell
        def get_area(r,c):
            # 1. check if visited or any other condition which makes it invalid cell
            if (r,c) in visited:
                return 0
            
            # 2. set to visited and process
            visited.add((r,c))

            #3. default value
            # should be 1 that is the value for a cell
            area = 1

            #3. for each choice- neighbors
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]:

                #4. if valid move
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc]==1:
                    #4. add area for all neighbors
                    area += get_area(nr,nc)

            return area


        max_area = 0
        has_zero = False

        # for each cell 
        for r, row in enumerate(grid):
            for c, val in enumerate(row):

                # if it can be visited 
                if grid[r][c]==0:

                    # if you go any zero or else all 1 
                    has_zero = True

                    # visited for each traversal from this cell
                    visited = set()
                    max_area = max(max_area, get_area(r,c))
        return max_area if has_zero else len(grid)*len(grid[0])

    
    def largestIsland(self, grid: List[List[int]]) -> int:

        island_areas = {} # islandnum:area
        # save area for each islands
        island_num = 2
        neighbors = lambda r, c: [(r,c+1),(r+1,c),(r-1,c),(r,c-1)]
        N = len(grid)
        def get_area(r,c, island_num):
            grid[r][c] = island_num
            area = 1
            for nr,nc in neighbors(r,c):
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc] == 1:
                    area += get_area(nr,nc, island_num)
            
            return area

        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] == 1:# and (r,c) not in visited:
                    island_areas[island_num] = get_area(r,c, island_num)
                    island_num +=1

        # for each zero add neigbor areas
        max_area = -1
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    neighbor_islands = { grid[nr][nc] for nr,nc in neighbors(r,c) if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc] >1}
                    print(neighbor_islands)
                    max_area = max(max_area, 1+ sum(island_areas[neighbor_island] for neighbor_island in neighbor_islands))
        
        return N*N if max_area<0 else max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()
  
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0  

            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    seen.clear()
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])
    
    def largestIsland(self, grid: List[List[int]]) -> int:
        max_area = 0
        found_zero = False
        visited = set()
        def get_area(r,c):
            if (r,c) in visited:
                return 0
            
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0

            visited.add((r,c))
            area = 1
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                area+= get_area(nr,nc)
            
            return area

        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] == 0:
                    visited.clear()
                    found_zero = True
                    grid[r][c] = 1
                    max_area = max(max_area, get_area(r,c))
                    grid[r][c]= 0

        return max_area if found_zero else len(grid) * len(grid[0])

    def largestIsland(self, grid: List[List[int]]) -> int:

        island_areas = {} # islandnum:area
        # save area for each islands
        island_num = 2
        neighbors = lambda r, c: [(r,c+1),(r+1,c),(r-1,c),(r,c-1)]
        N = len(grid)
        
        def get_area(r,c, island_num):
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c] == 1):
                return 0
            grid[r][c] = island_num
            area = 1
            for nr,nc in neighbors(r,c):
                area += get_area(nr,nc, island_num)
            
            return area

        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] == 1:# and (r,c) not in visited:
                    island_areas[island_num] = get_area(r,c, island_num)
                    island_num +=1

        # for each zero add neigbor areas
        max_area = -1
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    neighbor_islands = { grid[nr][nc] for nr,nc in neighbors(r,c) if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc] >1}
                    print(neighbor_islands)
                    max_area = max(max_area, 1+ sum(island_areas[neighbor_island] for neighbor_island in neighbor_islands))
        
        return N*N if max_area<0 else max_area
```

## Attempt 28 · 2024-02-06 07:12 IST · Accepted · Python3

[submission 1167335012](https://leetcode.com/submissions/detail/1167335012/) · tests 75/75 · runtime 2890 ms (beats 5.0%)

```python
class Solution1:
    def largestIsland1(self, grid: List[List[int]]) -> int:
        '''
        islands can get connectd if you replace any cell value
        approach 1 : start with zeros and then start counting area and putting it in visited
        If you use seen/visited with dfs - you need to reset/initialize seen outside the dfs method and when you do that you need to add initial ()
        O(MN MN)

        approach 2: but you don't have to calculate area everytime, instead you can save area of each island with island number and then use some logic to calculate total area if you flip each zero to one
        either use visited or set grid value itself to island number to avoid visiting again
        
        time complexity O(MN)
        '''
        N = len(grid)

        def neighbors(r,c):
            for nr, nc in [(r+1,c),(r-1,c),(r,c-1),(r,c+1)]:
                if 0<=nr<N and 0<=nc<N:
                    yield nr,nc
        
        def area(r,c, island_num):
            '''
            calculate area of island using return 1+ dfs()
            with base condition if invalid return 0
            '''
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0
            grid[r][c] = island_num
            
            return 1 + dfs(r+1,c, island_num) + dfs(r-1,c, island_num) + dfs(r,c-1, island_num) +dfs(r,c+1, island_num)
            
        areas = {}
        island_num = 2

        # 1. caclulate area fo each island and save it in hashset 
        #  update island number to avoid visited cells
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    areas[island_num] = area(row,col,island_num)
                    island_num +=1

        #2. find max area so far if there are any islands else set it to zero
        max_area = max(areas.values() or [0])

        #3. now flip each zero, that is count 1+ area of neighboring islands 
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] ==0:

                    #4. get distinct neighboring areas other than 0 
                    nei_groups = {grid[nr][nc] for nr, nc in neighbors(row,col) if grid[nr][nc] > 1}

                    #5. add 1 for this 0 cell and rest of neighbor areas
                    max_area =  max(max_area, 1+ sum(areas[i] for i in nei_groups))
        return max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()
  
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0  

            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])

class Solution(object):
    def largestIsland(self, grid):

        # calculate area of the island 
        # update island_num

        def neighbors(r,c):
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]):
                    yield nr,nc

        def area(r,c, island_num):
            if not (0 <= r < len(grid) and 0 <= c < len(grid[0]) and grid[r][c] == 1):
                return 0
            
            grid[r][c] = island_num
            island_area = 1

            for nr,nc in neighbors(r,c):
                island_area += area(nr,nc, island_num)
            
            return island_area

        # get island areas
        island_num = 2
        areas = {}
        # max_area = 0
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==1:
                    areas[island_num] = area(r,c,island_num)
                    island_num+=1
                    # print(areas[island_num])
                    # max_area = max(max_area, areas[island_num])

        max_area = max(areas.values(), default=0)

        # join nei island areas
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    # nei_islands = set()
                    nei_islands = { grid[nr][nc] for nr,nc in neighbors(r,c) if grid[nr][nc]>1}

                    # add areas 
                    max_area =  max(max_area, 1 + sum(areas[i] for i in nei_islands))

        return max_area

                    


        




    def largestIsland3(self, grid):
        N = len(grid)

        def check(r, c):
            seen = {(r, c)}
            stack = [(r, c)]
            while stack:
                r, c = stack.pop()
                for nr, nc in ((r-1, c), (r, c-1), (r+1, c), (r, c+1)):
                    if (nr, nc) not in seen and 0 <= nr < N and 0 <= nc < N and grid[nr][nc]:
                        stack.append((nr, nc))
                        seen.add((nr, nc))
            return len(seen)


        def area(r,c):
            count = 1
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if  0<=nr<len(grid) and 0<=nc<len(grid[0]) and (nr,nc) not in seen and grid[nr][nc]==1:
                    seen.add((nr,nc))
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                seen = set({(r,c)})
                if val == 0:
                    has_zero = True
                    ans = max(ans, area(r, c))

        return ans if has_zero else N*N

    def largestIsland(self, grid):
        # dfs call to get area for a cell
        def get_area(r,c):
            # 1. check if visited or any other condition which makes it invalid cell
            if (r,c) in visited:
                return 0
            
            # 2. set to visited and process
            visited.add((r,c))

            #3. default value
            # should be 1 that is the value for a cell
            area = 1

            #3. for each choice- neighbors
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]:

                #4. if valid move
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc]==1:
                    #4. add area for all neighbors
                    area += get_area(nr,nc)

            return area


        max_area = 0
        has_zero = False

        # for each cell 
        for r, row in enumerate(grid):
            for c, val in enumerate(row):

                # if it can be visited 
                if grid[r][c]==0:

                    # if you go any zero or else all 1 
                    has_zero = True

                    # visited for each traversal from this cell
                    visited = set()
                    max_area = max(max_area, get_area(r,c))
        return max_area if has_zero else len(grid)*len(grid[0])

    
    def largestIsland(self, grid: List[List[int]]) -> int:

        island_areas = {} # islandnum:area
        # save area for each islands
        island_num = 2
        neighbors = lambda r, c: [(r,c+1),(r+1,c),(r-1,c),(r,c-1)]
        N = len(grid)
        def get_area(r,c, island_num):
            grid[r][c] = island_num
            area = 1
            for nr,nc in neighbors(r,c):
                if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc] == 1:
                    area += get_area(nr,nc, island_num)
            
            return area

        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] == 1:# and (r,c) not in visited:
                    island_areas[island_num] = get_area(r,c, island_num)
                    island_num +=1

        # for each zero add neigbor areas
        max_area = -1
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    neighbor_islands = { grid[nr][nc] for nr,nc in neighbors(r,c) if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc] >1}
                    print(neighbor_islands)
                    max_area = max(max_area, 1+ sum(island_areas[neighbor_island] for neighbor_island in neighbor_islands))
        
        return N*N if max_area<0 else max_area

    def largestIsland(self, grid: List[List[int]]) -> int:
        seen = set()
  
        def area(r,c):
            if not( 0<=r<len(grid) and 0<=c<len(grid[0]) and (r,c) not in seen and grid[r][c]==1):
                return 0  

            count = 1
            seen.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                    count  += area(nr,nc)
                    
            return count

        ans = 0
        has_zero = False
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    seen.clear()
                    has_zero = True
                    # seen.add((r,c))
                    grid[r][c] =1
                    ans = max(ans ,area(r,c))
                    grid[r][c] =0


        return ans if has_zero else len(grid)* len(grid[0])
    
    def largestIsland(self, grid: List[List[int]]) -> int:
        max_area = 0
        found_zero = False
        visited = set()
        def get_area(r,c):
            if (r,c) in visited:
                return 0
            
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c]==1):
                return 0

            visited.add((r,c))
            area = 1
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                area+= get_area(nr,nc)
            
            return area

        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] == 0:
                    visited.clear()
                    found_zero = True
                    grid[r][c] = 1
                    max_area = max(max_area, get_area(r,c))
                    grid[r][c]= 0

        return max_area if found_zero else len(grid) * len(grid[0])

    def largestIsland(self, grid: List[List[int]]) -> int:

        island_areas = {} # islandnum:area
        # save area for each islands
        island_num = 2
        neighbors = lambda r, c: [(r,c+1),(r+1,c),(r-1,c),(r,c-1)]
        N = len(grid)
        
        def get_area(r,c, island_num):
            if not(0<=r<len(grid) and 0<=c<len(grid[0]) and grid[r][c] == 1):
                return 0
            grid[r][c] = island_num
            area = 1
            for nr,nc in neighbors(r,c):
                area += get_area(nr,nc, island_num)
            
            return area

        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] == 1:# and (r,c) not in visited:
                    island_areas[island_num] = get_area(r,c, island_num)
                    island_num +=1

        # for each zero add neigbor areas
        max_area = -1
        for r in range(len(grid)):
            for c in range(len(grid[0])):
                if grid[r][c] ==0:
                    neighbor_islands = { grid[nr][nc] for nr,nc in neighbors(r,c) if 0<=nr<len(grid) and 0<=nc<len(grid[0]) and grid[nr][nc] >1}
                    print(neighbor_islands)
                    max_area = max(max_area, 1+ sum(island_areas[neighbor_island] for neighbor_island in neighbor_islands))
        
        return N*N if max_area<0 else max_area
```
