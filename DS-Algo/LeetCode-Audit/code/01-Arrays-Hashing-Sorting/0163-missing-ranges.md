# 163. Missing Ranges

[Problem](https://leetcode.com/problems/missing-ranges/) · Easy · Arrays, Hashing & Sorting → Gap scan

LeetCode tags: array

Attempts since Mar 2023: 8 · accepted: 5 · failed before first AC: 2

## Attempt 1 · 2024-01-27 01:27 IST · Wrong Answer · Python3

[submission 1157722737](https://leetcode.com/submissions/detail/1157722737/) · tests 32/39

Failing input:

```text
[]
1
1
```

Expected:

```text
[[1,1]]
```

Your output:

```text
[]
```

```python
class Solution:
    def findMissingRanges(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        output = []
        prev = lower +1
        for i in range(len(nums)):
            if nums[i] - prev >1:
                output.append([prev , nums[i]-1])

            prev = nums[i] 

        output.append([prev +1 , upper])
        print(output)
        return output

    def findMissingRanges(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        prev = lower - 1
        result = []
        for num in nums:
            if num - prev > 1:
                result.append([prev+1, num-1])

            prev = num

        if upper - prev > 1:
            result.append([prev+1, upper])
        return result
```

## Attempt 2 · 2024-01-27 01:28 IST · Wrong Answer · Python3

[submission 1157723377](https://leetcode.com/submissions/detail/1157723377/) · tests 33/39

Failing input:

```text
[-1]
-1
0
```

Expected:

```text
[[0,0]]
```

Your output:

```text
[]
```

```python
class Solution:
    def findMissingRanges(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        output = []
        prev = lower +1
        for i in range(len(nums)):
            if nums[i] - prev >1:
                output.append([prev , nums[i]-1])

            prev = nums[i] 

        output.append([prev +1 , upper])
        print(output)
        return output

    def findMissingRanges(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        if not nums:
            return [[lower, upper]]
        prev = lower - 1
        result = []
        for num in nums:
            if num - prev > 1:
                result.append([prev+1, num-1])

            prev = num

        if upper - prev > 1:
            result.append([prev+1, upper])
        return result
```

## Attempt 3 · 2024-01-27 01:30 IST · Accepted · Python3

[submission 1157724802](https://leetcode.com/submissions/detail/1157724802/) · tests 39/39 · runtime 26 ms (beats 0%)

```python
class Solution:
    def findMissingRanges(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        output = []
        prev = lower +1
        for i in range(len(nums)):
            if nums[i] - prev >1:
                output.append([prev , nums[i]-1])

            prev = nums[i] 

        output.append([prev +1 , upper])
        print(output)
        return output

    def findMissingRanges(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        if not nums:
            return [[lower, upper]]
        prev = lower - 1
        result = []
        for num in nums:
            if num - prev > 1:
                print('here', num)
                result.append([prev+1, num-1])

            prev = num
        
        if upper - prev >= 1:
            print('last', num)
            result.append([prev+1, upper])
        return result
```

## Attempt 4 · 2024-01-27 01:32 IST · Accepted · Python3

[submission 1157725597](https://leetcode.com/submissions/detail/1157725597/) · tests 39/39 · runtime 34 ms (beats 0%)

```python
class Solution:
    def findMissingRanges(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        output = []
        prev = lower +1
        for i in range(len(nums)):
            if nums[i] - prev >1:
                output.append([prev , nums[i]-1])

            prev = nums[i] 

        output.append([prev +1 , upper])
        print(output)
        return output

    def findMissingRanges(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        # empty list
        if not nums:
            return [[lower, upper]]

        prev = lower - 1
        result = []

        # for each num, get prev and calculate
        for num in nums:
            if num - prev > 1:
                print('here', num)
                result.append([prev+1, num-1])

            prev = num
        
        # upper range inclusive
        if upper - prev >= 1: # inclusive range 
            print('last', num)
            result.append([prev+1, upper])
        return result
```

## Attempt 5 · 2024-02-05 07:41 IST · Wrong Answer · Python3

[submission 1166355998](https://leetcode.com/submissions/detail/1166355998/) · tests 32/39

Failing input:

```text
[]
1
1
```

Expected:

```text
[[1,1]]
```

Your output:

```text
[]
```

```python
class Solution:
    def findMissingRanges(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        output = []
        prev = lower +1
        for i in range(len(nums)):
            if nums[i] - prev >1:
                output.append([prev , nums[i]-1])

            prev = nums[i] 

        output.append([prev +1 , upper])
        print(output)
        return output

    def findMissingRanges(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        # empty list
        if not nums:
            return [[lower, upper]]

        prev = lower - 1
        result = []

        # for each num, get prev and calculate
        for num in nums:
            if num - prev > 1:
                print('here', num)
                result.append([prev+1, num-1])

            prev = num
        
        # upper range inclusive
        if upper - prev >= 1: # inclusive range 
            print('last', num)
            result.append([prev+1, upper])
        return result

    def findMissingRanges(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        last = lower -1
        result = []
        for num in nums:
            if num - last > 1:
                result.append([last+1, num-1])
            last = num
        if upper-last >1:
            result.append([last+1, upper])
        return result
```

## Attempt 6 · 2024-02-05 07:43 IST · Accepted · Python3

[submission 1166357219](https://leetcode.com/submissions/detail/1166357219/) · tests 39/39 · runtime 35 ms (beats 0%)

```python
class Solution:
    def findMissingRanges(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        output = []
        prev = lower +1
        for i in range(len(nums)):
            if nums[i] - prev >1:
                output.append([prev , nums[i]-1])

            prev = nums[i] 

        output.append([prev +1 , upper])
        print(output)
        return output

    def findMissingRanges3(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        # empty list
        if not nums:
            return [[lower, upper]]

        prev = lower - 1
        result = []

        # for each num, get prev and calculate
        for num in nums:
            if num - prev > 1:
                print('here', num)
                result.append([prev+1, num-1])

            prev = num
        
        # upper range inclusive
        if upper - prev >= 1: # inclusive range 
            print('last', num)
            result.append([prev+1, upper])
        return result

    def findMissingRanges(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        last = lower -1
        result = []
        for num in nums:
            if num - last > 1:
                result.append([last+1, num-1])
                print(result)
            last = num
        if upper-last >=1:
            result.append([last+1, upper])
        print(result)
        return result
```

## Attempt 7 · 2024-02-05 07:43 IST · Accepted · Python3

[submission 1166357276](https://leetcode.com/submissions/detail/1166357276/) · tests 39/39 · runtime 30 ms (beats 0%)

```python
class Solution:
    def findMissingRanges(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        output = []
        prev = lower +1
        for i in range(len(nums)):
            if nums[i] - prev >1:
                output.append([prev , nums[i]-1])

            prev = nums[i] 

        output.append([prev +1 , upper])
        print(output)
        return output

    def findMissingRanges3(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        # empty list
        if not nums:
            return [[lower, upper]]

        prev = lower - 1
        result = []

        # for each num, get prev and calculate
        for num in nums:
            if num - prev > 1:
                print('here', num)
                result.append([prev+1, num-1])

            prev = num
        
        # upper range inclusive
        if upper - prev >= 1: # inclusive range 
            print('last', num)
            result.append([prev+1, upper])
        return result

    def findMissingRanges(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        last = lower -1
        result = []
        for num in nums:
            if num - last > 1:
                result.append([last+1, num-1])
                # print(result)
            last = num
        if upper-last >=1:
            result.append([last+1, upper])
        # print(result)
        return result
```

## Attempt 8 · 2024-02-10 23:46 IST · Accepted · Python3

[submission 1171631028](https://leetcode.com/submissions/detail/1171631028/) · tests 39/39 · runtime 33 ms (beats 0%)

```python
class Solution:
    def findMissingRanges(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        output = []
        prev = lower +1
        for i in range(len(nums)):
            if nums[i] - prev >1:
                output.append([prev , nums[i]-1])

            prev = nums[i] 

        output.append([prev +1 , upper])
        print(output)
        return output

    def findMissingRanges3(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        # empty list
        if not nums:
            return [[lower, upper]]

        prev = lower - 1
        result = []

        # for each num, get prev and calculate
        for num in nums:
            if num - prev > 1:
                print('here', num)
                result.append([prev+1, num-1])

            prev = num
        
        # upper range inclusive
        if upper - prev >= 1: # inclusive range 
            print('last', num)
            result.append([prev+1, upper])
        return result

    def findMissingRanges(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        last = lower -1
        result = []
        for num in nums:
            # missing before num excluding num
            if num - last > 1:
                # if num - last <=3:
                #     for i in range(1,num-last):
                #         result.append([last+i])
                # else:
                result.append([last+1, num-1])
            last = num
            
        # missing upto upper- including upper
        if upper-last >=1:
            result.append([last+1, upper])
        return result

    def findMissingRanges(self, nums: List[int], lower: int, upper: int) -> List[List[int]]:
        # find missing in between (last, curr) and (last, upper]
        last = lower -1
        result = []
        for i in range(len(nums)):
            if nums[i] - last > 1:
                result.append([last+1, nums[i]-1]) 
            last = nums[i]
        
        if upper - last >= 1:
            result.append([last+1, upper])

        return result
```
