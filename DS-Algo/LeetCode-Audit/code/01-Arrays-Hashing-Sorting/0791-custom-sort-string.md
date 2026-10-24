# 791. Custom Sort String

[Problem](https://leetcode.com/problems/custom-sort-string/) · Medium · Arrays, Hashing & Sorting → Counting sort

LeetCode tags: hash-table, string, sorting

Attempts since Mar 2023: 5 · accepted: 5 · failed before first AC: 0

## Attempt 1 · 2023-12-04 11:52 IST · Accepted · Python3

[submission 1111967531](https://leetcode.com/submissions/detail/1111967531/) · tests 39/39 · runtime 34 ms (beats 0.8%)

```python
class Solution:
    def customSortString(self, order: str, s: str) -> str:
        s_count = Counter(s)
        result = []
        for o in order:
            result.append( o * s_count[o])
            s_count[o] =0
        
        for s, cnt in s_count.items():
            result.append(s*cnt)
        
        return ''.join(result)
```

## Attempt 2 · 2024-02-02 08:58 IST · Accepted · Python3

[submission 1163535743](https://leetcode.com/submissions/detail/1163535743/) · tests 39/39 · runtime 36 ms (beats 0.8%)

```python
class Solution:
    def customSortString(self, order: str, s: str) -> str:
        s_count = Counter(s)
        result = []
        for o in order:
            result.append( o * s_count[o])
            s_count[o] =0
        
        for s, cnt in s_count.items():
            result.append(s*cnt)
        
        return ''.join(result)
```

## Attempt 3 · 2024-02-03 22:43 IST · Accepted · Python3

[submission 1165061692](https://leetcode.com/submissions/detail/1165061692/) · tests 39/39 · runtime 34 ms (beats 0.8%)

```python
class Solution:
    def customSortString(self, order: str, s: str) -> str:
        s_count = Counter(s)
        result = []
        for o in order:
            result.append( o * s_count[o])
            s_count[o] =0
        
        for s, cnt in s_count.items():
            result.append(s*cnt)
        
        return ''.join(result)

    def customSortString(self, order: str, s: str) -> str:
        string_counter = Counter(s)
        result = []
        for letter in order:
            result.append(letter * string_counter[letter])
            string_counter[letter] = 0

        for letter in string_counter.keys():
            result.append(letter * string_counter[letter])

        return ''.join(result)
```

## Attempt 4 · 2024-02-03 22:47 IST · Accepted · Python3

[submission 1165064991](https://leetcode.com/submissions/detail/1165064991/) · tests 39/39 · runtime 41 ms (beats 0.8%)

```python
class Solution:
    def customSortString(self, order: str, s: str) -> str:
        s_count = Counter(s)
        result = []
        for o in order:
            result.append( o * s_count[o])
            s_count[o] =0
        
        for s, cnt in s_count.items():
            result.append(s*cnt)
        
        return ''.join(result)

    def customSortString(self, order: str, s: str) -> str:
        string_counter = Counter(s)
        result = []
        for letter in order:
            print(list(letter * 3))
            result.extend([letter] * string_counter[letter])
            string_counter[letter] = 0

        for letter in string_counter.keys():
            result.extend([letter] * string_counter[letter])

        # print(result)
        return ''.join(result)
```

## Attempt 5 · 2024-02-03 22:55 IST · Accepted · Python3

[submission 1165073106](https://leetcode.com/submissions/detail/1165073106/) · tests 39/39 · runtime 37 ms (beats 0.8%)

```python
class Solution:
    def customSortString(self, order: str, s: str) -> str:
        s_count = Counter(s)
        result = []
        for o in order:
            result.append( o * s_count[o])
            s_count[o] =0
        
        for s, cnt in s_count.items():
            result.append(s*cnt)
        
        return ''.join(result)

    def customSortString(self, order: str, s: str) -> str:
        string_counter = Counter(s)
        result = []
        for letter in order:
            print(list(letter * 3))
            result.extend([letter] * string_counter[letter])
            string_counter[letter] = 0

        for letter in string_counter.keys():
            result.extend([letter] * string_counter[letter])

        # print(result)
        return ''.join(result)

    def customSortString(self, order: str, s: str) -> str:
        order_map = {ch:i for i, ch in enumerate(order)}

        s = sorted(s, key = lambda x: order_map.get(x, len(s)))
        print(''.join(s))
        return ''.join(s)
```
