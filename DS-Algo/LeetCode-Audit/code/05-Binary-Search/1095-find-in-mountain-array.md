# 1095. Find in Mountain Array

[Problem](https://leetcode.com/problems/find-in-mountain-array/) · Hard · Binary Search → Peak + two searches

LeetCode tags: array, binary-search, interactive, ternary-search

Attempts since Mar 2023: 8 · accepted: 6 · failed before first AC: 1

## Attempt 1 · 2023-05-22 14:46 IST · Wrong Answer · C++

[submission 955004567](https://leetcode.com/submissions/detail/955004567/) · tests 52/78

Failing input:

```text
[1,2,3,4,5,3,1]
2
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
/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int low = 0, high = mountainArr.length() -1;
        int ans =-1;

        while(low < high){
            int mid = (low + high)>>1;
            int midVal = mountainArr.get(mid);
            int next = mountainArr.get(mid+1);
            if(mid > midVal){
                high = mid;
            }
            else{
                low = mid+1;
            }
        }
        int maxiInd = low;
        // Binary search in both of the MountainArray
        // 0, maxiInd and maxiInd+1, length()
        low = 0, high = maxiInd;
        while(low < high){
            int mid = (low + high)>>1;
            int midVal = mountainArr.get(mid);
            if(midVal > target){
                high = mid-1;
            }
            else if(midVal < target){
                low = mid+1;
            }
            else{
                ans = mid;
                high = mid -1;
            }
        }
        if(ans != -1) return ans;
        
        low = maxiInd, high = mountainArr.length() -1;
        while(low < high){
            int mid = (low + high)>>1;
            int midVal = mountainArr.get(mid);
            if(midVal > target){
                low = mid + 1;
                
            }
            else if(midVal < target){
                high = mid-1;
            }
            else{
                ans = mid;
                high = mid -1;
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-05-22 14:52 IST · Accepted · C++

[submission 955007097](https://leetcode.com/submissions/detail/955007097/) · tests 78/78 · runtime 4 ms (beats 76.2%)

```cpp
/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int low = 0, high = mountainArr.length() -1;
        int ans =-1;

        while(low < high){
            int mid = (low + high)>>1;
            int midVal = mountainArr.get(mid);
            int next = mountainArr.get(mid+1);
            if(midVal > next){
                high = mid;
            }
            else{
                low = mid+1;
            }
        }
        int maxiInd = low;
        // Binary search in both of the MountainArray
        // 0, maxiInd and maxiInd+1, length()
        low = 0, high = maxiInd;
        // cout<<maxiInd<<" -- ";
        while(low <= high){
            int mid = (low + high)>>1;
            int midVal = mountainArr.get(mid);
            if(midVal > target){
                high = mid-1;
            }
            else if(midVal < target){
                low = mid+1;
            }
            else{
                ans = mid;
                high = mid -1;
            }
        }
        // cout<<ans;
        if(ans != -1) return ans;
        
        low = maxiInd, high = mountainArr.length() -1;
        while(low <= high){
            int mid = (low + high)>>1;
            int midVal = mountainArr.get(mid);
            if(midVal > target){
                low = mid + 1;
            }
            else if(midVal < target){
                high = mid-1;
            }
            else{
                ans = mid;
                high = mid -1;
            }
        }
        return ans;
    }
};
```

## Attempt 3 · 2023-05-22 15:37 IST · Accepted · C++

[submission 955028890](https://leetcode.com/submissions/detail/955028890/) · runtime 10 ms

_Code not returned by LeetCode._

## Attempt 4 · 2023-05-22 15:38 IST · Accepted · C++

[submission 955029117](https://leetcode.com/submissions/detail/955029117/) · tests 78/78 · runtime 6 ms (beats 32.5%)

```cpp
/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

class Solution {
    int orderAgnonsticBS(MountainArray &arr, int target, int low, int high){
        bool isAsc = true;
        isAsc = arr.get(low) >= arr.get(high) 
                                ? false : true;
        int ans = -1;
        while(low <= high){
            int mid = (low + high)>>1;
            int midVal = arr.get(mid);
            if(midVal > target){
                if(isAsc) high = mid-1;
                else low = mid+1;
            }
            else if(midVal < target){
                if(isAsc) low = mid+1;
                else high = mid -1;
            }
            else{
                ans = mid;
                high = mid -1;
            }
        }
        return ans;
    }
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int low = 0, high = mountainArr.length() -1;
        int ans =-1;

        while(low < high){
            int mid = (low + high)>>1;
            int midVal = mountainArr.get(mid);
            int next = mountainArr.get(mid+1);
            if(midVal > next){
                high = mid;
            }
            else{
                low = mid+1;
            }
        }
        int maxiInd = low;
        // Binary search in both of the MountainArray
        // 0, maxiInd and maxiInd+1, length()
        low = 0, high = maxiInd;
        ans = orderAgnonsticBS(mountainArr, target, low, high);

        if(ans != -1) return ans;
        
        low = maxiInd+1, high = mountainArr.length() -1;
        ans = orderAgnonsticBS(mountainArr, target, low, high);

        return ans;
    }
};
```

## Attempt 5 · 2023-12-29 06:10 IST · Wrong Answer · Python3

[submission 1130977442](https://leetcode.com/submissions/detail/1130977442/) · tests 77/79

Failing input:

```text
[0,5,3,1]
1
```

Expected:

```text
3
```

Your output:

```text
-1
```

```python
# """
# This is MountainArray's API interface.
# You should not implement it, or speculate about its implementation
# """
#class MountainArray:
#    def get(self, index: int) -> int:
#    def length(self) -> int:

class Solution:
    def findInMountainArray(self, target: int, mountain_arr: 'MountainArray') -> int:
        # 1. find peak index using binary search
        length = mountain_arr.length()
        l = 0
        r = length-1

        while l<r:
            mid = (l+r)//2
            if mountain_arr.get(mid) < mountain_arr.get(mid+1):
                l = mid+1
            else:
                r = mid
        peak_index = l
        

        #2. search in strictly increaseing part of th earry
        #from 0 to peak_index find value target
        l = 0
        r = peak_index

        while l <=r:
            mid = (l+r)//2
            if mountain_arr.get(mid) == target:
                return mid
            elif mountain_arr.get(mid) < target:
                l = mid+1
            else:
                r = mid - 1

        # still not found in the increasing part - check decreasing part
        l = peak_index+1
        r = length -1

        while l <=r:
            mid = (l+r)//2
            if mountain_arr.get(mid) == target:
                return mid
            elif mountain_arr.get(mid) < target:
                l = mid+1
            else:
                r = mid - 1

        return -1
```

## Attempt 6 · 2023-12-29 06:11 IST · Accepted · Python3

[submission 1130977791](https://leetcode.com/submissions/detail/1130977791/) · tests 79/79 · runtime 56 ms (beats 5.8%)

```python
# """
# This is MountainArray's API interface.
# You should not implement it, or speculate about its implementation
# """
#class MountainArray:
#    def get(self, index: int) -> int:
#    def length(self) -> int:

class Solution:
    def findInMountainArray(self, target: int, mountain_arr: 'MountainArray') -> int:
        # 1. find peak index using binary search
        length = mountain_arr.length()
        l = 0
        r = length-1

        while l<r:
            mid = (l+r)//2
            if mountain_arr.get(mid) < mountain_arr.get(mid+1):
                l = mid+1
            else:
                r = mid
        peak_index = l
        

        #2. search in strictly increaseing part of th earry
        #from 0 to peak_index find value target
        l = 0
        r = peak_index

        while l <=r:
            mid = (l+r)//2
            if mountain_arr.get(mid) == target:
                return mid
            elif mountain_arr.get(mid) < target:
                l = mid+1
            else:
                r = mid - 1

        # still not found in the increasing part - check decreasing part
        l = peak_index+1
        r = length -1

        while l <=r:
            mid = (l+r)//2
            if mountain_arr.get(mid) == target:
                return mid
            elif mountain_arr.get(mid) > target:
                l = mid+1
            else:
                r = mid - 1

        return -1
```

## Attempt 7 · 2023-12-29 06:12 IST · Accepted · Python3

[submission 1130978155](https://leetcode.com/submissions/detail/1130978155/) · tests 79/79 · runtime 75 ms (beats 5.8%)

```python
# """
# This is MountainArray's API interface.
# You should not implement it, or speculate about its implementation
# """
#class MountainArray:
#    def get(self, index: int) -> int:
#    def length(self) -> int:

class Solution:
    def findInMountainArray(self, target: int, mountain_arr: 'MountainArray') -> int:
        # 1. find peak index using binary search
        length = mountain_arr.length()
        l = 0
        r = length-1

        while l<r:
            mid = (l+r)//2
            if mountain_arr.get(mid) < mountain_arr.get(mid+1):
                l = mid+1
            else:
                r = mid
        peak_index = l
        

        #2. search in strictly increaseing part of th earry
        #from 0 to peak_index find value target
        l = 0
        r = peak_index

        while l <=r:
            mid = (l+r)//2
            if mountain_arr.get(mid) == target:
                return mid
            elif mountain_arr.get(mid) < target:
                l = mid+1
            else:
                r = mid - 1

        # still not found in the increasing part - check decreasing part
        l = peak_index+1
        r = length -1

        while l <=r:
            mid = (l+r)//2
            if mountain_arr.get(mid) == target:
                return mid
            elif mountain_arr.get(mid) > target:
                l = mid+1
            else:
                r = mid - 1

        return -1
```

## Attempt 8 · 2024-01-07 04:40 IST · Accepted · Python3

[submission 1138956729](https://leetcode.com/submissions/detail/1138956729/) · tests 79/79 · runtime 36 ms (beats 94.8%)

```python
# """
# This is MountainArray's API interface.
# You should not implement it, or speculate about its implementation
# """
#class MountainArray:
#    def get(self, index: int) -> int:
#    def length(self) -> int:

class Solution:
    def findInMountainArray(self, target: int, mountain_arr: 'MountainArray') -> int:
        # 1. find peak index using binary search
        length = mountain_arr.length()
        l = 0
        r = length-1

        while l<r:
            mid = (l+r)//2
            if mountain_arr.get(mid) < mountain_arr.get(mid+1):
                l = mid+1
            else:
                r = mid
        peak_index = l
        

        #2. search in strictly increaseing part of th earry
        #from 0 to peak_index find value target
        l = 0
        r = peak_index

        while l <=r:
            mid = (l+r)//2
            if mountain_arr.get(mid) == target:
                return mid
            elif mountain_arr.get(mid) < target:
                l = mid+1
            else:
                r = mid - 1

        # still not found in the increasing part - check decreasing part
        l = peak_index+1
        r = length -1

        while l <=r:
            mid = (l+r)//2
            if mountain_arr.get(mid) == target:
                return mid
            elif mountain_arr.get(mid) > target:
                l = mid+1
            else:
                r = mid - 1

        return -1
```
