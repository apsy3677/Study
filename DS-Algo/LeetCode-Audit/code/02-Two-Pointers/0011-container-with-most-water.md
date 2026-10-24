# 11. Container With Most Water

[Problem](https://leetcode.com/problems/container-with-most-water/) · Medium · Two Pointers → Opposite ends

LeetCode tags: array, two-pointers, greedy

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-08-24 23:26 IST · Accepted · C++

[submission 1030734523](https://leetcode.com/submissions/detail/1030734523/) · tests 61/61 · runtime 64 ms (beats 6.1%)

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int i=0,j=height.size(),n=height.size(), max=INT_MIN, curr;
        while(i<j) {
            curr = (min(height[i], height[j-1])) * (n-1);
            if(curr>max) {
                max=curr;
            }
            height[i]>height[j-1]? j--:i++;
            n--;
        }
        return max;
    }
};
```
