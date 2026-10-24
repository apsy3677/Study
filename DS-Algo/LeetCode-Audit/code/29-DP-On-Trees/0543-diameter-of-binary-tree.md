# 543. Diameter of Binary Tree

[Problem](https://leetcode.com/problems/diameter-of-binary-tree/) · Easy · DP: On Trees → Height + diameter

LeetCode tags: tree, depth-first-search, binary-tree, dp-on-trees

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-12-21 05:35 IST · Accepted · Python3

[submission 1124645907](https://leetcode.com/submissions/detail/1124645907/) · tests 105/105 · runtime 60 ms (beats 5.1%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        diameter = 0

        def dfs(root):
            nonlocal diameter
            if not root:
                return 0
            
            left = dfs(root.left)
            right = dfs(root.right)
            diameter = max(diameter, left + right )

            return max(left, right) + 1
        dfs(root)

        return diameter

    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        stack = []
        last_visited=None
        depths = {None:-1}
        max_dia = 0
        while stack or root:

            # go to leftmost
            while root:
                stack.append(root)
                root = root.left

            # peek 
            next_node = stack[-1]

            # process right if not visited
            if next_node.right and last_visited != next_node.right:
                root = next_node.right
            
            # process node
            else:
                left_depth = depths[next_node.left] +1
                right_depth = depths[next_node.right] + 1

                depths[next_node] = max(left_depth, right_depth)
                max_dia = max(max_dia, left_depth + right_depth)

                last_visited = stack.pop()
        return max_dia
```

## Attempt 2 · 2023-12-21 10:36 IST · Accepted · Python3

[submission 1124787020](https://leetcode.com/submissions/detail/1124787020/) · tests 105/105 · runtime 37 ms (beats 5.1%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        diameter = 0

        def dfs(root):
            nonlocal diameter
            if not root:
                return 0
            
            left = dfs(root.left)
            right = dfs(root.right)
            diameter = max(diameter, left + right )

            return max(left, right) + 1
        dfs(root)

        return diameter

    def diameterOfBinaryTree3(self, root: Optional[TreeNode]) -> int:
        '''
        perform post order traversal 
        find depth of left and right 

        '''
        stack = []
        last_visited=None
        depths = {None:-1}
        max_dia = 0
        # 1. while stack or root
        while stack or root:

            # 2. go to leftmost
            while root:
                stack.append(root)
                root = root.left

            # 3. peek last element on stack
            next_node = stack[-1]

            # 4. process right if not visited
            if next_node.right and last_visited != next_node.right:
                root = next_node.right
            
            # 5. process parent node now
            else:
                left_depth = depths[next_node.left] +1
                right_depth = depths[next_node.right] + 1

                depths[next_node] = max(left_depth, right_depth)
                max_dia = max(max_dia, left_depth + right_depth)

                last_visited = stack.pop()
        return max_dia


    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        stack =[]
        lastVisited = None

        depths = {None:-1}
        max_dia = 0

        while stack or root:
            #2. go to left
            while root:
                stack.append(root)
                root = root.left

            #3. peek
            node = stack[-1]

            #4. if right not processed
            if node.right and node.right != lastVisited:
                # same way process it as root
                root = node.right
            else:
                # process root
                left = depths[node.left] +1
                right = depths[node.right] +1

                depths[node] = max(left, right)
                max_dia = max(max_dia, left+ right)
                lastVisited = stack.pop()

        return max_dia
```

## Attempt 3 · 2024-02-04 01:11 IST · Accepted · Python3

[submission 1165187633](https://leetcode.com/submissions/detail/1165187633/) · tests 105/105 · runtime 39 ms (beats 5.1%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        diameter = 0

        def dfs(root):
            nonlocal diameter
            if not root:
                return 0
            
            left = dfs(root.left)
            right = dfs(root.right)
            diameter = max(diameter, left + right )

            return max(left, right) + 1
        dfs(root)

        return diameter

    def diameterOfBinaryTree3(self, root: Optional[TreeNode]) -> int:
        '''
        perform post order traversal 
        find depth of left and right 

        '''
        stack = []
        last_visited=None
        depths = {None:-1}
        max_dia = 0
        # 1. while stack or root
        while stack or root:

            # 2. go to leftmost
            while root:
                stack.append(root)
                root = root.left

            # 3. peek last element on stack
            next_node = stack[-1]

            # 4. process right if not visited
            if next_node.right and last_visited != next_node.right:
                root = next_node.right
            
            # 5. process parent node now
            else:
                left_depth = depths[next_node.left] +1
                right_depth = depths[next_node.right] + 1

                depths[next_node] = max(left_depth, right_depth)
                max_dia = max(max_dia, left_depth + right_depth)

                last_visited = stack.pop()
        return max_dia


    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        stack =[]
        lastVisited = None

        depths = {None:0}
        max_dia = 0

        while stack or root:
            #2. go to left
            while root:
                stack.append(root)
                root = root.left

            #3. peek
            node = stack[-1]

            #4. if right not processed
            if node.right and node.right != lastVisited:
                # same way process it as root
                root = node.right
            else:
                # process root
                left = depths[node.left]
                right = depths[node.right]

                depths[node] = 1+ max(left, right)
                max_dia = max(max_dia, left+ right)
                lastVisited = stack.pop()

        return max_dia
                
    def diameterOfBinaryTree3(self, root: Optional[TreeNode]) -> int:
        '''
        for each node you can decide at that node if its left and right would make a longest length
        from post order -> you will get lenght of left and right -> update longest value -> return max of either edge
        '''
        dia = 0
        def dfs(root):
            nonlocal dia
            if not root:
                return 0

            left = dfs(root.left)
            right = dfs(root.right)

            dia = max(dia, left+right)

            return max(left, right) + 1

        dfs(root)
        return dia

    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        stack = []
        lengths = {None:0}
        dia = 0
        last_visited=None
        while stack or root:
            while root:
                stack.append(root)
                root = root.left

            node = stack[-1]

            if node.right and last_visited != node.right:
                root = node.right

            else:
                left = lengths[root.left] 
                right = lengths[root.left]

                dia = max(dia, left+right)
                lengths[node] = 1 + max(left, right)

                last_visited = stack.pop()

        return dia

    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        stack = []
        last_visited = None
        lengths = {None:0}
        dia = 0
        while stack or root:
            while root:
                stack.append(root)
                root = root.left

            next_node = stack[-1]

            if next_node.right and next_node.right != last_visited:
                root = next_node.right
            else:

                lengths[next_node] = 1 + max(lengths[next_node.left], lengths[next_node.right])
                dia = max(dia, lengths[next_node.left] + lengths[next_node.right])
                last_visited = stack.pop()
        return dia
```
