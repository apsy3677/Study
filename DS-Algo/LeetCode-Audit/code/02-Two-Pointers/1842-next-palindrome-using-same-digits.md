# 1842. Next Palindrome Using Same Digits

[Problem](https://leetcode.com/problems/next-palindrome-using-same-digits/) · Hard · Two Pointers → Next permutation on half

LeetCode tags: two-pointers, string

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-26 01:31 IST · Accepted · C++

[submission 922051842](https://leetcode.com/submissions/detail/922051842/) · tests 48/48 · runtime 11 ms (beats 0%)

```cpp
class Solution {
public:
    string nextPalindrome(string num) {
        if(!next_permutation(num.begin(), num.begin()+num.size()/2)) return "";
        copy(num.begin(), num.begin()+num.size()/2, num.rbegin());
        return num;
    }
};
```
