# 428. Serialize and Deserialize N-ary Tree

[Problem](https://leetcode.com/problems/serialize-and-deserialize-n-ary-tree/) · Hard · Binary Tree (DFS & Recursion) → Serialization

LeetCode tags: string, tree, depth-first-search, breadth-first-search

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-03-30 23:47 IST · Accepted · C++

[submission 924979950](https://leetcode.com/submissions/detail/924979950/) · tests 38/38 · runtime 47 ms (beats 16.7%)

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(Node* root) {
        if(!root) return "";
        queue<Node*> q;
        string retval = "";
        q.push(root);
        retval += to_string(root->val);
        retval += ",null,";
        while(!q.empty()) {
            auto curr = q.front();
            q.pop();
            for(auto c: curr->children) {
                q.push(c);
                retval += to_string(c->val);
                retval += ",";             
            }
            retval += "null,";
        }
        retval.pop_back();
        return retval;
    }
	
    // Decodes your encoded data to tree.
    Node* deserialize(string data) {
        if(data.size() == 0) return nullptr;
        queue<string> q1;
        queue<Node*>  q2;
        stringstream ss(data);
        string token;
        while(getline(ss, token, ',')) {
            q1.push(token);
        }
        
        Node* res = new Node(stoi(q1.front()));
        q2.push(res);
        q1.pop();
        q1.pop();

        while(!q1.empty()) {
            auto currstr = q1.front();
            auto currnode = q2.front();
            q2.pop();
            while(q1.front() != "null") {
                auto child = new Node(stoi(q1.front()));
                currnode->children.push_back(child);
                q1.pop();
                q2.push(child);
            }
            q1.pop();
        }
        return res;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
```

## Attempt 2 · 2024-02-07 07:30 IST · Accepted · Python3

[submission 1168339130](https://leetcode.com/submissions/detail/1168339130/) · tests 38/38 · runtime 48 ms (beats 100%)

```python
class WrappableInt:
        def __init__(self, x):
            self.value = x
        def getValue(self):
            return self.value
        def increment(self):
            self.value += 1

class Codec:
    
    def serialize(self, root: 'Node') -> str:
        """Encodes a tree to a single string.
        
        :type root: Node
        :rtype: str
        """
        serialized = []
        if not root:
            return ''
        def dfs(node):
            if not node:
                return
            # Serialize the current node's value
            serialized.append(str(node.val))
            # Recursively serialize each child
            for child in node.children:
                dfs(child)
            # Mark the end of children for the current node
            serialized.append('#')
            
        dfs(root)
        return ','.join(serialized)
    
    def deserialize(self, data: str) -> 'Node':
        """Decodes your encoded data to tree.
        
        :type data: str
        :rtype: Node
        """
        if not data:  # Check if the input string is empty
            return None
        values = data.split(',')
        values_iter = iter(values)
        print(values)
        def dfs():
            val = next(values_iter)
            if val == '#':  # End of children marker
                return None
            node = Node(val)
            while True:
                child = dfs()  # Recursively build the subtree
                if child is None:
                    break  # End of this node's children
                node.children.append(child)
            return node

        return dfs()  # Start the recursion with the root node
```

## Attempt 3 · 2024-02-10 19:40 IST · Accepted · Python3

[submission 1171450469](https://leetcode.com/submissions/detail/1171450469/) · tests 38/38 · runtime 59 ms (beats 95.3%)

```python
class WrappableInt:
        def __init__(self, x):
            self.value = x
        def getValue(self):
            return self.value
        def increment(self):
            self.value += 1

class Codec:
    
    def serialize(self, root: 'Node') -> str:
        """Encodes a tree to a single string.
        
        :type root: Node
        :rtype: str
        """
        serialized = []
        if not root:
            return ''
        def dfs(node):
            if not node:
                return
            # Serialize the current node's value
            serialized.append(str(node.val))
            # Recursively serialize each child
            for child in node.children:
                dfs(child)
            # Mark the end of children for the current node
            serialized.append('#')
            
        dfs(root)
        print(serialized)
        return ','.join(serialized)
    
    def deserialize(self, data: str) -> 'Node':
        """Decodes your encoded data to tree.
        
        :type data: str
        :rtype: Node
        """
        if not data:  # Check if the input string is empty
            return None
        values = data.split(',')
        values_iter = iter(values)
        print(values)
        def dfs():
            val = next(values_iter)
            if val == '#':  # End of children marker
                return None
            node = Node(val)
            while True:
                child = dfs()  # Recursively build the subtree
                if child is None:
                    break  # End of this node's children
                node.children.append(child)
            return node

        return dfs()  # Start the recursion with the root node


class Codec:
    def serialize(self, root: 'Node') -> str:
        def dfs(root):
            if not root:
                return []
            nodes = [str(root.val)]
            for child in root.children:
                nodes.extend(dfs(child))
            nodes.append('#')
            return nodes
        res = dfs(root)
        return ','.join(res)

    def deserialize(self, data: str) -> 'Node':
        values = data.split(',')
        values_iter = iter(values)
        def dfs():
            value = next(values_iter)
            if value == '#':
                return

            root = Node(value)
            while True:
                child = dfs()
                if child:
                    root.children.append(child)
                else: break
            return root

        return dfs() if data else None
```
