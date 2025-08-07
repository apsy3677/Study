#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    int findUnsortedSubarray(std::vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;
        
        // Step 1: Find the leftmost element that is out of order
        int left = -1;
        for (int i = 0; i < n - 1; i++) {
            if (nums[i] > nums[i + 1]) {
                left = i;
                break;
            }
        }
        
        // If no such element found, array is already sorted
        if (left == -1) return 0;
        
        // Step 2: Find the rightmost element that is out of order
        int right = -1;
        for (int i = n - 1; i > 0; i--) {
            if (nums[i] < nums[i - 1]) {
                right = i;
                break;
            }
        }
        
        // Step 3: Find min and max in the candidate subarray
        int minVal = INT_MAX, maxVal = INT_MIN;
        for (int i = left; i <= right; i++) {
            minVal = std::min(minVal, nums[i]);
            maxVal = std::max(maxVal, nums[i]);
        }
        
        // Step 4: Expand boundaries
        // Extend left boundary
        while (left > 0 && nums[left - 1] > minVal) {
            left--;
        }
        
        // Extend right boundary
        while (right < n - 1 && nums[right + 1] < maxVal) {
            right++;
        }
        
        // Step 5: Return the length
        return right - left + 1;
    }
    
    // Alternative approach using sorting comparison
    int findUnsortedSubarrayAlternative(std::vector<int>& nums) {
        std::vector<int> sorted_nums = nums;
        std::sort(sorted_nums.begin(), sorted_nums.end());
        
        int left = nums.size(), right = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != sorted_nums[i]) {
                left = std::min(left, i);
                right = std::max(right, i);
            }
        }
        
        return right >= left ? right - left + 1 : 0;
    }
};

// Helper function to print array
void printArray(const std::vector<int>& arr) {
    std::cout << "[";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i];
        if (i < arr.size() - 1) std::cout << ", ";
    }
    std::cout << "]";
}

// Test function
void testSolution() {
    Solution solution;
    
    // Test cases
    std::vector<std::vector<int>> testCases = {
        {2, 6, 4, 8, 10, 9, 15},  // Expected: 5 (subarray [6,4,8,10,9])
        {1, 2, 3, 4},             // Expected: 0 (already sorted)
        {1},                      // Expected: 0 (single element)
        {1, 3, 2, 2, 2},          // Expected: 4 (subarray [3,2,2,2])
        {2, 1},                   // Expected: 2 (entire array)
        {1, 2, 3, 3, 3}           // Expected: 0 (already sorted)
    };
    
    std::cout << "Testing Shortest Unsorted Subarray Solution:\n";
    std::cout << "==========================================\n\n";
    
    for (int i = 0; i < testCases.size(); i++) {
        std::vector<int> nums = testCases[i];
        
        std::cout << "Test Case " << (i + 1) << ":\n";
        std::cout << "Input:  ";
        printArray(nums);
        std::cout << "\n";
        
        int result1 = solution.findUnsortedSubarray(nums);
        int result2 = solution.findUnsortedSubarrayAlternative(nums);
        
        std::cout << "Result (Method 1): " << result1 << "\n";
        std::cout << "Result (Method 2): " << result2 << "\n";
        std::cout << "----------------------------------------\n\n";
    }
}

int main() {
    testSolution();
    
    // Interactive example
    std::cout << "\nInteractive Example:\n";
    std::cout << "Enter array size: ";
    int n;
    std::cin >> n;
    
    if (n > 0) {
        std::vector<int> arr(n);
        std::cout << "Enter " << n << " elements: ";
        for (int i = 0; i < n; i++) {
            std::cin >> arr[i];
        }
        
        Solution solution;
        int result = solution.findUnsortedSubarray(arr);
        
        std::cout << "\nInput array: ";
        printArray(arr);
        std::cout << "\nMinimum length of unsorted subarray: " << result << "\n";
        
        if (result > 0) {
            std::cout << "If you sort any subarray of length " << result 
                      << ", the entire array will become sorted.\n";
        } else {
            std::cout << "The array is already sorted!\n";
        }
    }
    
    return 0;
}
