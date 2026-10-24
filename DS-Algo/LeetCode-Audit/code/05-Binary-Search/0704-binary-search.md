# 704. Binary Search

[Problem](https://leetcode.com/problems/binary-search/) · Easy · Binary Search → Classic search

LeetCode tags: array, binary-search

Attempts since Mar 2023: 7 · accepted: 5 · failed before first AC: 0

## Attempt 1 · 2023-03-07 00:05 IST · Accepted · C++

[submission 910349125](https://leetcode.com/submissions/detail/910349125/) · tests 47/47 · runtime 47 ms (beats 0.1%)

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        
        int low= 0, high = nums.size()-1, mid =0;
        int index = -1;
        for(; low<=high;){
            mid = (low+high)/2;
            if(nums[mid] == target){
                index = mid;
                break;
            }
            else if(nums[mid] > target){
                high = mid -1;
            }
            else{
                low = mid +1;
            }
        }
        return index;
    }
};
```

## Attempt 2 · 2023-03-07 00:31 IST · Accepted · C++

[submission 910363447](https://leetcode.com/submissions/detail/910363447/) · tests 47/47 · runtime 43 ms (beats 0.1%)

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        
        int low= 0, high = nums.size()-1, mid =0;
        int index = -1;
        for(; low<=high;){
            mid = (low+high)/2;
            if(nums[mid] == target){
                index = mid;
                break;
            }
            else if(nums[mid] > target){
                high = mid -1;
            }
            else{
                low = mid +1;
            }
        }
        return index;
    }
};
```

## Attempt 3 · 2023-08-17 23:41 IST · Accepted · C++

[submission 1024207359](https://leetcode.com/submissions/detail/1024207359/) · tests 47/47 · runtime 30 ms (beats 0.1%)

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int start=0, end=nums.size()-1, mid;
        if(target<nums[0] || target>nums[end]) {
            return -1;
        }
        while(start<=end) {
            mid = (start+end)/2;
            if(target==nums[mid]) {
                return mid;
            } else if(target > nums[mid]) {
                start = mid+1;
            } else {
                end = mid-1;
            }
        }
        return -1;
    }
};
```

## Attempt 4 · 2023-11-13 23:04 IST · Accepted · Python3

[submission 1098061854](https://leetcode.com/submissions/detail/1098061854/) · tests 47/47 · runtime 238 ms (beats 0.2%)

```python
class Solution:
    def search(self, nums: List[int], target: int) -> int:
        l = 0
        r = len(nums) -1 
        
        while l <= r:
            mid = (l+r) //2
            if nums[mid] == target:
                return mid
            elif nums[mid] < target:
                l = l+1
            else:
                r = r - 1
        return -1
```

## Attempt 5 · 2023-11-13 23:20 IST · Wrong Answer · Python3

[submission 1098072700](https://leetcode.com/submissions/detail/1098072700/) · tests 33/47

Failing input:

```text
[5]
5
```

Expected:

```text
0
```

Your output:

```text
-1
```

```python
class Solution:
    def search(self, nums: List[int], target: int) -> int:
        l = 0
        r = len(nums) -1 
        
        while l < r:
            mid = (l+r) //2
            if nums[mid] == target:
                return mid
            elif nums[mid] < target:
                l = l+1
            else:
                r = r - 1
        return -1
```

## Attempt 6 · 2023-11-13 23:23 IST · Wrong Answer · Python3

[submission 1098074316](https://leetcode.com/submissions/detail/1098074316/) · tests 24/47

Failing input:

```text
[5]
5
```

Expected:

```text
0
```

Your output:

```text
-1
```

```python
class Solution:
    def search(self, nums: List[int], target: int) -> int:
        l = 0
        r = len(nums) -1 
        
        while l < r:
            mid = (l+r) //2
            if nums[mid] == target:
                return mid
            elif nums[mid] < target:
                l = mid+1
            else:
                r = mid - 1
        return -1
```

## Attempt 7 · 2023-11-13 23:23 IST · Accepted · Python3

[submission 1098074392](https://leetcode.com/submissions/detail/1098074392/) · tests 47/47 · runtime 212 ms (beats 0.2%)

```python
class Solution:
    def search(self, nums: List[int], target: int) -> int:
        l = 0
        r = len(nums) -1 
        
        while l <= r:
            mid = (l+r) //2
            if nums[mid] == target:
                return mid
            elif nums[mid] < target:
                l = mid+1
            else:
                r = mid - 1
        return -1
```
