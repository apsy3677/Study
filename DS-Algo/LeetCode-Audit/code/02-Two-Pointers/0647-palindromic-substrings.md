# 647. Palindromic Substrings

[Problem](https://leetcode.com/problems/palindromic-substrings/) · Medium · Two Pointers → Expand around centre

LeetCode tags: two-pointers, string, dynamic-programming

Attempts since Mar 2023: 11 · accepted: 6 · failed before first AC: 2

## Attempt 1 · 2023-05-19 19:52 IST · Wrong Answer · C++

[submission 953384084](https://leetcode.com/submissions/detail/953384084/) · tests 12/130

Failing input:

```text
"aba"
```

Expected:

```text
4
```

Your output:

```text
3
```

```cpp
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();

        vector<vector<int>> dp(n+1, vector<int> (n+1, 0));

        for(int i=0;i<n;i++) dp[i][i] = 1;
        vector<string> pallindromes;
        pallindromes.push_back("");

        for(int i = 0; i<n;i++){
            for(int j = 0;j<n; j++){
                if((j-i) ==1 && s[i] == s[j]){
                    dp[i][j] = 1;
                    pallindromes.push_back(s.substr(i, j-i+1));
                }
                else{
                    if(i>0 && j> 0 && s[i] == s[j]){
                        dp[i][j] = dp[i-1][j-1];
                        pallindromes.push_back(s.substr(i, j-i+1));
                    }
                }
            }
        }
        return pallindromes.size();
    }
};
```

## Attempt 2 · 2023-05-20 08:31 IST · Output Limit Exceeded · C++

[submission 953666711](https://leetcode.com/submissions/detail/953666711/) · tests 128/130

Failing input:

```text
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa ... [602 more chars]
```

Expected:

```text
500500
```

```cpp
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();

        vector<vector<int>> dp(n+1, vector<int> (n+1, 0));
        vector<string> pallindromes;

        for(int i=0;i<n;i++) dp[i][i] = 1, pallindromes.push_back(s.substr(i, 1));
        // pallindromes.push_back("");
        dp[0][0] = 1;
        for(int i=n-1;i>=0;i--){
            for(int j=i+1;j<n;j++){
                if(s[i] == s[j]){
                    if(j-i ==1 || dp[i+1][j-1]){
                        dp[i][j] = true;
                        pallindromes.push_back(s.substr(i, j-i+1));
                        cout<<s.substr(i, j-i+1)<<" ";
                        // if(ans.size() < j-i+1){
                        //     ans = s.substr(i, j-i+1);
                        // }
                    }
                    
                }
                
            }
        }
        for(int i = 0; i<n ; i++){
            for(int j = i;j<n ; j++){
                // if(i == j){
                //     dp[i][j] = 1;
                //     pallindromes.push_back(s.substr(i, j-i+1));
                //     cout<<s.substr(i, j-i+1)<<" ";
                // }
                // else if((j-i) == 1 && s[i] == s[j]){
                //     cout<<s.substr(i, j-i+1)<<" ";
                //     dp[i][j] = 1;
                //     pallindromes.push_back(s.substr(i, j-i+1));
                // }
                // else{
                //     if(i>0 && j<n-1 && s[i] == s[j]){
                //         dp[i][j] = dp[i-1][j+1];
                //         if(dp[i][j] == 1)
                //     cout<<s.substr(i, j-i+1)<<" ",
                //             pallindromes.push_back(s.substr(i, j-i+1)) ;
                //     }
                // }
            }
        }
        return pallindromes.size();
    }
};
```

## Attempt 3 · 2023-05-20 08:32 IST · Accepted · C++

[submission 953666842](https://leetcode.com/submissions/detail/953666842/) · tests 130/130 · runtime 252 ms (beats 21.3%)

```cpp
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();

        vector<vector<int>> dp(n+1, vector<int> (n+1, 0));
        vector<string> pallindromes;

        for(int i=0;i<n;i++) dp[i][i] = 1, pallindromes.push_back(s.substr(i, 1));
        // pallindromes.push_back("");
        dp[0][0] = 1;
        for(int i=n-1;i>=0;i--){
            for(int j=i+1;j<n;j++){
                if(s[i] == s[j]){
                    if(j-i ==1 || dp[i+1][j-1]){
                        dp[i][j] = true;
                        pallindromes.push_back(s.substr(i, j-i+1));
                        // cout<<s.substr(i, j-i+1)<<" ";
                        // if(ans.size() < j-i+1){
                        //     ans = s.substr(i, j-i+1);
                        // }
                    }
                    
                }
                
            }
        }
        for(int i = 0; i<n ; i++){
            for(int j = i;j<n ; j++){
                // if(i == j){
                //     dp[i][j] = 1;
                //     pallindromes.push_back(s.substr(i, j-i+1));
                //     cout<<s.substr(i, j-i+1)<<" ";
                // }
                // else if((j-i) == 1 && s[i] == s[j]){
                //     cout<<s.substr(i, j-i+1)<<" ";
                //     dp[i][j] = 1;
                //     pallindromes.push_back(s.substr(i, j-i+1));
                // }
                // else{
                //     if(i>0 && j<n-1 && s[i] == s[j]){
                //         dp[i][j] = dp[i-1][j+1];
                //         if(dp[i][j] == 1)
                //     cout<<s.substr(i, j-i+1)<<" ",
                //             pallindromes.push_back(s.substr(i, j-i+1)) ;
                //     }
                // }
            }
        }
        return pallindromes.size();
    }
};
```

## Attempt 4 · 2023-05-20 08:39 IST · Wrong Answer · C++

[submission 953668569](https://leetcode.com/submissions/detail/953668569/) · tests 20/130

Failing input:

```text
"fdsklf"
```

Expected:

```text
6
```

Your output:

```text
7
```

```cpp
class Solution {
public:
    int util(string &s){
        int n = s.size();

        vector<vector<int>> dp(n+1, vector<int> (n+1, 0));
        vector<string> pallindromes;

        for(int i=0;i<n;i++) dp[i][i] = 1, pallindromes.push_back(s.substr(i, 1));

        for(int i = 0; i<n;i++){
            for(int j = i;j<n; j++){
                if(i==j) continue;
                if((j-i) ==1 && s[i] == s[j]){
                    dp[i][j] = 1;
                    pallindromes.push_back(s.substr(i, j-i+1));
                }
                else{
                    if(s[i] == s[j]){
                        dp[i][j] = dp[i+1][j-1];
                        pallindromes.push_back(s.substr(i, j-i+1));
                    }
                }
            }
        }
        return pallindromes.size();
    }
    int countSubstrings(string s) {
        return util(s);
        int n = s.size();

        vector<vector<int>> dp(n+1, vector<int> (n+1, 0));
        vector<string> pallindromes;

        for(int i=0;i<n;i++) dp[i][i] = 1, pallindromes.push_back(s.substr(i, 1));
        // pallindromes.push_back("");
        dp[0][0] = 1;
        for(int i=n-1;i>=0;i--){
            for(int j=i+1;j<n;j++){
                if(s[i] == s[j]){
                    if(j-i ==1 || dp[i+1][j-1]){
                        dp[i][j] = true;
                        pallindromes.push_back(s.substr(i, j-i+1));
                        // cout<<s.substr(i, j-i+1)<<" ";
                        // if(ans.size() < j-i+1){
                        //     ans = s.substr(i, j-i+1);
                        // }
                    }
                    
                }
                
            }
        }
        for(int i = 0; i<n ; i++){
            for(int j = i;j<n ; j++){
                // if(i == j){
                //     dp[i][j] = 1;
                //     pallindromes.push_back(s.substr(i, j-i+1));
                //     cout<<s.substr(i, j-i+1)<<" ";
                // }
                // else if((j-i) == 1 && s[i] == s[j]){
                //     cout<<s.substr(i, j-i+1)<<" ";
                //     dp[i][j] = 1;
                //     pallindromes.push_back(s.substr(i, j-i+1));
                // }
                // else{
                //     if(i>0 && j<n-1 && s[i] == s[j]){
                //         dp[i][j] = dp[i-1][j+1];
                //         if(dp[i][j] == 1)
                //     cout<<s.substr(i, j-i+1)<<" ",
                //             pallindromes.push_back(s.substr(i, j-i+1)) ;
                //     }
                // }
            }
        }
        return pallindromes.size();
    }
};
```

## Attempt 5 · 2023-05-20 08:43 IST · Wrong Answer · C++

[submission 953669727](https://leetcode.com/submissions/detail/953669727/) · tests 32/130

Failing input:

```text
"aaaaa"
```

Expected:

```text
15
```

Your output:

```text
12
```

```cpp
class Solution {
public:
    int util(string &s){
        int n = s.size();

        vector<vector<int>> dp(n+1, vector<int> (n+1, 0));
        vector<string> pallindromes;

        for(int i=0;i<n;i++) dp[i][i] = 1, pallindromes.push_back(s.substr(i, 1));

        for(int i = 0; i<n;i++){
            for(int j = i+1;j<n; j++){
                if(i==j) continue;
                if((j-i) ==1 && s[i] == s[j]){
                    dp[i][j] = 1;
                    cout<<s.substr(i, j-i+1)<<" ";
                    pallindromes.push_back(s.substr(i, j-i+1));
                }
                else{
                    if(s[i] == s[j]){
                        dp[i][j] = dp[i+1][j-1];
                        if(dp[i][j] == 1)
                            pallindromes.push_back(s.substr(i, j-i+1));
                    }
                }
            }
        }
        return pallindromes.size();
    }
    int countSubstrings(string s) {
        return util(s);
        int n = s.size();

        vector<vector<int>> dp(n+1, vector<int> (n+1, 0));
        vector<string> pallindromes;

        for(int i=0;i<n;i++) dp[i][i] = 1, pallindromes.push_back(s.substr(i, 1));
        // pallindromes.push_back("");
        dp[0][0] = 1;
        for(int i=n-1;i>=0;i--){
            for(int j=i+1;j<n;j++){
                if(s[i] == s[j]){
                    if(j-i ==1 || dp[i+1][j-1]){
                        dp[i][j] = true;
                        pallindromes.push_back(s.substr(i, j-i+1));
                        // cout<<s.substr(i, j-i+1)<<" ";
                        // if(ans.size() < j-i+1){
                        //     ans = s.substr(i, j-i+1);
                        // }
                    }
                    
                }
                
            }
        }
        for(int i = 0; i<n ; i++){
            for(int j = i;j<n ; j++){
                // if(i == j){
                //     dp[i][j] = 1;
                //     pallindromes.push_back(s.substr(i, j-i+1));
                //     cout<<s.substr(i, j-i+1)<<" ";
                // }
                // else if((j-i) == 1 && s[i] == s[j]){
                //     cout<<s.substr(i, j-i+1)<<" ";
                //     dp[i][j] = 1;
                //     pallindromes.push_back(s.substr(i, j-i+1));
                // }
                // else{
                //     if(i>0 && j<n-1 && s[i] == s[j]){
                //         dp[i][j] = dp[i-1][j+1];
                //         if(dp[i][j] == 1)
                //     cout<<s.substr(i, j-i+1)<<" ",
                //             pallindromes.push_back(s.substr(i, j-i+1)) ;
                //     }
                // }
            }
        }
        return pallindromes.size();
    }
};
```

## Attempt 6 · 2023-05-20 08:54 IST · Accepted · C++

[submission 953672826](https://leetcode.com/submissions/detail/953672826/) · tests 130/130 · runtime 213 ms (beats 21.5%)

```cpp
class Solution {
public:
    int util(string &s){
        int n = s.size();

        vector<vector<int>> dp(n+1, vector<int> (n+1, 0));
        vector<string> pallindromes;

        for(int i=0;i<n;i++) dp[i][i] = 1, pallindromes.push_back(s.substr(i, 1));

        // we have to start this way coz in DP we use states after i+1, so it is necessary to do it this way
        for(int i = n-1; i>=0;i--){
            for(int j = i+1;j<n; j++){
                // if(i==j) continue;
                if(s[i] == s[j]){
                    if((j-i) ==1 || dp[i+1][j-1] == 1)
                        dp[i][j] = 1,
                        // cout<<s.substr(i, j-i+1)<<" ",
                        pallindromes.push_back(s.substr(i, j-i+1));
                }
                
            }
        }
        return pallindromes.size();
    }
    int countSubstrings(string s) {
        return util(s);
        int n = s.size();

        vector<vector<int>> dp(n+1, vector<int> (n+1, 0));
        vector<string> pallindromes;

        for(int i=0;i<n;i++) dp[i][i] = 1, pallindromes.push_back(s.substr(i, 1));

        for(int i=n-1;i>=0;i--){
            for(int j=i+1;j<n;j++){
                if(s[i] == s[j]){
                    if(j-i ==1 || dp[i+1][j-1]){
                        dp[i][j] = true;
                        pallindromes.push_back(s.substr(i, j-i+1));
                        // cout<<s.substr(i, j-i+1)<<" ";
                        // if(ans.size() < j-i+1){
                        //     ans = s.substr(i, j-i+1);
                        // }
                    }
                    
                }
                
            }
        }
        for(int i = 0; i<n ; i++){
            for(int j = i;j<n ; j++){
                // if(i == j){
                //     dp[i][j] = 1;
                //     pallindromes.push_back(s.substr(i, j-i+1));
                //     cout<<s.substr(i, j-i+1)<<" ";
                // }
                // else if((j-i) == 1 && s[i] == s[j]){
                //     cout<<s.substr(i, j-i+1)<<" ";
                //     dp[i][j] = 1;
                //     pallindromes.push_back(s.substr(i, j-i+1));
                // }
                // else{
                //     if(i>0 && j<n-1 && s[i] == s[j]){
                //         dp[i][j] = dp[i-1][j+1];
                //         if(dp[i][j] == 1)
                //     cout<<s.substr(i, j-i+1)<<" ",
                //             pallindromes.push_back(s.substr(i, j-i+1)) ;
                //     }
                // }
            }
        }
        return pallindromes.size();
    }
};
```

## Attempt 7 · 2023-05-20 10:55 IST · Accepted · C++

[submission 953713702](https://leetcode.com/submissions/detail/953713702/) · tests 130/130 · runtime 265 ms (beats 21.3%)

```cpp
class Solution {
public:
    int util(string &s){
        int n = s.size();

        vector<vector<int>> dp(n+1, vector<int> (n+1, 0));
        vector<string> pallindromes;

        for(int i=0;i<n;i++) dp[i][i] = 1, pallindromes.push_back(s.substr(i, 1));

        // we have to start this way coz in DP we use states after i+1, so it is necessary to do it this way
        for(int i = n-1; i>=0;i--){
            for(int j = i+1;j<n; j++){
                if(s[i] == s[j]){
                    if((j-i) ==1 || dp[i+1][j-1] == 1)
                        dp[i][j] = 1,
                        // cout<<s.substr(i, j-i+1)<<" ",
                        pallindromes.push_back(s.substr(i, j-i+1));
                }
                
            }
        }
        return pallindromes.size();
    }
    int countSubstrings(string s) {
        return util(s);
        int n = s.size();

        vector<vector<int>> dp(n+1, vector<int> (n+1, 0));
        vector<string> pallindromes;

        for(int i=0;i<n;i++) dp[i][i] = 1, pallindromes.push_back(s.substr(i, 1));

        for(int i=n-1;i>=0;i--){
            for(int j=i+1;j<n;j++){
                if(s[i] == s[j]){
                    if(j-i ==1 || dp[i+1][j-1]){
                        dp[i][j] = true;
                        pallindromes.push_back(s.substr(i, j-i+1));
                        // cout<<s.substr(i, j-i+1)<<" ";
                    }
                    
                }
                
            }
        }
        return pallindromes.size();
    }
};
```

## Attempt 8 · 2023-05-20 13:53 IST · Accepted · C++

[submission 953789609](https://leetcode.com/submissions/detail/953789609/) · tests 130/130 · runtime 249 ms (beats 21.3%)

```cpp
class Solution {
public:
    int util(string &s){
        int n = s.size();

        vector<vector<int>> dp(n+1, vector<int> (n+1, 0));
        vector<string> pallindromes;

        for(int i=0;i<n;i++) dp[i][i] = 1, pallindromes.push_back(s.substr(i, 1));

        // we have to start this way coz in DP we use states after i+1, so it is necessary to do it this way
        for(int i = n-1; i>=0;i--){
            for(int j = i+1;j<n; j++){
                if(s[i] == s[j]){
                    if((j-i) ==1 || dp[i+1][j-1] == 1)
                        dp[i][j] = 1,
                        // cout<<s.substr(i, j-i+1)<<" ",
                        pallindromes.push_back(s.substr(i, j-i+1));
                }
                
            }
        }
        return pallindromes.size();
    }
    int countSubstrings(string s) {
        return util(s);
        int n = s.size();

        vector<vector<int>> dp(n+1, vector<int> (n+1, 0));
        vector<string> pallindromes;

        for(int i=0;i<n;i++) dp[i][i] = 1, pallindromes.push_back(s.substr(i, 1));

        for(int i=n-1;i>=0;i--){
            for(int j=i+1;j<n;j++){
                if(s[i] == s[j]){
                    if(j-i ==1 || dp[i+1][j-1]){
                        dp[i][j] = true;
                        pallindromes.push_back(s.substr(i, j-i+1));
                        // cout<<s.substr(i, j-i+1)<<" ";
                    }
                    
                }
                
            }
        }
        return pallindromes.size();
    }
};
```

## Attempt 9 · 2024-01-25 22:39 IST · Output Limit Exceeded · Python3

[submission 1156665634](https://leetcode.com/submissions/detail/1156665634/) · tests 128/130

Failing input:

```text
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa ... [602 more chars]
```

Expected:

```text
500500
```

```python
class Solution:
    def countSubstrings(self, s: str) -> int:
        def is_palin(l, r):
            while l<r:
                if s[l]!=s[r]:
                    return False
                l+=1
                r-=1
            print(s[l:r], 'yes')
            return True

        all_palins = []
        for start in range(len(s)):
            for end in range(start, len(s)):
                print(s[start:end])
                if is_palin(start, end):
                    all_palins.append(s[start:end])

        return len(all_palins)
```

## Attempt 10 · 2024-01-25 22:39 IST · Accepted · Python3

[submission 1156665756](https://leetcode.com/submissions/detail/1156665756/) · tests 130/130 · runtime 4932 ms (beats 5.0%)

```python
class Solution:
    def countSubstrings(self, s: str) -> int:
        def is_palin(l, r):
            while l<r:
                if s[l]!=s[r]:
                    return False
                l+=1
                r-=1
            print(s[l:r], 'yes')
            return True

        all_palins = []
        for start in range(len(s)):
            for end in range(start, len(s)):
                # print(s[start:end])
                if is_palin(start, end):
                    all_palins.append(s[start:end])

        return len(all_palins)
```

## Attempt 11 · 2024-01-25 23:05 IST · Accepted · Python3

[submission 1156688848](https://leetcode.com/submissions/detail/1156688848/) · tests 130/130 · runtime 149 ms (beats 35.1%)

```python
class Solution:
    def countSubstrings(self, s: str) -> int:
        def is_palin(l, r):
            while l<r:
                if s[l]!=s[r]:
                    return False
                l+=1
                r-=1
            print(s[l:r], 'yes')
            return True

        all_palins = []
        for start in range(len(s)):
            for end in range(start, len(s)):
                # print(s[start:end])
                if is_palin(start, end):
                    all_palins.append(s[start:end])

        return len(all_palins)

    def countSubstrings(self, s: str) -> int:
        memo = [[False]* len(s) for _ in range(len(s))]

        count = 0

        # substrings of length 1 and 2
        for i in range(len(s)):
            memo[i][i] = True
            count +=1
            if i< len(s)-1 and s[i+1] == s[i]:
                memo[i][i+1] = True
                count +=1

        # other substrings
        n = len(s)
        for length in range(3, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1
                if s[i] == s[j] and memo[i + 1][j - 1]:
                    memo[i][j] = True
                    count += 1
        return count
```
