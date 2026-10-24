# 1480. Running Sum of 1d Array

[Problem](https://leetcode.com/problems/running-sum-of-1d-array/) · Easy · Prefix Sum & Difference Array → Running sum

LeetCode tags: array, prefix-sum

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-06 21:05 IST · Accepted · C++

[submission 910238803](https://leetcode.com/submissions/detail/910238803/) · tests 53/53 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> ans;
        int sum=0;
        for(int i=0; i<nums.size();i++){
            sum += nums[i];
            ans.push_back(sum);
        }
        return ans;
    }
};
```
