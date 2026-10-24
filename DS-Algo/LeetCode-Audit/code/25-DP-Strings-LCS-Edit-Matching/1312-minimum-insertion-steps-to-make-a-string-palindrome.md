# 1312. Minimum Insertion Steps to Make a String Palindrome

[Problem](https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/) · Hard · DP: Strings (LCS, Edit, Matching) → Via longest palindromic subsequence

LeetCode tags: string, dynamic-programming

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-13 13:56 IST · Accepted · C++

[submission 914260676](https://leetcode.com/submissions/detail/914260676/) · tests 58/58 · runtime 113 ms (beats 5.3%)

```cpp
class Solution {
public:
    int minInsertions(string s) {
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

        return n - dp[n][n];
    }
};
```
