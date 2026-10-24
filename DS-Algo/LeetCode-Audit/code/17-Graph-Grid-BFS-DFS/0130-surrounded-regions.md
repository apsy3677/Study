# 130. Surrounded Regions

[Problem](https://leetcode.com/problems/surrounded-regions/) · Medium · Graph: Grid BFS/DFS → Border flood fill

LeetCode tags: array, depth-first-search, breadth-first-search, union-find, matrix

Attempts since Mar 2023: 6 · accepted: 5 · failed before first AC: 0

## Attempt 1 · 2023-03-25 16:44 IST · Accepted · C++

[submission 921806754](https://leetcode.com/submissions/detail/921806754/) · tests 58/58 · runtime 12 ms (beats 5.1%)

```cpp
class Solution {
public:
    vector<vector<int>> diff = {{0,1}, {0,-1}, {1,0}, {-1,0}};

    void dfs(int x, int y, vector<vector<char>>& grid){
        int m = grid.size();
        int n = grid[0].size();

        // if(x<0 || x>=m || y<0 ||y>=n){
        //     // out of bound
        //     return;
        // }
        // if(x == 0 || x == m-1 || y==0 || y==n-1){
        //     // edge of grid
        //     if(grid[x][y] == 'O'){
        //         return false;
        //     }else if(grid[x][y] == 'X'){
        //         return true;
        //     }
        // }
        grid[x][y] = 'E';
        for(auto d:diff){
            int newX = x + d[0];
            int newY = y + d[1];
            if(newX<0 || newX>=m || newY<0 ||newY>=n){
            // out of bound
                continue;
            }
            if(grid[newX][newY] == 'O')
            {
                // grid[newX][newY] = 'E';
                dfs(newX, newY, grid);
            }
        }
        // if(grid[x][y] == 'O')
        //     grid[x][y] = 'X';
        // return true;
    }
    void solve(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if((grid[i][j] == 'O') && (i==0 || i==m-1 || j==0 || j==n-1)){
                    dfs(i,j, grid);
                }
            }
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j] == 'O'){
                    grid[i][j] = 'X';
                }
                else if(grid[i][j] == 'E'){
                    grid[i][j] = 'O';
                }
            }
        }
        // return grid;
        
    }
};
```

## Attempt 2 · 2023-03-25 16:44 IST · Accepted · C++

[submission 921806966](https://leetcode.com/submissions/detail/921806966/) · tests 58/58 · runtime 15 ms (beats 5.1%)

```cpp
class Solution {
public:
    vector<vector<int>> diff = {{0,1}, {0,-1}, {1,0}, {-1,0}};

    void dfs(int x, int y, vector<vector<char>>& grid){
        int m = grid.size();
        int n = grid[0].size();

        grid[x][y] = 'E';
        for(auto d:diff){
            int newX = x + d[0];
            int newY = y + d[1];
            if(newX<0 || newX>=m || newY<0 ||newY>=n){
            // out of bound
                continue;
            }
            if(grid[newX][newY] == 'O')
            {
                dfs(newX, newY, grid);
            }
        }
        // if(grid[x][y] == 'O')
        //     grid[x][y] = 'X';
        // return true;
    }
    void solve(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if((grid[i][j] == 'O') && (i==0 || i==m-1 || j==0 || j==n-1)){
                    dfs(i,j, grid);
                }
            }
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j] == 'O'){
                    grid[i][j] = 'X';
                }
                else if(grid[i][j] == 'E'){
                    grid[i][j] = 'O';
                }
            }
        }
        // return grid;
        
    }
};
```

## Attempt 3 · 2023-04-29 09:56 IST · Accepted · C++

[submission 941379617](https://leetcode.com/submissions/detail/941379617/) · tests 58/58 · runtime 25 ms (beats 5.1%)

```cpp
class Solution {
public:
    vector<vector<int>> diff = {{0,1}, {0,-1}, {1,0}, {-1,0}};

    void dfs(int x, int y, vector<vector<char>>& grid){
        int m = grid.size();
        int n = grid[0].size();

        grid[x][y] = 'E';
        for(auto d:diff){
            int newX = x + d[0];
            int newY = y + d[1];
            if(newX<0 || newX>=m || newY<0 ||newY>=n || grid[newX][newY] == 'X' || grid[newX][newY] == 'E'){
            // out of bound
                continue;
            }
            // if(grid[newX][newY] == 'O')
            // {
                dfs(newX, newY, grid);
            // }
        }
        // if(grid[x][y] == 'O')
        //     grid[x][y] = 'X';
        // return true;
    }
    void solve(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if((grid[i][j] == 'O') && (i==0 || i==m-1 || j==0 || j==n-1)){
                    dfs(i,j, grid);
                }
            }
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j] == 'O'){
                    grid[i][j] = 'X';
                }
                else if(grid[i][j] == 'E'){
                    grid[i][j] = 'O';
                }
            }
        }
        // return grid;
        
    }
};
```

## Attempt 4 · 2023-04-29 09:57 IST · Runtime Error · C++

[submission 941379852](https://leetcode.com/submissions/detail/941379852/) · tests 3/58

Failing input:

```text
[["O","O"],["O","O"]]
```

Expected:

```text
[["O","O"],["O","O"]]
```

Runtime error:

```text
AddressSanitizer:DEADLYSIGNAL
=================================================================
==23==ERROR: AddressSanitizer: stack-overflow on address 0x7fff2270dff8 (pc 0x0000002acb21 bp 0x000000000018 sp 0x7fff2270e000 T0)
==23==ABORTING
```

```cpp
class Solution {
public:
    vector<vector<int>> diff = {{0,1}, {0,-1}, {1,0}, {-1,0}};

    void dfs(int x, int y, vector<vector<char>>& grid){
        int m = grid.size();
        int n = grid[0].size();

        grid[x][y] = 'E';
        for(auto d:diff){
            int newX = x + d[0];
            int newY = y + d[1];
            if(newX<0 || newX>=m || newY<0 ||newY>=n || grid[newX][newY] == 'X' ){
            // out of bound and previosuly visited
                continue;
            }
                dfs(newX, newY, grid);
        }
    }
    void solve(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if((grid[i][j] == 'O') && (i==0 || i==m-1 || j==0 || j==n-1)){
                    dfs(i,j, grid);
                }
            }
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j] == 'O'){
                    grid[i][j] = 'X';
                }
                else if(grid[i][j] == 'E'){
                    grid[i][j] = 'O';
                }
            }
        }
        // return grid;
        
    }
};
```

## Attempt 5 · 2023-04-29 09:58 IST · Accepted · C++

[submission 941380038](https://leetcode.com/submissions/detail/941380038/) · tests 58/58 · runtime 11 ms (beats 5.1%)

```cpp
class Solution {
public:
    vector<vector<int>> diff = {{0,1}, {0,-1}, {1,0}, {-1,0}};

    void dfs(int x, int y, vector<vector<char>>& grid){
        int m = grid.size();
        int n = grid[0].size();

        grid[x][y] = 'E';
        for(auto d:diff){
            int newX = x + d[0];
            int newY = y + d[1];
            if(newX<0 || newX>=m || newY<0 ||newY>=n || grid[newX][newY] == 'X' || grid[newX][newY] == 'E'){
            // out of bound and previosuly visited
                continue;
            }
                dfs(newX, newY, grid);
        }
    }
    void solve(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if((grid[i][j] == 'O') && (i==0 || i==m-1 || j==0 || j==n-1)){
                    dfs(i,j, grid);
                }
            }
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j] == 'O'){
                    grid[i][j] = 'X';
                }
                else if(grid[i][j] == 'E'){
                    grid[i][j] = 'O';
                }
            }
        }
    }
};
```

## Attempt 6 · 2023-04-29 10:18 IST · Accepted · C++

[submission 941385744](https://leetcode.com/submissions/detail/941385744/) · tests 58/58 · runtime 24 ms (beats 5.1%)

```cpp
class Solution {
public:
    vector<vector<int>> diff = {{0,1}, {0,-1}, {1,0}, {-1,0}};

    void dfs(int x, int y, vector<vector<char>>& grid){
        int m = grid.size();
        int n = grid[0].size();
        cout<<"DFS "<<x<<":"<<y<<"|"<<grid[x][y]<<" ";
        grid[x][y] = 'E';
        for(auto d:diff){
            int newX = x + d[0];
            int newY = y + d[1];
            if(newX<0 || newX>=m || newY<0 ||newY>=n || grid[newX][newY] == 'X' || grid[newX][newY] == 'E'){
            // out of bound and previosuly visited
                continue;
            }
                dfs(newX, newY, grid);
        }
    }
    void solve(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        for(int i=0;i<m;i++){
            if(grid[i][0] == 'O'){
                dfs(i,0, grid);
            }
            if( grid[i][n-1] == 'O'){
                dfs(i,n-1, grid);
            }
        }
        for(int i=0;i<n;i++){
            if(grid[0][i] == 'O'){
                dfs(0,i, grid);
            }
            if( grid[m-1][i] == 'O'){
                dfs(m-1,i, grid);
            }
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j] == 'O'){
                    grid[i][j] = 'X';
                }
                else if(grid[i][j] == 'E'){
                    grid[i][j] = 'O';
                }
            }
        }
    }
};
```
