# 416. Partition Equal Subset Sum

[Problem](https://leetcode.com/problems/partition-equal-subset-sum/) · Medium · DP: Knapsack / Subset → Subset sum

LeetCode tags: array, dynamic-programming, knapsack-problem, 0-1-knapsack

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-12 22:53 IST · Accepted · C++

[submission 913930133](https://leetcode.com/submissions/detail/913930133/) · tests 141/141 · runtime 330 ms (beats 5.0%)

```cpp
class Solution {
public:

    bool subset(int n, int sum, vector<int>& nums, vector<vector<int>> &dp){
        if(sum == 0){
            return true;
        }
        if(n==0){
            return sum == nums[n];
        }
        if(dp[n][sum] != -1){
            return dp[n][sum];
        }
        bool notTaken = subset(n-1, sum, nums, dp);
        bool taken = false;

        if(nums[n]<=sum){
            taken = subset(n-1, sum-nums[n], nums, dp);
        }
        return dp[n][sum] = notTaken || taken; 
    }

    bool canPartition(vector<int>& nums) {
        if(nums.size()<2){
            return false;
        }
        int sum =0;
        for(auto x:nums)
            sum+=x;
        if(sum%2)
            return false;
        // find a subset such that sum is sum/2.
        vector<vector<int>> dp(nums.size(), vector<int>(sum+1, -1));

        return subset(nums.size()-1, sum/2, nums, dp);

    }
};
```
