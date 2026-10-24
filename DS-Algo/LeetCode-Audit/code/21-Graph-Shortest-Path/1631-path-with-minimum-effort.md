# 1631. Path With Minimum Effort

[Problem](https://leetcode.com/problems/path-with-minimum-effort/) · Medium · Graph: Shortest Path → Minimax Dijkstra

LeetCode tags: array, binary-search, depth-first-search, breadth-first-search, union-find, heap-priority-queue, matrix, dijkstra

Attempts since Mar 2023: 9 · accepted: 5 · failed before first AC: 2

## Attempt 1 · 2023-04-30 12:51 IST · Wrong Answer · C++

[submission 941993188](https://leetcode.com/submissions/detail/941993188/) · tests 3/75

Failing input:

```text
[[3]]
```

Expected:

```text
0
```

Your output:

```text
-1000000000
```

```cpp
class Solution {
    typedef pair<int,pair<int,int>> piii;
    typedef pair<int,int> pii;
public:
    int minimumEffortPath(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        pii src = {0,0}, dest = {n-1,m-1};
        vector<vector<int>> dist(n, vector<int>(n, 1e9));
        priority_queue<piii, vector<piii>, greater<piii>> pq;
        pq.push({-1e9,src});
        dist[0][0] = -1e9;
        int dx[] = {-1,0,1,0};
        int dy[] = {0,-1,0,1};
        int ans = 1e9;
        while(!pq.empty()){
            auto node = pq.top(); pq.pop();
            src = node.second;
            int dis = node.first;
            if(src == dest){
                cout<<dis<<"|";
                ans = min(ans, dis);
            }
            for(int i=0;i<4;i++){
                int r = src.first + dx[i];
                int c = src.second + dy[i];

                if(r>=0 && r<n && c>=0 && c<m && abs(grid[src.first][src.second]-grid[r][c]) < dist[r][c]){
                    int diff = abs(grid[src.first][src.second]-grid[r][c]);               dist[r][c] = diff;
                    pq.push({max(diff, dis), {r,c}});
                }
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-04-30 12:52 IST · Runtime Error · C++

[submission 941993668](https://leetcode.com/submissions/detail/941993668/) · tests 4/75

Failing input:

```text
[[1,10,6,7,9,10,4,9]]
```

Expected:

```text
9
```

Runtime error:

```text
=================================================================
==23==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x6020000007d4 at pc 0x00000034e446 bp 0x7ffc06ac4d10 sp 0x7ffc06ac4d08
READ of size 4 at 0x6020000007d4 thread T0
    #2 0x7faf742a8082  (/lib/x86_64-linux-gnu/libc.so.6+0x24082)
0x6020000007d4 is located 0 bytes to the right of 4-byte region [0x6020000007d0,0x602000000 ... [1532 more chars]
```

```cpp
class Solution {
    typedef pair<int,pair<int,int>> piii;
    typedef pair<int,int> pii;
public:
    int minimumEffortPath(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        pii src = {0,0}, dest = {n-1,m-1};
        vector<vector<int>> dist(n, vector<int>(n, 1e9));
        priority_queue<piii, vector<piii>, greater<piii>> pq;
        pq.push({0,src});
        dist[0][0] = 0;
        int dx[] = {-1,0,1,0};
        int dy[] = {0,-1,0,1};
        int ans = 1e9;
        while(!pq.empty()){
            auto node = pq.top(); pq.pop();
            src = node.second;
            int dis = node.first;
            if(src == dest){
                cout<<dis<<"|";
                ans = min(ans, dis);
            }
            for(int i=0;i<4;i++){
                int r = src.first + dx[i];
                int c = src.second + dy[i];

                if(r>=0 && r<n && c>=0 && c<m && abs(grid[src.first][src.second]-grid[r][c]) < dist[r][c]){
                    int diff = abs(grid[src.first][src.second]-grid[r][c]);               dist[r][c] = diff;
                    pq.push({max(diff, dis), {r,c}});
                }
            }
        }
        return ans;
    }
};
```

## Attempt 3 · 2023-04-30 12:55 IST · Accepted · C++

[submission 941994698](https://leetcode.com/submissions/detail/941994698/) · tests 75/75 · runtime 282 ms (beats 5.2%)

```cpp
class Solution {
    typedef pair<int,pair<int,int>> piii;
    typedef pair<int,int> pii;
public:
    int minimumEffortPath(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        pii src = {0,0}, dest = {n-1,m-1};
        vector<vector<int>> dist(n, vector<int>(m, 1e9));
        priority_queue<piii, vector<piii>, greater<piii>> pq;
        pq.push({0,src});
        dist[0][0] = 0;
        int dx[] = {-1,0,1,0};
        int dy[] = {0,-1,0,1};
        int ans = 1e9;
        while(!pq.empty()){
            auto node = pq.top(); pq.pop();
            src = node.second;
            int dis = node.first;
            if(src == dest){
                cout<<dis<<"|";
                ans = min(ans, dis);
            }
            for(int i=0;i<4;i++){
                int r = src.first + dx[i];
                int c = src.second + dy[i];

                if(r>=0 && r<n && c>=0 && c<m && abs(grid[src.first][src.second]-grid[r][c]) < dist[r][c]){
                    int diff = abs(grid[src.first][src.second]-grid[r][c]);               dist[r][c] = diff;
                    pq.push({max(diff, dis), {r,c}});
                }
            }
        }
        return ans;
    }
};
```

## Attempt 4 · 2023-04-30 13:02 IST · Accepted · C++

[submission 941997459](https://leetcode.com/submissions/detail/941997459/) · tests 75/75 · runtime 234 ms (beats 6.9%)

```cpp
class Solution {
    typedef pair<int,pair<int,int>> piii;
    typedef pair<int,int> pii;
public:
    int minimumEffortPath(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        pii src = {0,0}, dest = {n-1,m-1};
        vector<vector<int>> dist(n, vector<int>(m, 1e9));
        priority_queue<piii, vector<piii>, greater<piii>> pq;
        pq.push({0,src});
        dist[0][0] = 0;
        int dx[] = {-1,0,1,0};
        int dy[] = {0,-1,0,1};
        int ans = 1e9;
        while(!pq.empty()){
            auto node = pq.top(); pq.pop();
            src = node.second;
            int dis = node.first;
            if(src == dest){
                cout<<dis<<"|";
                ans = min(ans, dis);
                return ans;
            }
            for(int i=0;i<4;i++){
                int r = src.first + dx[i];
                int c = src.second + dy[i];

                if(r>=0 && r<n && c>=0 && c<m && abs(grid[src.first][src.second]-grid[r][c]) < dist[r][c]){
                    int diff = abs(grid[src.first][src.second]-grid[r][c]);               dist[r][c] = diff;
                    pq.push({max(diff, dis), {r,c}});
                }
            }
        }
        return ans;
    }
};
```

## Attempt 5 · 2023-12-28 22:46 IST · Accepted · Python3

[submission 1130722345](https://leetcode.com/submissions/detail/1130722345/) · tests 75/75 · runtime 642 ms (beats 13.2%)

```python
class Solution:
    def minimumEffortPath(self, heights: List[List[int]]) -> int:
        
        '''
        similar to djkstra problem - find shortest path in weighted graph
        '''
        rows, cols = len(heights), len(heights[0])
        effort_to = [[float('inf')] * cols for _ in range(rows)]
        effort_to[0][0] = 0

        # Min-heap: (effort, row, col)
        min_heap = [(0, 0, 0)]

        while min_heap:
            effort, row, col = heapq.heappop(min_heap)

            # If we've reached the bottom-right cell, return the effort
            if row == rows - 1 and col == cols - 1:
                return effort

            for nr, nc in [(row-1, col), (row+1, col), (row, col-1), (row, col+1)]:
                if 0 <= nr < rows and 0 <= nc < cols:
                    # Calculate the effort to reach the neighbor
                    next_effort = max(effort, abs(heights[nr][nc] - heights[row][col]))
                    # If this path to neighbor is better, update and add to heap
                    if next_effort < effort_to[nr][nc]:
                        effort_to[nr][nc] = next_effort
                        heapq.heappush(min_heap, (next_effort, nr, nc))

        return 0
```

## Attempt 6 · 2023-12-28 22:58 IST · Output Limit Exceeded · Python3

[submission 1130731608](https://leetcode.com/submissions/detail/1130731608/) · tests 15/75

Failing input:

```text
[[876152,480136,914305,818785,744219,482979,803034,224126,795699,612972,431503,650200,819501,878173,117519,911971,530299,511070,332967,464758,473678,336858,576080,142257,431902,953017,276039,946828,617285,809125,875219,915600,116826,949029,734733,496152,454662,945192,587521,393008,91056,491827,983229,541842,530615,370176,373018,372680,721423,691136,277853,946141,781544,340278],[828513,253737,13265 ... [31406 more chars]
```

Expected:

```text
430152
```

```python
class Solution:
    def minimumEffortPath(self, heights: List[List[int]]) -> int:
        
        '''
        similar to djkstra problem - find shortest path in weighted graph
        '''
        rows, cols = len(heights), len(heights[0])
        effort_to = [[float('inf')] * cols for _ in range(rows)]

        # keep track of effort so far and 
        # compare effort from previous to current cell with effort so far
        effort_to[0][0] = 0

        # Min-heap: (effort, row, col)
        # you can't use visited because you don't know which path will lead to mimimum
        # the future path to same cell could lead to minimum
        # min_heap can have same node multiple times if you encounter a min distance later
        min_heap = [(0, 0, 0)]

        while min_heap:
            effort, row, col = heapq.heappop(min_heap)

            # If we've reached the bottom-right cell, return the effort
            if row == rows - 1 and col == cols - 1:
                return effort

            for nr, nc in [(row-1, col), (row+1, col), (row, col-1), (row, col+1)]:
                
                if 0 <= nr < rows and 0 <= nc < cols:
                    
                    # Calculate the effort to reach the neighbor
                    next_effort = max(effort, abs(heights[nr][nc] - heights[row][col]))
                    
                    # If this path to neighbor is better, update and add to heap
                    if next_effort < effort_to[nr][nc]:
                        effort_to[nr][nc] = next_effort
                        heapq.heappush(min_heap, (next_effort, nr, nc))
            print(min_heap)

        return 0
```

## Attempt 7 · 2023-12-28 22:58 IST · Accepted · Python3

[submission 1130731765](https://leetcode.com/submissions/detail/1130731765/) · tests 75/75 · runtime 598 ms (beats 13.7%)

```python
class Solution:
    def minimumEffortPath(self, heights: List[List[int]]) -> int:
        
        '''
        similar to djkstra problem - find shortest path in weighted graph
        '''
        rows, cols = len(heights), len(heights[0])
        effort_to = [[float('inf')] * cols for _ in range(rows)]

        # keep track of effort so far and 
        # compare effort from previous to current cell with effort so far
        effort_to[0][0] = 0

        # Min-heap: (effort, row, col)
        # you can't use visited because you don't know which path will lead to mimimum
        # the future path to same cell could lead to minimum
        # min_heap can have same node multiple times if you encounter a min distance later
        min_heap = [(0, 0, 0)]

        while min_heap:
            effort, row, col = heapq.heappop(min_heap)

            # If we've reached the bottom-right cell, return the effort
            if row == rows - 1 and col == cols - 1:
                return effort

            for nr, nc in [(row-1, col), (row+1, col), (row, col-1), (row, col+1)]:
                
                if 0 <= nr < rows and 0 <= nc < cols:
                    
                    # Calculate the effort to reach the neighbor
                    next_effort = max(effort, abs(heights[nr][nc] - heights[row][col]))
                    
                    # If this path to neighbor is better, update and add to heap
                    if next_effort < effort_to[nr][nc]:
                        effort_to[nr][nc] = next_effort
                        heapq.heappush(min_heap, (next_effort, nr, nc))
            # print(min_heap)

        return 0
```

## Attempt 8 · 2024-01-15 23:51 IST · Wrong Answer · Python3

[submission 1147122502](https://leetcode.com/submissions/detail/1147122502/) · tests 9/75

Failing input:

```text
[[1,10,6,7,9,10,4,9]]
```

Expected:

```text
9
```

Your output:

```text
5
```

```python
class Solution:
    def minimumEffortPath(self, heights: List[List[int]]) -> int:
        
        '''
        similar to djkstra problem - find shortest path in weighted graph
        '''
        rows, cols = len(heights), len(heights[0])
        effort_to = [[float('inf')] * cols for _ in range(rows)]

        # keep track of effort so far and 
        # compare effort from previous to current cell with effort so far
        effort_to[0][0] = 0

        # Min-heap: (effort, row, col)
        # you can't use visited because you don't know which path will lead to mimimum
        # the future path to same cell could lead to minimum
        # min_heap can have same node multiple times if you encounter a min distance later
        min_heap = [(0, 0, 0)]

        while min_heap:
            effort, row, col = heapq.heappop(min_heap)

            # If we've reached the bottom-right cell, return the effort
            if row == rows - 1 and col == cols - 1:
                return effort

            for nr, nc in [(row-1, col), (row+1, col), (row, col-1), (row, col+1)]:
                
                if 0 <= nr < rows and 0 <= nc < cols:
                    
                    # Calculate the effort to reach the neighbor
                    next_effort = max(effort, abs(heights[nr][nc] - heights[row][col]))
                    
                    # If this path to neighbor is better, update and add to heap
                    if next_effort < effort_to[nr][nc]:
                        effort_to[nr][nc] = next_effort
                        heapq.heappush(min_heap, (next_effort, nr, nc))
            # print(min_heap)

        return 0

    def minimumEffortPath(self, heights):
        rows, cols = len(heights), len(heights[0])
        directions = [(0, 1), (0, -1), (-1, 0), (1, 0)]

        # Function to calculate effort between two cells
        def get_effort(x, y, nx, ny):
            return abs(heights[x][y] - heights[nx][ny])

        # BFS with effort tracking
        queue = deque([(0, 0, 0)])
        effort_to = [[float('inf')]*cols for _ in range(rows)]

        effort_to[0][0] = 0
        while queue:
            x, y, current_effort = queue.popleft()
            # if (x, y) == (rows - 1, cols - 1):
            #     return current_effort  # Reached destination
            for dx, dy in directions:
                nx, ny = x + dx, y + dy
                if 0 <= nx < rows and 0 <= ny < cols:
                    # new_effort = max(current_effort, )
                    new_effort = get_effort(x, y, nx, ny)
                    if new_effort < effort_to[nx][ny]:
                        effort_to[nx][ny] = new_effort
                        queue.append((nx, ny, new_effort))

        return effort_to[rows-1][cols-1]
```

## Attempt 9 · 2024-01-15 23:51 IST · Accepted · Python3

[submission 1147122724](https://leetcode.com/submissions/detail/1147122724/) · tests 75/75 · runtime 6626 ms (beats 5.0%)

```python
class Solution:
    def minimumEffortPath(self, heights: List[List[int]]) -> int:
        
        '''
        similar to djkstra problem - find shortest path in weighted graph
        '''
        rows, cols = len(heights), len(heights[0])
        effort_to = [[float('inf')] * cols for _ in range(rows)]

        # keep track of effort so far and 
        # compare effort from previous to current cell with effort so far
        effort_to[0][0] = 0

        # Min-heap: (effort, row, col)
        # you can't use visited because you don't know which path will lead to mimimum
        # the future path to same cell could lead to minimum
        # min_heap can have same node multiple times if you encounter a min distance later
        min_heap = [(0, 0, 0)]

        while min_heap:
            effort, row, col = heapq.heappop(min_heap)

            # If we've reached the bottom-right cell, return the effort
            if row == rows - 1 and col == cols - 1:
                return effort

            for nr, nc in [(row-1, col), (row+1, col), (row, col-1), (row, col+1)]:
                
                if 0 <= nr < rows and 0 <= nc < cols:
                    
                    # Calculate the effort to reach the neighbor
                    next_effort = max(effort, abs(heights[nr][nc] - heights[row][col]))
                    
                    # If this path to neighbor is better, update and add to heap
                    if next_effort < effort_to[nr][nc]:
                        effort_to[nr][nc] = next_effort
                        heapq.heappush(min_heap, (next_effort, nr, nc))
            # print(min_heap)

        return 0

    def minimumEffortPath(self, heights):
        rows, cols = len(heights), len(heights[0])
        directions = [(0, 1), (0, -1), (-1, 0), (1, 0)]

        # Function to calculate effort between two cells
        def get_effort(x, y, nx, ny):
            return abs(heights[x][y] - heights[nx][ny])

        # BFS with effort tracking
        queue = deque([(0, 0, 0)])
        effort_to = [[float('inf')]*cols for _ in range(rows)]

        effort_to[0][0] = 0
        while queue:
            x, y, current_effort = queue.popleft()
            # if (x, y) == (rows - 1, cols - 1):
            #     return current_effort  # Reached destination
            for dx, dy in directions:
                nx, ny = x + dx, y + dy
                if 0 <= nx < rows and 0 <= ny < cols:
                    new_effort = max(current_effort,get_effort(x, y, nx, ny) )
                    # new_effort = get_effort(x, y, nx, ny)
                    if new_effort < effort_to[nx][ny]:
                        effort_to[nx][ny] = new_effort
                        queue.append((nx, ny, new_effort))

        return effort_to[rows-1][cols-1]
```
