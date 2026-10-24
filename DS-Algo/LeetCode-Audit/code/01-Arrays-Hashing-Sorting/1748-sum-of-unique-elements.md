# 1748. Sum of Unique Elements

[Problem](https://leetcode.com/problems/sum-of-unique-elements/) · Easy · Arrays, Hashing & Sorting → Counting

LeetCode tags: array, hash-table, counting

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-12-31 07:53 IST · Accepted · Python3

[submission 1132621107](https://leetcode.com/submissions/detail/1132621107/) · tests 73/73 · runtime 50 ms (beats 0.6%)

```python
class Solution:
    def sumOfUnique(self, nums: List[int]) -> int:
        hashmap = Counter()
        for num in nums:
            hashmap[num] +=1
            
        total = 0
        for item,val in hashmap.items():
            if val == 1:
                total+= item
                
        return total
```
