# 116. Populating Next Right Pointers in Each Node

[Problem](https://leetcode.com/problems/populating-next-right-pointers-in-each-node/) · Medium · Binary Tree (BFS / Level Order) → Level linking

LeetCode tags: linked-list, tree, depth-first-search, breadth-first-search, binary-tree

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-25 15:58 IST · Accepted · C++

[submission 921787275](https://leetcode.com/submissions/detail/921787275/) · tests 59/59 · runtime 19 ms (beats 11.8%)

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        if(!root)   return root;

        queue<Node*> qu;
        qu.push(root);

        while(!qu.empty()){
            int sz = qu.size();
            Node *prev = NULL;
            for(int i=0;i<sz;i++){
                Node * curr = qu.front();
                qu.pop();
                if(curr) curr->next = prev;
                prev = curr;

                // push children in right to left order 
                if(curr->right) qu.push(curr->right);
                if(curr->left) qu.push(curr->left);
            }
        }
        return root;
    }
};
```
