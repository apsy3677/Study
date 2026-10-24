# 259. 3Sum Smaller

[Problem](https://leetcode.com/problems/3sum-smaller/) · Medium · Two Pointers → Sort + two pointers

LeetCode tags: array, two-pointers, binary-search, sorting

Attempts since Mar 2023: 3 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-11-23 07:47 IST · Accepted · Python3

[submission 1104553566](https://leetcode.com/submissions/detail/1104553566/) · tests 316/316 · runtime 1025 ms (beats 13.1%)

```python
class Solution:
    def threeSumSmaller(self, nums: List[int], target: int) -> int:
        nums.sort()
        n = len(nums)
        count=0
        for i in range(n-1):
            left = i+1
            right = n-1
            
            while left < right:
                total = nums[i] + nums[left] + nums[right]

                if total< target:
                    count += right-left
                    left +=1
                else:
                    right -=1
        return count
```

## Attempt 2 · 2023-11-23 07:58 IST · Output Limit Exceeded · Python3

[submission 1104557332](https://leetcode.com/submissions/detail/1104557332/) · tests 314/316

Failing input:

```text
[30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30, ... [10103 more chars]
```

Expected:

```text
0
```

```python
class Solution:
    def threeSumSmaller(self, nums: List[int], target: int) -> int:
        nums.sort()
        n = len(nums) - 1
        print(nums)
        count=0
        for i in range(n-1):
            print(i)
            left = i+1
            right = n
            
            while left < right:
                print(left, right)
                total = nums[i] + nums[left] + nums[right]

                if total< target:
                    # print(i, left, right)
                    count += right-left
                    left +=1
                else:
                    right -=1
        return count
```

## Attempt 3 · 2023-11-23 08:00 IST · Accepted · Python3

[submission 1104557842](https://leetcode.com/submissions/detail/1104557842/) · tests 316/316 · runtime 1057 ms (beats 12.8%)

```python
class Solution:
    def threeSumSmaller(self, nums: List[int], target: int) -> int:
        nums.sort()
        n = len(nums) - 1
        print(nums)
        count=0
        for i in range(len(nums)-2):
            # print(i)
            left = i+1
            right = n
            
            while left < right:
                # print(left, right)
                total = nums[i] + nums[left] + nums[right]

                if total< target:
                    # print(i, left, right)
                    count += right-left
                    left +=1
                else:
                    right -=1
        return count
```
