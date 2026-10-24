# 938. Range Sum of BST

[Problem](https://leetcode.com/problems/range-sum-of-bst/) · Easy · Binary Search Tree → Range-pruned DFS

LeetCode tags: tree, depth-first-search, binary-search-tree, binary-tree

Attempts since Mar 2023: 13 · accepted: 13 · failed before first AC: 0

## Attempt 1 · 2023-03-07 00:36 IST · Accepted · C++

[submission 910366212](https://leetcode.com/submissions/detail/910366212/) · tests 41/41 · runtime 135 ms (beats 3.0%)

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
    int rangeSumBST(TreeNode* root, int low, int high) {
        
        if(root == NULL){
            return 0;
        }
        
        if(root->val >= low && root->val <=high){
            
            return rangeSumBST(root->left, low, high) + root->val + rangeSumBST(root->right, low, high);
        }
        else if(root->val <low){
            return rangeSumBST(root->right, low, high);
        }
        else{
            return rangeSumBST(root->left, low, high);
        }

    }
};
```

## Attempt 2 · 2023-03-07 00:50 IST · Accepted · C++

[submission 910373064](https://leetcode.com/submissions/detail/910373064/) · tests 41/41 · runtime 152 ms (beats 3.0%)

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
    int rangeSumBST(TreeNode* root, int low, int high) {
        
        // iterative Approach

        int ans =0;

        stack<TreeNode *> st;
        st.push(root);

        while(!st.empty()){
            TreeNode * node = st.top();
            st.pop();

            if(node != NULL){
                if(node->val>=low && node->val<=high){
                    ans+= node->val;
                }
                if(node->val > low)
                    st.push(node->left);
                
                if(node->val < high)
                    st.push(node->right);
            }
        }

        return ans;

        // recursive Approach
        // if(root == NULL){
        //     return 0;
        // }
        
        // if(root->val >= low && root->val <=high){
            
        //     return rangeSumBST(root->left, low, high) + root->val + rangeSumBST(root->right, low, high);
        // }
        // else if(root->val <low){
        //     return rangeSumBST(root->right, low, high);
        // }
        // else{
        //     return rangeSumBST(root->left, low, high);
        // }

    }
};
```

## Attempt 3 · 2023-03-07 00:51 IST · Accepted · C++

[submission 910373631](https://leetcode.com/submissions/detail/910373631/) · tests 41/41 · runtime 128 ms (beats 3.0%)

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
    int rangeSumBST(TreeNode* root, int low, int high) {
        
        // iterative Approach

        int ans =0;

        stack<TreeNode *> st;
        st.push(root);

        while(!st.empty()){
            TreeNode * node = st.top();
            st.pop();

            if(node != NULL){
                if(node->val>=low && node->val<=high){
                    ans+= node->val;
                }
                if(node->left)
                    st.push(node->left);
                
                if(node->right){
                    st.push(node->right);
                }
                // if(node->val > low)
                //     st.push(node->left);
                
                // if(node->val < high)
                //     st.push(node->right);
            }
        }

        return ans;

        // recursive Approach
        // if(root == NULL){
        //     return 0;
        // }
        
        // if(root->val >= low && root->val <=high){
            
        //     return rangeSumBST(root->left, low, high) + root->val + rangeSumBST(root->right, low, high);
        // }
        // else if(root->val <low){
        //     return rangeSumBST(root->right, low, high);
        // }
        // else{
        //     return rangeSumBST(root->left, low, high);
        // }

    }
};
```

## Attempt 4 · 2023-04-01 23:22 IST · Accepted · C++

[submission 926105512](https://leetcode.com/submissions/detail/926105512/) · tests 41/41 · runtime 126 ms (beats 3.0%)

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
    int rangeSumBST(TreeNode* root, int low, int high) {
        
        // iterative Approach

        // int ans =0;

        // stack<TreeNode *> st;
        // st.push(root);

        // while(!st.empty()){
        //     TreeNode * node = st.top();
        //     st.pop();

        //     if(node != NULL){
        //         if(node->val>=low && node->val<=high){
        //             ans+= node->val;
        //         }
        //         if(node->left)
        //             st.push(node->left);
                
        //         if(node->right){
        //             st.push(node->right);
        //         }
        //         // if(node->val > low)
        //         //     st.push(node->left);
                
        //         // if(node->val < high)
        //         //     st.push(node->right);
        //     }
        // }

        // return ans;

        // recursive Approach
        if(root == NULL){
            return 0;
        }
        
        if(root->val >= low && root->val <=high){
            
            return rangeSumBST(root->left, low, high) + root->val + rangeSumBST(root->right, low, high);
        }
        else if(root->val <low){
            return rangeSumBST(root->right, low, high);
        }
        else{
            return rangeSumBST(root->left, low, high);
        }

    }
};
```

## Attempt 5 · 2023-04-01 23:24 IST · Accepted · C++

[submission 926106990](https://leetcode.com/submissions/detail/926106990/) · tests 41/41 · runtime 143 ms (beats 3.0%)

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
    int rangeSumBST(TreeNode* root, int low, int high) {
        
        // iterative Approach

        int ans =0;

        stack<TreeNode *> st;
        st.push(root);

        while(!st.empty()){
            TreeNode * node = st.top();
            st.pop();

            if(node != NULL){
                if(node->val>=low && node->val<=high){
                    ans+= node->val;
                }
                if(node->left)
                    st.push(node->left);
                
                if(node->right){
                    st.push(node->right);
                }
                // if(node->val > low)
                //     st.push(node->left);
                
                // if(node->val < high)
                //     st.push(node->right);
            }
        }

        return ans;

        // recursive Approach
        if(root == NULL){
            return 0;
        }
        
        if(root->val >= low && root->val <=high){
            
            return rangeSumBST(root->left, low, high) + root->val + rangeSumBST(root->right, low, high);
        }
        else if(root->val <low){
            return rangeSumBST(root->right, low, high);
        }
        else{
            return rangeSumBST(root->left, low, high);
        }

    }
};
```

## Attempt 6 · 2023-04-01 23:26 IST · Accepted · C++

[submission 926107893](https://leetcode.com/submissions/detail/926107893/) · tests 41/41 · runtime 151 ms (beats 3.0%)

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
    int rangeSumBST(TreeNode* root, int low, int high) {
        
        // iterative Approach

        int ans =0;

        stack<TreeNode *> st;
        st.push(root);

        while(!st.empty()){
            TreeNode * node = st.top();
            st.pop();

            if(node != NULL){
                if(node->val>=low && node->val<=high){
                    ans+= node->val;
                    st.push(node->left);
                    st.push(node->right);
                }
                // if(node->left)
                //     st.push(node->left);
                
                // if(node->right){
                //     st.push(node->right);
                // }
                else if(node->val < low)
                    st.push(node->right);
                
                else
                    st.push(node->left);
            }
        }

        return ans;

        // recursive Approach
        if(root == NULL){
            return 0;
        }
        
        if(root->val >= low && root->val <=high){
            
            return rangeSumBST(root->left, low, high) + root->val + rangeSumBST(root->right, low, high);
        }
        else if(root->val <low){
            return rangeSumBST(root->right, low, high);
        }
        else{
            return rangeSumBST(root->left, low, high);
        }

    }
};
```

## Attempt 7 · 2023-11-23 04:05 IST · Accepted · Python3

[submission 1104480226](https://leetcode.com/submissions/detail/1104480226/) · tests 41/41 · runtime 194 ms (beats 5.5%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def rangeSumBST(self, root: Optional[TreeNode], low: int, high: int) -> int:
        
        total = 0

        def dfs(root):
            nonlocal total
            if not root:
                return 

            if low<=root.val<=high:
                total+= root.val

            dfs(root.left)
            dfs(root.right)

        dfs(root)
        return total
```

## Attempt 8 · 2023-12-04 12:21 IST · Accepted · Python3

[submission 1111983463](https://leetcode.com/submissions/detail/1111983463/) · tests 41/41 · runtime 197 ms (beats 5.5%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def rangeSumBST(self, root: Optional[TreeNode], low: int, high: int) -> int:
        
        def dfs(root):
            total = 0
            if not root:
                return 0

            if low<=root.val<=high:
                total+= root.val

            total += dfs(root.left) 
            total += dfs(root.right) 
            return total 

        return dfs(root)
```

## Attempt 9 · 2023-12-04 12:24 IST · Accepted · Python3

[submission 1111984908](https://leetcode.com/submissions/detail/1111984908/) · tests 41/41 · runtime 147 ms (beats 5.5%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def rangeSumBST(self, root: Optional[TreeNode], low: int, high: int) -> int:
        
        def dfs(root):
            total = 0
            if not root:
                return 0

            if low<=root.val<=high:
                total+= root.val

            # call left only when low range is smaller than value
            # meaning there could be more numbers on left that falls in rang e of [low, ]
            if low < root.val:
                total += dfs(root.left) 
            if high > root.val : 
                total += dfs(root.right) 
            return total 

        return dfs(root)
```

## Attempt 10 · 2023-12-04 12:27 IST · Accepted · Python3

[submission 1111986775](https://leetcode.com/submissions/detail/1111986775/) · tests 41/41 · runtime 160 ms (beats 5.5%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def rangeSumBST1(self, root: Optional[TreeNode], low: int, high: int) -> int:
        '''
        call left only when low is less than root.val and same for high

        '''
        def dfs(root):
            total = 0
            if not root:
                return 0

            if low<=root.val<=high:
                total+= root.val

            # call left only when low range is smaller than value
            # meaning there could be more numbers on left that falls in rang e of [low, ]
            if low < root.val:
                total += dfs(root.left) 
            if high > root.val : 
                total += dfs(root.right) 
            return total 

        return dfs(root)

    def rangeSumBST(self, root: Optional[TreeNode], low: int, high: int) -> int:
        if not root:
            return 
        stack = [root]
        total = 0

        while stack:
            node = stack.pop()
            if node:
                if low <= node.val <= high:
                    total += node.val

                if low< node.val:
                    stack.append(node.left)
                if high>node.val:
                    stack.append(node.right)

        return total
```

## Attempt 11 · 2023-12-04 12:28 IST · Accepted · Python3

[submission 1111986984](https://leetcode.com/submissions/detail/1111986984/) · tests 41/41 · runtime 165 ms (beats 5.5%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def rangeSumBST1(self, root: Optional[TreeNode], low: int, high: int) -> int:
        '''
        call left only when low is less than root.val and same for high

        '''
        def dfs(root):
            total = 0
            if not root:
                return 0

            if low<=root.val<=high:
                total+= root.val

            # call left only when low range is smaller than value
            # meaning there could be more numbers on left that falls in rang e of [low, ]
            if low < root.val:
                total += dfs(root.left) 
            if high > root.val : 
                total += dfs(root.right) 
            return total 

        return dfs(root)

    def rangeSumBST(self, root: Optional[TreeNode], low: int, high: int) -> int:
        if not root:
            return 
        stack = [root]
        total = 0

        while stack:
            node = stack.pop()
            
            # for iterative 
            # remember to check null node
            if node:
                if low <= node.val <= high:
                    total += node.val

                if low< node.val:
                    stack.append(node.left)
                if high>node.val:
                    stack.append(node.right)

        return total
```

## Attempt 12 · 2024-01-14 20:30 IST · Accepted · Python3

[submission 1146073032](https://leetcode.com/submissions/detail/1146073032/) · tests 41/41 · runtime 102 ms (beats 5.5%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def rangeSumBST1(self, root: Optional[TreeNode], low: int, high: int) -> int:
        '''
        call left only when low is less than root.val and same for high

        '''
        def dfs(root):
            total = 0
            if not root:
                return 0

            if low<=root.val<=high:
                total+= root.val

            # call left only when low range is smaller than value
            # meaning there could be more numbers on left that falls in rang e of [low, ]
            if low < root.val:
                total += dfs(root.left) 
            if high > root.val : 
                total += dfs(root.right) 
            return total 

        return dfs(root)

    def rangeSumBST(self, root: Optional[TreeNode], low: int, high: int) -> int:
        if not root:
            return 
        stack = [root]
        total = 0

        while stack:
            node = stack.pop()
            
            # for iterative 
            # remember to check null node
            if node:
                if low <= node.val <= high:
                    total += node.val

                if low< node.val:
                    stack.append(node.left)
                if high>node.val:
                    stack.append(node.right)

        return total

    def rangeSumBST(self, root: Optional[TreeNode], low: int, high: int) -> int:
        def dfs(root):
            if not root:
                return 0

            total = 0

            if low <=root.val <= high:
                total += root.val

            if low < root.val:
                total += dfs(root.left)
            if high > root.val:
                total += dfs(root.right)

            return total 
        return dfs(root)


    def rangeSumBST(self, root: Optional[TreeNode], low: int, high: int) -> int:
        # inorder traversal won't take advantage of the fact that its bst
        # stacking only when within range 

        stack = [root]
        total = 0
        while stack:
            root = stack.pop()

            if root:
                if low <=root.val <= high:
                    total += root.val

                if low < root.val:
                    stack.append(root.left)
            
                if high > root.val:
                    stack.append(root.right)
        return total
```

## Attempt 13 · 2025-07-16 12:04 IST · Accepted · C++

[submission 1699707053](https://leetcode.com/submissions/detail/1699707053/) · tests 41/41 · runtime 0 ms (beats 100%)

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
    int rangeSumBST(TreeNode* root, int low, int high) {
        if (!root) return 0;

        if(root->val < low) return rangeSumBST(root->right, low, high);
        if(root->val > high) return rangeSumBST(root->left, low, high);

        return root->val + rangeSumBST(root->left, low, high) + rangeSumBST(root->right, low, high);
    }
};
```
