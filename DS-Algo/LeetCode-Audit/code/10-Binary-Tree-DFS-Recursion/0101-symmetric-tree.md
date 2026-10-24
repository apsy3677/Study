# 101. Symmetric Tree

[Problem](https://leetcode.com/problems/symmetric-tree/) · Easy · Binary Tree (DFS & Recursion) → Mirror DFS

LeetCode tags: tree, depth-first-search, breadth-first-search, binary-tree

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-03-25 15:48 IST · Accepted · C++

[submission 921783249](https://leetcode.com/submissions/detail/921783249/) · tests 199/199 · runtime 7 ms (beats 0.5%)

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
    bool isSymUtil(TreeNode *r1, TreeNode *r2){
        if(!r1 && !r2){
            return true;
        }
        else if(r1 && r2){
        }
        else{
            return false;
        }
        if(r1->val != r2->val ) return false;

        return isSymUtil(r1->left, r2->right) && isSymUtil(r1->right, r2->left);
    }
public:
    bool isSymmetric(TreeNode* root) {
        return isSymUtil(root, root);
    }
};
```

## Attempt 2 · 2023-03-25 15:49 IST · Accepted · C++

[submission 921783664](https://leetcode.com/submissions/detail/921783664/) · tests 199/199 · runtime 5 ms (beats 0.5%)

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
    bool isSymUtil(TreeNode *r1, TreeNode *r2){
        if(!r1 && !r2){
            return true;
        }
        else if(r1 && r2){
            if(r1->val != r2->val ) return false;

            return isSymUtil(r1->left, r2->right) && isSymUtil(r1->right, r2->left);
        }
        else{
            return false;
        }
        
    }
public:
    bool isSymmetric(TreeNode* root) {
        return isSymUtil(root, root);
    }
};
```
