# 572. Subtree of Another Tree

[Problem](https://leetcode.com/problems/subtree-of-another-tree/) · Easy · Binary Tree (DFS & Recursion) → Tree matching

LeetCode tags: tree, depth-first-search, string-matching, binary-tree, hash-function

Attempts since Mar 2023: 4 · accepted: 4 · failed before first AC: 0

## Attempt 1 · 2023-05-21 08:37 IST · Accepted · C++

[submission 954240879](https://leetcode.com/submissions/detail/954240879/) · tests 182/182 · runtime 27 ms (beats 5.1%)

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
    bool isSameTree(TreeNode * p, TreeNode* q){
        if(!p || !q) return p==NULL && q==NULL;

        if(p->val == q->val){
            return isSameTree(p->left, q->left) &&
                isSameTree(p->right, q->right);
        }
        return false;
    }
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(!root) return false;

        if(isSameTree(root, subRoot)) return true;

        return isSubtree(root->left, subRoot) || 
                isSubtree(root->right, subRoot);
    }
};
```

## Attempt 2 · 2023-05-21 08:43 IST · Accepted · C++

[submission 954245431](https://leetcode.com/submissions/detail/954245431/) · tests 182/182 · runtime 20 ms (beats 5.1%)

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
    bool isSameTree(TreeNode * p, TreeNode* q){
        if(!p || !q) return p==NULL && q==NULL;

        if(p->val == q->val){
            return isSameTree(p->left, q->left) &&
                isSameTree(p->right, q->right);
        }
        return false;
    }
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(!root && subRoot) return false;

        if(!subRoot) return true;

        if(root->val == subRoot->val && isSameTree(root, subRoot)) 
            return true;

        return isSubtree(root->left, subRoot) || 
                isSubtree(root->right, subRoot);
    }
};
```

## Attempt 3 · 2023-05-21 08:45 IST · Accepted · C++

[submission 954246381](https://leetcode.com/submissions/detail/954246381/) · tests 182/182 · runtime 26 ms (beats 5.1%)

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
    bool isSameTree(TreeNode * p, TreeNode* q){
        if(!p || !q) return p==NULL && q==NULL;

        if(p->val == q->val){
            return isSameTree(p->left, q->left) &&
                isSameTree(p->right, q->right);
        }
        return false;
    }
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(!root && subRoot) return false;

        if(!subRoot) return true;

        if(root->val == subRoot->val && isSameTree(root, subRoot)) 
            return true;

        return isSubtree(root->left, subRoot) | 
                isSubtree(root->right, subRoot);
    }
};
```

## Attempt 4 · 2023-05-21 08:45 IST · Accepted · C++

[submission 954246623](https://leetcode.com/submissions/detail/954246623/) · tests 182/182 · runtime 25 ms (beats 5.1%)

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
    bool isSameTree(TreeNode * p, TreeNode* q){
        if(!p || !q) return p==NULL && q==NULL;

        if(p->val == q->val){
            return isSameTree(p->left, q->left) &&
                isSameTree(p->right, q->right);
        }
        return false;
    }
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(!root && subRoot) return false;

        if(!subRoot) return true;

        if(root->val == subRoot->val && isSameTree(root, subRoot)) 
            return true;

        return isSubtree(root->left, subRoot) || 
                isSubtree(root->right, subRoot);
    }
};
```
