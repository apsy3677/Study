# 931. Minimum Falling Path Sum

[Problem](https://leetcode.com/problems/minimum-falling-path-sum/) · Medium · DP: Grid / 2D → Falling path

LeetCode tags: array, dynamic-programming, matrix

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-12 18:19 IST · Accepted · C++

[submission 913806269](https://leetcode.com/submissions/detail/913806269/) · tests 49/49 · runtime 16 ms (beats 5.2%)

```cpp
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n= grid.size();
        vector<vector<int>> dp(n, vector<int> (n, INT_MAX));
        for(int i=0;i<n;i++){
            dp[0][i] = grid[0][i];
        }
        for(int i=1;i<n;i++){
            for(int j=0;j<n;j++){
                int ans = dp[i-1][j];
                // j-1, j, j+1 of last row
                if(j>0){
                    ans = min(dp[i-1][j-1], ans);
                }
                if(j<n-1){
                    ans = min(ans, dp[i-1][j+1]);
                }
                dp[i][j] = grid[i][j] + ans;
            } 
        }
        int ans = INT_MAX;
        for(int i=0;i<n;i++){
            ans = min(ans, dp[n-1][i]);
        }
        return ans;
    }
};
```
