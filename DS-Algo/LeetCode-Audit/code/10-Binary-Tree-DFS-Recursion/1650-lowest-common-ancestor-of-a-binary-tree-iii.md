# 1650. Lowest Common Ancestor of a Binary Tree III

[Problem](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iii/) · Medium · Binary Tree (DFS & Recursion) → Parent pointers, two-pointer

LeetCode tags: hash-table, two-pointers, tree, binary-tree, binary-lifting, lowest-common-ancestor

Attempts since Mar 2023: 4 · accepted: 4 · failed before first AC: 0

## Attempt 1 · 2023-11-21 21:26 IST · Accepted · Python3

[submission 1103550089](https://leetcode.com/submissions/detail/1103550089/) · tests 31/31 · runtime 62 ms (beats 47.8%)

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
        self.parent = None
"""

class Solution:
    def lowestCommonAncestor(self, p: 'Node', q: 'Node') -> 'Node':
        l1 = p
        l2 = q

        #' path is X+Y+Z '
        while l1!= l2:
            l1 = l1.parent if l1 else q
            l2 = l2.parent if l2 else p

        return l1
```

## Attempt 2 · 2023-12-04 11:01 IST · Accepted · Python3

[submission 1111939118](https://leetcode.com/submissions/detail/1111939118/) · tests 31/31 · runtime 47 ms (beats 99.1%)

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
        self.parent = None
"""

class Solution:
    def lowestCommonAncestor(self, p: 'Node', q: 'Node') -> 'Node':
        
        '''
        when parent pointer is given 

        approach 1 : find ancetors of p 
        then find ancesort of q and if any parent is in ancestors of p return
        time O(H) to find ancestors of p and then same for q
        space - O(H)

        approach 2 - lets say p is extra x steps below q 
        then q has to traverse extra x steps for steps same as p and q 
        1. find depth(p) , depth(q)
        2. traverse dpeth(p) - depth of q for both
        3. then traverse equally unless p!=q
        
        '''
        ancestors = set()
        while p:
           ancestors.add(p)
           p = p.parent

        while q and q not in ancestors:
            q = q.parent

        return q
```

## Attempt 3 · 2023-12-04 11:14 IST · Accepted · Python3

[submission 1111946116](https://leetcode.com/submissions/detail/1111946116/) · tests 31/31 · runtime 73 ms (beats 5.7%)

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
        self.parent = None
"""

class Solution:
    def lowestCommonAncestor1(self, p: 'Node', q: 'Node') -> 'Node':
        
        '''
        when parent pointer is given 

        approach 1 : find ancetors of p 
        then find ancesort of q and if any parent is in ancestors of p return
        time O(H) to find ancestors of p and then same for q
        space - O(H)

        approach 2 - lets say p is extra x steps below q 
        then q has to traverse extra x steps for steps same as p and q 
        1. find depth(p) , depth(q)
        2. traverse dpeth(p) - depth of q for both
        3. then traverse equally unless p!=q
        
        '''
        ancestors = set()
        while p:
           ancestors.add(p)
           p = p.parent

        while q and q not in ancestors:
            q = q.parent

        return q

    def lowestCommonAncestor3(self, p: 'Node', q: 'Node') -> 'Node':

        def depth(node):
            depth = 0
            while node:
                node = node.parent
                depth+=1
            return depth

        p_depth = depth(p)
        q_depth = depth(q)

        print(p_depth, q_depth)
        for i in range(p_depth-q_depth):
            p = p.parent

        for i in range(q_depth-p_depth):
            q = q.parent

        print(p.val, q.val)

        while p and q and p!=q:
            p = p.parent
            q = q.parent

        return p

    def lowestCommonAncestor(self, p: 'Node', q: 'Node') -> 'Node':

        l1 = p
        l2 = q

        while l1!=l2:
            l1 = l1.parent if l1 else q
            l2 = l2.parent if l2 else p
        
        return l1
```

## Attempt 4 · 2024-01-12 22:15 IST · Accepted · Python3

[submission 1144374104](https://leetcode.com/submissions/detail/1144374104/) · tests 31/31 · runtime 52 ms (beats 93.3%)

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
        self.parent = None
"""

class Solution:
    def lowestCommonAncestor1(self, p: 'Node', q: 'Node') -> 'Node':
        
        '''
        when parent pointer is given 

        approach 1 : find ancetors of p 
        then find ancesort of q and if any parent is in ancestors of p return
        time O(H) to find ancestors of p and then same for q
        space - O(H)

        approach 2 - lets say p is extra x steps below q 
        then q has to traverse extra x steps for steps same as p and q 
        1. find depth(p) , depth(q)
        2. traverse dpeth(p) - depth of q for both
        3. then traverse equally unless p!=q
        
        '''
        ancestors = set()
        while p:
           ancestors.add(p)
           p = p.parent

        while q and q not in ancestors:
            q = q.parent

        return q

    def lowestCommonAncestor3(self, p: 'Node', q: 'Node') -> 'Node':

        def depth(node):
            depth = 0
            while node:
                node = node.parent
                depth+=1
            return depth

        p_depth = depth(p)
        q_depth = depth(q)

        print(p_depth, q_depth)
        for i in range(p_depth-q_depth):
            p = p.parent

        for i in range(q_depth-p_depth):
            q = q.parent

        print(p.val, q.val)

        while p and q and p!=q:
            p = p.parent
            q = q.parent

        return p

    def lowestCommonAncestor(self, p: 'Node', q: 'Node') -> 'Node':

        l1 = p
        l2 = q

        while l1!=l2:
            l1 = l1.parent if l1.parent else q
            l2 = l2.parent if l2.parent else p
        
        return l1
```
