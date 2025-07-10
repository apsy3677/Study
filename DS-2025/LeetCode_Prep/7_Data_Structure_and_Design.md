# Data Structure and Design Problems

## 1. LRU Cache (LC146)

**Problem**: Design an LRU (Least Recently Used) cache with get and put operations in O(1) time.

**Approach**: Combine a doubly linked list for ordering and a hash map for O(1) access.

**Time Complexity**: O(1) for both get and put operations.

**Space Complexity**: O(capacity) for storing the key-value pairs.

```cpp
class LRUCache {
private:
    int capacity;
    
    // Use list to maintain order (front = most recent, back = least recent)
    list<pair<int, int>> items;  // (key, value) pairs
    
    // Map from key to iterator for O(1) access
    unordered_map<int, list<pair<int, int>>::iterator> cache;

public:
    LRUCache(int capacity) : capacity(capacity) {}
    
    int get(int key) {
        // If key doesn't exist
        if (cache.find(key) == cache.end()) {
            return -1;
        }
        
        // Move accessed item to front (most recently used)
        items.splice(items.begin(), items, cache[key]);
        
        return cache[key]->second;  // Return the value
    }
    
    void put(int key, int value) {
        // If key already exists, update value and move to front
        if (cache.find(key) != cache.end()) {
            cache[key]->second = value;  // Update value
            items.splice(items.begin(), items, cache[key]);  // Move to front
            return;
        }
        
        // If cache is at capacity, remove least recently used item
        if (items.size() >= capacity) {
            int keyToRemove = items.back().first;  // Get key of least recent item
            items.pop_back();  // Remove from list
            cache.erase(keyToRemove);  // Remove from map
        }
        
        // Add new item at the front
        items.push_front({key, value});
        cache[key] = items.begin();
    }
};
```

## 2. Design Tic-Tac-Toe (LC348)

**Problem**: Design a Tic-Tac-Toe game that allows players to make moves and determines if a player has won.

**Approach**: Use row, column, and diagonal counters to avoid checking the entire board.

**Time Complexity**: O(1) per move.

**Space Complexity**: O(n) for an n×n board.

```cpp
class TicTacToe {
private:
    int n;
    vector<int> rows;    // Track sum for each row
    vector<int> cols;    // Track sum for each column
    int diagonal;        // Track sum for main diagonal
    int antiDiagonal;    // Track sum for anti-diagonal

public:
    TicTacToe(int n) {
        this->n = n;
        rows.resize(n, 0);
        cols.resize(n, 0);
        diagonal = 0;
        antiDiagonal = 0;
    }
    
    // Returns 0 if no winner yet, 1 if player 1 wins, 2 if player 2 wins
    int move(int row, int col, int player) {
        // Convert player to +1 or -1 for easier counting
        int val = (player == 1) ? 1 : -1;
        
        // Update row and column sums
        rows[row] += val;
        cols[col] += val;
        
        // Update diagonal sums if applicable
        if (row == col) {
            diagonal += val;
        }
        if (row + col == n - 1) {
            antiDiagonal += val;
        }
        
        // Check for winner
        if (abs(rows[row]) == n || abs(cols[col]) == n || 
            abs(diagonal) == n || abs(antiDiagonal) == n) {
            return player;
        }
        
        return 0;  // No winner yet
    }
};
```

## 3. Moving Average from Data Stream (LC346)

**Problem**: Calculate the moving average of a data stream with a fixed window size.

**Approach**: Use a queue to maintain the window and track the sum.

**Time Complexity**: O(1) per operation.

**Space Complexity**: O(size) for the queue.

```cpp
class MovingAverage {
private:
    queue<int> window;
    int size;
    double sum;

public:
    MovingAverage(int size) {
        this->size = size;
        sum = 0;
    }
    
    double next(int val) {
        // Add new value
        window.push(val);
        sum += val;
        
        // Remove oldest value if window exceeds size
        if (window.size() > size) {
            sum -= window.front();
            window.pop();
        }
        
        return sum / window.size();
    }
};
```

## 4. Random Pick with Weight (LC528)

**Problem**: Pick an index randomly with probability proportional to its weight.

**Approach**: Use prefix sum and binary search.

**Time Complexity**: O(log n) per pick operation.

**Space Complexity**: O(n) for storing the prefix sums.

```cpp
class Solution {
private:
    vector<int> prefixSums;
    int totalSum;

public:
    Solution(vector<int>& w) {
        prefixSums.resize(w.size());
        
        // Calculate prefix sums
        prefixSums[0] = w[0];
        for (int i = 1; i < w.size(); i++) {
            prefixSums[i] = prefixSums[i-1] + w[i];
        }
        
        totalSum = prefixSums.back();
    }
    
    int pickIndex() {
        // Generate random number between 1 and totalSum
        int target = rand() % totalSum + 1;
        
        // Binary search for the first prefix sum >= target
        int left = 0;
        int right = prefixSums.size() - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (prefixSums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return left;
    }
};
```

## 5. Random Pick Index (LC398)

**Problem**: Given an array of integers with possible duplicates, randomly pick an index at which a given target appears.

**Approach**: Use reservoir sampling for O(1) space.

**Time Complexity**: O(n) per pick operation.

**Space Complexity**: O(1) for random picking.

```cpp
class Solution {
private:
    vector<int> nums;

public:
    Solution(vector<int>& nums) {
        this->nums = nums;
    }
    
    int pick(int target) {
        int result = -1;
        int count = 0;
        
        // Reservoir sampling
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == target) {
                // Increment count of target numbers seen
                count++;
                
                // With probability 1/count, select this index
                if (rand() % count == 0) {
                    result = i;
                }
            }
        }
        
        return result;
    }
};
```

## Key Design Patterns for Data Structure Problems

1. **Combination of Data Structures**:
   - Hash map + linked list (LRU Cache)
   - Heap + hash map (Top K Frequent Elements)
   - Trie + hash map (Word Dictionary)

2. **Efficient Updates**:
   - Lazy evaluation (only update when needed)
   - Incremental maintenance (update counters rather than recomputing)
   - Batch operations (amortize cost over multiple operations)

3. **Space-Time Tradeoffs**:
   - Preprocessing: Build auxiliary data structures to speed up queries
   - Caching: Store results of expensive computations
   - Summarization: Keep aggregate statistics instead of raw data

4. **Design Principles**:
   - Single responsibility: Each component handles one aspect
   - Encapsulation: Hide implementation details
   - Extensibility: Allow for future requirements

5. **Optimization Techniques**:
   - Binary search for sorted data
   - Reservoir sampling for stream processing
   - Bloom filters for membership testing
   - Rolling hashes for string problems

When designing data structures in interviews, start by clarifying requirements (operations, constraints, expected performance), then outline the key components and their interactions before diving into implementation details.
