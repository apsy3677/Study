# Arrays and Strings Problems

## 1. Two Sum (LC1)

**Problem**: Given an array of integers `nums` and an integer `target`, return indices of the two numbers such that they add up to `target`.

**Approach**: Use a hash map to store visited elements and their indices. For each element, check if its complement (target - current element) exists in the hash map.

**Time Complexity**: O(n) - We traverse the array once.

**Space Complexity**: O(n) - In worst case, we store all elements in the hash map.

```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen; // value -> index
    
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        
        // If we've seen the complement before
        if (seen.count(complement)) {
            return {seen[complement], i};
        }
        
        // Store current value and index
        seen[nums[i]] = i;
    }
    
    return {}; // No solution
}
```

## 2. Best Time to Buy and Sell Stock (LC121)

**Problem**: Given an array of prices where `prices[i]` is the price of a stock on day `i`, maximize profit by choosing a day to buy and a later day to sell.

**Approach**: Track the minimum price seen so far and calculate the maximum profit at each step.

**Time Complexity**: O(n) - We scan the array once.

**Space Complexity**: O(1) - We only use two variables.

```cpp
int maxProfit(vector<int>& prices) {
    if (prices.empty()) return 0;
    
    int minPrice = INT_MAX;
    int maxProfit = 0;
    
    for (int price : prices) {
        // Update minimum price seen so far
        minPrice = min(minPrice, price);
        
        // Update maximum profit if selling at current price
        maxProfit = max(maxProfit, price - minPrice);
    }
    
    return maxProfit;
}
```

## 3. Valid Palindrome (LC125)

**Problem**: Determine if a string is a palindrome, considering only alphanumeric characters and ignoring case.

**Approach**: Use two pointers starting from both ends and move inward, skipping non-alphanumeric characters.

**Time Complexity**: O(n) - We scan the string once.

**Space Complexity**: O(1) - In-place comparison.

```cpp
bool isPalindrome(string s) {
    int left = 0;
    int right = s.length() - 1;
    
    while (left < right) {
        // Skip non-alphanumeric characters
        if (!isalnum(s[left])) {
            left++;
            continue;
        }
        if (!isalnum(s[right])) {
            right--;
            continue;
        }
        
        // Compare characters (case-insensitive)
        if (tolower(s[left]) != tolower(s[right])) {
            return false;
        }
        
        left++;
        right--;
    }
    
    return true;
}
```

## 4. Move Zeroes (LC283)

**Problem**: Move all zeroes to the end of an array while maintaining the relative order of non-zero elements.

**Approach**: Use a two-pointer technique to collect and place non-zero elements, then fill the rest with zeros.

**Time Complexity**: O(n) - One pass through the array.

**Space Complexity**: O(1) - In-place operation.

```cpp
void moveZeroes(vector<int>& nums) {
    int nonZeroPos = 0;  // Position for next non-zero element
    
    // Place all non-zero elements
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != 0) {
            nums[nonZeroPos++] = nums[i];
        }
    }
    
    // Fill remaining positions with zeros
    while (nonZeroPos < nums.size()) {
        nums[nonZeroPos++] = 0;
    }
}
```

## 5. Merge Intervals (LC56)

**Problem**: Given an array of intervals, merge all overlapping intervals.

**Approach**: Sort the intervals by start time, then merge overlapping intervals in one pass.

**Time Complexity**: O(n log n) due to sorting.

**Space Complexity**: O(n) for the result array.

```cpp
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};
    
    // Sort by start time
    sort(intervals.begin(), intervals.end());
    
    vector<vector<int>> merged;
    merged.push_back(intervals[0]);
    
    for (int i = 1; i < intervals.size(); i++) {
        // If current interval overlaps with the last merged interval
        if (intervals[i][0] <= merged.back()[1]) {
            // Merge by updating the end time
            merged.back()[1] = max(merged.back()[1], intervals[i][1]);
        } else {
            // No overlap, add new interval
            merged.push_back(intervals[i]);
        }
    }
    
    return merged;
}
```

## 6. Subarray Sum Equals K (LC560)

**Problem**: Given an array of integers and an integer `k`, find the total number of continuous subarrays whose sum equals `k`.

**Approach**: Use a hash map to store the prefix sum frequencies.

**Time Complexity**: O(n) - We scan the array once.

**Space Complexity**: O(n) for the hash map.

```cpp
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefixSums = {{0, 1}}; // Empty subarray with sum 0
    int sum = 0;
    int count = 0;
    
    for (int num : nums) {
        sum += num;
        
        // If (sum - k) exists in prefixSums, it means we have subarrays ending at current position with sum k
        if (prefixSums.count(sum - k)) {
            count += prefixSums[sum - k];
        }
        
        prefixSums[sum]++;
    }
    
    return count;
}
```

## 7. Buildings With an Ocean View (LC1762)

**Problem**: Return indices of buildings that have an ocean view (no taller buildings to the right).

**Approach**: Scan from right to left, tracking the maximum height seen.

**Time Complexity**: O(n) - We scan the array once.

**Space Complexity**: O(n) for the result array.

```cpp
vector<int> findBuildings(vector<int>& heights) {
    vector<int> result;
    int maxHeight = 0;
    
    // Process buildings from right to left
    for (int i = heights.size() - 1; i >= 0; i--) {
        if (heights[i] > maxHeight) {
            // Current building has an ocean view
            result.push_back(i);
            maxHeight = heights[i];
        }
    }
    
    // Reverse to get indices in ascending order
    reverse(result.begin(), result.end());
    return result;
}
```

## 8. Can Place Flowers (LC605)

**Problem**: Determine if `n` new flowers can be planted in a flowerbed without violating the no-adjacent-flowers rule.

**Approach**: Check each position for valid placement, updating the array as we go.

**Time Complexity**: O(n) - We scan the flowerbed once.

**Space Complexity**: O(1) - In-place operation.

```cpp
bool canPlaceFlowers(vector<int>& flowerbed, int n) {
    int count = 0;
    
    for (int i = 0; i < flowerbed.size(); i++) {
        // Check if current spot is empty and its neighbors are also empty
        if (flowerbed[i] == 0 && 
            (i == 0 || flowerbed[i-1] == 0) && 
            (i == flowerbed.size()-1 || flowerbed[i+1] == 0)) {
            
            flowerbed[i] = 1;  // Plant a flower
            count++;
            
            // Check if we've placed enough flowers
            if (count >= n) return true;
        }
    }
    
    return count >= n;
}
```

## 9. Merge Sorted Array (LC88)

**Problem**: Merge two sorted arrays `nums1` and `nums2` into `nums1` as one sorted array.

**Approach**: Fill from the end to avoid overwriting elements.

**Time Complexity**: O(m + n) - We process each element once.

**Space Complexity**: O(1) - In-place operation.

```cpp
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int p1 = m - 1;  // Pointer to end of nums1 elements
    int p2 = n - 1;  // Pointer to end of nums2
    int p = m + n - 1;  // Pointer to end of merged array
    
    // Fill nums1 from the end
    while (p1 >= 0 && p2 >= 0) {
        if (nums1[p1] > nums2[p2]) {
            nums1[p--] = nums1[p1--];
        } else {
            nums1[p--] = nums2[p2--];
        }
    }
    
    // If any elements remain in nums2, copy them
    while (p2 >= 0) {
        nums1[p--] = nums2[p2--];
    }
}
```

## 10. Group Shifted Strings (LC249)

**Problem**: Given a string array, group all strings that belong to the same shifting sequence.

**Approach**: Normalize each string to a canonical form by calculating the difference between adjacent characters.

**Time Complexity**: O(n * k) where n is the number of strings and k is the average string length.

**Space Complexity**: O(n * k) for storing the groups.

```cpp
vector<vector<string>> groupStrings(vector<string>& strings) {
    unordered_map<string, vector<string>> groups;
    
    for (const string& str : strings) {
        string key = "";
        
        // Create a normalized key based on character differences
        for (int i = 1; i < str.size(); i++) {
            // Add 26 to handle negative differences
            int diff = (str[i] - str[i-1] + 26) % 26;
            key += 'a' + diff;
            key += ',';  // Delimiter between differences
        }
        
        groups[key].push_back(str);
    }
    
    // Convert groups to result format
    vector<vector<string>> result;
    for (auto& pair : groups) {
        result.push_back(pair.second);
    }
    
    return result;
}
```

## 11. Making a Large Island (LC827)

**Problem**: You can change at most one 0 to 1. Return the size of the largest island after modification.

**Approach**: Use DFS to identify and size existing islands, then check each 0 to see which would create the largest island if changed to 1.

**Time Complexity**: O(n²) where n is the size of the grid.

**Space Complexity**: O(n²) for the grid and island ID mapping.

```cpp
int largestIsland(vector<vector<int>>& grid) {
    int n = grid.size();
    unordered_map<int, int> islandSize;  // island ID -> size
    int islandId = 2;  // Start with ID 2 to distinguish from grid values 0 and 1
    
    // Mark each island with a unique ID and calculate its size
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                int size = dfs(grid, i, j, islandId);
                islandSize[islandId] = size;
                islandId++;
            }
        }
    }
    
    // If the grid is all 1s
    if (islandSize.size() == 1 && islandSize.begin()->second == n * n) {
        return n * n;
    }
    
    // If the grid is all 0s
    if (islandSize.empty()) {
        return 1;
    }
    
    int maxSize = 0;
    int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    
    // Try changing each 0 to 1 and calculate the new island size
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0) {
                unordered_set<int> neighborIslands;
                
                // Check all 4 directions for connecting islands
                for (auto& dir : dirs) {
                    int ni = i + dir[0];
                    int nj = j + dir[1];
                    
                    if (ni >= 0 && ni < n && nj >= 0 && nj < n && grid[ni][nj] > 1) {
                        neighborIslands.insert(grid[ni][nj]);
                    }
                }
                
                // Calculate size if this 0 is changed to 1
                int newSize = 1;  // Start with the changed cell
                for (int id : neighborIslands) {
                    newSize += islandSize[id];
                }
                
                maxSize = max(maxSize, newSize);
            }
        }
    }
    
    // If no 0s were changed, return the size of the largest original island
    if (maxSize == 0) {
        for (auto& pair : islandSize) {
            maxSize = max(maxSize, pair.second);
        }
    }
    
    return maxSize;
}

int dfs(vector<vector<int>>& grid, int i, int j, int islandId) {
    int n = grid.size();
    if (i < 0 || i >= n || j < 0 || j >= n || grid[i][j] != 1) {
        return 0;
    }
    
    grid[i][j] = islandId;  // Mark with island ID
    
    int size = 1;
    size += dfs(grid, i + 1, j, islandId);
    size += dfs(grid, i - 1, j, islandId);
    size += dfs(grid, i, j + 1, islandId);
    size += dfs(grid, i, j - 1, islandId);
    
    return size;
}
```

## Additional Problems

The file also includes solutions to:
- LC408 Valid Word Abbreviation
- LC31 Next Permutation
- LC1424 Diagonal Traverse 2
- LC415 Add Strings
- LC670 Maximum Swap
- LC163 Missing Ranges
- LC791 Custom Sort String
- LC65 Valid Number
- LC1047 Remove All Adjacent Duplicates In String
- LC680 Valid Palindrome 2
- LC1570 Dot Product of Two Sparse Vectors

These follow similar patterns of clear problem statements, optimal approaches, and efficient C++ implementations.
