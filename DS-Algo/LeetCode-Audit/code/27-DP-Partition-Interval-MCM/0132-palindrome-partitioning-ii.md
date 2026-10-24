# 132. Palindrome Partitioning II

[Problem](https://leetcode.com/problems/palindrome-partitioning-ii/) · Hard · DP: Partition / Interval (MCM) → Front partition DP

LeetCode tags: string, dynamic-programming

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-05-04 10:06 IST · Accepted · C++

[submission 944160153](https://leetcode.com/submissions/detail/944160153/) · tests 36/36 · runtime 390 ms (beats 44.4%)

```cpp
class Solution {
    bool isPalindrome(int start, int end, string &s){
        while(start < end){
            if(s[start++] != s[end--]) return false;
        }
        return true;
    }
    int f(int i, string &s, vector<int> &dp){
        if(i==s.size()) return 0;
        
        if(dp[i] != -1) return dp[i];
        // string i to j
        int mini = 1e9;
        for(int j=i;j<s.size();j++){
            if(isPalindrome(i,j,s)){
                int cost = 1 + f(j+1,s,dp);
                mini = min(mini, cost);
            }
        }
        return dp[i] = mini;
    }
public:
    int minCut(string s) {
        int n = s.size();
        vector<int> dp(n, -1);
        return f(0,s, dp) -1;
    }
};
```

## Attempt 2 · 2023-05-04 10:11 IST · Accepted · C++

[submission 944161976](https://leetcode.com/submissions/detail/944161976/) · tests 36/36 · runtime 655 ms (beats 44.4%)

```cpp
class Solution {
    bool isPalindrome(int start, int end, string &s){
        while(start < end){
            if(s[start++] != s[end--]) return false;
        }
        return true;
    }
    int f(int i, string &s, vector<int> &dp){
        if(i==s.size()) return 0;
        
        if(dp[i] != -1) return dp[i];
        // string i to j
        int mini = 1e9;
        for(int j=i;j<s.size();j++){
            if(isPalindrome(i,j,s)){
                int cost = 1 + f(j+1,s,dp);
                mini = min(mini, cost);
            }
        }
        return dp[i] = mini;
    }
    int tabulation(string s){
        int n = s.size();
        vector<int> dp(n+1, 0);
        dp[n] = 0;

        for(int i=n-1;i>=0;i--){
            int mini = 1e9;
            for(int j=i;j<s.size();j++){
                if(isPalindrome(i,j,s)){
                    int cost = 1 + f(j+1,s,dp);
                    mini = min(mini, cost);
                }
            }
            dp[i] = mini;
        }
        return dp[0]-1;
    }
public:
    int minCut(string s) {
        int n = s.size();
        vector<int> dp(n, -1);
        return tabulation(s);
        // return f(0,s, dp) -1;
    }
};
```

## Attempt 3 · 2023-05-04 10:12 IST · Accepted · C++

[submission 944162403](https://leetcode.com/submissions/detail/944162403/) · tests 36/36 · runtime 646 ms (beats 44.4%)

```cpp
class Solution {
    bool isPalindrome(int start, int end, string &s){
        while(start < end){
            if(s[start++] != s[end--]) return false;
        }
        return true;
    }
    int f(int i, string &s, vector<int> &dp){
        if(i==s.size()) return 0;
        
        if(dp[i] != -1) return dp[i];
        // string i to j
        int mini = 1e9;
        for(int j=i;j<s.size();j++){
            if(isPalindrome(i,j,s)){
                int cost = 1 + f(j+1,s,dp);
                mini = min(mini, cost);
            }
        }
        return dp[i] = mini;
    }
    int tabulation(string s){
        int n = s.size();
        vector<int> dp(n+1, 0);
        dp[n] = 0;

        for(int i=n-1;i>=0;i--){
            int mini = 1e9;
            for(int j=i;j<s.size();j++){
                if(isPalindrome(i,j,s)){
                    int cost = 1 + dp[j+1];
                    mini = min(mini, cost);
                }
            }
            dp[i] = mini;
        }
        return dp[0]-1;
    }
public:
    int minCut(string s) {
        int n = s.size();
        vector<int> dp(n, -1);
        return tabulation(s);
        // return f(0,s, dp) -1;
    }
};
```
