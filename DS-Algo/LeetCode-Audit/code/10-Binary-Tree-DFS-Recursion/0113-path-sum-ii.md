# 113. Path Sum II

[Problem](https://leetcode.com/problems/path-sum-ii/) · Medium · Binary Tree (DFS & Recursion) → Root-to-leaf paths

LeetCode tags: backtracking, tree, depth-first-search, binary-tree

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-05-20 16:21 IST · Accepted · C++

[submission 953852353](https://leetcode.com/submissions/detail/953852353/) · tests 115/115 · runtime 7 ms (beats 27.7%)

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
    void hasPathSum(TreeNode* root, int targetSum, vector<int> &path, vector<vector<int>> &ans) {
        if(!root) return;

        if(!root->left && !root->right){
            if(targetSum == root->val){
                path.push_back(root->val);
                ans.push_back(path);
                path.pop_back();
            }
        }
        path.push_back(root->val);
        hasPathSum(root->left, targetSum-root->val, path, ans);
        path.pop_back();

        path.push_back(root->val);
        hasPathSum(root->right, targetSum-root->val, path, ans);
        path.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> ans;
        vector<int> path;

        hasPathSum(root, targetSum, path, ans);
        return ans;
    }
};
```

## Attempt 2 · 2023-05-20 17:57 IST · Accepted · C++

[submission 953889600](https://leetcode.com/submissions/detail/953889600/) · tests 115/115 · runtime 18 ms (beats 11.1%)

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
    void hasPathSum(TreeNode* root, int targetSum, vector<int> &path, vector<vector<int>> &ans) {
        if(!root){
            // if(targetSum == 0){
            //     // path.push_back(root->val);
            //     ans.push_back(path);
            //     // path.pop_back();
            // }
            return;
        }
        path.push_back(root->val);

        if(!root->left && !root->right){
            if(targetSum == root->val){
                // path.push_back(root->val);
                ans.push_back(path);
                // path.pop_back();
            }
        }
        hasPathSum(root->left, targetSum-root->val, path, ans);
        // path.pop_back();

        // path.push_back(root->val);
        hasPathSum(root->right, targetSum-root->val, path, ans);

        path.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> ans;
        vector<int> path;

        hasPathSum(root, targetSum, path, ans);
        return ans;
    }
};
```
