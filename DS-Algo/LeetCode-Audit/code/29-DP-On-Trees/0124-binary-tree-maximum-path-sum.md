# 124. Binary Tree Maximum Path Sum

[Problem](https://leetcode.com/problems/binary-tree-maximum-path-sum/) · Hard · DP: On Trees → Max gain

LeetCode tags: dynamic-programming, tree, depth-first-search, binary-tree, dp-on-trees

Attempts since Mar 2023: 10 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-10-19 18:05 IST · Accepted · C++

[submission 1079157157](https://leetcode.com/submissions/detail/1079157157/) · tests 95/95 · runtime 21 ms (beats 3.9%)

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
    int maxPathSum(TreeNode* root) {
        if(!root) return 0;

        int maxSum = INT_MIN;
        maxPath(root, maxSum);
        return maxSum;
    }
    int maxPath(TreeNode * root, int &maxSum){
        if(!root) return 0;

        int lsum = max(0, maxPath(root->left, maxSum));
        int rsum = max(0, maxPath(root->right, maxSum));

        maxSum = max(maxSum, lsum + rsum + root->val);

        return root->val + max(lsum, rsum);
    }
};
```

## Attempt 2 · 2024-01-12 08:56 IST · Wrong Answer · Python3

[submission 1143852014](https://leetcode.com/submissions/detail/1143852014/) · tests 65/96

Failing input:

```text
[-3]
```

Expected:

```text
-3
```

Your output:

```text
0
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        # post order find sum of path at each node
        maxSum = 0
        def dfs(root):
            nonlocal maxSum
            if not root:
                return 0

            left = dfs(root.left)
            right = dfs(root.right)

            maxSum = max(maxSum, root.val + left + right)
            # print(root.val, maxSum, left, right)
            return root.val + max(left, right)

        dfs(root)
        return maxSum
```

## Attempt 3 · 2024-01-12 08:56 IST · Wrong Answer · Python3

[submission 1143852237](https://leetcode.com/submissions/detail/1143852237/) · tests 69/96

Failing input:

```text
[2,-1]
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
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        # post order find sum of path at each node
        maxSum = float('-inf')
        def dfs(root):
            nonlocal maxSum
            if not root:
                return 0

            left = dfs(root.left)
            right = dfs(root.right)

            maxSum = max(maxSum, root.val + left + right)
            # print(root.val, maxSum, left, right)
            return root.val + max(left, right)

        dfs(root)
        return maxSum
```

## Attempt 4 · 2024-01-12 08:58 IST · Wrong Answer · Python3

[submission 1143853210](https://leetcode.com/submissions/detail/1143853210/) · tests 71/96

Failing input:

```text
[2,-1]
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
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        # post order find sum of path at each node
        maxSum = float('-inf')
        def dfs(root):
            nonlocal maxSum
            if not root:
                return 0

            left = dfs(root.left)
            right = dfs(root.right)

            maxSum = max(maxSum, root.val + left + right)
            # print(root.val, maxSum, left, right)

            # you can decide not to include left, right or root
            return max(root.val, root.val + max(left, right))

        dfs(root)
        return maxSum
```

## Attempt 5 · 2024-01-12 08:59 IST · Runtime Error · Python3

[submission 1143853742](https://leetcode.com/submissions/detail/1143853742/) · tests 0/96

Failing input:

```text
[1,2,3]
```

Expected:

```text
6
```

Runtime error:

```text
TypeError: unsupported operand type(s) for +: 'int' and 'tuple'
                         ~~~~~~~~~^~~~~~
    maxSum = max(maxSum, root.val + left + right)
Line 19 in dfs (Solution.py)
    dfs(root)
Line 26 in maxPathSum (Solution.py)
          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    ret = Solution().maxPathSum(param_1)
Line 46 in _driver (Solution.py)
    _driver()
Line 57 in <module> (Solution.py)
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        # post order find sum of path at each node
        maxSum = float('-inf')
        def dfs(root):
            nonlocal maxSum
            if not root:
                return 0

            left = dfs(root.left)
            right = dfs(root.right)

            maxSum = max(maxSum, root.val + left + right)
            maxSum = max(maxSum, root.val)
            # print(root.val, maxSum, left, right)

            # you can decide not to include left, right or root
            return root.val, root.val + max(left, right)

        dfs(root)
        return maxSum
```

## Attempt 6 · 2024-01-12 08:59 IST · Wrong Answer · Python3

[submission 1143853815](https://leetcode.com/submissions/detail/1143853815/) · tests 83/96

Failing input:

```text
[1,-2,3]
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
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        # post order find sum of path at each node
        maxSum = float('-inf')
        def dfs(root):
            nonlocal maxSum
            if not root:
                return 0

            left = dfs(root.left)
            right = dfs(root.right)

            maxSum = max(maxSum, root.val + left + right)
            maxSum = max(maxSum, root.val)
            # print(root.val, maxSum, left, right)

            # you can decide not to include left, right or root
            return root.val + max(left, right)

        dfs(root)
        return maxSum
```

## Attempt 7 · 2024-01-12 09:00 IST · Wrong Answer · Python3

[submission 1143854609](https://leetcode.com/submissions/detail/1143854609/) · tests 94/96

Failing input:

```text
[9,6,-3,null,null,-6,2,null,null,2,null,-6,-6,-6]
```

Expected:

```text
16
```

Your output:

```text
15
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        # post order find sum of path at each node
        maxSum = float('-inf')
        def dfs(root):
            nonlocal maxSum
            if not root:
                return 0

            left = dfs(root.left)
            right = dfs(root.right)

            maxSum = max(maxSum, root.val, root.val + left , root.val+right, root.val + left + right)
            maxSum = max(maxSum, root.val)
            # print(root.val, maxSum, left, right)

            # you can decide not to include left, right or root
            return root.val + max(left, right)

        dfs(root)
        return maxSum
```

## Attempt 8 · 2024-01-12 09:05 IST · Accepted · Python3

[submission 1143857588](https://leetcode.com/submissions/detail/1143857588/) · tests 96/96 · runtime 66 ms (beats 5.4%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        # post order find sum of path at each node
        maxSum = float('-inf')
        def dfs(root):
            nonlocal maxSum
            if not root:
                return 0
            # maxPath = float('-inf')
            left = dfs(root.left)
            right = dfs(root.right)

            maxSum = max(maxSum, root.val, root.val + left, root.val+ right,  root.val + left + right)
            # print(root.val, maxSum, left, right)

            # you can decide not to include left, right or root
            return root.val + max(left,right, 0)

        dfs(root)
        return maxSum
```

## Attempt 9 · 2025-04-30 14:02 IST · Wrong Answer · C++

[submission 1621808779](https://leetcode.com/submissions/detail/1621808779/) · tests 73/96

Failing input:

```text
[5,4,8,11,null,13,4,7,2,null,null,null,1]
```

Expected:

```text
48
```

Your output:

```text
55
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
    int maxPathSumUtil(TreeNode* root, int &max_path) {
        if (!root) {
            return 0;
        }
        int left = max(0, maxPathSumUtil(root->left, max_path));
        int right = max(0, maxPathSumUtil(root->right, max_path));
        max_path = max({max_path, left + right + root->val});
        return  max({root->val, left + right + root->val});
    }
    int maxPathSum(TreeNode* root) {
        int max_path = INT_MIN;

        maxPathSumUtil(root, max_path);
        return max_path;
    }
};
```

## Attempt 10 · 2025-04-30 14:04 IST · Accepted · C++

[submission 1621809992](https://leetcode.com/submissions/detail/1621809992/) · tests 96/96 · runtime 4 ms (beats 6.7%)

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
    int maxPathSumUtil(TreeNode* root, int &max_path) {
        if (!root) {
            return 0;
        }
        int left = max(0, maxPathSumUtil(root->left, max_path));
        int right = max(0, maxPathSumUtil(root->right, max_path));
        max_path = max({max_path, left + right + root->val});
        return  root->val + max({left , right});
    }
    int maxPathSum(TreeNode* root) {
        int max_path = INT_MIN;

        maxPathSumUtil(root, max_path);
        return max_path;
    }
};
```
