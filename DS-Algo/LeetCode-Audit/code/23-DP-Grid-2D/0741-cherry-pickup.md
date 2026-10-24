# 741. Cherry Pickup

[Problem](https://leetcode.com/problems/cherry-pickup/) · Hard · DP: Grid / 2D → Two walkers (3D state)

LeetCode tags: array, dynamic-programming, matrix

Attempts since Mar 2023: 13 · accepted: 4 · failed before first AC: 2

## Attempt 1 · 2023-03-12 11:53 IST · Wrong Answer · Java

[submission 913652420](https://leetcode.com/submissions/detail/913652420/) · tests 49/59

Failing input:

```text
[[1,1,1,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,1],[1,0,0,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,1,1,1]]
```

Expected:

```text
15
```

Your output:

```text
14
```

```java
class Solution {
    public int cherryPickup(int[][] grid) {
        int ans = 0;
        int[][] path = bestPath(grid);
        if (path == null) return 0;
        for (int[] step: path) {
            ans += grid[step[0]][step[1]];
            grid[step[0]][step[1]] = 0;
        }

        for (int[] step: bestPath(grid))
            ans += grid[step[0]][step[1]];

        return ans;
    }
    
    public int[][] bestPath(int[][] grid) {
        int N = grid.length;
        int[][] dp = new int[N][N];
        for (int[] row: dp) Arrays.fill(row, Integer.MIN_VALUE);
        dp[N-1][N-1] = grid[N-1][N-1];
        for (int i = N-1; i >= 0; --i) {
            for (int j = N-1; j >= 0; --j) {
                if (grid[i][j] >= 0 && (i != N-1 || j != N-1)) {
                    dp[i][j] = Math.max(i+1 < N ? dp[i+1][j] : Integer.MIN_VALUE,
                                        j+1 < N ? dp[i][j+1] : Integer.MIN_VALUE);
                    dp[i][j] += grid[i][j];
                }
            }
        }
        if (dp[0][0] < 0) return null;
        int[][] ans = new int[2*N - 1][2];
        int i = 0, j = 0, t = 0;
        while (i != N-1 || j != N-1) {
            if (j+1 == N || i+1 < N && dp[i+1][j] >= dp[i][j+1]) i++;
            else j++;

            ans[t][0] = i;
            ans[t][1] = j;
            t++;
        }
        return ans;
    }
}
```

## Attempt 2 · 2023-03-12 14:29 IST · Wrong Answer · C++

[submission 913718323](https://leetcode.com/submissions/detail/913718323/) · tests 48/59

Failing input:

```text
[[1,1,-1,1,1],[1,1,1,1,1],[-1,1,1,-1,-1],[0,1,1,-1,0],[1,0,-1,1,0]]
```

Expected:

```text
0
```

Your output:

```text
-2147483638
```

```cpp
class Solution {
public:
    // int dp[55][55][55][55];
    // vector<vector<vector<vector<int>>>> dp;
    int n;
    
    int recur(int x, int y, int x1, int y1, vector<vector<int>>& grid,
    vector<vector<vector<vector<int>>>> &dp){
        if(x>=n || y>=n || x1>=n ||y1>=n || grid[x][y]==-1 ||grid[x1][y1]==-1 ){
            return INT_MIN;
        }
        if(x==n-1 && y==n-1)
            return grid[x][y];
        if(x1==n-1 && y1==n-1)
            return grid[x1][y1];
        if(dp[x][y][x1][y1] != INT_MIN)
            return dp[x][y][x1][y1];
        
        int ans = grid[x][y] + (x1 ==x && y==y1 ? 0 : grid[x1][y1]);

        ans += max(max(recur(x,y+1,x1,y1+1,grid,dp), recur(x,y+1,x1+1,y1,grid,dp)), 
                max(recur(x+1,y,x1,y1+1,grid,dp), recur(x+1,y,x1+1,y1,grid,dp)));
        dp[x][y][x1][y1] = ans;
        return ans;
    }
    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();
        
        // vector<vector<vector<vector<int>>>> dp(n+1, vector<int>(n+1, vector<int>(n+1, vector<int>(n+1, INT_MIN))));
        vector<vector<vector<vector<int>>>> dp(n+1, vector<vector<vector<int>>>(n+1, vector<vector<int>>(n+1, vector<int>(n+1, INT_MIN))));
        
        int ans = recur(0,0,0,0,grid,dp);
        ans = (ans==-2147483645) ? 0 : ans;
        return ans;
    }
};
```

## Attempt 3 · 2023-03-12 14:30 IST · Accepted · C++

[submission 913718543](https://leetcode.com/submissions/detail/913718543/) · tests 59/59 · runtime 832 ms (beats 5.1%)

```cpp
class Solution {
public:
    // int dp[55][55][55][55];
    // vector<vector<vector<vector<int>>>> dp;
    int n;
    
    int recur(int x, int y, int x1, int y1, vector<vector<int>>& grid,
    vector<vector<vector<vector<int>>>> &dp){
        if(x>=n || y>=n || x1>=n ||y1>=n || grid[x][y]==-1 ||grid[x1][y1]==-1 ){
            return INT_MIN;
        }
        if(x==n-1 && y==n-1)
            return grid[x][y];
        if(x1==n-1 && y1==n-1)
            return grid[x1][y1];
        if(dp[x][y][x1][y1] != INT_MIN)
            return dp[x][y][x1][y1];
        
        int ans = grid[x][y] + (x1 ==x && y==y1 ? 0 : grid[x1][y1]);

        ans += max(max(recur(x,y+1,x1,y1+1,grid,dp), recur(x,y+1,x1+1,y1,grid,dp)), 
                max(recur(x+1,y,x1,y1+1,grid,dp), recur(x+1,y,x1+1,y1,grid,dp)));
        dp[x][y][x1][y1] = ans;
        return ans;
    }
    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();
        
        // vector<vector<vector<vector<int>>>> dp(n+1, vector<int>(n+1, vector<int>(n+1, vector<int>(n+1, INT_MIN))));
        vector<vector<vector<vector<int>>>> dp(n+1, vector<vector<vector<int>>>(n+1, vector<vector<int>>(n+1, vector<int>(n+1, INT_MIN))));
        
        int ans = recur(0,0,0,0,grid,dp);
        ans = (ans<0) ? 0 : ans;
        return ans;
    }
};
```

## Attempt 4 · 2023-03-23 19:38 IST · Accepted · C++

[submission 920744257](https://leetcode.com/submissions/detail/920744257/) · tests 59/59 · runtime 754 ms (beats 5.1%)

```cpp
class Solution {
public:
    // int dp[55][55][55][55];
    // vector<vector<vector<vector<int>>>> dp;
    int n;
    
    int recur(int x, int y, int x1, int y1, vector<vector<int>>& grid,
    vector<vector<vector<vector<int>>>> &dp){
        if(x>=n || y>=n || x1>=n ||y1>=n || grid[x][y]==-1 ||grid[x1][y1]==-1 ){
            return INT_MIN;
        }
        if(x==n-1 && y==n-1)
            return grid[x][y];
        if(x1==n-1 && y1==n-1)
            return grid[x1][y1];
        if(dp[x][y][x1][y1] != INT_MIN)
            return dp[x][y][x1][y1];
        
        int ans = grid[x][y] + (x1 ==x && y==y1 ? 0 : grid[x1][y1]);

        ans += max(max(recur(x,y+1,x1,y1+1,grid,dp), recur(x,y+1,x1+1,y1,grid,dp)), 
                max(recur(x+1,y,x1,y1+1,grid,dp), recur(x+1,y,x1+1,y1,grid,dp)));
        dp[x][y][x1][y1] = ans;
        return ans;
    }
    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();
        
        // vector<vector<vector<vector<int>>>> dp(n+1, vector<int>(n+1, vector<int>(n+1, vector<int>(n+1, INT_MIN))));
        vector<vector<vector<vector<int>>>> dp(n+1, vector<vector<vector<int>>>(n+1, vector<vector<int>>(n+1, vector<int>(n+1, INT_MIN))));
        
        int ans = recur(0,0,0,0,grid,dp);
        ans = (ans<0) ? 0 : ans;
        return ans;
    }
};
```

## Attempt 5 · 2023-03-23 20:19 IST · Wrong Answer · C++

[submission 920765466](https://leetcode.com/submissions/detail/920765466/) · tests 3/59

Failing input:

```text
[[1]]
```

Expected:

```text
1
```

Your output:

```text
0
```

```cpp
class Solution {
    typedef vector<vector<vector<int>>> VVVI;
    typedef vector<vector<int>> VVI;
    typedef vector<int> VI;
    bool reached = false;
public:
    // int dp[55][55][55][55];
    // vector<vector<vector<vector<int>>>> dp;
    int n;
    
    int recur(int x, int y, int x1, int y1, vector<vector<int>>& grid,
    vector<vector<vector<vector<int>>>> &dp){
        if(x>=n || y>=n || x1>=n ||y1>=n || grid[x][y]==-1 ||grid[x1][y1]==-1 ){
            return INT_MIN;
        }
        if(x==n-1 && y==n-1)
            return grid[x][y];
        if(x1==n-1 && y1==n-1)
            return grid[x1][y1];
        if(dp[x][y][x1][y1] != INT_MIN)
            return dp[x][y][x1][y1];
        
        int ans = grid[x][y] + (x1 ==x && y==y1 ? 0 : grid[x1][y1]);

        ans += max(max(recur(x,y+1,x1,y1+1,grid,dp), recur(x,y+1,x1+1,y1,grid,dp)), 
                max(recur(x+1,y,x1,y1+1,grid,dp), recur(x+1,y,x1+1,y1,grid,dp)));
        dp[x][y][x1][y1] = ans;
        return ans;
    }
    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();
        
        // vector<vector<vector<vector<int>>>> dp(n+1, vector<int>(n+1, vector<int>(n+1, vector<int>(n+1, INT_MIN))));
        vector<vector<vector<vector<int>>>> dp(n+1, vector<vector<vector<int>>>(n+1, vector<vector<int>>(n+1, vector<int>(n+1, INT_MIN))));

        VVVI dpp = VVVI(n+1, VVI(n+1, VI(n+1, INT_MIN)));
        
        dfs(0, 0, 0, grid ,dpp);
        cout<<" reached "<< reached<<" ";
        // ans = recur(0,0,0,0,grid,dp);
        int ans = dpp[0][0][0];
        ans = (ans<0) ? 0 : ans;
        return ans;
    }

    int dfs(int r1, int c1, int c2, vector<vector<int>>& grid, VVVI &dp){
        int r2 = r1+c1-c2;
        // we are moving both together therefore total steps will be same
        // r1+c1 = r2+c2
        int n = grid.size();

        if(r1>=n || r2>=n || c1>=n && c2>=n || grid[r1][c1]==-1 || grid[r2][c2]==-1 ){
            return INT_MIN;
        }

        if(r1==n-1 && c1==n-1){
            // both will be here at this time
            reached = true;
            return grid[r1][c1];
        }
        if(dp[r1][c1][c2] != INT_MIN){
            return dp[r1][c1][c2];
        }
        int ans = grid[r1][c1] + (r1==r2 && c1==c2 ? 0: grid[r2][c2]);

        ans += max(max(dfs(r1+1,c1,c2,grid,dp), dfs(r1+1,c1,c2+1,grid,dp)), 
                   max(dfs(r1,c1+1,c2,grid,dp), dfs(r1,c1+1,c2+1,grid,dp)));

        cout<< r1<<" "<<c1<<" "<<c2<<"|"<<ans <<":: "; 
        dp[r1][c1][c2] = ans;

        return ans;
    }
};
```

## Attempt 6 · 2023-03-23 20:20 IST · Runtime Error · C++

[submission 920766139](https://leetcode.com/submissions/detail/920766139/) · tests 4/59

Failing input:

```text
[[1,1,1,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,1],[1,0,0,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,1,1,1]]
```

Expected:

```text
15
```

Runtime error:

```text
Line 67: Char 13: runtime error: signed integer overflow: -1094795585 + -2147483648 cannot be represented in type 'int' (solution.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:76:13
```

```cpp
class Solution {
    typedef vector<vector<vector<int>>> VVVI;
    typedef vector<vector<int>> VVI;
    typedef vector<int> VI;
    bool reached = false;
public:
    // int dp[55][55][55][55];
    // vector<vector<vector<vector<int>>>> dp;
    int n;
    
    int recur(int x, int y, int x1, int y1, vector<vector<int>>& grid,
    vector<vector<vector<vector<int>>>> &dp){
        if(x>=n || y>=n || x1>=n ||y1>=n || grid[x][y]==-1 ||grid[x1][y1]==-1 ){
            return INT_MIN;
        }
        if(x==n-1 && y==n-1)
            return grid[x][y];
        if(x1==n-1 && y1==n-1)
            return grid[x1][y1];
        if(dp[x][y][x1][y1] != INT_MIN)
            return dp[x][y][x1][y1];
        
        int ans = grid[x][y] + (x1 ==x && y==y1 ? 0 : grid[x1][y1]);

        ans += max(max(recur(x,y+1,x1,y1+1,grid,dp), recur(x,y+1,x1+1,y1,grid,dp)), 
                max(recur(x+1,y,x1,y1+1,grid,dp), recur(x+1,y,x1+1,y1,grid,dp)));
        dp[x][y][x1][y1] = ans;
        return ans;
    }
    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();
        
        // vector<vector<vector<vector<int>>>> dp(n+1, vector<int>(n+1, vector<int>(n+1, vector<int>(n+1, INT_MIN))));
        vector<vector<vector<vector<int>>>> dp(n+1, vector<vector<vector<int>>>(n+1, vector<vector<int>>(n+1, vector<int>(n+1, INT_MIN))));

        VVVI dpp = VVVI(n+1, VVI(n+1, VI(n+1, INT_MIN)));
        
        dfs(0, 0, 0, grid ,dpp);
        cout<<" reached "<< reached<<" ";
        // ans = recur(0,0,0,0,grid,dp);
        int ans = dpp[0][0][0];
        ans = (ans<0) ? 0 : ans;
        return ans;
    }

    int dfs(int r1, int c1, int c2, vector<vector<int>>& grid, VVVI &dp){
        int r2 = r1+c1-c2;
        // we are moving both together therefore total steps will be same
        // r1+c1 = r2+c2
        int n = grid.size();

        if(r1>=n || r2>=n || c1>=n && c2>=n || grid[r1][c1]==-1 || grid[r2][c2]==-1 ){
            return INT_MIN;
        }

        if(r1==n-1 && c1==n-1){
            // both will be here at this time
            reached = true;
            dp[r1][c1][c2] = grid[r1][c1];
            return grid[r1][c1];
        }
        if(dp[r1][c1][c2] != INT_MIN){
            return dp[r1][c1][c2];
        }
        int ans = grid[r1][c1] + (r1==r2 && c1==c2 ? 0: grid[r2][c2]);

        ans += max(max(dfs(r1+1,c1,c2,grid,dp), dfs(r1+1,c1,c2+1,grid,dp)), 
                   max(dfs(r1,c1+1,c2,grid,dp), dfs(r1,c1+1,c2+1,grid,dp)));

        cout<< r1<<" "<<c1<<" "<<c2<<"|"<<ans <<":: "; 
        dp[r1][c1][c2] = ans;

        return ans;
    }
};
```

## Attempt 7 · 2023-03-23 20:45 IST · Runtime Error · C++

[submission 920779356](https://leetcode.com/submissions/detail/920779356/) · tests 4/59

Failing input:

```text
[[1,1,1,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,1],[1,0,0,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,1,1,1]]
```

Expected:

```text
15
```

Runtime error:

```text
Line 65: Char 14: runtime error: signed integer overflow: -1094795585 + -2147483648 cannot be represented in type 'int' (solution.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:74:14
```

```cpp
class Solution {
    typedef vector<vector<vector<int>>> VVVI;
    typedef vector<vector<int>> VVI;
    typedef vector<int> VI;
    bool reached = false;
public:
    // int dp[55][55][55][55];
    // vector<vector<vector<vector<int>>>> dp;
    int n;
    
    int recur(int x, int y, int x1, int y1, vector<vector<int>>& grid,
    vector<vector<vector<vector<int>>>> &dp){
        if(x>=n || y>=n || x1>=n ||y1>=n || grid[x][y]==-1 ||grid[x1][y1]==-1 ){
            return INT_MIN;
        }
        if(x==n-1 && y==n-1)
            return grid[x][y];
        if(x1==n-1 && y1==n-1)
            return grid[x1][y1];
        if(dp[x][y][x1][y1] != INT_MIN)
            return dp[x][y][x1][y1];
        
        int ans = grid[x][y] + (x1 ==x && y==y1 ? 0 : grid[x1][y1]);

        ans += max(max(recur(x,y+1,x1,y1+1,grid,dp), recur(x,y+1,x1+1,y1,grid,dp)), 
                max(recur(x+1,y,x1,y1+1,grid,dp), recur(x+1,y,x1+1,y1,grid,dp)));
        dp[x][y][x1][y1] = ans;
        return ans;
    }
    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();
        
        // vector<vector<vector<vector<int>>>> dp(n+1, vector<int>(n+1, vector<int>(n+1, vector<int>(n+1, INT_MIN))));
        // vector<vector<vector<vector<int>>>> dp(n+1, vector<vector<vector<int>>>(n+1, vector<vector<int>>(n+1, vector<int>(n+1, INT_MIN))));

        VVVI dpp = VVVI(n+1, VVI(n+1, VI(n+1, INT_MIN)));

        // ans = recur(0,0,0,0,grid,dp);
        int ans = dfs(0, 0, 0, grid ,dpp);;
        ans = (ans<0) ? 0 : ans;
        return ans;
    }

    int dfs(int r1, int c1, int c2, vector<vector<int>>& grid, VVVI &dp){
        int r2 = r1+c1-c2;
        // we are moving both together therefore total steps will be same
        // r1+c1 = r2+c2
        int n = grid.size();

        if(r1>=n || r2>=n || c1>=n && c2>=n || grid[r1][c1]==-1 || grid[r2][c2]==-1 ){
            return INT_MIN;
        }

        if(r1==n-1 && c1==n-1){
            // both will be here at this time
            // reached = true;
            dp[r1][c1][c2] = grid[r1][c1];
            return grid[r1][c1];
        }
        if(dp[r1][c1][c2] != INT_MIN){
            return dp[r1][c1][c2];
        }
        int ans = grid[r1][c1] + (r1==r2 && c1==c2 ? 0: grid[r2][c2]);

        ans  += max(max(dfs(r1+1,c1,c2,grid,dp), dfs(r1+1,c1,c2+1,grid,dp)), 
                   max(dfs(r1,c1+1,c2,grid,dp), dfs(r1,c1+1,c2+1,grid,dp)));

        // cout<< r1<<" "<<c1<<" "<<c2<<"|"<<ans <<":: "; 
        dp[r1][c1][c2] = ans;

        return ans;
    }
};
```

## Attempt 8 · 2023-03-23 20:47 IST · Runtime Error · C++

[submission 920780304](https://leetcode.com/submissions/detail/920780304/) · tests 4/59

Failing input:

```text
[[1,1,1,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,1],[1,0,0,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,1,1,1]]
```

Expected:

```text
15
```

Runtime error:

```text
Line 65: Char 14: runtime error: signed integer overflow: -1094795585 + -2147483648 cannot be represented in type 'int' (solution.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:74:14
```

```cpp
class Solution {
    typedef vector<vector<vector<int>>> VVVI;
    typedef vector<vector<int>> VVI;
    typedef vector<int> VI;
    bool reached = false;
public:
    // int dp[55][55][55][55];
    // vector<vector<vector<vector<int>>>> dp;
    int n;
    
    int recur(int x, int y, int x1, int y1, vector<vector<int>>& grid,
    vector<vector<vector<vector<int>>>> &dp){
        if(x>=n || y>=n || x1>=n ||y1>=n || grid[x][y]==-1 ||grid[x1][y1]==-1 ){
            return INT_MIN;
        }
        if(x==n-1 && y==n-1)
            return grid[x][y];
        if(x1==n-1 && y1==n-1)
            return grid[x1][y1];
        if(dp[x][y][x1][y1] != INT_MIN)
            return dp[x][y][x1][y1];
        
        int ans = grid[x][y] + (x1 ==x && y==y1 ? 0 : grid[x1][y1]);

        ans += max(max(recur(x,y+1,x1,y1+1,grid,dp), recur(x,y+1,x1+1,y1,grid,dp)), 
                max(recur(x+1,y,x1,y1+1,grid,dp), recur(x+1,y,x1+1,y1,grid,dp)));
        dp[x][y][x1][y1] = ans;
        return ans;
    }
    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();
        
        // vector<vector<vector<vector<int>>>> dp(n+1, vector<int>(n+1, vector<int>(n+1, vector<int>(n+1, INT_MIN))));
        // vector<vector<vector<vector<int>>>> dp(n+1, vector<vector<vector<int>>>(n+1, vector<vector<int>>(n+1, vector<int>(n+1, INT_MIN))));

        VVVI dpp = VVVI(n+1, VVI(n+1, VI(n+1, INT_MIN)));

        // ans = recur(0,0,0,0,grid,dp);
        int ans = dfs(0, 0, 0, grid ,dpp);;
        ans = (ans<0) ? 0 : ans;
        return ans;
    }

    int dfs(int r1, int c1, int c2, vector<vector<int>>& grid, VVVI &dp){
        int r2 = r1+c1-c2;
        // we are moving both together therefore total steps will be same
        // r1+c1 = r2+c2
        int n = grid.size();

        if(r1>=n || r2>=n || c1>=n && c2>=n || grid[r1][c1]==-1 || grid[r2][c2]==-1 ){
            return INT_MIN;
        }

        if(r1==n-1 && c1==n-1){
            // both will be here at this time
            // reached = true;
            // dp[r1][c1][c2] = grid[r1][c1];
            return grid[r1][c1];
        }
        if(dp[r1][c1][c2] != INT_MIN){
            return dp[r1][c1][c2];
        }
        int ans = grid[r1][c1] + (r1==r2 && c1==c2 ? 0: grid[r2][c2]);

        ans  += max(max(dfs(r1+1,c1,c2,grid,dp), dfs(r1+1,c1,c2+1,grid,dp)), 
                   max(dfs(r1,c1+1,c2,grid,dp), dfs(r1,c1+1,c2+1,grid,dp)));

        // cout<< r1<<" "<<c1<<" "<<c2<<"|"<<ans <<":: "; 
        dp[r1][c1][c2] = ans;

        return ans;
    }
};
```

## Attempt 9 · 2023-03-25 02:24 IST · Runtime Error · C++

[submission 921516464](https://leetcode.com/submissions/detail/921516464/) · tests 4/59

Failing input:

```text
[[1,1,1,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,1],[1,0,0,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,1,1,1]]
```

Expected:

```text
15
```

Runtime error:

```text
=================================================================
==32==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x603000000300 at pc 0x0000003470db bp 0x7ffc1681f8c0 sp 0x7ffc1681f8b8
READ of size 4 at 0x603000000300 thread T0
    #15 0x7f85898a60b2  (/lib/x86_64-linux-gnu/libc.so.6+0x270b2)
0x603000000300 is located 0 bytes to the right of 32-byte region [0x6030000002e0,0x6030000 ... [1534 more chars]
```

```cpp
class Solution {
    typedef vector<vector<vector<int>>> VVVI;
    typedef vector<vector<int>> VVI;
    typedef vector<int> VI;
    bool reached = false;
public:
    // int dp[55][55][55][55];
    // vector<vector<vector<vector<int>>>> dp;
    int n;
    
    int recur(int x, int y, int x1, int y1, vector<vector<int>>& grid,
    vector<vector<vector<vector<int>>>> &dp){
        if(x>=n || y>=n || x1>=n ||y1>=n || grid[x][y]==-1 ||grid[x1][y1]==-1 ){
            return INT_MIN;
        }
        if(x==n-1 && y==n-1)
            return grid[x][y];
        if(x1==n-1 && y1==n-1)
            return grid[x1][y1];
        if(dp[x][y][x1][y1] != INT_MIN)
            return dp[x][y][x1][y1];
        
        int ans = grid[x][y] + (x1 ==x && y==y1 ? 0 : grid[x1][y1]);

        ans += max(max(recur(x,y+1,x1,y1+1,grid,dp), recur(x,y+1,x1+1,y1,grid,dp)), 
                max(recur(x+1,y,x1,y1+1,grid,dp), recur(x+1,y,x1+1,y1,grid,dp)));
        dp[x][y][x1][y1] = ans;
        return ans;
    }
    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();
        
        // vector<vector<vector<vector<int>>>> dp(n+1, vector<int>(n+1, vector<int>(n+1, vector<int>(n+1, INT_MIN))));
        // vector<vector<vector<vector<int>>>> dp(n+1, vector<vector<vector<int>>>(n+1, vector<vector<int>>(n+1, vector<int>(n+1, INT_MIN))));

        VVVI dpp = VVVI(n+1, VVI(n+1, VI(n+1, INT_MIN)));

        // ans = recur(0,0,0,0,grid,dp);
        int ans = dfs(0, 0, 0, grid ,dpp);;
        ans = (ans<0) ? 0 : ans;
        return ans;
    }

    int dfs(int r1, int c1, int c2, vector<vector<int>>& grid, VVVI &dp){
        int r2 = r1+c1-c2;
        // we are moving both together therefore total steps will be same
        // r1+c1 = r2+c2
        int n = grid.size();

        if(r1>=n || r2>=n || c1>=n && c2>=n || grid[r1][c1]==-1 || grid[r2][c2]==-1 ){
            return INT_MIN;
        }

        if(r1==n-1 && c1==n-1){
            // both will be here at this time
            // reached = true;
            // dp[r1][c1][c2] = grid[r1][c1];
            return grid[r1][c1];
        }
        if(dp[r1][c1][c2] != INT_MIN){
            return dp[r1][c1][c2];
        }
        long long ans = grid[r1][c1] + (r1==r2 && c1==c2 ? 0: grid[r2][c2]);

        ans  += (long long)max(max(dfs(r1+1,c1,c2,grid,dp), dfs(r1+1,c1,c2+1,grid,dp)), 
                   max(dfs(r1,c1+1,c2,grid,dp), dfs(r1,c1+1,c2+1,grid,dp)));

        // cout<< r1<<" "<<c1<<" "<<c2<<"|"<<ans <<":: "; 
        dp[r1][c1][c2] = ans;

        return ans;
    }
};
```

## Attempt 10 · 2023-05-02 07:58 IST · Runtime Error · C++

[submission 942952292](https://leetcode.com/submissions/detail/942952292/) · tests 4/59

Failing input:

```text
[[1,1,1,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,1],[1,0,0,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,1,1,1]]
```

Expected:

```text
15
```

Runtime error:

```text
=================================================================
==22==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x603000000300 at pc 0x00000034ef0b bp 0x7fffc5c93d60 sp 0x7fffc5c93d58
READ of size 4 at 0x603000000300 thread T0
    #15 0x7fe217d23082  (/lib/x86_64-linux-gnu/libc.so.6+0x24082)
0x603000000300 is located 0 bytes to the right of 32-byte region [0x6030000002e0,0x6030000 ... [1534 more chars]
```

```cpp
class Solution {
    typedef vector<vector<vector<int>>> VVVI;
    typedef vector<vector<int>> VVI;
    typedef vector<int> VI;
    bool reached = false;
public:
    VVVI memo;
    // int dp[55][55][55][55];
    // vector<vector<vector<vector<int>>>> dp;
    int n,m;
    int striver(int r, int c1, int c2, vector<vector<int>>& grid){
        // base case
        if(c1 <0 || c2< 0 || c1 >=m || c2>=m){
            // out of bound
            return -1e8;
        }
        if(r == n-1){
            return memo[r][c1][c2] = c1 == c2 ? grid[r][c1] : grid[r][c1] + grid[r][c2];
        }
        if(memo[r][c1][c2] != -1) return memo[r][c1][c2];

        int maxi = -1e8;
        for(int nc1=-1 ; nc1<=1;nc1++){
            for(int nc2=-1; nc2<=1;nc2++){
                int total = 0;
                if(c1 == c2){
                    total = grid[r][c1];
                }
                else{
                    total = grid[r][c1] + grid[r][c2];
                }
                total += striver(r+1, c1 + nc1, c2 + nc2, grid);
                maxi = max(total, maxi);
            }
        }
        // cout<<r<<"|"<<c1<<"|"<<c2<<"::"<<maxi<<" ";

        return memo[r][c1][c2] = maxi;
    }
    
    int recur(int x, int y, int x1, int y1, vector<vector<int>>& grid,
    vector<vector<vector<vector<int>>>> &dp){
        if(x>=n || y>=n || x1>=n ||y1>=n || grid[x][y]==-1 ||grid[x1][y1]==-1 ){
            return INT_MIN;
        }
        if(x==n-1 && y==n-1)
            return grid[x][y];
        if(x1==n-1 && y1==n-1)
            return grid[x1][y1];
        if(dp[x][y][x1][y1] != INT_MIN)
            return dp[x][y][x1][y1];
        
        int ans = grid[x][y] + (x1 ==x && y==y1 ? 0 : grid[x1][y1]);

        ans += max(max(recur(x,y+1,x1,y1+1,grid,dp), recur(x,y+1,x1+1,y1,grid,dp)), 
                max(recur(x+1,y,x1,y1+1,grid,dp), recur(x+1,y,x1+1,y1,grid,dp)));
        dp[x][y][x1][y1] = ans;
        return ans;
    }
    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();
        m = grid[0].size();
        
        memo.resize(n+1, VVI(n+1, VI(n+1, INT_MIN)));

        // vector<vector<vector<vector<int>>>> dp(n+1, vector<int>(n+1, vector<int>(n+1, vector<int>(n+1, INT_MIN))));
        // vector<vector<vector<vector<int>>>> dp(n+1, vector<vector<vector<int>>>(n+1, vector<vector<int>>(n+1, vector<int>(n+1, INT_MIN))));

        VVVI dpp = VVVI(n+1, VVI(n+1, VI(n+1, INT_MIN)));

        // ans = recur(0,0,0,0,grid,dp);
        int ans = dfs(0, 0, 0, grid ,dpp);;
        ans = (ans<0) ? 0 : ans;
        return ans;
    }

    int dfs(int r1, int c1, int c2, vector<vector<int>>& grid, VVVI &dp){
        int r2 = r1+c1-c2;
        // we are moving both together therefore total steps will be same
        // r1+c1 = r2+c2
        int n = grid.size();

        if(r1>=n || r2>=n || c1>=n && c2>=n || grid[r1][c1]==-1 || grid[r2][c2]==-1 ){
            return INT_MIN;
        }

        if(r1==n-1 && c1==n-1){
            // both will be here at this time
            // reached = true;
            // dp[r1][c1][c2] = grid[r1][c1];
            return grid[r1][c1];
        }
        if(dp[r1][c1][c2] != INT_MIN){
            return dp[r1][c1][c2];
        }
        long long ans = grid[r1][c1] + (r1==r2 && c1==c2 ? 0: grid[r2][c2]);

        ans  += (long long)max(max(dfs(r1+1,c1,c2,grid,dp), dfs(r1+1,c1,c2+1,grid,dp)), 
                   max(dfs(r1,c1+1,c2,grid,dp), dfs(r1,c1+1,c2+1,grid,dp)));

        // cout<< r1<<" "<<c1<<" "<<c2<<"|"<<ans <<":: "; 
        dp[r1][c1][c2] = ans;

        return ans;
    }
};
```

## Attempt 11 · 2023-05-02 08:22 IST · Accepted · C++

[submission 942960945](https://leetcode.com/submissions/detail/942960945/) · tests 59/59 · runtime 89 ms (beats 21.5%)

```cpp
class Solution {
    typedef vector<vector<vector<int>>> VVVI;
    typedef vector<vector<int>> VVI;
    typedef vector<int> VI;
    bool reached = false;
public:
    VVVI memo;
    // int dp[55][55][55][55];
    // vector<vector<vector<vector<int>>>> dp;
    int n,m;
    int striver(int r, int c1, int c2, vector<vector<int>>& grid){
        int r2 = r+c1-c2;
        // we are moving both together therefore total steps will be same
        // r1+c1 = r2+c2
        // base case
        if(c1 <0 || c2< 0 || c1 >=m || c2>=m || 
            r<0 || r2<0 || r>=n || r2>=n || 
            grid[r][c1] == -1 || grid[r2][c2] == -1){
            // out of bound
            return -1e8;
        }
        if(r == n-1 && c1 == n-1){
            return memo[r][c1][c2] = grid[r][c1];
        }
        if(memo[r][c1][c2] != -1) return memo[r][c1][c2];

        int maxi = -1e8;
        // only 2 calls right or down {RR, RD, DR, DD}}
        // dx = {0,1}
        // dy = {1,0}
        int dx[] = {0,1};
        int dy[] = {1,0};
        long long ans = grid[r][c1] + (r==r2 && c1==c2 ? 0: grid[r][c2]);
        maxi = max(max(striver(r+1,c1,c2, grid), striver(r+1,c1,c2+1, grid)),
                    max(striver(r,c1+1,c2, grid), striver(r,c1+1,c2+1, grid)));

        // cout<<r<<"|"<<c1<<"|"<<c2<<"::"<<maxi<<" ";

        return memo[r][c1][c2] = maxi;
    }

    int recur(int x, int y, int x1, int y1, vector<vector<int>>& grid,
    vector<vector<vector<vector<int>>>> &dp){
        if(x>=n || y>=n || x1>=n ||y1>=n || grid[x][y]==-1 ||grid[x1][y1]==-1 ){
            return INT_MIN;
        }
        if(x==n-1 && y==n-1)
            return grid[x][y];
        if(x1==n-1 && y1==n-1)
            return grid[x1][y1];
        if(dp[x][y][x1][y1] != INT_MIN)
            return dp[x][y][x1][y1];
        
        int ans = grid[x][y] + (x1 ==x && y==y1 ? 0 : grid[x1][y1]);

        ans += max(max(recur(x,y+1,x1,y1+1,grid,dp), recur(x,y+1,x1+1,y1,grid,dp)), 
                max(recur(x+1,y,x1,y1+1,grid,dp), recur(x+1,y,x1+1,y1,grid,dp)));
        dp[x][y][x1][y1] = ans;
        return ans;
    }
    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();
        m = grid[0].size();
        
        memo.resize(n+1, VVI(n+1, VI(n+1, INT_MIN)));

        // vector<vector<vector<vector<int>>>> dp(n+1, vector<int>(n+1, vector<int>(n+1, vector<int>(n+1, INT_MIN))));
        // vector<vector<vector<vector<int>>>> dp(n+1, vector<vector<vector<int>>>(n+1, vector<vector<int>>(n+1, vector<int>(n+1, INT_MIN))));

        VVVI dpp = VVVI(n+1, VVI(n+1, VI(n+1, INT_MIN)));

        // ans = recur(0,0,0,0,grid,dp);
        int ans = dfs(0, 0, 0, grid ,dpp);;
        ans = (ans<0) ? 0 : ans;
        return ans;
    }

    int dfs(int r1, int c1, int c2, vector<vector<int>>& grid, VVVI &dp){
        int r2 = r1+c1-c2;
        // we are moving both together therefore total steps will be same
        // r1+c1 = r2+c2
        int n = grid.size();

        if(r1>=n || r2>=n || c1>=n || c2>=n || grid[r1][c1]==-1 || grid[r2][c2]==-1 ){
            return -1e8;
        }

        if(r1==n-1 && c1==n-1){
            // both will be here at this time
            // reached = true;
            // dp[r1][c1][c2] = grid[r1][c1];
            return grid[r1][c1];
        }
        if(dp[r1][c1][c2] != INT_MIN){
            return dp[r1][c1][c2];
        }
        long long ans = grid[r1][c1] + (r1==r2 && c1==c2 ? 0: grid[r2][c2]);

        ans  += (long long)max(max(dfs(r1+1,c1,c2,grid,dp), dfs(r1+1,c1,c2+1,grid,dp)), 
                   max(dfs(r1,c1+1,c2,grid,dp), dfs(r1,c1+1,c2+1,grid,dp)));

        // cout<< r1<<" "<<c1<<" "<<c2<<"|"<<ans <<":: "; 
        dp[r1][c1][c2] = ans;

        return ans;
    }
};
```

## Attempt 12 · 2023-05-02 08:26 IST · Wrong Answer · C++

[submission 942962528](https://leetcode.com/submissions/detail/942962528/) · tests 40/59

Failing input:

```text
[[1,1,1,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,1],[1,0,0,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,1,1,1,1]]
```

Expected:

```text
15
```

Your output:

```text
19
```

```cpp
class Solution {
    typedef vector<vector<vector<int>>> VVVI;
    typedef vector<vector<int>> VVI;
    typedef vector<int> VI;
    bool reached = false;
public:
    VVVI memo;
    // int dp[55][55][55][55];
    // vector<vector<vector<vector<int>>>> dp;
    int n,m;
    int striver(int r, int c1, int c2, vector<vector<int>>& grid){
        int r2 = r+c1-c2;
        // we are moving both together therefore total steps will be same
        // r1+c1 = r2+c2
        // base case
        if(c1 <0 || c2< 0 || c1 >=m || c2>=m || 
            r<0 || r2<0 || r>=n || r2>=n || 
            grid[r][c1] == -1 || grid[r2][c2] == -1){
            // out of bound
            return -1e8;
        }
        if(r == n-1 && c1 == n-1){
            return memo[r][c1][c2] = grid[r][c1];
        }
        if(memo[r][c1][c2] != -1) return memo[r][c1][c2];

        int maxi = -1e8;
        // only 2 calls right or down {RR, RD, DR, DD}}
        // dx = {0,1}
        // dy = {1,0}
        int dx[] = {0,1};
        int dy[] = {1,0};
        long long ans = grid[r][c1] + (r==r2 && c1==c2 ? 0: grid[r][c2]);
        ans += max(max(striver(r+1,c1,c2, grid), striver(r+1,c1,c2+1, grid)),
                    max(striver(r,c1+1,c2, grid), striver(r,c1+1,c2+1, grid)));

        // cout<<r<<"|"<<c1<<"|"<<c2<<"::"<<maxi<<" ";

        return memo[r][c1][c2] = ans;
    }

    int recur(int x, int y, int x1, int y1, vector<vector<int>>& grid,
    vector<vector<vector<vector<int>>>> &dp){
        if(x>=n || y>=n || x1>=n ||y1>=n || grid[x][y]==-1 ||grid[x1][y1]==-1 ){
            return INT_MIN;
        }
        if(x==n-1 && y==n-1)
            return grid[x][y];
        if(x1==n-1 && y1==n-1)
            return grid[x1][y1];
        if(dp[x][y][x1][y1] != INT_MIN)
            return dp[x][y][x1][y1];
        
        int ans = grid[x][y] + (x1 ==x && y==y1 ? 0 : grid[x1][y1]);

        ans += max(max(recur(x,y+1,x1,y1+1,grid,dp), recur(x,y+1,x1+1,y1,grid,dp)), 
                max(recur(x+1,y,x1,y1+1,grid,dp), recur(x+1,y,x1+1,y1,grid,dp)));
        dp[x][y][x1][y1] = ans;
        return ans;
    }
    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();
        m = grid[0].size();
        
        memo.resize(n+1, VVI(n+1, VI(n+1, -1)));
        int ans = striver(0,0,0,grid);
        if(ans < 0) return 0;
        return ans;
        // vector<vector<vector<vector<int>>>> dp(n+1, vector<int>(n+1, vector<int>(n+1, vector<int>(n+1, INT_MIN))));
        // vector<vector<vector<vector<int>>>> dp(n+1, vector<vector<vector<int>>>(n+1, vector<vector<int>>(n+1, vector<int>(n+1, INT_MIN))));

        VVVI dpp = VVVI(n+1, VVI(n+1, VI(n+1, INT_MIN)));

        // ans = recur(0,0,0,0,grid,dp);
        ans = dfs(0, 0, 0, grid ,dpp);;
        ans = (ans<0) ? 0 : ans;
        return ans;
    }

    int dfs(int r1, int c1, int c2, vector<vector<int>>& grid, VVVI &dp){
        int r2 = r1+c1-c2;
        // we are moving both together therefore total steps will be same
        // r1+c1 = r2+c2
        int n = grid.size();

        if(r1>=n || r2>=n || c1>=n || c2>=n || grid[r1][c1]==-1 || grid[r2][c2]==-1 ){
            return -1e8;
        }

        if(r1==n-1 && c1==n-1){
            // both will be here at this time
            // reached = true;
            // dp[r1][c1][c2] = grid[r1][c1];
            return grid[r1][c1];
        }
        if(dp[r1][c1][c2] != INT_MIN){
            return dp[r1][c1][c2];
        }
        long long ans = grid[r1][c1] + (r1==r2 && c1==c2 ? 0: grid[r2][c2]);

        ans  += (long long)max(max(dfs(r1+1,c1,c2,grid,dp), dfs(r1+1,c1,c2+1,grid,dp)), 
                   max(dfs(r1,c1+1,c2,grid,dp), dfs(r1,c1+1,c2+1,grid,dp)));

        // cout<< r1<<" "<<c1<<" "<<c2<<"|"<<ans <<":: "; 
        dp[r1][c1][c2] = ans;

        return ans;
    }
};
```

## Attempt 13 · 2023-05-02 08:28 IST · Accepted · C++

[submission 942963304](https://leetcode.com/submissions/detail/942963304/) · tests 59/59 · runtime 79 ms (beats 23.0%)

```cpp
class Solution {
    typedef vector<vector<vector<int>>> VVVI;
    typedef vector<vector<int>> VVI;
    typedef vector<int> VI;
    bool reached = false;
public:
    VVVI memo;
    // int dp[55][55][55][55];
    // vector<vector<vector<vector<int>>>> dp;
    int n,m;
    int striver(int r, int c1, int c2, vector<vector<int>>& grid){
        int r2 = r+c1-c2;
        // we are moving both together therefore total steps will be same
        // r1+c1 = r2+c2
        // base case
        if(c1 <0 || c2< 0 || c1 >=m || c2>=m || 
            r<0 || r2<0 || r>=n || r2>=n || 
            grid[r][c1] == -1 || grid[r2][c2] == -1){
            // out of bound
            return -1e8;
        }
        if(r == n-1 && c1 == n-1){
            return memo[r][c1][c2] = grid[r][c1];
        }
        if(memo[r][c1][c2] != -1) return memo[r][c1][c2];

        int maxi = -1e8;
        // only 4 calls right or down {RR, RD, DR, DD}}

        long long ans = grid[r][c1] + (r==r2 && c1==c2 ? 0: grid[r2][c2]);
        maxi = ans + max(max(striver(r+1,c1,c2, grid), striver(r+1,c1,c2+1, grid)),
                    max(striver(r,c1+1,c2, grid), striver(r,c1+1,c2+1, grid)));

        // cout<<r<<"|"<<c1<<"|"<<c2<<"::"<<maxi<<" ";

        return memo[r][c1][c2] = maxi;
    }

    int recur(int x, int y, int x1, int y1, vector<vector<int>>& grid,
    vector<vector<vector<vector<int>>>> &dp){
        if(x>=n || y>=n || x1>=n ||y1>=n || grid[x][y]==-1 ||grid[x1][y1]==-1 ){
            return INT_MIN;
        }
        if(x==n-1 && y==n-1)
            return grid[x][y];
        if(x1==n-1 && y1==n-1)
            return grid[x1][y1];
        if(dp[x][y][x1][y1] != INT_MIN)
            return dp[x][y][x1][y1];
        
        int ans = grid[x][y] + (x1 ==x && y==y1 ? 0 : grid[x1][y1]);

        ans += max(max(recur(x,y+1,x1,y1+1,grid,dp), recur(x,y+1,x1+1,y1,grid,dp)), 
                max(recur(x+1,y,x1,y1+1,grid,dp), recur(x+1,y,x1+1,y1,grid,dp)));
        dp[x][y][x1][y1] = ans;
        return ans;
    }
    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();
        m = grid[0].size();
        
        memo.resize(n+1, VVI(n+1, VI(n+1, -1)));
        int ans = striver(0,0,0,grid);
        if(ans < 0) return 0;
        return ans;
        // vector<vector<vector<vector<int>>>> dp(n+1, vector<int>(n+1, vector<int>(n+1, vector<int>(n+1, INT_MIN))));
        // vector<vector<vector<vector<int>>>> dp(n+1, vector<vector<vector<int>>>(n+1, vector<vector<int>>(n+1, vector<int>(n+1, INT_MIN))));

        VVVI dpp = VVVI(n+1, VVI(n+1, VI(n+1, INT_MIN)));

        // ans = recur(0,0,0,0,grid,dp);
        ans = dfs(0, 0, 0, grid ,dpp);;
        ans = (ans<0) ? 0 : ans;
        return ans;
    }

    int dfs(int r1, int c1, int c2, vector<vector<int>>& grid, VVVI &dp){
        int r2 = r1+c1-c2;
        // we are moving both together therefore total steps will be same
        // r1+c1 = r2+c2
        int n = grid.size();

        if(r1>=n || r2>=n || c1>=n || c2>=n || grid[r1][c1]==-1 || grid[r2][c2]==-1 ){
            return -1e8;
        }

        if(r1==n-1 && c1==n-1){
            // both will be here at this time
            // reached = true;
            // dp[r1][c1][c2] = grid[r1][c1];
            return grid[r1][c1];
        }
        if(dp[r1][c1][c2] != INT_MIN){
            return dp[r1][c1][c2];
        }
        long long ans = grid[r1][c1] + (r1==r2 && c1==c2 ? 0: grid[r2][c2]);

        ans  += (long long)max(max(dfs(r1+1,c1,c2,grid,dp), dfs(r1+1,c1,c2+1,grid,dp)), 
                   max(dfs(r1,c1+1,c2,grid,dp), dfs(r1,c1+1,c2+1,grid,dp)));

        // cout<< r1<<" "<<c1<<" "<<c2<<"|"<<ans <<":: "; 
        dp[r1][c1][c2] = ans;

        return ans;
    }
};
```
