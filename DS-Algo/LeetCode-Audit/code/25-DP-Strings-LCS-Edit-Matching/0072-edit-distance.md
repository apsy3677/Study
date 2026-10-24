# 72. Edit Distance

[Problem](https://leetcode.com/problems/edit-distance/) · Medium · DP: Strings (LCS, Edit, Matching) → Edit distance

LeetCode tags: string, dynamic-programming

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-03-13 17:02 IST · Accepted · C++

[submission 914331669](https://leetcode.com/submissions/detail/914331669/) · tests 1146/1146 · runtime 20 ms (beats 14.1%)

```cpp
class Solution {
public:
    int minDistance(string s1, string s2) {
        int n = s1.size(), m= s2.size();

        vector<vector<int>> dp(n+1, vector<int>(m+1,INT_MAX));

        for(int i=0;i<=n;i++){
            dp[i][0] = i;
        }
        for(int i=0;i<=m;i++){
            dp[0][i] = i;
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(s1[i-1] == s2[j-1]){
                    dp[i][j] = 0 + dp[i-1][j-1];
                }
                else{
                    dp[i][j] = 1 + min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1]));
                }
            }
        }

        return dp[n][m];
    }
};
```

## Attempt 2 · 2023-05-03 11:03 IST · Accepted · C++

[submission 943623300](https://leetcode.com/submissions/detail/943623300/) · tests 1146/1146 · runtime 4 ms (beats 84.1%)

```cpp
class Solution {
    int rec(int n, int m, string &s, string &t, vector<vector<int>> &dp){
        if(n==0) return m;
        if(m==0) return n;
        if(dp[n][m] != -1) return dp[n][m];

        if(s[n-1]==t[m-1])
            return dp[n][m] = 0+rec(n-1,m-1,s,t, dp);
        
        return dp[n][m] = 1 + min(min(rec(n-1,m-1,s,t, dp), rec(n-1,m,s,t,dp)), rec(n,m-1,s,t,dp));
    }
public:
    int minDistance(string s1, string s2) {
        int n = s1.size(), m= s2.size();

        vector<vector<int>> dp(n+1, vector<int>(m+1,-1));
        return rec(n,m,s1,s2, dp);
        for(int i=0;i<=n;i++){
            dp[i][0] = i;
        }
        for(int i=0;i<=m;i++){
            dp[0][i] = i;
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(s1[i-1] == s2[j-1]){
                    dp[i][j] = 0 + dp[i-1][j-1];
                }
                else{
                    dp[i][j] = 1 + min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1]));
                }
            }
        }

        return dp[n][m];
    }
};
```
