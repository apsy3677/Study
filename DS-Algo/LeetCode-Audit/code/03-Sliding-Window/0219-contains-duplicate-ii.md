# 219. Contains Duplicate II

[Problem](https://leetcode.com/problems/contains-duplicate-ii/) · Easy · Sliding Window → Window set

LeetCode tags: array, hash-table, sliding-window

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-11-18 02:45 IST · Accepted · Python3

[submission 1101040393](https://leetcode.com/submissions/detail/1101040393/) · tests 58/58 · runtime 518 ms (beats 5.0%)

```python
class Solution:
    def containsNearbyDuplicate(self, nums: List[int], k: int) -> bool:
        hashmap = {}
        for i in range(len(nums)):
            if nums[i] in hashmap and i - hashmap[nums[i]] <=k : return True
            hashmap[nums[i]] = i
        return False
```
