# 383. Ransom Note

[Problem](https://leetcode.com/problems/ransom-note/) · Easy · Arrays, Hashing & Sorting → Counting

LeetCode tags: hash-table, string, counting

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2024-01-04 03:33 IST · Accepted · Python3

[submission 1136046852](https://leetcode.com/submissions/detail/1136046852/) · tests 128/128 · runtime 56 ms (beats 6.3%)

```python
class Solution:
    def canConstruct(self, ransomNote: str, magazine: str) -> bool:
        magazine_counter = Counter(magazine)
        ransomNote_counter = Counter(ransomNote)

        return len(ransomNote_counter - magazine_counter) <=0
```
