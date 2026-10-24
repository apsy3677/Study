# 1732. Find the Highest Altitude

[Problem](https://leetcode.com/problems/find-the-highest-altitude/) · Easy · Prefix Sum & Difference Array → Running sum

LeetCode tags: array, prefix-sum

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-09-01 23:08 IST · Accepted · C++

[submission 1037851819](https://leetcode.com/submissions/detail/1037851819/) · tests 80/80 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int result = 0, currSum = 0, n = gain.size();
        for(int i=0;i<n;i++) {
            currSum = currSum + gain[i];
            if(currSum>result) {
                result = currSum;
            }
        }
        return result;
    }
};
```
