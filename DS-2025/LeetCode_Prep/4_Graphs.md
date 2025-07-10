# Graph Problems

## 1. Clone Graph (LC133)

**Problem**: Given a reference of a node in a connected undirected graph, return a deep copy of the graph.

**Approach**: Use BFS or DFS traversal with a hash map to track the mapping between original and cloned nodes.

**Time Complexity**: O(V + E) - We visit each node and edge once.

**Space Complexity**: O(V) for the hash map and queue.

```cpp
Node* cloneGraph(Node* node) {
    if (!node) return nullptr;
    
    // Map from original node to its clone
    unordered_map<Node*, Node*> visited;
    
    // BFS traversal
    queue<Node*> q;
    q.push(node);
    
    // Create the first node's clone
    visited[node] = new Node(node->val);
    
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        
        // Process all neighbors
        for (Node* neighbor : curr->neighbors) {
            // If not cloned yet, create new node and add to queue
            if (visited.find(neighbor) == visited.end()) {
                visited[neighbor] = new Node(neighbor->val);
                q.push(neighbor);
            }
            
            // Add the cloned neighbor to current clone's neighbors
            visited[curr]->neighbors.push_back(visited[neighbor]);
        }
    }
    
    return visited[node];
}
```

## 2. Shortest Path in Binary Matrix (LC1091)

**Problem**: Find the shortest path from top-left to bottom-right in a binary matrix where 0 represents an open cell and 1 represents a wall.

**Approach**: Use BFS to find the shortest path, considering all 8 directions.

**Time Complexity**: O(n²) where n is the size of the n×n matrix.

**Space Complexity**: O(n²) for the queue and visited set.

```cpp
int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int n = grid.size();
    
    // Check if start or end is blocked
    if (grid[0][0] == 1 || grid[n-1][n-1] == 1) {
        return -1;
    }
    
    // Directions: horizontal, vertical, and diagonal
    vector<pair<int, int>> dirs = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };
    
    // BFS queue with {row, col, distance}
    queue<tuple<int, int, int>> q;
    q.push({0, 0, 1});  // Starting position with distance 1
    
    // Mark start as visited
    grid[0][0] = 1;
    
    while (!q.empty()) {
        auto [row, col, dist] = q.front();
        q.pop();
        
        // Check if reached the target
        if (row == n-1 && col == n-1) {
            return dist;
        }
        
        // Explore all 8 directions
        for (auto& [dr, dc] : dirs) {
            int newRow = row + dr;
            int newCol = col + dc;
            
            // Check if valid cell and not visited/blocked
            if (newRow >= 0 && newRow < n && 
                newCol >= 0 && newCol < n && 
                grid[newRow][newCol] == 0) {
                
                // Mark as visited
                grid[newRow][newCol] = 1;
                q.push({newRow, newCol, dist + 1});
            }
        }
    }
    
    return -1;  // No path found
}
```

## 3. Robot Room Cleaner (LC489)

**Problem**: Control a robot to clean an entire room, handling obstacles efficiently.

**Approach**: Use backtracking with DFS to explore all reachable cells. Track visited cells with a hash set.

**Time Complexity**: O(n * m) where n×m is the room size.

**Space Complexity**: O(n * m) for the visited set.

```cpp
void cleanRoom(Robot& robot) {
    // Use a set to track visited cells
    unordered_set<string> visited;
    
    // Directions: up, right, down, left
    vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    
    // Start DFS from (0,0) facing up (arbitrary starting point)
    dfs(robot, 0, 0, 0, dirs, visited);
}

// Helper to convert cell coordinates to string key
string cellKey(int row, int col) {
    return to_string(row) + "," + to_string(col);
}

void dfs(Robot& robot, int row, int col, int dir, 
         vector<pair<int, int>>& dirs, unordered_set<string>& visited) {
    
    // Mark current cell as visited
    visited.insert(cellKey(row, col));
    
    // Clean current cell
    robot.clean();
    
    // Explore in all four directions
    for (int i = 0; i < 4; i++) {
        // Calculate new direction and position
        int newDir = (dir + i) % 4;
        int newRow = row + dirs[newDir].first;
        int newCol = col + dirs[newDir].second;
        
        // If not visited and can move, then explore
        if (visited.find(cellKey(newRow, newCol)) == visited.end() && 
            robot.move()) {
            
            dfs(robot, newRow, newCol, newDir, dirs, visited);
            
            // Backtrack: go back to previous position
            robot.turnRight();
            robot.turnRight();
            robot.move();
            robot.turnRight();
            robot.turnRight();
        }
        
        // Turn to the next direction
        robot.turnRight();
    }
}
```

## 4. Accounts Merge (LC721)

**Problem**: Merge email accounts belonging to the same person.

**Approach**: Use Union-Find to identify connected accounts and merge them.

**Time Complexity**: O(n * m * log(n * m)) where n is the number of accounts and m is the average number of emails per account.

**Space Complexity**: O(n * m) for the parent array and email-to-index map.

```cpp
vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    // Union-Find data structure
    int n = accounts.size();
    vector<int> parent(n);
    for (int i = 0; i < n; i++) {
        parent[i] = i;  // Initialize each account as its own parent
    }
    
    // Function to find parent with path compression
    function<int(int)> find = [&](int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    };
    
    // Union function
    auto unionSets = [&](int x, int y) {
        parent[find(x)] = find(y);
    };
    
    // Map email to account index
    unordered_map<string, int> emailToIndex;
    
    // Group accounts using Union-Find
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < accounts[i].size(); j++) {
            string email = accounts[i][j];
            
            if (emailToIndex.find(email) != emailToIndex.end()) {
                // Email seen before, union the accounts
                unionSets(i, emailToIndex[email]);
            } else {
                // First time seeing this email
                emailToIndex[email] = i;
            }
        }
    }
    
    // Collect emails for each merged account
    unordered_map<int, set<string>> mergedAccounts;
    for (int i = 0; i < n; i++) {
        int parent = find(i);
        for (int j = 1; j < accounts[i].size(); j++) {
            mergedAccounts[parent].insert(accounts[i][j]);
        }
    }
    
    // Format the result
    vector<vector<string>> result;
    for (auto& [parent, emails] : mergedAccounts) {
        vector<string> account;
        account.push_back(accounts[parent][0]);  // Add name
        account.insert(account.end(), emails.begin(), emails.end());  // Add emails
        result.push_back(account);
    }
    
    return result;
}
```

## 5. Nested List Weight Sum (LC339)

**Problem**: Return the weighted sum of integers in a nested list, where weight is depth.

**Approach**: Use DFS or BFS to traverse the nested structure and calculate the sum.

**Time Complexity**: O(n) where n is the total number of elements.

**Space Complexity**: O(d) where d is the maximum depth of nesting.

```cpp
int depthSum(vector<NestedInteger>& nestedList) {
    return dfs(nestedList, 1);
}

int dfs(vector<NestedInteger>& list, int depth) {
    int sum = 0;
    
    for (auto& ni : list) {
        if (ni.isInteger()) {
            // Integer, add to sum with weight = depth
            sum += ni.getInteger() * depth;
        } else {
            // List, recurse with increased depth
            sum += dfs(ni.getList(), depth + 1);
        }
    }
    
    return sum;
}
```

## Common Graph Problem Patterns

1. **Traversal Techniques**:
   - BFS: For shortest paths in unweighted graphs, level-order processing
   - DFS: For exploring all paths, connectivity, cycles
   - Bidirectional BFS: For finding shortest path in large graphs

2. **Union-Find (Disjoint Set)**:
   - Ideal for grouping elements and finding connected components
   - Operations: makeSet, find, union
   - Path compression and rank/size optimization for efficiency

3. **Topological Sort**:
   - For scheduling problems and dependency resolution
   - Only applicable to directed acyclic graphs (DAGs)

4. **Graph Representation**:
   - Adjacency list: Space-efficient for sparse graphs (most common)
   - Adjacency matrix: Fast edge lookup, good for dense graphs
   - Edge list: Simple for specific algorithms

5. **Common Graph Problems**:
   - Shortest path: Dijkstra's, Bellman-Ford, Floyd-Warshall
   - Minimum spanning tree: Prim's, Kruskal's
   - Cycle detection: DFS with visited tracking
   - Connectivity: DFS/BFS traversal

Remember to consider the graph type (directed/undirected, weighted/unweighted, cyclic/acyclic) when selecting your approach, and be careful about potential cycles in your traversal.
