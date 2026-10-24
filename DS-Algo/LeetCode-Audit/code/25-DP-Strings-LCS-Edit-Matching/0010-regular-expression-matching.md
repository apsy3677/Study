# 10. Regular Expression Matching

[Problem](https://leetcode.com/problems/regular-expression-matching/) · Hard · DP: Strings (LCS, Edit, Matching) → Pattern matching

LeetCode tags: string, dynamic-programming, recursion

Attempts since Mar 2023: 3 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2023-05-07 09:35 IST · Wrong Answer · C++

[submission 945849140](https://leetcode.com/submissions/detail/945849140/) · tests 288/354

Failing input:

```text
"aab"
"c*a*b"
```

Expected:

```text
true
```

Your output:

```text
false
```

```cpp
class Solution {
    bool wildcardMatchingUtil(string & S1, string & S2, int i, int j, vector < vector < int >> & dp) {

      //Base Conditions
      if (i < 0 && j < 0)
        return true;
      if (i < 0 && j >= 0)
        return false;
      if (j < 0 && i >= 0)
        return starOnly(S1, i);

      if (dp[i][j] != -1) return dp[i][j];

      bool ans = false;
      if (S1[i] == S2[j] || S1[i] == '.')
        return ans =  dp[i][j] = wildcardMatchingUtil(S1, S2, i - 1, j - 1, dp);

      else {
        if (S1[i] == '*')
          return dp[i][j] = wildcardMatchingUtil(S1, S2, i - 1, j, dp) || wildcardMatchingUtil(S1, S2, i, j - 1, dp);
        else return dp[i][j] = false;
      }
    }
    bool starOnly(string &p, int m){
        // bool ans = true;
        for(int i=0;i<=m;i++){
            if(p[i] != '*'){
                return false;
            }
        }
        return true;
    }
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m=p.size();
        // vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
        // return rec(n-1, m-1, s, p, dp);
        
        vector<vector<int>> dp(m+1, vector<int>(n+1, -1));
        return wildcardMatchingUtil(p, s, m-1, n-1, dp);
    }
};
```

## Attempt 2 · 2023-05-07 09:57 IST · Accepted · C++

[submission 945858570](https://leetcode.com/submissions/detail/945858570/) · tests 354/354 · runtime 15 ms (beats 12.7%)

```cpp
class Solution {
//     bool wildcardMatchingUtil(string & S1, string & S2, int i, int j, vector < vector < int >> & dp) {

//       //Base Conditions
//       if (i < 0 && j < 0)
//         return true;
//       if (i < 0 && j >= 0)
//         return false;
//       if (j < 0 && i >= 0)
//         return starOnly(S1, i);

//       if (dp[i][j] != -1) return dp[i][j];

//       bool ans = false;
//       // if (S1[i] == S2[j] || S1[i] == '.')
//       if (S1[i] == S2[j])
//         return ans =  dp[i][j] = wildcardMatchingUtil(S1, S2, i - 1, j - 1, dp);

//       else {
//         if (S1[i] == '*')
//           return dp[i][j] = wildcardMatchingUtil(S1, S2, i - 1, j, dp) || wildcardMatchingUtil(S1, S2, i, j - 1, dp);
//         else if(S1[i] == '.'){
//           return dp[i][j] = wildcardMatchingUtil(S1, S2, i - 1, j - 1, dp);
//         }
//         else return dp[i][j] = false;
//       }
//     }
//     bool starOnly(string &p, int m){
//         // bool ans = true;
//         for(int i=0;i<=m;i++){
//             if(p[i] != '*'){
//                 return false;
//             }
//         }
//         return true;
//     }
// public:
//     bool isMatch(string s, string p) {
//         int n = s.size(), m=p.size();
//         // vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
//         // return rec(n-1, m-1, s, p, dp);

//         vector<vector<int>> dp(m+1, vector<int>(n+1, -1));
//         return wildcardMatchingUtil(p, s, m-1, n-1, dp);
//     }
public:
  unordered_map<string, int> dp;
bool util(string s, string p, int n, int m){
    string key = to_string(n) + to_string(m);

    if(n <= -1 && m <= -1)
        return true;

    if(n == -1 && p[m] == '*')
        return util(s, p, n, m-2);

    if(n == -1 || m == -1)
        return false;

    if(dp.count(key))
        return dp[key];

    if(s[n] == p[m]){
        dp[key] = util(s, p, n-1, m-1);
    }
    else{
        if(p[m] == '*'){
            if(s[n] == p[m-1] || p[m-1] == '.'){
                dp[key] = (util(s, p, n-1, m) || util(s, p, n, m-2));
            }
            else{
                dp[key] = util(s, p, n, m-2);
            }
        }
        else if(p[m] == '.'){
            dp[key] = util(s, p, n-1, m-1);
        }
        else
            dp[key] = false;
    }

    return dp[key];
}

bool isMatch(string s, string p) {
    return util(s, p, s.length()-1, p.length()-1);
}
};
```

## Attempt 3 · 2023-05-07 09:59 IST · Wrong Answer · C++

[submission 945859184](https://leetcode.com/submissions/detail/945859184/) · tests 260/354

Failing input:

```text
"mississippi"
"mis*is*p*."
```

Expected:

```text
false
```

Your output:

```text
true
```

```cpp
class Solution {
    bool wildcardMatchingUtil(string & S1, string & S2, int i, int j, vector < vector < int >> & dp) {

      //Base Conditions
      if (i < 0 && j < 0)
        return true;
      if (i < 0 && j >= 0)
        return false;
      if (j < 0 && i >= 0)
        return true;
        // return starOnly(S1, i);

      if (dp[i][j] != -1) return dp[i][j];

      bool ans = false;
      // if (S1[i] == S2[j] || S1[i] == '.')
      if (S1[i] == S2[j])
        return ans =  dp[i][j] = wildcardMatchingUtil(S1, S2, i - 1, j - 1, dp);

      else {
        if (S1[i] == '*')
          return dp[i][j] = wildcardMatchingUtil(S1, S2, i - 1, j, dp) || wildcardMatchingUtil(S1, S2, i, j - 1, dp);
        else if(S1[i] == '.'){
          return dp[i][j] = wildcardMatchingUtil(S1, S2, i - 1, j - 1, dp);
        }
        else return dp[i][j] = false;
      }
    }
    bool starOnly(string &p, int m){
        // bool ans = true;
        for(int i=0;i<=m;i++){
            if(p[i] != '*'){
                return false;
            }
        }
        return true;
    }
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m=p.size();
        // vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
        // return rec(n-1, m-1, s, p, dp);

        vector<vector<int>> dp(m+1, vector<int>(n+1, -1));
        return wildcardMatchingUtil(p, s, m-1, n-1, dp);
    }
};
```
