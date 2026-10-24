# 1161. Maximum Level Sum of a Binary Tree

[Problem](https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/) · Medium · Binary Tree (BFS / Level Order) → Level order

LeetCode tags: tree, depth-first-search, breadth-first-search, binary-tree

Attempts since Mar 2023: 3 · accepted: 2 · failed before first AC: 1

## Attempt 1 · 2024-02-06 12:54 IST · Wrong Answer · Python3

[submission 1167571169](https://leetcode.com/submissions/detail/1167571169/) · tests 38/41

Failing input:

```text
[-100,-200,-300,-20,-5,-10,null]
```

Expected:

```text
3
```

Your output:

```text
0
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def maxLevelSum(self, root: Optional[TreeNode]) -> int:
        queue = deque([root])
        max_level_sum = 0
        max_level = 0
        level =0
        while queue:
            
            level_sum = 0
            level+=1
            for _ in range(len(queue)):
                root = queue.popleft()
                level_sum += root.val 

                if root.left:
                    queue.append(root.left)
                if root.right:
                    queue.append(root.right)

            if level_sum > max_level_sum :
                max_level_sum = level_sum
                max_level = level

        return max_level
```

## Attempt 2 · 2024-02-06 12:55 IST · Accepted · Python3

[submission 1167571941](https://leetcode.com/submissions/detail/1167571941/) · tests 41/41 · runtime 154 ms (beats 5.2%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def maxLevelSum(self, root: Optional[TreeNode]) -> int:
        queue = deque([root])
        max_level_sum = float('-inf')
        max_level = 0
        level =0
        while queue:
            
            level_sum = 0
            level+=1
            for _ in range(len(queue)):
                root = queue.popleft()
                level_sum += root.val 

                if root.left:
                    queue.append(root.left)
                if root.right:
                    queue.append(root.right)

            if level_sum > max_level_sum :
                max_level_sum = level_sum
                max_level = level

        return max_level
```

## Attempt 3 · 2024-02-07 01:42 IST · Accepted · Python3

[submission 1168161300](https://leetcode.com/submissions/detail/1168161300/) · tests 41/41 · runtime 147 ms (beats 5.2%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def maxLevelSum(self, root: Optional[TreeNode]) -> int:
        queue = deque([root])
        max_level_sum = float('-inf')
        max_level = 0
        level =0
        while queue:
            
            level_sum = 0
            level+=1
            for _ in range(len(queue)):
                root = queue.popleft()
                level_sum += root.val 

                if root.left:
                    queue.append(root.left)
                if root.right:
                    queue.append(root.right)

            if level_sum > max_level_sum :
                max_level_sum = level_sum
                max_level = level

        return max_level
```
