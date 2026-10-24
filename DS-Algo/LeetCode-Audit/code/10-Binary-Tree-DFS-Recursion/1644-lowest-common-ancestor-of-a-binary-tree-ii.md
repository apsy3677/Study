# 1644. Lowest Common Ancestor of a Binary Tree II

[Problem](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-ii/) · Medium · Binary Tree (DFS & Recursion) → LCA with existence check

LeetCode tags: tree, depth-first-search, binary-tree, binary-lifting, lowest-common-ancestor

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2024-02-06 13:00 IST · Accepted · Python3

[submission 1167575616](https://leetcode.com/submissions/detail/1167575616/) · tests 80/80 · runtime 153 ms (beats 37.1%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        
        ans = None
        def dfs(root):
            nonlocal ans

            if not root:
                return False

            left = dfs(root.left)
            right = dfs(root.right)
            mid = root in [p,q]

            if left + right + mid >=2:
                ans = root

            return mid or left or right
        dfs(root)
        return ans
```

## Attempt 2 · 2024-02-06 13:06 IST · Accepted · Python3

[submission 1167580078](https://leetcode.com/submissions/detail/1167580078/) · tests 80/80 · runtime 151 ms (beats 45.9%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        
        ans = None
        def dfs(root):
            nonlocal ans

            if not root or ans is not None:
                return False

            left = dfs(root.left)
            right = dfs(root.right)
            mid = root in [p,q]

            if left + right + mid >=2:
                ans = root

            return mid or left or right
        dfs(root)
        return ans
```

## Attempt 3 · 2024-02-10 15:00 IST · Accepted · Python3

[submission 1171287329](https://leetcode.com/submissions/detail/1171287329/) · tests 80/80 · runtime 138 ms (beats 86.1%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        
        ans = None
        def dfs(root):
            nonlocal ans

            if not root or ans is not None:
                return False

            left = dfs(root.left)
            right = dfs(root.right)
            mid = root in [p,q]

            if left + right + mid >=2:
                ans = root

            return mid or left or right
        dfs(root)
        return ans
```
