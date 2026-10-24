# 958. Check Completeness of a Binary Tree

[Problem](https://leetcode.com/problems/check-completeness-of-a-binary-tree/) · Medium · Binary Tree (BFS / Level Order) → Level order null check

LeetCode tags: tree, breadth-first-search, binary-tree

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2024-02-10 21:26 IST · Accepted · Python3

[submission 1171520216](https://leetcode.com/submissions/detail/1171520216/) · tests 120/120 · runtime 35 ms (beats 0.6%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def isCompleteTree(self, root: Optional[TreeNode]) -> bool:
        q = deque([root])
        flag= False
        while q:
            root = q.popleft()
            if not root:
                flag = True
            else:
                if flag: return False
                q.append(root.left)
                q.append(root.right)
        return True


class Solution:
    def isCompleteTree(self, root: Optional[TreeNode]) -> bool:
        queue = deque([root])
        found_empty = False

        while queue:
            node = queue.popleft()
            if not node:
                found_empty = True
            else:
                if found_empty: return False
                queue.append(node.left)
                queue.append(node.right)
        return True
```
