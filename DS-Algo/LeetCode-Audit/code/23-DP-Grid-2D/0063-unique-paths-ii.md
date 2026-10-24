# 63. Unique Paths II

[Problem](https://leetcode.com/problems/unique-paths-ii/) · Medium · DP: Grid / 2D → Count paths with obstacles

LeetCode tags: array, dynamic-programming, matrix

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2023-03-12 17:25 IST · Wrong Answer · C++

[submission 913786083](https://leetcode.com/submissions/detail/913786083/) · tests 37/41

Failing input:

```text
[[1,0]]
```

Expected:

```text
0
```

Your output:

```text
1
```

```cpp
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        int n=grid.size();
        int m=grid[0].size();

        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
        dp[0][0] = grid[0][0] ==0 ? 1 : 0;
        for(int i=1;i<n;i++){
            if(grid[i][0]){
                break;
            }
            dp[i][0] = 1;
        }
        for(int i=1;i<m;i++){
            if(grid[0][i]){
                break;
            }
            dp[0][i] = 1;
        }
        
        for(int i=1;i<n;i++){
            for(int j=1;j<m;j++){
                if(grid[i][j] == 1){
                    continue;
                }
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }

        return dp[n-1][m-1];
    }
};
```

## Attempt 2 · 2023-03-12 17:27 IST · Accepted · C++

[submission 913786813](https://leetcode.com/submissions/detail/913786813/) · tests 41/41 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        int n=grid.size();
        int m=grid[0].size();

        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
        // dp[0][0] = grid[0][0] == 0 ? 1 : 0;
        for(int i=0;i<n;i++){
            if(grid[i][0]){
                break;
            }
            dp[i][0] = 1;
        }
        for(int i=0;i<m;i++){
            if(grid[0][i]){
                break;
            }
            dp[0][i] = 1;
        }
        
        for(int i=1;i<n;i++){
            for(int j=1;j<m;j++){
                if(grid[i][j] == 1){
                    continue;
                }
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }

        return dp[n-1][m-1];
    }
};
```
