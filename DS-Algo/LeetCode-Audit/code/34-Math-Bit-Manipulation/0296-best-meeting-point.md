# 296. Best Meeting Point

[Problem](https://leetcode.com/problems/best-meeting-point/) · Hard · Math & Bit Manipulation → Median

LeetCode tags: array, math, sorting, matrix

Attempts since Mar 2023: 5 · accepted: 2 · failed before first AC: 1

## Attempt 1 · 2023-11-17 01:13 IST · Time Limit Exceeded · Python

[submission 1100314137](https://leetcode.com/submissions/detail/1100314137/) · tests 56/58

Failing input:

```text
[[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, ... [24021 more chars]
```

Expected:

```text
665500
```

```python
class Solution(object):
    def minTotalDistance(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        # get all points
        points = []
        minDistance = float('inf')

        def distance(points, row, col):
            distance=0
            for point in points:
                distance += abs(point[0]- row) + abs(point[1] - col)
            return distance

        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] ==1:
                    points.append((i,j))

        for i in range(len(grid)):
            for j in range(len(grid[0])):
                dist = distance(points, i,j)
                minDistance = min(dist, minDistance)
        
        return minDistance
```

## Attempt 2 · 2023-11-17 01:26 IST · Accepted · Python

[submission 1100321094](https://leetcode.com/submissions/detail/1100321094/) · tests 58/58 · runtime 82 ms (beats 18.2%)

```python
class Solution(object):
    def minTotalDistance1(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        # get all points
        points = []
        minDistance = float('inf')

        def distance(points, row, col):
            distance=0
            for point in points:
                distance += abs(point[0]- row) + abs(point[1] - col)
            return distance

        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] ==1:
                    points.append((i,j))

        for i in range(len(grid)):
            for j in range(len(grid[0])):
                dist = distance(points, i,j)
                minDistance = min(dist, minDistance)
        
        return minDistance


    def minTotalDistance(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        rows = []
        cols = []

        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] ==1:
                    rows.append(i)
                    cols.append(j)

        def findMedian(arr):
            arr.sort()
            if len(arr) %2 ==0:
                median = (arr[len(arr)//2 - 1] + arr[len(arr)//2]) // 2
                # print(median)
            else:
                median = arr[len(arr)//2]
            
            return median 

        rowMedian = findMedian(rows)
        colMedian = findMedian(cols)

        # print(rowMedian, colMedian)
        return sum([abs(r- rowMedian) + abs(c - colMedian) for r ,c in zip(rows,cols)])
```

## Attempt 3 · 2023-12-05 03:38 IST · Accepted · Python3

[submission 1112468782](https://leetcode.com/submissions/detail/1112468782/) · tests 58/58 · runtime 111 ms (beats 5.5%)

```python
class Solution:
    def minTotalDistance(self, grid: List[List[int]]) -> int:
        '''
        best meeting point in grid with no obstacles
        
        approach 1: for each position on the grid find the manhattan distance to all the houses 1's
        and sum total
        1. collect all the 1s in the houses array 
        2. for each position, find distance of this point to all houses
        3. find minimum of total distance
        time - O(MN MN)
        space O(MN)

        approach 2: finding mahattan distance, requires two indendent operations on x and y axis
        which is median on 1d axis that is a point which is at center of all points

        median(x) median(y)
        1. collect 1s rows and cols - O(MN)
        2. sort rows and cols O(MN log MN)
        3. find median 
        4. sum rows median and cols medians


        '''
        def collectCoords(grid):
            rows =[]
            cols = []
            # for all houses 1s collect rows and cols
            for r in range(len(grid)):
                for c in range(len(grid[0])):

                    # for each house collect row and col
                    if grid[r][c]==1:
                        # rows are insorted order the way we traverse
                        rows.append(r)

                        # cols are not in sorted order
                        cols.append(c)
            return rows, cols

        def find_median(coords):
            coords.sort()
            mid = len(coords)//2
            return coords[mid]


        rows, cols = collectCoords(grid)

        # find median by sorting and then center element or either for even
        median_x = find_median(rows)
        median_y = find_median(cols)
        print(rows, cols, median_x,median_y)

        # find manhattan indepndently of x and y
        return sum(abs(x-median_x) for x in rows) + sum(abs(y-median_y) for y in cols)
```

## Attempt 4 · 2023-12-30 04:38 IST · Time Limit Exceeded · Python3

[submission 1131760567](https://leetcode.com/submissions/detail/1131760567/) · tests 57/58

Failing input:

```text
[[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, ... [80001 more chars]
```

Expected:

```text
4000000
```

```python
class Solution1:
    def minTotalDistance(self, grid: List[List[int]]) -> int:
        '''
        best meeting point in grid with no obstacles
        
        approach 1: for each position on the grid find the manhattan distance to all the houses 1's
        and sum total
        1. collect all the 1s in the houses array 
        2. for each position, find distance of this point to all houses
        3. find minimum of total distance
        time - O(MN MN)
        space O(MN)

        approach 2: finding mahattan distance, requires two indendent operations on x and y axis
        which is median on 1d axis that is a point which is at center of all points

        median(x) median(y)
        1. collect 1s rows and cols - O(MN)
        2. sort rows and cols O(MN log MN)
        3. find median 
        4. sum rows median and cols medians


        '''
        def collectCoords(grid):
            rows =[]
            cols = []
            # for all houses 1s collect rows and cols
            for r in range(len(grid)):
                for c in range(len(grid[0])):

                    # for each house collect row and col
                    if grid[r][c]==1:
                        # rows are insorted order the way we traverse
                        rows.append(r)

                        # cols are not in sorted order
                        cols.append(c)
            return rows, cols

        def find_median(coords):
            coords.sort()
            mid = len(coords)//2
            return coords[mid]


        rows, cols = collectCoords(grid)

        # find median by sorting and then center element or either for even
        median_x = find_median(rows)
        median_y = find_median(cols)
        print(rows, cols, median_x,median_y)

        # find manhattan indepndently of x and y
        return sum(abs(x-median_x) for x in rows) + sum(abs(y-median_y) for y in cols)


class Solution:
    def minTotalDistance(self, grid: List[List[int]]) -> int:
        '''
        best meeting point in grid with no obstacles
        
        approach 1: for each position on the grid find the manhattan distance to all the houses 1's
        and sum total
        1. collect all the 1s in the houses array 
        2. for each position, find distance of this point to all houses
        3. find minimum of total distance
        time - O(MN MN)
        space O(MN)

        approach 2: finding mahattan distance, requires two indendent operations on x and y axis
        which is median on 1d axis that is a point which is at center of all points

        median(x) median(y)
        1. collect 1s rows and cols - O(MN)
        2. sort rows and cols O(MN log MN)
        3. find median 
        4. sum rows median and cols medians


        '''
        def collectCoords(grid):
            rows =[]
            cols = []
            # for all houses 1s collect rows and cols
            for r in range(len(grid)):
                for c in range(len(grid[0])):

                    # for each house collect row and col
                    if grid[r][c]==1:
                        # rows are insorted order the way we traverse
                        rows.append(r)

                        # cols are not in sorted order
                        cols.append(c)
            return rows, cols

        rows, cols = collectCoords(grid)
        points  = list(zip(rows, cols))
        

        # need to calculate distance to all the 1 points from all the cells in the grid

        def calculateDist(r,c, points):
            dist = 0 
            for point in points:
                dist += abs(r-point[0]) + abs(c-point[1])
            return dist
        
        minDist = float('inf')

        for r in range(len(grid)):
            for c in range(len(grid[0])):
                dist = calculateDist(r,c, points)
                minDist = min(minDist, dist)
        return minDist
```

## Attempt 5 · 2024-02-05 07:14 IST · Runtime Error · Python3

[submission 1166342304](https://leetcode.com/submissions/detail/1166342304/) · tests 0/58

Failing input:

```text
[[1,0,0,0,1],[0,0,0,0,0],[0,0,1,0,0]]
```

Expected:

```text
6
```

Runtime error:

```text
TypeError: None is not valid value for the expected return type integer
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    raise TypeError(str(ret) + " is not valid value for the expected return type integer");
Line 162 in _driver (Solution.py)
    _driver()
Line 169 in <module> (Solution.py)
During handling of the above exception, another exception occu ... [300 more chars]
```

```python
class Solution1:
    def minTotalDistance(self, grid: List[List[int]]) -> int:
        '''
        best meeting point in grid with no obstacles
        
        approach 1: for each position on the grid find the manhattan distance to all the houses 1's
        and sum total
        1. collect all the 1s in the houses array 
        2. for each position, find distance of this point to all houses
        3. find minimum of total distance
        time - O(MN MN)
        space O(MN)

        approach 2: finding mahattan distance, requires two indendent operations on x and y axis
        which is median on 1d axis that is a point which is at center of all points

        median(x) median(y)
        1. collect 1s rows and cols - O(MN)
        2. sort rows and cols O(M log M + N log N)
        3. find median 
        4. sum rows median and cols medians


        '''
        def collectCoords(grid):
            rows =[]
            cols = []
            # for all houses 1s collect rows and cols
            for r in range(len(grid)):
                for c in range(len(grid[0])):

                    # for each house collect row and col
                    if grid[r][c]==1:
                        # rows are insorted order the way we traverse
                        rows.append(r)

                        # cols are not in sorted order
                        cols.append(c)
            return rows, cols

        def find_median(coords):
            coords.sort()
            mid = len(coords)//2
            return coords[mid]


        rows, cols = collectCoords(grid)

        # find median by sorting and then center element or either for even
        median_x = find_median(rows)
        median_y = find_median(cols)
        print(rows, cols, median_x,median_y)

        # find manhattan indepndently of x and y
        return sum(abs(x-median_x) for x in rows) + sum(abs(y-median_y) for y in cols)


class Solution:
    def minTotalDistance(self, grid: List[List[int]]) -> int:
        '''
        best meeting point in grid with no obstacles
        
        approach 1: for each position on the grid find the manhattan distance to all the houses 1's
        and sum total
        1. collect all the 1s in the houses array 
        2. for each position, find distance of this point to all houses
        3. find minimum of total distance
        time - O(MN MN)
        space O(MN)

        approach 2: finding mahattan distance, requires two indendent operations on x and y axis
        which is median on 1d axis that is a point which is at center of all points

        median(x) median(y)
        1. collect 1s rows and cols - O(MN)
        2. sort rows and cols O(MN log MN)
        3. find median 
        4. sum rows median and cols medians


        '''
        def collectCoords(grid):
            rows =[]
            cols = []
            # for all houses 1s collect rows and cols
            for r in range(len(grid)):
                for c in range(len(grid[0])):

                    # for each house collect row and col
                    if grid[r][c]==1:
                        # rows are insorted order the way we traverse
                        rows.append(r)

                        # cols are not in sorted order
                        cols.append(c)
            return rows, cols

        rows, cols = collectCoords(grid)
        points  = list(zip(rows, cols))
        

        # need to calculate distance to all the 1 points from all the cells in the grid

        def calculateDist(r,c, points):
            dist = 0 
            for point in points:
                dist += abs(r-point[0]) + abs(c-point[1])
            return dist
        
        minDist = float('inf')

        for r in range(len(grid)):
            for c in range(len(grid[0])):
                dist = calculateDist(r,c, points)
                minDist = min(minDist, dist)
        return minDist

    def minTotalDistance(self, grid: List[List[int]]) -> int:
        def collect_points(grid):
            rows = []
            cols = []
            for r in range(len(grid)):
                for c in range(len(grid)):
                    if grid[r][c] ==1:
                        rows.append(r)
                        cols.append(c)
            return rows, cols

        rows, cols = collect_points(grid)

        # find median 
        def find_median(coords):
            coords.sort()
            mid = len(coords)//2
```
