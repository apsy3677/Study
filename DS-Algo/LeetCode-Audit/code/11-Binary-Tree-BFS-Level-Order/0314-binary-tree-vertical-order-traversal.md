# 314. Binary Tree Vertical Order Traversal

[Problem](https://leetcode.com/problems/binary-tree-vertical-order-traversal/) · Medium · Binary Tree (BFS / Level Order) → Column BFS

LeetCode tags: hash-table, tree, depth-first-search, breadth-first-search, sorting, binary-tree

Attempts since Mar 2023: 4 · accepted: 2 · failed before first AC: 1

## Attempt 1 · 2023-07-12 22:20 IST · Wrong Answer · Python3

[submission 992832751](https://leetcode.com/submissions/detail/992832751/) · tests 213/214

Failing input:

```text
[]
```

Expected:

```text
[]
```

Your output:

```text
[[]]
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right


class Solution:
    def verticalOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        queue = deque([(root,0)])
        result = defaultdict(list)

        minCol = maxCol = 0

        while queue:
            node, column = queue.popleft()

            if node is not None:
                result[column].append(node.val)
                
                minCol = min(column, minCol)
                maxCol = max(column, maxCol)

                queue.append((node.left, column-1))
                queue.append((node.right, column+1))

        return [result[x] for x in range(minCol, maxCol+1)]
```

## Attempt 2 · 2023-07-12 22:21 IST · Accepted · Python3

[submission 992833046](https://leetcode.com/submissions/detail/992833046/) · tests 214/214 · runtime 47 ms (beats 0.1%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right


class Solution:
    def verticalOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        if root is None:
            return []
        queue = deque([(root,0)])
        result = defaultdict(list)

        minCol = maxCol = 0

        while queue:
            node, column = queue.popleft()

            if node is not None:
                result[column].append(node.val)
                
                minCol = min(column, minCol)
                maxCol = max(column, maxCol)

                queue.append((node.left, column-1))
                queue.append((node.right, column+1))

        return [result[x] for x in range(minCol, maxCol+1)]
```

## Attempt 3 · 2023-12-04 09:29 IST · Wrong Answer · Python3

[submission 1111891986](https://leetcode.com/submissions/detail/1111891986/) · tests 213/214

Failing input:

```text
[]
```

Expected:

```text
[]
```

Your output:

```text
[[]]
```

```python


        
        

        

class Solution:
    def verticalOrder6(self, root: Optional[TreeNode]) -> List[List[int]]:
        ## ensures vertical ordering - level order BFS - one level aft erother 
        ## so no need to take care of row level and you have to take care of col order 
        ## which is handled by mincol and maxcol
        ## time complexity 

        # if you don't do the min max logic, you would need sorted(columnTable.keyss())
        # which would take O(N Log N) because for worst case - each node has left node that means there is one element in each column and you sort N otherwise it is W log W - which is width or number of cols
        # SPACE complexity - columnTable N nodes and queue two level of nodes - O(N)


        # 1. handle empty node
        if root is None:
            return []

        #2. set queue and visited
        # this ensures that you can do all validations and updates before and after enque in loop
        # put root and column - no row 
        queue = deque([(root,0)])
        result = defaultdict(list)

        minCol = maxCol = 0


        while queue:
            node, column = queue.popleft()

            #3. if not none then add it 
            if node is not None:
                result[column].append(node.val)
                
                minCol = min(column, minCol)
                maxCol = max(column, maxCol)


                #4. process left first for left to right
                queue.append((node.left, column-1))
                queue.append((node.right, column+1))


        # 5. return all results
        return [result[x] for x in range(minCol, maxCol+1)]




    def verticalOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        ## BFS traversal provides the row ordering because of level traversal
        # but dfs doesn't have row ordereing so we need to keep track of row and later sort

        # time complexity - since for each col we need to sort nodes in that col
        # maximum number of nodes in column would be when we have zigzag pattern
        # so total complexity is W * H LOG H

        # here you sort on the height level and in BFS witout min max you sort on the width level


        nodeList = defaultdict(list)
        minCol = maxCol = 0
        
        def dfs(node, row, col):
            nonlocal minCol, maxCol
            if not node:
                return 


            minCol = min(minCol, col)
            maxCol = max(maxCol, col)
                
            nodeList[col].append((row, node.val))
            
            dfs(node.left, row+1,  col-1)
            dfs(node.right, row+1, col+1)

        dfs(root, 0, 0)
        
        output = []
        for col in range(minCol, maxCol+1):
            nodeList[col].sort(key = lambda x:x[0])
            output.append([val for row, val in nodeList[col]])
            
        return output
```

## Attempt 4 · 2023-12-04 09:29 IST · Accepted · Python3

[submission 1111892126](https://leetcode.com/submissions/detail/1111892126/) · tests 214/214 · runtime 37 ms (beats 0.1%)

```python


        
        

        

class Solution:
    def verticalOrder6(self, root: Optional[TreeNode]) -> List[List[int]]:
        ## ensures vertical ordering - level order BFS - one level aft erother 
        ## so no need to take care of row level and you have to take care of col order 
        ## which is handled by mincol and maxcol
        ## time complexity 

        # if you don't do the min max logic, you would need sorted(columnTable.keyss())
        # which would take O(N Log N) because for worst case - each node has left node that means there is one element in each column and you sort N otherwise it is W log W - which is width or number of cols
        # SPACE complexity - columnTable N nodes and queue two level of nodes - O(N)


        # 1. handle empty node
        if root is None:
            return []

        #2. set queue and visited
        # this ensures that you can do all validations and updates before and after enque in loop
        # put root and column - no row 
        queue = deque([(root,0)])
        result = defaultdict(list)

        minCol = maxCol = 0


        while queue:
            node, column = queue.popleft()

            #3. if not none then add it 
            if node is not None:
                result[column].append(node.val)
                
                minCol = min(column, minCol)
                maxCol = max(column, maxCol)


                #4. process left first for left to right
                queue.append((node.left, column-1))
                queue.append((node.right, column+1))


        # 5. return all results
        return [result[x] for x in range(minCol, maxCol+1)]




    def verticalOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        ## BFS traversal provides the row ordering because of level traversal
        # but dfs doesn't have row ordereing so we need to keep track of row and later sort

        # time complexity - since for each col we need to sort nodes in that col
        # maximum number of nodes in column would be when we have zigzag pattern
        # so total complexity is W * H LOG H

        # here you sort on the height level and in BFS witout min max you sort on the width level
        
        if not root:
            return []

        nodeList = defaultdict(list)
        minCol = maxCol = 0
        
        def dfs(node, row, col):
            nonlocal minCol, maxCol
            if not node:
                return 


            minCol = min(minCol, col)
            maxCol = max(maxCol, col)
                
            nodeList[col].append((row, node.val))
            
            dfs(node.left, row+1,  col-1)
            dfs(node.right, row+1, col+1)

        dfs(root, 0, 0)
        
        output = []
        for col in range(minCol, maxCol+1):
            nodeList[col].sort(key = lambda x:x[0])
            output.append([val for row, val in nodeList[col]])
            
        return output
```
