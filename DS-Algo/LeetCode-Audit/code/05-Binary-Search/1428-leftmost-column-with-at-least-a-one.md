# 1428. Leftmost Column with at Least a One

[Problem](https://leetcode.com/problems/leftmost-column-with-at-least-a-one/) · Medium · Binary Search → Staircase / per-row search

LeetCode tags: array, binary-search, matrix, interactive

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-03-16 18:27 IST · Accepted · C++

[submission 916266861](https://leetcode.com/submissions/detail/916266861/) · tests 37/37 · runtime 6 ms (beats 48.8%)

```cpp
/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * class BinaryMatrix {
 *   public:
 *     int get(int row, int col);
 *     vector<int> dimensions();
 * };
 */

class Solution {
public:
    int leftMostColumnWithOne(BinaryMatrix &mat) {
        int ans =INT_MAX;
        vector<int> dim = mat.dimensions();
        int n = dim[0], m = dim[1];
        int left, right,mid;
        for(int i=0;i<n;i++){
            //BS
            left = 0, right = m-1;

            while(left<=right){
                mid = (left+right)/2;
                int col = mat.get(i, mid);
                if(col ==1){
                    ans = min(ans, mid);
                    right = mid-1;
                }
                else
                {
                    left = mid+1;
                }
            }
        }
        return ans = ans==INT_MAX ? -1 : ans;
    }
};
```

## Attempt 2 · 2023-03-30 22:40 IST · Accepted · C++

[submission 924939203](https://leetcode.com/submissions/detail/924939203/) · tests 37/37 · runtime 13 ms (beats 8.5%)

```cpp
/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * class BinaryMatrix {
 *   public:
 *     int get(int row, int col);
 *     vector<int> dimensions();
 * };
 */

class Solution {
public:
    int leftMostColumnWithOne(BinaryMatrix &mat) {
        int ans =INT_MAX;
        vector<int> dim = mat.dimensions();
        int n = dim[0], m = dim[1];
        int left, right,mid;
        for(int i=0;i<n;i++){
            //BS
            left = 0, right = min(m-1,ans);

            while(left<=right){
                mid = (left+right)/2;
                int col = mat.get(i, mid);
                if(col ==1){
                    ans = min(ans, mid);
                    right = mid-1;
                }
                else
                {
                    left = mid+1;
                }
            }
        }
        return ans = ans==INT_MAX ? -1 : ans;
    }
};
```
