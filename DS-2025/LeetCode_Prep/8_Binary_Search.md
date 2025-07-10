# Binary Search Problems

## 1. Pow(x, n) (LC50)

**Problem**: Implement pow(x, n), which calculates x raised to the power n.

**Approach**: Use binary exponentiation (divide and conquer) to calculate the result efficiently.

**Time Complexity**: O(log n) - Each step halves the exponent.

**Space Complexity**: O(log n) for the recursion stack.

```cpp
double myPow(double x, int n) {
    // Handle edge cases
    if (n == 0) return 1;
    if (x == 0) return 0;
    
    // Handle negative exponent
    if (n < 0) {
        // Handle INT_MIN special case to avoid overflow
        if (n == INT_MIN) {
            return myPow(1/x, INT_MAX) / x;
        }
        return myPow(1/x, -n);
    }
    
    // Binary exponentiation
    if (n % 2 == 0) {
        // Even exponent: x^n = (x^2)^(n/2)
        return myPow(x * x, n / 2);
    } else {
        // Odd exponent: x^n = x * x^(n-1)
        return x * myPow(x, n - 1);
    }
}

// Iterative version for better space complexity
double myPowIterative(double x, int n) {
    // Handle edge cases and negative exponent
    if (n == 0) return 1;
    if (x == 0) return 0;
    
    long long N = n;  // Convert to long to handle INT_MIN
    if (N < 0) {
        x = 1/x;
        N = -N;
    }
    
    double result = 1;
    double current_product = x;
    
    // Binary exponentiation using bits
    while (N > 0) {
        if (N % 2 == 1) {
            // If current bit is 1, multiply result by current product
            result *= current_product;
        }
        // Square the current product for next bit
        current_product *= current_product;
        N /= 2;  // Move to next bit
    }
    
    return result;
}
```

## 2. Kth Missing Positive Number (LC1539)

**Problem**: Find the kth positive integer that is missing from a sorted array.

**Approach**: Use binary search to find the index where the number of missing positives is at least k.

**Time Complexity**: O(log n) - Binary search on the array.

**Space Complexity**: O(1) - Constant extra space.

```cpp
int findKthPositive(vector<int>& arr, int k) {
    int left = 0;
    int right = arr.size() - 1;
    
    // Binary search for the position where the number of missing elements is at least k
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Calculate how many positive numbers are missing at this position
        // arr[mid] - (mid + 1) = current value - expected value if no numbers were missing
        int missing = arr[mid] - (mid + 1);
        
        if (missing < k) {
            // Not enough missing numbers yet, go right
            left = mid + 1;
        } else {
            // Too many missing numbers, go left
            right = mid - 1;
        }
    }
    
    // At this point, right is the index where missing numbers < k
    // The kth missing number is (right + 1) + k - missing at that position
    // Simplified: right + 1 + k - (arr[right] - (right + 1)) = k + 2*right + 2 - arr[right]
    // Further simplified for the case when right = -1 (all missing are before array): k
    
    return right == -1 ? k : k + right + 1 - (arr[right] - (right + 1));
    
    // Alternative formulation: return left + k;  // This also works
}
```

## 3. Find First and Last Position in Sorted Array (LC34)

**Problem**: Find the starting and ending position of a given target value in a sorted array.

**Approach**: Use binary search twice - once to find the first occurrence, once to find the last.

**Time Complexity**: O(log n) - Two binary searches.

**Space Complexity**: O(1) - Constant extra space.

```cpp
vector<int> searchRange(vector<int>& nums, int target) {
    // Find first occurrence
    int first = findBound(nums, target, true);
    if (first == -1) {
        return {-1, -1};  // Target not found
    }
    
    // Find last occurrence
    int last = findBound(nums, target, false);
    
    return {first, last};
}

int findBound(vector<int>& nums, int target, bool isFirst) {
    int left = 0;
    int right = nums.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            // Found target, but keep searching for bound
            result = mid;
            
            if (isFirst) {
                // For first occurrence, search left half
                right = mid - 1;
            } else {
                // For last occurrence, search right half
                left = mid + 1;
            }
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}
```

## 4. Kth Largest Element in an Array (LC215)

**Problem**: Find the kth largest element in an unsorted array.

**Approach**: Use QuickSelect algorithm (based on QuickSort's partitioning).

**Time Complexity**: O(n) on average, O(n²) worst case.

**Space Complexity**: O(1) - In-place partitioning.

```cpp
int findKthLargest(vector<int>& nums, int k) {
    // Convert to 0-based index for k-th largest
    int targetIndex = nums.size() - k;
    
    return quickSelect(nums, 0, nums.size() - 1, targetIndex);
}

int quickSelect(vector<int>& nums, int left, int right, int targetIndex) {
    // Use random pivot for better average performance
    int pivotIndex = left + rand() % (right - left + 1);
    int pivotValue = nums[pivotIndex];
    
    // Move pivot to the end
    swap(nums[pivotIndex], nums[right]);
    
    // Partition elements around pivot
    int storeIndex = left;
    for (int i = left; i < right; i++) {
        if (nums[i] <= pivotValue) {
            swap(nums[i], nums[storeIndex]);
            storeIndex++;
        }
    }
    
    // Move pivot to its final position
    swap(nums[storeIndex], nums[right]);
    
    // Check if we found the target index
    if (storeIndex == targetIndex) {
        return nums[storeIndex];
    } else if (storeIndex < targetIndex) {
        // Target is in the right partition
        return quickSelect(nums, storeIndex + 1, right, targetIndex);
    } else {
        // Target is in the left partition
        return quickSelect(nums, left, storeIndex - 1, targetIndex);
    }
}
```

## 5. Find Peak Element (LC162)

**Problem**: Find a peak element in an array where neighboring elements are different.

**Approach**: Use binary search to find a peak by comparing with neighbors.

**Time Complexity**: O(log n) - Binary search approach.

**Space Complexity**: O(1) - Constant extra space.

```cpp
int findPeakElement(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        // Compare with next element to determine which half has a peak
        if (nums[mid] > nums[mid + 1]) {
            // Decreasing part, peak is in left half including mid
            right = mid;
        } else {
            // Increasing part, peak is in right half excluding mid
            left = mid + 1;
        }
    }
    
    // When left == right, we've found a peak
    return left;
}
```

## Binary Search Templates and Variations

1. **Standard Binary Search**:
   ```cpp
   int binarySearch(vector<int>& nums, int target) {
       int left = 0;
       int right = nums.size() - 1;
       
       while (left <= right) {
           int mid = left + (right - left) / 2;
           
           if (nums[mid] == target) {
               return mid;  // Found
           } else if (nums[mid] < target) {
               left = mid + 1;  // Search right
           } else {
               right = mid - 1;  // Search left
           }
       }
       
       return -1;  // Not found
   }
   ```

2. **Left-most Boundary Search**:
   ```cpp
   int leftmostBound(vector<int>& nums, int target) {
       int left = 0;
       int right = nums.size() - 1;
       int result = -1;
       
       while (left <= right) {
           int mid = left + (right - left) / 2;
           
           if (nums[mid] >= target) {
               // Move left, but remember this position
               if (nums[mid] == target) {
                   result = mid;
               }
               right = mid - 1;
           } else {
               left = mid + 1;
           }
       }
       
       return result;
   }
   ```

3. **Right-most Boundary Search**:
   ```cpp
   int rightmostBound(vector<int>& nums, int target) {
       int left = 0;
       int right = nums.size() - 1;
       int result = -1;
       
       while (left <= right) {
           int mid = left + (right - left) / 2;
           
           if (nums[mid] <= target) {
               // Move right, but remember this position
               if (nums[mid] == target) {
                   result = mid;
               }
               left = mid + 1;
           } else {
               right = mid - 1;
           }
       }
       
       return result;
   }
   ```

4. **Binary Search on Answers**:
   ```cpp
   int binarySearchAnswer(vector<int>& nums) {
       int left = minPossibleAnswer;
       int right = maxPossibleAnswer;
       
       while (left < right) {
           int mid = left + (right - left) / 2;
           
           if (isValid(mid, nums)) {
               // This value works, but we want the optimal value
               right = mid;
           } else {
               left = mid + 1;
           }
       }
       
       return left;  // The optimal answer
   }
   ```

Remember these key tips for binary search problems:
- Always double-check boundary conditions
- Be careful with integer overflow when calculating mid
- Choose the right template for the problem type
- For complex problems, first identify what to search for
- Check corner cases like empty array, single element
