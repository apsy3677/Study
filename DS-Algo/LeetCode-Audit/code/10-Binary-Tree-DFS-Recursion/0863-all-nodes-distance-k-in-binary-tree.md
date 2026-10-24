# 863. All Nodes Distance K in Binary Tree

[Problem](https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/) · Medium · Binary Tree (DFS & Recursion) → Parent map + BFS

LeetCode tags: hash-table, tree, depth-first-search, breadth-first-search, binary-tree

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-05-05 08:11 IST · Accepted · C++

[submission 944684853](https://leetcode.com/submissions/detail/944684853/) · tests 57/57 · runtime 3 ms (beats 82.9%)

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    void markParents(TreeNode * root, unordered_map<TreeNode*, TreeNode*> &parents, TreeNode* target){

        queue<TreeNode*> qu;
        qu.push(root);
        while(!qu.empty()){
            auto curr = qu.front();
            qu.pop();

            if(curr->left){
                parents[curr->left] = curr;
                qu.push(curr->left);
            }
            if(curr->right){
                parents[curr->right] = curr;
                qu.push(curr->right);
            }
        }
    }
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        unordered_map<TreeNode*, TreeNode*> parents;
        markParents(root, parents, target);

        unordered_map<TreeNode*,bool> visited;
        queue<TreeNode*> qu;
        qu.push(target);
        visited[target] = true;

        int level=0;
        while(!qu.empty()){
            int sz = qu.size();
            if(level++ == k) break;

            while(sz--){
                auto curr = qu.front(); qu.pop();
                if(curr->left && !visited[curr->left]){
                    qu.push(curr->left);
                    visited[curr->left] = true;
                }
                if(curr->right && !visited[curr->right]){
                    qu.push(curr->right);
                    visited[curr->right] = true;
                }
                if(parents[curr] && !visited[parents[curr]]){
                    qu.push(parents[curr]);
                    visited[parents[curr]] = true;
                }
            }
        }
        vector<int> res;
        while(!qu.empty()){
            auto curr = qu.front(); qu.pop();
            res.push_back(curr->val);
        }
        return res;
    }
};
```

## Attempt 2 · 2024-02-06 20:56 IST · Accepted · Python3

[submission 1167903284](https://leetcode.com/submissions/detail/1167903284/) · tests 57/57 · runtime 51 ms (beats 45.1%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def distanceK(self, root: TreeNode, target: TreeNode, k: int) -> List[int]:
        graph = defaultdict(list)
        def build_graph(node, parent):
            if node and parent:
                graph[node.val].append(parent.val)
                graph[parent.val].append(node.val)

            if node.left:
                build_graph(node.left, node)
            if node.right:
                build_graph(node.right, node)
        build_graph(root, None)

        answer = []
        visited = set()

        def dfs(curr, distance):
            if curr in visited:
                return

            visited.add(curr)
            
            if distance == k:
                answer.append(curr)
                return

            for neighbor in graph[curr]:
                dfs(neighbor, distance+1)
                
        dfs(target.val, 0)
        return answer

    def distanceK(self, root: TreeNode, target: TreeNode, k: int) -> List[int]:
        graph = defaultdict(list)
        def build_graph(root, parent):
            if not root:
                return
                
            if parent:
                graph[root].append(parent)
                graph[parent].append(root)

            # if root.left:
            build_graph(root.left, root)
            # if root.right:
            build_graph(root.right, root)

        build_graph(root,None)
        
        result = []
        visited = set()
        def dfs(root, dist):
            if root in visited:
                return 

            visited.add(root)

            if dist == k:
                result.append(root.val)
                return 

            for edge in graph[root]:
                dfs(edge, dist +1)
            
        dfs(target, 0)

        return result
```
