# 34. Find First and Last Position of Element in Sorted Array

[Problem](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/) · Medium · Binary Search → Lower/upper bound

LeetCode tags: array, binary-search

Attempts since Mar 2023: 7 · accepted: 7 · failed before first AC: 0

## Attempt 1 · 2023-03-21 08:45 IST · Accepted · C++

[submission 919203923](https://leetcode.com/submissions/detail/919203923/) · tests 88/88 · runtime 12 ms (beats 0.0%)

```cpp
class Solution {
public:

    int first(vector<int>& arr, int x){
        int mid, low =0, high=arr.size() -1;
        int ans = -1;
        while(low<=high){
            mid = (low + high)/2;

            if(arr[mid] == x){
                ans = mid;
                high = mid -1;
            }
            else if(arr[mid]> x){
                high = mid -1;
            }
            else{
                low = mid+1;
            }
        }
        return ans;
    }

    int last(vector<int>& arr, int x){
        int mid, low =0, high=arr.size() -1;
        int ans = -1;
        while(low<=high){
            mid = (low + high)/2;

            if(arr[mid] == x){
                ans = mid;
                low = mid + 1;
            }
            else if(arr[mid]> x){
                high = mid -1;
            }
            else{
                low = mid+1;
            }
        }
        return ans;
    }

    vector<int> searchRange(vector<int>& arr, int x) {
        vector<int> ans = {-1,-1};
        if(arr.size() == 0){
            return ans;
        }
        ans[0] = first(arr,x);
        ans[1] = last(arr,x);

        return ans;
    }
};
```

## Attempt 2 · 2023-03-22 21:06 IST · Accepted · C++

[submission 920196302](https://leetcode.com/submissions/detail/920196302/) · tests 88/88 · runtime 10 ms (beats 0.0%)

```cpp
class Solution {
public:

    int first(vector<int>& arr, int x){
        int mid, low =0, high=arr.size() -1;
        int ans = -1;
        while(low<=high){
            mid = (low + high)/2;

            if(arr[mid] == x){
                ans = mid;
                high = mid -1;
            }
            else if(arr[mid]> x){
                high = mid -1;
            }
            else{
                low = mid+1;
            }
        }
        return ans;
    }

    int last(vector<int>& arr, int x){
        int mid, low =0, high=arr.size() -1;
        int ans = -1;
        while(low<=high){
            mid = (low + high)/2;

            if(arr[mid] == x){
                ans = mid;
                low = mid + 1;
            }
            else if(arr[mid]> x){
                high = mid -1;
            }
            else{
                low = mid+1;
            }
        }
        return ans;
    }

    vector<int> searchRange(vector<int>& arr, int x) {
        vector<int> ans = {-1,-1};
        if(arr.size() == 0){
            return ans;
        }
        ans[0] = first(arr,x);
        ans[1] = last(arr,x);

        return ans;
    }
};
```

## Attempt 3 · 2023-05-20 15:34 IST · Accepted · C++

[submission 953831601](https://leetcode.com/submissions/detail/953831601/) · tests 88/88 · runtime 8 ms (beats 0.0%)

```cpp
class Solution {
public:

    int first(vector<int>& arr, int x){
        int mid, low =0, high=arr.size() -1;
        int ans = -1;
        while(low<=high){
            mid = (low + high)/2;

            if(arr[mid] == x){
                ans = mid;
                high = mid -1;
            }
            else if(arr[mid]> x){
                high = mid -1;
            }
            else{
                low = mid+1;
            }
        }
        return ans;
    }

    int last(vector<int>& arr, int x){
        int mid, low =0, high=arr.size() -1;
        int ans = -1;
        while(low<=high){
            mid = (low + high)/2;

            if(arr[mid] == x){
                ans = mid;
                low = mid + 1;
            }
            else if(arr[mid]> x){
                high = mid -1;
            }
            else{
                low = mid+1;
            }
        }
        return ans;
    }

    vector<int> searchRange(vector<int>& arr, int x) {
        int n = arr.size();

        int low = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        if(low == n || arr[low] != x) return {-1,-1};
        int high = upper_bound(arr.begin(), arr.end(), x) - arr.begin();
        return {low, high-1};
        // vector<int> ans = {-1,-1};
        // if(arr.size() == 0){
        //     return ans;
        // }
        // ans[0] = first(arr,x);
        // ans[1] = last(arr,x);

        // return ans;
    }
};
```

## Attempt 4 · 2023-05-22 13:20 IST · Accepted · C++

[submission 954964502](https://leetcode.com/submissions/detail/954964502/) · tests 88/88 · runtime 8 ms (beats 0.0%)

```cpp
class Solution {
public:

    int searchIndex(vector<int>& arr, int x, bool firstIndex){
        int mid, low =0, high=arr.size() -1;
        int ans = -1;
        while(low <= high){
            mid = (low + high)/2;

            if(arr[mid] == x){
                ans = mid;
                if(firstIndex){
                    high = mid-1;
                }
                else{
                    low = mid + 1;
                }
            }
            else if(arr[mid]> x){
                high = mid -1;
            }
            else{
                low = mid+1;
            }
        }
        return ans;
    }

    vector<int> searchRange(vector<int>& arr, int x) {
        int n = arr.size();

        // int low = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        // if(low == n || arr[low] != x) return {-1,-1};
        // int high = upper_bound(arr.begin(), arr.end(), x) - arr.begin();
        // return {low, high-1};
        vector<int> ans = {-1,-1};
        if(arr.size() == 0){
            return ans;
        }

        return {searchIndex(arr, x, true), 
                searchIndex(arr,x,false)};
    }
};
```

## Attempt 5 · 2023-11-19 05:25 IST · Accepted · Python3

[submission 1101715842](https://leetcode.com/submissions/detail/1101715842/) · tests 88/88 · runtime 83 ms (beats 0.0%)

```python
class Solution:
    def searchRange(self, nums: List[int], target: int) -> List[int]:  
        l, r =0, len(nums) -1

        def binary_search(l, r, bound):
            while l<=r:
                mid = (l + r) //2

                if bound == 'upper':
                    if nums[mid] <= target:
                        l = mid +1
                    else:
                        r = mid - 1
                else:
                    if target <= nums[mid]:
                        r = mid -1
                    else:
                        l = mid+1
            return l
        
        start = binary_search(l, r, 'lower')
        end = binary_search(l, r, 'upper')
        
        if end-1<start:
            return [-1,-1]
        else:
            return [start, end-1]
```

## Attempt 6 · 2024-01-07 03:09 IST · Accepted · Python3

[submission 1138914018](https://leetcode.com/submissions/detail/1138914018/) · tests 88/88 · runtime 74 ms (beats 0.0%)

```python
class Solution:
    def searchRange(self, nums: List[int], target: int) -> List[int]:  
        l, r =0, len(nums) -1

        def binary_search(l, r, bound):
            while l<=r:
                mid = (l + r) //2

                if bound == 'upper':
                    if nums[mid] <= target:
                        l = mid +1
                    else:
                        r = mid - 1
                else:
                    if target <= nums[mid]:
                        r = mid -1
                    else:
                        l = mid+1
            return l
        
        start = binary_search(l, r, 'lower')
        end = binary_search(l, r, 'upper')
        print(start, end)
        if end == start:
            return [-1,-1]
        else:
            return [start, end-1]
```

## Attempt 7 · 2024-01-16 08:37 IST · Accepted · Python3

[submission 1147430361](https://leetcode.com/submissions/detail/1147430361/) · tests 88/88 · runtime 86 ms (beats 0.0%)

```python
class Solution:
    def searchRange(self, nums: List[int], target: int) -> List[int]:  
        l, r =0, len(nums) -1

        def binary_search(l, r, bound):
            while l<=r:
                mid = (l + r) //2

                if bound == 'upper':
                    if nums[mid] <= target:
                        l = mid +1
                    else:
                        r = mid - 1
                else:
                    if target <= nums[mid]:
                        r = mid -1
                    else:
                        l = mid+1
            
            return l if bound=='lower' else r
        
        start = binary_search(l, r, 'lower')
        end = binary_search(l, r, 'upper')
        if start > end:
            return [-1,-1]
        else:
            return [start, end]
```
