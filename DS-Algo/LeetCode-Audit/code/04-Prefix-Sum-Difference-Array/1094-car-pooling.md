# 1094. Car Pooling

[Problem](https://leetcode.com/problems/car-pooling/) · Medium · Prefix Sum & Difference Array → Difference array

LeetCode tags: array, sorting, heap-priority-queue, simulation, prefix-sum

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2025-04-16 17:03 IST · Accepted · C++

[submission 1608472430](https://leetcode.com/submissions/detail/1608472430/) · tests 59/59 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        map<int, int> active;

        for (auto trip : trips) {
            int pass = trip[0];
            int l = trip[1];
            int r = trip[2];
            active[l] += pass;
            active[r] -= pass;
        }
        int curr = 0;
        for (auto point : active) {
            curr += point.second;
            if (curr > capacity) {
                return false;
            }
        }
        return true;
    }
};
```
