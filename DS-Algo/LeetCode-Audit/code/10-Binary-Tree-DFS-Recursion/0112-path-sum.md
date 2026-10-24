# 112. Path Sum

[Problem](https://leetcode.com/problems/path-sum/) · Easy · Binary Tree (DFS & Recursion) → Root-to-leaf

LeetCode tags: tree, depth-first-search, breadth-first-search, binary-tree

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-05-20 16:14 IST · Accepted · C++

[submission 953849102](https://leetcode.com/submissions/detail/953849102/) · tests 117/117 · runtime 12 ms (beats 0.9%)

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
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(!root) return false;

        if(!root->left && !root->right) return targetSum == root->val;

        return hasPathSum(root->left, targetSum-root->val) ||
        hasPathSum(root->right, targetSum-root->val);
    }
};
```
