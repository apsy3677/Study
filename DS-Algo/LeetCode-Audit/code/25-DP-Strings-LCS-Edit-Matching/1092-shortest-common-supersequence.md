# 1092. Shortest Common Supersequence 

[Problem](https://leetcode.com/problems/shortest-common-supersequence/) · Hard · DP: Strings (LCS, Edit, Matching) → LCS reconstruction

LeetCode tags: string, dynamic-programming, longest-common-subsequence

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2023-03-13 14:38 IST · Wrong Answer · C++

[submission 914276409](https://leetcode.com/submissions/detail/914276409/) · tests 9/47

Failing input:

```text
"abac"
"cab"
```

Expected:

```text
"cabac"
```

Your output:

```text
"cabcac"
```

```cpp
class Solution {
public:
    string shortestCommonSupersequence(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, -1));

        // initialize llcs of "abc" & ""
        for(int i=0;i<=n;i++){
            dp[i][0] = 0;
        }
        for(int i=0;i<=m;i++){
            dp[0][i] = 0;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(s1[i-1] == s2[j-1]){
                    dp[i][j] = dp[i-1][j-1] + 1;
                }
                else{
                    dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
                }
            }
        }

        int i = n, j= m;
        string ans = "";
        while(i>0 && j>0){
            if(s1[i-1] == s2[j-1]){
                // LCS Char
                ans = s1[i-1] + ans;
                i--;
                j--;
            }
            else{
                
                if(dp[i-1][j] > dp[i][j-1]){
                    ans += s1[i-1] + ans;
                    i--;
                }
                else{
                    ans += s2[j-1] + ans;
                    j--;
                }
            }
        }
        while(i>0){
            ans = s1[i-1] + ans;
            i--;
        }
        while(j>0){
            ans = s2[j-1] + ans;
            j--;
        }
        // reverse(ans.begin(), ans.end());
        return ans;
    }
};
```

## Attempt 2 · 2023-03-13 14:52 IST · Accepted · C++

[submission 914282202](https://leetcode.com/submissions/detail/914282202/) · tests 47/47 · runtime 36 ms (beats 6.3%)

```cpp
class Solution {
public:
    string shortestCommonSupersequence(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

        // initialize llcs of "abc" & ""
        for(int i=0;i<=n;i++){
            dp[i][0] = 0;
        }
        for(int i=0;i<=m;i++){
            dp[0][i] = 0;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(s1[i-1] == s2[j-1]){
                    dp[i][j] = dp[i-1][j-1] + 1;
                }
                else{
                    dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
                }
            }
        }

        int i = n, j= m;
        string ans = "";

        int len = dp[n][m];
        int idx = len -1;

        while(i>0 && j>0){
            if(s1[i-1] == s2[j-1]){
                // LCS Char
                ans = s1[i-1] + ans;
                cout<<"L "<<ans<<" ";
                idx--;
                i--;
                j--;
            }
            else if(dp[i-1][j] > dp[i][j-1]){
                    ans = s1[i-1] + ans;
                    cout<<"NL "<<ans<<" ";
                    i--;
            }
            else{
                ans = s2[j-1] + ans;
                cout<<"NL "<< ans<<" ";
                j--;
            }
        }
        while(i>0){
            ans = s1[i-1] + ans;
            cout<<"NL "<< ans<<" ";
            i--;
        }
        while(j>0){
            ans = s2[j-1] + ans;
            cout<<"NL "<< ans<<" ";
            j--;
        }
        // reverse(ans.begin(), ans.end());
        return ans;
    }
};
```
