# 111. Minimum Depth of Binary Tree

[Problem](https://leetcode.com/problems/minimum-depth-of-binary-tree/) · Easy · Binary Tree (BFS / Level Order) → BFS to first leaf

LeetCode tags: tree, depth-first-search, breadth-first-search, binary-tree

Attempts since Mar 2023: 3 · accepted: 1 · failed before first AC: 2

## Attempt 1 · 2024-02-06 13:20 IST · Runtime Error · Python3

[submission 1167590140](https://leetcode.com/submissions/detail/1167590140/) · tests 2/53

Failing input:

```text
[]
```

Expected:

```text
0
```

Runtime error:

```text
TypeError: inf is not valid value for the expected return type integer
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    raise TypeError(str(ret) + " is not valid value for the expected return type integer");
Line 49 in _driver (Solution.py)
    _driver()
Line 56 in <module> (Solution.py)
During handling of the above exception, another exception occurre ... [302 more chars]
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def minDepth(self, root: Optional[TreeNode]) -> int:
        ans = float('inf')
        def dfs(root, depth):
            nonlocal ans
            if not root:
                return 
            
            dfs(root.left, depth+1)
            dfs(root.right, depth + 1)

            if not root.left and not root.right:
                # print(root.val, depth)
                ans = min(ans, depth)

        dfs(root,1)
        return ans
```

## Attempt 2 · 2024-02-06 13:21 IST · Runtime Error · Python3

[submission 1167590527](https://leetcode.com/submissions/detail/1167590527/) · tests 2/53

Failing input:

```text
[]
```

Expected:

```text
0
```

Runtime error:

```text
TypeError: inf is not valid value for the expected return type integer
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    raise TypeError(str(ret) + " is not valid value for the expected return type integer");
Line 49 in _driver (Solution.py)
    _driver()
Line 56 in <module> (Solution.py)
During handling of the above exception, another exception occurre ... [302 more chars]
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def minDepth(self, root: Optional[TreeNode]) -> int:
        ans = float('inf')
        def dfs(root, depth):
            nonlocal ans
            if not root:
                return 
            
            dfs(root.left, depth+1)
            dfs(root.right, depth + 1)

            if not root.left and not root.right:
                # print(root.val, depth)
                ans = min(ans, depth)

        dfs(root,1)
        return ans
```

## Attempt 3 · 2024-02-06 13:21 IST · Accepted · Python3

[submission 1167590796](https://leetcode.com/submissions/detail/1167590796/) · tests 53/53 · runtime 264 ms (beats 5.2%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def minDepth(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0
        ans = float('inf')
        def dfs(root, depth):
            nonlocal ans
            if not root:
                return 
            
            dfs(root.left, depth+1)
            dfs(root.right, depth + 1)

            if not root.left and not root.right:
                # print(root.val, depth)
                ans = min(ans, depth)

        dfs(root,1)
        return ans
```
