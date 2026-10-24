# 361. Bomb Enemy

[Problem](https://leetcode.com/problems/bomb-enemy/) · Medium · DP: Grid / 2D → Row/column precompute

LeetCode tags: array, dynamic-programming, matrix

Attempts since Mar 2023: 4 · accepted: 1 · failed before first AC: 3

## Attempt 1 · 2023-03-16 17:43 IST · Wrong Answer · C++

[submission 916248914](https://leetcode.com/submissions/detail/916248914/) · tests 9/40

Failing input:

```text
[["W","W","W"],["0","0","0"],["E","E","E"]]
```

Expected:

```text
1
```

Your output:

```text
2
```

```cpp
class Solution {
public:
    vector<pair<int,int>> diff = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    int n,m;
    int dfs(int x, int y, bool horizontal, vector<vector<char>>& grid, vector<vector<bool>> &visited){
        
        if(grid[x][y] == 'W'){
            return 0;
        }
        visited[x][y] = true;
        int ans = 0;

        ans = grid[x][y] == 'E' ? 1: 0;
        if(horizontal){
            
            for(int i=0;i<2;i++){
                int dy = y + diff[i].second;
                if(dy < 0 || dy>=m){
                    continue;
                }
                if(visited[x][dy] && grid[x][dy] != 'W'){

                    // call dfs x, dy
                    // if(grid[x][dy] == 'E') ans++;
                    ans += dfs(x,dy,horizontal, grid, visited);
                }
            }
        }
        else{
            for(int i=2;i<diff.size();i++){
                int dx = x + diff[i].first;
                if(dx < 0 || dx>=n || y < 0 || y>=m){
                    continue;
                }
                if(!visited[dx][y] && grid[dx][y] != 'W'){

                    // call dfs x, dy
                    // if(grid[dx][y] == 'E') ans++;
                    ans += dfs(dx,y,horizontal, grid, visited);
                }
            }
        }
        visited[x][y] = false;
        return ans;
    }

    int maxKilledEnemies(vector<vector<char>>& grid) {
        n = grid.size(), m = grid[0].size();

        vector<vector<bool>> visited(n, vector<bool>(m, false));

        int ans = 0;

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j] != '0'){
                    int hEnemies = dfs(i,j,true, grid, visited);
                    int vEnemies = dfs(i,j,false,grid, visited);
                    cout<<hEnemies<<":"<<vEnemies<<"|";
                    ans = max(ans, hEnemies + vEnemies);
                }
            }
        }

        return ans;
    }
};
```

## Attempt 2 · 2023-03-16 17:47 IST · Time Limit Exceeded · C++

[submission 916250425](https://leetcode.com/submissions/detail/916250425/) · tests 39/40

Failing input:

```text
[["0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","E","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0 ... [1000601 more chars]
```

Expected:

```text
22
```

```cpp
class Solution {
public:
    vector<pair<int,int>> diff = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    int n,m;
    int dfs(int x, int y, bool horizontal, vector<vector<char>>& grid, vector<vector<bool>> &visited){
        
        if(grid[x][y] == 'W'){
            return 0;
        }
        visited[x][y] = true;
        int ans = 0;

        ans = grid[x][y] == 'E' ? 1: 0;
        if(horizontal){
            
            for(int i=0;i<2;i++){
                int dy = y + diff[i].second;
                if(dy < 0 || dy>=m){
                    continue;
                }
                if(!visited[x][dy] && grid[x][dy] != 'W'){

                    // call dfs x, dy
                    // if(grid[x][dy] == 'E') ans++;
                    ans += dfs(x,dy,horizontal, grid, visited);
                }
            }
        }
        else{
            for(int i=2;i<diff.size();i++){
                int dx = x + diff[i].first;
                if(dx < 0 || dx>=n || y < 0 || y>=m){
                    continue;
                }
                if(!visited[dx][y] && grid[dx][y] != 'W'){

                    // call dfs x, dy
                    // if(grid[dx][y] == 'E') ans++;
                    ans += dfs(dx,y,horizontal, grid, visited);
                }
            }
        }
        visited[x][y] = false;
        return ans;
    }

    int maxKilledEnemies(vector<vector<char>>& grid) {
        n = grid.size(), m = grid[0].size();

        vector<vector<bool>> visited(n, vector<bool>(m, false));

        int ans = 0;

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j] == '0'){
                    int hEnemies = dfs(i,j,true, grid, visited);
                    int vEnemies = dfs(i,j,false,grid, visited);
                    cout<<"("<<i<<","<<j<<")";
                    cout<<hEnemies<<":"<<vEnemies<<"|";
                    ans = max(ans, hEnemies + vEnemies);
                }
            }
        }

        return ans;
    }
};
```

## Attempt 3 · 2023-03-16 17:47 IST · Time Limit Exceeded · C++

[submission 916250697](https://leetcode.com/submissions/detail/916250697/) · tests 39/40

Failing input:

```text
[["0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","E","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0 ... [1000601 more chars]
```

Expected:

```text
22
```

```cpp
class Solution {
public:
    vector<pair<int,int>> diff = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    int n,m;
    int dfs(int x, int y, bool horizontal, vector<vector<char>>& grid, vector<vector<bool>> &visited){
        
        if(grid[x][y] == 'W'){
            return 0;
        }
        visited[x][y] = true;
        int ans = 0;

        ans = grid[x][y] == 'E' ? 1: 0;
        if(horizontal){
            
            for(int i=0;i<2;i++){
                int dy = y + diff[i].second;
                if(dy < 0 || dy>=m){
                    continue;
                }
                if(!visited[x][dy] && grid[x][dy] != 'W'){

                    // call dfs x, dy
                    // if(grid[x][dy] == 'E') ans++;
                    ans += dfs(x,dy,horizontal, grid, visited);
                }
            }
        }
        else{
            for(int i=2;i<diff.size();i++){
                int dx = x + diff[i].first;
                if(dx < 0 || dx>=n || y < 0 || y>=m){
                    continue;
                }
                if(!visited[dx][y] && grid[dx][y] != 'W'){

                    // call dfs x, dy
                    // if(grid[dx][y] == 'E') ans++;
                    ans += dfs(dx,y,horizontal, grid, visited);
                }
            }
        }
        visited[x][y] = false;
        return ans;
    }

    int maxKilledEnemies(vector<vector<char>>& grid) {
        n = grid.size(), m = grid[0].size();

        vector<vector<bool>> visited(n, vector<bool>(m, false));

        int ans = 0;

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j] == '0'){
                    int hEnemies = dfs(i,j,true, grid, visited);
                    int vEnemies = dfs(i,j,false,grid, visited);
                    // cout<<"("<<i<<","<<j<<")";
                    // cout<<hEnemies<<":"<<vEnemies<<"|";
                    ans = max(ans, hEnemies + vEnemies);
                }
            }
        }

        return ans;
    }
};
```

## Attempt 4 · 2023-03-30 23:20 IST · Accepted · C++

[submission 924963710](https://leetcode.com/submissions/detail/924963710/) · tests 40/40 · runtime 1941 ms (beats 5.9%)

```cpp
class Solution {
public:
    vector<pair<int,int>> diff = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    int n,m;
    int dfs(int x, int y, bool horizontal, vector<vector<char>>& grid, vector<vector<bool>> &visited){
        
        if(grid[x][y] == 'W'){
            return 0;
        }
        visited[x][y] = true;
        int ans = 0;

        ans = grid[x][y] == 'E' ? 1: 0;
        if(horizontal){
            
            for(int i=0;i<2;i++){
                int dy = y + diff[i].second;
                if(dy < 0 || dy>=m){
                    continue;
                }
                if(!visited[x][dy] && grid[x][dy] != 'W'){

                    // call dfs x, dy
                    // if(grid[x][dy] == 'E') ans++;
                    ans += dfs(x,dy,horizontal, grid, visited);
                }
            }
        }
        else{
            for(int i=2;i<diff.size();i++){
                int dx = x + diff[i].first;
                if(dx < 0 || dx>=n || y < 0 || y>=m){
                    continue;
                }
                if(!visited[dx][y] && grid[dx][y] != 'W'){

                    // call dfs x, dy
                    // if(grid[dx][y] == 'E') ans++;
                    ans += dfs(dx,y,horizontal, grid, visited);
                }
            }
        }
        visited[x][y] = false;
        return ans;
    }

    int maxKilledEnemies(vector<vector<char>>& grid) {
        n = grid.size(), m = grid[0].size();

        vector<vector<bool>> visited(n, vector<bool>(m, false));

        int ans = 0;

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j] == '0'){
                    // int hEnemies = dfs(i,j,true, grid, visited);
                    // int vEnemies = dfs(i,j,false,grid, visited);
                    // cout<<"("<<i<<","<<j<<")";
                    // cout<<hEnemies<<":"<<vEnemies<<"|";
                    int killed = killEnemies(i,j,grid);
                    ans = max(ans, killed);
                    // ans = max(ans, hEnemies + vEnemies);
                }
            }
        }

        return ans;
    }
    int killEnemies(int row, int col, vector<vector<char>>& grid) {
        int enemyCount = 0;
        // look to the left side of the cell
        for (int c = col - 1; c >= 0; --c) {
            if (grid[row][c] == 'W')
                break;
            else if (grid[row][c] == 'E')
                enemyCount += 1;
        }

        // look to the right side of the cell
        for (int c = col + 1; c < m; ++c) {
            if (grid[row][c] == 'W')
                break;
            else if (grid[row][c] == 'E')
                enemyCount += 1;
        }

        // look to the up side of the cell
        for (int r = row - 1; r >= 0; --r) {
            if (grid[r][col] == 'W')
                break;
            else if (grid[r][col] == 'E')
                enemyCount += 1;
        }

        // look to the down side of the cell
        for (int r = row + 1; r < n; ++r) {
            if (grid[r][col] == 'W')
                break;
            else if (grid[r][col] == 'E')
                enemyCount += 1;
        }

        return enemyCount;
    }
};
```
