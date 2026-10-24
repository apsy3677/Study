# 1424. Diagonal Traverse II

[Problem](https://leetcode.com/problems/diagonal-traverse-ii/) · Medium · Arrays, Hashing & Sorting → Group by i+j

LeetCode tags: array, sorting, heap-priority-queue

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-12-11 05:19 IST · Accepted · Python3

[submission 1116793579](https://leetcode.com/submissions/detail/1116793579/) · tests 56/56 · runtime 783 ms (beats 5.3%)

```python
class Solution:
    def findDiagonalOrder(self, nums: List[List[int]]) -> List[int]:
        groups = defaultdict(list)

        for row in range(len(nums)-1, -1, -1):
            for col in range(len(nums[row])):
                diag = row + col
                groups[diag].append(nums[row][col])

        ans = []
        curr = 0
        while curr in groups:
            ans.extend(groups[curr])
            curr+=1
        
        return ans
```

## Attempt 2 · 2024-01-27 09:18 IST · Accepted · Python3

[submission 1157919798](https://leetcode.com/submissions/detail/1157919798/) · tests 56/56 · runtime 655 ms (beats 5.3%)

```python
class Solution:
    def findDiagonalOrder(self, nums: List[List[int]]) -> List[int]:
        groups = defaultdict(list)

        for row in range(len(nums)-1, -1, -1):
            for col in range(len(nums[row])):
                diag = row + col
                groups[diag].append(nums[row][col])

        ans = []
        curr = 0
        while curr in groups:
            ans.extend(groups[curr])
            curr+=1
        
        return ans

    def findDiagonalOrder(self, nums: List[List[int]]) -> List[int]:
        queue = deque([(0,0)])
        ans = []
        while queue:
            row, col = queue.popleft()
            ans.append(nums[row][col])
            
            if col ==0 and row+1 <len(nums):
                print('first col')
                print(nums[row+1][col])
                queue.append((row+1, col))

            if col+1  < len(nums[row]):
                print(nums[row][col+1])
                queue.append((row, col+1))

        return ans

    def findDiagonalOrder(self, nums: List[List[int]]) -> List[int]:
        groups = defaultdict(list)

        for row in range(len(nums)-1, -1,-1):
            for col in range(len(nums[row])):
                groups[row+col].append(nums[row][col])

        result = []
        curr = 0
        while curr in groups:
            result.extend(groups[curr])
            curr+=1
        return result

    def findDiagonalOrder(self, nums: List[List[int]]) -> List[int]:
        queue = deque([(0,0)])
        ans = []
        while queue:
            row, col = queue.popleft()

            ans.append(nums[row][col])
            if col == 0 and row+1 < len(nums):
                queue.append((row+1, col))

            if col +1 < len(nums[row]):
                queue.append((row, col+1))
        return ans
```
