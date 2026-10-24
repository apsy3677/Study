# 1522. Diameter of N-Ary Tree

[Problem](https://leetcode.com/problems/diameter-of-n-ary-tree/) · Medium · DP: On Trees → Top-2 heights

LeetCode tags: tree, depth-first-search, dp-on-trees

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-12-11 21:14 IST · Accepted · Python3

[submission 1117330803](https://leetcode.com/submissions/detail/1117330803/) · tests 38/38 · runtime 45 ms (beats 92.2%)

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children if children is not None else []
"""

class Solution:
    def diameter(self, root: 'Node') -> int:
        """
        you need two max children to get the diameter with the root included 
        compared to binary there there could be multiple children so you can't simply do dia = height(left)+height(right)

        """
        if not root:
            return 0

        diameter = 0
        def height(node):
            nonlocal diameter
            if not node:
                return 0

            # when you find new max assign first as second and new as first
            max_length_first = 0
            max_length_second = 0 

            # for each children find its height and update first and second max
            for child in node.children:
                path_length = height(child)
                if path_length > max_length_first:
                    max_length_second = max_length_first
                    max_length_first = path_length
                elif path_length > max_length_second:
                    max_length_second = path_length

            # update diameter as max children sum
            diameter = max(diameter, max_length_first + max_length_second)


            # max child + 1 will be sent to parent
            return max_length_first + 1

        height(root)
        return diameter
```
