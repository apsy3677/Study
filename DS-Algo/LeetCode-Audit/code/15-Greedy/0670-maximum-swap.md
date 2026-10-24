# 670. Maximum Swap

[Problem](https://leetcode.com/problems/maximum-swap/) · Medium · Greedy → Last occurrence

LeetCode tags: math, greedy

Attempts since Mar 2023: 8 · accepted: 3 · failed before first AC: 3

## Attempt 1 · 2023-11-16 06:08 IST · Wrong Answer · Python

[submission 1099721690](https://leetcode.com/submissions/detail/1099721690/) · tests 105/112

Failing input:

```text
98368
```

Expected:

```text
98863
```

Your output:

```text
38968
```

```python
class Solution(object):
    def maximumSwap(self, num):
        """
        :type num: int
        :rtype: int
        """
        nums = [int(l) for l in list(str(num))]
        maxIndex = len(nums) - 1
        smallIndex = 0
        for i in range(len(nums)-1, -1,-1):
            if nums[maxIndex] < nums[i]:
                maxIndex = i
            elif  nums[i] < nums[maxIndex]:
                smallIndex = i
        nums[maxIndex], nums[smallIndex] = nums[smallIndex], nums[maxIndex]
        print(maxIndex,smallIndex)
        return int(''.join([str(l) for l in nums]))
```

## Attempt 2 · 2023-11-23 03:33 IST · Wrong Answer · Python3

[submission 1104468055](https://leetcode.com/submissions/detail/1104468055/) · tests 87/112

Failing input:

```text
1993
```

Expected:

```text
9913
```

Your output:

```text
9193
```

```python
class Solution:
    def maximumSwap(self, num: int) -> int:
        # find max index and if you find a number lower than max to the left, replace

        num = list(str(num))
        maxIndex = len(num) -1
        
        i = len(num)-1
        x,y = 0,0
        while i >=0:
            if num[i] >= num[maxIndex]:
                maxIndex = i
            else:
                x = i
                y = maxIndex
            i-=1
        num[x], num[y] = num[y], num[x]

        return int(''.join(num))
```

## Attempt 3 · 2023-11-23 03:34 IST · Wrong Answer · Python3

[submission 1104468418](https://leetcode.com/submissions/detail/1104468418/) · tests 102/112

Failing input:

```text
98368
```

Expected:

```text
98863
```

Your output:

```text
98368
```

```python
class Solution:
    def maximumSwap(self, num: int) -> int:
        # find max index and if you find a number lower than max to the left, replace

        num = list(str(num))
        maxIndex = len(num) -1
        
        i = len(num)-1
        x,y = 0,0
        while i >=0:
            if num[i] > num[maxIndex]:
                maxIndex = i
            else:
                x = i
                y = maxIndex
            i-=1
        num[x], num[y] = num[y], num[x]

        return int(''.join(num))
```

## Attempt 4 · 2023-11-23 03:36 IST · Accepted · Python3

[submission 1104469286](https://leetcode.com/submissions/detail/1104469286/) · tests 112/112 · runtime 40 ms (beats 0%)

```python
class Solution:
    def maximumSwap(self, num: int) -> int:
        # find max index and if you find a number lower than max to the left, replace

        num = list(str(num))
        maxIndex = len(num) -1
        
        i = len(num)-1
        x,y = 0,0
        while i >=0:
            if num[i] > num[maxIndex]:
                maxIndex = i
            elif num[i] < num[maxIndex]:
                x = i
                y = maxIndex
            i-=1
        num[x], num[y] = num[y], num[x]

        return int(''.join(num))
```

## Attempt 5 · 2023-11-23 03:38 IST · Wrong Answer · Python3

[submission 1104470021](https://leetcode.com/submissions/detail/1104470021/) · tests 87/112

Failing input:

```text
1993
```

Expected:

```text
9913
```

Your output:

```text
9193
```

```python
class Solution:
    def maximumSwap(self, num: int) -> int:
        # find max index and if you find a number lower than max to the left, replace

        num = list(str(num))
        maxIndex = len(num) -1
        
        i = len(num)-1
        x,y = 0,0
        while i >=0:
            if num[i] >= num[maxIndex]:
                maxIndex = i
            #if num[i] < num[maxIndex]:
            else:
                x = i
                y = maxIndex
            i-=1
        num[x], num[y] = num[y], num[x]

        return int(''.join(num))
```

## Attempt 6 · 2023-11-23 03:39 IST · Wrong Answer · Python3

[submission 1104470630](https://leetcode.com/submissions/detail/1104470630/)

_Code not returned by LeetCode._

## Attempt 7 · 2023-12-31 01:24 IST · Accepted · Python3

[submission 1132457069](https://leetcode.com/submissions/detail/1132457069/) · tests 112/112 · runtime 46 ms (beats 0%)

```python
class Solution:
    def maximumSwap(self, num: int) -> int:
        # find max index and if you find a number lower than max to the left, replace

        '''
        to find the maximum value, we should swap smallest on the most significan digits to maximum on the least significant digits

        I can only get large number if I replace max value from right with smaller value to its left.
        if I replace with smaller value to its right - it will be smaller number

        find maxIndex but only swap if you find smaller element on its left 
        
        what will happen with equal digits - you go on and don't replace 
        goal is to replace least significant maximum digit with most significant smallest digit
        '''
        num = list(str(num))
        maxIndex = len(num) -1
        
        i = len(num)-1
        index_to_swap, swap_index = 0,0
        while i >=0:
            # go on looking even if num[i] == num[maxIndex]
            # we want to keep least significat digit
            if num[i] > num[maxIndex]:
                maxIndex = i
            #if num[i] < num[maxIndex]:
            else:
                index_to_swap = i
                swap_index = maxIndex
            i-=1
        num[index_to_swap], num[swap_index] = num[swap_index], num[index_to_swap]

        return int(''.join(num))
        
    def maximumSwap(self, num: int) -> int:
        
        num = list(str(num))
        i = len(num)- 1
        index_to_swap = 0
        swap_with_index = 0 
        max_index = len(num) -1 
        while i>=0:
            if num[i] > num[max_index]:
                max_index = i
            elif num[i] < num[max_index]:
                index_to_swap = max_index
                swap_with_index = i 
            i-=1
        
        num[index_to_swap], num[swap_with_index] = num[swap_with_index] , num[index_to_swap]

        return int(''.join(num))
```

## Attempt 8 · 2024-02-03 02:46 IST · Accepted · Python3

[submission 1164268995](https://leetcode.com/submissions/detail/1164268995/) · tests 112/112 · runtime 33 ms (beats 0%)

```python
class Solution:
    def maximumSwap(self, num: int) -> int:
        # find max index and if you find a number lower than max to the left, replace

        '''
        to find the maximum value, we should swap smallest on the most significan digits to maximum on the least significant digits

        I can only get large number if I replace max value from right with smaller value to its left.
        if I replace with smaller value to its right - it will be smaller number

        find maxIndex but only swap if you find smaller element on its left 
        
        what will happen with equal digits - you go on and don't replace 
        goal is to replace least significant maximum digit with most significant smallest digit
        '''
        num = list(str(num))
        maxIndex = len(num) -1
        
        i = len(num)-1
        index_to_swap, swap_index = 0,0
        while i >=0:
            # go on looking even if num[i] == num[maxIndex]
            # we want to keep least significat digit
            if num[i] > num[maxIndex]:
                maxIndex = i
            #if num[i] < num[maxIndex]:
            else:
                index_to_swap = i
                swap_index = maxIndex
            i-=1
        num[index_to_swap], num[swap_index] = num[swap_index], num[index_to_swap]

        return int(''.join(num))
        
    def maximumSwap(self, num: int) -> int:
        
        num = list(str(num))
        i = len(num)- 1
        index_to_swap = 0
        swap_with_index = 0 
        max_index = len(num) -1 
        while i>=0:
            if num[i] > num[max_index]:
                max_index = i
            elif num[i] < num[max_index]:
                index_to_swap = max_index
                swap_with_index = i 
            i-=1
            
        num[index_to_swap], num[swap_with_index] = num[swap_with_index] , num[index_to_swap]

        return int(''.join(num))

    def maximumSwap(self, num: int) -> int:
        num = list(str(num))
        index = len(num) -1
        index_to_swap = len(num) -1  # max index 
        swap_with_index = len(num) - 1 # smaller digit to left
        max_index = len(num) - 1
        
        while index >=0:
            if num[index] > num[max_index]:
                max_index = index
            elif num[index] < num[max_index]:
                index_to_swap = max_index
                swap_with_index = index
            index -=1

        num[index_to_swap], num[swap_with_index] = num[swap_with_index], num[index_to_swap]
        return int(''.join(num))
```
