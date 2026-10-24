# 1944. Number of Visible People in a Queue

[Problem](https://leetcode.com/problems/number-of-visible-people-in-a-queue/) · Hard · Monotonic Stack / Deque → Monotonic stack

LeetCode tags: array, stack, monotonic-stack

Attempts since Mar 2023: 4 · accepted: 4 · failed before first AC: 0

## Attempt 1 · 2024-01-23 10:50 IST · Accepted · Python3

[submission 1154268527](https://leetcode.com/submissions/detail/1154268527/) · tests 42/42 · runtime 735 ms (beats 5.1%)

```python
class Solution:
    def canSeePersonsCount(self, heights: List[int]) -> List[int]:
        stack = []
        result = [0]*len(heights)
        i = len(heights) - 1
        while i>=0:
            while stack and stack[-1] < heights[i]:
                stack.pop()
                result[i] +=1
            else:
                if stack:
                    result[i] +=1

            stack.append(heights[i])
            i-=1
        return result
```

## Attempt 2 · 2024-01-23 10:50 IST · Accepted · Python3

[submission 1154268618](https://leetcode.com/submissions/detail/1154268618/) · tests 42/42 · runtime 766 ms (beats 5.1%)

```python
class Solution:
    def canSeePersonsCount(self, heights: List[int]) -> List[int]:
        stack = []
        result = [0]*len(heights)
        i = len(heights) - 1
        while i>=0:
            while stack and stack[-1] < heights[i]:
                stack.pop()
                result[i] +=1
            else:
                if stack:
                    result[i] +=1

            stack.append(heights[i])
            i-=1
        return result
```

## Attempt 3 · 2024-01-23 10:52 IST · Accepted · Python3

[submission 1154269872](https://leetcode.com/submissions/detail/1154269872/) · tests 42/42 · runtime 751 ms (beats 5.1%)

```python
class Solution:
    def canSeePersonsCount(self, heights: List[int]) -> List[int]:
        stack = []
        result = [0]*len(heights)
        i = len(heights) - 1
        while i>=0:
            while stack and stack[-1] < heights[i]:
                stack.pop()
                result[i] +=1
            # else:
            if stack:
                result[i] +=1

            stack.append(heights[i])
            i-=1
        return result
```

## Attempt 4 · 2024-02-11 00:20 IST · Accepted · Python3

[submission 1171657448](https://leetcode.com/submissions/detail/1171657448/) · tests 42/42 · runtime 793 ms (beats 5.1%)

```python
class Solution:
    def canSeePersonsCount(self, heights: List[int]) -> List[int]:
        stack = []
        result = [0]*len(heights)
        i = len(heights) - 1
        while i>=0:
            while stack and stack[-1] < heights[i]:
                stack.pop()
                result[i] +=1
            # else:
            if stack:
                result[i] +=1

            stack.append(heights[i])
            i-=1
        return result

    def canSeePersonsCount(self, heights: List[int]) -> List[int]:
        indx = len(heights) - 1
        stack = []
        visible_count = [0] * len(heights) 

        for i in range(len(heights)-1, -1,-1):
            while stack and heights[stack[-1]] <= heights[i]:
                visible_count[i] +=1
                stack.pop()

            if stack:
                visible_count[i]+=1
            stack.append(i)
        return visible_count
```
