# 347. Top K Frequent Elements

[Problem](https://leetcode.com/problems/top-k-frequent-elements/) · Medium · Heap / Top-K → Top-K / bucket sort

LeetCode tags: array, hash-table, divide-and-conquer, sorting, heap-priority-queue, bucket-sort, counting, quickselect

Attempts since Mar 2023: 9 · accepted: 4 · failed before first AC: 4

## Attempt 1 · 2023-11-19 09:02 IST · Wrong Answer · Python3

[submission 1101830813](https://leetcode.com/submissions/detail/1101830813/) · tests 8/21

Failing input:

```text
[3,0,1,0]
1
```

Expected:

```text
[0]
```

Your output:

```text
[1]
```

```python
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        count = Counter(nums)

        heap = []

        for num in count.keys():
            if len(heap) >k:
                heapq.heappop(heap)
            
            heapq.heappush(heap, (-count[num], num))

        return [num for _, num in heap[:k]]
```

## Attempt 2 · 2023-11-19 09:03 IST · Wrong Answer · Python3

[submission 1101831528](https://leetcode.com/submissions/detail/1101831528/) · tests 8/21

Failing input:

```text
[3,0,1,0]
1
```

Expected:

```text
[0]
```

Your output:

```text
[1]
```

```python
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        count = Counter(nums)

        heap = []

        for num in count.keys():
            if len(heap) >k:
                heapq.heappop(heap)
            
            heapq.heappush(heap, (-count[num], num))
        print(heap)
        return [num for _, num in heap[:k]]
```

## Attempt 3 · 2023-11-19 09:03 IST · Wrong Answer · Python3

[submission 1101831932](https://leetcode.com/submissions/detail/1101831932/) · tests 8/21

Failing input:

```text
[3,0,1,0]
1
```

Expected:

```text
[0]
```

Your output:

```text
[1]
```

```python
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        count = Counter(nums)

        heap = []
        print(count)
        for num in count.keys():
            if len(heap) >k:
                heapq.heappop(heap)
            
            heapq.heappush(heap, (-count[num], num))
        print(heap)
        return [num for _, num in heap[:k]]
```

## Attempt 4 · 2023-11-19 09:09 IST · Wrong Answer · Python3

[submission 1101836944](https://leetcode.com/submissions/detail/1101836944/) · tests 5/21

Failing input:

```text
[1,1,1,2,2,3]
2
```

Expected:

```text
[1,2]
```

Your output:

```text
[2,3]
```

```python
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        count = Counter(nums)

        heap = []
        print(count)
        for num in count.keys():
            heapq.heappush(heap, (-count[num], num))
            if len(heap) >k:
                heapq.heappop(heap)
            
            
        print(heap)
        return [num for _, num in heap[:k]]
```

## Attempt 5 · 2023-11-19 09:09 IST · Accepted · Python3

[submission 1101837215](https://leetcode.com/submissions/detail/1101837215/) · tests 21/21 · runtime 103 ms (beats 5.0%)

```python
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        count = Counter(nums)

        heap = []
        print(count)
        for num in count.keys():
            heapq.heappush(heap, (count[num], num))
            if len(heap) >k:
                heapq.heappop(heap)
            
            
        print(heap)
        return [num for _, num in heap[:k]]
```

## Attempt 6 · 2023-11-19 19:46 IST · Accepted · Python3

[submission 1102113628](https://leetcode.com/submissions/detail/1102113628/) · tests 21/21 · runtime 96 ms (beats 5.0%)

```python
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        count = Counter(nums)

        heap = []
        for num in count.keys():
            heapq.heappush(heap, (count[num], num))
            if len(heap) >k:
                heapq.heappop(heap)
            
        return [num for _, num in heap]

    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        count = Counter(nums)
        unique = list(count.keys())

        def partition(left, right,pivot_index):
            pivot_frequency = count[unique[pivot_index]]

            #1. move pivot element to the right
            unique[pivot_index] , unique[right] = unique[right], unique[pivot_index]

            #2. move smaller elements to the left using a store_index
            # store_index will keep track of small elements
            store_index = left 
            for i in range(left, right):
                if count[unique[i]] < pivot_frequency:
                    unique[store_index], unique[i] = unique[i], unique[store_index]
                    store_index +=1

            # 3. move pivot to correct position
            unique[right], unique[store_index] = unique[store_index], unique[right]

            return store_index




        def quickselect(left, right, k_smallest):
            # 1. base condition
            if left == right:
                return 

            # 2. select a pivot index 
            pivot_index = random.randint(left, right)
            
            #  3. place pivot in the right position
            pivot_index = partition(left, right, pivot_index)

            # 4. make decision
            if k_smallest == pivot_index:
                return 
            elif k_smallest < pivot_index:
                quickselect(left, pivot_index -1, k_smallest)
            else:
                quickselect(pivot_index+1, right, k_smallest)

            
        n = len(unique)

        #quickselect will work from less frequent in the strat to the more frequent at the end
        # nth largest is n-k smallest 
        quickselect(0,n-1,n-k)

        return unique[n-k:]
```

## Attempt 7 · 2024-01-15 07:04 IST · Accepted · Python3

[submission 1146450475](https://leetcode.com/submissions/detail/1146450475/) · tests 21/21 · runtime 78 ms (beats 5.0%)

```python
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        count = Counter(nums)

        heap = []
        for num in count.keys():
            heapq.heappush(heap, (count[num], num))
            if len(heap) >k:
                heapq.heappop(heap)
            
        return [num for _, num in heap]



    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        count = Counter(nums)
        unique = list(count.keys())

        def partition(left, right,pivot_index):
            pivot_frequency = count[unique[pivot_index]]

            #1. move pivot element to the right
            unique[pivot_index] , unique[right] = unique[right], unique[pivot_index]

            #2. move smaller elements to the left using a store_index
            # store_index will keep track of small elements
            store_index = left 
            for i in range(left, right):
                if count[unique[i]] < pivot_frequency:
                    unique[store_index], unique[i] = unique[i], unique[store_index]
                    store_index +=1

            # 3. move pivot to correct position
            unique[right], unique[store_index] = unique[store_index], unique[right]

            return store_index




        def quickselect(left, right, k_smallest):
            # 1. base condition
            if left == right:
                return 

            # 2. select a pivot index 
            pivot_index = random.randint(left, right)
            
            #  3. place pivot in the right position
            pivot_index = partition(left, right, pivot_index)

            # 4. make decision
            if k_smallest == pivot_index:
                return 
            elif k_smallest < pivot_index:
                quickselect(left, pivot_index -1, k_smallest)
            else:
                quickselect(pivot_index+1, right, k_smallest)

            
        n = len(unique)

        #quickselect will work from less frequent in the strat to the more frequent at the end
        # nth largest is n-k smallest 
        quickselect(0,n-1,n-k)

        return unique[n-k:]

    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        nums_counter = Counter(nums)
        max_heap = []
        i=0
        for num, count in nums_counter.items():
            heapq.heappush(max_heap, (count, num))
            if i>=k:
                heapq.heappop(max_heap)
            i+=1

        return [num for _, num in max_heap]
```

## Attempt 8 · 2024-01-15 07:14 IST · Runtime Error · Python3

[submission 1146455215](https://leetcode.com/submissions/detail/1146455215/) · tests 4/21

Failing input:

```text
[3,0,1,0]
1
```

Expected:

```text
[0]
```

Runtime error:

```text
TypeError: Solution.topKFrequent.<locals>.quickselect() missing 1 required positional argument: 'k'
    quickselect(pivot_index+1, k)
Line 99 in quickselect (Solution.py)
    quickselect(0, len(unique_nums)-1, len(unique_nums)-k)
Line 103 in topKFrequent (Solution.py)
          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    ret = Solution().topKFrequent(param_1, param_2)
Line 130 in _driver (Soluti ... [55 more chars]
```

```python
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        count = Counter(nums)

        heap = []
        for num in count.keys():
            heapq.heappush(heap, (count[num], num))
            if len(heap) >k:
                heapq.heappop(heap)
            
        return [num for _, num in heap]



    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        count = Counter(nums)
        unique = list(count.keys())

        def partition(left, right,pivot_index):
            pivot_frequency = count[unique[pivot_index]]

            #1. move pivot element to the right
            unique[pivot_index] , unique[right] = unique[right], unique[pivot_index]

            #2. move smaller elements to the left using a store_index
            # store_index will keep track of small elements
            store_index = left 
            for i in range(left, right):
                if count[unique[i]] < pivot_frequency:
                    unique[store_index], unique[i] = unique[i], unique[store_index]
                    store_index +=1

            # 3. move pivot to correct position
            unique[right], unique[store_index] = unique[store_index], unique[right]

            return store_index




        def quickselect(left, right, k_smallest):
            # 1. base condition
            if left == right:
                return 

            # 2. select a pivot index 
            pivot_index = random.randint(left, right)
            
            #  3. place pivot in the right position
            pivot_index = partition(left, right, pivot_index)

            # 4. make decision
            if k_smallest == pivot_index:
                return 
            elif k_smallest < pivot_index:
                quickselect(left, pivot_index -1, k_smallest)
            else:
                quickselect(pivot_index+1, right, k_smallest)

            
        n = len(unique)

        #quickselect will work from less frequent in the strat to the more frequent at the end
        # nth largest is n-k smallest 
        quickselect(0,n-1,n-k)

        return unique[n-k:]

    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        nums_count = Counter(nums)
        unique_nums = list(nums_count.keys())

        def partition(l,r,pivot_index):
            pivot = nums_count[unique_nums[pivot_index]]
            # move pivot to right
            unique_nums[pivot_index], unique_nums[r] = unique_nums[r], unique_nums[pivot_index]

            # find right position of pivot
            store_index = l
            for i in range(l,r):
                if nums_count[unique_nums[i]] < pivot:
                    unique_nums[i], unique_nums[store_index] = unique_nums[store_index], unique_nums[i]
                    store_index +=1

            unique_nums[r], unique_nums[store_index] = unique_nums[store_index], unique_nums[r]

            return store_index

        def quickselect(l,r,k):
            if l>=r:
                return 
            
            pivot_index = random.randint(l,r)
            pivot_index = partition(l,r,pivot_index)

            if k< pivot_index:
                quickselect(l, pivot_index-1,k)
            elif k > pivot_index:
                quickselect(pivot_index+1, k)
            else:
                return

        quickselect(0, len(unique_nums)-1, len(unique_nums)-k)
        
        return unique_nums[len(unique_nums)-k:]
```

## Attempt 9 · 2024-01-15 07:15 IST · Accepted · Python3

[submission 1146455372](https://leetcode.com/submissions/detail/1146455372/) · tests 21/21 · runtime 81 ms (beats 5.0%)

```python
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        count = Counter(nums)

        heap = []
        for num in count.keys():
            heapq.heappush(heap, (count[num], num))
            if len(heap) >k:
                heapq.heappop(heap)
            
        return [num for _, num in heap]



    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        count = Counter(nums)
        unique = list(count.keys())

        def partition(left, right,pivot_index):
            pivot_frequency = count[unique[pivot_index]]

            #1. move pivot element to the right
            unique[pivot_index] , unique[right] = unique[right], unique[pivot_index]

            #2. move smaller elements to the left using a store_index
            # store_index will keep track of small elements
            store_index = left 
            for i in range(left, right):
                if count[unique[i]] < pivot_frequency:
                    unique[store_index], unique[i] = unique[i], unique[store_index]
                    store_index +=1

            # 3. move pivot to correct position
            unique[right], unique[store_index] = unique[store_index], unique[right]

            return store_index




        def quickselect(left, right, k_smallest):
            # 1. base condition
            if left == right:
                return 

            # 2. select a pivot index 
            pivot_index = random.randint(left, right)
            
            #  3. place pivot in the right position
            pivot_index = partition(left, right, pivot_index)

            # 4. make decision
            if k_smallest == pivot_index:
                return 
            elif k_smallest < pivot_index:
                quickselect(left, pivot_index -1, k_smallest)
            else:
                quickselect(pivot_index+1, right, k_smallest)

            
        n = len(unique)

        #quickselect will work from less frequent in the strat to the more frequent at the end
        # nth largest is n-k smallest 
        quickselect(0,n-1,n-k)

        return unique[n-k:]

    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        nums_count = Counter(nums)
        unique_nums = list(nums_count.keys())

        def partition(l,r,pivot_index):
            pivot = nums_count[unique_nums[pivot_index]]
            # move pivot to right
            unique_nums[pivot_index], unique_nums[r] = unique_nums[r], unique_nums[pivot_index]

            # find right position of pivot
            store_index = l
            for i in range(l,r):
                if nums_count[unique_nums[i]] < pivot:
                    unique_nums[i], unique_nums[store_index] = unique_nums[store_index], unique_nums[i]
                    store_index +=1

            unique_nums[r], unique_nums[store_index] = unique_nums[store_index], unique_nums[r]

            return store_index

        def quickselect(l,r,k):
            if l>=r:
                return 
            
            pivot_index = random.randint(l,r)
            pivot_index = partition(l,r,pivot_index)

            if k< pivot_index:
                quickselect(l, pivot_index-1,k)
            elif k > pivot_index:
                quickselect(pivot_index+1,r, k)
            else:
                return

        quickselect(0, len(unique_nums)-1, len(unique_nums)-k)
        
        return unique_nums[len(unique_nums)-k:]
```
