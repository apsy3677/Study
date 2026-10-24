# 1277. Count Square Submatrices with All Ones

[Problem](https://leetcode.com/problems/count-square-submatrices-with-all-ones/) · Medium · DP: Grid / 2D → Square DP

LeetCode tags: array, dynamic-programming, matrix

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-04-01 22:51 IST · Accepted · C++

[submission 926088154](https://leetcode.com/submissions/detail/926088154/) · tests 32/32 · runtime 67 ms (beats 5.7%)

```cpp
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> dp(n, vector<int>(m,0));

        int ans = 0;

        for(int i=0;i<n;i++){
            dp[i][0] = matrix[i][0];
            ans += dp[i][0];
        }
        for(int i=1;i<m;i++){
            dp[0][i] = matrix[0][i];
            ans += dp[0][i];
        }

        for(int i=1;i<n;i++){
            for(int j=1;j<m;j++){
                if(matrix[i][j] == 0){
                    dp[i][j] =0;
                }
                else{
                    dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1])) + 1 ;// 1 will add one submatix of lenth 1 at least
                }
                ans += dp[i][j];
            }
        }
        return ans;

    }
};
```
