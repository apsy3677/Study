# 643. Maximum Average Subarray I

[Problem](https://leetcode.com/problems/maximum-average-subarray-i/) · Easy · Sliding Window → Fixed window

LeetCode tags: array, sliding-window

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-08-25 00:08 IST · Accepted · C++

[submission 1030773000](https://leetcode.com/submissions/detail/1030773000/) · tests 127/127 · runtime 118 ms (beats 7.6%)

```cpp
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int i, n=nums.size();
        double currSum=0.0;
        for(i=0;i<k;i++) {
            currSum= currSum + nums[i];
        }
        double maxAvg = currSum/k;
        for(;i<n;i++) {
            currSum= currSum - nums[i-k] + nums[i];
            if((currSum)/k > maxAvg) {
                maxAvg = (currSum)/k;
            }
        }
        return maxAvg;
    }
};
```

## Attempt 2 · 2023-11-18 06:28 IST · Accepted · Python3

[submission 1101111135](https://leetcode.com/submissions/detail/1101111135/) · tests 127/127 · runtime 1105 ms (beats 5.1%)

```python
class Solution:
    def findMaxAverage(self, nums: List[int], k: int) -> float:
        prefixSum =[0]*len(nums)
        for i in range(len(nums)):
            prefixSum[i] = prefixSum[i-1] + nums[i]
        
        #print(prefixSum)
        maxAverage = prefixSum[k-1] * 1.0/k
        
        for i in range(k, len(nums)):
            maxAverage = max(maxAverage, (prefixSum[i]- prefixSum[i-k])*1.0/k )    
        return maxAverage
```
