# 1762. Buildings With an Ocean View

[Problem](https://leetcode.com/problems/buildings-with-an-ocean-view/) · Medium · Monotonic Stack / Deque → Right-to-left max

LeetCode tags: array, stack, monotonic-stack

Attempts since Mar 2023: 4 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-11-23 20:14 IST · Accepted · Python3

[submission 1104886054](https://leetcode.com/submissions/detail/1104886054/) · tests 77/77 · runtime 590 ms (beats 5.0%)

```python
class Solution:
    def findBuildings2(self, heights: List[int]) -> List[int]:
        result = []

        # left to right approach
        # instead of looking ahead, look back
        for i in range(len(heights)):
            # remove all buildings that are smaller than the current building because it will block the view of all smaller ones
            while result and heights[i] >= heights[result[-1]]:
                result.pop()

            result.append(i)

        return result

    def findBuildings1(self, heights: List[int]) -> List[int]:
        result = []

        # right to left
        # check if current buildings view is blocked by any building on the right
        # maintain a monotonic stack  - it will keep elements to the right of current element - only if elements are smaller than current element
        stack = []


    def findBuildings(self, heights: List[int]) -> List[int]:
        maxSoFar = -math.inf

        buildings = []
        for building in range(len(heights)-1, -1,-1):
            if heights[building] <= maxSoFar:
                continue
            maxSoFar = max(maxSoFar, heights[building])

            buildings.append(building)

        return buildings[::-1]
```

## Attempt 2 · 2023-11-23 20:22 IST · Wrong Answer · Python3

[submission 1104890598](https://leetcode.com/submissions/detail/1104890598/) · tests 56/77

Failing input:

```text
[2,2,2,2]
```

Expected:

```text
[3]
```

Your output:

```text
[0,1,2,3]
```

```python
class Solution:
    def findBuildings2(self, heights: List[int]) -> List[int]:
        result = []

        # left to right approach
        # instead of looking ahead, look back
        for i in range(len(heights)):
            # remove all buildings that are smaller than the current building because it will block the view of all smaller ones
            while result and heights[i] >= heights[result[-1]]:
                result.pop()

            result.append(i)

        return result

    def findBuildings(self, heights: List[int]) -> List[int]:
        result = []

        # right to left
        # check if current buildings view is blocked by any building on the right
        # maintain a monotonic stack  - it will keep elements to the right of current element - only if elements are smaller than current element
        stack = []

        buildings = []
        for building in range(len(heights)):
            while stack and heights[stack[-1]] < heights[building]:
                stack.pop()
            stack.append(building)
        return stack




    def findBuildings4(self, heights: List[int]) -> List[int]:
        maxSoFar = -math.inf

        buildings = []
        for building in range(len(heights)-1, -1,-1):
            if heights[building] <= maxSoFar:
                continue
            maxSoFar = max(maxSoFar, heights[building])

            buildings.append(building)

        return buildings[::-1]
```

## Attempt 3 · 2023-11-23 20:23 IST · Accepted · Python3

[submission 1104890758](https://leetcode.com/submissions/detail/1104890758/) · tests 77/77 · runtime 627 ms (beats 5.0%)

```python
class Solution:
    def findBuildings2(self, heights: List[int]) -> List[int]:
        result = []

        # left to right approach
        # instead of looking ahead, look back
        for i in range(len(heights)):
            # remove all buildings that are smaller than the current building because it will block the view of all smaller ones
            while result and heights[i] >= heights[result[-1]]:
                result.pop()

            result.append(i)

        return result

    def findBuildings(self, heights: List[int]) -> List[int]:
        result = []

        # right to left
        # check if current buildings view is blocked by any building on the right
        # maintain a monotonic stack  - it will keep elements to the right of current element - only if elements are smaller than current element
        stack = []

        buildings = []
        for building in range(len(heights)):
            while stack and heights[stack[-1]] <= heights[building]:
                stack.pop()
            stack.append(building)
        return stack




    def findBuildings4(self, heights: List[int]) -> List[int]:
        maxSoFar = -math.inf

        buildings = []
        for building in range(len(heights)-1, -1,-1):
            if heights[building] <= maxSoFar:
                continue
            maxSoFar = max(maxSoFar, heights[building])

            buildings.append(building)

        return buildings[::-1]
```

## Attempt 4 · 2023-12-04 10:54 IST · Accepted · Python3

[submission 1111935541](https://leetcode.com/submissions/detail/1111935541/) · tests 77/77 · runtime 611 ms (beats 5.0%)

```python
class Solution:
    def findBuildings2(self, heights: List[int]) -> List[int]:
        result = []

        # left to right approach
        # instead of looking ahead, look back
        # keep result as decreasing sequence 876531 - no equal values and no larger values in between
        for i in range(len(heights)):
            # remove all buildings that are smaller than the current building because it will block the view of all smaller ones

            # keep index of the buildings in stack
            # as long as height of top of stack is small than or equal to new building - pop 
            while result and heights[i] >= heights[result[-1]]:
                result.pop()


            # return indexes in same order
            result.append(i)

        return result

    def findBuildings(self, heights: List[int]) -> List[int]:
        result = []

        # right to left
        # check if current buildings view is blocked by any building on the right
        # maintain a monotonic stack  - it will keep elements to the right of current element - only if elements are smaller than current element
        stack = []

        buildings = []
        for building in range(len(heights)):
            while stack and heights[stack[-1]] <= heights[building]:
                stack.pop()
            stack.append(building)
        return stack




    def findBuildings4(self, heights: List[int]) -> List[int]:
        maxSoFar = -math.inf

        buildings = []
        # process buildings from right to left
        for building in range(len(heights)-1, -1,-1):

            # if current building is smaller than or equal to maxsoFar 
            # 4 98 -> don;t add it 
            if heights[building] <= maxSoFar:
                continue

            # update max so far
            maxSoFar = max(maxSoFar, heights[building])

            # add building
            buildings.append(building)

        # return reverse
        return buildings[::-1]
```
