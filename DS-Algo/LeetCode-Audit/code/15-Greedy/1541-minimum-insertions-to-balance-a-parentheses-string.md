# 1541. Minimum Insertions to Balance a Parentheses String

[Problem](https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/) · Medium · Greedy → Balance counter

LeetCode tags: string, stack, greedy, bracket-sequences

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-11-28 06:42 IST · Accepted · Python3

[submission 1107805104](https://leetcode.com/submissions/detail/1107805104/) · tests 102/102 · runtime 183 ms (beats 5.1%)

```python
class Solution:
    def minInsertions(self, s: str) -> int:
        opening = 0
        insertions = 0

        i=0
        while i < len(s):
            if s[i]=='(': opening+=1
            else:
                if i+1<len(s) and s[i+1] ==')':
                    i+=1
                else:
                    insertions +=1
                # print('s[i]', s[i], opening, insertions)
                if opening >0:
                    opening -=1
                else:
                    insertions +=1
            i+=1
        # print( opening, insertions)
        
        insertions += opening*2

        return insertions
```
