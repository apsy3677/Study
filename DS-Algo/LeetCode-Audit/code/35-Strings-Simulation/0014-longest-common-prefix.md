# 14. Longest Common Prefix

[Problem](https://leetcode.com/problems/longest-common-prefix/) · Easy · Strings & Simulation → Column scan

LeetCode tags: array, string, trie

Attempts since Mar 2023: 3 · accepted: 2 · failed before first AC: 1

## Attempt 1 · 2023-03-06 22:39 IST · Wrong Answer · C++

[submission 910295360](https://leetcode.com/submissions/detail/910295360/) · tests 110/124

Failing input:

```text
["cir","car"]
```

Expected:

```text
"c"
```

Your output:

```text
"cr"
```

```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string prefix  = "";
        int n = strs.size();
        if(n==0) return prefix;
        for(int i=0;i<strs[0].size();i++){
            char x = strs[0][i];
            bool mismatch = false;
            for(int j=1;j<n;j++){
                if(x != strs[j][i]){
                    mismatch = true;
                    break;
                }
                    
            }
            if(!mismatch)
                prefix+=x;
           
        }

        return prefix;
    }
};
```

## Attempt 2 · 2023-03-06 22:41 IST · Accepted · C++

[submission 910296028](https://leetcode.com/submissions/detail/910296028/) · tests 124/124 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string prefix  = "";
        int n = strs.size();
        if(n==0) return prefix;
        for(int i=0;i<strs[0].size();i++){
            char x = strs[0][i];
            bool mismatch = false;
            for(int j=1;j<n;j++){
                if(x != strs[j][i]){
                    mismatch = true;
                    return prefix;
                }
                    
            }
            prefix+=x;
           
        }

        return prefix;
    }
};
```

## Attempt 3 · 2023-03-07 00:38 IST · Accepted · C++

[submission 910366984](https://leetcode.com/submissions/detail/910366984/) · tests 124/124 · runtime 4 ms (beats 5.5%)

```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string prefix  = "";
        int n = strs.size();
        if(n==0) return prefix;
        for(int i=0;i<strs[0].size();i++){
            char x = strs[0][i];
            bool mismatch = false;
            for(int j=1;j<n;j++){
                if(x != strs[j][i]){
                    mismatch = true;
                    return prefix;
                }
                    
            }
            prefix+=x;
           
        }

        return prefix;
    }
};
```
