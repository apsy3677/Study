# 297. Serialize and Deserialize Binary Tree

[Problem](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/) · Hard · Binary Tree (DFS & Recursion) → Serialization

LeetCode tags: string, tree, depth-first-search, breadth-first-search, design, binary-tree

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-05-23 14:04 IST · Accepted · C++

[submission 955665005](https://leetcode.com/submissions/detail/955665005/) · tests 52/52 · runtime 44 ms (beats 11.7%)

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
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root) return "";
        queue<TreeNode*> qu;
        qu.push(root);
        string ans ="";

        while(!qu.empty()){
            int sz= qu.size();
            while(sz--){
                auto node = qu.front(); qu.pop();
                if(node == NULL) ans.append("#,");
                else {
                    ans.append( to_string(node->val) + ',');
                    qu.push(node->left);
                    qu.push(node->right);
                }
            }
        }
        cout<<ans<<" ";
        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data.size() == 0) return NULL;

        stringstream s(data);
        string str;
        getline(s,str, ',');
        TreeNode * root = new TreeNode(stoi(str));
        queue<TreeNode *> qu;
        qu.push(root);
        while(!qu.empty()){
            TreeNode *node = qu.front(); qu.pop();
            
            getline(s, str, ',');

            if(str == "#") {
                node->left = NULL;
            }
            else{
                TreeNode * left = new TreeNode( stoi(str));
                node->left = left;
                qu.push(left);
            }
            getline(s, str, ',');

            if(str == "#") {
                node->right = NULL;
            }
            else{
                TreeNode * right = new TreeNode( stoi(str));
                node->right = right;
                qu.push(right);
            }
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
```

## Attempt 2 · 2023-12-29 05:46 IST · Accepted · Python3

[submission 1130967362](https://leetcode.com/submissions/detail/1130967362/) · tests 53/53 · runtime 187 ms (beats 5.1%)

```python
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Codec:

    def serialize(self, root):
        """Encodes a tree to a single string.
        
        :type root: TreeNode
        :rtype: str
        """
        def dfs(root):
            path = ''
            if not root:
                return 'None,'
            
            path += str(root.val) +','
            path += dfs(root.left)
            path += dfs(root.right)

            return path
        # return dfs(root)
        return dfs(root)


    def deserialize(self, data):
        """Decodes your encoded data to tree.
        
        :type data: str
        :rtype: TreeNode
        """

        def dfs(l):
            # none - return 
            if l[0] =='None':
                l.pop(0)
                return None

            root = TreeNode(l[0])
            l.pop(0)
            root.left = dfs(l)
            root.right = dfs(l)
            return root

        data_list = data.split(',')
        root = dfs(data_list)
        return root
        

# Your Codec object will be instantiated and called as such:
# ser = Codec()
# deser = Codec()
# ans = deser.deserialize(ser.serialize(root))
```

## Attempt 3 · 2023-12-29 05:51 IST · Accepted · Python3

[submission 1130969649](https://leetcode.com/submissions/detail/1130969649/) · tests 53/53 · runtime 88 ms (beats 60.8%)

```python
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Codec1:

    def serialize(self, root):
        """Encodes a tree to a single string.
        
        :type root: TreeNode
        :rtype: str
        """
        def dfs(root):
            path = ''
            if not root:
                return 'None,'
            
            path += str(root.val) +','
            path += dfs(root.left)
            path += dfs(root.right)

            return path
        # return dfs(root)
        return dfs(root)


    def deserialize(self, data):
        """Decodes your encoded data to tree.
        
        :type data: str
        :rtype: TreeNode
        """

        def dfs(l):
            # none - return 
            if l[0] =='None':
                l.pop(0)
                return None

            root = TreeNode(l[0])
            l.pop(0)
            root.left = dfs(l)
            root.right = dfs(l)
            return root

        data_list = data.split(',')
        root = dfs(data_list)
        return root

class Codec:

    def serialize(self, root):
        """Encodes a tree to a single string."""
        if not root:
            return ""
        
        queue = collections.deque([root])
        result = []
        while queue:
            node = queue.popleft()
            if node:
                result.append(str(node.val))
                queue.append(node.left)
                queue.append(node.right)
            else:
                result.append("None")
        
        return ','.join(result)

    def deserialize(self, data):
        """Decodes your encoded data to tree."""
        if not data:
            return None

        values = data.split(',')
        root = TreeNode(int(values[0]))
        queue = collections.deque([root])
        index = 1

        while queue:
            node = queue.popleft()
            if values[index] != "None":
                node.left = TreeNode(int(values[index]))
                queue.append(node.left)
            index += 1

            if values[index] != "None":
                node.right = TreeNode(int(values[index]))
                queue.append(node.right)
            index += 1

        return root


# Your Codec object will be instantiated and called as such:
# ser = Codec()
# deser = Codec()
# ans = deser.deserialize(ser.serialize(root))
```
