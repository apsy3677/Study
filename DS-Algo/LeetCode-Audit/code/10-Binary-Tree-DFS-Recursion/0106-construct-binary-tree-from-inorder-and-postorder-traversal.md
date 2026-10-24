# 106. Construct Binary Tree from Inorder and Postorder Traversal

[Problem](https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/) · Medium · Binary Tree (DFS & Recursion) → Build from traversals

LeetCode tags: array, hash-table, divide-and-conquer, tree, binary-tree

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-05-05 08:59 IST · Accepted · C++

[submission 944702434](https://leetcode.com/submissions/detail/944702434/) · tests 202/202 · runtime 12 ms (beats 8.7%)

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
    unordered_map<int,int> mp;
    TreeNode* constructTree(int start, int end, int pStart, int pEnd, vector<int>& postorder, vector<int>& inorder){
        if(start > end || pStart > pEnd) return NULL;
        int val= postorder[pEnd];
        int idx = mp[val];
        TreeNode *root = new TreeNode(val);
        int ls = idx-start,rs = end-idx;
        root->left = constructTree(start, idx-1,pStart, pStart+ls -1,postorder,inorder);
        root->right = constructTree(idx+1, end, pStart+ls, pEnd-1,postorder,inorder);
        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        
        int n = postorder.size();
        int preIdx = n-1;
        for(int i=0;i<inorder.size();i++){
            mp[inorder[i]] =i;
        }
        return constructTree(0,n-1, 0, n-1, postorder, inorder);
    }
};
```

## Attempt 2 · 2023-05-05 09:00 IST · Accepted · C++

[submission 944702857](https://leetcode.com/submissions/detail/944702857/) · tests 202/202 · runtime 25 ms (beats 5.0%)

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
    unordered_map<int,int> mp;
    TreeNode* constructTree(int start, int end, int pStart, int pEnd, vector<int>& postorder, vector<int>& inorder){
        if(start > end || pStart > pEnd) return NULL;
        int val= postorder[pEnd];
        int idx = mp[val];
        TreeNode *root = new TreeNode(val);
        int ls = idx-start,rs = end-idx;
        root->left = constructTree(start, idx-1,pStart, pStart+ls -1,postorder,inorder);
        root->right = constructTree(idx+1, end, pEnd-rs, pEnd-1,postorder,inorder);
        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        
        int n = postorder.size();
        int preIdx = n-1;
        for(int i=0;i<inorder.size();i++){
            mp[inorder[i]] =i;
        }
        return constructTree(0,n-1, 0, n-1, postorder, inorder);
    }
};
```
