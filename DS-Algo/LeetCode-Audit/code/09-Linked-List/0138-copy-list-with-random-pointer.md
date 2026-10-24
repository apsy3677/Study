# 138. Copy List with Random Pointer

[Problem](https://leetcode.com/problems/copy-list-with-random-pointer/) · Medium · Linked List → Hash map / interleave

LeetCode tags: hash-table, linked-list

Attempts since Mar 2023: 13 · accepted: 11 · failed before first AC: 0

## Attempt 1 · 2023-05-19 18:04 IST · Accepted · C++

[submission 953335770](https://leetcode.com/submissions/detail/953335770/) · tests 19/19 · runtime 10 ms (beats 18.9%)

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        Node * curr = head, *newHead = nullptr;
        unordered_map<Node*, Node *> map;

        while(curr){
            Node * newNode = nullptr;
            newNode = new Node(curr->val);
            if(!newHead){
                newHead = newNode;
            }
            map[curr] = newNode;
            curr= curr->next;
        }

        curr = head;

        while(curr){
            map[curr]->next = map[curr->next];
            map[curr]->random = map[curr->random];
            curr = curr->next;
        }
        return newHead;
    }
};
```

## Attempt 2 · 2023-05-19 18:17 IST · Accepted · C++

[submission 953341041](https://leetcode.com/submissions/detail/953341041/) · tests 19/19 · runtime 12 ms (beats 14.0%)

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

Node *getNode(Node *node, unordered_map<Node*, Node *> &map){
    if(!node) return nullptr;
    if(map.find(node) != map.end()) return map[node];

    map[node]  = new Node(node->val);
    return map[node];
}

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head) return head;
        Node * curr = head, *newHead = nullptr;
        unordered_map<Node*, Node *> map;
        newHead = new Node(curr->val);
        map[curr] = newHead;
        
        while(curr){
            
            newHead->next = getNode(curr->next, map);
            newHead->random = getNode(curr->random, map);

            curr= curr->next;
            newHead = newHead->next;
        }

        return map[head];
    }
};
```

## Attempt 3 · 2023-05-19 18:19 IST · Accepted · C++

[submission 953341670](https://leetcode.com/submissions/detail/953341670/) · tests 19/19 · runtime 8 ms (beats 30.2%)

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

Node *getNode(Node *node, unordered_map<Node*, Node *> &map){
    if(!node) return nullptr;
    if(map.find(node) != map.end()) return map[node];

    map[node]  = new Node(node->val);
    return map[node];
}

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head) return head;

        Node * curr = head, *newHead = nullptr;
        unordered_map<Node*, Node *> map;

        while(curr){
            Node * newNode = nullptr;
            newNode = new Node(curr->val);
            if(!newHead){
                newHead = newNode;
            }
            map[curr] = newNode;
            curr= curr->next;
        }

        curr = head;

        while(curr){
            map[curr]->next = map[curr->next];
            map[curr]->random = map[curr->random];
            curr = curr->next;
        }
        return newHead;

        
    }
    Node * solution2(Node * head){
        if(!head) return nullptr;
        Node * curr = head, *newHead = nullptr;
        unordered_map<Node*, Node *> map;
        newHead = new Node(curr->val);
        map[curr] = newHead;

        while(curr){
            
            newHead->next = getNode(curr->next, map);
            newHead->random = getNode(curr->random, map);

            curr= curr->next;
            newHead = newHead->next;
        }

        return map[head];
    }
};
```

## Attempt 4 · 2023-05-20 13:48 IST · Accepted · C++

[submission 953787763](https://leetcode.com/submissions/detail/953787763/) · tests 19/19 · runtime 16 ms (beats 14.0%)

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

Node *getNode(Node *node, unordered_map<Node*, Node *> &map){
    if(!node) return nullptr;
    if(map.find(node) != map.end()) return map[node];

    map[node]  = new Node(node->val);
    return map[node];
}

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head) return head;

        Node * curr = head, *newHead = nullptr;
        unordered_map<Node*, Node *> map;

        while(curr){
            Node * newNode = nullptr;
            newNode = new Node(curr->val);
            if(!newHead){
                newHead = newNode;
            }
            map[curr] = newNode;
            curr= curr->next;
        }

        curr = head;

        while(curr){
            map[curr]->next = map[curr->next];
            map[curr]->random = map[curr->random];
            curr = curr->next;
        }
        return newHead;

        
    }
    Node * solution2(Node * head){
        if(!head) return nullptr;
        Node * curr = head, *newHead = nullptr;
        unordered_map<Node*, Node *> map;
        newHead = new Node(curr->val);
        map[curr] = newHead;

        while(curr){
            
            newHead->next = getNode(curr->next, map);
            newHead->random = getNode(curr->random, map);

            curr= curr->next;
            newHead = newHead->next;
        }

        return map[head];
    }
};
```

## Attempt 5 · 2023-05-20 13:49 IST · Accepted · C++

[submission 953787961](https://leetcode.com/submissions/detail/953787961/) · tests 19/19 · runtime 17 ms (beats 14.0%)

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

Node *getNode(Node *node, unordered_map<Node*, Node *> &map){
    if(!node) return nullptr;
    if(map.find(node) != map.end()) return map[node];

    map[node]  = new Node(node->val);
    return map[node];
}

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head) return head;
        return solution2(head);
        Node * curr = head, *newHead = nullptr;
        unordered_map<Node*, Node *> map;

        while(curr){
            Node * newNode = nullptr;
            newNode = new Node(curr->val);
            if(!newHead){
                newHead = newNode;
            }
            map[curr] = newNode;
            curr= curr->next;
        }

        curr = head;

        while(curr){
            map[curr]->next = map[curr->next];
            map[curr]->random = map[curr->random];
            curr = curr->next;
        }
        return newHead;

        
    }
    Node * solution2(Node * head){
        if(!head) return nullptr;
        Node * curr = head, *newHead = nullptr;
        unordered_map<Node*, Node *> map;
        newHead = new Node(curr->val);
        map[curr] = newHead;

        while(curr){
            
            newHead->next = getNode(curr->next, map);
            newHead->random = getNode(curr->random, map);

            curr= curr->next;
            newHead = newHead->next;
        }

        return map[head];
    }
};
```

## Attempt 6 · 2023-11-22 04:29 IST · Accepted · Python3

[submission 1103788126](https://leetcode.com/submissions/detail/1103788126/) · tests 19/19 · runtime 47 ms (beats 64.0%)

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random
"""

class Solution:
    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        visited = {}

        def copyNode(head):
            if not head:
                return 
            if head in visited:
                return visited[head]

            node = Node(head.val, None, None)
            visited[head] = node
            node.next = copyNode(head.next)
            node.random = copyNode(head.random)

            return node
        
        return copyNode(head)
```

## Attempt 7 · 2023-11-22 04:30 IST · Accepted · Python3

[submission 1103788203](https://leetcode.com/submissions/detail/1103788203/) · tests 19/19 · runtime 44 ms (beats 79.3%)

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random
"""

class Solution:
    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        visited = {}

        def copyNode(head):
            if not head:
                return 
            if head in visited:
                return visited[head]

            node = Node(head.val, None, None)
            visited[head] = node
            node.next = copyNode(head.next)
            node.random = copyNode(head.random)

            return node
        
        return copyNode(head)
```

## Attempt 8 · 2023-12-05 00:11 IST · Accepted · Python3

[submission 1112368671](https://leetcode.com/submissions/detail/1112368671/) · tests 19/19 · runtime 42 ms (beats 88.2%)

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random
"""

class Solution:
    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        '''
        approach 1 - dfs with visited to keep track of old and new node O(N)
        approach 2 - iterative with O(N) - 
        for iterative solution with linked list - you traverse until null node
        while old_node:

        approach 3 - interveave old and new nodes without needing to keep track of visited to find referenced node. O(1)

        '''        

        visited = {} # old node -> new node
        def copyList(head_node):

            # 1. handle empty node
            if not head_node:
                return

            # 2. check visited and add visited
            if head_node in visited:
                return visited[head_node]

            newNode = Node(head_node.val)
            visited[head_node] = newNode

            # 3. process other pointers
            newNode.next = copyList(head_node.next)
            newNode.random = copyList(head_node.random)

            return newNode

        copyList(head)
        return visited[head]


    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        if not head:
            return head

        old_node = head

        # create new nodes for each node and interweave
        # and set next nodes
        while old_node:
            new_node = Node(old_node.val)
            old_node.next, new_node.next = new_node, old_node.next
            old_node = new_node.next

        old_node = head
        # set random pointer
        while old_node:
            old_node.next.random = old_node.random.next if old_node.random else None
            old_node = old_node.next.next

        # unweave
        old_node = head
        new_node = head.next
        head_new = head.next
        while old_node:
            old_node.next = old_node.next.next
            new_node.next = new_node.next.next if new_node.next else None

            old_node = old_node.next
            new_node = new_node.next

        return head_new
```

## Attempt 9 · 2024-01-02 00:51 IST · Accepted · Python3

[submission 1134008815](https://leetcode.com/submissions/detail/1134008815/) · tests 19/19 · runtime 46 ms (beats 70.7%)

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random
"""

class Solution:
    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        '''
        approach 1 - dfs with visited to keep track of old and new node O(N)
        approach 2 - iterative with O(N) - 
        for iterative solution with linked list - you traverse until null node
        while old_node:

        approach 3 - interveave old and new nodes without needing to keep track of visited to find referenced node. O(1)

        '''        

        visited = {} # old node -> new node
        def copyList(head_node):

            # 1. handle empty node
            if not head_node:
                return

            # 2. check visited and add visited
            if head_node in visited:
                return visited[head_node]

            newNode = Node(head_node.val)
            visited[head_node] = newNode

            # 3. process other pointers
            newNode.next = copyList(head_node.next)
            newNode.random = copyList(head_node.random)

            return newNode

        copyList(head)
        return visited[head]


    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        if not head:
            return head

        
        old_node = head

        # create new nodes for each node and interweave
        # and set next nodes
        while old_node:
            new_node = Node(old_node.val)
            old_node.next, new_node.next = new_node, old_node.next
            old_node = new_node.next

        old_node = head
        # set random pointer
        while old_node:
            old_node.next.random = old_node.random.next if old_node.random else None
            old_node = old_node.next.next

        # unweave
        old_node = head
        new_node = head.next
        head_new = head.next
        while old_node:
            old_node.next = old_node.next.next
            new_node.next = new_node.next.next if new_node.next else None

            old_node = old_node.next
            new_node = new_node.next

        return head_new


    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':

        if not head:
            return head


        # point to the same start node
        curr = head

        # weave 

        # 1. create and weave new nodes
        # after each original node - create a new node and link 
        while curr:
            new_node = Node(curr.val)
            # link new pointer 
            curr.next, new_node.next = new_node,curr.next

            # take care of assigning the correct node here
            curr = new_node.next

        # now new node isafter original node
        # now just go ahead and link random nodes

        # 2. weave random nodes
        curr = head
        while curr:
            curr.next.random =  curr.random.next if curr.random else None

            # take care to get next of original node
            curr = curr.next.next

        #3. unweave
        # use a pointer to first new node and first old node
        # to return result keep new head in new_head
        old_node = head
        new_node = head.next
        new_head = head.next

        while old_node:
            old_node.next = old_node.next.next if old_node.next else None
            new_node.next = new_node.next.next  if new_node.next else None

            old_node = old_node.next
            new_node = new_node.next
        return new_head
```

## Attempt 10 · 2024-01-02 00:54 IST · Runtime Error · Python3

[submission 1134010731](https://leetcode.com/submissions/detail/1134010731/) · tests 3/19

Failing input:

```text
[]
```

Expected:

```text
[]
```

Runtime error:

```text
KeyError: None
           ~~~~~~~^^^^^^
    return visited[head]
Line 147 in copyRandomList (Solution.py)
               ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    copyHead = Solution().copyRandomList(head)
Line 254 in _driver (Solution.py)
    _driver()
Line 267 in <module> (Solution.py)
```

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random
"""

class Solution:
    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        '''
        approach 1 - dfs with visited to keep track of old and new node O(N)
        approach 2 - iterative with O(N) - 
        for iterative solution with linked list - you traverse until null node
        while old_node:

        approach 3 - interveave old and new nodes without needing to keep track of visited to find referenced node. O(1)

        '''        

        visited = {} # old node -> new node
        def copyList(head_node):

            # 1. handle empty node
            if not head_node:
                return

            # 2. check visited and add visited
            if head_node in visited:
                return visited[head_node]

            newNode = Node(head_node.val)
            visited[head_node] = newNode

            # 3. process other pointers
            newNode.next = copyList(head_node.next)
            newNode.random = copyList(head_node.random)

            return newNode

        copyList(head)
        return visited[head]


    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        if not head:
            return head

        
        old_node = head

        # create new nodes for each node and interweave
        # and set next nodes
        while old_node:
            new_node = Node(old_node.val)
            old_node.next, new_node.next = new_node, old_node.next
            old_node = new_node.next

        old_node = head
        # set random pointer
        while old_node:
            old_node.next.random = old_node.random.next if old_node.random else None
            old_node = old_node.next.next

        # unweave
        old_node = head
        new_node = head.next
        head_new = head.next
        while old_node:
            old_node.next = old_node.next.next
            new_node.next = new_node.next.next if new_node.next else None

            old_node = old_node.next
            new_node = new_node.next

        return head_new


    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':

        if not head:
            return head


        # point to the same start node
        curr = head

        # weave 

        # 1. create and weave new nodes
        # after each original node - create a new node and link 
        while curr:
            new_node = Node(curr.val)
            # link new pointer 
            curr.next, new_node.next = new_node,curr.next

            # take care of assigning the correct node here
            curr = new_node.next

        # now new node isafter original node
        # now just go ahead and link random nodes

        # 2. weave random nodes
        curr = head
        while curr:
            curr.next.random =  curr.random.next if curr.random else None

            # take care to get next of original node
            curr = curr.next.next

        #3. unweave
        # use a pointer to first new node and first old node
        # to return result keep new head in new_head
        old_node = head
        new_node = head.next
        new_head = head.next

        while old_node:
            old_node.next = old_node.next.next if old_node.next else None
            new_node.next = new_node.next.next  if new_node.next else None

            old_node = old_node.next
            new_node = new_node.next
        return new_head

    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        
        visited = {} # keep track of old and new node
        def dfs(node):
            if not node:
                return 

            if node in visited:
                return visited[node]

            # create new node and add to visited
            new_node = Node(node.val)
            visited[node] = new_node

            new_node.next = dfs(node.next)
            new_node.random = dfs(node.random)

            return new_node

        dfs(head)
        return visited[head]
```

## Attempt 11 · 2024-01-02 00:55 IST · Runtime Error · Python3

[submission 1134011422](https://leetcode.com/submissions/detail/1134011422/) · tests 3/19

Failing input:

```text
[]
```

Expected:

```text
[]
```

Runtime error:

```text
KeyError: None
           ~~~~~~~^^^^^^
    return visited[head]
Line 147 in copyRandomList (Solution.py)
               ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    copyHead = Solution().copyRandomList(head)
Line 254 in _driver (Solution.py)
    _driver()
Line 267 in <module> (Solution.py)
```

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random
"""

class Solution:
    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        '''
        approach 1 - dfs with visited to keep track of old and new node O(N)
        approach 2 - iterative with O(N) - 
        for iterative solution with linked list - you traverse until null node
        while old_node:

        approach 3 - interveave old and new nodes without needing to keep track of visited to find referenced node. O(1)

        '''        

        visited = {} # old node -> new node
        def copyList(head_node):

            # 1. handle empty node
            if not head_node:
                return

            # 2. check visited and add visited
            if head_node in visited:
                return visited[head_node]

            newNode = Node(head_node.val)
            visited[head_node] = newNode

            # 3. process other pointers
            newNode.next = copyList(head_node.next)
            newNode.random = copyList(head_node.random)

            return newNode

        copyList(head)
        return visited[head]


    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        if not head:
            return head

        
        old_node = head

        # create new nodes for each node and interweave
        # and set next nodes
        while old_node:
            new_node = Node(old_node.val)
            old_node.next, new_node.next = new_node, old_node.next
            old_node = new_node.next

        old_node = head
        # set random pointer
        while old_node:
            old_node.next.random = old_node.random.next if old_node.random else None
            old_node = old_node.next.next

        # unweave
        old_node = head
        new_node = head.next
        head_new = head.next
        while old_node:
            old_node.next = old_node.next.next
            new_node.next = new_node.next.next if new_node.next else None

            old_node = old_node.next
            new_node = new_node.next

        return head_new


    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':

        if not head:
            return head


        # point to the same start node
        curr = head

        # weave 

        # 1. create and weave new nodes
        # after each original node - create a new node and link 
        while curr:
            new_node = Node(curr.val)
            # link new pointer 
            curr.next, new_node.next = new_node,curr.next

            # take care of assigning the correct node here
            curr = new_node.next

        # now new node isafter original node
        # now just go ahead and link random nodes

        # 2. weave random nodes
        curr = head
        while curr:
            curr.next.random =  curr.random.next if curr.random else None

            # take care to get next of original node
            curr = curr.next.next

        #3. unweave
        # use a pointer to first new node and first old node
        # to return result keep new head in new_head
        old_node = head
        new_node = head.next
        new_head = head.next

        while old_node:
            old_node.next = old_node.next.next if old_node.next else None
            new_node.next = new_node.next.next  if new_node.next else None

            old_node = old_node.next
            new_node = new_node.next
        return new_head

    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        
        visited = {} # keep track of old and new node
        def copy_list(node):
            if not node:
                return 

            if node in visited:
                return visited[node]

            # create new node and add to visited
            new_node = Node(node.val)
            visited[node] = new_node

            new_node.next = copy_list(node.next)
            new_node.random = copy_list(node.random)

            return new_node

        copy_list(head)
        return visited[head]
```

## Attempt 12 · 2024-01-02 00:56 IST · Accepted · Python3

[submission 1134011626](https://leetcode.com/submissions/detail/1134011626/) · tests 19/19 · runtime 77 ms (beats 6.0%)

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random
"""

class Solution:
    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        '''
        approach 1 - dfs with visited to keep track of old and new node O(N)
        approach 2 - iterative with O(N) - 
        for iterative solution with linked list - you traverse until null node
        while old_node:

        approach 3 - interveave old and new nodes without needing to keep track of visited to find referenced node. O(1)

        '''        

        visited = {} # old node -> new node
        def copyList(head_node):

            # 1. handle empty node
            if not head_node:
                return

            # 2. check visited and add visited
            if head_node in visited:
                return visited[head_node]

            newNode = Node(head_node.val)
            visited[head_node] = newNode

            # 3. process other pointers
            newNode.next = copyList(head_node.next)
            newNode.random = copyList(head_node.random)

            return newNode

        copyList(head)
        return visited[head]


    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        if not head:
            return head

        
        old_node = head

        # create new nodes for each node and interweave
        # and set next nodes
        while old_node:
            new_node = Node(old_node.val)
            old_node.next, new_node.next = new_node, old_node.next
            old_node = new_node.next

        old_node = head
        # set random pointer
        while old_node:
            old_node.next.random = old_node.random.next if old_node.random else None
            old_node = old_node.next.next

        # unweave
        old_node = head
        new_node = head.next
        head_new = head.next
        while old_node:
            old_node.next = old_node.next.next
            new_node.next = new_node.next.next if new_node.next else None

            old_node = old_node.next
            new_node = new_node.next

        return head_new


    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':

        if not head:
            return head


        # point to the same start node
        curr = head

        # weave 

        # 1. create and weave new nodes
        # after each original node - create a new node and link 
        while curr:
            new_node = Node(curr.val)
            # link new pointer 
            curr.next, new_node.next = new_node,curr.next

            # take care of assigning the correct node here
            curr = new_node.next

        # now new node isafter original node
        # now just go ahead and link random nodes

        # 2. weave random nodes
        curr = head
        while curr:
            curr.next.random =  curr.random.next if curr.random else None

            # take care to get next of original node
            curr = curr.next.next

        #3. unweave
        # use a pointer to first new node and first old node
        # to return result keep new head in new_head
        old_node = head
        new_node = head.next
        new_head = head.next

        while old_node:
            old_node.next = old_node.next.next if old_node.next else None
            new_node.next = new_node.next.next  if new_node.next else None

            old_node = old_node.next
            new_node = new_node.next
        return new_head

    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        if not head:
            return 
            
        visited = {} # keep track of old and new node
        def copy_list(node):
            if not node:
                return 

            if node in visited:
                return visited[node]

            # create new node and add to visited
            new_node = Node(node.val)
            visited[node] = new_node

            new_node.next = copy_list(node.next)
            new_node.random = copy_list(node.random)

            return new_node

        copy_list(head)
        return visited[head]
```

## Attempt 13 · 2024-01-02 00:56 IST · Accepted · Python3

[submission 1134011763](https://leetcode.com/submissions/detail/1134011763/) · tests 19/19 · runtime 84 ms (beats 6.0%)

```python
"""
# Definition for a Node.
class Node:
    def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random
"""

class Solution:
    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        '''
        approach 1 - dfs with visited to keep track of old and new node O(N)
        approach 2 - iterative with O(N) - 
        for iterative solution with linked list - you traverse until null node
        while old_node:

        approach 3 - interveave old and new nodes without needing to keep track of visited to find referenced node. O(1)

        '''        

        visited = {} # old node -> new node
        def copyList(head_node):

            # 1. handle empty node
            if not head_node:
                return

            # 2. check visited and add visited
            if head_node in visited:
                return visited[head_node]

            newNode = Node(head_node.val)
            visited[head_node] = newNode

            # 3. process other pointers
            newNode.next = copyList(head_node.next)
            newNode.random = copyList(head_node.random)

            return newNode

        copyList(head)
        return visited[head]


    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        if not head:
            return head

        
        old_node = head

        # create new nodes for each node and interweave
        # and set next nodes
        while old_node:
            new_node = Node(old_node.val)
            old_node.next, new_node.next = new_node, old_node.next
            old_node = new_node.next

        old_node = head
        # set random pointer
        while old_node:
            old_node.next.random = old_node.random.next if old_node.random else None
            old_node = old_node.next.next

        # unweave
        old_node = head
        new_node = head.next
        head_new = head.next
        while old_node:
            old_node.next = old_node.next.next
            new_node.next = new_node.next.next if new_node.next else None

            old_node = old_node.next
            new_node = new_node.next

        return head_new


    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':

        if not head:
            return head


        # point to the same start node
        curr = head

        # weave 

        # 1. create and weave new nodes
        # after each original node - create a new node and link 
        while curr:
            new_node = Node(curr.val)
            # link new pointer 
            curr.next, new_node.next = new_node,curr.next

            # take care of assigning the correct node here
            curr = new_node.next

        # now new node isafter original node
        # now just go ahead and link random nodes

        # 2. weave random nodes
        curr = head
        while curr:
            curr.next.random =  curr.random.next if curr.random else None

            # take care to get next of original node
            curr = curr.next.next

        #3. unweave
        # use a pointer to first new node and first old node
        # to return result keep new head in new_head
        old_node = head
        new_node = head.next
        new_head = head.next

        while old_node:
            old_node.next = old_node.next.next if old_node.next else None
            new_node.next = new_node.next.next  if new_node.next else None

            old_node = old_node.next
            new_node = new_node.next
        return new_head

    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        if not head:
            return 

        visited = {} # keep track of old and new node
        def copy_list(node):
            if not node:
                return 

            if node in visited:
                return visited[node]

            # create new node and add to visited
            new_node = Node(node.val)
            visited[node] = new_node

            new_node.next = copy_list(node.next)
            new_node.random = copy_list(node.random)

            return new_node

        return copy_list(head)
        # return visited[head]
```
