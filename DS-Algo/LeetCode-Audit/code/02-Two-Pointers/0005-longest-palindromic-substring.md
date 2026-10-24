# 5. Longest Palindromic Substring

[Problem](https://leetcode.com/problems/longest-palindromic-substring/) · Medium · Two Pointers → Expand around centre

LeetCode tags: two-pointers, string, dynamic-programming, manacher

Attempts since Mar 2023: 7 · accepted: 5 · failed before first AC: 1

## Attempt 1 · 2023-03-20 18:32 IST · Wrong Answer · C++

[submission 918763865](https://leetcode.com/submissions/detail/918763865/) · tests 71/141

Failing input:

```text
"aacabdkacaa"
```

Expected:

```text
"aca"
```

Your output:

```text
"aacabdkacaa"
```

```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        // "dkabbaj" 
        // "jabbakd"
        int n = s.size();
        vector<vector<bool>> dp(n+1, vector<bool>(n+1, false));

        for(int i=0;i<n;i++){
            dp[i][i] = 1;
        }
        string ans = "";
        ans+= s[0];
        for(int i=n-1;i>=0;i--){
            for(int j=i+1;j<n;j++){
                if(s[i] == s[j]){
                    if(j-i ==1 || dp[i+1][j-1])
                    dp[i][j] = true;

                    if(ans.size() < j-i+1){
                        ans = s.substr(i, j-i+1);
                    }
                }
                
            }
        }
        return ans;
        
    }
};
```

## Attempt 2 · 2023-03-20 18:33 IST · Accepted · C++

[submission 918764471](https://leetcode.com/submissions/detail/918764471/) · tests 141/141 · runtime 196 ms (beats 18.4%)

```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        // "dkabbaj" 
        // "jabbakd"
        int n = s.size();
        vector<vector<bool>> dp(n+1, vector<bool>(n+1, false));

        for(int i=0;i<n;i++){
            dp[i][i] = 1;
        }
        string ans = "";
        ans+= s[0];

        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (s[i] == s[j])
                {
                    //If it is of two character OR if its susbtring is palindrome.
                    if (j - i == 1 || dp[i + 1][j - 1])
                    {
                        //Then it will also a palindrome substring
                        dp[i][j] = true;

                        //Check for Longest Palindrome substring
                        if (ans.size() < j - i + 1)
                            ans = s.substr(i, j - i + 1);
                    }
                }
            }
        }


        // for(int i=n-1;i>=0;i--){
        //     for(int j=i+1;j<n;j++){
        //         if(s[i] == s[j]){
        //             if(j-i ==1 || dp[i+1][j-1])
        //             dp[i][j] = true;

        //             if(ans.size() < j-i+1){
        //                 ans = s.substr(i, j-i+1);
        //             }
        //         }
                
        //     }
        // }
        return ans;
        
    }
};
```

## Attempt 3 · 2023-03-20 18:35 IST · Accepted · C++

[submission 918765526](https://leetcode.com/submissions/detail/918765526/) · tests 141/141 · runtime 355 ms (beats 12.6%)

```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        // "dkabbaj" 
        // "jabbakd"
        int n = s.size();
        vector<vector<bool>> dp(n+1, vector<bool>(n+1, false));

        for(int i=0;i<n;i++){
            dp[i][i] = 1;
        }
        string ans = "";
        ans+= s[0];

        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (s[i] == s[j])
                {
                    //If it is of two character OR if its susbtring is palindrome.
                    if (j - i == 1 || dp[i + 1][j - 1])
                    {
                        //Then it will also a palindrome substring
                        dp[i][j] = true;

                        //Check for Longest Palindrome substring
                        if (ans.size() < j - i + 1)
                            ans = s.substr(i, j - i + 1);
                    }
                }
            }
        }


        for(int i=n-1;i>=0;i--){
            for(int j=i+1;j<n;j++){
                if(s[i] == s[j]){
                    if(j-i ==1 || dp[i+1][j-1]){
                        dp[i][j] = true;

                        if(ans.size() < j-i+1){
                            ans = s.substr(i, j-i+1);
                        }
                    }
                    
                }
                
            }
        }
        return ans;
        
    }
};
```

## Attempt 4 · 2023-03-20 18:35 IST · Accepted · C++

[submission 918765732](https://leetcode.com/submissions/detail/918765732/) · tests 141/141 · runtime 211 ms (beats 17.6%)

```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        // "dkabbaj" 
        // "jabbakd"
        int n = s.size();
        vector<vector<bool>> dp(n+1, vector<bool>(n+1, false));

        for(int i=0;i<n;i++){
            dp[i][i] = 1;
        }
        string ans = "";
        ans+= s[0];

        


        for(int i=n-1;i>=0;i--){
            for(int j=i+1;j<n;j++){
                if(s[i] == s[j]){
                    if(j-i ==1 || dp[i+1][j-1]){
                        dp[i][j] = true;

                        if(ans.size() < j-i+1){
                            ans = s.substr(i, j-i+1);
                        }
                    }
                    
                }
                
            }
        }
        return ans;
        
    }
};
```

## Attempt 5 · 2023-05-20 09:55 IST · Wrong Answer · C++

[submission 953691696](https://leetcode.com/submissions/detail/953691696/) · tests 134/141

Failing input:

```text
"a"
```

Expected:

```text
"a"
```

Your output:

```text
""
```

```cpp
class Solution {
    int checkPallindrome(string &s, int left, int right){
        while(left>=0 && right < s.size() && s[left] == s[right]){
            left--, right++;
        }
        return right - left - 1;
    }
public:
    string constantSpace(string s){
        if(s.empty()) return "";
        string ans;
        int len = 0;
        int end =0 ,start = 0;
        for(int i=0;i<s.size();i++){
            int len1 = checkPallindrome(s, i, i);
            int len2 = checkPallindrome(s, i, i+1); 1;            
            // cout<<len1<<" len "<<len2<<"||";
            len = max(len1, len2);

            if(len > end - start +1){
                start = i - (len-1)/2;
                end = i+len/2;
                cout<<start<<"|"<<end<<" ";
                ans = s.substr(start, end-start +1);
                cout<<ans<<" :: ";
            }
        }
        return ans;
    }
    string longestPalindrome(string s) {
        // "dkabbaj" 
        // "jabbakd"
        int n = s.size();
        return constantSpace(s);
        vector<vector<bool>> dp(n+1, vector<bool>(n+1, false));

        for(int i=0;i<n;i++){
            dp[i][i] = 1;
        }
        string ans = "";
        ans+= s[0];

        for(int i=n-1;i>=0;i--){
            for(int j=i+1;j<n;j++){
                if(s[i] == s[j]){
                    if(j-i ==1 || dp[i+1][j-1]){
                        dp[i][j] = true;

                        if(ans.size() < j-i+1){
                            ans = s.substr(i, j-i+1);
                        }
                    }
                    
                }
                
            }
        }
        return ans;
        
    }
};
```

## Attempt 6 · 2023-05-20 09:56 IST · Accepted · C++

[submission 953692246](https://leetcode.com/submissions/detail/953692246/) · tests 141/141 · runtime 111 ms (beats 24.6%)

```cpp
class Solution {
    int checkPallindrome(string &s, int left, int right){
        while(left>=0 && right < s.size() && s[left] == s[right]){
            left--, right++;
        }
        return right - left - 1;
    }
public:
    string constantSpace(string s){
        if(s.empty()) return "";
        string ans;
        int len = 0;
        int end =0 ,start = 0;
        for(int i=0;i<s.size();i++){
            int len1 = checkPallindrome(s, i, i);
            int len2 = checkPallindrome(s, i, i+1);            
            cout<<len1<<" len "<<len2<<"||";
            len = max(len1, len2);

            if(len > end - start +1){
                start = i - (len-1)/2;
                end = i+len/2;
                cout<<start<<"|"<<end<<" ";
                ans = s.substr(start, end-start +1);
                cout<<ans<<" :: ";
            }
        }
        return s.substr(start, end-start +1);
    }
    string longestPalindrome(string s) {
        // "dkabbaj" 
        // "jabbakd"
        int n = s.size();
        return constantSpace(s);
        vector<vector<bool>> dp(n+1, vector<bool>(n+1, false));

        for(int i=0;i<n;i++){
            dp[i][i] = 1;
        }
        string ans = "";
        ans+= s[0];

        for(int i=n-1;i>=0;i--){
            for(int j=i+1;j<n;j++){
                if(s[i] == s[j]){
                    if(j-i ==1 || dp[i+1][j-1]){
                        dp[i][j] = true;

                        if(ans.size() < j-i+1){
                            ans = s.substr(i, j-i+1);
                        }
                    }
                    
                }
                
            }
        }
        return ans;
        
    }
};
```

## Attempt 7 · 2023-05-20 09:59 IST · Accepted · C++

[submission 953693067](https://leetcode.com/submissions/detail/953693067/) · tests 141/141 · runtime 123 ms (beats 23.0%)

```cpp
class Solution {
    int checkPallindrome(string &s, int left, int right){
        while(left>=0 && right < s.size() && s[left] == s[right]){
            left--, right++;
        }
        return right - left - 1;
    }
public:
    string constantSpace(string s){
        if(s.empty()) return "";
        string ans;
        int len = 0;
        int end =0 ,start = 0;
        for(int i=0;i<s.size();i++){
            int len1 = checkPallindrome(s, i, i);
            int len2 = checkPallindrome(s, i, i+1);            
            cout<<len1<<" len "<<len2<<"||";
            len = max(len1, len2);

            if(len > end - start){
                start = i - (len-1)/2;
                end = i + len/2;
                cout<<start<<"|"<<end<<" ";
                ans = s.substr(start, end-start +1);
                cout<<ans<<" :: ";
            }
        }
        return s.substr(start, end-start +1);
    }
    string longestPalindrome(string s) {
        // "dkabbaj" 
        // "jabbakd"
        int n = s.size();
        return constantSpace(s);
        vector<vector<bool>> dp(n+1, vector<bool>(n+1, false));

        for(int i=0;i<n;i++){
            dp[i][i] = 1;
        }
        string ans = "";
        ans+= s[0];

        for(int i=n-1;i>=0;i--){
            for(int j=i+1;j<n;j++){
                if(s[i] == s[j]){
                    if(j-i ==1 || dp[i+1][j-1]){
                        dp[i][j] = true;

                        if(ans.size() < j-i+1){
                            ans = s.substr(i, j-i+1);
                        }
                    }
                    
                }
                
            }
        }
        return ans;
        
    }
};
```
