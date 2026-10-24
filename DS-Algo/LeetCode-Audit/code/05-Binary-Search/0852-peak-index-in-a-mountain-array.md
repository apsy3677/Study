# 852. Peak Index in a Mountain Array

[Problem](https://leetcode.com/problems/peak-index-in-a-mountain-array/) · Medium · Binary Search → Peak

LeetCode tags: array, binary-search, ternary-search

Attempts since Mar 2023: 6 · accepted: 5 · failed before first AC: 1

## Attempt 1 · 2023-05-22 14:10 IST · Time Limit Exceeded · C++

[submission 954987202](https://leetcode.com/submissions/detail/954987202/) · tests 8/42

Failing input:

```text
[3,5,3,2,0]
```

Expected:

```text
1
```

```cpp
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int n =arr.size();
        int mid, low =0, high=arr.size() -1;
        int ans = -1;
        while(low <= high){
            mid = (low + high)/2;

            if( mid+1 < n && arr[mid] > arr[mid+1]){
                // in right half Decreasing array
                ans = mid;
                if(mid >0 && arr[mid] > arr[mid-1]){
                    return mid;
                }
                high = mid -1;
                
            }
            else if(mid>0 && arr[mid] > arr[mid-1]){
                // in left part incresing array
                if(mid+1 < n && arr[mid] > arr[mid+1]){
                    return mid;
                }
                low = mid + 1;
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-05-22 14:12 IST · Accepted · C++

[submission 954987979](https://leetcode.com/submissions/detail/954987979/) · tests 42/42 · runtime 117 ms (beats 0.4%)

```cpp
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int n =arr.size();
        int mid, low =0, high=arr.size() -1;
        int ans = -1;
        while(low <= high){
            mid = (low + high)/2;

            if( mid+1 < n && arr[mid] > arr[mid+1]){
                // in right half Decreasing array
                ans = mid;
                if(mid >0 && arr[mid] > arr[mid-1]){
                    return mid;
                }
                high = mid -1;
                
            }
            else if(mid>0 && arr[mid] > arr[mid-1]){
                // in left part incresing array
                if(mid+1 < n && arr[mid] > arr[mid+1]){
                    return mid;
                }
                low = mid + 1;
            }
            else{
                low = mid + 1;
            }
        }
        return ans;
    }
};
```

## Attempt 3 · 2023-05-22 14:15 IST · Accepted · C++

[submission 954989457](https://leetcode.com/submissions/detail/954989457/) · tests 42/42 · runtime 133 ms (beats 0.4%)

```cpp
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int n =arr.size();
        int mid, low =0, high=arr.size() -1;
        int ans = -1;
        while(low <= high){
            mid = (low + high)/2;

            if( mid+1 < n && arr[mid] > arr[mid+1]){
                // in right half Decreasing array
                ans = mid;
                if(mid >0 && arr[mid] > arr[mid-1]){
                    return mid;
                }
                high = mid;
                
            }
            else if(mid>0 && arr[mid] > arr[mid-1]){
                // in left part incresing array
                if(mid+1 < n && arr[mid] > arr[mid+1]){
                    return mid;
                }
                low = mid + 1;
            }
            else{
                // low = mid + 1;
                // high = mid -1;
            }
        }
        return ans;
    }
};
```

## Attempt 4 · 2023-05-22 14:15 IST · Accepted · C++

[submission 954989794](https://leetcode.com/submissions/detail/954989794/) · tests 42/42 · runtime 117 ms (beats 0.4%)

```cpp
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int n =arr.size();
        int mid, low =0, high=arr.size() -1;
        int ans = -1;
        while(low <= high){
            mid = (low + high)/2;

            if( mid+1 < n && arr[mid] > arr[mid+1]){
                // in right half Decreasing array
                ans = mid;
                if(mid >0 && arr[mid] > arr[mid-1]){
                    return mid;
                }
                high = mid;
                
            }
            else {
                // in left part incresing array
                if(mid+1 < n && arr[mid] > arr[mid+1]){
                    return mid;
                }
                low = mid + 1;
            }
            // else{
            //     // low = mid + 1;
            //     // high = mid -1;
            // }
        }
        return ans;
    }
};
```

## Attempt 5 · 2023-05-22 14:18 IST · Accepted · C++

[submission 954991084](https://leetcode.com/submissions/detail/954991084/) · tests 42/42 · runtime 130 ms (beats 0.4%)

```cpp
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int n =arr.size();
        int mid, low =0, high=arr.size() -1;
        int ans = -1;
        while(low <= high){
            mid = (low + high)/2;

            if( mid+1 < n && arr[mid] > arr[mid+1]){
                // in right half Decreasing array
                if(mid >0 && arr[mid] > arr[mid-1]){
                    return mid;
                }
                high = mid;
                
            }
            else if(mid > 0 && arr[mid] > arr[mid-1]){
                // in left part incresing array
                // if(mid+1 < n && arr[mid] > arr[mid+1]){
                //     return mid;
                // }
                low = mid + 1;
            }
            else{
                return mid;
                // low = mid + 1;
                // high = mid -1;
            }
        }
        return ans;
    }
};
```

## Attempt 6 · 2023-05-22 14:31 IST · Accepted · C++

[submission 954997100](https://leetcode.com/submissions/detail/954997100/) · tests 42/42 · runtime 109 ms (beats 0.4%)

```cpp
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int n =arr.size();
        int mid, low =0, high=arr.size() -1;
        int ans = -1;
        // important to run it for low < high not <= as we are checking next two elements as well.
        while(low < high){
            mid = (low + high)/2;

            // mid+1 exist coz low < high so there is one element in right of low for sure
            if(arr[mid] > arr[mid+1]){
                // we are in decreasing array 
                high = mid; // mid can be potential ans as it is greater than mid+1
            }
            else{
                // we are in increasing array so it means mid+1 will be greater than mid as first condition is also false mid is not greater than mid+1
                low = mid +1;
            }
        }

        return low;
    }
};
```
