# 366. Find Leaves of Binary Tree

[Problem](https://leetcode.com/problems/find-leaves-of-binary-tree/) · Medium · Binary Tree (DFS & Recursion) → Group by height

LeetCode tags: tree, depth-first-search, binary-tree, dp-on-trees

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-25 01:12 IST · Accepted · C++

[submission 921490889](https://leetcode.com/submissions/detail/921490889/) · tests 67/67 · runtime 6 ms (beats 0%)

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

void removeLeaves(TreeNode * root, vector<int> &leaves){
    if(!root){
        return;
    }
    if(root->left ){
        // leave node
        if(!root->left->left && !root->left->right){
            leaves.push_back(root->left->val);
            root->left = nullptr;
        }
    }
    if(root->right){
        if(!root->right->left && !root->right->right){
            leaves.push_back(root->right->val);
            root->right = nullptr;
        }
    }
    removeLeaves(root->left, leaves);
    removeLeaves(root->right, leaves);
}

class Solution {
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        vector<vector<int>> ans;
        if(!root){
            return ans;
        }
        while(root && (root->left != nullptr || root->right != nullptr)){
            vector<int> leaves;
            removeLeaves(root, leaves);
            ans.push_back(leaves);
        }
        ans.push_back({root->val});
        return ans;
    }
};
```
