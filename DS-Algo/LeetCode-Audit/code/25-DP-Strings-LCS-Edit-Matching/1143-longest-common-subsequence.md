# 1143. Longest Common Subsequence

[Problem](https://leetcode.com/problems/longest-common-subsequence/) · Medium · DP: Strings (LCS, Edit, Matching) → LCS

LeetCode tags: string, dynamic-programming, longest-common-subsequence

Attempts since Mar 2023: 5 · accepted: 3 · failed before first AC: 2

## Attempt 1 · 2023-03-13 11:53 IST · Time Limit Exceeded · C++

[submission 914209468](https://leetcode.com/submissions/detail/914209468/) · tests 46/47

Failing input:

```text
"ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc ... [1603 more chars]
```

Expected:

```text
0
```

```cpp
class Solution {
public:

    int lcs(int l1, int l2,string s1, string s2, vector<vector<int>> &dp){
        if(l1<0 || l2<0){
            return 0;
        }
        
        // Wrong base cases because l1 is 0 but l2 can be large and char at l1 can match with other chars(apart from l2) also in s2 
        // if(l1==0){
        //     return s1[l1] == s2[l2] ? 1: 0;
        // }
        // if(l2==0){
        //     return s1[l1] == s2[l2] ? 1: 0;
        // }
        if(dp[l1][l2] != -1)
            return dp[l1][l2];
        
        int equal =0, left =0, right =0;

        if(s1[l1] == s2[l2]){
            equal = 1 + lcs(l1-1, l2-1, s1,s2,dp);
        }
        else{
            left = 0 + lcs(l1-1, l2, s1, s2, dp);
            right = 0 + lcs(l1, l2-1, s1,s2,dp);
        }

        return dp[l1][l2]= max(equal, max(left,right));
    }

    int longestCommonSubsequence(string text1, string text2) {
        int l1 = text1.size(), l2 = text2.size();
        
        vector<vector<int>> dp (l1+1, vector<int>(l2+1, -1));
        return lcs(l1-1, l2-1, text1, text2, dp);
    }
};
```

## Attempt 2 · 2023-03-13 11:54 IST · Time Limit Exceeded · C++

[submission 914210046](https://leetcode.com/submissions/detail/914210046/) · tests 42/47

Failing input:

```text
"fcvafurqjylclorwfoladwfqzkbebslwnmpmlkbezkxoncvwhstwzwpqxqtyxozkpgtgtsjobujezgrkvevklmludgtyrmjaxyputqbyxqvupojutsjwlwluzsbmvyxifqtglwvcnkfsfglwjwrmtyxmdgjifyjwrsnenuvsdedsbqdovwzsdghclcdexmtsbexwrszihcpibwpidixmpmxshwzmjgtadmtkxqfkrsdqjcrmxkbkfoncrcvoxuvcdytajgfwrcxivixanuzerebuzklyhezevonqdsrkzetsrgfgxibqpmfuxcrinetyzkvudghgrytsvwzkjulmhanankxqfihenuhmfsfkfepibkjmzybmlkzozmluvybyzsleludsxkpiniz ... [1602 more chars]
```

Expected:

```text
323
```

```cpp
class Solution {
public:

    int lcs(int l1, int l2,string s1, string s2, vector<vector<int>> &dp){
        if(l1<0 || l2<0){
            return 0;
        }
        
        // Wrong base cases because l1 is 0 but l2 can be large and char at l1 can match with other chars(apart from l2) also in s2 
        // if(l1==0){
        //     return s1[l1] == s2[l2] ? 1: 0;
        // }
        // if(l2==0){
        //     return s1[l1] == s2[l2] ? 1: 0;
        // }
        if(dp[l1][l2] != -1)
            return dp[l1][l2];
        
        int equal =0, left =0, right =0;

        if(s1[l1] == s2[l2]){
            return dp[l1][l2] = equal = 1 + lcs(l1-1, l2-1, s1,s2,dp);
        }
        else{
            left = 0 + lcs(l1-1, l2, s1, s2, dp);
            right = 0 + lcs(l1, l2-1, s1,s2,dp);
            return dp[l1][l2] = max(left, right);
        }

        return dp[l1][l2]= max(equal, max(left,right));
    }

    int longestCommonSubsequence(string text1, string text2) {
        int l1 = text1.size(), l2 = text2.size();
        
        vector<vector<int>> dp (l1+1, vector<int>(l2+1, -1));
        return lcs(l1-1, l2-1, text1, text2, dp);
    }
};
```

## Attempt 3 · 2023-03-13 11:56 IST · Accepted · C++

[submission 914210738](https://leetcode.com/submissions/detail/914210738/) · tests 47/47 · runtime 101 ms (beats 5.2%)

```cpp
class Solution {
public:

    int lcs(int l1, int l2,string s1, string s2, vector<vector<int>> &dp){
        if(l1<0 || l2<0){
            return 0;
        }
        
        // Wrong base cases because l1 is 0 but l2 can be large and char at l1 can match with other chars(apart from l2) also in s2 
        // if(l1==0){
        //     return s1[l1] == s2[l2] ? 1: 0;
        // }
        // if(l2==0){
        //     return s1[l1] == s2[l2] ? 1: 0;
        // }
        if(dp[l1][l2] != -1)
            return dp[l1][l2];
        
        int equal =0, left =0, right =0;

        if(s1[l1] == s2[l2]){
            return dp[l1][l2] = equal = 1 + lcs(l1-1, l2-1, s1,s2,dp);
        }
        else{
            left = 0 + lcs(l1-1, l2, s1, s2, dp);
            right = 0 + lcs(l1, l2-1, s1,s2,dp);
            return dp[l1][l2] = max(left, right);
        }

        return dp[l1][l2]= max(equal, max(left,right));
    }

    int solveMem(string &a, string &b, int i, int j, vector<vector<int>> &dp){
        if(i >= a.size() || j >= b.size()) return 0;

        if(dp[i][j] != -1){
            return dp[i][j];
        }

        int ans = 0;
        if(a[i] == b[j]){
            ans = 1 + solveMem(a, b, i+1, j+1, dp);
        }
        else{
            ans = max( solveMem(a, b, i+1, j, dp), solveMem(a, b, i, j+1, dp) );
        }

        return dp[i][j] = ans;
    }

    int longestCommonSubsequence(string text1, string text2) {
        int l1 = text1.size(), l2 = text2.size();
        
        vector<vector<int>> dp (l1+1, vector<int>(l2+1, -1));
        return solveMem(text1, text2, 0, 0, dp);
        // return lcs(l1-1, l2-1, text1, text2, dp);
    }
};
```

## Attempt 4 · 2023-03-13 12:05 IST · Accepted · C++

[submission 914214722](https://leetcode.com/submissions/detail/914214722/) · tests 47/47 · runtime 94 ms (beats 5.2%)

```cpp
class Solution {
public:

    int lcs(int l1, int l2,string s1, string s2, vector<vector<int>> &dp){
        if(l1<0 || l2<0){
            return 0;
        }
        
        // Wrong base cases because l1 is 0 but l2 can be large and char at l1 can match with other chars(apart from l2) also in s2 
        // if(l1==0){
        //     return s1[l1] == s2[l2] ? 1: 0;
        // }
        // if(l2==0){
        //     return s1[l1] == s2[l2] ? 1: 0;
        // }
        if(dp[l1][l2] != -1)
            return dp[l1][l2];
        
        int equal =0, left =0, right =0;

        if(s1[l1] == s2[l2]){
            return dp[l1][l2] = equal = 1 + lcs(l1-1, l2-1, s1,s2,dp);
        }
        else{
            left = 0 + lcs(l1-1, l2, s1, s2, dp);
            right = 0 + lcs(l1, l2-1, s1,s2,dp);
            return dp[l1][l2] = max(left, right);
        }

        return dp[l1][l2]= max(equal, max(left,right));
    }

    int solveMem(string &a, string &b, int i, int j, vector<vector<int>> &dp){
        if(i >= a.size() || j >= b.size()) return 0;

        if(dp[i][j] != -1){
            return dp[i][j];
        }

        int ans = 0;
        if(a[i] == b[j]){
            ans = 1 + solveMem(a, b, i+1, j+1, dp);
        }
        else{
            ans = max( solveMem(a, b, i+1, j, dp), solveMem(a, b, i, j+1, dp) );
        }

        return dp[i][j] = ans;
    }

    int longestCommonSubsequence(string text1, string text2) {
        int l1 = text1.size(), l2 = text2.size();
        
        vector<vector<int>> dp1 (l1+1, vector<int>(l2+1, -1));
        // return solveMem(text1, text2, 0, 0, dp1);
        // return lcs(l1-1, l2-1, text1, text2, dp1);

        vector<vector<int>> dp (l1+1, vector<int>(l2+1, 0));

        for(int i=1;i<=l1;i++){
            for(int j=1;j<=l2;j++){
                if(text1[i-1] == text2[j-1]){
                    dp[i][j] = 1+ dp[i-1][j-1];
                }
                else{
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1] );
                }
            }
        }
        return dp[l1][l2];

    }
};
```

## Attempt 5 · 2023-03-13 12:58 IST · Accepted · C++

[submission 914237588](https://leetcode.com/submissions/detail/914237588/) · tests 47/47 · runtime 77 ms (beats 5.2%)

```cpp
class Solution {
public:

    int lcs(int l1, int l2,string s1, string s2, vector<vector<int>> &dp){
        if(l1<0 || l2<0){
            return 0;
        }
        
        // Wrong base cases because l1 is 0 but l2 can be large and char at l1 can match with other chars(apart from l2) also in s2 
        // if(l1==0){
        //     return s1[l1] == s2[l2] ? 1: 0;
        // }
        // if(l2==0){
        //     return s1[l1] == s2[l2] ? 1: 0;
        // }
        if(dp[l1][l2] != -1)
            return dp[l1][l2];
        
        int equal =0, left =0, right =0;

        if(s1[l1] == s2[l2]){
            return dp[l1][l2] = equal = 1 + lcs(l1-1, l2-1, s1,s2,dp);
        }
        else{
            left = 0 + lcs(l1-1, l2, s1, s2, dp);
            right = 0 + lcs(l1, l2-1, s1,s2,dp);
            return dp[l1][l2] = max(left, right);
        }

        return dp[l1][l2]= max(equal, max(left,right));
    }

    int solveMem(string &a, string &b, int i, int j, vector<vector<int>> &dp){
        if(i >= a.size() || j >= b.size()) return 0;

        if(dp[i][j] != -1){
            return dp[i][j];
        }

        int ans = 0;
        if(a[i] == b[j]){
            ans = 1 + solveMem(a, b, i+1, j+1, dp);
        }
        else{
            ans = max( solveMem(a, b, i+1, j, dp), solveMem(a, b, i, j+1, dp) );
        }

        return dp[i][j] = ans;
    }

    int longestCommonSubsequence(string text1, string text2) {
        int l1 = text1.size(), l2 = text2.size();
        
        vector<vector<int>> dp1 (l1+1, vector<int>(l2+1, -1));
        // return solveMem(text1, text2, 0, 0, dp1);
        // return lcs(l1-1, l2-1, text1, text2, dp1);

        vector<vector<int>> dp (l1+1, vector<int>(l2+1, 0));

        for(int i=1;i<=l1;i++){
            for(int j=1;j<=l2;j++){
                if(text1[i-1] == text2[j-1]){
                    dp[i][j] = 1+ dp[i-1][j-1];
                }
                else{
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1] );
                }
            }
        }
        int i=l1, j=l2;
        int len = dp[l1][l2];
        string lcsString = "";

        while(i>0 && j>0){
            if(text1[i-1] == text2[j-1]){
                lcsString = text1[i-1] + lcsString;
                i--; j--;
            }
            else{
                if(dp[i][j-1] > dp[i-1][j]){
                    j--;
                }
                else{
                    i--;
                }
            }
        }
        cout<<lcsString;
        return dp[l1][l2];

    }
};
```
