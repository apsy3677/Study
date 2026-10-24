# 44. Wildcard Matching

[Problem](https://leetcode.com/problems/wildcard-matching/) · Hard · DP: Strings (LCS, Edit, Matching) → Pattern matching

LeetCode tags: string, dynamic-programming, greedy, recursion

Attempts since Mar 2023: 6 · accepted: 3 · failed before first AC: 2

## Attempt 1 · 2023-03-13 17:49 IST · Wrong Answer · C++

[submission 914349601](https://leetcode.com/submissions/detail/914349601/) · tests 1479/1811

Failing input:

```text
"acdcb"
"a*c?b"
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
public:
    bool starOnly(string &p, int m){
        // bool ans = true;
        for(int i=0;i<=m;i++){
            if(p[i] != '*'){
                return false;
            }
        }
        return true;
    }
    bool rec(int n,int m, string &s, string &p, vector<vector<int>> &dp){

        if(n<0 && m<0){
            // both strings are traversed and matched
            return true;
        }
        if(m<0 && n>=0){
            // p is exhausted and s is still remaining then no match
            return false;
        }
        
        if(n<0 && m>=0){
            // s is exhausted and m is remaining
            if(starOnly(p, m)){
                return true;
            }
            else{
                return false;
            }
        }

        if(dp[n][m] != -1){
            return dp[n][m];
        }
        bool ans = false;
        if(s[n] == p[m] || p[m] == '?'){
            ans = rec(n-1, m-1, s, p, dp);
        }
        else{

            if(p[m] == '*'){
                // * can match "" empty and multiple chars
                // match all subsequences by matching nth char of s and again mathcing * for n-1, .... 0th char of s
                ans = rec(n, m-1, s, p, dp) /* replace * with nothing*/ || 
                        rec(n-1, m, s, p, dp); /* replace * with nth char*/
            }
            else{
                ans = rec(n-1, m, s, p, dp);
            }
        }
        return dp[n][m] = ans;
    }
    bool isMatch(string s, string p) {
        int n = s.size(), m=p.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, -1));

        return rec(n-1, m-1, s, p, dp);
    }
};
```

## Attempt 2 · 2023-03-13 17:54 IST · Time Limit Exceeded · C++

[submission 914351652](https://leetcode.com/submissions/detail/914351652/) · tests 1611/1811

Failing input:

```text
"aaaaaaabaaababbbabbbaabbaabbaaaaaabaabbaaababababab"
"ba******"
```

Expected:

```text
false
```

```cpp
class Solution {
public:
    bool isAllStars(string & S1, int i) {
  for (int j = 0; j <= i; j++) {
    if (S1[j] != '*')
      return false;
  }
  return true;
}

bool wildcardMatchingUtil(string & S1, string & S2, int i, int j, vector < vector < int >> & dp) {

  //Base Conditions
  if (i < 0 && j < 0)
    return true;
  if (i < 0 && j >= 0)
    return false;
  if (j < 0 && i >= 0)
    return isAllStars(S1, i);

  if (dp[i][j] != -1) return dp[i][j];

  if (S1[i] == S2[j] || S1[i] == '?')
    return dp[i][j] = wildcardMatchingUtil(S1, S2, i - 1, j - 1, dp);

  else {
    if (S1[i] == '*')
      return wildcardMatchingUtil(S1, S2, i - 1, j, dp) || wildcardMatchingUtil(S1, S2, i, j - 1, dp);
    else return false;
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
    bool rec(int n,int m, string &s, string &p, vector<vector<int>> &dp){

        if(n<0 && m<0){
            // both strings are traversed and matched
            return true;
        }
        if(m<0 && n>=0){
            // p is exhausted and s is still remaining then no match
            return false;
        }
        
        if(n<0 && m>=0){
            // s is exhausted and m is remaining
            if(starOnly(p, m)){
                return true;
            }
            else{
                return false;
            }
        }

        if(dp[n][m] != -1){
            return dp[n][m];
        }
        bool ans = false;
        if(s[n] == p[m] || p[m] == '?'){
            ans = rec(n-1, m-1, s, p, dp);
        }
        else{

            if(p[m] == '*'){
                // * can match "" empty and multiple chars
                // match all subsequences by matching nth char of s and again mathcing * for n-1, .... 0th char of s
                ans = rec(n, m-1, s, p, dp) /* replace * with nothing*/ || 
                        rec(n-1, m, s, p, dp); /* replace * with nth char*/
            }
            else{
                ans = rec(n-1, m, s, p, dp);
            }
        }
        return dp[n][m] = ans;
    }
    bool isMatch(string s, string p) {
        int n = s.size(), m=p.size();
        // vector<vector<int>> dp(n+1, vector<int>(m+1, -1));

        vector<vector<int>> dp(m+1, vector<int>(n+1, -1));
        return wildcardMatchingUtil(p, s, m-1, n-1, dp);
        // return rec(n-1, m-1, s, p, dp);
    }
};
```

## Attempt 3 · 2023-03-13 17:59 IST · Accepted · C++

[submission 914353737](https://leetcode.com/submissions/detail/914353737/) · tests 1811/1811 · runtime 55 ms (beats 48.4%)

```cpp
class Solution {
public:
    bool isAllStars(string & S1, int i) {
  for (int j = 0; j <= i; j++) {
    if (S1[j] != '*')
      return false;
  }
  return true;
}

bool wildcardMatchingUtil(string & S1, string & S2, int i, int j, vector < vector < int >> & dp) {

  //Base Conditions
  if (i < 0 && j < 0)
    return true;
  if (i < 0 && j >= 0)
    return false;
  if (j < 0 && i >= 0)
    return isAllStars(S1, i);

  if (dp[i][j] != -1) return dp[i][j];

  if (S1[i] == S2[j] || S1[i] == '?')
    return dp[i][j] = wildcardMatchingUtil(S1, S2, i - 1, j - 1, dp);

  else {
    if (S1[i] == '*')
      return wildcardMatchingUtil(S1, S2, i - 1, j, dp) || wildcardMatchingUtil(S1, S2, i, j - 1, dp);
    else return false;
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
    bool rec(int n,int m, string &s, string &p, vector<vector<int>> &dp){

        if(n<0 && m<0){
            // both strings are traversed and matched
            return true;
        }
        if(m<0 && n>=0){
            // p is exhausted and s is still remaining then no match
            return false;
        }
        
        if(n<0 && m>=0){
            // s is exhausted and m is remaining
            return starOnly(p, m);
        }

        if(dp[n][m] != -1){
            return dp[n][m];
        }
        bool ans;
        if(s[n] == p[m] || p[m] == '?'){
            ans = rec(n-1, m-1, s, p, dp);
        }
        else{

            if(p[m] == '*'){
                // * can match "" empty and multiple chars
                // match all subsequences by matching nth char of s and again mathcing * for n-1, .... 0th char of s
                ans = rec(n, m-1, s, p, dp) /* replace * with nothing*/ || 
                        rec(n-1, m, s, p, dp); /* replace * with nth char*/
            }
            else{
                // This is wrong
                // ans = rec(n-1, m, s, p, dp);
                // No match so return false directly
                return false;
            }
        }
        return dp[n][m] = ans;
    }
    bool isMatch(string s, string p) {
        int n = s.size(), m=p.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
        return rec(n-1, m-1, s, p, dp);

        // vector<vector<int>> dp(m+1, vector<int>(n+1, -1));
        // return wildcardMatchingUtil(p, s, m-1, n-1, dp);
    }
};
```

## Attempt 4 · 2023-05-03 11:20 IST · Time Limit Exceeded · C++

[submission 943630731](https://leetcode.com/submissions/detail/943630731/) · tests 1583/1811

Failing input:

```text
"bbbababbabbbbabbbbaabaaabbbbabbbababbbbababaabbbab"
"a******b*"
```

Expected:

```text
false
```

```cpp
class Solution {
public:
    bool isAllStars(string & S1, int i) {
  for (int j = 0; j <= i; j++) {
    if (S1[j] != '*')
      return false;
  }
  return true;
}

    bool wildcardMatchingUtil(string & S1, string & S2, int i, int j, vector < vector < int >> & dp) {

      //Base Conditions
      if (i < 0 && j < 0)
        return true;
      if (i < 0 && j >= 0)
        return false;
      if (j < 0 && i >= 0)
        return isAllStars(S1, i);

      if (dp[i][j] != -1) return dp[i][j];

      if (S1[i] == S2[j] || S1[i] == '?')
        return dp[i][j] = wildcardMatchingUtil(S1, S2, i - 1, j - 1, dp);

      else {
        if (S1[i] == '*')
          return wildcardMatchingUtil(S1, S2, i - 1, j, dp) || wildcardMatchingUtil(S1, S2, i, j - 1, dp);
        else return false;
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
    bool rec(int n,int m, string &s, string &p, vector<vector<int>> &dp){

        if(n<0 && m<0){
            // both strings are traversed and matched
            return true;
        }
        if(m<0 && n>=0){
            // p is exhausted and s is still remaining then no match
            return false;
        }
        
        if(n<0 && m>=0){
            // s is exhausted and m is remaining
            return starOnly(p, m);
        }

        if(dp[n][m] != -1){
            return dp[n][m];
        }
        bool ans = false;
        if(s[n] == p[m] || p[m] == '?'){
            ans = rec(n-1, m-1, s, p, dp);
        }
        else{

            if(p[m] == '*'){
                // * can match "" empty and multiple chars
                // match all subsequences by matching nth char of s and again mathcing * for n-1, .... 0th char of s
                ans = rec(n, m-1, s, p, dp) /* replace * with nothing*/ || 
                        rec(n-1, m, s, p, dp); /* replace * with nth char*/
            }
            else{
                // This is wrong
                // ans = rec(n-1, m, s, p, dp);
                // No match so return false directly
                ans =  false;
            }
        }
        return dp[n][m] = ans;
    }
    bool isMatch(string s, string p) {
        int n = s.size(), m=p.size();
        // vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
        // return rec(n-1, m-1, s, p, dp);

        vector<vector<int>> dp(m+1, vector<int>(n+1, -1));
        return wildcardMatchingUtil(p, s, m-1, n-1, dp);
    }
};
```

## Attempt 5 · 2023-05-03 11:22 IST · Accepted · C++

[submission 943631756](https://leetcode.com/submissions/detail/943631756/) · tests 1811/1811 · runtime 53 ms (beats 51.0%)

```cpp
class Solution {
public:
    bool isAllStars(string & S1, int i) {
  for (int j = 0; j <= i; j++) {
    if (S1[j] != '*')
      return false;
  }
  return true;
}

    bool wildcardMatchingUtil(string & S1, string & S2, int i, int j, vector < vector < int >> & dp) {

      //Base Conditions
      if (i < 0 && j < 0)
        return true;
      if (i < 0 && j >= 0)
        return false;
      if (j < 0 && i >= 0)
        return isAllStars(S1, i);

      if (dp[i][j] != -1) return dp[i][j];

      bool ans = false;
      if (S1[i] == S2[j] || S1[i] == '?')
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
    bool rec(int n,int m, string &s, string &p, vector<vector<int>> &dp){

        if(n<0 && m<0){
            // both strings are traversed and matched
            return true;
        }
        if(m<0 && n>=0){
            // p is exhausted and s is still remaining then no match
            return false;
        }
        
        if(n<0 && m>=0){
            // s is exhausted and m is remaining
            return starOnly(p, m);
        }

        if(dp[n][m] != -1){
            return dp[n][m];
        }
        bool ans = false;
        if(s[n] == p[m] || p[m] == '?'){
            ans = rec(n-1, m-1, s, p, dp);
        }
        else{

            if(p[m] == '*'){
                // * can match "" empty and multiple chars
                // match all subsequences by matching nth char of s and again mathcing * for n-1, .... 0th char of s
                ans = rec(n, m-1, s, p, dp) /* replace * with nothing*/ || 
                        rec(n-1, m, s, p, dp); /* replace * with nth char*/
            }
            else{
                // This is wrong
                // ans = rec(n-1, m, s, p, dp);
                // No match so return false directly
                ans =  false;
            }
        }
        return dp[n][m] = ans;
    }
    bool isMatch(string s, string p) {
        int n = s.size(), m=p.size();
        // vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
        // return rec(n-1, m-1, s, p, dp);

        vector<vector<int>> dp(m+1, vector<int>(n+1, -1));
        return wildcardMatchingUtil(p, s, m-1, n-1, dp);
    }
};
```

## Attempt 6 · 2023-05-03 11:23 IST · Accepted · C++

[submission 943632100](https://leetcode.com/submissions/detail/943632100/) · tests 1811/1811 · runtime 53 ms (beats 51.0%)

```cpp
class Solution {
public:
    bool isAllStars(string & S1, int i) {
  for (int j = 0; j <= i; j++) {
    if (S1[j] != '*')
      return false;
  }
  return true;
}

    bool wildcardMatchingUtil(string & S1, string & S2, int i, int j, vector < vector < int >> & dp) {

      //Base Conditions
      if (i < 0 && j < 0)
        return true;
      if (i < 0 && j >= 0)
        return false;
      if (j < 0 && i >= 0)
        return isAllStars(S1, i);

      if (dp[i][j] != -1) return dp[i][j];

      bool ans = false;
      if (S1[i] == S2[j] || S1[i] == '?')
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
    bool rec(int n,int m, string &s, string &p, vector<vector<int>> &dp){

        if(n<0 && m<0){
            // both strings are traversed and matched
            return true;
        }
        if(m<0 && n>=0){
            // p is exhausted and s is still remaining then no match
            return false;
        }
        
        if(n<0 && m>=0){
            // s is exhausted and m is remaining
            return starOnly(p, m);
        }

        if(dp[n][m] != -1){
            return dp[n][m];
        }
        bool ans = false;
        if(s[n] == p[m] || p[m] == '?'){
            ans = rec(n-1, m-1, s, p, dp);
        }
        else{

            if(p[m] == '*'){
                // * can match "" empty and multiple chars
                // match all subsequences by matching nth char of s and again mathcing * for n-1, .... 0th char of s
                ans = rec(n, m-1, s, p, dp) /* replace * with nothing*/ || 
                        rec(n-1, m, s, p, dp); /* replace * with nth char*/
            }
            else{
                // This is wrong
                // ans = rec(n-1, m, s, p, dp);
                // No match so return false directly
                ans =  false;
            }
        }
        return dp[n][m] = ans;
    }
    bool isMatch(string s, string p) {
        int n = s.size(), m=p.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
        return rec(n-1, m-1, s, p, dp);

        // vector<vector<int>> dp(m+1, vector<int>(n+1, -1));
        // return wildcardMatchingUtil(p, s, m-1, n-1, dp);
    }
};
```
