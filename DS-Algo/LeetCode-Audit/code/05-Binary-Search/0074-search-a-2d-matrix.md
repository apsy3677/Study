# 74. Search a 2D Matrix

[Problem](https://leetcode.com/problems/search-a-2d-matrix/) · Medium · Binary Search → Flattened search

LeetCode tags: array, binary-search, matrix

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2024-01-07 04:32 IST · Accepted · Python3

[submission 1138953190](https://leetcode.com/submissions/detail/1138953190/) · tests 133/133 · runtime 39 ms (beats 0.0%)

```python
class Solution:
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        n = len(matrix)
        m = len(matrix[0])
        l = 0
        r = m*n - 1

        while l <= r:

            mid = (l+r)//2

            mid_element = matrix[mid//m][mid%m] 
            if  mid_element == target:
                return True
            elif target < mid_element:
                r = mid - 1
            else:
                l = mid +1

        return False
```
