# 766. Toeplitz Matrix

[Problem](https://leetcode.com/problems/toeplitz-matrix/) · Easy · Strings & Simulation → Matrix scan

LeetCode tags: array, matrix

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-11-14 21:21 IST · Accepted · Python3

[submission 1098746900](https://leetcode.com/submissions/detail/1098746900/) · tests 483/483 · runtime 76 ms (beats 4.7%)

```python
class Solution:
    def isToeplitzMatrix(self, matrix: List[List[int]]) -> bool:
        for r, row in enumerate(matrix):
            for c, val in enumerate(row):
                if r>0 and c>0 and matrix[r-1][c-1] != val:
                    return False
        return True
```

## Attempt 2 · 2023-12-05 00:18 IST · Accepted · Python3

[submission 1112372456](https://leetcode.com/submissions/detail/1112372456/) · tests 483/483 · runtime 94 ms (beats 4.7%)

```python
class Solution:
    def isToeplitzMatrix(self, matrix: List[List[int]]) -> bool:
        '''
        approach 1 : create groups with r-c as key. this will group all diagonal
        but you need to keep only one value and if value is not same, not toeplitz
        space O(M+N) number of diagonals 

        approach 2: run from 
        '''
        for r in range(1, len(matrix)):
            for c in range(1, len(matrix[0])):
                if matrix[r-1][c-1] != matrix[r][c]:
                    return False
        return True
```
