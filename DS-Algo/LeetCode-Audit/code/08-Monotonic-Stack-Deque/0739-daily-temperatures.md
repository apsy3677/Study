# 739. Daily Temperatures

[Problem](https://leetcode.com/problems/daily-temperatures/) · Medium · Monotonic Stack / Deque → Next greater element

LeetCode tags: array, stack, monotonic-stack

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2025-03-22 23:59 IST · Accepted · C++

[submission 1582551479](https://leetcode.com/submissions/detail/1582551479/) · tests 48/48 · runtime 23 ms (beats 52.9%)

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack <int> st;
        vector<int> ans(temperatures.size(), 0);
        int j= 0;
        for (auto temp : temperatures) {
            while (!st.empty() && temp > temperatures[st.top()]) {
                int idx = st.top(); 
                st.pop();
                ans[idx] = j - idx;
            }
            st.push(j);
            j++;
        }
        return ans;
    }
};
```
