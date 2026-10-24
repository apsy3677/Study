# 2387. Median of a Row Wise Sorted Matrix

[Problem](https://leetcode.com/problems/median-of-a-row-wise-sorted-matrix/) · Medium · Binary Search on Answer → Count <= mid

LeetCode tags: array, binary-search, matrix

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-05-04 12:04 IST · Accepted · C++

[submission 944209105](https://leetcode.com/submissions/detail/944209105/) · tests 24/24 · runtime 172 ms (beats 5.9%)

```cpp
class Solution {
public:
    int check(vector<vector<int>>& grid, int middle){
        int ans = 0;
        for(int i=0;i<grid.size();i++){
            int nums =0;
            int l=0, h= grid[i].size()-1;
            while(l<=h){
                int mid = (l+h)/2;
                if(grid[i][mid] <= middle){
                    l = mid+1;
                }
                else{
                    h=mid-1;
                }
            }
            ans += l;
        }
        return ans;
    }
    int matrixMedian(vector<vector<int>>& grid) {
        // search space
        // median is 1 to 1e9
        int low = 0, high = 1e6;
        int tot = grid[0].size() * grid.size();
        int middle = tot/2;
        while(low <=high){
            int mid = (low + high)/2;
            int left = check(grid, mid);
            if(left <= middle){
                low = mid+1;
            }
            else{
                high = mid-1;
            }
        }
        return low;
    }
};
```
