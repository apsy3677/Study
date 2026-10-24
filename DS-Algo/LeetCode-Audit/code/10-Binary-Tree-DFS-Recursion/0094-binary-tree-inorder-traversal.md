# 94. Binary Tree Inorder Traversal

[Problem](https://leetcode.com/problems/binary-tree-inorder-traversal/) · Easy · Binary Tree (DFS & Recursion) → Iterative traversal

LeetCode tags: stack, tree, depth-first-search, binary-tree

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2024-11-07 11:05 IST · Accepted · C++

[submission 1445450809](https://leetcode.com/submissions/detail/1445450809/) · tests 71/71 · runtime 0 ms (beats 100%)

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
    void inorder_trav(TreeNode* root, vector<int>& inorder) {
        if (!root) return;

        inorder_trav(root->left, inorder);
        inorder.push_back(root->val);
        inorder_trav(root->right, inorder);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> inorder;
        inorder_trav(root, inorder);
        return inorder;
    }
};
```
