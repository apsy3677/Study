# 953. Verifying an Alien Dictionary

[Problem](https://leetcode.com/problems/verifying-an-alien-dictionary/) · Easy · Arrays, Hashing & Sorting → Rank map compare

LeetCode tags: array, hash-table, string

Attempts since Mar 2023: 11 · accepted: 2 · failed before first AC: 9

## Attempt 1 · 2023-11-27 10:18 IST · Wrong Answer · Python3

[submission 1107193695](https://leetcode.com/submissions/detail/1107193695/) · tests 122/125

Failing input:

```text
["hello","hello"]
"abcdefghijklmnopqrstuvwxyz"
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
    def isAlienSorted(self, words: List[str], order: str) -> bool:
        order_map = {c:i for i,c in enumerate(order)}
        for word1, word2 in zip(words, words[1:]):
            for c,d in zip(word1, word2):
                if c!=d:
                    if order_map[c] > order_map[d]:
                        return False
                    break
            else:
                return len(word1) < len(word2)
        return True
```

## Attempt 2 · 2023-11-27 10:18 IST · Wrong Answer · Python3

[submission 1107193795](https://leetcode.com/submissions/detail/1107193795/) · tests 122/125

Failing input:

```text
["apple","apple","app"]
"abcdefghijklmnopqrstuvwxyz"
```

Expected:

```text
false
```

Your output:

```text
true
```

```python
class Solution:
    def isAlienSorted(self, words: List[str], order: str) -> bool:
        order_map = {c:i for i,c in enumerate(order)}
        for word1, word2 in zip(words, words[1:]):
            for c,d in zip(word1, word2):
                if c!=d:
                    if order_map[c] > order_map[d]:
                        return False
                    break
            else:
                return len(word1) <= len(word2)
        return True
```

## Attempt 3 · 2023-11-27 10:18 IST · Wrong Answer · Python3

[submission 1107193931](https://leetcode.com/submissions/detail/1107193931/) · tests 120/125

Failing input:

```text
["apple","app"]
"abcdefghijklmnopqrstuvwxyz"
```

Expected:

```text
false
```

Your output:

```text
true
```

```python
class Solution:
    def isAlienSorted(self, words: List[str], order: str) -> bool:
        order_map = {c:i for i,c in enumerate(order)}
        for word1, word2 in zip(words, words[1:]):
            for c,d in zip(word1, word2):
                if c!=d:
                    if order_map[c] > order_map[d]:
                        return False
                    break
            else:
                return len(word1) >= len(word2)
        return True
```

## Attempt 4 · 2023-11-27 10:19 IST · Wrong Answer · Python3

[submission 1107194007](https://leetcode.com/submissions/detail/1107194007/) · tests 120/125

Failing input:

```text
["apple","app"]
"abcdefghijklmnopqrstuvwxyz"
```

Expected:

```text
false
```

Your output:

```text
true
```

```python
class Solution:
    def isAlienSorted(self, words: List[str], order: str) -> bool:
        order_map = {c:i for i,c in enumerate(order)}
        for word1, word2 in zip(words, words[1:]):
            for c,d in zip(word1, word2):
                if c!=d:
                    if order_map[c] > order_map[d]:
                        return False
                    break
            else:
                return len(word1) > len(word2)
        return True
```

## Attempt 5 · 2023-11-27 10:20 IST · Wrong Answer · Python3

[submission 1107194860](https://leetcode.com/submissions/detail/1107194860/) · tests 122/125

Failing input:

```text
["apple","apple","app"]
"abcdefghijklmnopqrstuvwxyz"
```

Expected:

```text
false
```

Your output:

```text
true
```

```python
class Solution:
    def isAlienSorted(self, words: List[str], order: str) -> bool:
        order_map = {c:i for i,c in enumerate(order)}
        for word1, word2 in zip(words, words[1:]):
            for c,d in zip(word1, word2):
                if c!=d:
                    if order_map[c] > order_map[d]:
                        return False
                    break
            else:
                return len(word1) <= len(word2)
        return True
```

## Attempt 6 · 2023-11-27 10:25 IST · Wrong Answer · Python3

[submission 1107196798](https://leetcode.com/submissions/detail/1107196798/) · tests 82/125

Failing input:

```text
["fxasxpc","dfbdrifhp","nwzgs","cmwqriv","ebulyfyve","miracx","sxckdwzv","dtijzluhts","wwbmnge","qmjwymmyox"]
"zkgwaverfimqxbnctdplsjyohu"
```

Expected:

```text
false
```

Your output:

```text
true
```

```python
class Solution:
    def isAlienSorted(self, words: List[str], order: str) -> bool:
        order_map = {c:i for i,c in enumerate(order)}
        for word1, word2 in zip(words, words[1:]):
            for c,d in zip(word1, word2):
                if order_map[c] > order_map[d]:
                    return False
                elif order_map[c] < order_map[d]:
                    return True
        return len(word1) <= len(word2)
```

## Attempt 7 · 2023-11-27 10:26 IST · Wrong Answer · Python3

[submission 1107197652](https://leetcode.com/submissions/detail/1107197652/) · tests 122/125

Failing input:

```text
["apple","apple","app"]
"abcdefghijklmnopqrstuvwxyz"
```

Expected:

```text
false
```

Your output:

```text
true
```

```python
class Solution:
    def isAlienSorted(self, words: List[str], order: str) -> bool:
        order_map = {c:i for i,c in enumerate(order)}
        for word1, word2 in zip(words, words[1:]):
            for c,d in zip(word1, word2):
                if c!=d:
                    if order_map[c] > order_map[d]:
                        return False
                    break
            else:
                return len(word1) <= len(word2)
        return True
```

## Attempt 8 · 2023-11-27 10:27 IST · Wrong Answer · Python3

[submission 1107197758](https://leetcode.com/submissions/detail/1107197758/) · tests 122/125

Failing input:

```text
["hello","hello"]
"abcdefghijklmnopqrstuvwxyz"
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
    def isAlienSorted(self, words: List[str], order: str) -> bool:
        order_map = {c:i for i,c in enumerate(order)}
        for word1, word2 in zip(words, words[1:]):
            for c,d in zip(word1, word2):
                if c!=d:
                    if order_map[c] > order_map[d]:
                        return False
                    break
            else:
                return len(word1) < len(word2)
        return True
```

## Attempt 9 · 2023-11-27 10:27 IST · Wrong Answer · Python3

[submission 1107197841](https://leetcode.com/submissions/detail/1107197841/) · tests 122/125

Failing input:

```text
["apple","apple","app"]
"abcdefghijklmnopqrstuvwxyz"
```

Expected:

```text
false
```

Your output:

```text
true
```

```python
class Solution:
    def isAlienSorted(self, words: List[str], order: str) -> bool:
        order_map = {c:i for i,c in enumerate(order)}
        for word1, word2 in zip(words, words[1:]):
            for c,d in zip(word1, word2):
                if c!=d:
                    if order_map[c] > order_map[d]:
                        return False
                    break
            else:
                return len(word1) <= len(word2)
        return True
```

## Attempt 10 · 2023-11-27 10:29 IST · Accepted · Python3

[submission 1107199075](https://leetcode.com/submissions/detail/1107199075/) · tests 125/125 · runtime 46 ms (beats 1.2%)

```python
class Solution:
    def isAlienSorted(self, words: List[str], order: str) -> bool:
        order_map = {c:i for i,c in enumerate(order)}
        for word1, word2 in zip(words, words[1:]):
            for c,d in zip(word1, word2):
                if c!=d:
                    if order_map[c] > order_map[d]:
                        return False
                    break
            else:
                if len(word1) > len(word2):
                    return False
        return True
```

## Attempt 11 · 2024-01-26 02:08 IST · Accepted · Python3

[submission 1156830185](https://leetcode.com/submissions/detail/1156830185/) · tests 125/125 · runtime 43 ms (beats 1.2%)

```python
class Solution:
    def isAlienSorted(self, words: List[str], order: str) -> bool:
        order_map = {c:i for i,c in enumerate(order)}
        for word1, word2 in zip(words, words[1:]):
            for c,d in zip(word1, word2):
                if c!=d:
                    if order_map[c] > order_map[d]:
                        return False
                    break
            else:
                if len(word1) > len(word2):
                    return False
        return True

    def isAlienSorted(self, words: List[str], order: str) -> bool:
        order_map = {ch:i for ch in order}
        for word1, word2 in zip(words, words[1:]):
            for c, d in zip(word1, word2):
                if c!=d:
                    if order_map[c] > order_map[d]:
                        return False
                    break
            else:
                if len(word1) > len(word2):
                    return False
        return True

    def isAlienSorted(self, words: List[str], order: str) -> bool:
        '''
        only compare first non matching character - then break
        from index of order char create map
        '''
        order_map = {ch:i for i, ch in enumerate(order)}

        for word1, word2 in zip(words, words[1:]):
            for c,d in zip(word1, word2):
                if c!=d:
                    if order_map[c] > order_map[d]:
                        return False
                    break
            else:
                if len(word1) > len(word2):
                    return False
        return True
```
