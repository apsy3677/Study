# 35. Search Insert Position

[Problem](https://leetcode.com/problems/search-insert-position/) · Easy · Binary Search → Lower bound

LeetCode tags: array, binary-search

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-05-22 12:37 IST · Accepted · C++

[submission 954943868](https://leetcode.com/submissions/detail/954943868/) · tests 65/65 · runtime 3 ms (beats 0.4%)

```cpp
class Solution {
public:
    int BS(vector<int>& arr, int target){
        int low = 0, high = arr.size() -1;

        while(low <= high){
            int mid = low + (high - low)/2;

            if(arr[mid] == target){
                return mid;
            }
            else if(arr[mid] < target){
                low = mid +1;
            }
            else{
                high = mid -1;
            }
        }
        return low;
    }
    int searchInsert(vector<int>& arr, int target) {
        return BS(arr, target);
    }
};
```
