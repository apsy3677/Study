# 1091. Shortest Path in Binary Matrix

[Problem](https://leetcode.com/problems/shortest-path-in-binary-matrix/) · Medium · Graph: Shortest Path → BFS, 8 directions

LeetCode tags: array, breadth-first-search, matrix

Attempts since Mar 2023: 8 · accepted: 8 · failed before first AC: 0

## Attempt 1 · 2023-04-30 11:57 IST · Accepted · C++

[submission 941971420](https://leetcode.com/submissions/detail/941971420/) · tests 89/89 · runtime 466 ms (beats 5.1%)

```cpp
class Solution {
    typedef pair<int,pair<int,int>> piii;
    typedef pair<int,int> pii;
public:

    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        if(grid[0][0]==1)return -1;
        int n = grid.size();
        pii src = {0,0}, dest = {n-1,n-1};
        vector<vector<int>> dist(n, vector<int>(n, 1e9));
        priority_queue<piii, vector<piii>, greater<piii>> pq;
        pq.push({1,src});
        while(!pq.empty()){
            auto node = pq.top(); pq.pop();
            src = node.second;
            int dis = node.first;
            if(src == dest){
                return dis;
            }
            for(int i=-1; i<=1;i++){
                for(int j= -1; j<=1;j++){
                    int r = src.first + i;
                    int c = src.second + j;
                    if(r>=0 && r<n && c>=0 && c<n && grid[r][c]==0 && dist[r][c] == 1e9){
                        cout<<r<<"|"<<c<<":"<<dis+1<<":: ";
                        if(dis + 1 < dist[r][c]){
                            dist[r][c] = dis +1;
                            pq.push({dist[r][c], {r,c}});
                        }
                    }
                }
            }
        }
        return -1;
    }
};
```

## Attempt 2 · 2023-04-30 11:58 IST · Accepted · C++

[submission 941971993](https://leetcode.com/submissions/detail/941971993/) · tests 89/89 · runtime 589 ms (beats 5.1%)

```cpp
class Solution {
    typedef pair<int,pair<int,int>> piii;
    typedef pair<int,int> pii;
public:

    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        if(grid[0][0]==1)return -1;
        int n = grid.size();
        pii src = {0,0}, dest = {n-1,n-1};
        vector<vector<int>> dist(n, vector<int>(n, 1e9));
        priority_queue<piii, vector<piii>, greater<piii>> pq;
        pq.push({1,src});
        while(!pq.empty()){
            int sz = pq.size();
            while(sz--){
                auto node = pq.top(); pq.pop();
                src = node.second;
                int dis = node.first;
                if(src == dest){
                    return dis;
                }
                for(int i=-1; i<=1;i++){
                    for(int j= -1; j<=1;j++){
                        int r = src.first + i;
                        int c = src.second + j;
                        if(r>=0 && r<n && c>=0 && c<n && grid[r][c]==0 && dist[r][c] == 1e9){
                            cout<<r<<"|"<<c<<":"<<dis+1<<":: ";
                            if(dis + 1 < dist[r][c]){
                                dist[r][c] = dis +1;
                                pq.push({dist[r][c], {r,c}});
                            }
                        }
                    }
                }
            }
            
        }
        return -1;
    }
};
```

## Attempt 3 · 2023-04-30 11:59 IST · Accepted · C++

[submission 941972432](https://leetcode.com/submissions/detail/941972432/) · tests 89/89 · runtime 516 ms (beats 5.1%)

```cpp
class Solution {
    typedef pair<int,pair<int,int>> piii;
    typedef pair<int,int> pii;
public:

    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        if(grid[0][0]==1)return -1;
        int n = grid.size();
        pii src = {0,0}, dest = {n-1,n-1};
        vector<vector<int>> dist(n, vector<int>(n, 1e9));
        priority_queue<piii, vector<piii>, greater<piii>> pq;
        pq.push({1,src});
        int level=0;
        while(!pq.empty()){
            int sz = pq.size();
            while(sz--){
                auto node = pq.top(); pq.pop();
                src = node.second;
                int dis = node.first;
                if(src == dest){
                    return level+1;
                }
                for(int i=-1; i<=1;i++){
                    for(int j= -1; j<=1;j++){
                        int r = src.first + i;
                        int c = src.second + j;
                        if(r>=0 && r<n && c>=0 && c<n && grid[r][c]==0 && dist[r][c] == 1e9){
                            cout<<r<<"|"<<c<<":"<<dis+1<<":: ";
                            if(dis + 1 < dist[r][c]){
                                dist[r][c] = dis +1;
                                pq.push({dist[r][c], {r,c}});
                            }
                        }
                    }
                }
            }
            level++;
        }
        return -1;
    }
};
```

## Attempt 4 · 2023-11-22 22:06 IST · Accepted · Python3

[submission 1104290379](https://leetcode.com/submissions/detail/1104290379/) · tests 90/90 · runtime 522 ms (beats 5.1%)

```python
class Solution:
    def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:
        N = len(grid)
        M = len(grid[0])

        def neighbors(r,c):
            for dr, dc in [(-1,0),(0,-1),(1,0),(0,1),(1,-1),(-1,1),(1,1),(-1,-1)]:
                yield r+dr, c+dc

        if grid[0][0] != 0 or grid[N-1][M-1]!=0:
            return -1

        queue = deque([(0,0)])

        grid[0][0] =1
        while queue:
            r, c = queue.popleft()
            if (r,c) == (N-1, M-1):
                return grid[r][c]
            for nr,nc in neighbors(r,c):
                if 0<=nr<N and 0<=nc<M and grid[nr][nc] ==0:
                    grid[nr][nc] = grid[r][c]+1
                    queue.append((nr,nc))

        return -1
```

## Attempt 5 · 2023-12-01 10:58 IST · Accepted · Python3

[submission 1110000050](https://leetcode.com/submissions/detail/1110000050/) · tests 90/90 · runtime 554 ms (beats 5.1%)

```python
class Solution:
    def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:
        N = len(grid)
        M = len(grid[0])

        if grid[0][0] != 0 or grid[N-1][M-1]!=0:
            return -1

        def neighbors(r,c):
            for dr, dc in [(-1,0),(0,-1),(1,0),(0,1),(1,-1),(-1,1),(1,1),(-1,-1)]:
                yield r+dr, c+dc

        queue = deque([(0,0)])

        grid[0][0] =1
        while queue:
            r, c = queue.popleft()
            distance = grid[r][c]
            
            # check if goal reached
            if (r,c) == (N-1, M-1):
                return distance

            for nr,nc in neighbors(r,c):
                # check visited
                if 0<=nr<N and 0<=nc<M and grid[nr][nc] ==0:

                    # add visited and enque
                    grid[nr][nc] = distance + 1
                    queue.append((nr,nc))

        return -1
```

## Attempt 6 · 2023-12-04 22:00 IST · Accepted · Python3

[submission 1112280515](https://leetcode.com/submissions/detail/1112280515/) · tests 90/90 · runtime 565 ms (beats 5.1%)

```python
class Solution:
    def shortestPathBinaryMatrix1(self, grid: List[List[int]]) -> int:
        N = len(grid)
        M = len(grid[0])

        if grid[0][0] != 0 or grid[N-1][M-1]!=0:
            return -1

        def neighbors(r,c):
            for dr, dc in [(-1,0),(0,-1),(1,0),(0,1),(1,-1),(-1,1),(1,1),(-1,-1)]:
                yield r+dr, c+dc

        queue = deque([(0,0)])

        grid[0][0] =1
        while queue:
            r, c = queue.popleft()
            distance = grid[r][c]
            
            # check if goal reached
            if (r,c) == (N-1, M-1):
                return distance

            for nr,nc in neighbors(r,c):
                # check visited
                if 0<=nr<N and 0<=nc<M and grid[nr][nc] ==0:

                    # add visited and enque
                    grid[nr][nc] = distance + 1
                    queue.append((nr,nc))

        return -1

    def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:
        N = len(grid)
        M = len(grid[0])
        
        if grid[0][0] != 0 or grid[N-1][M-1]!=0:
            return -1

        queue = deque([(0,0,1)]) # row, col, steps
        visited= set({(0,0)})
        

        while queue:
            r,c,steps = queue.popleft()

            if [r,c] == [N-1,M-1]:
                return steps

            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c),(r-1,c-1),(r+1,c+1),(r+1,c-1),(r-1,c+1)]:
                if 0<=nr<N and 0<=nc<M and grid[nr][nc] == 0 and (nr,nc) not in visited:
                    queue.append((nr,nc,steps+1))
                    visited.add((nr,nc))

        return -1
```

## Attempt 7 · 2024-02-03 06:21 IST · Accepted · Python3

[submission 1164358567](https://leetcode.com/submissions/detail/1164358567/) · tests 90/90 · runtime 385 ms (beats 5.1%)

```python
class Solution:
    def shortestPathBinaryMatrix1(self, grid: List[List[int]]) -> int:
        '''
        '''
        N = len(grid)
        M = len(grid[0])

        if grid[0][0] != 0 or grid[N-1][M-1]!=0:
            return -1

        def neighbors(r,c):
            for dr, dc in [(-1,0),(0,-1),(1,0),(0,1),(1,-1),(-1,1),(1,1),(-1,-1)]:
                yield r+dr, c+dc

        queue = deque([(0,0)])

        grid[0][0] =1
        while queue:
            r, c = queue.popleft()
            distance = grid[r][c]
            
            # check if goal reached
            if (r,c) == (N-1, M-1):
                return distance

            for nr,nc in neighbors(r,c):
                # check visited
                if 0<=nr<N and 0<=nc<M and grid[nr][nc] ==0:

                    # add visited and enque
                    grid[nr][nc] = distance + 1
                    queue.append((nr,nc))

        return -1

    def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:

        '''
        space complexity is still O(N) even though you have only at most 2 level of nodes at any time. the worst will occur around diagonal
        '''
        N = len(grid)
        M = len(grid[0])
        
        # 1. edge case if it is a good starting or ending point or not
        if grid[0][0] != 0 or grid[N-1][M-1]!=0:
            return -1

        queue = deque([(0,0,1)]) # row, col, steps
        #visited= set({(0,0)})
        grid[0][0] =1

        while queue:
            r,c,steps = queue.popleft()

            if [r,c] == [N-1,M-1]:
                return steps

            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c),(r-1,c-1),(r+1,c+1),(r+1,c-1),(r-1,c+1)]:
                if 0<=nr<N and 0<=nc<M and grid[nr][nc] == 0 :#and (nr,nc) not in visited:
                    queue.append((nr,nc,steps+1))
                    # visited.add((nr,nc))
                    grid[nr][nc] =1

        return -1
```

## Attempt 8 · 2024-02-06 06:50 IST · Accepted · Python3

[submission 1167323415](https://leetcode.com/submissions/detail/1167323415/) · tests 90/90 · runtime 410 ms (beats 5.1%)

```python
class Solution:
    def shortestPathBinaryMatrix1(self, grid: List[List[int]]) -> int:
        '''
        '''
        N = len(grid)
        M = len(grid[0])

        if grid[0][0] != 0 or grid[N-1][M-1]!=0:
            return -1

        def neighbors(r,c):
            for dr, dc in [(-1,0),(0,-1),(1,0),(0,1),(1,-1),(-1,1),(1,1),(-1,-1)]:
                yield r+dr, c+dc

        queue = deque([(0,0)])

        grid[0][0] =1
        while queue:
            r, c = queue.popleft()
            distance = grid[r][c]
            
            # check if goal reached
            if (r,c) == (N-1, M-1):
                return distance

            for nr,nc in neighbors(r,c):
                # check visited
                if 0<=nr<N and 0<=nc<M and grid[nr][nc] ==0:

                    # add visited and enque
                    grid[nr][nc] = distance + 1
                    queue.append((nr,nc))

        return -1

    def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:

        '''
        space complexity is still O(N) even though you have only at most 2 level of nodes at any time. the worst will occur around diagonal
        '''
        N = len(grid)
        M = len(grid[0])
        
        # 1. edge case if it is a good starting or ending point or not
        if grid[0][0] != 0 or grid[N-1][M-1]!=0:
            return -1

        queue = deque([(0,0,1)]) # row, col, steps
        visited= set({(0,0)})
        # grid[0][0] =1

        while queue:
            r,c,steps = queue.popleft()

            if [r,c] == [N-1,M-1]:
                return steps

            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c),(r-1,c-1),(r+1,c+1),(r+1,c-1),(r-1,c+1)]:
                if 0<=nr<N and 0<=nc<M and grid[nr][nc] == 0 and (nr,nc) not in visited:
                    queue.append((nr,nc,steps+1))
                    visited.add((nr,nc))
                    grid[nr][nc] =1

        return -1
```
