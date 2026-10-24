# 1891. Cutting Ribbons

[Problem](https://leetcode.com/problems/cutting-ribbons/) · Medium · Binary Search on Answer → Maximise length

LeetCode tags: array, binary-search

Attempts since Mar 2023: 9 · accepted: 1 · failed before first AC: 6

## Attempt 1 · 2023-11-27 21:25 IST · Wrong Answer · Python3

[submission 1107523392](https://leetcode.com/submissions/detail/1107523392/) · tests 39/50

Failing input:

```text
[5,7,9]
22
```

Expected:

```text
0
```

Your output:

```text
1
```

```python
class Solution:
    def maxLength(self, ribbons: List[int], k: int) -> int:
        left = 1 
        right = sum(ribbons)//k

        def canCut(length):
            count = 0
            for ribbon in ribbons:
                count += ribbon//length
            return count >=k

        while left < right:
            mid = (left + right+1)//2
            print('here')
            print(left, mid, right)
            if canCut(mid):
                print('can cut')
                left = mid
            else:
                print(print('cannot cut'))
                right = mid-1

        return left
```

## Attempt 2 · 2023-11-27 21:28 IST · Wrong Answer · Python3

[submission 1107524807](https://leetcode.com/submissions/detail/1107524807/) · tests 31/50

Failing input:

```text
[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,100000,1,1,1,1,1,1,1,1,1,1]
100049
```

Expected:

```text
1
```

Your output:

```text
0
```

```python
class Solution:
    def maxLength(self, ribbons: List[int], k: int) -> int:
        left = 1 
        right = sum(ribbons)//k
        if right < k:
            return 0
        def canCut(length):
            count = 0
            for ribbon in ribbons:
                count += ribbon//length
            return count >=k

        while left < right:
            mid = (left + right+1)//2
            # print('here')
            # print(left, mid, right)
            if canCut(mid):
                # print('can cut')
                left = mid
            else:
                # print(print('cannot cut'))
                right = mid-1

        return left
```

## Attempt 3 · 2023-11-27 21:28 IST · Wrong Answer · Python3

[submission 1107525012](https://leetcode.com/submissions/detail/1107525012/) · tests 31/50

Failing input:

```text
[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,100000,1,1,1,1,1,1,1,1,1,1]
100049
```

Expected:

```text
1
```

Your output:

```text
0
```

```python
class Solution:
    def maxLength(self, ribbons: List[int], k: int) -> int:
        left = 1 
        right = max(ribbons)
        if sum(ribbons)//k < k:
            return 0
        def canCut(length):
            count = 0
            for ribbon in ribbons:
                count += ribbon//length
            return count >=k

        while left < right:
            mid = (left + right+1)//2
            # print('here')
            # print(left, mid, right)
            if canCut(mid):
                # print('can cut')
                left = mid
            else:
                # print(print('cannot cut'))
                right = mid-1

        return left
```

## Attempt 4 · 2023-11-27 21:28 IST · Wrong Answer · Python3

[submission 1107525244](https://leetcode.com/submissions/detail/1107525244/) · tests 31/50

Failing input:

```text
[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,100000,1,1,1,1,1,1,1,1,1,1]
100049
```

Expected:

```text
1
```

Your output:

```text
0
```

```python
class Solution:
    def maxLength(self, ribbons: List[int], k: int) -> int:
        left = 1 
        right = sum(ribbons)//k
        if right <= k:
            return 0
        def canCut(length):
            count = 0
            for ribbon in ribbons:
                count += ribbon//length
            return count >=k

        while left < right:
            mid = (left + right+1)//2
            # print('here')
            # print(left, mid, right)
            if canCut(mid):
                # print('can cut')
                left = mid
            else:
                # print(print('cannot cut'))
                right = mid-1

        return left
```

## Attempt 5 · 2023-11-27 21:29 IST · Wrong Answer · Python3

[submission 1107525423](https://leetcode.com/submissions/detail/1107525423/) · tests 31/50

Failing input:

```text
[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,100000,1,1,1,1,1,1,1,1,1,1]
100049
```

Expected:

```text
1
```

Your output:

```text
0
```

```python
class Solution:
    def maxLength(self, ribbons: List[int], k: int) -> int:
        left = 1 
        right = sum(ribbons)//k
        print(left, right)
        if right < k:
            return 0
        def canCut(length):
            count = 0
            for ribbon in ribbons:
                count += ribbon//length
            return count >=k

        while left < right:
            mid = (left + right+1)//2
            # print('here')
            # print(left, mid, right)
            if canCut(mid):
                # print('can cut')
                left = mid
            else:
                # print(print('cannot cut'))
                right = mid-1

        return left
```

## Attempt 6 · 2023-11-27 21:40 IST · Wrong Answer · Python3

[submission 1107532529](https://leetcode.com/submissions/detail/1107532529/) · tests 31/50

Failing input:

```text
[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,100000,1,1,1,1,1,1,1,1,1,1]
100049
```

Expected:

```text
1
```

Your output:

```text
0
```

```python
class Solution:
    def maxLength(self, ribbons: List[int], k: int) -> int:
        left = 1 
        right = sum(ribbons)//k
        print(left, right)
        if right < k:
            return 0
        def canCut(length):
            count = 0
            for ribbon in ribbons:
                count += ribbon//length
            return count >=k

        while left <= right:
            mid = (left + right)//2
            # print('here')
            # print(left, mid, right)
            if canCut(mid):
                # print('can cut')
                left = mid+1
            else:
                # print(print('cannot cut'))
                right = mid-1

        return right
```

## Attempt 7 · 2023-11-27 21:41 IST · Accepted · Python3

[submission 1107532903](https://leetcode.com/submissions/detail/1107532903/) · tests 50/50 · runtime 1181 ms (beats 5.3%)

```python
class Solution:
    def maxLength(self, ribbons: List[int], k: int) -> int:
        left = 1 
        right = max(ribbons)
        print(left, right)
        # if sum(ribbons)//k < k:
        #     return 0
        def canCut(length):
            count = 0
            for ribbon in ribbons:
                count += ribbon//length
            return count >=k

        while left <= right:
            mid = (left + right)//2
            # print('here')
            # print(left, mid, right)
            if canCut(mid):
                # print('can cut')
                left = mid+1
            else:
                # print(print('cannot cut'))
                right = mid-1

        return right
```

## Attempt 8 · 2024-02-10 23:05 IST · Wrong Answer · Python3

[submission 1171597317](https://leetcode.com/submissions/detail/1171597317/) · tests 47/50

Failing input:

```text
[100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,1,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000]
49
```

Expected:

```text
100000
```

Your output:

```text
99999
```

```python
class Solution:
    def maxLength(self, ribbons: List[int], k: int) -> int:
        left = 1 
        right = max(ribbons)
        print(left, right)
        # if sum(ribbons)//k < k:
        #     return 0
        def canCut(length):
            count = 0
            for ribbon in ribbons:
                count += ribbon//length
            return count >=k

        while left <= right:
            mid = (left + right)//2
            print('here')
            print(left, mid, right)
            if canCut(mid):
                print('can cut')
                left = mid+1
            else:
                print(print('cannot cut'))
                right = mid-1

        return right
        
    def maxLength(self, ribbons: List[int], k: int) -> int:
        l = 1
        r = max(ribbons)

        def can_cut(ribbon_length):
            ribbons_count = 0
            for ribbon in ribbons:
                ribbons_count += ribbon // ribbon_length
            return ribbons_count >=k

        while l<r:
            mid = (l+r)//2
            print('checking if ribbon can be ', mid, can_cut(mid))
            if can_cut(mid):
                l = mid + 1
            else:
                r = mid
        return l-1
```

## Attempt 9 · 2024-02-10 23:05 IST · Wrong Answer · Python3

[submission 1171597648](https://leetcode.com/submissions/detail/1171597648/) · tests 47/50

Failing input:

```text
[100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,1,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000,100000]
49
```

Expected:

```text
100000
```

Your output:

```text
99999
```

```python
class Solution:
    def maxLength(self, ribbons: List[int], k: int) -> int:
        left = 1 
        right = max(ribbons)
        print(left, right)
        # if sum(ribbons)//k < k:
        #     return 0
        def canCut(length):
            count = 0
            for ribbon in ribbons:
                count += ribbon//length
            return count >=k

        while left <= right:
            mid = (left + right)//2
            print('here')
            print(left, mid, right)
            if canCut(mid):
                print('can cut')
                left = mid+1
            else:
                print(print('cannot cut'))
                right = mid-1

        return right
        
    def maxLength(self, ribbons: List[int], k: int) -> int:
        l = 1
        r = max(ribbons)

        def can_cut(ribbon_length):
            ribbons_count = 0
            for ribbon in ribbons:
                ribbons_count += ribbon // ribbon_length
            return ribbons_count >=k

        while l<r:
            mid = (l+r)//2
            # print('checking if ribbon can be ', mid, can_cut(mid))
            if can_cut(mid):
                l = mid + 1
            else:
                r = mid
        return l-1
```
