# 480. Sliding Window Median

[Problem](https://leetcode.com/problems/sliding-window-median/) · Hard · Heap / Top-K → Two heaps with lazy delete

LeetCode tags: array, hash-table, sliding-window, heap-priority-queue, treap

Attempts since Mar 2023: 4 · accepted: 3 · failed before first AC: 1

## Attempt 1 · 2023-11-18 00:52 IST · Wrong Answer · Python3

[submission 1100992387](https://leetcode.com/submissions/detail/1100992387/) · tests 21/43

Failing input:

```text
[1,4,2,3]
4
```

Expected:

```text
[2.50000]
```

Your output:

```text
[4.00000]
```

```python
class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        window = []
        medians = []
        for i in range(len(nums)):
            if i >=k:
                window.pop(bisect.bisect(window, nums[i-k]) -1)

            bisect.insort(window, nums[i])

            if i >= k-1:
                if k & 1:
                    median = window[len(window)//2]
                else: 
                    median = window[(len(window)//2 - 1 ) + len(window)//2]
                medians.append(median)
        return medians
```

## Attempt 2 · 2023-11-18 00:54 IST · Accepted · Python3

[submission 1100993055](https://leetcode.com/submissions/detail/1100993055/) · tests 43/43 · runtime 729 ms (beats 6.1%)

```python
class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        window = []
        medians = []
        for i in range(len(nums)):
            if i >=k:
                window.pop(bisect.bisect(window, nums[i-k]) -1)

            bisect.insort(window, nums[i])

            if i >= k-1:
                if k & 1:
                    median = window[k//2]
                else: 
                    median = (window[(k//2 - 1 )] + window[k//2])*0.5
                medians.append(median)
        return medians
```

## Attempt 3 · 2023-11-30 07:34 IST · Accepted · Python3

[submission 1109253947](https://leetcode.com/submissions/detail/1109253947/) · tests 43/43 · runtime 2529 ms (beats 5.0%)

```python
class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        window = []
        medians = []
        for i in range(len(nums)):
            if i>=k:
                #O(k)
                window.remove(nums[i-k])
            
            bisect.insort(window, nums[i])

            if i>=k-1:
                #print(window)
                if not k&1:
                    medians.append((window[k//2 - 1] + window[k//2])*0.5)
                else:
                    medians.append(window[k//2])

        return medians
```

## Attempt 4 · 2024-01-26 09:58 IST · Accepted · Python3

[submission 1157053663](https://leetcode.com/submissions/detail/1157053663/) · tests 43/43 · runtime 701 ms (beats 6.1%)

```python
class Solution:
    def __init__(self):
        # Min heap for the larger half of the numbers
        self.minHeap = []
        # Max heap for the smaller half of the numbers
        self.maxHeap = []
        # Dictionary to keep track of elements to be delayed removed
        self.delayed = {}

    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        '''
        approach 0 - everytime sort the window using klogk sort method 
        making time complexity nklogk

        approach 1 - iterate over all elements and once you have a window of size k or reach index k-1 start collecting medians
        we need to do sorting to identify the median 
        add - what we can do is for each new element put it in the correct place in the window 
        remove out of window element - after k-1, remove element from window using .remove() from list

        time complexity: O(nk) - k for remove and k for insort
        space - O(k) - window size
        
        approach 2 - use two heaps - min half and max half and balance it to always keep median elements at the top of two halfs 
        keep one heap always +1  
        '''
        window = []
        medians = []

        # O(n)
        for i in range(len(nums)):
            if i>=k:
                #remove from window of size k - O(k)
                window.remove[nums[i-k]]
            
            # O(k) - where log k for search and k for insertion
            bisect.insort(window, nums[i])

            if i>=k-1:
                if k&1:
                    medians.append((nums[k//2 - 1] + nums[k//2])*0.5)
                else:
                    medians.append(nums[k//2])

        
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        lo = []  # max heap
        hi = []  # min heap
        delayed_removal = Counter()

        def rebalance():
            # keep lo with max one extra
            # so if you have odd elements in the window, you pick the median from lo
            # else average of lo and hi
            # hi - 1 and lo - 2 allowed
            # hi - 1 and lo - 3 not allowed
            if len(lo) > len(hi) + 1:
                # lo has more elements
                heapq.heappush(hi, -heapq.heappop(lo))
            # if both are equal that's okay
            elif len(hi) > len(lo):
                heapq.heappush(lo, -heapq.heappop(hi))

        def remove(heap, element):
            delayed_removal[element] += 1

        result = []
        for i in range(len(nums)):
            # add
            # if it falls in lo heap or is the first element
            if not lo or nums[i] <= -lo[0]:
                heapq.heappush(lo, -nums[i])
            else:
                heapq.heappush(hi, nums[i])

            # finding the median
            if i >= k - 1:
                if len(lo) == len(hi):
                    result.append((-lo[0] + hi[0]) * 0.5)
                else:
                    result.append(-lo[0])

                # delayed removal
                # removing elements at the current window
                element_to_remove = nums[i - k + 1]
                remove(lo, element_to_remove)
                remove(hi, element_to_remove)

                rebalance()

                # Remove elements marked for delayed removal
                while lo and delayed_removal[-lo[0]] > 0:
                    delayed_removal[-lo[0]] -= 1
                    heapq.heappop(lo)
                while hi and delayed_removal[hi[0]] > 0:
                    delayed_removal[hi[0]] -= 1
                    heapq.heappop(hi)

        return result

    def medianSlidingWindow3(self, nums: List[int], k: int) -> List[float]:
        window = []
        medians = []
        def insert(window, num):
            l = 0
            r = len(window) -1

            while l<=r:
                mid = (l+r) //2
                if num <= window[mid]:
                    r = mid - 1
                else:
                    l = mid + 1
            
            print(window,l, num)
            window.insert(l, num)

            
        for i in range(len(nums)):
            if i >=k:
                # remove from window
                outgoing = bisect_left(window, nums[i - k])
                window.pop(outgoing)

            # insert new num
            insert(window, nums[i])
            if i>=k-1:
                if k &1:
                    medians.append(window[k//2])
                else:
                    medians.append((window[k//2 - 1] + window[k//2])*0.5)
        return medians

    def medianSlidingWindow4(self, nums: List[int], k: int) -> List[float]:
        window = []
        medians=[]
        for i in range(len(nums)):
            
            if i>=k:
                # remove from window
                # window.remove(nums[i-k])
                window.pop(bisect.bisect(window, nums[i-k]) - 1)

            # insert number at right position
            bisect.insort(window, nums[i])

            if i >=k-1:
                if k &1:
                    medians.append(window[k//2])
                else:
                    medians.append(0.5*(window[k//2] + window[k//2 -1]))
        return medians

    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        window =[]
        medians = []

        for i in range(len(nums)):
            if i>=k: # mistake 3 forgot i>=k 
                window.pop(bisect.bisect(window, nums[i-k]) - 1)

            bisect.insort(window, nums[i]) # mistake 2 - bisect.insort

            if i>=k-1:
                if k &1:
                    medians.append(window[k//2])
                else:
                    medians.append(0.5* (window[k//2] + window[k//2 - 1])) # mistake 1 forgot k//2 -1
        return medians
```
