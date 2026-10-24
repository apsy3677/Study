# 494. Target Sum

[Problem](https://leetcode.com/problems/target-sum/) · Medium · DP: Knapsack / Subset → Count subsets with difference

LeetCode tags: array, dynamic-programming, backtracking, knapsack-problem, 0-1-knapsack

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-13 02:21 IST · Accepted · C++

[submission 914018995](https://leetcode.com/submissions/detail/914018995/) · tests 140/140 · runtime 11 ms (beats 59.2%)

```cpp
class Solution {
public:
    int dfs(int i, int t, vector<int> &nums, vector<vector<int>> &dp) {
        if(!i) {
            if(!nums[0] && !t) return 2;
            if(!t) return 1;
            return nums[0] == t;
        }
        if(dp[i][t] != -1) return dp[i][t];

        int notPick = dfs(i - 1, t, nums, dp);
        int pick = nums[i] <= t ? dfs(i - 1, t - nums[i], nums, dp) : 0;

        return dp[i][t] = pick + notPick;
    }
    int findTargetSumWays(vector<int>& nums, int target) {
        int ts = accumulate(nums.begin(), nums.end(), 0), n = nums.size();
        if((target + ts) % 2 || target > ts || target < -ts) return 0;
        int t = (target + ts) / 2;

        vector<vector<int>> dp(n, vector<int>(t + 1, -1));
        return dfs(n - 1, t, nums, dp);
    }
};
```
