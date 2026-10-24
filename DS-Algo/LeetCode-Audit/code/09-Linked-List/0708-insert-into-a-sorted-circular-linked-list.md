# 708. Insert into a Sorted Circular Linked List

[Problem](https://leetcode.com/problems/insert-into-a-sorted-circular-linked-list/) · Medium · Linked List → Circular insert

LeetCode tags: linked-list

Attempts since Mar 2023: 7 · accepted: 3 · failed before first AC: 1

## Attempt 1 · 2023-11-23 01:20 IST · Wrong Answer · Python3

[submission 1104409561](https://leetcode.com/submissions/detail/1104409561/) · tests 104/108

Failing input:

```text
[3,3,5]
0
```

Expected:

```text
[3,3,5,0]
```

Your output:

```text
[3,0,3,5]
```

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, next=None):
        self.val = val
        self.next = next
"""

class Solution:
    def insert(self, head: 'Optional[Node]', insertVal: int) -> 'Node':

        newNode = Node(insertVal)

        if not head:
            newNode.next = newNode
            return newNode
        print(head.val)
        prev, curr = head, head.next

        while True:
            print(curr.val, prev.val)
            if prev.val <= insertVal <= curr.val or (prev.val>= curr.val and (insertVal >= prev.val or insertVal <= curr.val)):
                prev.next = newNode
                newNode.next = curr
                return head
            if curr == head:
                break
            prev, curr = curr, curr.next

        return head
```

## Attempt 2 · 2023-11-23 01:29 IST · Accepted · Python3

[submission 1104413974](https://leetcode.com/submissions/detail/1104413974/) · tests 108/108 · runtime 40 ms (beats 93.8%)

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, next=None):
        self.val = val
        self.next = next
"""

class Solution:
    def insert(self, head: 'Optional[Node]', insertVal: int) -> 'Node':

        newNode = Node(insertVal)

        if not head:
            newNode.next = newNode
            return newNode
        print(head.val)
        prev, curr = head, head.next

        while True:
            print(curr.val, prev.val)
            if prev.val <= insertVal <= curr.val or (prev.val> curr.val and (insertVal >= prev.val or insertVal <= curr.val)):
                prev.next = newNode
                newNode.next = curr
                return head
            if curr == head:
                break
            prev, curr = curr, curr.next

        # Insert at the end (back to head without finding a spot)
        prev.next = newNode
        newNode.next = curr
        return head
```

## Attempt 3 · 2023-11-23 01:32 IST · Accepted · Python3

[submission 1104415209](https://leetcode.com/submissions/detail/1104415209/) · tests 108/108 · runtime 46 ms (beats 70.9%)

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, next=None):
        self.val = val
        self.next = next
"""

class Solution:
    def insert(self, head: 'Optional[Node]', insertVal: int) -> 'Node':

        newNode = Node(insertVal)

        if not head:
            newNode.next = newNode
            return newNode
        prev, curr = head, head.next

        while True:
            # 1. lies in between nodes or  
            # 2. lies between head and tail =-largest and smallest
            # if you put equals in prev.val>curr.val it will fail for 3 3 5 if insert val is 0 
            if prev.val <= insertVal <= curr.val or (prev.val> curr.val and (insertVal >= prev.val or insertVal <= curr.val)):
                prev.next = newNode
                newNode.next = curr
                return head
            if curr == head:
                break
            prev, curr = curr, curr.next

        # 1. if all values are same in the linked list or
        # 2.  single node
        prev.next = newNode
        newNode.next = curr
        return head
```

## Attempt 4 · 2023-12-02 05:55 IST · Wrong Answer · Python3

[submission 1110526139](https://leetcode.com/submissions/detail/1110526139/) · tests 107/108

Failing input:

```text
[1,3,5]
3
```

Expected:

```text
[1,3,3,5]
```

Your output:

```text
[1,3,5,3]
```

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, next=None):
        self.val = val
        self.next = next
"""

class Solution:
    def insert(self, head: 'Optional[Node]', insertVal: int) -> 'Node':

        newNode = Node(insertVal)

        if not head:
            newNode.next = newNode
            return newNode
        prev, curr = head, head.next

        while True:
            # 1. lies in between nodes or  
            # 2. lies between head and tail =-largest and smallest
            # if you put equals in prev.val>curr.val it will fail for 3 3 5 if insert val is 0 
            if prev.val < insertVal < curr.val or (prev.val> curr.val and (insertVal >= prev.val or insertVal <= curr.val)):
                prev.next = newNode
                newNode.next = curr
                return head
            if curr == head:
                break
            prev, curr = curr, curr.next

        # 1. if all values are same in the linked list or
        # 2.  single node
        prev.next = newNode
        newNode.next = curr
        return head
```

## Attempt 5 · 2023-12-02 05:58 IST · Wrong Answer · Python3

[submission 1110526949](https://leetcode.com/submissions/detail/1110526949/) · tests 105/108

Failing input:

```text
[1]
0
```

Expected:

```text
[1,0]
```

Your output:

```text
[1]
```

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, next=None):
        self.val = val
        self.next = next
"""

class Solution:
    def insert(self, head: 'Optional[Node]', insertVal: int) -> 'Node':

        newNode = Node(insertVal)

        if not head:
            newNode.next = newNode
            return newNode
        prev, curr = head, head.next

        while True:
            # 1. lies in between nodes or  
            # 2. lies between head and tail =-largest and smallest
            # if you put equals in prev.val>curr.val it will fail for 3 3 5 if insert val is 0 
            if prev.val <= insertVal <= curr.val or (prev.val> curr.val and (insertVal >= prev.val or insertVal <= curr.val)):
                prev.next = newNode
                newNode.next = curr
                return head
            if curr == head:
                break
            prev, curr = curr, curr.next

        # 1. if all values are same in the linked list or
        # 2.  single node
        #prev.next = newNode
        #newNode.next = curr
        return head
```

## Attempt 6 · 2023-12-02 05:58 IST · Wrong Answer · Python3

[submission 1110527185](https://leetcode.com/submissions/detail/1110527185/)

_Code not returned by LeetCode._

## Attempt 7 · 2023-12-31 01:14 IST · Accepted · Python3

[submission 1132452299](https://leetcode.com/submissions/detail/1132452299/) · tests 108/108 · runtime 66 ms (beats 6.6%)

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, next=None):
        self.val = val
        self.next = next
"""

class Solution:
    def insert(self, head: 'Optional[Node]', insertVal: int) -> 'Node':

        newNode = Node(insertVal)

        if not head:
            newNode.next = newNode
            return newNode
        prev, curr = head, head.next

        while True:
            # 1. lies in between nodes or  
            # 2. lies between head and tail =-largest and smallest
            # if you put equals in prev.val>curr.val it will fail for 3 3 5 if insert val is 0 
            if prev.val <= insertVal <= curr.val or (prev.val > curr.val and (insertVal >= prev.val or insertVal <= curr.val)):
                prev.next = newNode
                newNode.next = curr
                return head
            if curr == head:
                break
            prev, curr = curr, curr.next

        #print(prev.val, curr.val)
        # 1. if all values are same in the linked list [3,3,3] and insert 0
        # 2.  single node
        prev.next = newNode
        newNode.next = curr
        return head



    def insert(self, head: 'Optional[Node]', insertVal: int) -> 'Node':
        node = Node(insertVal)

        # empty node
        if not head and insertVal:
               node.next = node 
               return node

        prev, curr = head, head.next

        while True:
            # 1. lies in between nodes or equal to nodes
            # 2. end of list where prev>curr, strictly
            if (prev.val <= insertVal <= curr.val) or ((prev.val <= insertVal or insertVal <= curr.val) and prev.val > curr.val):
                prev.next = node
                node.next = curr
                return head
            
            prev = curr
            curr = curr.next

            if curr == head:
                break

        # when all same and insertVal is either greater or smaller
        prev.next = node
        node.next = curr
        
        return head
        
    def insert(self, head: 'Optional[Node]', insertVal: int) -> 'Node':
        new_node = Node(insertVal)

        #1. empty list
        if not head:
            new_node.next = new_node
            return new_node

        prev, curr = head, head.next


        while True:
            #2. value lies between nodes
            if  curr.val>=insertVal>=prev.val or ((prev.val > curr.val) and (
                insertVal <= curr.val or insertVal >= prev.val
            )):
                prev.next = new_node
                new_node.next = curr
                return head

            if curr == head:
                break

            prev, curr = curr, curr.next

        # when all values are same or single ndoe
        prev.next = new_node
        new_node.next =curr
        return head
```
