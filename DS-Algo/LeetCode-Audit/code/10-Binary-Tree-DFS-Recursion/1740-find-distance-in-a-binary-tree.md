# 1740. Find Distance in a Binary Tree

[Problem](https://leetcode.com/problems/find-distance-in-a-binary-tree/) · Medium · Binary Tree (DFS & Recursion) → LCA + depth

LeetCode tags: hash-table, tree, depth-first-search, breadth-first-search, binary-tree, binary-lifting, lowest-common-ancestor

Attempts since Mar 2023: 4 · accepted: 4 · failed before first AC: 0

## Attempt 1 · 2023-03-25 21:08 IST · Accepted · C++

[submission 921919496](https://leetcode.com/submissions/detail/921919496/) · tests 58/58 · runtime 49 ms (beats 7.7%)

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
    TreeNode * Lca(TreeNode * root, int p, int q) {
        if (!root || root->val == p || root->val == q) {
            return root;
        }

        TreeNode * leftChild = Lca(root->left, p, q);
        TreeNode * rightChild = Lca(root->right, p, q);

        if (!leftChild) return rightChild;
        if (!rightChild) return leftChild;

        return root;
    }
    TreeNode * LCA(TreeNode* root, int p, int q){
        if(!root || root->val == p || root->val == q)  return root;

        TreeNode * left =LCA(root->left, p,q);
        TreeNode * right = LCA(root->right, p,q);

        if (!left) return right;
        if (!right) return left;

        return root;
        return !left ? right : !right ? left : root;
    }
    bool  dist(TreeNode * root, int val, int &dis){
        if(!root) return false;
        if(root->val == val ) return true;
        dis++;
        if(dist(root->left,val, dis)) return true;
        if(dist(root->right,val, dis)) return true;
        dis--;
        return false;
    }
    bool distance(TreeNode * node, int v, int& dist) {
        if (!node)
            return false;
        
        if (node->val == v) {
            return true;
        }

        dist++;
        if (distance(node->left, v, dist)) {
            return true;
        }
        if (distance(node->right, v, dist)) {
            return true;
        }
        dist--;
        return false;
    }
    
public:
    int findDistance(TreeNode* root, int p, int q) {
        TreeNode * lcaNode = LCA(root, p, q);
        int dist1 = 0;
        distance(lcaNode, p, dist1);
        int dist2 = 0;
        distance(lcaNode, q, dist2);
        return dist1 + dist2;

        TreeNode * lca = LCA(root, p, q);
        int lDis =0, rDis=0;
        lDis = distance(lca, p, lDis);
        rDis = distance(lca, q, rDis);
        return lDis + rDis;
    }
};
```

## Attempt 2 · 2023-03-25 21:09 IST · Accepted · C++

[submission 921919679](https://leetcode.com/submissions/detail/921919679/) · tests 58/58 · runtime 31 ms (beats 11.5%)

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
    TreeNode * Lca(TreeNode * root, int p, int q) {
        if (!root || root->val == p || root->val == q) {
            return root;
        }

        TreeNode * leftChild = Lca(root->left, p, q);
        TreeNode * rightChild = Lca(root->right, p, q);

        if (!leftChild) return rightChild;
        if (!rightChild) return leftChild;

        return root;
    }
    TreeNode * LCA(TreeNode* root, int p, int q){
        if(!root || root->val == p || root->val == q)  return root;

        TreeNode * left =LCA(root->left, p,q);
        TreeNode * right = LCA(root->right, p,q);

        // if (!left) return right;
        // if (!right) return left;

        // return root;
        return !left ? right : !right ? left : root;
    }
    bool  dist(TreeNode * root, int val, int &dis){
        if(!root) return false;
        if(root->val == val ) return true;
        dis++;
        if(dist(root->left,val, dis)) return true;
        if(dist(root->right,val, dis)) return true;
        dis--;
        return false;
    }
    bool distance(TreeNode * node, int v, int& dist) {
        if (!node)
            return false;
        
        if (node->val == v) {
            return true;
        }

        dist++;
        if (distance(node->left, v, dist)) {
            return true;
        }
        if (distance(node->right, v, dist)) {
            return true;
        }
        dist--;
        return false;
    }
    
public:
    int findDistance(TreeNode* root, int p, int q) {
        TreeNode * lcaNode = LCA(root, p, q);
        int dist1 = 0;
        distance(lcaNode, p, dist1);
        int dist2 = 0;
        distance(lcaNode, q, dist2);
        return dist1 + dist2;

        TreeNode * lca = LCA(root, p, q);
        int lDis =0, rDis=0;
        lDis = distance(lca, p, lDis);
        rDis = distance(lca, q, rDis);
        return lDis + rDis;
    }
};
```

## Attempt 3 · 2023-03-25 21:10 IST · Accepted · C++

[submission 921920168](https://leetcode.com/submissions/detail/921920168/) · tests 58/58 · runtime 41 ms (beats 11.5%)

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
    
    TreeNode * LCA(TreeNode* root, int p, int q){
        if(!root || root->val == p || root->val == q)  return root;

        TreeNode * left =LCA(root->left, p,q);
        TreeNode * right = LCA(root->right, p,q);

        // if (!left) return right;
        // if (!right) return left;

        // return root;
        return !left ? right : !right ? left : root;
    }
    bool  dist(TreeNode * root, int val, int &dis){
        if(!root) return false;
        if(root->val == val ) return true;
        dis++;
        if(dist(root->left,val, dis)) return true;
        if(dist(root->right,val, dis)) return true;
        dis--;
        return false;
    }
    
    
public:
    int findDistance(TreeNode* root, int p, int q) {

        TreeNode * lca = LCA(root, p, q);
        int lDis =0, rDis=0;
        dist(lca, p, lDis);
        dist(lca, q, rDis);
        return lDis + rDis;
    }
};
```

## Attempt 4 · 2023-03-25 21:15 IST · Accepted · C++

[submission 921922599](https://leetcode.com/submissions/detail/921922599/) · tests 58/58 · runtime 36 ms (beats 11.5%)

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
    
    TreeNode * LCA(TreeNode* root, int p, int q){
        if(!root || root->val == p || root->val == q)  return root;

        TreeNode * left =LCA(root->left, p,q);
        TreeNode * right = LCA(root->right, p,q);

        // if (!left) return right;
        // if (!right) return left;

        // return root;
        return !left ? right : !right ? left : root;
    }
    int  dist(TreeNode * root, int val, int level){
        if(!root) return -1;
        if(root->val == val ) return level;
        int l =dist(root->left,val, level+1);
        if(l!=-1) return l;

        int r =dist(root->right,val, level+1);
        return r;
    }
    
    
public:
    int findDistance(TreeNode* root, int p, int q) {

        TreeNode * lca = LCA(root, p, q);
        int lDis =0, rDis=0;
        lDis = dist(lca, p, lDis);
        rDis = dist(lca, q, rDis);
        return lDis + rDis;
    }
};
```
