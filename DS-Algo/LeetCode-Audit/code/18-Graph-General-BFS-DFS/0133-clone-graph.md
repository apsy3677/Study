# 133. Clone Graph

[Problem](https://leetcode.com/problems/clone-graph/) · Medium · Graph: General BFS/DFS → Copy with map

LeetCode tags: hash-table, depth-first-search, breadth-first-search, graph

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2025-06-14 22:44 IST · Accepted · C++

[submission 1664071397](https://leetcode.com/submissions/detail/1664071397/) · tests 22/22 · runtime 2 ms (beats 73.5%)

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
    set<Node *> visited;
    map<Node *, Node *> mapp;
    void dfs(Node *node) {
        if (!node) return;
        visited.insert(node);
        Node *new_node = new Node (node->val);
        mapp[node] = new_node;

        for (auto child : node->neighbors) {
            if (visited.find(child) == visited.end()) {
                dfs(child);
            }
        }
    }

    void dfsAddChilds(Node *node) {
        if (!node) return;
        visited.insert(node);
        auto new_node = mapp[node];
        if (!new_node) return;
        for (Node * child : node->neighbors) {
            (new_node->neighbors).push_back(mapp[child]);
            if (visited.find(child) == visited.end()) {
                auto new_child = mapp[child];
                dfsAddChilds(child);
            }
        }
    }
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;
        dfs(node);
        visited.clear();

        dfsAddChilds(node);
        return mapp[node];
    }
};
```

## Attempt 2 · 2025-06-14 22:49 IST · Accepted · C++

[submission 1664076025](https://leetcode.com/submissions/detail/1664076025/) · tests 22/22 · runtime 7 ms (beats 20.8%)

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
    set<Node *> visited;
    map<Node *, Node *> mapp;
    void dfs(Node *node) {
        if (!node) return;
        visited.insert(node);
        Node *new_node = new Node (node->val);
        mapp[node] = new_node;

        for (auto child : node->neighbors) {
            if (visited.find(child) == visited.end()) {
                dfs(child);
            }
        }
    }

    void dfsAddChilds(Node *node) {
        if (!node) return;
        visited.insert(node);
        auto new_node = mapp[node];
        if (!new_node) return;
        for (Node * child : node->neighbors) {
            (new_node->neighbors).push_back(mapp[child]);
            if (visited.find(child) == visited.end()) {
                auto new_child = mapp[child];
                dfsAddChilds(child);
            }
        }
    }
public:
    Node* cloneGraph(Node* node) {
        // if (!node) return nullptr;
        // dfs(node);
        // visited.clear();

        // dfsAddChilds(node);
        // return mapp[node];

        if (!node) return nullptr;
        
        // Map original nodes to their clones
        unordered_map<Node*, Node*> cloneMap;
        
        // Create the clone for the first node
        cloneMap[node] = new Node(node->val);
        
        // Use a queue for BFS
        queue<Node*> q;
        q.push(node);
        
        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();
            
            // Process all neighbors
            for (Node* neighbor : curr->neighbors) {
                // If neighbor not cloned yet, create clone and add to queue
                if (cloneMap.find(neighbor) == cloneMap.end()) {
                    cloneMap[neighbor] = new Node(neighbor->val);
                    q.push(neighbor);
                }
                
                // Add the cloned neighbor to the cloned current node
                cloneMap[curr]->neighbors.push_back(cloneMap[neighbor]);
            }
        }
        
        return cloneMap[node];
    }
};
```
