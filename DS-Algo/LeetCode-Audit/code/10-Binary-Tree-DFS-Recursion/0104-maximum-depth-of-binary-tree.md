# 104. Maximum Depth of Binary Tree

[Problem](https://leetcode.com/problems/maximum-depth-of-binary-tree/) · Easy · Binary Tree (DFS & Recursion) → Height DFS

LeetCode tags: tree, depth-first-search, breadth-first-search, binary-tree

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-25 15:51 IST · Accepted · C++

[submission 921784525](https://leetcode.com/submissions/detail/921784525/) · tests 39/39 · runtime 7 ms (beats 1.0%)

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
    int maxDepth(TreeNode* root) {
        if(!root) return 0;

        return max( maxDepth(root->left),maxDepth(root->right) ) +1;
    }
};
```
