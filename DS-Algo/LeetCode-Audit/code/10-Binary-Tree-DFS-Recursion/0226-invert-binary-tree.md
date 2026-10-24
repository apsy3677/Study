# 226. Invert Binary Tree

[Problem](https://leetcode.com/problems/invert-binary-tree/) · Easy · Binary Tree (DFS & Recursion) → Mirror

LeetCode tags: tree, depth-first-search, breadth-first-search, binary-tree

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-05-19 18:24 IST · Accepted · C++

[submission 953343922](https://leetcode.com/submissions/detail/953343922/) · tests 77/77 · runtime 4 ms (beats 0.0%)

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
    TreeNode* invertTree(TreeNode* root) {
        if(!root) return root;
        invertTree(root->left);
        invertTree(root->right);
        swap(root->left, root->right);

        return root;
    }
};
```

## Attempt 2 · 2023-05-20 13:50 IST · Accepted · C++

[submission 953788289](https://leetcode.com/submissions/detail/953788289/) · tests 77/77 · runtime 2 ms (beats 0.6%)

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
    TreeNode* invertTree(TreeNode* root) {
        if(!root) return root;
        invertTree(root->left);
        invertTree(root->right);
        
        swap(root->left, root->right);
        
        return root;
    }
};
```
