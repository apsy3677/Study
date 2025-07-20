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

## 10. Binary Search Tree Iterator (LC173)

**Problem**: Implement the BSTIterator class that represents an iterator over the in-order traversal of a binary search tree (BST).

**Requirements**:
- `BSTIterator(TreeNode* root)`: Initializes the iterator with BST root
- `int next()`: Returns the next smallest number in the BST (in-order)
- `bool hasNext()`: Returns true if there exists a next smallest number

**Key Constraints**:
- `next()` and `hasNext()` should run in average O(1) time
- Use O(h) memory, where h is the height of the tree

**In-Depth Analysis**:

The core insight is that in-order traversal of a BST gives us elements in sorted order. However, we can't do a full traversal upfront because:
1. Memory constraint: O(h) instead of O(n)
2. Time constraint: O(1) amortized per operation

**Approach: Controlled Recursion with Stack**

The key idea is to simulate the recursive in-order traversal using an explicit stack, but only traverse as much as needed for the next element.

**Algorithm**:
1. **Initialization**: Push all leftmost nodes onto stack (these are the smallest unvisited nodes)
2. **next()**: Pop from stack, add right subtree's leftmost path if exists
3. **hasNext()**: Check if stack is non-empty

**Why This Works**:
- Stack always contains the "path" to the next smallest element
- When we pop a node, its right subtree contains the next candidates
- We only traverse the left spine of each subtree when needed

**Visual Example**:
```
      7
     / \
    3   15
       /  \
      9   20

In-order: 3, 7, 9, 15, 20

Initial stack (leftmost path): [7, 3]
next(): pop 3, stack: [7]
next(): pop 7, add leftmost of right subtree, stack: [15, 9]  
next(): pop 9, stack: [15]
next(): pop 15, add leftmost of right subtree, stack: [20]
next(): pop 20, stack: []
```

**Implementation**:

```cpp
class BSTIterator {
private:
    stack<TreeNode*> stk;
    
    // Push all leftmost nodes from current node
    void pushLeftmost(TreeNode* node) {
        while (node) {
            stk.push(node);
            node = node->left;
        }
    }
    
public:
    BSTIterator(TreeNode* root) {
        pushLeftmost(root);
    }
    
    int next() {
        TreeNode* topNode = stk.top();
        stk.pop();
        
        // If right subtree exists, push its leftmost path
        if (topNode->right) {
            pushLeftmost(topNode->right);
        }
        
        return topNode->val;
    }
    
    bool hasNext() {
        return !stk.empty();
    }
};
```

**Alternative Implementation with More Explicit Control**:

```cpp
class BSTIterator {
private:
    stack<TreeNode*> nodeStack;
    
public:
    BSTIterator(TreeNode* root) {
        // Initialize stack with leftmost path
        while (root) {
            nodeStack.push(root);
            root = root->left;
        }
    }
    
    int next() {
        if (!hasNext()) return -1; // Error case
        
        // Get the next node (top of stack)
        TreeNode* nextNode = nodeStack.top();
        nodeStack.pop();
        int result = nextNode->val;
        
        // If this node has a right subtree,
        // push all leftmost nodes of that subtree
        TreeNode* rightSubtree = nextNode->right;
        while (rightSubtree) {
            nodeStack.push(rightSubtree);
            rightSubtree = rightSubtree->left;
        }
        
        return result;
    }
    
    bool hasNext() {
        return !nodeStack.empty();
    }
};
```

**Complexity Analysis**:

**Time Complexity**:
- **Constructor**: O(h) - Push leftmost path
- **next()**: O(1) amortized - Each node pushed and popped exactly once
- **hasNext()**: O(1) - Simple stack check

**Space Complexity**: O(h) - Stack stores at most h nodes (height of tree)

**Why O(1) Amortized for next()**:
- Each node is pushed onto stack exactly once during entire iteration
- Each node is popped from stack exactly once during entire iteration  
- Total operations across all next() calls: O(n)
- Amortized per call: O(n)/n = O(1)

**Edge Cases Handled**:
1. **Empty Tree**: Stack remains empty, hasNext() returns false
2. **Single Node**: Works correctly with just root
3. **Left-skewed Tree**: Stack grows to O(n) initially
4. **Right-skewed Tree**: Stack never grows beyond 1 element

**Follow-up: Bidirectional BST Iterator with previous()**:

```cpp
class BidirectionalBSTIterator {
private:
    stack<TreeNode*> nextStack;    // For next() operations
    stack<TreeNode*> prevStack;    // For previous() operations
    TreeNode* current;             // Current position
    
    void pushLeftPath(TreeNode* node, stack<TreeNode*>& stk) {
        while (node) {
            stk.push(node);
            node = node->left;
        }
    }
    
    void pushRightPath(TreeNode* node, stack<TreeNode*>& stk) {
        while (node) {
            stk.push(node);
            node = node->right;
        }
    }
    
public:
    BidirectionalBSTIterator(TreeNode* root) : current(nullptr) {
        pushLeftPath(root, nextStack);
    }
    
    int next() {
        if (!hasNext()) return -1;
        
        TreeNode* node = nextStack.top();
        nextStack.pop();
        
        // Push current to previous stack
        if (current) prevStack.push(current);
        current = node;
        
        // Push right subtree's leftmost path to next stack
        if (node->right) {
            pushLeftPath(node->right, nextStack);
        }
        
        return node->val;
    }
    
    int previous() {
        if (!hasPrevious()) return -1;
        
        TreeNode* node = prevStack.top();
        prevStack.pop();
        
        // Push current back to next stack
        if (current) nextStack.push(current);
        current = node;
        
        // Push left subtree's rightmost path to previous stack
        if (node->left) {
            pushRightPath(node->left, prevStack);
        }
        
        return node->val;
    }
    
    bool hasNext() {
        return !nextStack.empty();
    }
    
    bool hasPrevious() {
        return !prevStack.empty();
    }
};
```

**Alternative: Using Parent Pointers (O(1) Space per Operation)**:

```cpp
class BSTIteratorWithParent {
private:
    struct TreeNodeWithParent {
        int val;
        TreeNodeWithParent* left;
        TreeNodeWithParent* right;
        TreeNodeWithParent* parent;
    };
    
    TreeNodeWithParent* current;
    TreeNodeWithParent* root;
    
    TreeNodeWithParent* findMin(TreeNodeWithParent* node) {
        while (node && node->left) node = node->left;
        return node;
    }
    
    TreeNodeWithParent* findMax(TreeNodeWithParent* node) {
        while (node && node->right) node = node->right;
        return node;
    }
    
public:
    BSTIteratorWithParent(TreeNodeWithParent* root) : root(root) {
        current = findMin(root); // Start at smallest element
    }
    
    int next() {
        if (!current) return -1;
        
        int result = current->val;
        
        if (current->right) {
            // Go to leftmost node in right subtree
            current = findMin(current->right);
        } else {
            // Go up until we find a node that is left child of its parent
            TreeNodeWithParent* parent = current->parent;
            while (parent && current == parent->right) {
                current = parent;
                parent = parent->parent;
            }
            current = parent;
        }
        
        return result;
    }
    
    int previous() {
        if (!current) {
            // If at end, go to maximum
            current = findMax(root);
            return current ? current->val : -1;
        }
        
        int result = current->val;
        
        if (current->left) {
            // Go to rightmost node in left subtree
            current = findMax(current->left);
        } else {
            // Go up until we find a node that is right child of its parent
            TreeNodeWithParent* parent = current->parent;
            while (parent && current == parent->left) {
                current = parent;
                parent = parent->parent;
            }
            current = parent;
        }
        
        return result;
    }
};
```

## Tree Iterator Variations

### 1. **Pre-order Iterator** (Root → Left → Right)

```cpp
class PreorderIterator {
private:
    stack<TreeNode*> stk;
    
public:
    PreorderIterator(TreeNode* root) {
        if (root) stk.push(root);
    }
    
    int next() {
        if (stk.empty()) return -1;
        
        TreeNode* node = stk.top();
        stk.pop();
        
        // Push right first (so left is processed first)
        if (node->right) stk.push(node->right);
        if (node->left) stk.push(node->left);
        
        return node->val;
    }
    
    bool hasNext() {
        return !stk.empty();
    }
};
```

### 2. **Post-order Iterator** (Left → Right → Root)

```cpp
class PostorderIterator {
private:
    stack<TreeNode*> stk;
    TreeNode* lastVisited;
    
public:
    PostorderIterator(TreeNode* root) : lastVisited(nullptr) {
        pushLeftPath(root);
    }
    
private:
    void pushLeftPath(TreeNode* node) {
        while (node) {
            stk.push(node);
            node = node->left;
        }
    }
    
public:
    int next() {
        while (!stk.empty()) {
            TreeNode* peekNode = stk.top();
            
            // If right child exists and hasn't been processed yet
            if (peekNode->right && lastVisited != peekNode->right) {
                pushLeftPath(peekNode->right);
            } else {
                // Process current node
                stk.pop();
                lastVisited = peekNode;
                return peekNode->val;
            }
        }
        return -1;
    }
    
    bool hasNext() {
        return !stk.empty();
    }
};
```

### 3. **Level-order Iterator** (Breadth-First)

```cpp
class LevelOrderIterator {
private:
    queue<TreeNode*> q;
    
public:
    LevelOrderIterator(TreeNode* root) {
        if (root) q.push(root);
    }
    
    int next() {
        if (q.empty()) return -1;
        
        TreeNode* node = q.front();
        q.pop();
        
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
        
        return node->val;
    }
    
    bool hasNext() {
        return !q.empty();
    }
};
```

### 4. **Zigzag Level Iterator** (Alternating Left-Right, Right-Left)

```cpp
class ZigzagIterator {
private:
    queue<TreeNode*> q;
    bool leftToRight;
    vector<int> currentLevel;
    int levelIndex;
    
public:
    ZigzagIterator(TreeNode* root) : leftToRight(true), levelIndex(0) {
        if (root) q.push(root);
        prepareNextLevel();
    }
    
private:
    void prepareNextLevel() {
        if (q.empty()) return;
        
        currentLevel.clear();
        int levelSize = q.size();
        
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            currentLevel.push_back(node->val);
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        if (!leftToRight) {
            reverse(currentLevel.begin(), currentLevel.end());
        }
        
        leftToRight = !leftToRight;
        levelIndex = 0;
    }
    
public:
    int next() {
        if (levelIndex >= currentLevel.size()) {
            prepareNextLevel();
            if (currentLevel.empty()) return -1;
        }
        
        return currentLevel[levelIndex++];
    }
    
    bool hasNext() {
        return levelIndex < currentLevel.size() || !q.empty();
    }
};
```

### 5. **Morris Traversal Iterator** (O(1) Space)

```cpp
class MorrisIterator {
private:
    TreeNode* current;
    
    TreeNode* findPredecessor(TreeNode* node) {
        TreeNode* pred = node->left;
        while (pred->right && pred->right != node) {
            pred = pred->right;
        }
        return pred;
    }
    
public:
    MorrisIterator(TreeNode* root) : current(root) {}
    
    int next() {
        while (current) {
            if (!current->left) {
                // No left subtree, visit current and go right
                int val = current->val;
                current = current->right;
                return val;
            } else {
                // Find inorder predecessor
                TreeNode* pred = findPredecessor(current);
                
                if (!pred->right) {
                    // Create thread
                    pred->right = current;
                    current = current->left;
                } else {
                    // Thread exists, remove it and visit current
                    pred->right = nullptr;
                    int val = current->val;
                    current = current->right;
                    return val;
                }
            }
        }
        return -1;
    }
    
    bool hasNext() {
        return current != nullptr;
    }
};
```

### 6. **Boundary Traversal Iterator**

```cpp
class BoundaryIterator {
private:
    vector<int> boundary;
    int index;
    
    void addLeftBoundary(TreeNode* node, vector<int>& result) {
        if (!node || (!node->left && !node->right)) return;
        
        result.push_back(node->val);
        if (node->left) addLeftBoundary(node->left, result);
        else addLeftBoundary(node->right, result);
    }
    
    void addLeaves(TreeNode* node, vector<int>& result) {
        if (!node) return;
        if (!node->left && !node->right) {
            result.push_back(node->val);
            return;
        }
        addLeaves(node->left, result);
        addLeaves(node->right, result);
    }
    
    void addRightBoundary(TreeNode* node, vector<int>& result) {
        if (!node || (!node->left && !node->right)) return;
        
        if (node->right) addRightBoundary(node->right, result);
        else addRightBoundary(node->left, result);
        result.push_back(node->val); // Add after recursion (reverse order)
    }
    
public:
    BoundaryIterator(TreeNode* root) : index(0) {
        if (!root) return;
        
        boundary.push_back(root->val);
        if (!root->left && !root->right) return;
        
        addLeftBoundary(root->left, boundary);
        addLeaves(root, boundary);
        addRightBoundary(root->right, boundary);
    }
    
    int next() {
        return hasNext() ? boundary[index++] : -1;
    }
    
    bool hasNext() {
        return index < boundary.size();
    }
};
```

## Complexity Comparison

| Iterator Type | Space | Time (next) | Time (hasNext) | Use Case |
|---------------|-------|-------------|----------------|----------|
| In-order (BST) | O(h) | O(1) amortized | O(1) | Sorted traversal |
| Bidirectional | O(h) | O(1) amortized | O(1) | Navigation |
| Pre-order | O(h) | O(1) amortized | O(1) | Tree serialization |
| Post-order | O(h) | O(1) amortized | O(1) | Tree deletion |
| Level-order | O(w) | O(1) | O(1) | Level processing |
| Morris | O(1) | O(1) amortized | O(1) | Memory constrained |
| Zigzag | O(w) | O(1) amortized | O(1) | Display formatting |

**Follow-up Questions**:

**Q: What if we needed to support previous() as well?**
**A**: Implemented above using two stacks or parent pointers.

**Q: Can we do this iteratively without recursion?**
**A**: Yes, that's exactly what we're doing - using stack to eliminate recursion.

**Q: What about Morris Traversal for O(1) space?**
**A**: Morris traversal achieves O(1) space but modifies tree structure temporarily, which may not be acceptable for an iterator.

**Usage Example**:
```cpp
// Usage
TreeNode* root = /* construct BST */;
BSTIterator iterator(root);

while (iterator.hasNext()) {
    cout << iterator.next() << " ";
}
// Output: Elements in sorted order
```

**Key Insights**:
1. **Controlled Recursion**: Use stack to control how much of traversal we do
2. **Lazy Evaluation**: Only compute next elements when needed
3. **Amortized Analysis**: Although single operations might be O(h), average is O(1)
4. **Space-Time Tradeoff**: Use O(h) space to achieve O(1) time per operation

## Additional Problems

The file also includes detailed solutions to:
- Lowest Common Ancestor of a Binary Tree III (LC1650)
- Convert BST to Doubly Linked List (LC426)
- Binary Search Tree Iterator (LC173)

Each solution follows the pattern of problem statement, approach explanation, time and space complexity analysis, and efficient C++ implementation.
