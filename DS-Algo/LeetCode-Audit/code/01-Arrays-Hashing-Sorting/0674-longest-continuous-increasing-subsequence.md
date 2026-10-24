# 674. Longest Continuous Increasing Subsequence

[Problem](https://leetcode.com/problems/longest-continuous-increasing-subsequence/) · Easy · Arrays, Hashing & Sorting → Run scan

LeetCode tags: array

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2024-02-10 22:02 IST · Accepted · Python3

[submission 1171546475](https://leetcode.com/submissions/detail/1171546475/) · tests 35/35 · runtime 58 ms (beats 5.1%)

```python
class Solution:
    def findLengthOfLCIS(self, nums: List[int]) -> int:

        l = r = 0
        count = 0
        max_length= float('-inf')
        while r< len(nums):
            if r ==0 or nums[r]> nums[r-1]:
                count +=1
                max_length = max(max_length, r-l+1)
            else:
                count =1 
                l = r
            r+=1
        return max_length
```
