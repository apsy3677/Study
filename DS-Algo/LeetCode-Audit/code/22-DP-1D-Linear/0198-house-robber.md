# 198. House Robber

[Problem](https://leetcode.com/problems/house-robber/) · Medium · DP: 1D / Linear → Take/skip

LeetCode tags: array, dynamic-programming

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2025-01-24 13:59 IST · Accepted · C++

[submission 1518840008](https://leetcode.com/submissions/detail/1518840008/) · tests 70/70 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        vector<int> ans(nums.size(), 0);
        int prev = 0;
        int curr = nums[0];

        if (nums.size() < 2) return curr;

        ans [0] = nums[0];
        ans[1] = max(nums[0], nums[1]);

        for(int i= 2; i<nums.size(); i++) {
            ans[i] = max(ans[i-2] + nums[i], ans[i-1]);
        }

        return ans[nums.size()-1];
    }
};
```

## Attempt 2 · 2025-01-24 14:03 IST · Accepted · C++

[submission 1518842548](https://leetcode.com/submissions/detail/1518842548/) · tests 70/70 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        vector<int> ans(nums.size(), 0);
        int prev = 0;
        int curr = nums[0];

        if (nums.size() < 2) return curr;

        // ans [0] = nums[0];
        // ans[1] = max(nums[0], nums[1]);

        // for(int i= 2; i<nums.size(); i++) {
        //     ans[i] = max(ans[i-2] + nums[i], ans[i-1]);
        // }

        // return ans[nums.size()-1];

        for (int i=1; i<nums.size();i++){
            int temp = curr;
            curr = max(curr, prev + nums[i]);
            prev = temp;
        }
        return curr;
    }
};
```
