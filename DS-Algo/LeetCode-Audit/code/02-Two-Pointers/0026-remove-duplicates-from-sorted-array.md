# 26. Remove Duplicates from Sorted Array

[Problem](https://leetcode.com/problems/remove-duplicates-from-sorted-array/) · Easy · Two Pointers → Read/write pointers

LeetCode tags: array, two-pointers

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2024-03-25 20:11 IST · Accepted · C++

[submission 1213537851](https://leetcode.com/submissions/detail/1213537851/) · tests 362/362 · runtime 3 ms (beats 11.4%)

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        // remove duplicates
        // Keep the first one and keep removing while same element is present
        int last = INT_MIN, ans =0;
        for(int i=0;i<nums.size();i++){
            if(last == nums[i]) continue;
            last = nums[i];
            nums[ans++] = last;
        }
        return ans;
    }
};
```
