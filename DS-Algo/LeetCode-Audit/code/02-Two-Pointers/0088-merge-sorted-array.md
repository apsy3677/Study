# 88. Merge Sorted Array

[Problem](https://leetcode.com/problems/merge-sorted-array/) · Easy · Two Pointers → Merge from the end

LeetCode tags: array, two-pointers, sorting

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-11-16 00:39 IST · Accepted · Python

[submission 1099580916](https://leetcode.com/submissions/detail/1099580916/) · tests 59/59 · runtime 19 ms (beats 3.1%)

```python
class Solution(object):
    def merge(self, nums1, m, nums2, n):
        """
        :type nums1: List[int]
        :type m: int
        :type nums2: List[int]
        :type n: int
        :rtype: None Do not return anything, modify nums1 in-place instead.
        """
        p1 = m-1
        p2 = n-1
        p = m+n-1

        while p2 >=0:
            if p1>=0 and nums1[p1] > nums2[p2]:
                nums1[p] = nums1[p1]
                p-=1
                p1-=1
            else:
                nums1[p] = nums2[p2] 
                p-=1
                p2-=1
```

## Attempt 2 · 2023-11-24 03:41 IST · Accepted · Python3

[submission 1105108540](https://leetcode.com/submissions/detail/1105108540/) · tests 59/59 · runtime 58 ms (beats 1.8%)

```python
class Solution:
    def merge(self, nums1: List[int], m: int, nums2: List[int], n: int) -> None:
        """
        Do not return anything, modify nums1 in-place instead.
        """
        p1 = m -1
        p2 = n- 1
        p = len(nums1)-1
        while p2>=0:
            print(p1,p2,p,nums1)
            if p1>=0 and nums1[p1] > nums2[p2]:
                nums1[p] = nums1[p1]
                p1-=1
                p-=1
            else:
                nums1[p] = nums2[p2]
                p2-=1
                p-=1
```

## Attempt 3 · 2023-12-05 04:33 IST · Accepted · Python3

[submission 1112489517](https://leetcode.com/submissions/detail/1112489517/) · tests 59/59 · runtime 56 ms (beats 1.8%)

```python
class Solution:
    def merge(self, nums1: List[int], m: int, nums2: List[int], n: int) -> None:
        """
        Do not return anything, modify nums1 in-place instead.
        """
        p1 = m -1
        p2 = n- 1
        p = len(nums1)-1

        # merge all small list numbers
        while p2>=0:
            print(p1,p2,p,nums1)

            # if large list still has numbers and number is bigger
            if p1>=0 and nums1[p1] > nums2[p2]:
                nums1[p] = nums1[p1]
                p1-=1
                p-=1
            # copy from smaller list
            else:
                nums1[p] = nums2[p2]
                p2-=1
                p-=1
```
