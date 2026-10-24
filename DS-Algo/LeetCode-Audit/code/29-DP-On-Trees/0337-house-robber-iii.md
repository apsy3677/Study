# 337. House Robber III

[Problem](https://leetcode.com/problems/house-robber-iii/) · Medium · DP: On Trees → Rob/skip pair

LeetCode tags: dynamic-programming, tree, depth-first-search, binary-tree, dp-on-trees

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-05-11 12:36 IST · Accepted · C++

[submission 948276626](https://leetcode.com/submissions/detail/948276626/) · tests 124/124 · runtime 7 ms (beats 35.1%)

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
    typedef pair<int, int> pii;
    pii solve(TreeNode* root)   {
        if(!root)   return {0, 0};
        pii l = solve(root -> left), r = solve(root -> right), temp;
        temp.first = root -> val + l.second + r.second; // if we include the root then we can not include the left and right child of the root
        temp.second = max(l.first, l.second) + max(r.first, r.second);  // if we exclude the root then we can include or exclude the left and right child of the root
        return temp;
    }

    int rob(TreeNode* root) {
        if(!root)   return NULL;
        pii ans = solve(root);
        return max(ans.first, ans.second);
    }
};
```
