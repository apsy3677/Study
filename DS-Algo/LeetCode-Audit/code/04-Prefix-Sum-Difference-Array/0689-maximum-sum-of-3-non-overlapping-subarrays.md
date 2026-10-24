# 689. Maximum Sum of 3 Non-Overlapping Subarrays

[Problem](https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/) · Hard · Prefix Sum & Difference Array → Prefix sum + best left/right

LeetCode tags: array, dynamic-programming, sliding-window, prefix-sum

Attempts since Mar 2023: 1 · accepted: 0 · failed before first AC: 1

## Attempt 1 · 2024-02-04 11:47 IST · Wrong Answer · Python3

[submission 1165575011](https://leetcode.com/submissions/detail/1165575011/) · tests 19/43

Failing input:

```text
[7,13,20,19,19,2,10,1,1,19]
3
```

Expected:

```text
[1,4,7]
```

Your output:

```text
[1,3,7]
```

```python
class Solution:
    def maxSumOfThreeSubarrays(self, nums: List[int], k: int) -> List[int]:
    # def maxSumOfThreeSubarrays(nums, k):
        n = len(nums)
        # Calculate prefix sums
        prefix_sum = [0]
        for num in nums:
            prefix_sum.append(prefix_sum[-1] + num)
        
        # Initialize indices and sums for the three subarrays
        index1, index2, index3 = 0, k, 2*k
        max_sum1 = prefix_sum[k] - prefix_sum[0]
        max_sum2 = prefix_sum[2*k] - prefix_sum[k]
        max_sum3 = prefix_sum[3*k] - prefix_sum[2*k]
        max_total = max_sum1 + max_sum2 + max_sum3
        
        # Best indices for the subarrays
        best_indices = [0, k, 2*k]
        
        # Start scanning from the end of the third subarray
        for i in range(3*k, n + 1):
            # Update the third subarray sum
            sum3 = prefix_sum[i] - prefix_sum[i - k]
            # Update the second subarray sum
            if prefix_sum[i - k] - prefix_sum[i - 2*k] > max_sum2:
                max_sum2 = prefix_sum[i - k] - prefix_sum[i - 2*k]
                index2 = i - 2*k
            # Update the first subarray sum
            if prefix_sum[i - 2*k] - prefix_sum[i - 3*k] > max_sum1:
                max_sum1 = prefix_sum[i - 2*k] - prefix_sum[i - 3*k]
                index1 = i - 3*k
            
            # Update total max sum and best indices
            if max_sum1 + max_sum2 + sum3 > max_total:
                max_total = max_sum1 + max_sum2 + sum3
                best_indices = [index1, index2, i - k]
        
        return best_indices
```
