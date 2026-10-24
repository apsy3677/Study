# 1358. Number of Substrings Containing All Three Characters

[Problem](https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/) · Medium · Sliding Window → Count windows

LeetCode tags: hash-table, string, sliding-window

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2024-01-16 06:08 IST · Accepted · Python3

[submission 1147351380](https://leetcode.com/submissions/detail/1147351380/) · tests 54/54 · runtime 521 ms (beats 5.0%)

```python
class Solution:
    def numberOfSubstrings(self, s: str) -> int:
        l = r = 0
        window_count = Counter()
        total_substrings = 0

        at_least_one_of_each = lambda x: all(window_count[char]>0 for char in 'abc')

        while r < len(s):
            window_count[s[r]] +=1

            while at_least_one_of_each(window_count):
                # total strings
                total_substrings += len(s) - r
                window_count[s[l]] -=1
                l +=1
            r+=1

        return total_substrings
```
