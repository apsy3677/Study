# 1004. Max Consecutive Ones III

[Problem](https://leetcode.com/problems/max-consecutive-ones-iii/) · Medium · Sliding Window → At most k zeros

LeetCode tags: array, binary-search, sliding-window, prefix-sum

Attempts since Mar 2023: 4 · accepted: 4 · failed before first AC: 0

## Attempt 1 · 2023-08-25 23:35 IST · Accepted · C++

[submission 1031644223](https://leetcode.com/submissions/detail/1031644223/) · tests 55/55 · runtime 61 ms (beats 5.8%)

```cpp
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n=nums.size(), m=k, i=0, maxLength = 0, currLength = 0;
        for(i;i<n;i++) {
            if(nums[i] == 0 && m > 0 ) {
                currLength++;
                m--;
            } else if (nums[i] == 0) {
                while(nums[i-currLength] != 0 ) {
                    currLength--;
                }
                if (currLength<0) {
                    currLength=0;
                }
            } else {
                currLength++;
            }

            if(currLength > maxLength) {
                maxLength = currLength;
            }
        }
        return maxLength;
    }
};
```

## Attempt 2 · 2023-11-18 20:26 IST · Accepted · Python3

[submission 1101456423](https://leetcode.com/submissions/detail/1101456423/) · tests 55/55 · runtime 518 ms (beats 5.1%)

```python
class Solution:
    def longestOnes(self, nums: List[int], k: int) -> int:
        l, r = 0,0
        count_zeros = 0
        count_ones = 0
        while r< len(nums):
            if nums[r] ==0:
                count_zeros +=1

            while count_zeros >k and l<=r:
                if nums[l] ==0:
                    count_zeros -=1
                l+=1
            
            count_ones = max(count_ones, r-l+1)
            r+=1
        return count_ones
```

## Attempt 3 · 2024-01-16 00:59 IST · Accepted · Python3

[submission 1147176998](https://leetcode.com/submissions/detail/1147176998/) · tests 55/55 · runtime 488 ms (beats 5.1%)

```python
class Solution:
    def longestOnes(self, nums: List[int], k: int) -> int:
        l, r = 0,0
        count_zeros = 0
        count_ones = 0
        while r< len(nums):
            if nums[r] ==0:
                count_zeros +=1

            while count_zeros >k and l<=r:
                if nums[l] ==0:
                    count_zeros -=1
                l+=1
            
            count_ones = max(count_ones, r-l+1)
            r+=1
        return count_ones

    def longestOnes(self, nums: List[int], k: int) -> int: 
        r =0
        max_ones=0
        current_max=0
        while r< len(nums):
            if nums[r] ==0:
                current_max = 0
            else:
                current_max +=1
                max_ones = max(max_ones, current_max)
            r+=1
        return max_ones

    def longestOnes(self, nums: List[int], k: int) -> int: 
        left, right =0,0
        count_zeros = 0
        count_ones =0 

        # iterate
        while right < len(nums):

            # while explanding the window
            if nums[right] == 0:
                count_zeros +=1

            # if invalid - make window valid by contracting
            while left <= right and count_zeros >k:
                if nums[left] == 0:
                    count_zeros -=1
                left+=1

            # here it is a valid window
            count_ones = max(count_ones, right-left+1)
            right+=1
        return count_ones

    def longestOnes(self, nums: List[int], k: int) -> int:
        l = r = 0
        count_zeros = 0
        max_count = 0

        while r < len(nums):
            if nums[r] ==0:
                count_zeros +=1

            if l <=r and count_zeros >k:
                if nums[l] == 0:
                    count_zeros -=1
                l +=1

            # get max
            max_count = max(max_count, r-l+1)
            r+=1
        return max_count
```

## Attempt 4 · 2024-01-27 22:21 IST · Accepted · Python3

[submission 1158417154](https://leetcode.com/submissions/detail/1158417154/) · tests 55/55 · runtime 724 ms (beats 5.1%)

```python
class Solution:
    def longestOnes(self, nums: List[int], k: int) -> int:
        l, r = 0,0
        count_zeros = 0
        count_ones = 0
        while r< len(nums):
            if nums[r] ==0:
                count_zeros +=1

            while count_zeros >k and l<=r:
                if nums[l] ==0:
                    count_zeros -=1
                l+=1
            
            count_ones = max(count_ones, r-l+1)
            r+=1
        return count_ones

    def longestOnes(self, nums: List[int], k: int) -> int: 
        r =0
        max_ones=0
        current_max=0
        while r< len(nums):
            if nums[r] ==0:
                current_max = 0
            else:
                current_max +=1
                max_ones = max(max_ones, current_max)
            r+=1
        return max_ones

    def longestOnes(self, nums: List[int], k: int) -> int: 
        left, right =0,0
        count_zeros = 0
        count_ones =0 

        # iterate
        while right < len(nums):

            # while explanding the window
            if nums[right] == 0:
                count_zeros +=1

            # if invalid - make window valid by contracting
            while left <= right and count_zeros >k:
                if nums[left] == 0:
                    count_zeros -=1
                left+=1

            # here it is a valid window
            count_ones = max(count_ones, right-left+1)
            right+=1
        return count_ones

    def longestOnes(self, nums: List[int], k: int) -> int:
        l = r = 0
        count_zeros = 0
        max_count = 0

        while r < len(nums):
            if nums[r] ==0:
                count_zeros +=1

            while l <=r and count_zeros >k:
                if nums[l] == 0:
                    count_zeros -=1
                l +=1

            print(l,r, count_zeros)

            # get max
            max_count = max(max_count, r-l+1)
            r+=1
        return max_count
```
