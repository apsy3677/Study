# 436. Find Right Interval

[Problem](https://leetcode.com/problems/find-right-interval/) · Medium · Intervals & Sweep Line → Sort + binary search

LeetCode tags: array, binary-search, sorting

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2024-03-23 13:48 IST · Accepted · C++

[submission 1211492069](https://leetcode.com/submissions/detail/1211492069/) · tests 20/20 · runtime 63 ms (beats 11.7%)

```cpp
class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if (n==0) return {};
        vector<vector<int>> start(n, vector<int>(2)), end(n, vector<int>(2));

        for(int i=0;i<n;i++) {
            start[i][0] = intervals[i][0];
            start[i][1] = i;
            end[i][0] = intervals[i][1];
            end[i][1] = i;
        }
        sort(start.begin(), start.end());
        sort(end.begin(), end.end());

        vector<int> ans(n, -1);
        int rightIdx = 0;
        for(auto &last : end) {
            for (;rightIdx <n;){
                if(start[rightIdx][0] >= last[0]){
                    ans[last[1]] = start[rightIdx][1];
                    break;
                } else{
                    rightIdx++;
                }
            }
        }
        return ans;
    }
};
```
