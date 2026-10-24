# 64. Minimum Path Sum

[Problem](https://leetcode.com/problems/minimum-path-sum/) · Medium · DP: Grid / 2D → Min-cost path

LeetCode tags: array, dynamic-programming, matrix

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2023-03-12 11:13 IST · Wrong Answer · C++

[submission 913633670](https://leetcode.com/submissions/detail/913633670/) · tests 39/61

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
2
```

```cpp
class Solution {
public:
    vector<vector<bool>> seen;
    int n,m;
    int dfs(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& dp){
        if(i<0 || i>=n || j<0 || j>=m)
            return INT_MAX;
        if(i==0 && j==0){
            return dp[i][j] = grid[i][j];
        }

        if(dp[i][j] != -1){
            return dp[i][j];
        }
        seen[i][j] = true;

        int min1 = dfs(i,j+1,grid,dp);
        int min2 = dfs(i+1,j,grid,dp);

        return dp[i][j] = min(min1, min2);
    }

    int minPathSum(vector<vector<int>>& grid) {
        n= grid.size();
        m= grid[0].size();
        vector<vector<int>> dp(grid.size()+1, vector<int> (grid[0].size() +1, 0));
        seen.resize(grid.size()+1, vector<bool> (grid[0].size() +1, false) );
        
        for(int i=1;i<=m;i++){
            dp[1][i] += dp[1][i-1] + grid[0][i-1];
        }
        for(int i=1;i<=n;i++){
            dp[i][1] += dp[i-1][1] + grid[i-1][0];
        }

        for(int i=2;i<=n;i++){
            for(int j=2;j<=m;j++){
                dp[i][j] = grid[i-1][j-1] + min(dp[i-1][j], dp[i][j-1]);
            }
        }
        //return dfs(0,0,grid,dp);
        return dp[n][m];
    }
};
```

## Attempt 2 · 2023-03-12 11:17 IST · Accepted · C++

[submission 913635348](https://leetcode.com/submissions/detail/913635348/) · tests 61/61 · runtime 15 ms (beats 5.9%)

```cpp
class Solution {
public:
    vector<vector<bool>> seen;
    int n,m;
    int dfs(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& dp){
        if(i<0 || i>=n || j<0 || j>=m)
            return INT_MAX;
        if(i==0 && j==0){
            return dp[i][j] = grid[i][j];
        }

        if(dp[i][j] != -1){
            return dp[i][j];
        }
        seen[i][j] = true;

        int min1 = dfs(i,j+1,grid,dp);
        int min2 = dfs(i+1,j,grid,dp);

        return dp[i][j] = min(min1, min2);
    }

    int minPathSum(vector<vector<int>>& grid) {
        n= grid.size();
        m= grid[0].size();
        vector<vector<int>> dp(grid.size()+1, vector<int> (grid[0].size() +1, 0));
        // seen.resize(grid.size()+1, vector<bool> (grid[0].size() +1, false) );
        
        for(int i=1;i<=m;i++){
            dp[1][i] += dp[1][i-1] + grid[0][i-1];
        }
        for(int i=2;i<=n;i++){
            dp[i][1] += dp[i-1][1] + grid[i-1][0];
        }

        for(int i=2;i<=n;i++){
            for(int j=2;j<=m;j++){
                dp[i][j] = grid[i-1][j-1] + min(dp[i-1][j], dp[i][j-1]);
            }
        }
        //return dfs(0,0,grid,dp);
        return dp[n][m];
    }
};
```
