# 129. Sum Root to Leaf Numbers

[Problem](https://leetcode.com/problems/sum-root-to-leaf-numbers/) · Medium · Binary Tree (DFS & Recursion) → Path number DFS

LeetCode tags: tree, depth-first-search, binary-tree

Attempts since Mar 2023: 11 · accepted: 9 · failed before first AC: 2

## Attempt 1 · 2023-11-13 22:13 IST · Runtime Error · Python3

[submission 1098027197](https://leetcode.com/submissions/detail/1098027197/) · tests 0/108

Failing input:

```text
[1,2,3]
```

Expected:

```text
25
```

Runtime error:

```text
TypeError: None is not valid value for the expected return type integer
    raise TypeError(str(ret) + " is not valid value for the expected return type integer");
Line 37 in _driver (Solution.py)
    _driver()
Line 44 in <module> (Solution.py)
During handling of the above exception, another exception occurred:
TypeError: '<' not supported between instances of 'int' and 'NoneType'
Line 14 in _seri ... [165 more chars]
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        def dfs(root, root_to_leaf):
            if not root:
                return 0
            
            root_to_leaf += root.val
```

## Attempt 2 · 2023-11-22 02:58 IST · Runtime Error · Python3

[submission 1103750814](https://leetcode.com/submissions/detail/1103750814/) · tests 0/108

Failing input:

```text
[1,2,3]
```

Expected:

```text
25
```

Runtime error:

```text
TypeError: None is not valid value for the expected return type integer
    raise TypeError(str(ret) + " is not valid value for the expected return type integer");
Line 41 in _driver (Solution.py)
    _driver()
Line 48 in <module> (Solution.py)
During handling of the above exception, another exception occurred:
TypeError: '<' not supported between instances of 'int' and 'NoneType'
Line 14 in _seri ... [165 more chars]
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        def dfs(root, num, total):
            if not root:
                return 

            num = num * 10 + root.val
```

## Attempt 3 · 2023-12-02 02:20 IST · Accepted · Python3

[submission 1110454760](https://leetcode.com/submissions/detail/1110454760/) · tests 108/108 · runtime 38 ms (beats 0.2%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        def dfs(root, num):
            if not root:
                return 0

            num = num * 10 + root.val

            if not root.left and not root.right:
                return num

            return dfs(root.left, num) + dfs(root.right, num)

        total = 0
        def dfs1(root, num):
            nonlocal total
            if not root:
                return  0

            num = num * 10 + root.val
            if not root.left and not root.right:
                return num
            
            
            return dfs1(root.left, num) + dfs1(root.right, num)
        
        return dfs1(root,0)
```

## Attempt 4 · 2023-12-04 23:53 IST · Accepted · Python3

[submission 1112356748](https://leetcode.com/submissions/detail/1112356748/) · tests 108/108 · runtime 41 ms (beats 0.2%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        def dfs(root, current_number):
            '''
            do a preorder traversal 
            NOTE - always think of what do you want to return from leaf and from the node with children 

            for the leaf node return the current number so far
            for the root node with childrens - add left number + right number
            '''
            if not root:
                return 0

            current_number = current_number * 10 + root.val

            if not root.left and not root.right:
                return current_number

            return dfs(root.left, current_number) + dfs(root.right, current_number)

        return dfs(root, 0)
    
    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        
        stack = [(root, 0)]
        total = 0

        while stack:
            root, current_number = stack.pop()
            
            if root:
                current_number = current_number * 10 + root.val

                if not (root.left) and not root.right:
                    total += current_number
                
                else:
                    stack.append((root.left, current_number))
                    stack.append((root.right, current_number))
        return total
```

## Attempt 5 · 2024-01-14 04:39 IST · Accepted · Python3

[submission 1145425746](https://leetcode.com/submissions/detail/1145425746/) · runtime 43 ms

_Code not returned by LeetCode._

## Attempt 6 · 2024-02-06 05:23 IST · Accepted · Python3

[submission 1167280079](https://leetcode.com/submissions/detail/1167280079/) · tests 108/108 · runtime 33 ms (beats 0.2%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        def dfs(root, current_number):
            '''
            do a preorder traversal 
            NOTE - always think of what do you want to return from leaf and from the node with children 

            for the leaf node return the current number so far
            for the root node with childrens - add left number + right number
            '''
            if not root:
                return 0

            current_number = current_number * 10 + root.val

            if not root.left and not root.right:
                return current_number

            return dfs(root.left, current_number) + dfs(root.right, current_number)

        return dfs(root, 0)
    
    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        
        stack = [(root, 0)]
        total = 0

        while stack:
            root, current_number = stack.pop()
            
            if root:
                current_number = current_number * 10 + root.val

                if not (root.left) and not root.right:
                    total += current_number
                
                else:
                    stack.append((root.left, current_number))
                    stack.append((root.right, current_number))
        return total


    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        def dfs(root, current_number):
            if not root:
                return 

            # coming dowing and traversing
            current_number = current_number*10 + root.val

            if not(root.left) and not(root.right):
                return current_number

            left = dfs(root.left, current_number)
            right = dfs(root.right, current_number)

            print(root.val, left,right)

            # while going back 
            return left + right

        return dfs(root,0)

    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        total = 0
        def dfs(root, num):
            nonlocal total 
            # for empty node - children of leaf
            if not root:
                return 0

            # go on building number as you go down
            num = num * 10 + root.val

            # for leaf node different return
            if not root.left and not root.right:
                print(root.val, num)
                total += num
                return num

            left = dfs(root.left, num)
            right = dfs(root.right, num )

            # print(root.val, left+right)
            return left + right

        dfs(root, 0)
        return total

    
    def sumNumbers3(self, root: TreeNode):
        root_to_leaf = 0
        stack = [(root, 0) ]
        
        while stack:
            root, curr_number = stack.pop()
            if root is not None:
                curr_number = curr_number * 10 + root.val
                # if it's a leaf, update root-to-leaf sum
                if root.left is None and root.right is None:
                    root_to_leaf += curr_number
                    print(root.val, curr_number)
                else:
                    stack.append((root.right, curr_number))
                    stack.append((root.left, curr_number))
                        
        return root_to_leaf
            
    def sumNumbers3(self, root: Optional[TreeNode]) -> int:
        stack = [(root,0)]
        total = 0
        while stack:
            root, current_number = stack.pop()
            current_number = current_number * 10 + root.val
            if not root.left and not root.right:
                total += current_number

            if root.left:
                stack.append((root.left, current_number))
            if root.right:
                stack.append((root.right, current_number))

        return total
```

## Attempt 7 · 2024-02-06 05:23 IST · Accepted · Python3

[submission 1167280195](https://leetcode.com/submissions/detail/1167280195/) · tests 108/108 · runtime 28 ms (beats 0.2%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        def dfs(root, current_number):
            '''
            do a preorder traversal 
            NOTE - always think of what do you want to return from leaf and from the node with children 

            for the leaf node return the current number so far
            for the root node with childrens - add left number + right number
            '''
            if not root:
                return 0

            current_number = current_number * 10 + root.val

            if not root.left and not root.right:
                return current_number

            return dfs(root.left, current_number) + dfs(root.right, current_number)

        return dfs(root, 0)
    
    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        
        stack = [(root, 0)]
        total = 0

        while stack:
            root, current_number = stack.pop()
            
            if root:
                current_number = current_number * 10 + root.val

                if not (root.left) and not root.right:
                    total += current_number
                
                else:
                    stack.append((root.left, current_number))
                    stack.append((root.right, current_number))
        return total


    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        def dfs(root, current_number):
            if not root:
                return 

            # coming dowing and traversing
            current_number = current_number*10 + root.val

            if not(root.left) and not(root.right):
                return current_number

            left = dfs(root.left, current_number)
            right = dfs(root.right, current_number)

            print(root.val, left,right)

            # while going back 
            return left + right

        return dfs(root,0)

    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        total = 0
        def dfs(root, num):
            nonlocal total 
            # for empty node - children of leaf
            if not root:
                return 0

            # go on building number as you go down
            num = num * 10 + root.val

            # for leaf node different return
            if not root.left and not root.right:
                print(root.val, num)
                total += num
                return num

            left = dfs(root.left, num)
            right = dfs(root.right, num )

            # print(root.val, left+right)
            # return le ft + right

        dfs(root, 0)
        return total

    
    def sumNumbers3(self, root: TreeNode):
        root_to_leaf = 0
        stack = [(root, 0) ]
        
        while stack:
            root, curr_number = stack.pop()
            if root is not None:
                curr_number = curr_number * 10 + root.val
                # if it's a leaf, update root-to-leaf sum
                if root.left is None and root.right is None:
                    root_to_leaf += curr_number
                    print(root.val, curr_number)
                else:
                    stack.append((root.right, curr_number))
                    stack.append((root.left, curr_number))
                        
        return root_to_leaf
            
    def sumNumbers3(self, root: Optional[TreeNode]) -> int:
        stack = [(root,0)]
        total = 0
        while stack:
            root, current_number = stack.pop()
            current_number = current_number * 10 + root.val
            if not root.left and not root.right:
                total += current_number

            if root.left:
                stack.append((root.left, current_number))
            if root.right:
                stack.append((root.right, current_number))

        return total
```

## Attempt 8 · 2024-02-06 05:23 IST · Accepted · Python3

[submission 1167280238](https://leetcode.com/submissions/detail/1167280238/) · tests 108/108 · runtime 36 ms (beats 0.2%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        def dfs(root, current_number):
            '''
            do a preorder traversal 
            NOTE - always think of what do you want to return from leaf and from the node with children 

            for the leaf node return the current number so far
            for the root node with childrens - add left number + right number
            '''
            if not root:
                return 0

            current_number = current_number * 10 + root.val

            if not root.left and not root.right:
                return current_number

            return dfs(root.left, current_number) + dfs(root.right, current_number)

        return dfs(root, 0)
    
    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        
        stack = [(root, 0)]
        total = 0

        while stack:
            root, current_number = stack.pop()
            
            if root:
                current_number = current_number * 10 + root.val

                if not (root.left) and not root.right:
                    total += current_number
                
                else:
                    stack.append((root.left, current_number))
                    stack.append((root.right, current_number))
        return total


    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        def dfs(root, current_number):
            if not root:
                return 

            # coming dowing and traversing
            current_number = current_number*10 + root.val

            if not(root.left) and not(root.right):
                return current_number

            left = dfs(root.left, current_number)
            right = dfs(root.right, current_number)

            print(root.val, left,right)

            # while going back 
            return left + right

        return dfs(root,0)

    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        total = 0
        def dfs(root, num):
            nonlocal total 
            # for empty node - children of leaf
            if not root:
                return 0

            # go on building number as you go down
            num = num * 10 + root.val

            # for leaf node different return
            if not root.left and not root.right:
                # print(root.val, num)
                total += num
                return num

            left = dfs(root.left, num)
            right = dfs(root.right, num )

            # print(root.val, left+right)
            # return le ft + right

        dfs(root, 0)
        return total

    
    def sumNumbers3(self, root: TreeNode):
        root_to_leaf = 0
        stack = [(root, 0) ]
        
        while stack:
            root, curr_number = stack.pop()
            if root is not None:
                curr_number = curr_number * 10 + root.val
                # if it's a leaf, update root-to-leaf sum
                if root.left is None and root.right is None:
                    root_to_leaf += curr_number
                    print(root.val, curr_number)
                else:
                    stack.append((root.right, curr_number))
                    stack.append((root.left, curr_number))
                        
        return root_to_leaf
            
    def sumNumbers3(self, root: Optional[TreeNode]) -> int:
        stack = [(root,0)]
        total = 0
        while stack:
            root, current_number = stack.pop()
            current_number = current_number * 10 + root.val
            if not root.left and not root.right:
                total += current_number

            if root.left:
                stack.append((root.left, current_number))
            if root.right:
                stack.append((root.right, current_number))

        return total
```

## Attempt 9 · 2024-02-06 05:23 IST · Accepted · Python3

[submission 1167280282](https://leetcode.com/submissions/detail/1167280282/) · tests 108/108 · runtime 36 ms (beats 0.2%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        def dfs(root, current_number):
            '''
            do a preorder traversal 
            NOTE - always think of what do you want to return from leaf and from the node with children 

            for the leaf node return the current number so far
            for the root node with childrens - add left number + right number
            '''
            if not root:
                return 0

            current_number = current_number * 10 + root.val

            if not root.left and not root.right:
                return current_number

            return dfs(root.left, current_number) + dfs(root.right, current_number)

        return dfs(root, 0)
    
    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        
        stack = [(root, 0)]
        total = 0

        while stack:
            root, current_number = stack.pop()
            
            if root:
                current_number = current_number * 10 + root.val

                if not (root.left) and not root.right:
                    total += current_number
                
                else:
                    stack.append((root.left, current_number))
                    stack.append((root.right, current_number))
        return total


    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        def dfs(root, current_number):
            if not root:
                return 

            # coming dowing and traversing
            current_number = current_number*10 + root.val

            if not(root.left) and not(root.right):
                return current_number

            left = dfs(root.left, current_number)
            right = dfs(root.right, current_number)

            print(root.val, left,right)

            # while going back 
            return left + right

        return dfs(root,0)

    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        total = 0
        def dfs(root, num):
            nonlocal total 
            # for empty node - children of leaf
            if not root:
                return 0

            # go on building number as you go down
            num = num * 10 + root.val

            # for leaf node different return
            if not root.left and not root.right:
                # print(root.val, num)
                total += num
                return num

            left = dfs(root.left, num)
            right = dfs(root.right, num )

            # print(root.val, left+right)
            # return le ft + right

        dfs(root, 0)
        return total

    
    def sumNumbers3(self, root: TreeNode):
        root_to_leaf = 0
        stack = [(root, 0) ]
        
        while stack:
            root, curr_number = stack.pop()
            if root is not None:
                curr_number = curr_number * 10 + root.val
                # if it's a leaf, update root-to-leaf sum
                if root.left is None and root.right is None:
                    root_to_leaf += curr_number
                    print(root.val, curr_number)
                else:
                    stack.append((root.right, curr_number))
                    stack.append((root.left, curr_number))
                        
        return root_to_leaf
            
    def sumNumbers3(self, root: Optional[TreeNode]) -> int:
        stack = [(root,0)]
        total = 0
        while stack:
            root, current_number = stack.pop()
            current_number = current_number * 10 + root.val
            if not root.left and not root.right:
                total += current_number

            if root.left:
                stack.append((root.left, current_number))
            if root.right:
                stack.append((root.right, current_number))

        return total
```

## Attempt 10 · 2024-02-10 01:09 IST · Accepted · Python3

[submission 1170901525](https://leetcode.com/submissions/detail/1170901525/) · tests 108/108 · runtime 37 ms (beats 0.2%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        def dfs(root, current_number):
            '''
            do a preorder traversal 
            NOTE - always think of what do you want to return from leaf and from the node with children 

            for the leaf node return the current number so far
            for the root node with childrens - add left number + right number
            '''
            if not root:
                return 0

            current_number = current_number * 10 + root.val

            if not root.left and not root.right:
                return current_number

            return dfs(root.left, current_number) + dfs(root.right, current_number)

        return dfs(root, 0)
    
    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        
        stack = [(root, 0)]
        total = 0

        while stack:
            root, current_number = stack.pop()
            
            if root:
                current_number = current_number * 10 + root.val

                if not (root.left) and not root.right:
                    total += current_number
                
                else:
                    stack.append((root.left, current_number))
                    stack.append((root.right, current_number))
        return total


    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        def dfs(root, current_number):
            if not root:
                return 

            # coming dowing and traversing
            current_number = current_number*10 + root.val

            if not(root.left) and not(root.right):
                return current_number

            left = dfs(root.left, current_number)
            right = dfs(root.right, current_number)

            print(root.val, left,right)

            # while going back 
            return left + right

        return dfs(root,0)

    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        total = 0
        def dfs(root, num):
            nonlocal total 
            # for empty node - children of leaf
            if not root:
                return 0

            # go on building number as you go down
            num = num * 10 + root.val


            left = dfs(root.left, num)
            right = dfs(root.right, num )
            # for leaf node different return
            if not root.left and not root.right:
                print(root.val, num)
                total += num
                return num


            # print(root.val, left+right)
            # return le ft + right

        dfs(root, 0)
        return total

    
    def sumNumbers3(self, root: TreeNode):
        root_to_leaf = 0
        stack = [(root, 0) ]
        
        while stack:
            root, curr_number = stack.pop()
            if root is not None:
                curr_number = curr_number * 10 + root.val
                # if it's a leaf, update root-to-leaf sum
                if root.left is None and root.right is None:
                    root_to_leaf += curr_number
                    print(root.val, curr_number)
                else:
                    stack.append((root.right, curr_number))
                    stack.append((root.left, curr_number))
                        
        return root_to_leaf
            
    def sumNumbers3(self, root: Optional[TreeNode]) -> int:
        stack = [(root,0)]
        total = 0
        while stack:
            root, current_number = stack.pop()
            current_number = current_number * 10 + root.val
            if not root.left and not root.right:
                total += current_number

            if root.left:
                stack.append((root.left, current_number))
            if root.right:
                stack.append((root.right, current_number))

        return total
```

## Attempt 11 · 2025-06-14 22:01 IST · Accepted · C++

[submission 1664032755](https://leetcode.com/submissions/detail/1664032755/) · tests 108/108 · runtime 0 ms (beats 100%)

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
    int ans = 0;
    void sumNumbersUtil(TreeNode * root, int num) {
        if (!root) return;
        int new_num = num*10 + (root->val);
        if (!root->left && (!root->right)) {
            ans += new_num;
        }
        sumNumbersUtil(root->left, new_num);
        sumNumbersUtil(root->right, new_num);
    }
public:
    int sumNumbers(TreeNode* root) {
        sumNumbersUtil(root, 0);
        return ans;
    }
};
```
