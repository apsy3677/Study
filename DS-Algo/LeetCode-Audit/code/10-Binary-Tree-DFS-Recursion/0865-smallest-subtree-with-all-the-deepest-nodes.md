# 865. Smallest Subtree with all the Deepest Nodes

[Problem](https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/) · Medium · Binary Tree (DFS & Recursion) → Depth + LCA

LeetCode tags: hash-table, tree, depth-first-search, breadth-first-search, binary-tree, binary-lifting, lowest-common-ancestor, dp-on-trees

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2024-02-06 21:33 IST · Accepted · Python3

[submission 1167935171](https://leetcode.com/submissions/detail/1167935171/) · tests 58/58 · runtime 36 ms (beats 1.5%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def subtreeWithAllDeepest(self, root: TreeNode) -> TreeNode:
        depths = {}
        max_depth=0
        def dfs(node, depth):
            nonlocal max_depth
            if not node:
                return

            depths[node] = depth
            max_depth = max(max_depth, depth)
            dfs(node.left, depth+1)
            dfs(node.right, depth+1)

        dfs(root, 0)
        
        def ans(root):
            if not root:
                return

            if depths[root] == max_depth:
                # print(root.val, 'has max depth')
                return root

            L = ans(root.left)
            R = ans(root.right)

            
            # print('for', root.val,L.val if L else None,R.val if R else None)
            return root if L and R else L or R

        return ans(root)
```
