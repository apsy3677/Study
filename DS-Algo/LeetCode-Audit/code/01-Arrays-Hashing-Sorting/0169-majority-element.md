# 169. Majority Element

[Problem](https://leetcode.com/problems/majority-element/) · Easy · Arrays, Hashing & Sorting → Boyer-Moore vote

LeetCode tags: array, hash-table, divide-and-conquer, sorting, counting, boyer-moore-majority-vote-algorithm

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2025-01-25 11:30 IST · Accepted · C++

[submission 1519712914](https://leetcode.com/submissions/detail/1519712914/) · tests 52/52 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int idx = 0;
        int count = 1;
        for (int i = 1;i < nums.size();i++) {
            if (nums[i] == nums[idx]) {
                count++;
            } else {
                count--;
            }
            if (count == -1) {
                idx = i;
                count = 1;
            }
        }
        return nums[idx];
    }
};
```
