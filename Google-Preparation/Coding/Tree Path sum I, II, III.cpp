Path sum I, II, III
Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum. See below for an example.

Given the below binary tree and sum = 22,

      5
     / \
    4   8
   /   / \
  11  13  4
 /  \      \
7    2      1
return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.

    bool hasPathSum(TreeNode* root, int targetSum) {
        if(!root) return targetSum == 0;

        hasPathSum(root->left, targetSum-root->val) ||
        hasPathSum(root->right, targetSum-root->val);
    }