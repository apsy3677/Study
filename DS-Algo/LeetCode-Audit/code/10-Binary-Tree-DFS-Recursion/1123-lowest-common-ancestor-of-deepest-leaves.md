# 1123. Lowest Common Ancestor of Deepest Leaves

[Problem](https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/) · Medium · Binary Tree (DFS & Recursion) → Depth + LCA

LeetCode tags: hash-table, tree, depth-first-search, breadth-first-search, binary-tree, binary-lifting, lowest-common-ancestor, dp-on-trees

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2024-02-10 22:53 IST · Accepted · Python3

[submission 1171587420](https://leetcode.com/submissions/detail/1171587420/) · tests 81/81 · runtime 50 ms (beats 11.9%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def lcaDeepestLeaves(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        depths = {}
        max_depth = 0
        def find_depth(root, depth):
            nonlocal max_depth
            if not root:
                return None
            depths[root.val] = depth
            max_depth = max(max_depth, depth)
            find_depth(root.left, depth+1)
            find_depth(root.right, depth+1)
        find_depth(root, 0) 
        print(depths)
        def dfs(root):
            if not root:
                return

            if depths[root.val] == max_depth:
                return root
            
            left = dfs(root.left)
            right = dfs(root.right)

            return root if left and right else left or right
        return dfs(root)
```

## Attempt 2 · 2024-02-10 22:53 IST · Accepted · Python3

[submission 1171587817](https://leetcode.com/submissions/detail/1171587817/) · tests 81/81 · runtime 43 ms (beats 11.9%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def lcaDeepestLeaves(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        depths = {}
        max_depth = 0
        def find_depth(root, depth):
            nonlocal max_depth
            if not root:
                return None
            depths[root] = depth
            max_depth = max(max_depth, depth)
            find_depth(root.left, depth+1)
            find_depth(root.right, depth+1)
        find_depth(root, 0) 
        # print(depths)
        def dfs(root):
            if not root:
                return

            if depths[root] == max_depth:
                return root
            
            left = dfs(root.left)
            right = dfs(root.right)

            return root if left and right else left or right
        return dfs(root)
```
