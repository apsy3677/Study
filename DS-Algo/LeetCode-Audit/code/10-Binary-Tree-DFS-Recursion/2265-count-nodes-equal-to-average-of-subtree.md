# 2265. Count Nodes Equal to Average of Subtree

[Problem](https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/) · Medium · Binary Tree (DFS & Recursion) → Postorder aggregate

LeetCode tags: tree, depth-first-search, binary-tree

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2024-02-06 11:07 IST · Accepted · Python3

[submission 1167489848](https://leetcode.com/submissions/detail/1167489848/) · tests 139/139 · runtime 47 ms (beats 77.5%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def averageOfSubtree(self, root: TreeNode) -> int:
        count = 0
        def postorder(root):
            nonlocal count
            if not root:
                return 0, 0

            left_sum, left_count = postorder(root.left)
            right_sum, right_count = postorder(root.right)

            total_sum = root.val + left_sum + right_sum
            total_count = left_count+right_count + 1
            if total_sum//total_count == root.val:
                count+=1

            return root.val + left_sum + right_sum, total_count

        postorder(root)
        return count
```
