# 435. Non-overlapping Intervals

[Problem](https://leetcode.com/problems/non-overlapping-intervals/) · Medium · Intervals & Sweep Line → Greedy by end

LeetCode tags: array, dynamic-programming, greedy, sorting

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2024-03-23 11:26 IST · Accepted · C++

[submission 1211408422](https://leetcode.com/submissions/detail/1211408422/) · tests 59/59 · runtime 237 ms (beats 9.9%)

```cpp
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;

        sort(intervals.begin(), intervals.end(), [](vector<int> &v1, vector<int> &v2) {
            return v1[1] < v2[1];
        });
        int ans =0;
        int end = INT_MIN;
        for(auto &interval : intervals) {
            if (interval[0] >= end){
                end = interval[1];
            } else{
                ans++;
            }
        }
        return ans;
    }
};
```
