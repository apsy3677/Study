# 921. Minimum Add to Make Parentheses Valid

[Problem](https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/) · Medium · Greedy → Balance counter

LeetCode tags: string, stack, greedy, bracket-sequences

Attempts since Mar 2023: 4 · accepted: 4 · failed before first AC: 0

## Attempt 1 · 2023-11-13 00:55 IST · Accepted · Python3

[submission 1097415373](https://leetcode.com/submissions/detail/1097415373/) · tests 115/115 · runtime 49 ms (beats 0.6%)

```python
class Solution:
    def minAddToMakeValid(self, s: str) -> int:
        open = 0
        close = 0

        for symbol in s:
            if symbol == '(': open+=1
            elif symbol ==')' and open >0: open-=1
            else: close +=1
            #print(symbol, open,close)
        return open + close
```

## Attempt 2 · 2023-11-13 00:56 IST · Accepted · Python3

[submission 1097415671](https://leetcode.com/submissions/detail/1097415671/) · tests 115/115 · runtime 43 ms (beats 0.6%)

```python
class Solution:
    def minAddToMakeValid(self, s: str) -> int:
        unbalanced_open = 0
        unbalanced_close = 0

        for symbol in s:
            if symbol == '(': unbalanced_open+=1
            elif symbol ==')' and unbalanced_open >0: unbalanced_open-=1
            else: unbalanced_close +=1
            #print(symbol, open,close)
        return unbalanced_open + unbalanced_close
```

## Attempt 3 · 2023-12-05 00:41 IST · Accepted · Python3

[submission 1112386349](https://leetcode.com/submissions/detail/1112386349/) · tests 115/115 · runtime 49 ms (beats 0.6%)

```python
class Solution:
    def minAddToMakeValid(self, s: str) -> int:
        open_bal, close_bal = 0, 0

        for ch in s:
            if ch =='(': open_bal+=1
            elif ch ==')':
                if open_bal>0: 
                    open_bal -=1
                else: close_bal +=1
            # print(ch, open_bal,close_bal)
        return open_bal + close_bal
```

## Attempt 4 · 2023-12-05 00:42 IST · Accepted · Python3

[submission 1112386888](https://leetcode.com/submissions/detail/1112386888/) · tests 115/115 · runtime 46 ms (beats 0.6%)

```python
class Solution:
    def minAddToMakeValid(self, s: str) -> int:
        '''
        keep track of unbalnaced open and excess close
        when you encounter a unbalanced ) you will now because balance will be 0
        and at last all unmatched ( are unbalanced
        '''
        open_bal, close_bal = 0, 0

        for ch in s:
            if ch =='(': open_bal+=1
            elif ch ==')':
                if open_bal>0: 
                    open_bal -=1
                else: close_bal +=1
            # print(ch, open_bal,close_bal)
        return open_bal + close_bal
```
