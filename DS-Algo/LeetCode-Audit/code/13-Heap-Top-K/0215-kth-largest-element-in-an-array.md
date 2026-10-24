# 215. Kth Largest Element in an Array

[Problem](https://leetcode.com/problems/kth-largest-element-in-an-array/) · Medium · Heap / Top-K → Quickselect / heap

LeetCode tags: array, divide-and-conquer, sorting, heap-priority-queue, quickselect

Attempts since Mar 2023: 6 · accepted: 2 · failed before first AC: 1

## Attempt 1 · 2023-11-20 20:11 IST · Time Limit Exceeded · Python3

[submission 1102762670](https://leetcode.com/submissions/detail/1102762670/) · tests 0/41

Failing input:

```text
[3,2,1,5,6,4]
2
```

Expected:

```text
5
```

```python
class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        heap = []
        # if you insert in heap and pop out elements, it will have k largest
        for num in nums:
            heapq.heappush(nums, num)
            if len(heap) >k:
                heapq.heappop(heap)

        return heap[0]
```

## Attempt 2 · 2023-11-20 20:12 IST · Accepted · Python3

[submission 1102763129](https://leetcode.com/submissions/detail/1102763129/) · tests 41/41 · runtime 571 ms (beats 5.0%)

```python
class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        heap = []
        # if you insert in heap and pop out elements, it will have k largest
        for num in nums:
            heapq.heappush(heap, num)
            if len(heap) >k:
                heapq.heappop(heap)

        return heap[0]
```

## Attempt 3 · 2023-12-01 07:15 IST · Time Limit Exceeded · Python3

[submission 1109901339](https://leetcode.com/submissions/detail/1109901339/) · tests 40/41

Failing input:

```text
[1,2,3,4,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 ... [199612 more chars]
```

Expected:

```text
1
```

```python
class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        def quick_select(nums, k):
            pivot = random.choice(nums)
            left, mid, right = [],[],[]

            for num in nums:
                if num > pivot:
                    left.append(num)
                elif num < pivot:
                    right.append(num)
                else:
                    mid.append(num)

            print(left, mid, right,k)
            if k <= len(left):
                return quick_select(left, k)
            
            if len(left) + len(mid) < k:
                return quick_select(right, k-len(left)-len(mid))

            return pivot

        return quick_select(nums,k)

    def findKthLargest(self, nums: List[int], k: int) -> int:

        def partition(left, right, pivot_index):
            pivot = nums[pivot_index]

            # move to right
            nums[right], nums[pivot_index] = nums[pivot_index], nums[right]

            store_index = left
            for i in range(left, right):
                if nums[i] < pivot:
                    nums[i], nums[store_index] = nums[store_index], nums[i]
                    store_index+=1
            nums[right], nums[store_index] = nums[store_index], nums[right]

            return store_index

        def quickselect(left,right, k):
            if left == right:
                return 0

            pivot_index = random.randint(left, right)
            pivot_index = partition(left, right ,pivot_index)

            if pivot_index == k:
                return 
            elif k < pivot_index :
                quickselect(left, pivot_index-1, k)
            else:
                quickselect(pivot_index+1, right, k)

        quickselect(0, len(nums)-1, len(nums)-k)
        return nums[len(nums)-k]
```

## Attempt 4 · 2023-12-04 11:40 IST · Time Limit Exceeded · Python3

[submission 1111960771](https://leetcode.com/submissions/detail/1111960771/) · tests 40/41

Failing input:

```text
[1,2,3,4,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 ... [199612 more chars]
```

Expected:

```text
1
```

```python
class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:

        '''
        approach 1 : min-heap 
        you need min heap, so taht you can discard all n-k smallest elements using pop and then keep largest k
        push and the if it becomes len()> k: pop
        return 0 the 
        time n times log k operation
        space - k

        approach 2: quickselect

        '''
        def quick_select(nums, k):
            pivot = random.choice(nums)
            left, mid, right = [],[],[]

            for num in nums:
                if num > pivot:
                    left.append(num)
                elif num < pivot:
                    right.append(num)
                else:
                    mid.append(num)

            print(left, mid, right,k)
            if k <= len(left):
                return quick_select(left, k)
            
            if len(left) + len(mid) < k:
                return quick_select(right, k-len(left)-len(mid))

            return pivot

        return quick_select(nums,k)

    def findKthLargest(self, nums: List[int], k: int) -> int:

        def partition(left, right, pivot_index):
            # get pivot value
            pivot = nums[pivot_index]

            # move to right
            nums[right], nums[pivot_index] = nums[pivot_index], nums[right]


            # find correct place of pivot 
            # update store_index by moving i element to left if small
            store_index = left
            for i in range(left, right):
                if nums[i] < pivot:
                    nums[i], nums[store_index] = nums[store_index], nums[i]
                    store_index+=1

            # swap right pivot with store index
            nums[right], nums[store_index] = nums[store_index], nums[right]

            # return store_index
            return store_index

        def quickselect(left,right, k):

            # baase condition
            if left == right:
                return 0


            # select random pivot between left and right and patition
            pivot_index = random.randint(left, right)
            pivot_index = partition(left, right ,pivot_index)

            if pivot_index == k:
                return 
            elif k < pivot_index :
                quickselect(left, pivot_index-1, k)
            else:
                quickselect(pivot_index+1, right, k)

        # kth largest is n-kth smallest
        quickselect(0, len(nums)-1, len(nums)-k)
        return nums[len(nums)-k]
```

## Attempt 5 · 2023-12-04 11:43 IST · Time Limit Exceeded · Python3

[submission 1111962412](https://leetcode.com/submissions/detail/1111962412/) · tests 40/41

Failing input:

```text
[1,2,3,4,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 ... [199612 more chars]
```

Expected:

```text
1
```

```python
class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:

        '''
        approach 1 : min-heap 
        you need min heap, so taht you can discard all n-k smallest elements using pop and then keep largest k
        push and the if it becomes len()> k: pop
        return 0 the 
        time n times log k operation
        space - k

        approach 2: quickselect
        worst case - when rand is selected as either min or max value and parition is not balanced it doesn't divide problem in approx half

        the work done inside the partition is o(n)
        if paritions are worse outer quickselect will be called n times leading to O(n^2)

        space- recursion stack

        '''
        def quick_select(nums, k):
            pivot = random.choice(nums)
            left, mid, right = [],[],[]

            for num in nums:
                if num > pivot:
                    left.append(num)
                elif num < pivot:
                    right.append(num)
                else:
                    mid.append(num)

            print(left, mid, right,k)
            if k <= len(left):
                return quick_select(left, k)
            
            if len(left) + len(mid) < k:
                return quick_select(right, k-len(left)-len(mid))

            return pivot

        return quick_select(nums,k)

    def findKthLargest(self, nums: List[int], k: int) -> int:

        def partition(left, right, pivot_index):
            # get pivot value
            pivot = nums[pivot_index]

            # move to right
            nums[right], nums[pivot_index] = nums[pivot_index], nums[right]


            # find correct place of pivot 
            # update store_index by moving i element to left if small
            store_index = left
            for i in range(left, right):
                if nums[i] < pivot:
                    nums[i], nums[store_index] = nums[store_index], nums[i]
                    store_index+=1

            # swap right pivot with store index
            nums[right], nums[store_index] = nums[store_index], nums[right]

            # return store_index
            return store_index

        def quickselect(left,right, k):

            # baase condition
            if left == right:
                return 0


            # select random pivot between left and right and patition
            pivot_index = random.randint(left, right)
            pivot_index = partition(left, right ,pivot_index)

            if pivot_index == k:
                return 
            elif k < pivot_index :
                quickselect(left, pivot_index-1, k)
            else:
                quickselect(pivot_index+1, right, k)

        # kth largest is n-kth smallest
        quickselect(0, len(nums)-1, len(nums)-k)
        return nums[len(nums)-k]
```

## Attempt 6 · 2024-08-19 06:36 IST · Accepted · Java

[submission 1360851507](https://leetcode.com/submissions/detail/1360851507/) · tests 41/41 · runtime 58 ms (beats 64.0%)

```java
class Solution {
    private static final class PQComparator implements Comparator<Integer> {
        public int compare(Integer a , Integer b) {
            if (a < b) {
                return 1;
            } 
            if (a > b) {
                return -1;
            }
            return 0;
        }
    }


    public int findKthLargest(int[] nums, int k) {
        PriorityQueue<Integer> pq = new PriorityQueue(new PQComparator());
        for (int i = 0; i < nums.length; i++) {
            pq.add(nums[i]);
        }

        // Iterator it = pq.iterator();
        // while (it.hasNext()) {
        //     System.out.print(it.next() + " ");
        // }

        while (k-- > 1) {
            pq.poll();
        }
        return pq.peek();
    }
}
```
