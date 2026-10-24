# 986. Interval List Intersections

[Problem](https://leetcode.com/problems/interval-list-intersections/) · Medium · Intervals & Sweep Line → Two-pointer intersection

LeetCode tags: array, two-pointers, sweep-line

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-11-16 20:28 IST · Accepted · Python

[submission 1100140524](https://leetcode.com/submissions/detail/1100140524/) · tests 85/85 · runtime 100 ms (beats 5.6%)

```python
class Solution(object):
    def intervalIntersection(self, firstList, secondList):
        """
        :type firstList: List[List[int]]
        :type secondList: List[List[int]]
        :rtype: List[List[int]]
        """
        
        p1 = p2 = 0

        intersections = []
        while p1< len(firstList) and p2 < len(secondList):
            start = max(firstList[p1][0], secondList[p2][0])
            end = min(firstList[p1][1], secondList[p2][1])

            if start <= end:
                intersections.append([start, end])
            
            if firstList[p1][1] < secondList[p2][1]:
                p1+=1
            else:
                p2+=1
        
        return intersections
```

## Attempt 2 · 2023-11-28 04:12 IST · Accepted · Python3

[submission 1107749175](https://leetcode.com/submissions/detail/1107749175/) · tests 85/85 · runtime 138 ms (beats 6.1%)

```python
class Solution:
    def intervalIntersection(self, firstList: List[List[int]], secondList: List[List[int]]) -> List[List[int]]:
        p1 = p2 = 0
        intersections = []
        while p1 <len(firstList) and p2 < len(secondList):
            first_start, first_end = firstList[p1]
            second_start, second_end = secondList[p2]

            # if overlap
            if first_start<=second_end and second_start <=first_end:

                lo = max(first_start, second_start)
                hi = min(first_end, second_end)
                intersections.append([lo,hi])

            if first_end < second_end:
                p1+=1
            else:
                p2+=1

        return intersections
```

## Attempt 3 · 2024-02-10 02:17 IST · Accepted · Python3

[submission 1170940559](https://leetcode.com/submissions/detail/1170940559/) · tests 85/85 · runtime 126 ms (beats 6.1%)

```python
class Solution:
    def intervalIntersection(self, firstList: List[List[int]], secondList: List[List[int]]) -> List[List[int]]:
        p1 = p2 = 0
        intersections = []

        # for same length
        while p1 <len(firstList) and p2 < len(secondList):
            first_start, first_end = firstList[p1]
            second_start, second_end = secondList[p2]

            lo = max(first_start, second_start)
            hi = min(first_end, second_end)

            # first_start and second end and vice or lo<=hi
            if lo <= hi:
                # find lo max and hi min as intersection
                
                intersections.append([lo,hi])

            # first could be smaller or second
            if first_end < second_end:
                p1+=1
            else:
                p2+=1

        return intersections

    def intervalIntersection7(self, firstList: List[List[int]], secondList: List[List[int]]) -> List[List[int]]:
        intersections = []
        p2= p1=0
        while p1 < len(firstList) and p2< len(secondList):
            if firstList[p1] <= secondList[p2]:
                start, end = firstList[p1][0], firstList[p1][1]
                p1+=1
            else:
                start, end = secondList[p2][0], secondList[p2][1]
                p2+=1
            
            if union and start <=union[-1][1]:
                union[-1][1] = max()
```
