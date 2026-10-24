# 81. Search in Rotated Sorted Array II

[Problem](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/) · Medium · Binary Search → Rotated with duplicates

LeetCode tags: array, binary-search

Attempts since Mar 2023: 6 · accepted: 1 · failed before first AC: 5

## Attempt 1 · 2023-05-22 16:22 IST · Wrong Answer · C++

[submission 955050225](https://leetcode.com/submissions/detail/955050225/) · tests 275/280

Failing input:

```text
[1,0,1,1,1]
0
```

Expected:

```text
true
```

Your output:

```text
false
```

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

    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        int pivot = findPivott(nums);
        // int pivot = findPivot(nums);
        int ans = BS(nums, 0, pivot, target);
        if(ans != -1){
            return true;
        }
        ans = BS(nums, pivot + 1, n-1, target);
        return ans!=-1 ? true : false;
    }
};
```

## Attempt 2 · 2023-05-22 16:24 IST · Wrong Answer · C++

[submission 955050917](https://leetcode.com/submissions/detail/955050917/) · tests 272/280

Failing input:

```text
[1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1]
2
```

Expected:

```text
true
```

Your output:

```text
false
```

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

    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        int pivot = findPivott(nums);
        int ans = BS(nums, 0, pivot, target);
        if(ans != -1){
            return true;
        }
        ans = BS(nums, pivot + 1, n-1, target);
        return ans!=-1 ? true : false;
    }
};
```

## Attempt 3 · 2023-05-22 16:53 IST · Runtime Error · C++

[submission 955064764](https://leetcode.com/submissions/detail/955064764/) · tests 10/280

Failing input:

```text
[1,1]
0
```

Expected:

```text
false
```

Runtime error:

```text
=================================================================
==22==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x6020000005f8 at pc 0x00000034c867 bp 0x7ffda53295f0 sp 0x7ffda53295e8
READ of size 4 at 0x6020000005f8 thread T0
    #3 0x7f9ef51e1082  (/lib/x86_64-linux-gnu/libc.so.6+0x24082)
0x6020000005f8 is located 0 bytes to the right of 8-byte region [0x6020000005f0,0x602000000 ... [1533 more chars]
```

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

    int findPivott(vector<int> &arr){
        int low = 0, high = arr.size()-1;

        while(low < high){
            while(low < high && arr[low] == arr[low+1])
                low++;
            while(low < high && arr[high] == arr[high-1])
                high--;

            int mid = low + ((high - low)>>1);
            if(arr[mid] > arr[mid+1]){
                return mid;
            }

            if(arr[low] < arr[mid]) {
                low = mid + 1;
            }
            else {
                high = mid -1;
            }
        }
        return high;
    }

    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        int pivot = findPivott(nums);
        cout<<pivot<<" "<<nums[pivot]<<" ";
        int ans = BS(nums, 0, pivot, target);
        if(ans != -1){
            return true;
        }
        ans = BS(nums, pivot + 1, n-1, target);
        return ans!=-1 ? true : false;
    }
};
```

## Attempt 4 · 2023-05-22 16:55 IST · Runtime Error · C++

[submission 955065537](https://leetcode.com/submissions/detail/955065537/) · tests 13/280

Failing input:

```text
[1,3]
0
```

Expected:

```text
false
```

Runtime error:

```text
Line 1034: Char 34: runtime error: addition of unsigned offset to 0x602000000770 overflowed to 0x60200000076c (stl_vector.h)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior /usr/bin/../lib/gcc/x86_64-linux-gnu/9/../../../../include/c++/9/bits/stl_vector.h:1043:34
```

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

    int findPivott(vector<int> &arr){
        int low = 0, high = arr.size()-1;

        while(low < high){
            while(low < high && arr[low] == arr[low+1])
                low++;
            while(low < high && arr[high] == arr[high-1])
                high--;

            if(low >= high) break;

            int mid = low + ((high - low)>>1);
            if(arr[mid] > arr[mid+1]){
                return mid;
            }

            if(arr[low] < arr[mid]) {
                low = mid + 1;
            }
            else {
                high = mid -1;
            }
        }
        return high;
    }

    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        int pivot = findPivott(nums);
        cout<<pivot<<" "<<nums[pivot]<<" ";
        int ans = BS(nums, 0, pivot, target);
        if(ans != -1){
            return true;
        }
        ans = BS(nums, pivot + 1, n-1, target);
        return ans!=-1 ? true : false;
    }
};
```

## Attempt 5 · 2023-05-22 16:56 IST · Wrong Answer · C++

[submission 955066071](https://leetcode.com/submissions/detail/955066071/) · tests 279/280

Failing input:

```text
[15,16,19,20,25,1,3,4,5,7,10,14]
25
```

Expected:

```text
true
```

Your output:

```text
false
```

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

    int findPivott(vector<int> &arr){
        int low = 0, high = arr.size()-1;

        while(low < high){
            while(low < high && arr[low] == arr[low+1])
                low++;
            while(low < high && arr[high] == arr[high-1])
                high--;

            if(low >= high) break;

            int mid = low + ((high - low)>>1);
            if(arr[mid] > arr[mid+1]){
                return mid;
            }

            if(arr[low] < arr[mid]) {
                low = mid + 1;
            }
            else {
                high = mid -1;
            }
        }
        return high;
    }

    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        int pivot = findPivott(nums);
        // cout<<pivot<<" "<<nums[pivot]<<" ";
        int ans = BS(nums, 0, pivot, target);
        if(ans != -1){
            return true;
        }
        ans = BS(nums, pivot + 1, n-1, target);
        return ans!=-1 ? true : false;
    }
};
```

## Attempt 6 · 2023-05-22 17:01 IST · Accepted · C++

[submission 955068317](https://leetcode.com/submissions/detail/955068317/) · tests 280/280 · runtime 10 ms (beats 0.6%)

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

    int findPivott(vector<int> &arr){
        int low = 0, high = arr.size()-1;

        while(low < high){
            while(low < high && arr[low] == arr[low+1])
                low++;
            while(low < high && arr[high] == arr[high-1])
                high--;

            if(low >= high) break;

            int mid = low + ((high - low)>>1);
            if(arr[mid] > arr[mid+1]){
                return mid;
            }

            if(arr[low] <= arr[mid]) {
                low = mid + 1;
            }
            else {
                high = mid -1;
            }
        }
        return high;
    }

    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        int pivot = findPivott(nums);
        cout<<pivot<<" pivot "<<" ";
        int ans = BS(nums, 0, pivot, target);
        if(ans != -1){
            return true;
        }
        ans = BS(nums, pivot + 1, n-1, target);
        return ans!=-1 ? true : false;
    }
};
```
