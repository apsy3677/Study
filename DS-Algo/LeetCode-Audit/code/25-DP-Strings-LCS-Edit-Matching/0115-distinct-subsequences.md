# 115. Distinct Subsequences

[Problem](https://leetcode.com/problems/distinct-subsequences/) · Hard · DP: Strings (LCS, Edit, Matching) → Count matchings

LeetCode tags: string, dynamic-programming

Attempts since Mar 2023: 4 · accepted: 2 · failed before first AC: 2

## Attempt 1 · 2023-03-13 15:57 IST · Time Limit Exceeded · C++

[submission 914307571](https://leetcode.com/submissions/detail/914307571/) · tests 50/65

Failing input:

```text
"aabdbaabeeadcbbdedacbbeecbabebaeeecaeabaedadcbdbcdaabebdadbbaeabdadeaabbabbecebbebcaddaacccebeaeedababedeacdeaaaeeaecbe"
"bddabdcae"
```

Expected:

```text
10582116
```

```cpp
class Solution {
public:

    int rec(int n, int m, string &s, string &t, vector<vector<int>> dp){
        if(m<0){
            // all chars of t are matched in s
            return 1;
        }
        if(n<0){
            // all chars of s are travesed but not of t
            return 0;
        }
        if(dp[n][m] != -1){
            return dp[n][m];
        }
        int ans = 0;
        if(s[n] == t[m]){
            ans = rec(n-1,m-1,s,t,dp) + rec(n-1,m,s,t,dp);
        }else{
            ans = rec(n-1,m,s,t,dp);
        }

        return dp[n][m] = ans;
    }

    int numDistinct(string s, string t) {
        int n = s.size(), m= t.size();
        if(n<m){
            return 0;
        }
        vector<vector<int>> dp(n+1, vector<int>(m+1, -1));

        return rec(n-1, m-1, s, t, dp);
    }
};
```

## Attempt 2 · 2023-03-13 16:20 IST · Runtime Error · C++

[submission 914316326](https://leetcode.com/submissions/detail/914316326/) · tests 60/65

Failing input:

```text
"xslledayhxhadmctrliaxqpokyezcfhzaskeykchkmhpyjipxtsuljkwkovmvelvwxzwieeuqnjozrfwmzsylcwvsthnxujvrkszqwtglewkycikdaiocglwzukwovsghkhyidevhbgffoqkpabthmqihcfxxzdejletqjoxmwftlxfcxgxgvpperwbqvhxgsbbkmphyomtbjzdjhcrcsggleiczpbfjcgtpycpmrjnckslrwduqlccqmgrdhxolfjafmsrfdghnatexyanldrdpxvvgujsztuffoymrfteholgonuaqndinadtumnuhkboyzaqguwqijwxxszngextfcozpetyownmyneehdwqmtpjloztswmzzdzqhuoxrblppqvyvsqhnhry ... [651 more chars]
```

Expected:

```text
543744000
```

Runtime error:

```text
Line 46: Char 45: runtime error: signed integer overflow: 1474397256 + 891953512 cannot be represented in type 'int' (solution.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:55:45
```

```cpp
class Solution {
public:

    int rec(int n, int m, string &s, string &t, vector<vector<int>> dp){
        if(m<0){
            // all chars of t are matched in s
            return 1;
        }
        if(n<0){
            // all chars of s are travesed but not of t
            return 0;
        }
        if(dp[n][m] != -1){
            return dp[n][m];
        }
        int ans = 0;
        if(s[n] == t[m]){
            ans = rec(n-1,m-1,s,t,dp) + rec(n-1,m,s,t,dp);
        }else{
            ans = rec(n-1,m,s,t,dp);
        }

        return dp[n][m] = ans;
    }

    int numDistinct(string s, string t) {
        int n = s.size(), m= t.size();
        if(n<m){
            return 0;
        }
        // vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

        // return rec(n-1, m-1, s, t, dp);

        for(int i=0;i<=n;i++){
            dp[i][0] = 1;
        }
        for(int i=1;i<=m;i++){
            dp[0][i] = 0;
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(s[i-1] == t[j-1]){
                    dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
                }
                else{
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        return dp[n][m];
    }
};
```

## Attempt 3 · 2023-03-13 16:30 IST · Accepted · C++

[submission 914319803](https://leetcode.com/submissions/detail/914319803/) · tests 65/65 · runtime 48 ms (beats 7.4%)

```cpp
class Solution {
public:

    int rec(int n, int m, string &s, string &t, vector<vector<int>> dp){
        if(m<0){
            // all chars of t are matched in s
            return 1;
        }
        if(n<0){
            // all chars of s are travesed but not of t
            return 0;
        }
        if(dp[n][m] != -1){
            return dp[n][m];
        }
        int ans = 0;
        if(s[n] == t[m]){
            ans = rec(n-1,m-1,s,t,dp) + rec(n-1,m,s,t,dp);
        }else{
            ans = rec(n-1,m,s,t,dp);
        }

        return dp[n][m] = ans;
    }

    int numDistinct(string s, string t) {
        int n = s.size(), m= t.size();
        if(n<m){
            return 0;
        }
        // vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

        // return rec(n-1, m-1, s, t, dp);

        for(int i=0;i<=n;i++){
            dp[i][0] = 1;
        }
        for(int i=1;i<=m;i++){
            dp[0][i] = 0;
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(s[i-1] == t[j-1]){
                    dp[i][j] = (long long)dp[i-1][j-1] + dp[i-1][j];
                }
                else{
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        return dp[n][m];
    }
};
```

## Attempt 4 · 2023-03-13 16:48 IST · Accepted · C++

[submission 914326473](https://leetcode.com/submissions/detail/914326473/) · tests 65/65 · runtime 30 ms (beats 50.1%)

```cpp
class Solution {
public:

    int rec(int n, int m, string &s, string &t, vector<vector<int>> dp){
        if(m<0){
            // all chars of t are matched in s
            return 1;
        }
        if(n<0){
            // all chars of s are travesed but not of t
            return 0;
        }
        if(dp[n][m] != -1){
            return dp[n][m];
        }
        int ans = 0;
        if(s[n] == t[m]){
            ans = rec(n-1,m-1,s,t,dp) + rec(n-1,m,s,t,dp);
        }else{
            ans = rec(n-1,m,s,t,dp);
        }

        return dp[n][m] = ans;
    }

    int numDistinct(string s, string t) {
        int n = s.size(), m= t.size();
        if(n<m){
            return 0;
        }
        // vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
        // vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

        // return rec(n-1, m-1, s, t, dp);

        // vector<unsigned int> dp(m + 1), temp(m + 1);

        // dp[0] = temp[0] = 1;

        // for(int i=1; i<=n; i++) {
        //     for(int j=1; j<=m; j++) {
        //         if(s[i - 1] == t[j - 1]) temp[j] = dp[j - 1] + dp[j];
        //         else temp[j] = dp[j];
        //     }
        //     dp = temp;
        // }
        // return dp[m];

        vector<unsigned int> prev(m+1, 0);
        vector<unsigned int> curr(m+1, 0);

        // for(int i=0;i<=m;i++){
        //     prev[i]=1;
        // } // this base case is wrong
        prev[0] = curr[0] = 1;

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(s[i-1] == t[j-1]){
                    curr[j] = prev[j-1] + prev[j];
                }
                else{
                    curr[j] = prev[j];
                }
            }
            prev = curr;
        }

        return prev[m];

        // Iterative with N^2 space
        // for(int i=0;i<=n;i++){
        //     dp[i][0] = 1;
        // }
        // for(int i=1;i<=m;i++){
        //     dp[0][i] = 0;
        // }

        // for(int i=1;i<=n;i++){
        //     for(int j=1;j<=m;j++){
        //         if(s[i-1] == t[j-1]){
        //             dp[i][j] = (long long)dp[i-1][j-1] + dp[i-1][j];
        //         }
        //         else{
        //             dp[i][j] = dp[i-1][j];
        //         }
        //     }
        // }
        // return dp[n][m];
    }
};
```
