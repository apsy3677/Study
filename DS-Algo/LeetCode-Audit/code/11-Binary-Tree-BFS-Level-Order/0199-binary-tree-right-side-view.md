# 199. Binary Tree Right Side View

[Problem](https://leetcode.com/problems/binary-tree-right-side-view/) · Medium · Binary Tree (BFS / Level Order) → Last node per level

LeetCode tags: tree, depth-first-search, breadth-first-search, binary-tree

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-11-15 21:25 IST · Accepted · Python3

[submission 1099466326](https://leetcode.com/submissions/detail/1099466326/) · tests 216/216 · runtime 35 ms (beats 0.5%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def rightSideView(self, root: Optional[TreeNode]) -> List[int]:
        if not root:
            return []

        result = []
        queue = deque([root])

        while queue:
            size = len(queue)
            for i in range(size):
                root = queue.popleft()
                if i ==0:
                    result.append(root.val)
                if root.right:
                    queue.append(root.right)
                if root.left:
                    queue.append(root.left)
        return result
```

## Attempt 2 · 2023-12-05 00:40 IST · Accepted · Python3

[submission 1112385693](https://leetcode.com/submissions/detail/1112385693/) · tests 216/216 · runtime 44 ms (beats 0.5%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def rightSideView(self, root: Optional[TreeNode]) -> List[int]:
        '''
        approach 1 BFS traversal - 
        worst case in space - width/diameter of tree - complete tree
        traverse and add nodes from right and then put condition to check index =0


        DFS - traverse rightmost first and keep a reuslt for each level
        worst case space - skewed tree - heigh of tree
        when len(nodes) == level: append
        '''
        if not root:
            return []

        queue = deque([root])
        result = []
        while queue:
            
            n = len(queue)
            for i in range(n):
                node = queue.popleft()
                if i == 0:
                    result.append(node.val)
                
                if node.right:
                    queue.append(node.right)
                if node.left:
                    queue.append(node.left)

        return result



    def rightSideViewDFS(self, root: Optional[TreeNode]) -> List[int]:
        if not root:
            return []

        righViewNodes = []
        def dfs(root, depth):
            if not root:
                return 

            if depth == len(righViewNodes):
                righViewNodes.append(root.val)

            dfs(root.right, depth+1)
            dfs(root.left, depth+1)

        dfs(root, 0)
        return righViewNodes
```

## Attempt 3 · 2024-01-22 01:45 IST · Accepted · Python3

[submission 1152935407](https://leetcode.com/submissions/detail/1152935407/) · tests 216/216 · runtime 35 ms (beats 0.5%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def rightSideView(self, root: Optional[TreeNode]) -> List[int]:
        '''
        approach 1 BFS traversal - 
        worst case in space - width/diameter of tree - complete tree
        traverse and add nodes from right and then put condition to check index =0


        DFS - traverse rightmost first and keep a reuslt for each level
        worst case space - skewed tree - heigh of tree
        when len(nodes) == level: append
        '''
        if not root:
            return []

        queue = deque([root])
        result = []
        while queue:
            
            n = len(queue)
            for i in range(n):
                node = queue.popleft()
                if i == 0:
                    result.append(node.val)
                
                if node.right:
                    queue.append(node.right)
                if node.left:
                    queue.append(node.left)

        return result



    def rightSideViewDFS(self, root: Optional[TreeNode]) -> List[int]:
        if not root:
            return []

        righViewNodes = []
        def dfs(root, depth):
            if not root:
                return 

            if depth == len(righViewNodes):
                righViewNodes.append(root.val)

            dfs(root.right, depth+1)
            dfs(root.left, depth+1)

        dfs(root, 0)
        return righViewNodes

    def rightSideView(self, root: Optional[TreeNode]) -> List[int]:
        if not root:
            return []
        queue = deque([root])
        result = []
        while queue:
            
            for i in range(len(queue)):
                root = queue.popleft()
                
                if i ==0:
                    result.append(root.val)
                
                if root.right:
                    queue.append(root.right)

                if root.left:
                    queue.append(root.left)
        return result
```
