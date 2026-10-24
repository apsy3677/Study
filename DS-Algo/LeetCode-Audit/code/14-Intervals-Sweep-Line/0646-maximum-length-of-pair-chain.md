# 646. Maximum Length of Pair Chain

[Problem](https://leetcode.com/problems/maximum-length-of-pair-chain/) · Medium · Intervals & Sweep Line → Greedy by end

LeetCode tags: array, dynamic-programming, greedy, sorting, longest-increasing-subsequence

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2025-04-16 23:32 IST · Accepted · C++

[submission 1608807314](https://leetcode.com/submissions/detail/1608807314/) · tests 206/206 · runtime 8 ms (beats 59.3%)

```cpp
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        auto cmp = [] (vector<int> &a, vector<int> &b) {
            return a[1] < b[1];
        };
        sort(pairs.begin(), pairs.end(), cmp);

        int ans = 0;
        int end = -1008;
        for (auto chain : pairs) {
            int l = chain[0];
            int r = chain[1];

            if (l > end) {
                ans++;
                end = r;
            } else {
                // ignore 
            }
        }
        return ans;
    }
};
```
