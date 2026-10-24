# 67. Add Binary

[Problem](https://leetcode.com/problems/add-binary/) · Easy · Strings & Simulation → Digit addition

LeetCode tags: math, string, bit-manipulation, simulation

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-11-22 01:57 IST · Accepted · Python3

[submission 1103721725](https://leetcode.com/submissions/detail/1103721725/) · tests 296/296 · runtime 47 ms (beats 4.7%)

```python
class Solution:
    def addBinary(self, a: str, b: str) -> str:
        n = max(len(a), len(b))
        a, b = a.zfill(n), b.zfill(n)

        carry = 0
        result = []

        i=n-1
        while i >=0:
            value = (carry + int(a[i]) + int(b[i])) %2
            carry = (carry + int(a[i]) + int(b[i])) //2
            # print(value, carry)
            result.append(value)
            i-=1

        if carry:
            result.append(carry)
        return ''.join([str(x) for x in result[::-1]])
```

## Attempt 2 · 2023-11-22 01:57 IST · Accepted · Python3

[submission 1103721779](https://leetcode.com/submissions/detail/1103721779/) · tests 296/296 · runtime 40 ms (beats 4.7%)

```python
class Solution:
    def addBinary(self, a: str, b: str) -> str:
        n = max(len(a), len(b))
        a, b = a.zfill(n), b.zfill(n)

        carry = 0
        result = []

        i=n-1
        while i >=0:
            value = (carry + int(a[i]) + int(b[i])) %2
            carry = (carry + int(a[i]) + int(b[i])) //2
            # print(value, carry)
            result.append(value)
            i-=1

        if carry:
            result.append(carry)
        return ''.join([str(x) for x in result[::-1]])
```
