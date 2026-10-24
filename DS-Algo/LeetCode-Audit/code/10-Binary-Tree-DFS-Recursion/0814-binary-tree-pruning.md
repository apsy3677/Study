# 814. Binary Tree Pruning

[Problem](https://leetcode.com/problems/binary-tree-pruning/) · Medium · Binary Tree (DFS & Recursion) → Postorder prune

LeetCode tags: tree, depth-first-search, binary-tree

Attempts since Mar 2023: 11 · accepted: 1 · failed before first AC: 10

## Attempt 1 · 2023-12-31 07:53 IST · Wrong Answer · Python3

[submission 1132621142](https://leetcode.com/submissions/detail/1132621142/) · tests 29/31

Failing input:

```text
[0,null,0,0,0]
```

Expected:

```text
[]
```

Your output:

```text
[0]
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def pruneTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        '''
        when writing dfs
        assume left will have answer, right will have answer - just assume they problems are solved
        now, think about what should happen for the node with left and right 
        that is the root node will return true if either left or right or root has a 1'''
        def dfs(root):
            if not root:
                return False
            
            left = dfs(root.left)
            right = dfs(root.right)
            
            # print(root.val, left, right)
            if not left:
                root.left = None
            if not right:
                root.right=None
                
            return root.val == 1 or left or right
        
        dfs(root)
        return root
```

## Attempt 2 · 2023-12-31 07:54 IST · Runtime Error · Python3

[submission 1132621567](https://leetcode.com/submissions/detail/1132621567/) · tests 3/31

Failing input:

```text
[0,null,0,1,1,null,1,null,1,null,null,null,null]
```

Expected:

```text
[0,null,0,1,1,null,1,null,1]
```

Runtime error:

```text
TypeError: [] is not valid value for the expected return type TreeNode
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    raise TypeError(str(ret) + " is not valid value for the expected return type TreeNode");
Line 59 in _driver (Solution.py)
    _driver()
Line 66 in <module> (Solution.py)
During handling of the above exception, another exception occur ... [344 more chars]
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def pruneTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        '''
        when writing dfs
        assume left will have answer, right will have answer - just assume they problems are solved
        now, think about what should happen for the node with left and right 
        that is the root node will return true if either left or right or root has a 1'''
        
        if root and root.val !=1:
            return []
        
        def dfs(root):
            if not root:
                return False
            
            left = dfs(root.left)
            right = dfs(root.right)
            
            # print(root.val, left, right)
            if not left:
                root.left = None
            if not right:
                root.right=None
                
            return root.val == 1 or left or right
        
        dfs(root)
        return root
```

## Attempt 3 · 2023-12-31 07:54 IST · Runtime Error · Python3

[submission 1132621824](https://leetcode.com/submissions/detail/1132621824/) · tests 3/31

Failing input:

```text
[0,null,0,1,1,null,1,null,1,null,null,null,null]
```

Expected:

```text
[0,null,0,1,1,null,1,null,1]
```

Runtime error:

```text
NameError: name 'null' is not defined
            ^^^^
    return [null]
Line 16 in pruneTree (Solution.py)
          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    ret = Solution().pruneTree(param_1)
Line 55 in _driver (Solution.py)
    _driver()
Line 66 in <module> (Solution.py)
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def pruneTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        '''
        when writing dfs
        assume left will have answer, right will have answer - just assume they problems are solved
        now, think about what should happen for the node with left and right 
        that is the root node will return true if either left or right or root has a 1'''
        
        if root and root.val !=1:
            return [null]
        
        def dfs(root):
            if not root:
                return False
            
            left = dfs(root.left)
            right = dfs(root.right)
            
            # print(root.val, left, right)
            if not left:
                root.left = None
            if not right:
                root.right=None
                
            return root.val == 1 or left or right
        
        dfs(root)
        return root
```

## Attempt 4 · 2023-12-31 07:55 IST · Runtime Error · Python3

[submission 1132621943](https://leetcode.com/submissions/detail/1132621943/) · tests 3/31

Failing input:

```text
[0,null,0,1,1,null,1,null,1,null,null,null,null]
```

Expected:

```text
[0,null,0,1,1,null,1,null,1]
```

Runtime error:

```text
TypeError: [TreeNode{val: , left: None, right: None}] is not valid value for the expected return type TreeNode
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    raise TypeError(str(ret) + " is not valid value for the expected return type TreeNode");
Line 59 in _driver (Solution.py)
    _driver()
Line 66 in <module> (Solution.py)
During handling of the  ... [384 more chars]
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def pruneTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        '''
        when writing dfs
        assume left will have answer, right will have answer - just assume they problems are solved
        now, think about what should happen for the node with left and right 
        that is the root node will return true if either left or right or root has a 1'''
        
        if root and root.val !=1:
            return [TreeNode(val='')]
        
        def dfs(root):
            if not root:
                return False
            
            left = dfs(root.left)
            right = dfs(root.right)
            
            # print(root.val, left, right)
            if not left:
                root.left = None
            if not right:
                root.right=None
                
            return root.val == 1 or left or right
        
        dfs(root)
        return root
```

## Attempt 5 · 2023-12-31 07:55 IST · Runtime Error · Python3

[submission 1132622024](https://leetcode.com/submissions/detail/1132622024/) · tests 3/31

Failing input:

```text
[0,null,0,1,1,null,1,null,1,null,null,null,null]
```

Expected:

```text
[0,null,0,1,1,null,1,null,1]
```

Runtime error:

```text
TypeError: TreeNode{val: , left: None, right: None} is not valid value for the expected return type TreeNode
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    raise TypeError(str(ret) + " is not valid value for the expected return type TreeNode");
Line 59 in _driver (Solution.py)
    _driver()
Line 66 in <module> (Solution.py)
During handling of the ab ... [295 more chars]
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def pruneTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        '''
        when writing dfs
        assume left will have answer, right will have answer - just assume they problems are solved
        now, think about what should happen for the node with left and right 
        that is the root node will return true if either left or right or root has a 1'''
        
        if root and root.val !=1:
            return TreeNode(val='')
        
        def dfs(root):
            if not root:
                return False
            
            left = dfs(root.left)
            right = dfs(root.right)
            
            # print(root.val, left, right)
            if not left:
                root.left = None
            if not right:
                root.right=None
                
            return root.val == 1 or left or right
        
        dfs(root)
        return root
```

## Attempt 6 · 2023-12-31 07:55 IST · Runtime Error · Python3

[submission 1132622143](https://leetcode.com/submissions/detail/1132622143/) · tests 0/31

Failing input:

```text
[1,null,0,0,1]
```

Expected:

```text
[1,null,0,null,1]
```

Runtime error:

```text
SyntaxError: positional argument follows keyword argument
                                      ^
    return TreeNode(val='', None, None)
Line 16  (Solution.py)
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def pruneTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        '''
        when writing dfs
        assume left will have answer, right will have answer - just assume they problems are solved
        now, think about what should happen for the node with left and right 
        that is the root node will return true if either left or right or root has a 1'''
        
        if root and root.val !=1:
            return TreeNode(val='', None, None)
        
        def dfs(root):
            if not root:
                return False
            
            left = dfs(root.left)
            right = dfs(root.right)
            
            # print(root.val, left, right)
            if not left:
                root.left = None
            if not right:
                root.right=None
                
            return root.val == 1 or left or right
        
        dfs(root)
        return root
```

## Attempt 7 · 2023-12-31 07:56 IST · Wrong Answer · Python3

[submission 1132622379](https://leetcode.com/submissions/detail/1132622379/) · tests 15/31

Failing input:

```text
[0,null,0,1,1,null,1,null,1,null,null,null,null]
```

Expected:

```text
[0,null,0,1,1,null,1,null,1]
```

Your output:

```text
[0]
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def pruneTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        '''
        when writing dfs
        assume left will have answer, right will have answer - just assume they problems are solved
        now, think about what should happen for the node with left and right 
        that is the root node will return true if either left or right or root has a 1'''
        
        if root and root.val !=1:
            
            return TreeNode()
        
        def dfs(root):
            if not root:
                return False
            
            left = dfs(root.left)
            right = dfs(root.right)
            
            # print(root.val, left, right)
            if not left:
                root.left = None
            if not right:
                root.right=None
                
            return root.val == 1 or left or right
        
        dfs(root)
        return root
```

## Attempt 8 · 2023-12-31 07:56 IST · Wrong Answer · Python3

[submission 1132622540](https://leetcode.com/submissions/detail/1132622540/) · tests 29/31

Failing input:

```text
[0,null,0,0,0]
```

Expected:

```text
[]
```

Your output:

```text
[0]
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def pruneTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        '''
        when writing dfs
        assume left will have answer, right will have answer - just assume they problems are solved
        now, think about what should happen for the node with left and right 
        that is the root node will return true if either left or right or root has a 1'''
        
        if root and not root.left and not root.right and root.val !=1:
            return TreeNode()
        
        def dfs(root):
            if not root:
                return False
            
            left = dfs(root.left)
            right = dfs(root.right)
            
            # print(root.val, left, right)
            if not left:
                root.left = None
            if not right:
                root.right=None
                
            return root.val == 1 or left or right
        
        dfs(root)
        return root
```

## Attempt 9 · 2023-12-31 07:56 IST · Wrong Answer · Python3

[submission 1132622662](https://leetcode.com/submissions/detail/1132622662/) · tests 29/31

Failing input:

```text
[0,null,0,0,0]
```

Expected:

```text
[]
```

Your output:

```text
[0]
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def pruneTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        '''
        when writing dfs
        assume left will have answer, right will have answer - just assume they problems are solved
        now, think about what should happen for the node with left and right 
        that is the root node will return true if either left or right or root has a 1'''
        
        if root and not root.left and not root.right and root.val !=1:
            return TreeNode(None)
        
        def dfs(root):
            if not root:
                return False
            
            left = dfs(root.left)
            right = dfs(root.right)
            
            # print(root.val, left, right)
            if not left:
                root.left = None
            if not right:
                root.right=None
                
            return root.val == 1 or left or right
        
        dfs(root)
        return root
```

## Attempt 10 · 2023-12-31 07:57 IST · Wrong Answer · Python3

[submission 1132623294](https://leetcode.com/submissions/detail/1132623294/) · tests 29/31

Failing input:

```text
[0,null,0,0,0]
```

Expected:

```text
[]
```

Your output:

```text
[None]
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def pruneTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        '''
        when writing dfs
        assume left will have answer, right will have answer - just assume they problems are solved
        now, think about what should happen for the node with left and right 
        that is the root node will return true if either left or right or root has a 1'''
        
        
        
        def dfs(root):
            if not root:
                return False
            
            left = dfs(root.left)
            right = dfs(root.right)
            
            print(root.val, left, right)
            if not left:
                root.left = None
            if not right:
                root.right=None
                
            return root.val == 1 or left or right
        
        dfs(root)
        if root and not root.left and not root.right and root.val !=1:
            return TreeNode(None)
        return root
```

## Attempt 11 · 2023-12-31 08:02 IST · Accepted · Python3

[submission 1132625993](https://leetcode.com/submissions/detail/1132625993/) · tests 31/31 · runtime 84 ms (beats 0.8%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def pruneTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        '''
        when writing dfs
        assume left will have answer, right will have answer - just assume they problems are solved
        now, think about what should happen for the node with left and right 
        that is the root node will return true if either left or right or root has a 1'''
        
        
        
        def dfs(root):
            if not root:
                return False
            
            left = dfs(root.left)
            right = dfs(root.right)
            
            # print(root.val, left, right)
            if not left:
                root.left = None
            if not right:
                root.right=None
                
            return root.val == 1 or left or right
        
        dfs(root)
        return root if dfs(root) else None
```
