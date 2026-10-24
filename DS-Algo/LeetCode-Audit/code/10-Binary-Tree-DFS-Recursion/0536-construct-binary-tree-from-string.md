# 536. Construct Binary Tree from String

[Problem](https://leetcode.com/problems/construct-binary-tree-from-string/) · Medium · Binary Tree (DFS & Recursion) → Recursive parsing

LeetCode tags: string, stack, tree, depth-first-search, binary-tree

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2024-01-30 04:11 IST · Runtime Error · Python3

[submission 1160500292](https://leetcode.com/submissions/detail/1160500292/) · tests 5/86

Failing input:

```text
"4"
```

Expected:

```text
[4]
```

Runtime error:

```text
IndexError: string index out of range
           ~^^^^^^^
    print( s[index])
Line 26 in construct_tree (Solution.py)
           ^^^^^^^^^^^^^^^^^
    return construct_tree(0)[0]
Line 37 in str2tree (Solution.py)
          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    ret = Solution().str2tree(param_1)
Line 56 in _driver (Solution.py)
    _driver()
Line 67 in <module> (Solution.py)
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def str2tree(self, s: str) -> Optional[TreeNode]:
        def construct_tree(index):
            # base condition
            if index >= len(s):
                return None, index

            # Parse the integer value for the root
            start = index
            if s[index] == '-':  # Handle negative numbers
                index += 1
            while index < len(s) and s[index].isdigit():
                index += 1
            value = int(s[start:index])
            # print(index)
            # create root node
            node = TreeNode(value)

            # if it has left
            print( s[index])

            # next code be either close (5) or it could be 2(3)(5) 
            if index < len(s) and s[index] == '(':
                # ignore ( and start parsing from next
                node.left, index = construct_tree(index + 1)
            if node.left and index < len(s) and s[index] == '(':
                node.right, index = construct_tree(index + 1)
            
            return node, index + 1# if index < len(s) and s[index] == ')' else index

        return construct_tree(0)[0]
```

## Attempt 2 · 2024-01-30 04:13 IST · Accepted · Python3

[submission 1160501419](https://leetcode.com/submissions/detail/1160501419/) · tests 86/86 · runtime 72 ms (beats 6.6%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def str2tree(self, s: str) -> Optional[TreeNode]:
        def construct_tree(index):
            # base condition
            if index >= len(s):
                return None, index

            # Parse the integer value for the root
            start = index
            if s[index] == '-':  # Handle negative numbers
                index += 1
            while index < len(s) and s[index].isdigit():
                index += 1
            value = int(s[start:index])
            # print(index)
            # create root node
            node = TreeNode(value)

            # if it has left
            # print( s[index])

            # next code be either close (5) or it could be 2(3)(5) 
            if index < len(s) and s[index] == '(':
                # ignore ( and start parsing from next
                node.left, index = construct_tree(index + 1)
            if node.left and index < len(s) and s[index] == '(':
                node.right, index = construct_tree(index + 1)
            
            return node, index + 1# if index < len(s) and s[index] == ')' else index

        return construct_tree(0)[0]
```
