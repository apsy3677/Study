# 62. Unique Paths

[Problem](https://leetcode.com/problems/unique-paths/) · Medium · DP: Grid / 2D → Count paths

LeetCode tags: math, dynamic-programming, combinatorics

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-12 17:09 IST · Accepted · C++

[submission 913779888](https://leetcode.com/submissions/detail/913779888/) · tests 63/63 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    int uniquePaths(int row, int col) {
        vector<vector<int>> dp(row, vector<int>(col,0));
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(i==0){
                    dp[i][j] =1;
                    continue;
                }
                if(j==0){
                    dp[i][j] =1;
                    continue;
                }
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[row-1][col-1];
    }
};
```
