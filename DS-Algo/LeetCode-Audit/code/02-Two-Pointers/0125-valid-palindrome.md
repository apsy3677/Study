# 125. Valid Palindrome

[Problem](https://leetcode.com/problems/valid-palindrome/) · Easy · Two Pointers → Opposite ends

LeetCode tags: two-pointers, string

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-11-16 04:45 IST · Accepted · Python

[submission 1099691668](https://leetcode.com/submissions/detail/1099691668/) · tests 485/485 · runtime 23 ms (beats 36.1%)

```python
class Solution(object):
    def isPalindrome(self, s):
        """
        :type s: str
        :rtype: bool
        """
        l =0 
        r = len(s) -1

        while r>l:
            while r>l and not s[l].isalnum():
                l+=1

            while r>l and not s[r].isalnum():
                r-=1

            if s[l].lower()!= s[r].lower():
                return False

            r-=1
            l+=1
        return True
```

## Attempt 2 · 2023-11-24 19:52 IST · Accepted · Python3

[submission 1105496913](https://leetcode.com/submissions/detail/1105496913/) · tests 485/485 · runtime 47 ms (beats 6.0%)

```python
class Solution:
    def isPalindrome(self, s: str) -> bool:
        l = 0 
        r = len(s) - 1

        while l < r:
            while l<r and not s[l].isalnum():
                l+=1

            while l<r and not s[r].isalnum():
                r-=1

            if s[l].lower()!=s[r].lower():
                return False

            l+=1
            r-=1

        return True
```

## Attempt 3 · 2024-02-04 09:57 IST · Accepted · Python3

[submission 1165501847](https://leetcode.com/submissions/detail/1165501847/) · tests 485/485 · runtime 44 ms (beats 6.0%)

```python
class Solution:
    def isPalindrome(self, s: str) -> bool:
        l = 0 
        r = len(s) - 1

        while l < r:
            while l<r and not s[l].isalnum():
                l+=1

            while l<r and not s[r].isalnum():
                r-=1

            if s[l].lower()!=s[r].lower():
                return False

            l+=1
            r-=1

        return True

    def isPalindrome(self, s: str) -> bool:
        l = 0 
        r = len(s) - 1

        while l < r:
            while l< r and not s[l].isalnum():
                l+=1

            while l< r and not s[r].isalnum():
                r-=1

            if s[l].lower() != s[r].lower():
                return False

            l+=1
            r-=1

        return True

    def isPalindrome(self, s: str) -> bool:
        filtered_chars = []
        for l in s:
            if l.isalnum():
                filtered_chars.append(l.lower())

        # print(filtered_chars)
        return filtered_chars == filtered_chars[::-1]
```
