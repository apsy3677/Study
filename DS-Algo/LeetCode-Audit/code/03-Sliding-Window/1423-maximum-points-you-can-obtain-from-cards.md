# 1423. Maximum Points You Can Obtain from Cards

[Problem](https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/) · Medium · Sliding Window → Fixed window (complement)

LeetCode tags: array, sliding-window, prefix-sum

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-31 12:58 IST · Accepted · C++

[submission 925250833](https://leetcode.com/submissions/detail/925250833/) · tests 40/40 · runtime 51 ms (beats 3.1%)

```cpp
class Solution {
public:
    int maxScore(vector<int>& arr, int K) {
        int curr_points = 0;
        int max_points = 0;
        int size = arr.size();
        // Iterate over first K elements of array and update the
        // value for curr_points
        for (int i = 0; i < K; i++)
            curr_points += arr[i];
    
        // Update value for max_points
        max_points = curr_points;
    
        // j points to the end of the array
        int j = size - 1;
        for (int i = K - 1; i >= 0; i--) {
            curr_points = curr_points + arr[j] - arr[i];
            max_points = max(curr_points, max_points);
            j--;
        }
        // Return the final result
        return max_points;
    }
        
};
```
