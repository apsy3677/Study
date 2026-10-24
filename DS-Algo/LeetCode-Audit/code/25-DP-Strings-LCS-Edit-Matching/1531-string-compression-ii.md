# 1531. String Compression II

[Problem](https://leetcode.com/problems/string-compression-ii/) · Hard · DP: Strings (LCS, Edit, Matching) → Run-length DP

LeetCode tags: string, dynamic-programming

Attempts since Mar 2023: 5 · accepted: 3 · failed before first AC: 2

## Attempt 1 · 2023-03-26 23:24 IST · Time Limit Exceeded · C++

[submission 922576762](https://leetcode.com/submissions/detail/922576762/) · tests 53/144

Failing input:

```text
"bbbcbbccaaacabacccaccbabcaacab"
15
```

Expected:

```text
5
```

```cpp
// class Solution {
// public:
//     vector<int> _9s = {1,9,99,999,9999};
//     string str;
//     int n;
//     bool check(int count){
//         for(auto x: _9s) if(x==count) return true;
//         return false;
//     }
    
//     int dp(int idx, char last, int len, int k){
//         if(k<0) return INT_MAX;
//         if(idx == n) return 0;

//         int ifDelete = dp(idx+1,last,len,k-1);
//         int keep = 0;
//         if(str[idx] == last)
//         {
//             if(len==1 || len==9 || len==99)     keep++;
//             keep += dp(idx+1, last, len+1, k);
//         }
//         else    keep = 1 + dp(idx+1, str[idx], 1, k);
//         return min(ifDelete, keep);

//         // int remove =INT_MAX, take =0;
//         // // cout<<idx<<" "<<k<<" "<<last<<" "<<count<<" {"<<remove<<" "<<take<<"} :: ";
//         // remove = dp(s, idx+1,k-1,last, count);
//         // if(last == s[idx]){
//         //     if(count ==1 || count ==9 || count ==99) take++;
//         //     take = dp(s, idx+1, k, last, count+1);
//         // }
//         // else{
//         //     take = dp(s, idx+1, k, s[idx], 1) + 1;
//         // }
//         // int ans = min(remove, take);
        
//         // return ans;
//     }
//     int getLengthOfOptimalCompression(string s, int k) {
//         str = s;
//         n =s.size();
//         return dp(0,'a',0,k);
//         // return dp(s,0,k,'a',0);
//     }
// };
int dp[101][27][101][101];
class Solution {
public:
    string str;
    int n;
    int minLength(int i, int prev, int len, int k)
    {
        if(k<0)    return INT_MAX;
        if(i>=n)    return 0;
        // if(dp[i][prev][len][k] != -1)   return dp[i][prev][len][k];
        int ifDelete = minLength(i+1,prev,len,k-1);
        int keep = 0;
        if(str[i]-'a' == prev)
        {
            if(len==1 || len==9 || len==99)     keep++;
            keep += minLength(i+1, prev, len+1, k);
        }
        else    keep = 1 + minLength(i+1, str[i]-'a', 1, k);
        // return dp[i][prev][len][k] = min(ifDelete, keep);
        return  min(ifDelete, keep);
    }
    int getLengthOfOptimalCompression(string s, int k) {
        str = s;
        n = s.size();
        memset(dp,-1,sizeof(dp));
        return minLength(0,26,0,k);
    }
};
```

## Attempt 2 · 2023-03-26 23:32 IST · Time Limit Exceeded · C++

[submission 922581097](https://leetcode.com/submissions/detail/922581097/) · tests 53/144

Failing input:

```text
"bbbcbbccaaacabacccaccbabcaacab"
15
```

Expected:

```text
5
```

```cpp
// class Solution {
// public:
//     vector<int> _9s = {1,9,99,999,9999};
//     string str;
//     int n;
//     bool check(int count){
//         for(auto x: _9s) if(x==count) return true;
//         return false;
//     }
    
//     int dp(int idx, char last, int len, int k){
//         if(k<0) return INT_MAX;
//         if(idx == n) return 0;

//         int ifDelete = dp(idx+1,last,len,k-1);
//         int keep = 0;
//         if(str[idx] == last)
//         {
//             if(len==1 || len==9 || len==99)     keep++;
//             keep += dp(idx+1, last, len+1, k);
//         }
//         else    keep = 1 + dp(idx+1, str[idx], 1, k);
//         return min(ifDelete, keep);

//         // int remove =INT_MAX, take =0;
//         // // cout<<idx<<" "<<k<<" "<<last<<" "<<count<<" {"<<remove<<" "<<take<<"} :: ";
//         // remove = dp(s, idx+1,k-1,last, count);
//         // if(last == s[idx]){
//         //     if(count ==1 || count ==9 || count ==99) take++;
//         //     take = dp(s, idx+1, k, last, count+1);
//         // }
//         // else{
//         //     take = dp(s, idx+1, k, s[idx], 1) + 1;
//         // }
//         // int ans = min(remove, take);
        
//         // return ans;
//     }
//     int getLengthOfOptimalCompression(string s, int k) {
//         str = s;
//         n =s.size();
//         return dp(0,'a',0,k);
//         // return dp(s,0,k,'a',0);
//     }
// };
int dp[101][27][101][101];
class Solution {
public:
    string str;
    int n;
    int func(int idx, char last, int len, int k){
        if(k<0) return INT_MAX;
        if(idx == n) return 0;
        if(dp[idx][last][len][k] != -1)   return dp[idx][last][len][k];
        int ifDelete = func(idx+1,last,len,k-1);
        int keep = 0;
        if(str[idx] == last)
        {
            if(len==1 || len==9 || len==99)     keep++;
            keep += func(idx+1, last, len+1, k);
        }
        else    keep = 1 + func(idx+1, str[idx], 1, k);
        return dp[idx][last][len][k] = min(ifDelete, keep);
        // return min(ifDelete, keep);
    }
    int minLength(int i, int prev, int len, int k)
    {
        if(k<0)    return INT_MAX;
        if(i>=n)    return 0;
        // if(dp[i][prev][len][k] != -1)   return dp[i][prev][len][k];
        int ifDelete = minLength(i+1,prev,len,k-1);
        int keep = 0;
        if(str[i]-'a' == prev)
        {
            if(len==1 || len==9 || len==99)     keep++;
            keep += minLength(i+1, prev, len+1, k);
        }
        else    keep = 1 + minLength(i+1, str[i]-'a', 1, k);
        // return dp[i][prev][len][k] = min(ifDelete, keep);
        return  min(ifDelete, keep);
    }
    int getLengthOfOptimalCompression(string s, int k) {
        str = s;
        n = s.size();
        memset(dp,-1,sizeof(dp));
        return minLength(0,'a',0,k);
        // return minLength(0,26,0,k);
    }
};
```

## Attempt 3 · 2023-03-26 23:33 IST · Accepted · C++

[submission 922581859](https://leetcode.com/submissions/detail/922581859/) · tests 144/144 · runtime 2297 ms (beats 5.4%)

```cpp
// class Solution {
// public:
//     vector<int> _9s = {1,9,99,999,9999};
//     string str;
//     int n;
//     bool check(int count){
//         for(auto x: _9s) if(x==count) return true;
//         return false;
//     }
    
//     int dp(int idx, char last, int len, int k){
//         if(k<0) return INT_MAX;
//         if(idx == n) return 0;

//         int ifDelete = dp(idx+1,last,len,k-1);
//         int keep = 0;
//         if(str[idx] == last)
//         {
//             if(len==1 || len==9 || len==99)     keep++;
//             keep += dp(idx+1, last, len+1, k);
//         }
//         else    keep = 1 + dp(idx+1, str[idx], 1, k);
//         return min(ifDelete, keep);

//         // int remove =INT_MAX, take =0;
//         // // cout<<idx<<" "<<k<<" "<<last<<" "<<count<<" {"<<remove<<" "<<take<<"} :: ";
//         // remove = dp(s, idx+1,k-1,last, count);
//         // if(last == s[idx]){
//         //     if(count ==1 || count ==9 || count ==99) take++;
//         //     take = dp(s, idx+1, k, last, count+1);
//         // }
//         // else{
//         //     take = dp(s, idx+1, k, s[idx], 1) + 1;
//         // }
//         // int ans = min(remove, take);
        
//         // return ans;
//     }
//     int getLengthOfOptimalCompression(string s, int k) {
//         str = s;
//         n =s.size();
//         return dp(0,'a',0,k);
//         // return dp(s,0,k,'a',0);
//     }
// };
int dp[101][27][101][101];
class Solution {
public:
    string str;
    int n;
    int func(int idx, char last, int len, int k){
        if(k<0) return INT_MAX;
        if(idx == n) return 0;
        if(dp[idx][last][len][k] != -1)   return dp[idx][last][len][k];
        int ifDelete = func(idx+1,last,len,k-1);
        int keep = 0;
        if(str[idx] == last)
        {
            if(len==1 || len==9 || len==99)     keep++;
            keep += func(idx+1, last, len+1, k);
        }
        else    keep = 1 + func(idx+1, str[idx], 1, k);
        return dp[idx][last][len][k] = min(ifDelete, keep);
        // return min(ifDelete, keep);
    }
    int minLength(int i, int prev, int len, int k)
    {
        if(k<0)    return INT_MAX;
        if(i>=n)    return 0;
        if(dp[i][prev][len][k] != -1)   return dp[i][prev][len][k];
        int ifDelete = minLength(i+1,prev,len,k-1);
        int keep = 0;
        if(str[i]-'a' == prev)
        {
            if(len==1 || len==9 || len==99)     keep++;
            keep += minLength(i+1, prev, len+1, k);
        }
        else    keep = 1 + minLength(i+1, str[i]-'a', 1, k);
        return dp[i][prev][len][k] = min(ifDelete, keep);
        return  min(ifDelete, keep);
    }
    int getLengthOfOptimalCompression(string s, int k) {
        str = s;
        n = s.size();
        memset(dp,-1,sizeof(dp));
        // return func(0,'a',0,k);
        return minLength(0,26,0,k);
    }
};
```

## Attempt 4 · 2023-03-30 22:49 IST · Accepted · C++

[submission 924944608](https://leetcode.com/submissions/detail/924944608/) · tests 144/144 · runtime 2324 ms (beats 5.4%)

```cpp
// class Solution {
// public:
//     vector<int> _9s = {1,9,99,999,9999};
//     string str;
//     int n;
//     bool check(int count){
//         for(auto x: _9s) if(x==count) return true;
//         return false;
//     }
    
//     int dp(int idx, char last, int len, int k){
//         if(k<0) return INT_MAX;
//         if(idx == n) return 0;

//         int ifDelete = dp(idx+1,last,len,k-1);
//         int keep = 0;
//         if(str[idx] == last)
//         {
//             if(len==1 || len==9 || len==99)     keep++;
//             keep += dp(idx+1, last, len+1, k);
//         }
//         else    keep = 1 + dp(idx+1, str[idx], 1, k);
//         return min(ifDelete, keep);

//         // int remove =INT_MAX, take =0;
//         // // cout<<idx<<" "<<k<<" "<<last<<" "<<count<<" {"<<remove<<" "<<take<<"} :: ";
//         // remove = dp(s, idx+1,k-1,last, count);
//         // if(last == s[idx]){
//         //     if(count ==1 || count ==9 || count ==99) take++;
//         //     take = dp(s, idx+1, k, last, count+1);
//         // }
//         // else{
//         //     take = dp(s, idx+1, k, s[idx], 1) + 1;
//         // }
//         // int ans = min(remove, take);
        
//         // return ans;
//     }
//     int getLengthOfOptimalCompression(string s, int k) {
//         str = s;
//         n =s.size();
//         return dp(0,'a',0,k);
//         // return dp(s,0,k,'a',0);
//     }
// };
int dp[101][27][101][101];
class Solution {
public:
    string str;
    int n;
    int func(int idx, char last, int len, int k){
        if(k<0) return INT_MAX;
        if(idx == n) return 0;
        if(dp[idx][last-'a'][len][k] != -1)   return dp[idx][last-'a'][len][k];
        int ifDelete = func(idx+1,last,len,k-1);
        int keep = 0;
        if(str[idx] == last)
        {
            if(len==1 || len==9 || len==99)     keep++;
            keep += func(idx+1, last, len+1, k);
        }
        else    keep = 1 + func(idx+1, str[idx], 1, k);
        return dp[idx][last-'a'][len][k] = min(ifDelete, keep);
        // return min(ifDelete, keep);
    }
    int minLength(int i, int prev, int len, int k)
    {
        if(k<0)    return INT_MAX;
        if(i>=n)    return 0;
        if(dp[i][prev][len][k] != -1)   return dp[i][prev][len][k];
        int ifDelete = minLength(i+1,prev,len,k-1);
        int keep = 0;
        if(str[i]-'a' == prev)
        {
            if(len==1 || len==9 || len==99)     keep++;
            keep += minLength(i+1, prev, len+1, k);
        }
        else    keep = 1 + minLength(i+1, str[i]-'a', 1, k);
        return dp[i][prev][len][k] = min(ifDelete, keep);
        return  min(ifDelete, keep);
    }
    int getLengthOfOptimalCompression(string s, int k) {
        str = s;
        n = s.size();
        memset(dp,-1,sizeof(dp));
        return func(0,'z',0,k);
        // return minLength(0,26,0,k);
    }
};
```

## Attempt 5 · 2023-03-30 22:52 IST · Accepted · C++

[submission 924946354](https://leetcode.com/submissions/detail/924946354/) · tests 144/144 · runtime 2306 ms (beats 5.4%)

```cpp
// class Solution {
// public:
//     vector<int> _9s = {1,9,99,999,9999};
//     string str;
//     int n;
//     bool check(int count){
//         for(auto x: _9s) if(x==count) return true;
//         return false;
//     }
    
//     int dp(int idx, char last, int len, int k){
//         if(k<0) return INT_MAX;
//         if(idx == n) return 0;

//         int ifDelete = dp(idx+1,last,len,k-1);
//         int keep = 0;
//         if(str[idx] == last)
//         {
//             if(len==1 || len==9 || len==99)     keep++;
//             keep += dp(idx+1, last, len+1, k);
//         }
//         else    keep = 1 + dp(idx+1, str[idx], 1, k);
//         return min(ifDelete, keep);

//         // int remove =INT_MAX, take =0;
//         // // cout<<idx<<" "<<k<<" "<<last<<" "<<count<<" {"<<remove<<" "<<take<<"} :: ";
//         // remove = dp(s, idx+1,k-1,last, count);
//         // if(last == s[idx]){
//         //     if(count ==1 || count ==9 || count ==99) take++;
//         //     take = dp(s, idx+1, k, last, count+1);
//         // }
//         // else{
//         //     take = dp(s, idx+1, k, s[idx], 1) + 1;
//         // }
//         // int ans = min(remove, take);
        
//         // return ans;
//     }
//     int getLengthOfOptimalCompression(string s, int k) {
//         str = s;
//         n =s.size();
//         return dp(0,'a',0,k);
//         // return dp(s,0,k,'a',0);
//     }
// };
int dp[101][27][101][101];
class Solution {
public:
    string str;
    int n;
    int func(int idx, char last, int len, int k){
        if(k<0) return INT_MAX;
        if(idx == n) return 0;
        if(dp[idx][last-'a'][len][k] != -1)   return dp[idx][last-'a'][len][k];
        int ifDelete = func(idx+1,last,len,k-1);
        int keep = 0;
        if(str[idx] == last)
        {
            if(len==1 || len==9 || len==99)     keep++;
            keep += func(idx+1, last, len+1, k);
        }
        else    keep = 1 + func(idx+1, str[idx], 1, k);
        return dp[idx][last-'a'][len][k] = min(ifDelete, keep);
        // return min(ifDelete, keep);
    }
    int minLength(int i, int prev, int len, int k)
    {
        if(k<0)    return INT_MAX;
        if(i>=n)    return 0;
        if(dp[i][prev][len][k] != -1)   return dp[i][prev][len][k];
        int ifDelete = minLength(i+1,prev,len,k-1);
        int keep = 0;
        if(str[i]-'a' == prev)
        {
            if(len==1 || len==9 || len==99)     keep++;
            keep += minLength(i+1, prev, len+1, k);
        }
        else    keep = 1 + minLength(i+1, str[i]-'a', 1, k);
        return dp[i][prev][len][k] = min(ifDelete, keep);
        return  min(ifDelete, keep);
    }
    int getLengthOfOptimalCompression(string s, int k) {
        str = s;
        n = s.size();
        memset(dp,-1,sizeof(dp));
        return func(0,'z'+1,0,k);
        // return minLength(0,26,0,k);
    }
};
```
