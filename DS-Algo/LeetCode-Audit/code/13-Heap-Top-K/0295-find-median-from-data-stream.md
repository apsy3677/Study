# 295. Find Median from Data Stream

[Problem](https://leetcode.com/problems/find-median-from-data-stream/) · Hard · Heap / Top-K → Two heaps

LeetCode tags: two-pointers, design, sorting, heap-priority-queue, data-stream

Attempts since Mar 2023: 4 · accepted: 4 · failed before first AC: 0

## Attempt 1 · 2023-11-30 05:41 IST · Accepted · Python3

[submission 1109215964](https://leetcode.com/submissions/detail/1109215964/) · tests 21/21 · runtime 2290 ms (beats 5.0%)

```python
class MedianFinder:

    def __init__(self):
        self.nums =[]

    def addNum(self, num: int) -> None:
        self.nums.append(num)

    def findMedian(self) -> float:
        self.nums.sort()
        n = len(self.nums)

        if n & 1:
            return self.nums[n//2]
        else:
            return 0.5* (self.nums[n//2 -1] + self.nums[n//2])


# Your MedianFinder object will be instantiated and called as such:
# obj = MedianFinder()
# obj.addNum(num)
# param_2 = obj.findMedian()
```

## Attempt 2 · 2023-11-30 06:30 IST · Accepted · Python3

[submission 1109232253](https://leetcode.com/submissions/detail/1109232253/) · tests 21/21 · runtime 415 ms (beats 11.8%)

```python
class MedianFinder:

    def __init__(self):
        self.lo = []
        self.hi = []

    def addNum(self, num: int) -> None:
        if not self.lo or num < -self.lo[0]:
            heapq.heappush(self.lo, -num)
        else:
            heapq.heappush(self.hi, num)

        # rebalance 
        # low has extra element
        # since high has 1 less, check by adding 1 on high 
        # high+1 shoul be atmost same as lo
        if len(self.lo) > len(self.hi) + 1:
            heapq.heappush(self.hi, -heapq.heappop(self.lo))
        if len(self.hi) > len(self.lo):
            heapq.heappush(self.lo, -heapq.heappop(self.hi))

        #print(self.lo, self.hi)





    def findMedian(self) -> float:
        if len(self.lo) == len(self.hi):
            return (-self.lo[0] + self.hi[0])*0.5
        else:
            return -self.lo[0]

        if n & 1:
            return self.nums[n//2]
        else:
            return 0.5* (self.nums[n//2 -1] + self.nums[n//2])


# Your MedianFinder object will be instantiated and called as such:
# obj = MedianFinder()
# obj.addNum(num)
# param_2 = obj.findMedian()
```

## Attempt 3 · 2024-02-11 08:00 IST · Accepted · Python3

[submission 1171865915](https://leetcode.com/submissions/detail/1171865915/) · tests 21/21 · runtime 929 ms (beats 10.4%)

```python
class MedianFinder:

    def __init__(self):
        self.nums = []
        self.count = 0

    def addNum(self, num: int) -> None:
        bisect.insort(self.nums, num)
        self.count +=1
        

    def findMedian(self) -> float:
        if self.count  & 1:
            return self.nums[self.count//2]
        else:
            return (self.nums[self.count//2] + self.nums[self.count//2 - 1] )* 0.5


# Your MedianFinder object will be instantiated and called as such:
# obj = MedianFinder()
# obj.addNum(num)
# param_2 = obj.findMedian()
```

## Attempt 4 · 2024-02-11 08:06 IST · Accepted · Python3

[submission 1171872574](https://leetcode.com/submissions/detail/1171872574/) · tests 21/21 · runtime 1044 ms (beats 8.7%)

```python
class MedianFinder:

    def __init__(self):
        self.nums = []
        self.count = 0

    def _binary_search(self, nums, target):
        l = 0 
        r = len(nums)

        while l <r:
            mid = (l+r)//2
            if target> nums[mid]:
                l = mid +1
            else:
                 r = mid
        
        return l

    def addNum(self, num: int) -> None:
        l = self._binary_search(self.nums, num)
        # print(self.nums, num, l)
        self.nums.insert(l, num)
        # bisect.insort(self.nums, num)
        self.count +=1
        

    def findMedian(self) -> float:
        if self.count  & 1:
            return self.nums[self.count//2]
        else:
            return (self.nums[self.count//2] + self.nums[self.count//2 - 1] )* 0.5


# Your MedianFinder object will be instantiated and called as such:
# obj = MedianFinder()
# obj.addNum(num)
# param_2 = obj.findMedian()
```
