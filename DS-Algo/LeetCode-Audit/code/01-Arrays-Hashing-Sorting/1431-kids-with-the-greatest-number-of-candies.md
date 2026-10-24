# 1431. Kids With the Greatest Number of Candies

[Problem](https://leetcode.com/problems/kids-with-the-greatest-number-of-candies/) · Easy · Arrays, Hashing & Sorting → Max scan

LeetCode tags: array

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-08-18 21:57 IST · Accepted · C++

[submission 1025007443](https://leetcode.com/submissions/detail/1025007443/) · tests 103/103 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        int max = candies[0];
        int n = candies.size();
        vector<bool> result;
        for(int i=1;i<n;i++) {
            if(candies[i]>max) {
                max=candies[i];
            }
        }
        for(int i=0;i<n;i++) {
            bool flag = candies[i] + extraCandies >= max;
            result.push_back(flag);
        }
        return result;
    }
};
```
