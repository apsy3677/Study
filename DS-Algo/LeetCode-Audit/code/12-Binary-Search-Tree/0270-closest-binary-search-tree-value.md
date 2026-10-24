# 270. Closest Binary Search Tree Value

[Problem](https://leetcode.com/problems/closest-binary-search-tree-value/) · Easy · Binary Search Tree → Guided descent

LeetCode tags: binary-search, tree, depth-first-search, binary-search-tree, binary-tree

Attempts since Mar 2023: 21 · accepted: 6 · failed before first AC: 6

## Attempt 1 · 2023-11-17 03:14 IST · Wrong Answer · Python

[submission 1100371549](https://leetcode.com/submissions/detail/1100371549/) · tests 42/65

Failing input:

```text
[3,2,4,1]
4.142857
```

Expected:

```text
4
```

Your output:

```text
3
```

```python
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def closestValue(self, root, target):
        """
        :type root: TreeNode
        :type target: float
        :rtype: int
        """
        closest = root.val
        while root:
            closest = min(root.val, closest, key = lambda x: abs(target-x))

            if target< root.left:
                root = root.left
            elif target > root.left:
                root = root.right
            else:
                return root.val
        
        return closest
```

## Attempt 2 · 2023-11-17 03:14 IST · Wrong Answer · Python

[submission 1100371698](https://leetcode.com/submissions/detail/1100371698/) · tests 42/65

Failing input:

```text
[3,2,4,1]
4.142857
```

Expected:

```text
4
```

Your output:

```text
3
```

```python
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def closestValue(self, root, target):
        """
        :type root: TreeNode
        :type target: float
        :rtype: int
        """
        closest = root.val
        while root:
            closest = min(root.val, closest, key = lambda x: abs(target-x))

            if target< root.left:
                root = root.left
            else:
                root = root.right
            # else:
            #     return root.val
        
        return closest
```

## Attempt 3 · 2023-11-17 03:19 IST · Wrong Answer · Python

[submission 1100373877](https://leetcode.com/submissions/detail/1100373877/) · tests 26/65

Failing input:

```text
[1,null,2]
3.428571
```

Expected:

```text
2
```

Your output:

```text
1
```

```python
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def closestValue(self, root, target):
        """
        :type root: TreeNode
        :type target: float
        :rtype: int
        """
        closest = root.val
        while root:
            closest = min(root.val, closest, key = lambda x: abs(target-x))

            if target< root.left:
                root = root.left
            elif target > root.right:
                root = root.right
            else:
                return root.val
        
        return closest
```

## Attempt 4 · 2023-11-17 03:21 IST · Wrong Answer · Python

[submission 1100374398](https://leetcode.com/submissions/detail/1100374398/) · tests 26/65

Failing input:

```text
[1,null,2]
3.428571
```

Expected:

```text
2
```

Your output:

```text
1
```

```python
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def closestValue(self, root, target):
        """
        :type root: TreeNode
        :type target: float
        :rtype: int
        """
        closest = root.val
        while root:
            closest = min(root.val, closest, key = lambda x: abs(target-x))
            print(closest)
            if target< root.left:
                root = root.left
            elif target > root.right:
                root = root.right
            else:
                return root.val
        
        return closest
```

## Attempt 5 · 2023-11-17 03:21 IST · Wrong Answer · Python

[submission 1100374686](https://leetcode.com/submissions/detail/1100374686/) · tests 64/65

Failing input:

```text
[4,2,5,1,3]
4.5
```

Expected:

```text
4
```

Your output:

```text
5
```

```python
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def closestValue(self, root, target):
        """
        :type root: TreeNode
        :type target: float
        :rtype: int
        """
        closest = root.val
        while root:
            closest = min(root.val, closest, key = lambda x: abs(target-x))
            print(closest)
            if target< root.val:
                root = root.left
            elif target > root.val:
                root = root.right
            else:
                return root.val
        
        return closest
```

## Attempt 6 · 2023-11-17 03:22 IST · Runtime Error · Python

[submission 1100375199](https://leetcode.com/submissions/detail/1100375199/) · tests 0/65

Failing input:

```text
[4,2,5,1,3]
3.714286
```

Expected:

```text
4
```

Runtime error:

```text
NameError: global name 'x' is not defined
    closest = min(root.val, closest, key = (lambda x: abs(target-x),x))
Line 16 in closestValue (Solution.py)
    ret = Solution().closestValue(param_1, param_2)
Line 49 in _driver (Solution.py)
    _driver()
Line 59 in <module> (Solution.py)
```

```python
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def closestValue(self, root, target):
        """
        :type root: TreeNode
        :type target: float
        :rtype: int
        """
        closest = root.val
        while root:
            closest = min(root.val, closest, key = (lambda x: abs(target-x),x))
            print(closest)
            if target< root.val:
                root = root.left
            elif target > root.val:
                root = root.right
            else:
                return root.val
        
        return closest
```

## Attempt 7 · 2023-11-17 03:23 IST · Accepted · Python

[submission 1100375309](https://leetcode.com/submissions/detail/1100375309/) · tests 65/65 · runtime 31 ms (beats 7.1%)

```python
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def closestValue(self, root, target):
        """
        :type root: TreeNode
        :type target: float
        :rtype: int
        """
        closest = root.val
        while root:
            closest = min(root.val, closest, key = lambda x: (abs(target-x),x))
            print(closest)
            if target< root.val:
                root = root.left
            elif target > root.val:
                root = root.right
            else:
                return root.val
        
        return closest
```

## Attempt 8 · 2023-11-24 04:06 IST · Wrong Answer · Python3

[submission 1105116851](https://leetcode.com/submissions/detail/1105116851/) · tests 64/65

Failing input:

```text
[4,2,5,1,3]
3.5
```

Expected:

```text
3
```

Your output:

```text
4
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        closest_value = (math.inf,0)
        while root:
            if  abs(root.val - target) < closest_value[0]:
                    closest_value = (abs(root.val - target), root.val)
                
            if target == root.val:
                return root.val
            elif target < root.val:
                root= root.left
            else:
                root = root.right
        return closest_value[1]
```

## Attempt 9 · 2023-11-24 04:08 IST · Wrong Answer · Python3

[submission 1105117494](https://leetcode.com/submissions/detail/1105117494/) · tests 64/65

Failing input:

```text
[4,2,5,1,3]
4.5
```

Expected:

```text
4
```

Your output:

```text
5
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        closest_value = (math.inf,0)
        while root:
            if  abs(root.val - target) <= closest_value[0]:
                    closest_value = (abs(root.val - target), root.val)
                
            if target == root.val:
                return root.val
            elif target < root.val:
                root= root.left
            else:
                root = root.right
        return closest_value[1]
```

## Attempt 10 · 2023-11-24 04:10 IST · Wrong Answer · Python3

[submission 1105118128](https://leetcode.com/submissions/detail/1105118128/) · tests 40/65

Failing input:

```text
[1,null,2]
3.428571
```

Expected:

```text
2
```

Your output:

```text
1
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        closest_value = (math.inf,math.inf)
        while root:
            if  abs(root.val - target) <= closest_value[0] and root.val < closest_value[1]:
                    closest_value = (abs(root.val - target), root.val)
                
            if target == root.val:
                return root.val
            elif target < root.val:
                root= root.left
            else:
                root = root.right
        return closest_value[1]
```

## Attempt 11 · 2023-12-05 04:39 IST · Accepted · Python3

[submission 1112491562](https://leetcode.com/submissions/detail/1112491562/) · tests 65/65 · runtime 53 ms (beats 2.5%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        closest_value = math.inf
        while root:
            closest_value = min(root.val, closest_value, key = lambda x: (abs(target-x),x))
                
            if target == root.val:
                return root.val
            elif target < root.val:
                root= root.left
            else:
                root = root.right
        return closest_value
```

## Attempt 12 · 2023-12-05 05:42 IST · Wrong Answer · Python3

[submission 1112513924](https://leetcode.com/submissions/detail/1112513924/) · tests 62/65

Failing input:

```text
[1,null,2]
3.428571
```

Expected:

```text
2
```

Your output:

```text
1
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        closest_value = math.inf
        while root:
            closest_value = min(root.val, closest_value, key = lambda x: (abs(target-x),x))
                
            if target == root.val:
                return root.val
            elif target < root.val:
                root= root.left
            else:
                root = root.right
        return closest_value

    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        stack = []
        last = float('-inf')
        while stack or root:
            while root:
                stack.append(root)
                root = root.left
            
            root = stack.pop()
            if last <= target and target < root.val:
                return min(last, root.val, key = lambda x: abs(target-x))
                print('caompare', last, root.val)

            last = root.val
            root = root.right

        return 1
```

## Attempt 13 · 2023-12-05 05:43 IST · Accepted · Python3

[submission 1112514534](https://leetcode.com/submissions/detail/1112514534/) · tests 65/65 · runtime 49 ms (beats 2.5%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        closest_value = math.inf
        while root:
            closest_value = min(root.val, closest_value, key = lambda x: (abs(target-x),x))
                
            if target == root.val:
                return root.val
            elif target < root.val:
                root= root.left
            else:
                root = root.right
        return closest_value

    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        stack = []
        last = float('-inf')
        while stack or root:
            while root:
                stack.append(root)
                root = root.left
            
            root = stack.pop()
            if last <= target and target <= root.val:
                return min(last, root.val, key = lambda x: abs(target-x))
                print('caompare', last, root.val)

            last = root.val
            root = root.right

        return last
```

## Attempt 14 · 2024-02-04 00:26 IST · Accepted · Python3

[submission 1165155357](https://leetcode.com/submissions/detail/1165155357/) · tests 65/65 · runtime 39 ms (beats 2.5%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        closest_value = math.inf
        while root:
            closest_value = min(root.val, closest_value, key = lambda x: (abs(target-x),x))
                
            if target == root.val:
                return root.val
            elif target < root.val:
                root= root.left
            else:
                root = root.right
        return closest_value

    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        stack = []
        last = float('-inf')
        while stack or root:
            while root:
                stack.append(root)
                root = root.left
            
            root = stack.pop()
            if last <= target and target <= root.val:
                return min(last, root.val, key = lambda x: abs(target-x))
                print('caompare', last, root.val)

            last = root.val
            root = root.right

        return last


    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        if not root:
            return 0
        
        stack = []
        last = float('-inf')
        while stack or root:
            while root:
                stack.append(root)
                root = root.left

            root = stack.pop()
            if last<=target<=root.val:
                return min(last, root.val, key = lambda x: target-x)

            last = root.val
            root = root.right
        
        return -1

    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        closest = float('inf')
        def inorder(root):
            nonlocal closest
            if not root:
                return 

            inorder(root.left)
            closest = min(closest, root.val, key = lambda x: abs(target-x))
            inorder(root.right)        

        inorder(root)
        return closest
```

## Attempt 15 · 2024-02-04 00:46 IST · Wrong Answer · Python3

[submission 1165170326](https://leetcode.com/submissions/detail/1165170326/) · tests 43/65

Failing input:

```text
[1,null,8]
3.0
```

Expected:

```text
1
```

Your output:

```text
8
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        closest_value = math.inf
        while root:
            closest_value = min(root.val, closest_value, key = lambda x: (abs(target-x),x))
                
            if target == root.val:
                return root.val
            elif target < root.val:
                root= root.left
            else:
                root = root.right
        return closest_value

    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        stack = []
        last = float('-inf')
        while stack or root:
            while root:
                stack.append(root)
                root = root.left
            
            root = stack.pop()
            if last <= target and target <= root.val:
                return min(last, root.val, key = lambda x: abs(target-x))
                print('caompare', last, root.val)

            last = root.val
            root = root.right

        return last


    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        if not root:
            return 0
        
        stack = []
        last = float('-inf')
        while stack or root:
            while root:
                stack.append(root)
                root = root.left

            root = stack.pop()
            if last<=target<=root.val:
                return min(last, root.val, key = lambda x: target-x)

            last = root.val
            root = root.right
        
        return -1

    def closestValue2(self, root: Optional[TreeNode], target: float) -> int:
        closest = float('inf')
        def inorder(root):
            nonlocal closest
            if not root:
                return 

            inorder(root.left)
            closest = min(closest, root.val, key = lambda x: abs(target-x))
            inorder(root.right)        

        inorder(root)
        return closest

    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        if not root:
            return 0

        stack = []
        prev = float('-inf')
        while stack or root:
            while root:
                stack.append(root)
                root = root.left
            
            root = stack.pop()
            # check closest
            if prev<=target<=root.val:
                return min(prev, root.val, key = lambda x: (target-x))

            prev = root.val
            root = root.right

        return prev
```

## Attempt 16 · 2024-02-04 00:47 IST · Wrong Answer · Python3

[submission 1165170857](https://leetcode.com/submissions/detail/1165170857/) · tests 35/65

Failing input:

```text
[1,null,8]
3.0
```

Expected:

```text
1
```

Your output:

```text
8
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        closest_value = math.inf
        while root:
            closest_value = min(root.val, closest_value, key = lambda x: (abs(target-x),x))
                
            if target == root.val:
                return root.val
            elif target < root.val:
                root= root.left
            else:
                root = root.right
        return closest_value

    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        stack = []
        last = float('-inf')
        while stack or root:
            while root:
                stack.append(root)
                root = root.left
            
            root = stack.pop()
            if last <= target and target <= root.val:
                return min(last, root.val, key = lambda x: abs(target-x))
                print('caompare', last, root.val)

            last = root.val
            root = root.right

        return last


    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        if not root:
            return 0
        
        stack = []
        last = float('-inf')
        while stack or root:
            while root:
                stack.append(root)
                root = root.left

            root = stack.pop()
            if last<=target<=root.val:
                return min(last, root.val, key = lambda x: target-x)

            last = root.val
            root = root.right
        
        return -1

    def closestValue2(self, root: Optional[TreeNode], target: float) -> int:
        closest = float('inf')
        def inorder(root):
            nonlocal closest
            if not root:
                return 

            inorder(root.left)
            closest = min(closest, root.val, key = lambda x: abs(target-x))
            inorder(root.right)        

        inorder(root)
        return closest

    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        if not root:
            return 0

        stack = []
        prev = float('-inf')
        while stack or root:
            while root:
                stack.append(root)
                root = root.left
            
            root = stack.pop()
            # check closest
            if prev<=target<root.val:
                return min(prev, root.val, key = lambda x: (target-x))

            prev = root.val
            root = root.right

        return prev
```

## Attempt 17 · 2024-02-04 00:47 IST · Accepted · Python3

[submission 1165171041](https://leetcode.com/submissions/detail/1165171041/) · tests 65/65 · runtime 44 ms (beats 2.5%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        closest_value = math.inf
        while root:
            closest_value = min(root.val, closest_value, key = lambda x: (abs(target-x),x))
                
            if target == root.val:
                return root.val
            elif target < root.val:
                root= root.left
            else:
                root = root.right
        return closest_value

    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        stack = []
        last = float('-inf')
        while stack or root:
            while root:
                stack.append(root)
                root = root.left
            
            root = stack.pop()
            if last <= target and target <= root.val:
                return min(last, root.val, key = lambda x: abs(target-x))
                print('caompare', last, root.val)

            last = root.val
            root = root.right

        return last


    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        if not root:
            return 0
        
        stack = []
        last = float('-inf')
        while stack or root:
            while root:
                stack.append(root)
                root = root.left

            root = stack.pop()
            if last<=target<=root.val:
                return min(last, root.val, key = lambda x: target-x)

            last = root.val
            root = root.right
        
        return -1

    def closestValue2(self, root: Optional[TreeNode], target: float) -> int:
        closest = float('inf')
        def inorder(root):
            nonlocal closest
            if not root:
                return 

            inorder(root.left)
            closest = min(closest, root.val, key = lambda x: abs(target-x))
            inorder(root.right)        

        inorder(root)
        return closest

    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        if not root:
            return 0

        stack = []
        prev = float('-inf')
        while stack or root:
            while root:
                stack.append(root)
                root = root.left
            
            root = stack.pop()
            # check closest
            if prev<=target<=root.val:
                return min(prev, root.val, key = lambda x: abs(target-x))

            prev = root.val
            root = root.right

        return prev
```

## Attempt 18 · 2024-02-06 06:30 IST · Wrong Answer · Python3

[submission 1167313367](https://leetcode.com/submissions/detail/1167313367/) · tests 64/65

Failing input:

```text
[4,2,5,1,3]
4.5
```

Expected:

```text
4
```

Your output:

```text
5
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def closestValue(self, root: Optional[TreeNode], target: float) -> int:
        closest_value = math.inf
        while root:
            closest_value = min(root.val, closest_value, key = lambda x: (abs(target-x)))
                
            if target == root.val:
                return root.val
            elif target < root.val:
                root= root.left
            else:
                root = root.right
        return closest_value

    def closestValue3(self, root: Optional[TreeNode], target: float) -> int:
        stack = []
        last = float('-inf')
        while stack or root:
            while root:
                stack.append(root)
                root = root.left
            
            root = stack.pop()
            if last <= target and target <= root.val:
                return min(last, root.val, key = lambda x: abs(target-x))
                print('caompare', last, root.val)

            last = root.val
            root = root.right

        return last


    def closestValue3(self, root: Optional[TreeNode], target: float) -> int:
        if not root:
            return 0
        
        stack = []
        last = float('-inf')
        while stack or root:
            while root:
                stack.append(root)
                root = root.left

            root = stack.pop()
            if last<=target<=root.val:
                return min(last, root.val, key = lambda x: target-x)

            last = root.val
            root = root.right
        
        return -1

    def closestValue2(self, root: Optional[TreeNode], target: float) -> int:
        closest = float('inf')
        def inorder(root):
            nonlocal closest
            if not root:
                return 

            inorder(root.left)
            closest = min(closest, root.val, key = lambda x: abs(target-x))
            inorder(root.right)        

        inorder(root)
        return closest

    def closestValue3(self, root: Optional[TreeNode], target: float) -> int:
        if not root:
            return 0

        stack = []
        prev = float('-inf')
        while stack or root:
            while root:
                stack.append(root)
                root = root.left
            
            root = stack.pop()
            # check closest
            if prev<=target<=root.val:
                return min(prev, root.val, key = lambda x: abs(target-x))

            prev = root.val
            root = root.right

        return prev
```

## Attempt 19 · 2024-03-24 13:59 IST · Wrong Answer · C++

[submission 1212424797](https://leetcode.com/submissions/detail/1212424797/) · tests 6/65

Failing input:

```text
[1,null,2]
3.428571
```

Expected:

```text
2
```

Your output:

```text
1
```

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        int val, closest = root->val;

        while(!root) {
            val = root->val;
            closest = (abs(val-target)< abs(closest-target) || 
                    (abs(val-target)< abs(closest-target) && val < closest)) ?
                    val : closest ;
            root = target < root->val ? root->left : root->right ;
        }
        return closest;
    }
};
```

## Attempt 20 · 2024-03-24 14:07 IST · Wrong Answer · C++

[submission 1212429867](https://leetcode.com/submissions/detail/1212429867/) · tests 64/65

Failing input:

```text
[4,2,5,1,3]
3.5
```

Expected:

```text
3
```

Your output:

```text
4
```

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        int val, closest = root->val;

        while(root) {
            val = root->val;
            closest = (abs(val-target) < abs(closest-target) || 
                    (abs(val-target) < abs(closest-target) && val < closest)) ?
                    val : closest ;
            root = target < root->val ? root->left : root->right ;
        }
        return closest;
    }
};
```

## Attempt 21 · 2024-03-24 14:08 IST · Accepted · C++

[submission 1212430017](https://leetcode.com/submissions/detail/1212430017/) · tests 65/65 · runtime 10 ms (beats 0.4%)

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        int val, closest = root->val;

        while(root) {
            val = root->val;
            closest = (abs(val-target) < abs(closest-target) || 
                    (abs(val-target) == abs(closest-target) && val < closest)) ?
                    val : closest ;
            root = target < root->val ? root->left : root->right ;
        }
        return closest;
    }
};
```
