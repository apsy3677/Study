# 153. Find Minimum in Rotated Sorted Array

[Problem](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/) · Medium · Binary Search → Rotated minimum

LeetCode tags: array, binary-search

Attempts since Mar 2023: 5 · accepted: 5 · failed before first AC: 0

## Attempt 1 · 2023-05-22 17:45 IST · Accepted · C++

[submission 955088850](https://leetcode.com/submissions/detail/955088850/) · tests 150/150 · runtime 3 ms (beats 1.1%)

```cpp
class Solution {
public:
    int findPivott(vector<int> &arr){
        int low = 0, high = arr.size()-1;

        while(low < high){
            int mid = low + ((high - low)>>1);
            if(arr[mid] >= arr[mid+1]){
                return mid;
            }
            if(arr[low] <= arr[mid]) low = mid + 1;
            else{high = mid -1;}
        }
        return high;
    }
    int findMin(vector<int>& arr) {
        int pivot = findPivott(arr);
        // minimum is element after pivot
        return arr[(pivot+1)%arr.size()];
    }
};
```

## Attempt 2 · 2024-03-24 13:29 IST · Accepted · C++

[submission 1212405968](https://leetcode.com/submissions/detail/1212405968/) · tests 150/150 · runtime 3 ms (beats 1.1%)

```cpp
class Solution {
public:
    int findPivott(vector<int> &arr){
        int low = 0, high = arr.size()-1;

        while(low < high){
            int mid = low + ((high - low)>>1);
            if(arr[mid] >= arr[mid+1]){
                return mid;
            }
            if(arr[low] <= arr[mid]) low = mid + 1;
            else{high = mid -1;}
        }
        return low;
    }
    int findMin(vector<int>& arr) {
        int pivot = findPivott(arr);
        // minimum is element after pivot
        return arr[(pivot+1)%arr.size()];
    }
};
```

## Attempt 3 · 2024-03-24 13:29 IST · Accepted · C++

[submission 1212406170](https://leetcode.com/submissions/detail/1212406170/) · tests 150/150 · runtime 3 ms (beats 1.1%)

```cpp
class Solution {
public:
    int findPivott(vector<int> &arr){
        int low = 0, high = arr.size()-1;

        while(low < high){
            int mid = low + ((high - low)>>1);
            if(arr[mid] >= arr[mid+1]){
                return mid;
            }
            if(arr[low] <= arr[mid]) low = mid + 1;
            else{high = mid -1;}
        }
        // low == high at this point
        return low;
    }
    int findMin(vector<int>& arr) {
        int pivot = findPivott(arr);
        // minimum is element after pivot
        return arr[(pivot+1)%arr.size()];
    }
};
```

## Attempt 4 · 2024-03-24 13:30 IST · Accepted · C++

[submission 1212406620](https://leetcode.com/submissions/detail/1212406620/) · tests 150/150 · runtime 3 ms (beats 1.1%)

```cpp
class Solution {
public:
    int findPivott(vector<int> &arr){
        int low = 0, high = arr.size()-1;

        while(low < high){
            int mid = low + ((high - low)>>1);
            if(arr[mid] > arr[mid+1]){
                return mid;
            }
            if(arr[low] <= arr[mid]) low = mid + 1;
            else{high = mid -1;}
        }
        // low == high at this point
        return low;
    }
    int findMin(vector<int>& arr) {
        int pivot = findPivott(arr);
        // minimum is element after pivot
        return arr[(pivot+1)%arr.size()];
    }
};
```

## Attempt 5 · 2025-03-22 15:09 IST · Accepted · C++

[submission 1582142227](https://leetcode.com/submissions/detail/1582142227/) · tests 150/150 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];

        int low =0, high = nums.size()-1;
        int mid, ans = INT_MAX;

        while (low <= high) {
            ans = min(ans, min(nums[low], nums[high]));
            mid = low + (high-low)/2;
            ans = min(ans, nums[mid]);

            if(nums[low] <= nums[mid]) {
                low = mid+1;
            } else {
                high = mid-1;
            }
        }
        return ans;
    }
};
```
