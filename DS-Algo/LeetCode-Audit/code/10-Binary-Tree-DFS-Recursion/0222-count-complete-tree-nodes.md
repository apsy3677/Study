# 222. Count Complete Tree Nodes

[Problem](https://leetcode.com/problems/count-complete-tree-nodes/) · Medium · Binary Tree (DFS & Recursion) → Height + binary search

LeetCode tags: binary-search, bit-manipulation, tree, binary-tree

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-05-05 08:28 IST · Accepted · C++

[submission 944690918](https://leetcode.com/submissions/detail/944690918/) · tests 18/18 · runtime 41 ms (beats 0.1%)

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
    int countNodes(TreeNode* root) {
        if(!root) return 0;

        int lh = findLH(root);
        int rh = findRH(root);
        if(lh == rh) return (1<<lh)-1;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
    int findLH(TreeNode * root){
        int h =0;
        while(root){
            h++;
            root = root->left;
        }
        return h;
    }
    int findRH(TreeNode * root){
        int h =0;
        while(root){
            h++;
            root = root->right;
        }
        return h;
    }
};
```
