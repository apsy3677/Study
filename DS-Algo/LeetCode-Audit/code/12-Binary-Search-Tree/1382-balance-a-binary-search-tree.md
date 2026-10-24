# 1382. Balance a Binary Search Tree

[Problem](https://leetcode.com/problems/balance-a-binary-search-tree/) · Medium · Binary Search Tree → Inorder + rebuild

LeetCode tags: divide-and-conquer, greedy, tree, depth-first-search, binary-search-tree, binary-tree

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2024-02-06 10:51 IST · Accepted · Python3

[submission 1167477754](https://leetcode.com/submissions/detail/1167477754/) · tests 17/17 · runtime 199 ms (beats 6.2%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def balanceBST(self, root: TreeNode) -> TreeNode:
        nodes = []
        def inorder(root):
            nonlocal nodes
            if not root:
                return None
            
            inorder(root.left)
            nodes.append(root)
            inorder(root.right)

        def build_tree(nodes):
            if not nodes:
                return 
            mid = len(nodes) //2

            nodes[mid].left = build_tree(nodes[:mid])
            nodes[mid].right= build_tree(nodes[mid+1:])

            return nodes[mid]

        inorder(root)
        return build_tree(nodes)
```
