# Sliding Window / Two Pointer Problems

## 1. Max Consecutive Ones III (LC1004)

**Problem**: Given a binary array and an integer k, return the maximum number of consecutive 1's in the array if you can flip at most k 0's.

**Approach**: Use sliding window to maintain a window with at most k zeros.

**Time Complexity**: O(n) - Each element is processed at most twice.

**Space Complexity**: O(1) - Constant extra space.

```cpp
int longestOnes(vector<int>& nums, int k) {
    int left = 0;
    int maxLength = 0;
    int zeroCount = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        // If we encounter a 0, increment the count
        if (nums[right] == 0) {
            zeroCount++;
        }
        
        // If we have too many zeros, shrink window from left
        while (zeroCount > k) {
            if (nums[left] == 0) {
                zeroCount--;
            }
            left++;
        }
        
        // Update maximum length
        maxLength = max(maxLength, right - left + 1);
    }
    
    return maxLength;
}
```

## 2. Valid Palindrome II (LC680)

**Problem**: Given a string, determine if it can be a palindrome after deleting at most one character.

**Approach**: Use two pointers from both ends, handle one mismatch by checking both options.

**Time Complexity**: O(n) - Each character is examined at most twice.

**Space Complexity**: O(1) - In-place comparison.

```cpp
bool validPalindrome(string s) {
    int left = 0;
    int right = s.length() - 1;
    
    // Check for palindrome until we hit a mismatch
    while (left < right) {
        if (s[left] != s[right]) {
            // Try deleting either character
            return isPalindrome(s, left + 1, right) || 
                   isPalindrome(s, left, right - 1);
        }
        left++;
        right--;
    }
    
    return true;  // Already a palindrome
}

bool isPalindrome(const string& s, int left, int right) {
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}
```

## 3. Minimum Size Subarray Sum (LC209)

**Problem**: Find the minimum length subarray with a sum at least k.

**Approach**: Use sliding window to find all valid subarrays and track minimum length.

**Time Complexity**: O(n) - Each element is processed at most twice.

**Space Complexity**: O(1) - Constant extra space.

```cpp
int minSubArrayLen(int target, vector<int>& nums) {
    int left = 0;
    int sum = 0;
    int minLength = INT_MAX;
    
    for (int right = 0; right < nums.size(); right++) {
        sum += nums[right];
        
        // Shrink window from left as long as sum >= target
        while (sum >= target) {
            minLength = min(minLength, right - left + 1);
            sum -= nums[left];
            left++;
        }
    }
    
    return minLength == INT_MAX ? 0 : minLength;
}
```

## 4. Longest Substring Without Repeating Characters (LC3)

**Problem**: Find the length of the longest substring without repeating characters.

**Approach**: Use sliding window with a hash map to track the last position of each character.

**Time Complexity**: O(n) - Single pass through the string.

**Space Complexity**: O(k) where k is the size of the character set.

```cpp
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> lastSeen;  // Char -> last position
    int left = 0;
    int maxLength = 0;
    
    for (int right = 0; right < s.length(); right++) {
        // If character was seen before and is in current window
        if (lastSeen.find(s[right]) != lastSeen.end() && 
            lastSeen[s[right]] >= left) {
            // Move left pointer just past the previous occurrence
            left = lastSeen[s[right]] + 1;
        }
        
        // Update last position of current character
        lastSeen[s[right]] = right;
        
        // Update max length
        maxLength = max(maxLength, right - left + 1);
    }
    
    return maxLength;
}
```

## 5. Trapping Rain Water (LC42)

**Problem**: Given an elevation map represented by an array of integers, compute how much water can be trapped.

**Approach**: Use two pointers from both ends, tracking the maximum height seen from each side.

**Time Complexity**: O(n) - Single pass through the array.

**Space Complexity**: O(1) - Constant extra space.

```cpp
int trap(vector<int>& height) {
    int left = 0;
    int right = height.size() - 1;
    int leftMax = 0;
    int rightMax = 0;
    int water = 0;
    
    while (left < right) {
        // Process the smaller height side first
        if (height[left] < height[right]) {
            // Water can be trapped if current height is less than max seen
            if (height[left] >= leftMax) {
                leftMax = height[left];
            } else {
                water += leftMax - height[left];
            }
            left++;
        } else {
            if (height[right] >= rightMax) {
                rightMax = height[right];
            } else {
                water += rightMax - height[right];
            }
            right--;
        }
    }
    
    return water;
}
```

## 6. Three Sum (LC15)

**Problem**: Find all unique triplets in the array that give the sum of zero.

**Approach**: Sort the array, then use two-pointer technique for each element.

**Time Complexity**: O(n²) - For each element, we do a two-pointer sweep.

**Space Complexity**: O(n) for the result, not counting the sort.

```cpp
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    if (nums.size() < 3) return result;
    
    // Sort the array
    sort(nums.begin(), nums.end());
    
    for (int i = 0; i < nums.size() - 2; i++) {
        // Skip duplicates for first element
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        
        int target = -nums[i];
        int left = i + 1;
        int right = nums.size() - 1;
        
        while (left < right) {
            int sum = nums[left] + nums[right];
            
            if (sum < target) {
                left++;
            } else if (sum > target) {
                right--;
            } else {
                // Found a triplet
                result.push_back({nums[i], nums[left], nums[right]});
                
                // Skip duplicates
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;
                
                left++;
                right--;
            }
        }
    }
    
    return result;
}
```

## Key Patterns for Sliding Window / Two Pointer Problems

1. **Fixed-Size Window**:
   - Window of constant size k slides through the array/string
   - Efficient for problems asking for calculations on subarrays of fixed size

2. **Variable-Size Window**:
   - Window expands and contracts based on a condition
   - Used for finding the longest/shortest subarray meeting a condition

3. **Two-Pointer Technique**:
   - Pointers at both ends moving inward (palindrome checks, container problems)
   - Fast & slow pointers (cycle detection, middle finding)
   - Start & end of a window (sliding window problems)

4. **Common Window Patterns**:
   - Track frequency of elements in the window using a hash map
   - Maintain monotonic property (increasing/decreasing)
   - Update result as the window changes

5. **Optimization Techniques**:
   - Skip duplicate elements when sorted (especially in two-sum or k-sum problems)
   - Pre-process the array (sorting, computing running sums)
   - Track maximum/minimum values within the window

Remember that the key insight is usually figuring out exactly how to expand and shrink the window or move the pointers based on the problem constraints.
