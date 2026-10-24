# 398. Random Pick Index

[Problem](https://leetcode.com/problems/random-pick-index/) · Medium · Math & Bit Manipulation → Reservoir sampling

LeetCode tags: hash-table, math, reservoir-sampling, randomized

Attempts since Mar 2023: 6 · accepted: 0 · failed before first AC: 6

## Attempt 1 · 2023-11-25 04:46 IST · Runtime Error · Python3

[submission 1105733373](https://leetcode.com/submissions/detail/1105733373/) · tests 0/15

Failing input:

```text
["Solution","pick","pick","pick"]
[[[1,2,3,3,3]],[3],[1],[3]]
```

Expected:

```text
[null,4,0,2]
```

Runtime error:

```text
NameError: name 'nums' is not defined. Did you mean: 'num'?
    for i,num in enumerate(nums):
Line 11 in pick (Solution.py)
    result = obj.pick(
Line 27 in __helper_select_method__ (Solution.py)
    ret.append(__DriverSolution__().__helper_select_method__(method, params[index], obj))
Line 65 in _driver (Solution.py)
    _driver()
Line 74 in <module> (Solution.py)
```

```python
class Solution:

    def __init__(self, nums: List[int]):
        self.nums = nums

    def pick(self, target: int) -> int:
        count = sum(1 for num in self.nums if num ==target)

        selected = random.randint(1, count)

        for i,num in enumerate(nums):
            if num ==target:
                selected -=1
                


# Your Solution object will be instantiated and called as such:
# obj = Solution(nums)
# param_1 = obj.pick(target)
```

## Attempt 2 · 2023-11-25 04:47 IST · Time Limit Exceeded · Python3

[submission 1105733520](https://leetcode.com/submissions/detail/1105733520/) · tests 14/15

Failing input:

```text
["Solution","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pi ... [149644 more chars]
```

Expected:

```text
[null,12470,13346,11552,17500,8225,16379,16037,11447,14322,682,17303,151,9304,10760,10370,5209,596,1629,2453,13056,925,10289,4984,2054,7454,3841,3450,2647,8405,2956,4278,12962,14439,5605,4320,9345,5916,2528,15815,6095,8529,17750,8308,396,12305,18300,16671,16929,10618,13380,9645,3510,8061,1168,13027,3451,1343,19097,19692,1901,17321,11616,3278,744,16778,6715,5019,15571,87,15892,13300,3048,18123,5820 ... [54026 more chars]
```

```python
class Solution:

    def __init__(self, nums: List[int]):
        self.nums = nums

    def pick(self, target: int) -> int:
        count = sum(1 for num in self.nums if num ==target)

        selected = random.randint(1, count)

        for i,num in enumerate(self.nums):
            if num ==target:
                selected -=1
                if selected ==0:
                    return i



# Your Solution object will be instantiated and called as such:
# obj = Solution(nums)
# param_1 = obj.pick(target)
```

## Attempt 3 · 2023-12-05 03:45 IST · Time Limit Exceeded · Python3

[submission 1112471660](https://leetcode.com/submissions/detail/1112471660/) · tests 14/15

Failing input:

```text
["Solution","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pi ... [149644 more chars]
```

Expected:

```text
[null,12470,13346,11552,17500,8225,16379,16037,11447,14322,682,17303,151,9304,10760,10370,5209,596,1629,2453,13056,925,10289,4984,2054,7454,3841,3450,2647,8405,2956,4278,12962,14439,5605,4320,9345,5916,2528,15815,6095,8529,17750,8308,396,12305,18300,16671,16929,10618,13380,9645,3510,8061,1168,13027,3451,1343,19097,19692,1901,17321,11616,3278,744,16778,6715,5019,15571,87,15892,13300,3048,18123,5820 ... [54026 more chars]
```

```python
class Solution:
    '''
    find indexes with target value and select from one of them
    or generate random number and then pick 
    or use reservoir sampling that is for data stream, it gives equal probablity to all target values to overwrite its index with equal probablity
    when you have seen single target value - 100 chance of choosing this index
    when you seen next traget - 50% change it gets to overwrite choosen index
    when you seen next - 33% change
    '''
    def __init__(self, nums: List[int]):
        self.nums = nums

    def pick(self, target: int) -> int:
        count = sum(1 for num in self.nums if num ==target)

        selected = random.randint(1, count)

        for i,num in enumerate(self.nums):
            if num ==target:
                selected -=1
                if selected ==0:
                    return i



# Your Solution object will be instantiated and called as such:
# obj = Solution(nums)
# param_1 = obj.pick(target)
```

## Attempt 4 · 2024-01-02 01:21 IST · Runtime Error · Python3

[submission 1134027278](https://leetcode.com/submissions/detail/1134027278/) · tests 0/15

Failing input:

```text
["Solution","pick","pick","pick"]
[[[1,2,3,3,3]],[3],[1],[3]]
```

Expected:

```text
[null,4,0,2]
```

Runtime error:

```text
TypeError: None is not valid value for the expected return type integer
    raise TypeError(str(result) + " is not valid value for the expected return type integer")
Line 54 in __helper_select_method__ (Solution.py)
               ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    ret.append(__DriverSolution__().__helper_select_method__(method, params[index], obj))
Line  ... [489 more chars]
```

```python
class Solution1:
    '''
    find indexes with target value and select from one of them
    or generate random number and then pick 
    or use reservoir sampling that is for data stream, it gives equal probablity to all target values to overwrite its index with equal probablity
    when you have seen single target value - 100 chance of choosing this index
    when you seen next traget - 50% change it gets to overwrite choosen index
    when you seen next - 33% change

    each target value gets 
    if random.randint(1, count) == count: overwrite this index
    '''
    def __init__(self, nums: List[int]):
        self.nums = nums

    def pick(self, target: int) -> int:
        count = sum(1 for num in self.nums if num ==target)

        selected = random.randint(1, count)

        for i,num in enumerate(self.nums):
            if num ==target:
                selected -=1
                if selected ==0:
                    return i

class Solution:
    def __init__(self, nums: List[int]):
        self.nums = nums

    def pick(self, target: int) -> int:
        count = 0
        chosen_index = None
        for i in range(len(self.nums)):
            count += self.nums[i] == target
            if self.nums[i] == target and random.randint(0,count) ==0:
                chosen_index =  i
        return chosen_index 
# Your Solution object will be instantiated and called as such:
# obj = Solution(nums)
# param_1 = obj.pick(target)
```

## Attempt 5 · 2024-01-02 01:22 IST · Time Limit Exceeded · Python3

[submission 1134027560](https://leetcode.com/submissions/detail/1134027560/) · tests 14/15

Failing input:

```text
["Solution","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pi ... [149644 more chars]
```

Expected:

```text
[null,12470,13346,11552,17500,8225,16379,16037,11447,14322,682,17303,151,9304,10760,10370,5209,596,1629,2453,13056,925,10289,4984,2054,7454,3841,3450,2647,8405,2956,4278,12962,14439,5605,4320,9345,5916,2528,15815,6095,8529,17750,8308,396,12305,18300,16671,16929,10618,13380,9645,3510,8061,1168,13027,3451,1343,19097,19692,1901,17321,11616,3278,744,16778,6715,5019,15571,87,15892,13300,3048,18123,5820 ... [54026 more chars]
```

```python
class Solution1:
    '''
    find indexes with target value and select from one of them
    or generate random number and then pick 
    or use reservoir sampling that is for data stream, it gives equal probablity to all target values to overwrite its index with equal probablity
    when you have seen single target value - 100 chance of choosing this index
    when you seen next traget - 50% change it gets to overwrite choosen index
    when you seen next - 33% change

    each target value gets 
    if random.randint(1, count) == count: overwrite this index
    '''
    def __init__(self, nums: List[int]):
        self.nums = nums

    def pick(self, target: int) -> int:
        count = sum(1 for num in self.nums if num ==target)

        selected = random.randint(1, count)

        for i,num in enumerate(self.nums):
            if num ==target:
                selected -=1
                if selected ==0:
                    return i

class Solution:
    def __init__(self, nums: List[int]):
        self.nums = nums

    def pick(self, target: int) -> int:
        count = 0
        chosen_index = None
        for i in range(len(self.nums)):
            count += self.nums[i] == target
            if self.nums[i] == target and random.randint(0,count-1) ==0:
                chosen_index =  i
        return chosen_index 
# Your Solution object will be instantiated and called as such:
# obj = Solution(nums)
# param_1 = obj.pick(target)
```

## Attempt 6 · 2024-01-02 01:23 IST · Time Limit Exceeded · Python3

[submission 1134027921](https://leetcode.com/submissions/detail/1134027921/) · tests 14/15

Failing input:

```text
["Solution","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pick","pi ... [149644 more chars]
```

Expected:

```text
[null,12470,13346,11552,17500,8225,16379,16037,11447,14322,682,17303,151,9304,10760,10370,5209,596,1629,2453,13056,925,10289,4984,2054,7454,3841,3450,2647,8405,2956,4278,12962,14439,5605,4320,9345,5916,2528,15815,6095,8529,17750,8308,396,12305,18300,16671,16929,10618,13380,9645,3510,8061,1168,13027,3451,1343,19097,19692,1901,17321,11616,3278,744,16778,6715,5019,15571,87,15892,13300,3048,18123,5820 ... [54026 more chars]
```

```python
class Solution1:
    '''
    find indexes with target value and select from one of them
    or generate random number and then pick 
    or use reservoir sampling that is for data stream, it gives equal probablity to all target values to overwrite its index with equal probablity
    when you have seen single target value - 100 chance of choosing this index
    when you seen next traget - 50% change it gets to overwrite choosen index
    when you seen next - 33% change

    each target value gets 
    if random.randint(1, count) == count: overwrite this index
    '''
    def __init__(self, nums: List[int]):
        self.nums = nums

    def pick(self, target: int) -> int:
        count = sum(1 for num in self.nums if num ==target)

        selected = random.randint(1, count)

        for i,num in enumerate(self.nums):
            if num ==target:
                selected -=1
                if selected ==0:
                    return i

class Solution:
    def __init__(self, nums: List[int]):
        self.nums = nums

    def pick(self, target: int) -> int:
        count = 0
        chosen_index = None

        for i, num in enumerate(self.nums):
            if num == target:
                count += 1
                # Generate a random number between 0 and count - 1 (inclusive)
                if random.randint(0, count - 1) == 0:
                    chosen_index = i

        return chosen_index
```
