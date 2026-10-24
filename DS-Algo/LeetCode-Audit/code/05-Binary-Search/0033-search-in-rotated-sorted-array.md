# 33. Search in Rotated Sorted Array

[Problem](https://leetcode.com/problems/search-in-rotated-sorted-array/) · Medium · Binary Search → Rotated array

LeetCode tags: array, binary-search

Attempts since Mar 2023: 8 · accepted: 7 · failed before first AC: 0

## Attempt 1 · 2023-03-25 12:57 IST · Accepted · C++

[submission 921712032](https://leetcode.com/submissions/detail/921712032/) · tests 195/195 · runtime 7 ms (beats 0.4%)

```cpp
class Solution {
public:
    int BS(vector<int> &arr, int low, int high, int x){

        int  mid;
        int n = arr.size();
        // if(low <0 || high>=n)
        //     return -1;
        while(low<=high){
            mid = low +(high-low)/2;
            if(arr[mid] == x){
                return mid;
            }
            else if(arr[mid] > x){
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        return -1;
    }
    int findPivot(vector<int> &arr){
        int n = arr.size();
        int low = 0, high = n-1, mid;
        int pivot =-1;
        if(arr[0] < arr[n-1]){
            return 0;
        }
        while(low <= high){
            mid = low + (high - low)/2;
            if(mid >0 && arr[mid]<arr[mid-1]){
                return pivot = mid;
            }
            if(mid+1 <= n-1 && arr[mid]>arr[mid+1] ){
                return pivot = mid+1;
            }
            if(arr[low] < arr[mid]){
                low = mid+1;
            }
            else{
                high = mid -1;
            }

        }
        return 0;
        // if(arr[0] > arr[n-1]){
        //     return -1;
        // }
        if(arr[0] < arr[n-1]){
            return n-1;
        }
        return -1;
    }
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int pivot = findPivot(nums);

        int low, high,idx =0;

        if(pivot == 0 ){
            // already sorted
            return BS(nums, 0, n-1, target);
        }
        // // 
        low = pivot, high = n-1;
        idx = BS(nums, low, high, target);
        cout<<pivot<<" pivot|| "<<idx<<" searched once "<<low<<" low - high "<<high<<" ";
        if(idx == -1){
            cout<<low <<" "<<high;
            low = 0, high = pivot -1;
            idx = BS(nums, low, high, target) ;
        }
        // else {
        //     
        // }
        return idx;
    }
};
```

## Attempt 2 · 2023-05-04 13:38 IST · Accepted · C++

[submission 944246756](https://leetcode.com/submissions/detail/944246756/) · tests 195/195 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    int BS(vector<int> &arr, int low, int high, int x){

        int  mid;
        int n = arr.size();
        // if(low <0 || high>=n)
        //     return -1;
        while(low<=high){
            mid = low +(high-low)/2;
            if(arr[mid] == x){
                return mid;
            }
            else if(arr[mid] > x){
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        return -1;
    }
    int findPivot(vector<int> &arr){
        int n = arr.size();
        int low = 0, high = n-1, mid;
        int pivot =-1;
        if(arr[0] < arr[n-1]){
            return 0;
        }
        while(low <= high){
            mid = low + (high - low)/2;
            if(mid >0 && arr[mid]<arr[mid-1]){
                return pivot = mid;
            }
            if(mid+1 <= n-1 && arr[mid]>arr[mid+1] ){
                return pivot = mid+1;
            }
            if(arr[low] < arr[mid]){
                low = mid+1;
            }
            else{
                high = mid -1;
            }

        }
        return 0;
        // if(arr[0] > arr[n-1]){
        //     return -1;
        // }
        if(arr[0] < arr[n-1]){
            return n-1;
        }
        return -1;
    }
    int searchInOneGo(vector<int> &arr, int target){
        int n = arr.size();
        int low = 0;
        int high = n-1;

        while(low<=high){
            int mid = (low+high)/2;
            if(arr[mid] == target) return mid;
            
            // left array is sorted
            if(arr[low] <= arr[mid]){
                if(target >= arr[low] && target <= arr[mid]){
                    high = mid-1;
                }
                else{
                    low = mid+1;
                }

            }
            else{
                // right array is sorted
                if(target >= arr[mid] && target <= arr[high]){
                    low = mid+1;
                }
                else{
                    high = mid-1;
                }
            }
        }
        return -1;
    }
    int search(vector<int>& nums, int target) {
        return searchInOneGo(nums, target);
        int n = nums.size();
        int pivot = findPivot(nums);

        int low, high,idx =0;

        if(pivot == 0 ){
            // already sorted
            return BS(nums, 0, n-1, target);
        }
        // // 
        low = pivot, high = n-1;
        idx = BS(nums, low, high, target);
        cout<<pivot<<" pivot|| "<<idx<<" searched once "<<low<<" low - high "<<high<<" ";
        if(idx == -1){
            cout<<low <<" "<<high;
            low = 0, high = pivot -1;
            idx = BS(nums, low, high, target) ;
        }
        // else {
        //     
        // }
        return idx;
    }
};
```

## Attempt 3 · 2023-05-04 13:38 IST · Accepted · C++

[submission 944246907](https://leetcode.com/submissions/detail/944246907/) · tests 195/195 · runtime 11 ms (beats 0.4%)

```cpp
class Solution {
public:
    int BS(vector<int> &arr, int low, int high, int x){

        int  mid;
        int n = arr.size();
        // if(low <0 || high>=n)
        //     return -1;
        while(low<=high){
            mid = low +(high-low)/2;
            if(arr[mid] == x){
                return mid;
            }
            else if(arr[mid] > x){
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        return -1;
    }
    int findPivot(vector<int> &arr){
        int n = arr.size();
        int low = 0, high = n-1, mid;
        int pivot =-1;
        if(arr[0] < arr[n-1]){
            return 0;
        }
        while(low <= high){
            mid = low + (high - low)/2;
            if(mid >0 && arr[mid]<arr[mid-1]){
                return pivot = mid;
            }
            if(mid+1 <= n-1 && arr[mid]>arr[mid+1] ){
                return pivot = mid+1;
            }
            if(arr[low] < arr[mid]){
                low = mid+1;
            }
            else{
                high = mid -1;
            }

        }
        return 0;
        // if(arr[0] > arr[n-1]){
        //     return -1;
        // }
        if(arr[0] < arr[n-1]){
            return n-1;
        }
        return -1;
    }
    int searchInOneGo(vector<int> &arr, int target){
        int n = arr.size();
        int low = 0;
        int high = n-1;

        while(low<=high){
            int mid = (low+high)/2;
            if(arr[mid] == target) return mid;
            
            // left array is sorted
            if(arr[low] <= arr[mid]){
                if(target >= arr[low] && target <= arr[mid]){
                    high = mid-1;
                }
                else{
                    low = mid+1;
                }

            }
            else{
                // right array is sorted
                if(target >= arr[mid] && target <= arr[high]){
                    low = mid+1;
                }
                else{
                    high = mid-1;
                }
            }
        }
        return -1;
    }
    int search(vector<int>& nums, int target) {
        return searchInOneGo(nums, target);
        // int n = nums.size();
        // int pivot = findPivot(nums);

        // int low, high,idx =0;

        // if(pivot == 0 ){
        //     // already sorted
        //     return BS(nums, 0, n-1, target);
        // }
        // // // 
        // low = pivot, high = n-1;
        // idx = BS(nums, low, high, target);
        // cout<<pivot<<" pivot|| "<<idx<<" searched once "<<low<<" low - high "<<high<<" ";
        // if(idx == -1){
        //     cout<<low <<" "<<high;
        //     low = 0, high = pivot -1;
        //     idx = BS(nums, low, high, target) ;
        // }
        // // else {
        // //     
        // // }
        // return idx;
    }
};
```

## Attempt 4 · 2023-05-04 13:39 IST · Accepted · C++

[submission 944247245](https://leetcode.com/submissions/detail/944247245/) · tests 195/195 · runtime 11 ms (beats 0.4%)

```cpp
class Solution {
public:
    int BS(vector<int> &arr, int low, int high, int x){

        int  mid;
        int n = arr.size();
        // if(low <0 || high>=n)
        //     return -1;
        while(low<=high){
            mid = low +(high-low)/2;
            if(arr[mid] == x){
                return mid;
            }
            else if(arr[mid] > x){
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        return -1;
    }
    int findPivot(vector<int> &arr){
        int n = arr.size();
        int low = 0, high = n-1, mid;
        int pivot =-1;
        if(arr[0] < arr[n-1]){
            return 0;
        }
        while(low <= high){
            mid = low + (high - low)/2;
            if(mid >0 && arr[mid]<arr[mid-1]){
                return pivot = mid;
            }
            if(mid+1 <= n-1 && arr[mid]>arr[mid+1] ){
                return pivot = mid+1;
            }
            if(arr[low] < arr[mid]){
                low = mid+1;
            }
            else{
                high = mid -1;
            }

        }
        return 0;
        // if(arr[0] > arr[n-1]){
        //     return -1;
        // }
        if(arr[0] < arr[n-1]){
            return n-1;
        }
        return -1;
    }
    int searchInOneGo(vector<int> &arr, int target){
        int n = arr.size();
        int low = 0;
        int high = n-1;

        while(low<=high){
            int mid = (low+high)/2;
            if(arr[mid] == target) return mid;
            
            // left array is sorted
            if(arr[low] <= arr[mid]){
                if(target >= arr[low] && target <= arr[mid]){
                    high = mid-1;
                }
                else{
                    low = mid+1;
                }

            }
            else{
                // right array is sorted
                if(target >= arr[mid] && target <= arr[high]){
                    low = mid+1;
                }
                else{
                    high = mid-1;
                }
            }
        }
        return -1;
    }
    int search(vector<int>& nums, int target) {
        return searchInOneGo(nums, target);
        // int n = nums.size();
        // int pivot = findPivot(nums);

        // int low, high,idx =0;

        // if(pivot == 0 ){
        //     // already sorted
        //     return BS(nums, 0, n-1, target);
        // }
        // // // 
        // low = pivot, high = n-1;
        // idx = BS(nums, low, high, target);
        // cout<<pivot<<" pivot|| "<<idx<<" searched once "<<low<<" low - high "<<high<<" ";
        // if(idx == -1){
        //     cout<<low <<" "<<high;
        //     low = 0, high = pivot -1;
        //     idx = BS(nums, low, high, target) ;
        // }
        // // else {
        // //     
        // // }
        // return idx;
    }
};
```

## Attempt 5 · 2023-05-22 16:19 IST · Accepted · C++

[submission 955048937](https://leetcode.com/submissions/detail/955048937/) · tests 195/195 · runtime 3 ms (beats 1.6%)

```cpp
class Solution {
public:
    int BS(vector<int> &arr, int low, int high, int x){

        int  mid;
        int n = arr.size();
        while(low<=high){
            mid = low +(high-low)/2;
            if(arr[mid] == x){
                return mid;
            }
            else if(arr[mid] > x){
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        return -1;
    }
    int searchInOneGo(vector<int> &arr, int target){
        int n = arr.size();
        int low = 0;
        int high = n-1;

        while(low<=high){
            int mid = (low+high)/2;
            if(arr[mid] == target) return mid;
            
            // left array is sorted
            if(arr[low] <= arr[mid]){
                if(target >= arr[low] && target <= arr[mid]){
                    high = mid-1;
                }
                else{
                    low = mid+1;
                }

            }
            else{
                // right array is sorted
                if(target >= arr[mid] && target <= arr[high]){
                    low = mid+1;
                }
                else{
                    high = mid-1;
                }
            }
        }
        return -1;
    }
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
        return high;
    }
    int search(vector<int>& nums, int target) {
        // return searchInOneGo(nums, target);
        int n = nums.size();
        int pivot = findPivott(nums);
        // int pivot = findPivot(nums);
        int ans = BS(nums, 0, pivot, target);
        if(ans != -1){
            return ans;
        }
        return BS(nums, pivot + 1, n-1, target);

    }
};
```

## Attempt 6 · 2023-05-22 16:25 IST · Accepted · C++

[submission 955051699](https://leetcode.com/submissions/detail/955051699/) · tests 195/195 · runtime 10 ms (beats 0.4%)

```cpp
class Solution {
public:
    int BS(vector<int> &arr, int low, int high, int x){

        int  mid;
        int n = arr.size();
        while(low<=high){
            mid = low +(high-low)/2;
            if(arr[mid] == x){
                return mid;
            }
            else if(arr[mid] > x){
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        return -1;
    }
    int searchInOneGo(vector<int> &arr, int target){
        int n = arr.size();
        int low = 0;
        int high = n-1;

        while(low<=high){
            int mid = (low+high)/2;
            if(arr[mid] == target) return mid;
            
            // left array is sorted
            if(arr[low] <= arr[mid]){
                if(target >= arr[low] && target <= arr[mid]){
                    high = mid-1;
                }
                else{
                    low = mid+1;
                }

            }
            else{
                // right array is sorted
                if(target >= arr[mid] && target <= arr[high]){
                    low = mid+1;
                }
                else{
                    high = mid-1;
                }
            }
        }
        return -1;
    }
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
    int search(vector<int>& nums, int target) {
        // return searchInOneGo(nums, target);
        int n = nums.size();
        int pivot = findPivott(nums);
        // int pivot = findPivot(nums);
        int ans = BS(nums, 0, pivot, target);
        if(ans != -1){
            return ans;
        }
        return BS(nums, pivot + 1, n-1, target);

    }
};
```

## Attempt 7 · 2024-01-07 04:50 IST · Accepted · Python3

[submission 1138961252](https://leetcode.com/submissions/detail/1138961252/) · tests 195/195 · runtime 41 ms (beats 0.1%)

```python
class Solution:
    def search(self, nums: List[int], target: int) -> int:
        # find the pivot 
        l, r = 0, len(nums) -1 

        while l <= r:
            mid = (l+r)//2

            if nums[mid] > nums[-1]:
                l = mid +1
            else:
                r = mid - 1
        
        pivot_idx = l
        # print(pivot)

        def binarySerach(l, r, target):
            left = l
            right = r
            while left <= right:
                mid = (left+right)//2 
                if nums[mid] == target:
                    return mid
                elif nums[mid] > target:
                    right= mid -1
                else:
                    left = mid +1
            return -1
            
        print(pivot_idx)
        answer = binarySerach(0, pivot_idx, target)
        if answer !=-1:
            return answer
        return binarySerach(pivot_idx, len(nums)-1, target)
        # return answer
```

## Attempt 8 · 2025-03-22 14:58 IST · Wrong Answer · C++

[submission 1582134200](https://leetcode.com/submissions/detail/1582134200/) · tests 193/196

Failing input:

```text
[3,1]
1
```

Expected:

```text
1
```

Your output:

```text
-1
```

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0, high = nums.size()-1;
        int mid;

        while (low <= high) {
            mid = low + (high-low)/2;

            if(nums[mid] == target) return mid;

            if (nums[low] < nums[mid]) {
                if (nums[low] <= target && target <= nums[mid]) {
                    high = mid-1;
                } else {
                    low = mid+1;
                }
            } else {
                if (nums[mid] <= target && target <= nums[high]) {
                    low = mid+1;
                } else {
                    high = mid-1;
                }
            }
        }

        return -1;
    }
};
```
