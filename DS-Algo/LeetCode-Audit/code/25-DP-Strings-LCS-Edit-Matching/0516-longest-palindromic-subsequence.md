# 516. Longest Palindromic Subsequence

[Problem](https://leetcode.com/problems/longest-palindromic-subsequence/) · Medium · DP: Strings (LCS, Edit, Matching) → LCS with reverse

LeetCode tags: string, dynamic-programming

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-13 13:45 IST · Accepted · C++

[submission 914256431](https://leetcode.com/submissions/detail/914256431/) · tests 86/86 · runtime 217 ms (beats 5.0%)

```cpp
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        string t = s;
        reverse(s.begin(),s.end());
        int n= s.size();
        vector<vector<int>> dp(n+1, vector<int>(n+1, 0));

        // initialize llcs of "abc" & ""
        for(int i=0;i<=n;i++){
            dp[i][0] = 0;
            dp[0][i] = 0;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(s[i-1] == t[j-1]){
                    dp[i][j] = dp[i-1][j-1] + 1;
                }
                else{
                    dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
                }
            }
        }

        return dp[n][n];
    }
};
```
