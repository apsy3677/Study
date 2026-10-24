# 173. Binary Search Tree Iterator

[Problem](https://leetcode.com/problems/binary-search-tree-iterator/) · Medium · Binary Search Tree → Controlled inorder stack

LeetCode tags: stack, tree, design, binary-search-tree, binary-tree, iterator

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-12-21 22:20 IST · Accepted · Python3

[submission 1125232440](https://leetcode.com/submissions/detail/1125232440/) · tests 61/61 · runtime 65 ms (beats 5.8%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class BSTIterator:
    '''
    approach 1: created a inroder sorted list using inorder dfs and then return elements
    O(n) to initialize and then O(1)

    approach2: do controlled stack recursion for inorder
    # first time put all nodes do leftmost
    '''
    def _leftmost_inorder(self,root):
        # 
        while root:
            self.stack.append(root)
            root = root.left



    def __init__(self, root: Optional[TreeNode]):
        self.stack =[]
        self._leftmost_inorder(root)
        
    
    
    def next(self) -> int:
        topmost_node = self.stack.pop()

        self._leftmost_inorder(topmost_node.right)
        return topmost_node.val

    def hasNext(self) -> bool:
        return len(self.stack) >0 

# Your BSTIterator object will be instantiated and called as such:
# obj = BSTIterator(root)
# param_1 = obj.next()
# param_2 = obj.hasNext()
```

## Attempt 2 · 2025-07-19 14:41 IST · Accepted · C++

[submission 1703293806](https://leetcode.com/submissions/detail/1703293806/) · tests 61/61 · runtime 4 ms (beats 59.7%)

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
class BSTIterator {
    stack<TreeNode *> st;
    void traverse(TreeNode * root) {
        while (root) {
            st.push(root);
            root = root->left;
        }
    }
public:
    BSTIterator(TreeNode* root) {
        traverse(root);
    }
    
    int next() {
        if (st.empty()) 
            return -1; // not possible in this question
        auto node = st.top(); 
        st.pop();
        traverse(node->right); // traverse the right side of tree.
        return node->val;
    }
    
    bool hasNext() {
        return !st.empty();
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
```
