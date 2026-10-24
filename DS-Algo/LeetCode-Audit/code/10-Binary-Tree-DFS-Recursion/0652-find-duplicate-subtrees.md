# 652. Find Duplicate Subtrees

[Problem](https://leetcode.com/problems/find-duplicate-subtrees/) · Medium · Binary Tree (DFS & Recursion) → Subtree serialization

LeetCode tags: hash-table, tree, depth-first-search, binary-tree

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-03-21 19:24 IST · Accepted · C++

[submission 919510923](https://leetcode.com/submissions/detail/919510923/) · tests 175/175 · runtime 47 ms (beats 5.0%)

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
    map<string,int> mp;
    vector<TreeNode *> ans;
public:
    string traverse (TreeNode * root){
        if(root == nullptr){
            return "";
        }
        
        string left = "(" + traverse(root->left) + ")";
        string right = "(" + traverse(root->right) + ")";
        string tree = left + to_string(root->val) + right;
        mp[tree]++;
        if(mp[tree] ==2){
            ans.push_back(root);
        }

        return tree;
    }
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        
        traverse(root);

        return ans;
    }
};
```

## Attempt 2 · 2023-03-22 22:07 IST · Accepted · C++

[submission 920228711](https://leetcode.com/submissions/detail/920228711/) · tests 175/175 · runtime 56 ms (beats 5.0%)

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
    map<string,int> mp;
    vector<TreeNode *> ans;
public:
    string traverse (TreeNode * root){
        if(root == nullptr){
            return "";
        }
        
        string left = "(" + traverse(root->left) + ")";
        string right = "(" + traverse(root->right) + ")";
        string tree = left + to_string(root->val) + right;
        mp[tree]++;
        if(mp[tree] ==2){
            ans.push_back(root);
        }

        return tree;
    }
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        
        traverse(root);

        return ans;
    }
};
```
