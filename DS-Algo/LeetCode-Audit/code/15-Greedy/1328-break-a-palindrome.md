# 1328. Break a Palindrome

[Problem](https://leetcode.com/problems/break-a-palindrome/) · Medium · Greedy → Greedy character change

LeetCode tags: string, greedy

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-27 00:45 IST · Accepted · C++

[submission 922617647](https://leetcode.com/submissions/detail/922617647/) · tests 31/31 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    string breakPalindrome(string palindrome) {
        int length = palindrome.size();
        
        if (length <= 1) { 
            return "";
        }
        
        for (int i = 0; i < length / 2; i++) {
            if (palindrome[i] != 'a') {
                palindrome[i] = 'a';
                return palindrome;
            }
        }
        
        palindrome[length - 1] = 'b';
        return palindrome;
    }
};
```
