# 540. Single Element in a Sorted Array

[Problem](https://leetcode.com/problems/single-element-in-a-sorted-array/) · Medium · Binary Search → Parity halves

LeetCode tags: array, binary-search

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-05-04 13:06 IST · Accepted · C++

[submission 944234757](https://leetcode.com/submissions/detail/944234757/) · tests 15/15 · runtime 30 ms (beats 3.5%)

```cpp
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();

        int low =0;
        int high=n-2;
        while(low <= high){
            int mid = (low + high)/2;
            int idx = 0;
            cout<<mid<<" ";
            if(mid%2 == 0){
                idx = mid+1;
                if(nums[mid] == nums[idx]){
                    low = mid + 1;
                }
                else{
                    high = mid -1;
                }
            }
            else{
                idx = mid-1;
                if(nums[mid] == nums[idx]){
                    low = mid + 1;
                }
                else{
                    high = mid -1;
                }
            }

        }
        return nums[low];
    }
};
```
