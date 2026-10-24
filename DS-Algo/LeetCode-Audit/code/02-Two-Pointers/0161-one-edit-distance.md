# 161. One Edit Distance

[Problem](https://leetcode.com/problems/one-edit-distance/) · Medium · Two Pointers → Single mismatch

LeetCode tags: two-pointers, string

Attempts since Mar 2023: 4 · accepted: 1 · failed before first AC: 3

## Attempt 1 · 2024-01-29 05:20 IST · Runtime Error · Python3

[submission 1159605169](https://leetcode.com/submissions/detail/1159605169/) · tests 2/136

Failing input:

```text
"a"
""
```

Expected:

```text
true
```

Runtime error:

```text
IndexError: string index out of range
               ~^^^
    if s[i] != t[i]:
Line 14 in isOneEditDistance (Solution.py)
          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    ret = Solution().isOneEditDistance(param_1, param_2)
Line 44 in _driver (Solution.py)
    _driver()
Line 55 in <module> (Solution.py)
```

```python
class Solution:
    def isOneEditDistance(self, s: str, t: str) -> bool:
        ns = len(s)
        nt= len(t)

        # makre sure s is ahorter
        if ns > nt:
            self.isOneEditDistance(t,s)

        if nt - ns >1:
            return False
            
        for i in range(len(s)):
            if s[i] != t[i]: 
                if ns==nt:
                    s[i+1:] == t[i+1:]
                else:
                    return s[i:] == t[i+1:]
        return ns+1 == nt
```

## Attempt 2 · 2024-01-29 05:28 IST · Runtime Error · Python3

[submission 1159608686](https://leetcode.com/submissions/detail/1159608686/) · tests 2/136

Failing input:

```text
"a"
""
```

Expected:

```text
true
```

Runtime error:

```text
IndexError: string index out of range
               ~^^^
    if s[i] != t[i]:
Line 14 in isOneEditDistance (Solution.py)
          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    ret = Solution().isOneEditDistance(param_1, param_2)
Line 44 in _driver (Solution.py)
    _driver()
Line 55 in <module> (Solution.py)
```

```python
class Solution:
    def isOneEditDistance(self, s: str, t: str) -> bool:
        ns = len(s)
        nt= len(t)

        # makre sure s is ahorter
        if ns > nt:
            self.isOneEditDistance(t,s)

        if nt - ns >1:
            return False
            
        for i in range(len(s)):
            if s[i] != t[i]: 
                if ns==nt:
                    s[i+1:] == t[i+1:]
                else:
                    return s[i:] == t[i+1:]
        return ns+1 == nt
```

## Attempt 3 · 2024-01-29 05:31 IST · Wrong Answer · Python3

[submission 1159609608](https://leetcode.com/submissions/detail/1159609608/) · tests 121/136

Failing input:

```text
"a"
"A"
```

Expected:

```text
true
```

Your output:

```text
false
```

```python
class Solution:
    def isOneEditDistance(self, s: str, t: str) -> bool:
        ns = len(s)
        nt= len(t)

        # makre sure s is ahorter
        if ns > nt:
            return self.isOneEditDistance(t,s)

        if nt - ns >1:
            return False

        for i in range(ns):
            if s[i] != t[i]: 
                if ns==nt:
                    s[i+1:] == t[i+1:]
                else:
                    return s[i:] == t[i+1:]
        return ns+1 == nt
```

## Attempt 4 · 2024-01-29 05:31 IST · Accepted · Python3

[submission 1159609851](https://leetcode.com/submissions/detail/1159609851/) · tests 136/136 · runtime 39 ms (beats 5.7%)

```python
class Solution:
    def isOneEditDistance(self, s: str, t: str) -> bool:
        ns = len(s)
        nt= len(t)

        # makre sure s is ahorter
        if ns > nt:
            return self.isOneEditDistance(t,s)

        if nt - ns >1:
            return False

        for i in range(ns):
            if s[i] != t[i]: 
                if ns==nt:
                    return s[i+1:] == t[i+1:]
                else:
                    return s[i:] == t[i+1:]
        return ns+1 == nt
```
