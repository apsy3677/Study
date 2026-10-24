# 1570. Dot Product of Two Sparse Vectors

[Problem](https://leetcode.com/problems/dot-product-of-two-sparse-vectors/) · Medium · Design → Sparse map

LeetCode tags: array, hash-table, two-pointers, design, linear-algebra

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2023-12-01 03:30 IST · Runtime Error · Python3

[submission 1109823795](https://leetcode.com/submissions/detail/1109823795/) · tests 0/99

Failing input:

```text
[1,0,0,2,3]
[0,3,0,4,0]
```

Expected:

```text
8
```

Runtime error:

```text
NameError: name 'SparseVector' is not defined
    v1 = SparseVector(param_1);
Line 7 in SparseVectorDriver (Solution.py)
    ret = SparseVectorDriver(param_1, param_2)
Line 26 in _driver (Solution.py)
    _driver()
Line 37 in <module> (Solution.py)
```

_Code not returned by LeetCode._

## Attempt 2 · 2023-12-01 03:34 IST · Accepted · Python3

[submission 1109825198](https://leetcode.com/submissions/detail/1109825198/) · tests 99/99 · runtime 1484 ms (beats 5.1%)

```python
class SparseVector:
    def __init__(self, nums: List[int]):
        self.pairs = []
        for i, num in enumerate(nums):
            if num !=0:
                self.pairs.append([i, num])


    # Return the dotProduct of two sparse vectors
    def dotProduct(self, vec: 'SparseVector') -> int:
        result = 0
        
        p, q = 0,0

        while p< len(self.pairs) and q <len(vec.pairs):
            # print(self.pairs[p], vec.pairs[q])
            if self.pairs[p][0] == vec.pairs[q][0]:
                result += self.pairs[p][1] * vec.pairs[q][1]
                p+=1
                q+=1
            elif self.pairs[p][0] < vec.pairs[q][0]:
                p+=1
            else:
                q+=1
        
        return result
# Your SparseVector object will be instantiated and called as such:
# v1 = SparseVector(nums1)
# v2 = SparseVector(nums2)
# ans = v1.dotProduct(v2)
```
