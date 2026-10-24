# 99. Recover Binary Search Tree

[Problem](https://leetcode.com/problems/recover-binary-search-tree/) · Medium · Binary Search Tree → Inorder swap detection

LeetCode tags: tree, depth-first-search, binary-search-tree, binary-tree

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2026-06-18 10:20 IST · Accepted · C++

[submission 2037054274](https://leetcode.com/submissions/detail/2037054274/) · tests 1919/1919 · runtime 2 ms (beats 23.9%)

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
    TreeNode *first = nullptr, *second = nullptr, *prev = nullptr;
public:
void inorder(TreeNode * root) {
    if (!root) return;

    inorder(root->left);

    if (prev && prev->val > root->val) {
        if (!first) first = prev;
        second = root;
    }
    prev = root;

    inorder(root->right);
}
    void recoverTree(TreeNode* root) {
        inorder(root);
        swap(first->val, second->val);
    }
};
```
