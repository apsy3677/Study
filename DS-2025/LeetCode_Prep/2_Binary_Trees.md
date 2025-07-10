# Binary Trees Problems

## 1. Diameter of Binary Tree (LC543)

**Problem**: Find the length of the longest path between any two nodes in a binary tree.

**Approach**: Use recursive DFS to calculate height and diameter simultaneously. The diameter is the maximum sum of left and right subtree heights.

**Time Complexity**: O(n) - We visit each node once.

**Space Complexity**: O(h) - Where h is the height of the tree (recursion stack).

```cpp
int diameterOfBinaryTree(TreeNode* root) {
    int diameter = 0;
    calculateHeight(root, diameter);
    return diameter;
}

int calculateHeight(TreeNode* node, int& diameter) {
    if (!node) return 0;
    
    // Calculate height of left and right subtrees
    int leftHeight = calculateHeight(node->left, diameter);
    int rightHeight = calculateHeight(node->right, diameter);
    
    // Update diameter if current path is longer
    diameter = max(diameter, leftHeight + rightHeight);
    
    // Return height of current subtree
    return 1 + max(leftHeight, rightHeight);
}
```

## 2. Lowest Common Ancestor of a Binary Tree (LC236)

**Problem**: Find the lowest common ancestor (LCA) of two nodes in a binary tree.

**Approach**: Use recursive DFS. If a node is either p or q, or has one in the left subtree and one in the right subtree, it is the LCA.

**Time Complexity**: O(n) - We visit each node once in worst case.

**Space Complexity**: O(h) - Where h is the height of the tree.

```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // Base cases
    if (!root || root == p || root == q) return root;
    
    // Look for p and q in left and right subtrees
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    
    // If both nodes found in different subtrees, current node is LCA
    if (left && right) return root;
    
    // Otherwise, return non-null result
    return left ? left : right;
}
```

## 3. Binary Tree Right Side View (LC199)

**Problem**: Return the values visible from the right side of a binary tree.

**Approach**: Use level-order traversal (BFS) and take the last node at each level.

**Time Complexity**: O(n) - We visit each node once.

**Space Complexity**: O(w) - Where w is the maximum width of the tree.

```cpp
vector<int> rightSideView(TreeNode* root) {
    if (!root) return {};
    
    vector<int> result;
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int levelSize = q.size();
        
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            // If this is the last node in the level, add to result
            if (i == levelSize - 1) {
                result.push_back(node->val);
            }
            
            // Add children to queue
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    
    return result;
}
```

## 4. Sum Root to Leaf Numbers (LC129)

**Problem**: Calculate the total sum of all root-to-leaf numbers in a binary tree.

**Approach**: Use DFS with a running sum that's updated at each level.

**Time Complexity**: O(n) - We visit each node once.

**Space Complexity**: O(h) - Where h is the height of the tree.

```cpp
int sumNumbers(TreeNode* root) {
    return dfs(root, 0);
}

int dfs(TreeNode* node, int currSum) {
    if (!node) return 0;
    
    // Update current number
    currSum = currSum * 10 + node->val;
    
    // If leaf node, return current number
    if (!node->left && !node->right) {
        return currSum;
    }
    
    // Continue DFS on both subtrees
    return dfs(node->left, currSum) + dfs(node->right, currSum);
}
```

## 5. Range Sum of BST (LC938)

**Problem**: Calculate the sum of values of all nodes with value between low and high in a binary search tree.

**Approach**: Use BST properties to prune the search space during traversal.

**Time Complexity**: O(n) in worst case, but often better due to BST properties.

**Space Complexity**: O(h) - Where h is the height of the tree.

```cpp
int rangeSumBST(TreeNode* root, int low, int high) {
    if (!root) return 0;
    
    // If current node's value is outside range, we can prune
    if (root->val < low) {
        return rangeSumBST(root->right, low, high); // Only go right
    }
    if (root->val > high) {
        return rangeSumBST(root->left, low, high);  // Only go left
    }
    
    // Current value is in range, include it and search both children
    return root->val + 
           rangeSumBST(root->left, low, high) + 
           rangeSumBST(root->right, low, high);
}
```

## 6. Vertical Order Traversal of a Binary Tree (LC987)

**Problem**: Return the vertical order traversal of a binary tree.

**Approach**: Use BFS with coordinates and sort by column, row, and value.

**Time Complexity**: O(n log n) due to sorting.

**Space Complexity**: O(n) for storing nodes and coordinates.

```cpp
vector<vector<int>> verticalTraversal(TreeNode* root) {
    if (!root) return {};
    
    // Map column -> row -> values
    map<int, map<int, multiset<int>>> nodes;
    queue<tuple<TreeNode*, int, int>> q; // node, column, row
    q.push({root, 0, 0});
    
    while (!q.empty()) {
        auto [node, col, row] = q.front();
        q.pop();
        
        nodes[col][row].insert(node->val);
        
        if (node->left) q.push({node->left, col - 1, row + 1});
        if (node->right) q.push({node->right, col + 1, row + 1});
    }
    
    // Build result from map
    vector<vector<int>> result;
    for (auto& [col, rowMap] : nodes) {
        vector<int> colResult;
        for (auto& [row, values] : rowMap) {
            colResult.insert(colResult.end(), values.begin(), values.end());
        }
        result.push_back(colResult);
    }
    
    return result;
}
```

## 7. Convert BST to Doubly Linked List (LC426)

**Problem**: Convert a binary search tree to a sorted doubly linked list in-place.

**Approach**: Use inorder traversal with a prev pointer to create links.

**Time Complexity**: O(n) - We visit each node once.

**Space Complexity**: O(h) for recursion stack.

```cpp
Node* treeToDoublyList(Node* root) {
    if (!root) return nullptr;
    
    // Dummy head and pointer to track previous node
    Node dummy(0);
    Node* prev = &dummy;
    
    inorder(root, prev);
    
    // Connect head and tail
    prev->right = dummy.right;
    dummy.right->left = prev;
    
    return dummy.right;
}

void inorder(Node* node, Node*& prev) {
    if (!node) return;
    
    // Process left subtree
    inorder(node->left, prev);
    
    // Link current node with previous
    prev->right = node;
    node->left = prev;
    prev = node;
    
    // Process right subtree
    inorder(node->right, prev);
}
```

## 8. Closest Binary Search Tree Value (LC270)

**Problem**: Find the value in a BST that is closest to a target value.

**Approach**: Use binary search property to navigate the tree.

**Time Complexity**: O(h) where h is the height of the tree.

**Space Complexity**: O(1) for iterative solution.

```cpp
int closestValue(TreeNode* root, double target) {
    int closest = root->val;
    
    while (root) {
        // Update closest if current value is closer
        if (abs(root->val - target) < abs(closest - target)) {
            closest = root->val;
        }
        
        // Navigate left or right based on target
        root = target < root->val ? root->left : root->right;
    }
    
    return closest;
}
```

## 9. Lowest Common Ancestor of a Binary Tree III (LC1650)

**Problem**: Find the LCA of two nodes in a binary tree where each node has a parent pointer.

**Approach**: Use a similar approach to finding the intersection of two linked lists.

**Time Complexity**: O(h) where h is the height of the tree.

**Space Complexity**: O(1) - No extra space.

```cpp
Node* lowestCommonAncestor(Node* p, Node* q) {
    Node* a = p;
    Node* b = q;
    
    // Both pointers will either meet at the LCA or become null after the same number of steps
    while (a != b) {
        a = a ? a->parent : q;  // Move to parent or reset to other node
        b = b ? b->parent : p;
    }
    
    return a;  // This is the LCA
}
```

## Additional Problems

The file also includes detailed solutions to:
- Lowest Common Ancestor of a Binary Tree III (LC1650)
- Convert BST to Doubly Linked List (LC426)

Each solution follows the pattern of problem statement, approach explanation, time and space complexity analysis, and efficient C++ implementation.
