# 426. Convert Binary Search Tree to Sorted Doubly Linked List

[Problem](https://leetcode.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list/) · Medium · Binary Search Tree → Inorder linking

LeetCode tags: linked-list, stack, tree, depth-first-search, binary-search-tree, binary-tree, doubly-linked-list

Attempts since Mar 2023: 6 · accepted: 3 · failed before first AC: 1

## Attempt 1 · 2023-11-23 02:11 IST · Runtime Error · Python3

[submission 1104433573](https://leetcode.com/submissions/detail/1104433573/) · tests 2/50

Failing input:

```text
[]
```

Expected:

```text
[]
```

Runtime error:

```text
AttributeError: 'NoneType' object has no attribute 'right'
    last.right = first
Line 33 in treeToDoublyList (Solution.py)
    ret = Solution().treeToDoublyList(node)
Line 111 in _driver (Solution.py)
    _driver()
Line 122 in <module> (Solution.py)
```

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
"""

class Solution:
    def treeToDoublyList(self, root: 'Optional[Node]') -> 'Optional[Node]':

        def dfs(node):
            nonlocal first, last
            if not node:
                return node

            dfs(node.left)

            #logic
            if last:
                last.right = node
                node.left = last
            else:
                first = node

            last = node
            dfs(node.right)
        
        first, last= None, None
        dfs(root)

        last.right = first
        first.left = last
        return first
```

## Attempt 2 · 2023-11-23 02:11 IST · Accepted · Python3

[submission 1104433674](https://leetcode.com/submissions/detail/1104433674/) · tests 50/50 · runtime 47 ms (beats 56.9%)

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
"""

class Solution:
    def treeToDoublyList(self, root: 'Optional[Node]') -> 'Optional[Node]':

        if not root:
            return None
        def dfs(node):
            nonlocal first, last
            if not node:
                return node

            dfs(node.left)

            #logic
            if last:
                last.right = node
                node.left = last
            else:
                first = node

            last = node
            dfs(node.right)
        
        first, last= None, None
        dfs(root)

        last.right = first
        first.left = last
        return first
```

## Attempt 3 · 2023-12-04 12:16 IST · Wrong Answer · Python3

[submission 1111980709](https://leetcode.com/submissions/detail/1111980709/) · tests 1/50

Failing input:

```text
[4,2,5,1,3]
```

Expected:

```text
[1,2,3,4,5]
```

Your output:

```text
[]
```

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
"""

class Solution:
    def treeToDoublyList1(self, root: 'Optional[Node]') -> 'Optional[Node]':

        if not root:
            return None

        # do an inorder traversal 
        # success of a node is next node in inorder traversal
        def dfs(node):
            nonlocal first, last
            # base condition
            if not node:
                return node


            dfs(node.left)

            # for the first time set first 
            # and then update last successor 
            if last:
                last.right = node
                node.left = last
            else:
                first = node

            # set last everytime to keep track of parent/successor
            last = node
            dfs(node.right)
        
        first, last= None, None
        dfs(root)

        # link first and last at end
        last.right = first
        first.left = last
        
        return first

    def treeToDoublyList(self, root: 'Optional[Node]') -> 'Optional[Node]':
        if not root:
            return None
        def morris(root):
            while root:
                print('starting',root.val) 
                if not root.left:
                    print('ans',root.val)
                    root = root.right
                else:
                    pre = root.left
                    print('found right', pre.val)
                    while pre.right:
                        print('going right', pre.right.val)
                        pre = pre.right
                    print('setting root as right')
                    pre.right = root
                    temp = root
                    root = root.left
                    print('setting left as null and root as', root.val)
                    temp.left = None
        morris(root)
```

## Attempt 4 · 2024-01-02 00:11 IST · Accepted · Python3

[submission 1133982312](https://leetcode.com/submissions/detail/1133982312/) · tests 50/50 · runtime 94 ms (beats 5.9%)

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
"""

class Solution:
    def treeToDoublyList(self, root: 'Optional[Node]') -> 'Optional[Node]':

        if not root:
            return None

        # do an inorder traversal 
        # success of a node is next node in inorder traversal
        def dfs(node):
            
            nonlocal first, last
            # base condition
            if not node:
                return node

            print('callign left on', node.val if node else None)
            dfs(node.left)

            # for the first time set first 
            # and then update last successor 
            if last:
                print('linking right and left')
                print('linking last', last.val,'setting right with', node.val)
                last.right = node
                node.left = last
            else:
                print('assigned first as', node.val)
                first = node

            
            # set last everytime to keep track of parent/successor
            last = node
            print('assigned last as', last.val)
            print('callign right on', node.val if node else None)
            dfs(node.right)
        
        first, last= None, None
        dfs(root)

        # link first and last at end
        last.right = first
        first.left = last
        
        return first

    def treeToDoublyList1(self, root: 'Optional[Node]') -> 'Optional[Node]':
        if not root:
            return None
        def morris(root):
            # you have to make root.left = None
            # if there is a left -> go to the right most -> link right to root -> then make root as root.left and assign root.left as null
            while root:
                print('starting',root.val) 

                if not root.left:
                    print('ans',root.val)
                    root = root.right
                else:
                    pre = root.left
                    print('found right', pre.val)
                    while pre.right:
                        print('going right', pre.right.val)
                        pre = pre.right
                    print('setting root as right')
                    pre.right = root
                    temp = root
                    root = root.left
                    print('setting left as null and root as', root.val)
                    temp.left = None
        morris(root)
```

## Attempt 5 · 2024-01-13 03:43 IST · Runtime Error · Python3

[submission 1144582273](https://leetcode.com/submissions/detail/1144582273/) · tests 2/50

Failing input:

```text
[]
```

Expected:

```text
[]
```

Runtime error:

```text
AttributeError: 'NoneType' object has no attribute 'left'
    ^^^^^^^^^
    head.left = prev
Line 74 in treeToDoublyList (Solution.py)
          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    ret = Solution().treeToDoublyList(node)
Line 153 in _driver (Solution.py)
    _driver()
Line 164 in <module> (Solution.py)
```

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
"""

class Solution:
    def treeToDoublyList(self, root: 'Optional[Node]') -> 'Optional[Node]':

        if not root:
            return None

        # do an inorder traversal 
        # success of a node is next node in inorder traversal
        def dfs(node):
            
            nonlocal first, last
            # base condition
            if not node:
                return node

            print('callign left on', node.val if node else None)
            dfs(node.left)

            # for the first time set first 
            # and then update last successor 
            if last:
                print('linking right and left')
                print('linking last', last.val,'setting right with', node.val)
                last.right = node
                node.left = last
            else:
                print('assigned first as', node.val)
                first = node

            
            # set last everytime to keep track of parent/successor
            last = node
            print('assigned last as', last.val)
            print('callign right on', node.val if node else None)
            dfs(node.right)
        
        first, last= None, None
        dfs(root)

        # link first and last at end
        last.right = first
        first.left = last
        
        return first

    def treeToDoublyList(self, root: 'Optional[Node]') -> 'Optional[Node]':
        stack = []
        current = root
        # inorder
        prev, head = None, None
        while stack or current:
            while current:
                stack.append(current)
                current = current.left

            current = stack.pop()

            if prev:
                prev.right = current
                current.left = prev
            else:
                head = current
            prev = current
            current = current.right
        head.left = prev
        prev.right = head

        return head
```

## Attempt 6 · 2024-01-13 03:44 IST · Accepted · Python3

[submission 1144582411](https://leetcode.com/submissions/detail/1144582411/) · tests 50/50 · runtime 32 ms (beats 99.0%)

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
"""

class Solution:
    def treeToDoublyList(self, root: 'Optional[Node]') -> 'Optional[Node]':

        if not root:
            return None

        # do an inorder traversal 
        # success of a node is next node in inorder traversal
        def dfs(node):
            
            nonlocal first, last
            # base condition
            if not node:
                return node

            print('callign left on', node.val if node else None)
            dfs(node.left)

            # for the first time set first 
            # and then update last successor 
            if last:
                print('linking right and left')
                print('linking last', last.val,'setting right with', node.val)
                last.right = node
                node.left = last
            else:
                print('assigned first as', node.val)
                first = node

            
            # set last everytime to keep track of parent/successor
            last = node
            print('assigned last as', last.val)
            print('callign right on', node.val if node else None)
            dfs(node.right)
        
        first, last= None, None
        dfs(root)

        # link first and last at end
        last.right = first
        first.left = last
        
        return first

    def treeToDoublyList(self, root: 'Optional[Node]') -> 'Optional[Node]':
        if not root:
            return None

        stack = []
        current = root
        # inorder
        prev, head = None, None
        while stack or current:
            while current:
                stack.append(current)
                current = current.left

            current = stack.pop()

            if prev:
                prev.right = current
                current.left = prev
            else:
                head = current
            prev = current
            current = current.right
        head.left = prev
        prev.right = head

        return head
```
