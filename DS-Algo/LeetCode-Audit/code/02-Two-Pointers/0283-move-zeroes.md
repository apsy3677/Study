# 283. Move Zeroes

[Problem](https://leetcode.com/problems/move-zeroes/) · Easy · Two Pointers → Read/write pointers

LeetCode tags: array, two-pointers

Attempts since Mar 2023: 13 · accepted: 10 · failed before first AC: 0

## Attempt 1 · 2023-08-24 22:30 IST · Accepted · C++

[submission 1030683227](https://leetcode.com/submissions/detail/1030683227/) · tests 74/74 · runtime 18 ms (beats 7.1%)

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int i=0, j=0, k, n=nums.size();
        while(j<n) {
            if(isNonZero(nums[j])) {
                k=nums[i];
                nums[i] = nums[j];
                nums[j]=k;
                i++;
            }
            j++;    
        }
    }

    bool isNonZero(int num) {
        return num != 0;
    }
};
```

## Attempt 2 · 2023-08-24 22:31 IST · Accepted · C++

[submission 1030684594](https://leetcode.com/submissions/detail/1030684594/) · tests 74/74 · runtime 20 ms (beats 7.0%)

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int i=0, j=0, k, n=nums.size();
        while(j<n) {
            if(isNonZero(nums[j])) {
                k=nums[i];
                nums[i] = nums[j];
                nums[j]=k;
                i++;
            }
            j++;    
        }
    }

    bool isNonZero(int num) {
        return num != 0;
    }
};
```

## Attempt 3 · 2023-11-14 20:47 IST · Accepted · Python3

[submission 1098725717](https://leetcode.com/submissions/detail/1098725717/) · tests 74/74 · runtime 147 ms (beats 9.2%)

```python
class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        left = 0
        for right in range(len(nums)):
            if nums[right]!=0:
                nums[left], nums[right] = nums[right], nums[left]
                left +=1
```

## Attempt 4 · 2023-11-14 20:59 IST · Accepted · Python3

[submission 1098732870](https://leetcode.com/submissions/detail/1098732870/) · tests 74/74 · runtime 148 ms (beats 9.2%)

```python
class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        lastNonZeroFoundAt = 0
        for idx in range(len(nums)):
            if (nums[idx] != 0):
                nums[lastNonZeroFoundAt] = nums[idx]
                lastNonZeroFoundAt +=1
        print(nums)
        for idx in range(lastNonZeroFoundAt, len(nums)):
            nums[idx] = 0
```

## Attempt 5 · 2023-11-15 23:43 IST · Accepted · Python

[submission 1099547386](https://leetcode.com/submissions/detail/1099547386/) · tests 74/74 · runtime 122 ms (beats 10.2%)

```python
class Solution(object):
    def moveZeroes(self, nums):
        """
        :type nums: List[int]
        :rtype: None Do not return anything, modify nums in-place instead.
        """
        l = -1
        r = 0

        while r < len(nums):
            if nums[r]!=0:
                l+=1
                nums[l], nums[r] = nums[r], nums[l]

            r+=1
        return nums
```

## Attempt 6 · 2023-11-15 23:44 IST · Accepted · Python

[submission 1099548511](https://leetcode.com/submissions/detail/1099548511/) · tests 74/74 · runtime 124 ms (beats 10.2%)

```python
class Solution(object):
    def moveZeroes(self, nums):
        """
        :type nums: List[int]
        :rtype: None Do not return anything, modify nums in-place instead.
        """
        l = 0 
        r = 0

        while r<len(nums):
            if nums[r]!=0:
                nums[l], nums[r] = nums[r], nums[l]
                l+=1
            r+=1
```

## Attempt 7 · 2023-11-21 21:56 IST · Accepted · Python3

[submission 1103569067](https://leetcode.com/submissions/detail/1103569067/) · tests 74/74 · runtime 139 ms (beats 9.2%)

```python
class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        idx = 0

        for i in range(len(nums)):
            if nums[i] !=0:
                nums[idx], nums[i] = nums[i], nums[idx]
                idx+=1

        return nums
```

## Attempt 8 · 2023-11-21 21:57 IST · Wrong Answer · Python3

[submission 1103569587](https://leetcode.com/submissions/detail/1103569587/) · tests 24/74

Failing input:

```text
[2,1]
```

Expected:

```text
[2,1]
```

Your output:

```text
[1,2]
```

```python
class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        idx = 0

        for i in range(1,len(nums)):
            if nums[i] !=0:
                nums[idx], nums[i] = nums[i], nums[idx]
                idx+=1

        return nums
```

## Attempt 9 · 2023-12-03 03:20 IST · Accepted · Python3

[submission 1111081946](https://leetcode.com/submissions/detail/1111081946/) · tests 74/74 · runtime 141 ms (beats 9.2%)

```python
class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        idx = 0

        for i in range(len(nums)):
            if nums[i] !=0:
                nums[idx], nums[i] = nums[i], nums[idx]
                idx+=1

        return nums
```

## Attempt 10 · 2023-12-03 03:20 IST · Wrong Answer · Python3

[submission 1111082004](https://leetcode.com/submissions/detail/1111082004/) · tests 24/74

Failing input:

```text
[2,1]
```

Expected:

```text
[2,1]
```

Your output:

```text
[1,2]
```

```python
class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        idx = 0

        for i in range(1,len(nums)):
            if nums[i] !=0:
                nums[idx], nums[i] = nums[i], nums[idx]
                idx+=1

        return nums
```

## Attempt 11 · 2023-12-03 03:23 IST · Wrong Answer · Python3

[submission 1111083414](https://leetcode.com/submissions/detail/1111083414/) · tests 24/74

Failing input:

```text
[2,1]
```

Expected:

```text
[2,1]
```

Your output:

```text
[1,2]
```

```python
class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        idx = 0

        for i in range(1,len(nums)):
            if nums[i] !=0:
                if idx!=i:
                    nums[idx], nums[i] = nums[i], nums[idx]
                idx+=1

        return nums
```

## Attempt 12 · 2023-12-03 03:24 IST · Accepted · Python3

[submission 1111083586](https://leetcode.com/submissions/detail/1111083586/) · tests 74/74 · runtime 134 ms (beats 9.2%)

```python
class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        idx = 0

        for i in range(0,len(nums)):
            if nums[i] !=0:
                if idx!=i:
                    nums[idx], nums[i] = nums[i], nums[idx]
                idx+=1

        return nums
```

## Attempt 13 · 2023-12-05 02:37 IST · Accepted · Python3

[submission 1112443699](https://leetcode.com/submissions/detail/1112443699/) · tests 74/74 · runtime 146 ms (beats 9.2%)

```python
class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.

        idx points to the location where nonzero number should be copied
        """
        idx = 0

        for i in range(0,len(nums)):
            if nums[i] !=0:
                if idx!=i:
                    nums[idx], nums[i] = nums[i], nums[idx]
                idx+=1

        return nums
```
