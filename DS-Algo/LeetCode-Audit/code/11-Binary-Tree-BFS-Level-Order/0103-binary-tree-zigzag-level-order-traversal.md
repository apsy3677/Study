# 103. Binary Tree Zigzag Level Order Traversal

[Problem](https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/) · Medium · Binary Tree (BFS / Level Order) → Level order

LeetCode tags: tree, breadth-first-search, binary-tree

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2024-02-10 21:22 IST · Accepted · Python3

[submission 1171517062](https://leetcode.com/submissions/detail/1171517062/) · tests 33/33 · runtime 34 ms (beats 0.3%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def zigzagLevelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        if not root:
            return
        queue =deque([root])
        left_to_right = 1
        zigzag_nodes = []
        while queue:
            level_queue = deque()
            for _ in range(len(queue)):
                node = queue.popleft()

                if left_to_right==1:
                    level_queue.append(node.val)
                else:
                    level_queue.appendleft(node.val)
                
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
            
            zigzag_nodes.append(level_queue)
            left_to_right = -1 * left_to_right
        return zigzag_nodes
```
