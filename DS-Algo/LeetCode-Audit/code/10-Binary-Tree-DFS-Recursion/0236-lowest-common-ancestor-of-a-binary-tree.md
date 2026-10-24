# 236. Lowest Common Ancestor of a Binary Tree

[Problem](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/) · Medium · Binary Tree (DFS & Recursion) → LCA

LeetCode tags: tree, depth-first-search, binary-tree, binary-lifting, lowest-common-ancestor

Attempts since Mar 2023: 7 · accepted: 5 · failed before first AC: 0

## Attempt 1 · 2023-05-05 07:18 IST · Accepted · C++

[submission 944666986](https://leetcode.com/submissions/detail/944666986/) · tests 31/31 · runtime 27 ms (beats 99.2%)

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (! root || root == p || root == q){
            return root;
        }
        TreeNode * la = lowestCommonAncestor(root->left, p, q);
        TreeNode * ra = lowestCommonAncestor(root->right, p, q);
        if(!la) return ra;
        else if(!ra) return la;
        else return root;
    }
};
```

## Attempt 2 · 2023-12-04 21:15 IST · Runtime Error · Python3

[submission 1112251672](https://leetcode.com/submissions/detail/1112251672/) · tests 0/32

Failing input:

```text
[3,5,1,6,2,0,8,null,null,7,4]
5
1
```

Expected:

```text
3
```

Runtime error:

```text
NameError: name 'node' is not defined. Did you mean: 'mode'?
    parents[root.left] = node
Line 77 in lowestCommonAncestor (Solution.py)
    ret = Solution().lowestCommonAncestor(
Line 118 in __helper__ (Solution.py)
    ret = __DriverSolution__().__helper__(
Line 137 in _driver (Solution.py)
    _driver()
Line 149 in <module> (Solution.py)
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:

    def __init__(self):
        # Variable to store LCA node.
        self.ans = None

    def lowestCommonAncestor(self, root, p, q):
        """
        :type root: TreeNode
        :type p: TreeNode
        :type q: TreeNode
        :rtype: TreeNode

        without parent pointer
        have to traverse from root to find both

        approach 1 - iterative dfs traversal unless you find both p and q and put then in parents list - then it makes it like problem with parent pointer 
        O(N) in worst case to find parents and then O(H) to find ancestors

        approach 2- dfs traversal at that node will have
        first node from bottom(dfs which finishes the bottom nodes first) that has node in either -> mid + left, left + right or right + mid

        for only one node you will have this condition otherwise atmost you will have one of them as true


        """
        def recurse_tree2(current_node):

            # If reached the end of a branch, return False.
            if not current_node:
                return False

            # Left Recursion
            left = recurse_tree(current_node.left)

            # Right Recursion
            right = recurse_tree(current_node.right)

            # If the current node is one of p or q
            mid = current_node == p or current_node == q

            # If any two of the three flags left, right or mid become True.
            if mid + left + right >= 2:
                self.ans = current_node

            print(current_node.val, self.ans.val if self.ans else '', mid + left + right)

            # Return True if either of the three bool values is True.
            return mid or left or right

        # Traverse the tree
        recurse_tree(root)
        return self.ans

    def lowestCommonAncestor(self, root, p, q):
        stack = [root]

        # find parent for each node 
        parents = set({root:None})
        
        # while either of p or q parent not found
        while p not in parents or q not in parents:

            # like iterative tree traversal but not as long as stack but limited to 
            # unless parent of p and q not found
            root = stack.pop()

            # add left and right to stack
            if root.left:
                parents[root.left] = node
                stack.append(root.left)

            if node.right:
                parents[root.right] = node
                stack.append(root.right)

        print(parents)

        ancestors = set()
        while p:
            ancestors.add(p)
            p = parents[p]

        while q not in ancestors:
            q = parents[q]

        return q
```

## Attempt 3 · 2023-12-31 04:31 IST · Time Limit Exceeded · Python3

[submission 1132541577](https://leetcode.com/submissions/detail/1132541577/) · tests 29/32

Failing input:

```text
[-1,0,null,1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9,null,10,null,11,null,12,null,13,null,14,null,15,null,16,null,17,null,18,null,19,null,20,null,21,null,22,null,23,null,24,null,25,null,26,null,27,null,28,null,29,null,30,null,31,null,32,null,33,null,34,null,35,null,36,null,37,null,38,null,39,null,40,null,41,null,42,null,43,null,44,null,45,null,46,null,47,null,48,null,49,null,50,nul ... [98499 more chars]
```

Expected:

```text
9998
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:

    def __init__(self):
        # Variable to store LCA node.
        self.ans = None

    def lowestCommonAncestor(self, root, p, q):
        """
        :type root: TreeNode
        :type p: TreeNode
        :type q: TreeNode
        :rtype: TreeNode

        without parent pointer
        have to traverse from root to find both

        approach 1 - iterative dfs traversal unless you find both p and q and put then in parents list - then it makes it like problem with parent pointer 
        O(N) in worst case to find parents and then O(H) to find ancestors

        approach 2- dfs traversal at that node will have
        first node from bottom(dfs which finishes the bottom nodes first) that has node in either -> mid + left, left + right or right + mid

        for only one node you will have this condition otherwise atmost you will have one of them as true


        """
        def recurse_tree2(current_node):

            # If reached the end of a branch, return False.
            if not current_node:
                return False

            # Left Recursion
            left = recurse_tree(current_node.left)

            # Right Recursion
            right = recurse_tree(current_node.right)

            # If the current node is one of p or q
            mid = current_node == p or current_node == q

            # If any two of the three flags left, right or mid become True.
            if (mid and left) or (mid and right) or (left and right):
                self.ans = current_node

            print(current_node.val, self.ans.val if self.ans else '', mid + left + right)

            # Return True if either of the three bool values is True.
            return mid or left or right

        # Traverse the tree
        recurse_tree(root)
        return self.ans

    def lowestCommonAncestor(self, root, p, q):
        stack = [root]

        # find parent for each node 
        parents = {root:None}
        
        # while either of p or q parent not found
        while p not in parents or q not in parents:

            # like iterative tree traversal but not as long as stack but limited to 
            # unless parent of p and q not found
            root = stack.pop()

            # add left and right to stack
            if root.left:
                parents[root.left] = root
                stack.append(root.left)

            if root.right:
                parents[root.right] = root
                stack.append(root.right)

        print(parents)

        ancestors = set()
        while p:
            ancestors.add(p)
            p = parents[p]

        while q not in ancestors:
            q = parents[q]

        return q
```

## Attempt 4 · 2023-12-31 04:31 IST · Accepted · Python3

[submission 1132541758](https://leetcode.com/submissions/detail/1132541758/) · tests 32/32 · runtime 66 ms (beats 100%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:

    def __init__(self):
        # Variable to store LCA node.
        self.ans = None

    def lowestCommonAncestor(self, root, p, q):
        """
        :type root: TreeNode
        :type p: TreeNode
        :type q: TreeNode
        :rtype: TreeNode

        without parent pointer
        have to traverse from root to find both

        approach 1 - iterative dfs traversal unless you find both p and q and put then in parents list - then it makes it like problem with parent pointer 
        O(N) in worst case to find parents and then O(H) to find ancestors

        approach 2- dfs traversal at that node will have
        first node from bottom(dfs which finishes the bottom nodes first) that has node in either -> mid + left, left + right or right + mid

        for only one node you will have this condition otherwise atmost you will have one of them as true


        """
        def recurse_tree(current_node):

            # If reached the end of a branch, return False.
            if not current_node:
                return False

            # Left Recursion
            left = recurse_tree(current_node.left)

            # Right Recursion
            right = recurse_tree(current_node.right)

            # If the current node is one of p or q
            mid = current_node == p or current_node == q

            # If any two of the three flags left, right or mid become True.
            if (mid and left) or (mid and right) or (left and right):
                self.ans = current_node

            print(current_node.val, self.ans.val if self.ans else '', mid + left + right)

            # Return True if either of the three bool values is True.
            return mid or left or right

        # Traverse the tree
        recurse_tree(root)
        return self.ans

    def lowestCommonAncestor3(self, root, p, q):
        stack = [root]

        # find parent for each node 
        parents = {root:None}
        
        # while either of p or q parent not found
        while p not in parents or q not in parents:

            # like iterative tree traversal but not as long as stack but limited to 
            # unless parent of p and q not found
            root = stack.pop()

            # add left and right to stack
            if root.left:
                parents[root.left] = root
                stack.append(root.left)

            if root.right:
                parents[root.right] = root
                stack.append(root.right)

        print(parents)

        ancestors = set()
        while p:
            ancestors.add(p)
            p = parents[p]

        while q not in ancestors:
            q = parents[q]

        return q
```

## Attempt 5 · 2023-12-31 04:32 IST · Accepted · Python3

[submission 1132541940](https://leetcode.com/submissions/detail/1132541940/) · tests 32/32 · runtime 103 ms (beats 99.9%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:

    def __init__(self):
        # Variable to store LCA node.
        self.ans = None

    def lowestCommonAncestor(self, root, p, q):
        """
        :type root: TreeNode
        :type p: TreeNode
        :type q: TreeNode
        :rtype: TreeNode

        without parent pointer
        have to traverse from root to find both

        approach 1 - iterative dfs traversal unless you find both p and q and put then in parents list - then it makes it like problem with parent pointer 
        O(N) in worst case to find parents and then O(H) to find ancestors

        approach 2- dfs traversal at that node will have
        first node from bottom(dfs which finishes the bottom nodes first) that has node in either -> mid + left, left + right or right + mid

        for only one node you will have this condition otherwise atmost you will have one of them as true


        """
        def recurse_tree(current_node):

            # If reached the end of a branch, return False.
            if not current_node:
                return False

            # Left Recursion
            left = recurse_tree(current_node.left)

            # Right Recursion
            right = recurse_tree(current_node.right)

            # If the current node is one of p or q
            mid = current_node == p or current_node == q

            # If any two of the three flags left, right or mid become True.
            if (mid and left) or (mid and right) or (left and right):
                self.ans = current_node

            #print(current_node.val, self.ans.val if self.ans else '', mid + left + right)

            # Return True if either of the three bool values is True.
            return mid or left or right

        # Traverse the tree
        recurse_tree(root)
        return self.ans

    def lowestCommonAncestor3(self, root, p, q):
        stack = [root]

        # find parent for each node 
        parents = {root:None}
        
        # while either of p or q parent not found
        while p not in parents or q not in parents:

            # like iterative tree traversal but not as long as stack but limited to 
            # unless parent of p and q not found
            root = stack.pop()

            # add left and right to stack
            if root.left:
                parents[root.left] = root
                stack.append(root.left)

            if root.right:
                parents[root.right] = root
                stack.append(root.right)

        print(parents)

        ancestors = set()
        while p:
            ancestors.add(p)
            p = parents[p]

        while q not in ancestors:
            q = parents[q]

        return q
```

## Attempt 6 · 2023-12-31 04:32 IST · Accepted · Python3

[submission 1132542057](https://leetcode.com/submissions/detail/1132542057/) · tests 32/32 · runtime 51 ms (beats 100%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:

    def __init__(self):
        # Variable to store LCA node.
        self.ans = None

    def lowestCommonAncestor(self, root, p, q):
        """
        :type root: TreeNode
        :type p: TreeNode
        :type q: TreeNode
        :rtype: TreeNode

        without parent pointer
        have to traverse from root to find both

        approach 1 - iterative dfs traversal unless you find both p and q and put then in parents list - then it makes it like problem with parent pointer 
        O(N) in worst case to find parents and then O(H) to find ancestors

        approach 2- dfs traversal at that node will have
        first node from bottom(dfs which finishes the bottom nodes first) that has node in either -> mid + left, left + right or right + mid

        for only one node you will have this condition otherwise atmost you will have one of them as true


        """
        def recurse_tree(current_node):

            # If reached the end of a branch, return False.
            if not current_node:
                return False

            # Left Recursion
            left = recurse_tree(current_node.left)

            # Right Recursion
            right = recurse_tree(current_node.right)

            # If the current node is one of p or q
            mid = current_node in [p,q]

            # If any two of the three flags left, right or mid become True.
            if (mid and left) or (mid and right) or (left and right):
                self.ans = current_node

            #print(current_node.val, self.ans.val if self.ans else '', mid + left + right)

            # Return True if either of the three bool values is True.
            return mid or left or right

        # Traverse the tree
        recurse_tree(root)
        return self.ans

    def lowestCommonAncestor3(self, root, p, q):
        stack = [root]

        # find parent for each node 
        parents = {root:None}
        
        # while either of p or q parent not found
        while p not in parents or q not in parents:

            # like iterative tree traversal but not as long as stack but limited to 
            # unless parent of p and q not found
            root = stack.pop()

            # add left and right to stack
            if root.left:
                parents[root.left] = root
                stack.append(root.left)

            if root.right:
                parents[root.right] = root
                stack.append(root.right)

        print(parents)

        ancestors = set()
        while p:
            ancestors.add(p)
            p = parents[p]

        while q not in ancestors:
            q = parents[q]

        return q
```

## Attempt 7 · 2025-03-22 16:24 IST · Accepted · C++

[submission 1582194949](https://leetcode.com/submissions/detail/1582194949/) · tests 32/32 · runtime 14 ms (beats 100.0%)

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q) return root;

        // if (root == p || root == q) return root;

        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        if (left && right) return root;

        return left ? left : right;
    }
};
```
