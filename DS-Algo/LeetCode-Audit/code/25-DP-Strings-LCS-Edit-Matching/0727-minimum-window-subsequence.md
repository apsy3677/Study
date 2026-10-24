# 727. Minimum Window Subsequence

[Problem](https://leetcode.com/problems/minimum-window-subsequence/) · Hard · DP: Strings (LCS, Edit, Matching) → Subsequence window

LeetCode tags: string, dynamic-programming, sliding-window

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-05-05 19:00 IST · Accepted · C++

[submission 944967796](https://leetcode.com/submissions/detail/944967796/) · tests 68/68 · runtime 372 ms (beats 16.3%)

```cpp
class Solution {
public:
    string minWindow(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        // declare the DP table and initialize it with large values
        vector dp(n + 1, vector<int>(m + 1, 1000000000));
        // the base case of DP
        dp[0][0] = 0;
        int end = 0, length = n + 1;
        for (int i = 1; i <= n; i++) {
            // the base of DP
            dp[i][0] = 0;
            // DP transitions
            for (int j = 1; j <= m; j++) {
                // different transitions depending on whether or not s1[i - 1] == s2[j - 1]
                dp[i][j] = 1 + (s1[i - 1] == s2[j - 1] ? dp[i - 1][j - 1] : dp[i - 1][j]);
            }
            // update the answer
            if (dp[i][m] < length) {
                length = dp[i][m];
                end = i;
            }
        }
        // return the answer
        return length > n ? "" : s1.substr(end - length, length);
    }
};
```

## Attempt 2 · 2023-05-05 19:04 IST · Accepted · C++

[submission 944969484](https://leetcode.com/submissions/detail/944969484/) · tests 68/68 · runtime 8 ms (beats 68.5%)

```cpp
class Solution {
    int f(int n, int m, string &s1, string &s2){
        if(m == 0){
            return 0;
        }
        return 0;
    }
public:
    string minWindow(string s1, string s2) {
        int m = s1.size();
        int n = s2.size();
        int start = 0, len = INT_MAX, count = 0;
        for (int i = 0; i < m; i++)
        {
            if (s1[i] == s2[count]) count++;

            // all characters in s2 are matched. now reduce the window to the right most part which has all the characters in s2
            if (count == n)
            {
                int j = i;
                while (count > 0)
                {
                    if (s2[count - 1] == s1[j--])
                    {
                        count--;
                    }
                }
                j++; // index in s1 which is the first character in s2

                if (len > i - j + 1)
                {
                    len = i - j + 1;
                    start = j;
                }
                // move back i so it starts next search from j+1 in next iteration
                i = j;
            }
        }
        if (len == INT_MAX) return "";
        return s1.substr(start, len);
    }
};
```

## Attempt 3 · 2023-05-08 09:50 IST · Accepted · C++

[submission 946400703](https://leetcode.com/submissions/detail/946400703/) · tests 68/68 · runtime 10 ms (beats 64.1%)

```cpp
class Solution {
    int f(int n, int m, string &s1, string &s2){
        if(m == 0){
            return 0;
        }
        return 0;
    }
    string minWin(string &s1, string &s2){
        int len = INT_MAX, start = 0;
        int ind2 = 0;
        for(int ind1=0;ind1<s1.size();ind1++){
            if(s1[ind1] == s2[ind2]) ind2++;

            if(ind2 == s2.size()){
                // all chars are matched 
                // traverse backwards
                int revInd1 = ind1;
                while(ind2 > 0){
                    if(s2[ind2 - 1] == s1[revInd1]) ind2--;
                    revInd1--; // move 1 char back in s1
                }
                // revInd is pointing to 1 element before 1st char matched
                revInd1++;
                if(ind1 - revInd1 + 1 < len){
                    len = ind1-revInd1+1;
                    start = revInd1;
                }
                ind1 = revInd1; // ind1 will  get ind1++ in next iteration and will satrt finding a new one
            }
        }
        if(len == INT_MAX) return "";
        return s1.substr(start, len);
    }
public:
    string minWindow(string s1, string s2) {
        return minWin(s1, s2);
    }
};
```
