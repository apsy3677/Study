# 392. Is Subsequence

[Problem](https://leetcode.com/problems/is-subsequence/) · Easy · Two Pointers → Subsequence scan

LeetCode tags: two-pointers, string, dynamic-programming

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2023-08-24 22:40 IST · Wrong Answer · C++

[submission 1030692905](https://leetcode.com/submissions/detail/1030692905/) · tests 17/19

Failing input:

```text
"b"
"abc"
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
public:
    bool isSubsequence(string s, string t) {
        int n=s.size(),m=t.size(),i=0,j=0;
        while (i<n&&j<m) {
            if(s[i] == t[j]) {
                i++;
            }
            j++;
        }
        return n==0 || (i==n && j==m);
    }
};
```

## Attempt 2 · 2023-08-24 22:41 IST · Accepted · C++

[submission 1030693648](https://leetcode.com/submissions/detail/1030693648/) · tests 19/19 · runtime 3 ms (beats 4.7%)

```cpp
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int n=s.size(),m=t.size(),i=0,j=0;
        while (i<n&&j<m) {
            if(s[i] == t[j]) {
                i++;
            }
            j++;
        }
        return n==0 || (i==n);
    }
};
```
