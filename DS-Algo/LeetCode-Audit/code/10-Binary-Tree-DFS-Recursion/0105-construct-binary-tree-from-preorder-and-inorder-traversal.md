# 105. Construct Binary Tree from Preorder and Inorder Traversal

[Problem](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/) · Medium · Binary Tree (DFS & Recursion) → Build from traversals

LeetCode tags: array, hash-table, divide-and-conquer, tree, binary-tree

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-05-05 08:43 IST · Accepted · C++

[submission 944696483](https://leetcode.com/submissions/detail/944696483/) · tests 203/203 · runtime 11 ms (beats 17.8%)

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
    unordered_map<int,int> mp;
    TreeNode* constructTree(int start, int end, int &pre, vector<int>& preorder, vector<int>& inorder){
        if(start > end) return NULL;
        int val=preorder[pre++];
        int idx = mp[val];
        TreeNode *root = new TreeNode(val);

        root->left = constructTree(start, idx-1,pre,preorder,inorder);
        root->right = constructTree(idx+1, end, pre,preorder,inorder);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int preIdx =0;
        int n = preorder.size();
        for(int i=0;i<inorder.size();i++){
            mp[inorder[i]] =i;
        }
        return constructTree(0,n-1, preIdx, preorder, inorder);
    }
};
```
