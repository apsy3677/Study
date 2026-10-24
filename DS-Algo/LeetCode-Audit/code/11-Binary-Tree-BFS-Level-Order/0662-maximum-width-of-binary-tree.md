# 662. Maximum Width of Binary Tree

[Problem](https://leetcode.com/problems/maximum-width-of-binary-tree/) · Medium · Binary Tree (BFS / Level Order) → Position index per level

LeetCode tags: tree, depth-first-search, breadth-first-search, binary-tree

Attempts since Mar 2023: 3 · accepted: 1 · failed before first AC: 2

## Attempt 1 · 2023-05-05 07:28 IST · Runtime Error · C++

[submission 944669999](https://leetcode.com/submissions/detail/944669999/) · tests 72/114

Failing input:

```text
[0,0,0,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,n ... [545 more chars]
```

Expected:

```text
2
```

Runtime error:

```text
Line 34: Char 44: runtime error: signed integer overflow: 2 * 1610612734 cannot be represented in type 'int' (solution.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:43:44
```

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
    int widthOfBinaryTree(TreeNode* root) {
        if(!root) return 0;

        queue<pair<TreeNode*, int>> qu;
        qu.push({root,0});
        int left =0, right=0;
        int ans =0;
        while(!qu.empty()){
            int sz = qu.size();
            left = qu.front().second;
            while(sz--){
                auto it = qu.front(); qu.pop();
                auto node = it.first;
                auto id = it.second;
                right = max(id, right);
                if(node->left){
                    qu.push({node->left,2*id +1});
                    
                }
                if(node->right){
                    qu.push({node->right, 2*id +2});
                    // right = max(2*id +2, right);
                }
            }
            ans = max(ans, right-left+1);
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-05-05 07:35 IST · Runtime Error · C++

[submission 944672326](https://leetcode.com/submissions/detail/944672326/) · tests 72/114

Failing input:

```text
[0,0,0,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,null,0,0,null,n ... [545 more chars]
```

Expected:

```text
2
```

Runtime error:

```text
Line 37: Char 46: runtime error: signed integer overflow: 2 * 6917529027641081854 cannot be represented in type 'long long' (solution.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:46:46
```

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
    typedef long long ll;
public:
    int widthOfBinaryTree(TreeNode* root) {
        if(!root) return 0;

        queue<pair<TreeNode*, ll>> qu;
        qu.push({root,0});
        ll left =0, right=0;
        ll ans =0;
        while(!qu.empty()){
            int sz = qu.size();
            left = qu.front().second;
            right = qu.back().second;
            ans = max(ans, right-left+1);
            while(sz--){
                auto it = qu.front(); qu.pop();
                auto node = it.first;
                ll id = it.second;
                right = max(id, right);
                if(node->left){
                    qu.push({node->left,2LL*id +1});
                    
                }
                if(node->right){
                    qu.push({node->right, 2LL*id + 2});
                    // right = max(2*id +2, right);
                }
            }
            
        }
        return (int)ans;
    }
};
```

## Attempt 3 · 2023-05-05 07:36 IST · Accepted · C++

[submission 944672783](https://leetcode.com/submissions/detail/944672783/) · tests 114/114 · runtime 10 ms (beats 2.4%)

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
    typedef long long ll;
public:
    int widthOfBinaryTree(TreeNode* root) {
        if(!root) return 0;

        queue<pair<TreeNode*, ll>> qu;
        qu.push({root,0});
        ll left =0, right=0;
        ll ans =0;
        while(!qu.empty()){
            int sz = qu.size();
            left = qu.front().second;
            right = qu.back().second;
            ans = max(ans, right-left+1);
            while(sz--){
                auto it = qu.front(); qu.pop();
                auto node = it.first;
                ll id = it.second - left;
                right = max(id, right);
                if(node->left){
                    qu.push({node->left,2LL*id +1});
                    
                }
                if(node->right){
                    qu.push({node->right, 2LL*id + 2});
                    // right = max(2*id +2, right);
                }
            }
            
        }
        return (int)ans;
    }
};
```
