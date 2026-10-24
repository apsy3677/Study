# 1493. Longest Subarray of 1's After Deleting One Element

[Problem](https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/) · Medium · Sliding Window → At most 1 zero

LeetCode tags: array, dynamic-programming, sliding-window

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-09-01 20:58 IST · Accepted · C++

[submission 1037751435](https://leetcode.com/submissions/detail/1037751435/) · tests 81/81 · runtime 28 ms (beats 6.2%)

```cpp
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int i = 0, j = 0, available = 1, n = nums.size(), ans=0, result = 0;

        while(j<n) {
            if(nums[j]==0) {
                if(available > 0) {
                    available = 0;
                    ans++;
                } else {
                    while(nums[i] != 0) {
                        i++;
                        ans--;
                    }
                    i++;
                    available--;
                }
            } else {
                ans++;
            }

            if(ans<0) {
                ans=0;
            }

            if(ans>result) {
                result = ans;
            }
            j++;
        }
        return result-1;
    }
};
```
