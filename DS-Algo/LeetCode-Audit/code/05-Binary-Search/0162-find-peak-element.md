# 162. Find Peak Element

[Problem](https://leetcode.com/problems/find-peak-element/) · Medium · Binary Search → Peak

LeetCode tags: array, binary-search

Attempts since Mar 2023: 7 · accepted: 6 · failed before first AC: 0

## Attempt 1 · 2023-05-22 14:55 IST · Accepted · C++

[submission 955008412](https://leetcode.com/submissions/detail/955008412/) · tests 66/66 · runtime 8 ms (beats 0.1%)

```cpp
class Solution {
public:
    int findPeakElement(vector<int>& arr) {
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

## Attempt 2 · 2023-11-21 22:12 IST · Runtime Error · Python3

[submission 1103579764](https://leetcode.com/submissions/detail/1103579764/) · tests 2/66

Failing input:

```text
[1]
```

Expected:

```text
0
```

Runtime error:

```text
IndexError: list index out of range
    while i< len(nums) and nums[i+1] > nums[i]:
Line 4 in findPeakElement (Solution.py)
    ret = Solution().findPeakElement(param_1)
Line 26 in _driver (Solution.py)
    _driver()
Line 37 in <module> (Solution.py)
```

```python
class Solution:
    def findPeakElement(self, nums: List[int]) -> int:
        i = 0
        while i< len(nums) and nums[i+1] > nums[i]:
             i+=1

        return i
```

## Attempt 3 · 2023-11-21 22:13 IST · Accepted · Python3

[submission 1103580103](https://leetcode.com/submissions/detail/1103580103/) · tests 66/66 · runtime 57 ms (beats 0.3%)

```python
class Solution:
    def findPeakElement(self, nums: List[int]) -> int:
        i = 0
        while i < len(nums)-1 and nums[i+1] > nums[i]:
             i+=1

        return i
```

## Attempt 4 · 2023-11-21 22:23 IST · Accepted · Python3

[submission 1103587049](https://leetcode.com/submissions/detail/1103587049/) · tests 66/66 · runtime 45 ms (beats 0.3%)

```python
class Solution:
    def findPeakElement1(self, nums: List[int]) -> int:
        i = 0
        
        while i < len(nums)-1 and nums[i+1] > nums[i]:
             i+=1

        return i   


    def findPeakElement(self, nums: List[int]) -> int:
        l, r = 0, len(nums)-1

        while l < r:
            mid = (l + r)//2

            if nums[mid+1] > nums[mid]:
                l = mid +1
            else:
                r = mid
        
        return l
```

## Attempt 5 · 2023-12-05 00:49 IST · Accepted · Python3

[submission 1112390472](https://leetcode.com/submissions/detail/1112390472/) · tests 66/66 · runtime 43 ms (beats 0.3%)

```python
class Solution:
    def findPeakElement1(self, nums: List[int]) -> int:
        '''
        1. peak is in middle
        2. start is peak
        3. end is peak
         

        approach 1: O(n)
        go on climbing the hill to find peak - as long as next element is greater than current
        you will reach peak eventually


        approach 2: for uphill and downhill there is some way of sorting, which can aid in binary search decision making if there are no plateus or duplicates. if you encounter duplicates, you won't be able to decide which way to go

        '''
        i = 0
        
        while i < len(nums)-1 and nums[i+1] > nums[i]:
             i+=1

        return i   



    def findPeakElement(self, nums: List[int]) -> int:
        # run simple binary search to find peak
        # keep pointer on the max value on both end
        l, r = 0, len(nums)-1

        while l < r:
            mid = (l + r)//2

            if nums[mid+1] > nums[mid]:
                l = mid +1
            else:
                r = mid
        
        return l
```

## Attempt 6 · 2024-01-22 03:06 IST · Accepted · Python3

[submission 1152981759](https://leetcode.com/submissions/detail/1152981759/) · tests 66/66 · runtime 43 ms (beats 0.3%)

```python
class Solution:
    def findPeakElement1(self, nums: List[int]) -> int:
        '''
        1. peak is in middle
        2. start is peak
        3. end is peak
         

        approach 1: O(n)
        go on climbing the hill to find peak - as long as next element is greater than current
        you will reach peak eventually


        approach 2: for uphill and downhill there is some way of sorting, which can aid in binary search decision making if there are no plateus or duplicates. if you encounter duplicates, you won't be able to decide which way to go

        '''
        i = 0
        
        while i < len(nums)-1 and nums[i+1] > nums[i]:
             i+=1

        return i   



    def findPeakElement(self, nums: List[int]) -> int:
        # run simple binary search to find peak
        # keep pointer on the max value on both end
        l, r = 0, len(nums)-1

        while l < r:
            mid = (l + r)//2

            if nums[mid+1] > nums[mid]:
                l = mid +1
            else:
                r = mid
        
        return l
    
    def findPeakElement1(self, nums: List[int]) -> int:
        indx = 0
        while indx < len(nums) and nums[i+1] > nums[i]:
            i+=1

        return i

    def findPeakElement(self, nums: List[int]) -> int:
        l = 0
        r = len(nums)-1
        
        while l<r:
            mid = (l+r)//2
            if nums[mid] <= nums[mid+1]:
                l = mid + 1
            else:
                r = mid
        return l
```

## Attempt 7 · 2024-02-06 05:37 IST · Accepted · Python3

[submission 1167286757](https://leetcode.com/submissions/detail/1167286757/) · tests 66/66 · runtime 30 ms (beats 0.3%)

```python
class Solution:
    def findPeakElement1(self, nums: List[int]) -> int:
        '''
        1. peak is in middle
        2. start is peak
        3. end is peak
         

        approach 1: O(n)
        go on climbing the hill to find peak - as long as next element is greater than current
        you will reach peak eventually


        approach 2: for uphill and downhill there is some way of sorting, which can aid in binary search decision making if there are no plateus or duplicates. if you encounter duplicates, you won't be able to decide which way to go

        '''
        i = 0
        
        while i < len(nums)-1 and nums[i+1] > nums[i]:
             i+=1

        return i   



    def findPeakElement(self, nums: List[int]) -> int:
        # run simple binary search to find peak
        # keep pointer on the max value on both end
        l, r = 0, len(nums)-1

        while l < r:
            mid = (l + r)//2

            if nums[mid+1] > nums[mid]:
                l = mid +1
            else:
                r = mid
        
        return l
    
    def findPeakElement1(self, nums: List[int]) -> int:
        indx = 0
        while indx < len(nums) and nums[i+1] > nums[i]:
            i+=1

        return i

    def findPeakElement(self, nums: List[int]) -> int:
        l = 0
        r = len(nums)-1
        
        while l<r:
            mid = (l+r)//2
            if nums[mid] < nums[mid+1]:
                l = mid + 1
            else:
                r = mid
        return l
```
