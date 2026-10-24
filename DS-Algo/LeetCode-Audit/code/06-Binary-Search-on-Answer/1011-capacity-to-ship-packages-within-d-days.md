# 1011. Capacity To Ship Packages Within D Days

[Problem](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/) · Medium · Binary Search on Answer → Minimise capacity

LeetCode tags: array, binary-search

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-11-20 01:23 IST · Accepted · Python3

[submission 1102276611](https://leetcode.com/submissions/detail/1102276611/) · tests 87/87 · runtime 450 ms (beats 5.7%)

```python
class Solution:
    def shipWithinDays(self, weights: List[int], days: int) -> int:
        def isFeasible(weights, capacity, days):
            daysNeeded = 1 
            currentLoad = 0
            for weight in weights:
                currentLoad+=weight
                if currentLoad > capacity:
                    daysNeeded+=1
                    currentLoad = weight

            return daysNeeded <=days

        totalLoad = sum(weights)
        maxLoad = max(weights)
        
        l = maxLoad
        r = totalLoad

        while (l<r):
            mid = (l+r)//2
            if (isFeasible(weights, mid, days)):
                r = mid
            else:
                l = mid+1
        
        
        return l
```

## Attempt 2 · 2023-11-27 20:08 IST · Accepted · Python3

[submission 1107477954](https://leetcode.com/submissions/detail/1107477954/) · tests 87/87 · runtime 480 ms (beats 5.0%)

```python
class Solution:
    def shipWithinDays(self, weights: List[int], days: int) -> int:
        #1. search space
        left, right = max(weights), sum(weights)
        
        # 2. condition
        def canShip(capacity):
            load = 0
            daysNeeded=1
            for weight in weights:
                load +=weight
                if load > capacity:
                    daysNeeded+=1
                    load = weight
            return daysNeeded <= days

        while left < right:
            mid = (left + right)//2

            if canShip(mid):
                right = mid 
            else:
                left = mid +1
        return left
```
