# 1060. Missing Element in Sorted Array

[Problem](https://leetcode.com/problems/missing-element-in-sorted-array/) · Medium · Binary Search → Missing-count search

LeetCode tags: array, binary-search

Attempts since Mar 2023: 4 · accepted: 3 · failed before first AC: 1

## Attempt 1 · 2023-12-12 01:03 IST · Wrong Answer · Python3

[submission 1117497054](https://leetcode.com/submissions/detail/1117497054/) · tests 8/37

Failing input:

```text
[4,7,9,10]
1
```

Expected:

```text
5
```

Your output:

```text
8
```

```python
class Solution:
    def missingElement(self, nums: List[int], k: int) -> int:
        n = len(nums)
        for i in range(1, n):
            # total numbers missing between the gap
            missing_in_gap = nums[i] - nums[i-1] - 1

            # 5 8 -> missing 6 and 7 
            # if you are looking for 2nd 
            # and missing is >=k that means missing is 5+2
            if missing_in_gap >=k:
                nums[i-1] +k
            
            # relative to new number how many missing 
            k-= missing_in_gap

        # if number is past the last digit
        return nums[n-1] +k
```

## Attempt 2 · 2023-12-12 01:03 IST · Accepted · Python3

[submission 1117497243](https://leetcode.com/submissions/detail/1117497243/) · tests 37/37 · runtime 266 ms (beats 5.8%)

```python
class Solution:
    def missingElement(self, nums: List[int], k: int) -> int:
        n = len(nums)
        for i in range(1, n):
            # total numbers missing between the gap
            missing_in_gap = nums[i] - nums[i-1] - 1

            # 5 8 -> missing 6 and 7 
            # if you are looking for 2nd 
            # and missing is >=k that means missing is 5+2
            if missing_in_gap >=k:
                return nums[i-1] +k
            
            # relative to new number how many missing 
            k-= missing_in_gap

        # if number is past the last digit
        return nums[n-1] +k
```

## Attempt 3 · 2024-01-07 02:57 IST · Accepted · Python3

[submission 1138908166](https://leetcode.com/submissions/detail/1138908166/) · tests 37/37 · runtime 226 ms (beats 5.8%)

```python
class Solution:
    def missingElement(self, nums: List[int], k: int) -> int:
        n = len(nums)
        for i in range(1, n):
            # total numbers missing between the gap
            missing_in_gap = nums[i] - nums[i-1] - 1

            # 5 8 -> missing 6 and 7 
            # if you are looking for 2nd 
            # and missing is >=k that means missing is 5+2
            if missing_in_gap >=k:
                return nums[i-1] +k
            
            # relative to new number how many missing 
            k-= missing_in_gap

        # if number is past the last digit
        return nums[n-1] +k 

    def missingElement(self,nums, k):
        left = 0
        right = len(nums) - 1

        # Calculate the total number of missing numbers up to the end of the array
        total_missing = nums[-1] - nums[0] + 1 - len(nums)

        # If kth missing number is beyond the last element in nums
        if k > total_missing:
            # Calculate how many numbers are missing beyond the last element
            additional_missing = k - total_missing
            # The kth missing number is then the last element plus this additional count
            return nums[-1] + additional_missing
            
        while left < right:
            mid = (left + right) // 2
            missing = nums[mid] - nums[0] - mid
            if k > missing:
                left = mid + 1
            else:
                right = mid

        print(left)
        # Adjust k for the number of missing numbers already found
        k -= (nums[left - 1] - nums[0] - (left - 1))
        
        # Return the kth missing number after nums[left - 1]
        return nums[left - 1] + k
```

## Attempt 4 · 2024-01-24 09:18 IST · Accepted · Python3

[submission 1155179452](https://leetcode.com/submissions/detail/1155179452/) · tests 37/37 · runtime 218 ms (beats 5.8%)

```python
class Solution:
    def missingElement(self, nums: List[int], k: int) -> int:
        n = len(nums)
        for i in range(1, n):
            # total numbers missing between the gap
            missing_in_gap = nums[i] - nums[i-1] - 1

            # 5 8 -> missing 6 and 7 
            # if you are looking for 2nd 
            # and missing is >=k that means missing is 5+2
            if missing_in_gap >=k:
                return nums[i-1] +k
            
            # relative to new number how many missing 
            k-= missing_in_gap

        # if number is past the last digit
        return nums[n-1] +k 

    def missingElement(self,nums, k):
        left = 0
        right = len(nums) - 1

        # Calculate the total number of missing numbers up to the end of the array
        total_missing = nums[-1] - nums[0] + 1 - len(nums)

        # # If kth missing number is beyond the last element in nums
        # if k > total_missing:
        #     # Calculate how many numbers are missing beyond the last element
        #     additional_missing = k - total_missing
        #     # The kth missing number is then the last element plus this additional count
        #     return nums[-1] + additional_missing
            
        while left <= right:
            mid = (left + right) // 2
            missing = nums[mid] - nums[0] - mid
            if k > missing:
                left = mid + 1
            else:
                right = mid - 1
        print(left, right)
        missing_till_previous = nums[left-1] - nums[0] - (left-1)
        k_from_previous = k - missing_till_previous
        return nums[left-1]+ k_from_previous

        # # Adjust k for the number of missing numbers already found
        # k -= (nums[left - 1] - nums[0] - (left - 1))
        
        # # Return the kth missing number after nums[left - 1]
        # return nums[left - 1] + k
```
