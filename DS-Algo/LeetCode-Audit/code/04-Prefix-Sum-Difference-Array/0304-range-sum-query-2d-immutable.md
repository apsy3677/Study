# 304. Range Sum Query 2D - Immutable

[Problem](https://leetcode.com/problems/range-sum-query-2d-immutable/) · Medium · Prefix Sum & Difference Array → 2D prefix sum

LeetCode tags: array, design, matrix, prefix-sum

Attempts since Mar 2023: 1 · accepted: 0 · failed before first AC: 1

## Attempt 1 · 2023-11-30 00:32 IST · Wrong Answer · Python3

[submission 1109090813](https://leetcode.com/submissions/detail/1109090813/) · tests 3/22

Failing input:

```text
["NumMatrix","sumRegion"]
[[[[-1]]],[0,0,0,0]]
```

Expected:

```text
[null,-1]
```

Your output:

```text
[null,0]
```

```python
class NumMatrix:

    def __init__(self, matrix: List[List[int]]):
        self.data =[[0]*len(matrix[0]) for i in range(len(matrix))]
        
        for r in range(len(matrix)):
            prefixSum = 0
            for c in range(0, len(matrix[0])):
                prefixSum += matrix[r][c]
                self.data[r][c] = prefixSum
        print(self.data)

    def sumRegion(self, row1: int, col1: int, row2: int, col2: int) -> int:
        total = 0
        for i in range(row1, row2+1):
            print(self.data[i][col2], self.data[i][col1])
            total += self.data[i][col2] - self.data[i][col1-1]
        return total
```
