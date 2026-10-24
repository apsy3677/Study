# 1293. Shortest Path in a Grid with Obstacles Elimination

[Problem](https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/) · Hard · Graph: Shortest Path → BFS with extra state (k)

LeetCode tags: array, breadth-first-search, matrix

Attempts since Mar 2023: 3 · accepted: 1 · failed before first AC: 2

## Attempt 1 · 2023-03-24 02:08 IST · Time Limit Exceeded · C++

[submission 920951219](https://leetcode.com/submissions/detail/920951219/) · tests 22/53

Failing input:

```text
[[0,0,0,0,0,0,0,0,0,0],[0,1,1,1,1,1,1,1,1,0],[0,1,0,0,0,0,0,0,0,0],[0,1,0,1,1,1,1,1,1,1],[0,1,0,0,0,0,0,0,0,0],[0,1,1,1,1,1,1,1,1,0],[0,1,0,0,0,0,0,0,0,0],[0,1,0,1,1,1,1,1,1,1],[0,1,0,1,1,1,1,0,0,0],[0,1,0,0,0,0,0,0,1,0],[0,1,1,1,1,1,1,0,1,0],[0,0,0,0,0,0,0,0,1,0]]
1
```

Expected:

```text
20
```

```cpp
class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> visited(n, vector<int>(m,0));

        queue<vector<int>> qu;
        // push 0,0, currlen, k
        qu.push({0,0,0,k});
        while(!qu.empty()){
            auto t = qu.front();
            qu.pop();
            int x = t[0];
            int y = t[1];
            int len = t[2];
            int rem = t[3];

            if(x<0 || x>=n || y<0 || y>=m){
                continue;
            }
            if(x == n-1 && y==m-1){
                return len;
            }
            if(grid[x][y] ==1){
                if(rem>0){
                    rem--;
                }
                else{
                    continue;
                }
            }
            // check if this cell is already visited
            if(visited[x][y] != 0 && visited[x][y] > rem){
                continue;
            }
            visited[x][y] = rem;
            qu.push({x+1, y, len+1, rem});
            qu.push({x-1, y, len+1, rem});
            qu.push({x, y+1, len+1, rem});
            qu.push({x, y-1, len+1, rem});
        }
        return -1;
    }
};
```

## Attempt 2 · 2023-03-24 02:12 IST · Time Limit Exceeded · C++

[submission 920952432](https://leetcode.com/submissions/detail/920952432/) · tests 23/53

Failing input:

```text
[[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, ... [2637 more chars]
```

Expected:

```text
387
```

```cpp
class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> visited(n, vector<int>(m,0));

        queue<vector<int>> qu;
        // push 0,0, currlen, k
        qu.push({0,0,0,k});
        while(!qu.empty()){
            auto t = qu.front();
            qu.pop();
            int x = t[0];
            int y = t[1];
            int len = t[2];
            int rem = t[3];

            if(x<0 || x>=n || y<0 || y>=m){
                continue;
            }
            if(x == n-1 && y==m-1){
                return len;
            }
            if(grid[x][y] ==1){
                if(rem>0){
                    rem--;
                }
                else{
                    continue;
                }
            }
            // check if this cell is already visited
            if(visited[x][y] != 0 && visited[x][y] >= rem){
                continue;
            }
            visited[x][y] = rem;
            qu.push({x+1, y, len+1, rem});
            qu.push({x-1, y, len+1, rem});
            qu.push({x, y+1, len+1, rem});
            qu.push({x, y-1, len+1, rem});
        }
        return -1;
    }
};
```

## Attempt 3 · 2023-03-24 02:21 IST · Accepted · C++

[submission 920955793](https://leetcode.com/submissions/detail/920955793/) · tests 53/53 · runtime 200 ms (beats 25.0%)

```cpp
class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {

        return solve(grid, k);

        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> visited(n, vector<int>(m,0));
        if(k>= m+n-2){
            return m+n-2;
        }
        queue<vector<int>> qu;
        // push 0,0, currlen, k
        qu.push({0,0,0,k});
        while(!qu.empty()){
            auto t = qu.front();
            qu.pop();
            int x = t[0];
            int y = t[1];
            int len = t[2];
            int rem = t[3];

            if(x<0 || x>=n || y<0 || y>=m){
                continue;
            }
            if(x == n-1 && y==m-1){
                return len;
            }
            if(grid[x][y] ==1){
                if(rem>0){
                    rem--;
                }
                else{
                    continue;
                }
            }
            // check if this cell is already visited
            if(visited[x][y] != 0 && visited[x][y] >= rem){
                continue;
            }
            visited[x][y] = rem;
            qu.push({x+1, y, len+1, rem});
            // qu.push({x-1, y, len+1, rem});
            qu.push({x, y+1, len+1, rem});
            // qu.push({x, y-1, len+1, rem});
        }
        return -1;
    }
    int solve(vector<vector<int>>& grid,int k){
		// At a particular cell we will store the number of obstacles that we can still remove after walking through that cell
        vector<vector<int>> vis(grid.size(),vector<int>(grid[0].size(),-1));
        queue<vector<int>> q;
		
		// queue stores (x,y,current path length,number of obstacles we can still remove)
        q.push({0,0,0,k});
        while(!q.empty()){
            auto t=q.front();
            int x=t[0],y=t[1];
            q.pop();
			
			// Exit if current position is outside of the grid
            if(x<0 || y<0 || x>=grid.size() || y>=grid[0].size()){
                continue;
            }
			
			// Destination found
            if(x==grid.size()-1 && y==grid[0].size()-1)
                return t[2];

            if(grid[x][y]==1){
                if(t[3]>0) // If we encounter an obstacle and we can remove it
                    t[3]--;
                else
                    continue;
            }
			
			// The cell was previously visited by some path and we were able to remove more obstacles from the previous path.
			// Then we don't need to continue on our current path
            if(vis[x][y]!=-1 && vis[x][y]>=t[3])
                continue;
            vis[x][y]=t[3];
            
            q.push({x+1,y,t[2]+1,t[3]});
            q.push({x,y+1,t[2]+1,t[3]});
            q.push({x-1,y,t[2]+1,t[3]});
            q.push({x,y-1,t[2]+1,t[3]});
            
        }
        return -1;
    }
};
```
