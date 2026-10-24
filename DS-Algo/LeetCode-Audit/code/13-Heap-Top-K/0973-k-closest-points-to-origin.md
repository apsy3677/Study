# 973. K Closest Points to Origin

[Problem](https://leetcode.com/problems/k-closest-points-to-origin/) · Medium · Heap / Top-K → Size-k max-heap

LeetCode tags: array, math, divide-and-conquer, geometry, sorting, heap-priority-queue, quickselect, k-d-tree

Attempts since Mar 2023: 25 · accepted: 7 · failed before first AC: 0

## Attempt 1 · 2023-11-13 03:04 IST · Accepted · Python3

[submission 1097473741](https://leetcode.com/submissions/detail/1097473741/) · tests 87/87 · runtime 694 ms (beats 5.0%)

```python
class Solution:
    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        heap = []

        for point in points:
            distance = -(point[0]**2 + point[1]**2)
            heapq.heappush(heap, (distance, point))
            if len(heap) > k:
                heapq.heappop(heap)
        return [point for (_,point) in heap]
```

## Attempt 2 · 2023-11-13 03:53 IST · Runtime Error · Python3

[submission 1097493384](https://leetcode.com/submissions/detail/1097493384/) · tests 0/87

Failing input:

```text
[[1,3],[-2,2]]
1
```

Expected:

```text
[[-2,2]]
```

Runtime error:

```text
SyntaxError: expected ':'
                   ^
    def partition()
Line 5  (Solution.py)
```

```python
class Solution:
    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        def partition()
        def quickselect(left, right, k):
            if left >= right:
                return
            
            pivot_index = random.randint(left, right)
            
            # move pivot to right
            points[right], points[pivot_index] =  points[right], points[pivot_index]

            pivot_index = parition(left, right)

            if pivot_index == k:
                return
            elif k < pivot_index:
                quickselect(left, pivot_index-1, k)
            else:
                quickselect(pivot_index+1, right, k)
```

## Attempt 3 · 2023-11-22 09:15 IST · Accepted · Python3

[submission 1103898500](https://leetcode.com/submissions/detail/1103898500/) · tests 87/87 · runtime 714 ms (beats 5.0%)

```python
class Solution:
    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        heap = []

        for i, point in enumerate(points):
            heapq.heappush(heap,(-dist(i), point))
            if i>=k:
                heapq.heappop(heap)
        
        return [point for _, point in heap]
```

## Attempt 4 · 2023-11-22 09:49 IST · Wrong Answer · Python3

[submission 1103914155](https://leetcode.com/submissions/detail/1103914155/) · tests 33/87

Failing input:

```text
[[3,2],[7,7],[9,-9],[4,-6],[-3,-6]]
4
```

Expected:

```text
[[3,2],[-3,-6],[4,-6],[7,7]]
```

Your output:

```text
[[3,2],[-3,-6],[4,-6],[9,-9]]
```

```python
class Solution:
    def kClosest1(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        heap = []

        for i, point in enumerate(points):
            heapq.heappush(heap,(-dist(i), point))
            if i>=k:
                heapq.heappop(heap)
        
        return [point for _, point in heap]

    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2
        
        def partition(l,r):
            pivot_index = random.randint(l,r)
            pivot = dist(pivot_index)

            points[pivot_index], points[r] = points[r], points[pivot_index]
            i = l
            for j in range(l,r):
                if dist(j) < pivot:
                    points[i], points[j] = points[j], points[i]
                    i+=1
            
            points[i], points[r] = points[r], points[i]

            return pivot_index

        def quickselect(l,r,k):
            if l>=r: return
            pivot_index = partition(l,r)
            if pivot_index == k:
                return
            elif k > pivot_index :
                quickselect(pivot_index+1, r, k)
            else:
                quickselect(l, pivot_index-1, k)

        quickselect(0, len(points)-1, k-1)
        return points[:k]
```

## Attempt 5 · 2023-11-22 09:53 IST · Wrong Answer · Python3

[submission 1103915863](https://leetcode.com/submissions/detail/1103915863/) · tests 28/87

Failing input:

```text
[[-2,10],[-4,-8],[10,7],[-4,-7]]
3
```

Expected:

```text
[[-4,-7],[-4,-8],[-2,10]]
```

Your output:

```text
[[-4,-7],[-4,-8],[10,7]]
```

```python
class Solution:
    def kClosest1(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        heap = []

        for i, point in enumerate(points):
            heapq.heappush(heap,(-dist(i), point))
            if i>=k:
                heapq.heappop(heap)
        
        return [point for _, point in heap]

    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2
        
        def partition(l,r):
            pivot_index = random.randint(l,r)
            pivot = dist(pivot_index)

            points[pivot_index], points[r] = points[r], points[pivot_index]
            i = l
            for j in range(l,r):
                if dist(j) < pivot:
                    points[i], points[j] = points[j], points[i]
                    i+=1
            
            points[i], points[r] = points[r], points[i]

            return pivot_index

        def quickselect(l,r,k):
            if l>=r: return
            pivot_index = partition(l,r)
            print(points)
            if pivot_index == k:
                return
            elif k > pivot_index :
                quickselect(pivot_index+1, r, k)
            else:
                quickselect(l, pivot_index-1, k)

        quickselect(0, len(points)-1, k-1)
        return points[:k]
```

## Attempt 6 · 2023-11-22 09:53 IST · Wrong Answer · Python3

[submission 1103916168](https://leetcode.com/submissions/detail/1103916168/) · tests 31/87

Failing input:

```text
[[-2,10],[-4,-8],[10,7],[-4,-7]]
3
```

Expected:

```text
[[-4,-7],[-4,-8],[-2,10]]
```

Your output:

```text
[[-4,-7],[-4,-8],[10,7]]
```

```python
class Solution:
    def kClosest1(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        heap = []

        for i, point in enumerate(points):
            heapq.heappush(heap,(-dist(i), point))
            if i>=k:
                heapq.heappop(heap)
        
        return [point for _, point in heap]

    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2
        
        def partition(l,r):
            pivot_index = random.randint(l,r)
            pivot = dist(pivot_index)

            points[pivot_index], points[r] = points[r], points[pivot_index]
            i = l
            for j in range(l,r):
                if dist(j) < pivot:
                    points[i], points[j] = points[j], points[i]
                    i+=1
            
            points[i], points[r] = points[r], points[i]

            return pivot_index

        def quickselect(l,r,k):
            if l>=r: return
            pivot_index = partition(l,r)
            print(points)
            if pivot_index == k:
                return
            elif k > pivot_index :
                quickselect(pivot_index+1, r, k)
            else:
                quickselect(l, pivot_index-1, k)

        quickselect(0, len(points)-1, k)
        return points[:k]
```

## Attempt 7 · 2023-11-22 10:00 IST · Output Limit Exceeded · Python3

[submission 1103919192](https://leetcode.com/submissions/detail/1103919192/) · tests 81/87

Failing input:

```text
[[-5121,9946],[6825,6472],[5831,-650],[5516,-3009],[9604,9409],[-3942,1971],[-5436,-9958],[3257,-6805],[-3579,-3659],[3802,-3866],[-1053,-9984],[5539,-2237],[-8804,-5578],[570,-1222],[5706,8177],[-6375,3843],[5222,5140],[7164,-5345],[-1364,-3083],[6827,-6011],[3626,-7881],[-1117,-844],[-7882,3429],[-8601,236],[-5483,-3347],[-7400,6639],[-1931,3701],[-8487,-3188],[-5131,-7115],[-2467,-5645],[-3903, ... [127334 more chars]
```

Expected:

```text
[[46,-196],[131,165],[-225,-28],[-178,-201],[-212,173],[-136,-242],[145,251],[307,-65],[-330,-31],[-144,307],[-337,-156],[-288,-252],[388,58],[-418,-1],[417,-75],[-289,321],[34,-448],[-40,474],[290,385],[65,-507],[479,-199],[75,517],[50,-521],[64,523],[82,524],[-34,-562],[-61,-561],[-356,440],[-521,281],[-381,459],[201,-596],[391,501],[-203,-636],[681,-27],[-262,-647],[-331,619],[9,-703],[-723,-10 ... [78963 more chars]
```

```python
class Solution:
    def kClosest1(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        heap = []

        for i, point in enumerate(points):
            heapq.heappush(heap,(-dist(i), point))
            if i>=k:
                heapq.heappop(heap)
        
        return [point for _, point in heap]

    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2
        
        def partition(l,r):
            pivot_index = random.randint(l,r)
            pivot = dist(pivot_index)

            points[pivot_index], points[r] = points[r], points[pivot_index]
            i = l
            for j in range(l,r):
                if dist(j) < pivot:
                    points[i], points[j] = points[j], points[i]
                    i+=1
            
            points[i], points[r] = points[r], points[i]

            return i

        def quickselect(l,r,k):
            if l==r: return
            pivot_index = partition(l,r)
            print(points)
            if pivot_index == k:
                return
            elif k > pivot_index :
                quickselect(pivot_index+1, r, k)
            else:
                quickselect(l, pivot_index-1, k)

        quickselect(0, len(points)-1, k-1)
        return points[:k]
```

## Attempt 8 · 2023-11-22 10:05 IST · Runtime Error · Python3

[submission 1103921868](https://leetcode.com/submissions/detail/1103921868/) · tests 0/87

Failing input:

```text
[[1,3],[-2,2]]
1
```

Expected:

```text
[[-2,2]]
```

Runtime error:

```text
SyntaxError: invalid syntax
        ^
    elif:
Line 38  (Solution.py)
```

```python
class Solution:
    def kClosest1(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        heap = []

        for i, point in enumerate(points):
            heapq.heappush(heap,(-dist(i), point))
            if i>=k:
                heapq.heappop(heap)
        
        return [point for _, point in heap]

    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2
        
        def partition(l,r):
            pivot_index = random.randint(l,r)
            pivot = dist(pivot_index)

            points[pivot_index], points[r] = points[r], points[pivot_index]
            i = l
            for j in range(l,r):
                if dist(j) < pivot:
                    points[i], points[j] = points[j], points[i]
                    i+=1
            
            points[i], points[r] = points[r], points[i]

            return i

        def quickselect(l,r,k):
            if l==r: return
            pivot_index = partition(l,r)
            
            if k > pivot_index :
                quickselect(pivot_index+1, r, k)
            elif:
                quickselect(l, pivot_index-1, k)

        quickselect(0, len(points)-1, k-1)
        return points[:k]
```

## Attempt 9 · 2023-11-22 10:05 IST · Time Limit Exceeded · Python3

[submission 1103922048](https://leetcode.com/submissions/detail/1103922048/) · tests 85/87

Failing input:

```text
[[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000, ... [139607 more chars]
```

Expected:

```text
[[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000, ... [139601 more chars]
```

```python
class Solution:
    def kClosest1(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        heap = []

        for i, point in enumerate(points):
            heapq.heappush(heap,(-dist(i), point))
            if i>=k:
                heapq.heappop(heap)
        
        return [point for _, point in heap]

    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2
        
        def partition(l,r):
            pivot_index = random.randint(l,r)
            pivot = dist(pivot_index)

            points[pivot_index], points[r] = points[r], points[pivot_index]
            i = l
            for j in range(l,r):
                if dist(j) < pivot:
                    points[i], points[j] = points[j], points[i]
                    i+=1
            
            points[i], points[r] = points[r], points[i]

            return i

        def quickselect(l,r,k):
            if l==r: return
            pivot_index = partition(l,r)
            
            if k > pivot_index:
                quickselect(pivot_index+1, r, k)
            elif k < pivot_index:
                quickselect(l, pivot_index-1, k)

        quickselect(0, len(points)-1, k-1)
        return points[:k]
```

## Attempt 10 · 2023-11-22 10:08 IST · Output Limit Exceeded · Python3

[submission 1103923083](https://leetcode.com/submissions/detail/1103923083/) · tests 82/87

Failing input:

```text
[[-4590,777],[6633,7111],[6375,-1654],[-764,-3563],[2374,5149],[-2840,8057],[-6663,4859],[-5563,802],[-6110,-2393],[9152,-6197],[332,3209],[4627,9160],[-9990,3577],[-5024,-3598],[-1928,1041],[-7301,-212],[4708,6595],[7386,2396],[7066,2046],[-4203,-8044],[-5625,-3842],[-2881,8488],[9063,8730],[9593,2568],[8892,-3457],[-1750,4716],[7314,9898],[-8662,-3332],[-7192,-8638],[-5316,-3478],[877,6056],[-98 ... [127041 more chars]
```

Expected:

```text
[[-14,123],[-127,-49],[-15,-198],[203,86],[-129,-189],[64,-225],[-96,-280],[-341,112],[-121,-396],[321,264],[-176,394],[411,149],[-157,-415],[337,292],[277,-358],[471,43],[-180,450],[-472,136],[442,-273],[-1,-531],[405,-345],[-432,324],[-547,-134],[-227,543],[508,-308],[-606,-42],[-515,323],[15,-609],[409,455],[-594,-204],[254,-586],[528,-394],[457,-515],[463,-544],[-258,-686],[-670,311],[654,-345 ... [67697 more chars]
```

```python
class Solution:
    def kClosest1(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        heap = []

        for i, point in enumerate(points):
            heapq.heappush(heap,(-dist(i), point))
            if i>=k:
                heapq.heappop(heap)
        
        return [point for _, point in heap]

    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2
        
        def partition(l,r):
            pivot_index = random.randint(l,r)
            pivot = dist(pivot_index)

            points[pivot_index], points[r] = points[r], points[pivot_index]
            i = l
            for j in range(l,r):
                if dist(j) < pivot:
                    points[i], points[j] = points[j], points[i]
                    i+=1
            
            points[i], points[r] = points[r], points[i]

            return i

        def quickselect(l,r,k):
            if l==r: return
            pivot_index = partition(l,r)
            print(points)
            if pivot_index == k:
                return
            elif k > pivot_index :
                quickselect(pivot_index+1, r, k)
            else:
                quickselect(l, pivot_index-1, k)

        quickselect(0, len(points)-1, k-1)
        return points[:k]
```

## Attempt 11 · 2023-11-22 10:08 IST · Time Limit Exceeded · Python3

[submission 1103923243](https://leetcode.com/submissions/detail/1103923243/) · tests 85/87

Failing input:

```text
[[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000, ... [139607 more chars]
```

Expected:

```text
[[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000, ... [139601 more chars]
```

```python
class Solution:
    def kClosest1(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        heap = []

        for i, point in enumerate(points):
            heapq.heappush(heap,(-dist(i), point))
            if i>=k:
                heapq.heappop(heap)
        
        return [point for _, point in heap]

    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2
        
        def partition(l,r):
            pivot_index = random.randint(l,r)
            pivot = dist(pivot_index)

            points[pivot_index], points[r] = points[r], points[pivot_index]
            i = l
            for j in range(l,r):
                if dist(j) < pivot:
                    points[i], points[j] = points[j], points[i]
                    i+=1
            
            points[i], points[r] = points[r], points[i]

            return i

        def quickselect(l,r,k):
            if l==r: return
            pivot_index = partition(l,r)
            #print(points)
            if pivot_index == k:
                return
            elif k > pivot_index :
                quickselect(pivot_index+1, r, k)
            else:
                quickselect(l, pivot_index-1, k)

        quickselect(0, len(points)-1, k-1)
        return points[:k]
```

## Attempt 12 · 2023-11-22 10:14 IST · Time Limit Exceeded · Python3

[submission 1103926441](https://leetcode.com/submissions/detail/1103926441/) · tests 85/87

Failing input:

```text
[[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000, ... [139607 more chars]
```

Expected:

```text
[[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000, ... [139601 more chars]
```

```python
class Solution:
    def kClosest1(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        heap = []

        for i, point in enumerate(points):
            heapq.heappush(heap,(-dist(i), point))
            if i>=k:
                heapq.heappop(heap)
        
        return [point for _, point in heap]

    def kClosest(self, points, K):
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        def sort(i, j, K):
            # Partially sorts A[i:j+1] so the first K elements are
            # the smallest K elements.
            if i >= j: return

            # Put random element as A[i] - this is the pivot
            k = random.randint(i, j)
            points[i], points[k] = points[k], points[i]

            mid = partition(i, j)
            if K < mid - i + 1:
                sort(i, mid - 1, K)
            elif K > mid - i + 1:
                sort(mid + 1, j, K - (mid - i + 1))

        def partition(i, j):
            # Partition by pivot A[i], returning an index mid
            # such that A[i] <= A[mid] <= A[j] for i < mid < j.
            oi = i
            pivot = dist(i)
            i += 1

            while True:
                while i < j and dist(i) < pivot:
                    i += 1
                while i <= j and dist(j) >= pivot:
                    j -= 1
                if i >= j: break
                points[i], points[j] = points[j], points[i]

            points[oi], points[j] = points[j], points[oi]
            return j

        sort(0, len(points) - 1, K)
        return points[:K]

    def kClosest2(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2
        
        def partition(l,r):
            pivot_index = random.randint(l,r)
            pivot = dist(pivot_index)

            points[pivot_index], points[r] = points[r], points[pivot_index]
            i = l
            for j in range(l,r):
                if dist(j) < pivot:
                    points[i], points[j] = points[j], points[i]
                    i+=1
            
            points[i], points[r] = points[r], points[i]

            return i

        def quickselect(l,r,k):
            if l>=r: return
            pivot_index = partition(l,r)
            #print(points)
            if pivot_index == k:
                return
            elif k > pivot_index :
                quickselect(pivot_index+1, r, k)
            else:
                quickselect(l, pivot_index-1, k)

        quickselect(0, len(points)-1, k-1)
        return points[:k]
```

## Attempt 13 · 2023-12-02 02:38 IST · Wrong Answer · Python3

[submission 1110461639](https://leetcode.com/submissions/detail/1110461639/) · tests 16/87

Failing input:

```text
[[2,2],[2,2],[2,2],[2,2],[2,2],[2,2],[1,1]]
1
```

Expected:

```text
[[1,1]]
```

Your output:

```text
[[2,2]]
```

```python
class Solution:
    def kClosest1(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        heap = []

        for i, point in enumerate(points):
            heapq.heappush(heap,(-dist(i), point))
            if i>=k:
                heapq.heappop(heap)
        
        return [point for _, point in heap]

    def kClosest(self, points, K):
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        def partition(l,r,pivot_idx):
            pivot = dist(pivot_idx)

            points[r], points[pivot_idx] = points[pivot_idx] ,points[r]

            store_idx = l
            for i in range(l,r):
                if  dist(i) < pivot:
                    store_idx +=1
            
            points[r], points[store_idx] = points[store_idx] ,points[r]

            return store_idx

        def qs(l, r, k):
            if l ==r:
                return 

            pivot_idx = random.randint(l, r)
            pivot_idx = partition(l,r,pivot_idx)

            if k == pivot_idx:
                return
            elif k<pivot_idx:
                qs(l,pivot_idx-1,k)
            else:
                qs(pivot_idx+1,r,k)

        qs(0, len(points)-1,K)
        return points[:K]




    def kClosest2(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2
        
        def partition(l,r):
            pivot_index = random.randint(l,r)
            pivot = dist(pivot_index)

            points[pivot_index], points[r] = points[r], points[pivot_index]
            i = l
            for j in range(l,r):
                if dist(j) < pivot:
                    points[i], points[j] = points[j], points[i]
                    i+=1
            
            points[i], points[r] = points[r], points[i]

            return i

        def quickselect(l,r,k):
            if l>=r: return
            pivot_index = partition(l,r, pivot_idx)
            #print(points)
            if pivot_index == k:
                return
            elif k > pivot_index :
                quickselect(pivot_index+1, r, k)
            else:
                quickselect(l, pivot_index-1, k)

        quickselect(0, len(points)-1, k-1)
        return points[:k]
```

## Attempt 14 · 2023-12-02 02:40 IST · Wrong Answer · Python3

[submission 1110462128](https://leetcode.com/submissions/detail/1110462128/) · tests 20/87

Failing input:

```text
[[2,2],[2,2],[2,2],[2,2],[2,2],[2,2],[1,1]]
1
```

Expected:

```text
[[1,1]]
```

Your output:

```text
[[2,2]]
```

```python
class Solution:
    def kClosest1(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        heap = []

        for i, point in enumerate(points):
            heapq.heappush(heap,(-dist(i), point))
            if i>=k:
                heapq.heappop(heap)
        
        return [point for _, point in heap]

    def kClosest(self, points, K):
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        def partition(l,r,pivot_idx):
            pivot = dist(pivot_idx)

            points[r], points[pivot_idx] = points[pivot_idx] ,points[r]

            store_idx = l
            for i in range(l,r):
                if  dist(i) < pivot:
                    points[store_idx], points[i] = points[store_idx] ,points[i]
                    store_idx +=1
            
            points[r], points[store_idx] = points[store_idx] ,points[r]

            return store_idx

        def qs(l, r, k):
            if l ==r:
                return 

            pivot_idx = random.randint(l, r)
            pivot_idx = partition(l,r,pivot_idx)

            if k == pivot_idx:
                return
            elif k<pivot_idx:
                qs(l,pivot_idx-1,k)
            else:
                qs(pivot_idx+1,r,k)

        qs(0, len(points)-1,K)
        return points[:K]




    def kClosest2(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2
        
        def partition(l,r):
            pivot_index = random.randint(l,r)
            pivot = dist(pivot_index)

            points[pivot_index], points[r] = points[r], points[pivot_index]
            i = l
            for j in range(l,r):
                if dist(j) < pivot:
                    points[i], points[j] = points[j], points[i]
                    i+=1
            
            points[i], points[r] = points[r], points[i]

            return i

        def quickselect(l,r,k):
            if l>=r: return
            pivot_index = partition(l,r, pivot_idx)
            #print(points)
            if pivot_index == k:
                return
            elif k > pivot_index :
                quickselect(pivot_index+1, r, k)
            else:
                quickselect(l, pivot_index-1, k)

        quickselect(0, len(points)-1, k-1)
        return points[:k]
```

## Attempt 15 · 2023-12-02 02:43 IST · Wrong Answer · Python3

[submission 1110463354](https://leetcode.com/submissions/detail/1110463354/) · tests 24/87

Failing input:

```text
[[2,2],[2,2],[2,2],[2,2],[2,2],[2,2],[1,1]]
1
```

Expected:

```text
[[1,1]]
```

Your output:

```text
[[2,2]]
```

```python
class Solution:
    def kClosest1(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        heap = []

        for i, point in enumerate(points):
            heapq.heappush(heap,(-dist(i), point))
            if i>=k:
                heapq.heappop(heap)
        
        return [point for _, point in heap]

    def kClosest(self, points, K):
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        def partition(l,r,pivot_idx):
            pivot = dist(pivot_idx)

            points[r], points[pivot_idx] = points[pivot_idx] ,points[r]

            store_idx = l
            for i in range(l,r):
                if  dist(i) < pivot:
                    points[store_idx], points[i] = points[store_idx] ,points[i]
                    store_idx +=1
            
            points[r], points[store_idx] = points[store_idx] ,points[r]

            return store_idx

        def qs(l, r, k):
            if l ==r:
                return 

            pivot_idx = random.randint(l, r)
            pivot_idx = partition(l,r,pivot_idx)

            if k == pivot_idx:
                return
            elif k<pivot_idx:
                qs(l,pivot_idx-1,k)
            else:
                qs(pivot_idx+1,r,k)

        qs(0, len(points)-1,K- 1)
        return points[:K]




    def kClosest2(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2
        
        def partition(l,r):
            pivot_index = random.randint(l,r)
            pivot = dist(pivot_index)

            points[pivot_index], points[r] = points[r], points[pivot_index]
            i = l
            for j in range(l,r):
                if dist(j) < pivot:
                    points[i], points[j] = points[j], points[i]
                    i+=1
            
            points[i], points[r] = points[r], points[i]

            return i

        def quickselect(l,r,k):
            if l>=r: return
            pivot_index = partition(l,r, pivot_idx)
            #print(points)
            if pivot_index == k:
                return
            elif k > pivot_index :
                quickselect(pivot_index+1, r, k)
            else:
                quickselect(l, pivot_index-1, k)

        quickselect(0, len(points)-1, k-1)
        return points[:k]
```

## Attempt 16 · 2023-12-02 02:44 IST · Time Limit Exceeded · Python3

[submission 1110463589](https://leetcode.com/submissions/detail/1110463589/) · tests 85/87

Failing input:

```text
[[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000, ... [139607 more chars]
```

Expected:

```text
[[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000, ... [139601 more chars]
```

```python
class Solution:
    def kClosest1(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        heap = []

        for i, point in enumerate(points):
            heapq.heappush(heap,(-dist(i), point))
            if i>=k:
                heapq.heappop(heap)
        
        return [point for _, point in heap]

    def kClosest(self, points, K):
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        def partition(l,r,pivot_idx):
            pivot = dist(pivot_idx)

            points[r], points[pivot_idx] = points[pivot_idx] ,points[r]

            store_idx = l
            for i in range(l,r):
                if  dist(i) < pivot:
                    points[store_idx], points[i] = points[store_idx] ,points[i]
                    store_idx +=1
            
            points[r], points[store_idx] = points[store_idx] ,points[r]

            return store_idx

        def qs(l, r, k):
            if l ==r:
                return 

            pivot_idx = random.randint(l, r)
            pivot_idx = partition(l,r,pivot_idx)

            if k == pivot_idx:
                return
            elif k<pivot_idx:
                qs(l,pivot_idx-1,k)
            else:
                qs(pivot_idx+1,r,k)

        qs(0, len(points)-1,K-1)
        return points[:K]




    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2
        
        def partition(l,r):
            pivot_index = random.randint(l,r)
            pivot = dist(pivot_index)

            points[pivot_index], points[r] = points[r], points[pivot_index]
            i = l
            for j in range(l,r):
                if dist(j) < pivot:
                    points[i], points[j] = points[j], points[i]
                    i+=1
            
            points[i], points[r] = points[r], points[i]

            return i

        def quickselect(l,r,k):
            if l>=r: return
            pivot_index = partition(l,r)
            #print(points)
            if pivot_index == k:
                return
            elif k > pivot_index :
                quickselect(pivot_index+1, r, k)
            else:
                quickselect(l, pivot_index-1, k)

        quickselect(0, len(points)-1, k-1)
        return points[:k]
```

## Attempt 17 · 2023-12-02 02:58 IST · Accepted · Python3

[submission 1110469085](https://leetcode.com/submissions/detail/1110469085/) · tests 87/87 · runtime 713 ms (beats 5.0%)

```python
class Solution:
    def kClosest1(self, points: List[List[int]], k: int) -> List[List[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        heap = []

        for i, point in enumerate(points):
            heapq.heappush(heap,(-dist(i), point))
            if i>=k:
                heapq.heappop(heap)
        
        return [point for _, point in heap]

    def kClosest(self, points, K):
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        def partition(l,r,pivot_idx):
            pivot = dist(pivot_idx)

            points[r], points[pivot_idx] = points[pivot_idx] ,points[r]

            store_idx = l
            for i in range(l,r):
                if  dist(i) < pivot:
                    points[store_idx], points[i] = points[store_idx] ,points[i]
                    store_idx +=1
            
            points[r], points[store_idx] = points[store_idx] ,points[r]

            return store_idx

        def qs(l, r, k):
            if l >=r:
                return 

            pivot_idx = random.randint(l, r)
            pivot_idx = partition(l,r,pivot_idx)

            if k == pivot_idx:
                return
            elif k<pivot_idx:
                qs(l,pivot_idx-1,k)
            else:
                qs(pivot_idx+1,r,k)

        qs(0, len(points)-1,K-1)
        return points[:K]




    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        heap = []
        for i, point in enumerate(points):
            dist = point[0]**2+point[1]**2
            heapq.heappush(heap, (-dist,point))
            if i>=k:
                heapq.heappop(heap) 

        return ([p for _, p in heap])
```

## Attempt 18 · 2023-12-04 22:32 IST · Accepted · Python3

[submission 1112301809](https://leetcode.com/submissions/detail/1112301809/) · tests 87/87 · runtime 699 ms (beats 5.0%)

```python
class Solution:
    def kClosest1(self, points: List[List[int]], k: int) -> List[List[int]]:

        '''
        to find k largest, you use minheap and pop out n-k smallest elements what remains is k largest and kth largest is at top 

        to find k smallest, you use maxheap and popout n-k largest elements 
        what remains is k smallest elements and kth smallest element at top

        time complexity - Nlogk
        it is good if k is small - but if k is large it is same as nlogn solution of sorting whole list and getting k

        better approach is to use quickselect with O(n)
        '''
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        heap = []

        for i, point in enumerate(points):
            heapq.heappush(heap,(-dist(i), point))
            if i>=k:
                heapq.heappop(heap)
        
        return [point for _, point in heap]

    def kClosest(self, points, K):
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        def partition(l,r,pivot_idx):
            pivot = dist(pivot_idx)

            points[r], points[pivot_idx] = points[pivot_idx] ,points[r]

            store_idx = l
            for i in range(l,r):
                if  dist(i) < pivot:
                    points[store_idx], points[i] = points[store_idx] ,points[i]
                    store_idx +=1
            
            points[r], points[store_idx] = points[store_idx] ,points[r]

            return store_idx

        def qs(l, r, k):
            if l >=r:
                return 

            pivot_idx = random.randint(l, r)
            pivot_idx = partition(l,r,pivot_idx)

            if k == pivot_idx:
                return
            elif k<pivot_idx:
                qs(l,pivot_idx-1,k)
            else:
                qs(pivot_idx+1,r,k)

        # put k-1 index in its correct position
        qs(0, len(points)-1,K-1)
        return points[:K]




    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        heap = []
        for i, point in enumerate(points):
            dist = point[0]**2+point[1]**2
            heapq.heappush(heap, (-dist,point))
            if i>=k:
                heapq.heappop(heap) 

        return ([p for _, p in heap])
```

## Attempt 19 · 2023-12-31 07:10 IST · Wrong Answer · Python3

[submission 1132603413](https://leetcode.com/submissions/detail/1132603413/) · tests 26/87

Failing input:

```text
[[3,3],[5,-1],[-2,4]]
2
```

Expected:

```text
[[3,3],[-2,4]]
```

Your output:

```text
[[3,3],[5,-1]]
```

```python
class Solution:
    def kClosest1(self, points: List[List[int]], k: int) -> List[List[int]]:

        '''
        to find k largest, you use minheap and pop out n-k smallest elements what remains is k largest and kth largest is at top 

        to find k smallest, you use maxheap and popout n-k largest elements 
        what remains is k smallest elements and kth smallest element at top

        time complexity - Nlogk
        it is good if k is small - but if k is large it is same as nlogn solution of sorting whole list and getting k

        better approach is to use quickselect with O(n)
        '''
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        heap = []

        for i, point in enumerate(points):
            heapq.heappush(heap,(-dist(i), point))
            if i>=k:
                heapq.heappop(heap)
        
        return [point for _, point in heap]

    def kClosest(self, points, K):
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        def partition(l,r,pivot_idx):
            pivot = dist(pivot_idx)

            points[r], points[pivot_idx] = points[pivot_idx] ,points[r]

            
            store_idx = l # correct position of the pivot element
            # you copy smaller eleemnt at store_indx and increment it
            for i in range(l,r):
                if  dist(i) < pivot:
                    points[store_idx], points[i] = points[store_idx] ,points[i]
                    store_idx +=1
            
            points[r], points[store_idx] = points[store_idx] ,points[r]

            return store_idx

        def qs(l, r, k):
            if l >=r:
                return 

            pivot_idx = random.randint(l, r)
            pivot_idx = partition(l,r,pivot_idx)

            if k == pivot_idx:
                return
            elif k<pivot_idx:
                qs(l,pivot_idx-1,k)
            else:
                qs(pivot_idx+1,r,k)

        # put k-1 index in its correct position
        qs(0, len(points)-1,K-1)
        return points[:K]


    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:

        dist = lambda i: points[i][0]**2 + points[i][1]**2

        def partition(l,r,pivot_idx):
            pivot = dist(pivot_idx)

            # move pivot to right
            points[pivot_idx], points[r] =  points[r], points[pivot_idx] 

            correct_pivot_idx = l # correct position of pivot
            for i in range(l, r):
                if dist(i) < pivot:
                    points[correct_pivot_idx], points[i] =  points[i], points[correct_pivot_idx] 
                    correct_pivot_idx +=1

            # move the pivot to correct position
            points[r], points[correct_pivot_idx] = points[correct_pivot_idx] ,points[r]

            return correct_pivot_idx
 
        def quickselect(l, r, k):
            if l>=r:
                return
            
            pivot_idx = random.randint(l,r)
            pivot_idx = partition(l,r,pivot_idx)

            if pivot_idx == k:
                return
            elif pivot_idx < k:
                quickselect(l, pivot_idx-1, k)
            else:
                quickselect(pivot_idx+1, r, k)


        quickselect(0, len(points)-1, k-1)
        return points[:k]

    def kClosest2(self, points: List[List[int]], k: int) -> List[List[int]]:
        '''
        create a max heap 
        insert -value
        popout n-k items
        remainign k are closest
        '''
        heap = []
        for i, point in enumerate(points):
            dist = point[0]**2+point[1]**2
            heapq.heappush(heap, (-dist,point))
            if i>=k:
                heapq.heappop(heap) 

        return ([p for _, p in heap])
```

## Attempt 20 · 2023-12-31 07:11 IST · Wrong Answer · Python3

[submission 1132603909](https://leetcode.com/submissions/detail/1132603909/) · tests 17/87

Failing input:

```text
[[2,2],[2,2],[2,2],[2,2],[2,2],[2,2],[1,1]]
1
```

Expected:

```text
[[1,1]]
```

Your output:

```text
[[2,2]]
```

```python
class Solution:
    def kClosest1(self, points: List[List[int]], k: int) -> List[List[int]]:

        '''
        to find k largest, you use minheap and pop out n-k smallest elements what remains is k largest and kth largest is at top 

        to find k smallest, you use maxheap and popout n-k largest elements 
        what remains is k smallest elements and kth smallest element at top

        time complexity - Nlogk
        it is good if k is small - but if k is large it is same as nlogn solution of sorting whole list and getting k

        better approach is to use quickselect with O(n)
        '''
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        heap = []

        for i, point in enumerate(points):
            heapq.heappush(heap,(-dist(i), point))
            if i>=k:
                heapq.heappop(heap)
        
        return [point for _, point in heap]

    def kClosest(self, points, K):
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        def partition(l,r,pivot_idx):
            pivot = dist(pivot_idx)

            points[r], points[pivot_idx] = points[pivot_idx] ,points[r]

            
            store_idx = l # correct position of the pivot element
            # you copy smaller eleemnt at store_indx and increment it
            for i in range(l,r):
                if  dist(i) < pivot:
                    points[store_idx], points[i] = points[store_idx] ,points[i]
                    store_idx +=1
            
            points[r], points[store_idx] = points[store_idx] ,points[r]

            return store_idx

        def qs(l, r, k):
            if l >=r:
                return 

            pivot_idx = random.randint(l, r)
            pivot_idx = partition(l,r,pivot_idx)

            if k == pivot_idx:
                return
            elif k<pivot_idx:
                qs(l,pivot_idx-1,k)
            else:
                qs(pivot_idx+1,r,k)

        # put k-1 index in its correct position
        qs(0, len(points)-1,K-1)
        return points[:K]


    def kClosest6(self, points: List[List[int]], k: int) -> List[List[int]]:

        dist = lambda i: points[i][0]**2 + points[i][1]**2

        def partition(l,r,pivot_idx):
            pivot = dist(pivot_idx)

            # move pivot to right
            points[pivot_idx], points[r] =  points[r], points[pivot_idx] 

            correct_pivot_idx = l # correct position of pivot
            for i in range(l, r):
                if dist(i) < pivot:
                    points[correct_pivot_idx], points[i] =  points[i], points[correct_pivot_idx] 
                    correct_pivot_idx +=1

            # move the pivot to correct position
            points[r], points[correct_pivot_idx] = points[correct_pivot_idx] ,points[r]

            return correct_pivot_idx
 
        def quickselect(l, r, k):
            if l>=r:
                return
            
            pivot_idx = random.randint(l,r)
            pivot_idx = partition(l,r,pivot_idx)

            if pivot_idx == k:
                return
            elif pivot_idx < k:
                quickselect(l, pivot_idx-1, k)
            else:
                quickselect(pivot_idx+1, r, k)


        quickselect(0, len(points)-1, k-1)
        return points[:k]

    def kClosest2(self, points: List[List[int]], k: int) -> List[List[int]]:
        '''
        create a max heap 
        insert -value
        popout n-k items
        remainign k are closest
        '''
        heap = []
        for i, point in enumerate(points):
            dist = point[0]**2+point[1]**2
            heapq.heappush(heap, (-dist,point))
            if i>=k:
                heapq.heappop(heap) 

        return ([p for _, p in heap])
```

## Attempt 21 · 2023-12-31 07:11 IST · Wrong Answer · Python3

[submission 1132604152](https://leetcode.com/submissions/detail/1132604152/) · tests 7/87

Failing input:

```text
[[3,3],[5,-1],[-2,4]]
2
```

Expected:

```text
[[3,3],[-2,4]]
```

Your output:

```text
[[3,3],[5,-1]]
```

```python
class Solution:
    def kClosest1(self, points: List[List[int]], k: int) -> List[List[int]]:

        '''
        to find k largest, you use minheap and pop out n-k smallest elements what remains is k largest and kth largest is at top 

        to find k smallest, you use maxheap and popout n-k largest elements 
        what remains is k smallest elements and kth smallest element at top

        time complexity - Nlogk
        it is good if k is small - but if k is large it is same as nlogn solution of sorting whole list and getting k

        better approach is to use quickselect with O(n)
        '''
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        heap = []

        for i, point in enumerate(points):
            heapq.heappush(heap,(-dist(i), point))
            if i>=k:
                heapq.heappop(heap)
        
        return [point for _, point in heap]

    def kClosest(self, points, K):
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        def partition(l,r,pivot_idx):
            pivot = dist(pivot_idx)

            points[r], points[pivot_idx] = points[pivot_idx] ,points[r]

            
            store_idx = l # correct position of the pivot element
            # you copy smaller eleemnt at store_indx and increment it
            for i in range(l,r):
                if  dist(i) < pivot:
                    points[store_idx], points[i] = points[store_idx] ,points[i]
                    store_idx +=1
            
            points[r], points[store_idx] = points[r],points[store_idx] 

            return store_idx

        def qs(l, r, k):
            if l >=r:
                return 

            pivot_idx = random.randint(l, r)
            pivot_idx = partition(l,r,pivot_idx)

            if k == pivot_idx:
                return
            elif k<pivot_idx:
                qs(l,pivot_idx-1,k)
            else:
                qs(pivot_idx+1,r,k)

        # put k-1 index in its correct position
        qs(0, len(points)-1,K-1)
        return points[:K]


    def kClosest6(self, points: List[List[int]], k: int) -> List[List[int]]:

        dist = lambda i: points[i][0]**2 + points[i][1]**2

        def partition(l,r,pivot_idx):
            pivot = dist(pivot_idx)

            # move pivot to right
            points[pivot_idx], points[r] =  points[r], points[pivot_idx] 

            correct_pivot_idx = l # correct position of pivot
            for i in range(l, r):
                if dist(i) < pivot:
                    points[correct_pivot_idx], points[i] =  points[i], points[correct_pivot_idx] 
                    correct_pivot_idx +=1

            # move the pivot to correct position
            points[r], points[correct_pivot_idx] = points[correct_pivot_idx] ,points[r]

            return correct_pivot_idx
 
        def quickselect(l, r, k):
            if l>=r:
                return
            
            pivot_idx = random.randint(l,r)
            pivot_idx = partition(l,r,pivot_idx)

            if pivot_idx == k:
                return
            elif pivot_idx < k:
                quickselect(l, pivot_idx-1, k)
            else:
                quickselect(pivot_idx+1, r, k)


        quickselect(0, len(points)-1, k-1)
        return points[:k]

    def kClosest2(self, points: List[List[int]], k: int) -> List[List[int]]:
        '''
        create a max heap 
        insert -value
        popout n-k items
        remainign k are closest
        '''
        heap = []
        for i, point in enumerate(points):
            dist = point[0]**2+point[1]**2
            heapq.heappush(heap, (-dist,point))
            if i>=k:
                heapq.heappop(heap) 

        return ([p for _, p in heap])
```

## Attempt 22 · 2023-12-31 07:13 IST · Time Limit Exceeded · Python3

[submission 1132604943](https://leetcode.com/submissions/detail/1132604943/) · tests 85/87

Failing input:

```text
[[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000, ... [139607 more chars]
```

Expected:

```text
[[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000,10000],[10000, ... [139601 more chars]
```

```python
class Solution:
    def kClosest1(self, points: List[List[int]], k: int) -> List[List[int]]:

        '''
        to find k largest, you use minheap and pop out n-k smallest elements what remains is k largest and kth largest is at top 

        to find k smallest, you use maxheap and popout n-k largest elements 
        what remains is k smallest elements and kth smallest element at top

        time complexity - Nlogk
        it is good if k is small - but if k is large it is same as nlogn solution of sorting whole list and getting k

        better approach is to use quickselect with O(n)
        '''
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        heap = []

        for i, point in enumerate(points):
            heapq.heappush(heap,(-dist(i), point))
            if i>=k:
                heapq.heappop(heap)
        
        return [point for _, point in heap]

    def kClosest(self, points, K):
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        def partition(l,r,pivot_idx):
            pivot = dist(pivot_idx)

            points[r], points[pivot_idx] = points[pivot_idx] ,points[r]

            
            store_idx = l # correct position of the pivot element
            # you copy smaller eleemnt at store_indx and increment it
            for i in range(l,r):
                if  dist(i) < pivot:
                    points[store_idx], points[i] = points[store_idx] ,points[i]
                    store_idx +=1
            
            points[r], points[store_idx] = points[r],points[store_idx] 

            return store_idx

        def qs(l, r, k):
            if l >=r:
                return 

            pivot_idx = random.randint(l, r)
            pivot_idx = partition(l,r,pivot_idx)

            if k == pivot_idx:
                return
            elif k<pivot_idx:
                qs(l,pivot_idx-1,k)
            else:
                qs(pivot_idx+1,r,k)

        # put k-1 index in its correct position
        qs(0, len(points)-1,K-1)
        return points[:K]


    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:

        dist = lambda i: points[i][0]**2 + points[i][1]**2

        def partition(l,r,pivot_idx):
            pivot = dist(pivot_idx)

            # move pivot to right
            points[pivot_idx], points[r] =  points[r], points[pivot_idx] 

            correct_pivot_idx = l # correct position of pivot
            for i in range(l, r):
                if dist(i) < pivot:
                    points[correct_pivot_idx], points[i] =  points[i], points[correct_pivot_idx] 
                    correct_pivot_idx +=1

            # move the pivot to correct position
            points[r], points[correct_pivot_idx] = points[correct_pivot_idx] ,points[r]

            return correct_pivot_idx
 
        def quickselect(l, r, k):
            if l>=r:
                return
            
            pivot_idx = random.randint(l,r)
            pivot_idx = partition(l,r,pivot_idx)

            if pivot_idx == k:
                return
            elif pivot_idx < k:
                quickselect(pivot_idx+1, r, k)
            else:
                quickselect(l, pivot_idx-1, k)


        quickselect(0, len(points)-1, k-1)
        return points[:k]

    def kClosest2(self, points: List[List[int]], k: int) -> List[List[int]]:
        '''
        create a max heap 
        insert -value
        popout n-k items
        remainign k are closest
        '''
        heap = []
        for i, point in enumerate(points):
            dist = point[0]**2+point[1]**2
            heapq.heappush(heap, (-dist,point))
            if i>=k:
                heapq.heappop(heap) 

        return ([p for _, p in heap])
```

## Attempt 23 · 2024-02-06 05:30 IST · Accepted · Python3

[submission 1167283292](https://leetcode.com/submissions/detail/1167283292/) · tests 87/87 · runtime 633 ms (beats 5.0%)

```python
class Solution:
    def kClosest1(self, points: List[List[int]], k: int) -> List[List[int]]:

        '''
        to find k largest, you use minheap and pop out n-k smallest elements what remains is k largest and kth largest is at top 

        to find k smallest, you use maxheap and popout n-k largest elements 
        what remains is k smallest elements and kth smallest element at top

        time complexity - Nlogk
        it is good if k is small - but if k is large it is same as nlogn solution of sorting whole list and getting k

        better approach is to use quickselect with O(n)
        '''
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        heap = []

        for i, point in enumerate(points):
            heapq.heappush(heap,(-dist(i), point))
            if i>=k:
                heapq.heappop(heap)
        
        return [point for _, point in heap]

    def kClosest(self, points, K):
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        def partition(l,r,pivot_idx):
            pivot = dist(pivot_idx)

            points[r], points[pivot_idx] = points[pivot_idx] ,points[r]

            
            store_idx = l # correct position of the pivot element
            # you copy smaller eleemnt at store_indx and increment it
            for i in range(l,r):
                if  dist(i) < pivot:
                    points[store_idx], points[i] = points[store_idx] ,points[i]
                    store_idx +=1
            
            points[r], points[store_idx] = points[r],points[store_idx] 

            return store_idx

        def qs(l, r, k):
            if l >=r:
                return 

            pivot_idx = random.randint(l, r)
            pivot_idx = partition(l,r,pivot_idx)

            if k == pivot_idx:
                return
            elif k<pivot_idx:
                qs(l,pivot_idx-1,k)
            else:
                qs(pivot_idx+1,r,k)

        # put k-1 index in its correct position
        qs(0, len(points)-1,K-1)
        return points[:K]


    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:

        dist = lambda i: points[i][0]**2 + points[i][1]**2

        def partition(l,r,pivot_idx):
            pivot = dist(pivot_idx)

            # move pivot to right
            points[pivot_idx], points[r] =  points[r], points[pivot_idx] 

            correct_pivot_idx = l # correct position of pivot
            for i in range(l, r):
                if dist(i) < pivot:
                    points[correct_pivot_idx], points[i] =  points[i], points[correct_pivot_idx] 
                    correct_pivot_idx +=1

            # move the pivot to correct position
            points[r], points[correct_pivot_idx] = points[correct_pivot_idx] ,points[r]

            return correct_pivot_idx
 
        def quickselect(l, r, k):
            if l>=r:
                return
            
            pivot_idx = random.randint(l,r)
            pivot_idx = partition(l,r,pivot_idx)

            if pivot_idx == k:
                return
            elif pivot_idx < k:
                quickselect(pivot_idx+1, r, k)
            else:
                quickselect(l, pivot_idx-1, k)


        quickselect(0, len(points)-1, k-1)
        return points[:k]

    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        '''
        create a max heap 
        insert -value
        popout n-k items
        remainign k are closest
        '''
        heap = []
        for i, point in enumerate(points):
            dist = point[0]**2+point[1]**2
            heapq.heappush(heap, (-dist,point))
            if i>=k:
                heapq.heappop(heap) 

        return ([p for _, p in heap])
```

## Attempt 24 · 2025-06-14 21:53 IST · Accepted · C++

[submission 1664025842](https://leetcode.com/submissions/detail/1664025842/) · tests 87/87 · runtime 44 ms (beats 54.9%)

```cpp
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        vector< pair<int,int> > dis;
        int idx = 0;
        for (auto point : points) {
            int x = point[0];
            int y = point[1];

            int dist = (x*x) + (y*y);

            dis.push_back({dist, idx});
            idx++;
        }
        sort(dis.begin(), dis.end());
        vector< vector<int>> ans;
        for (int i=0; i<k;i++) {
            int idx = dis[i].second;
            ans.push_back({points[idx][0], points[idx][1]});
        }
        return ans;
    }
};
```

## Attempt 25 · 2025-06-14 21:54 IST · Accepted · C++

[submission 1664026000](https://leetcode.com/submissions/detail/1664026000/) · tests 87/87 · runtime 44 ms (beats 54.9%)

```cpp
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        vector< pair<int,int> > dis;
        int idx = 0;
        for (auto point : points) {
            int x = point[0];
            int y = point[1];
            int dist = (x*x) + (y*y);
            dis.push_back({dist, idx});
            idx++;
        }
        sort(dis.begin(), dis.end());
        vector< vector<int>> ans;
        for (int i=0; i<k;i++) {
            int idx = dis[i].second;
            ans.push_back({points[idx][0], points[idx][1]});
        }
        return ans;
    }
};
```
