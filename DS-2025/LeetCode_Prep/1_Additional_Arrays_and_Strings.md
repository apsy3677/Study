# Additional Array and String Problems

## 1. Valid Word Abbreviation (LC408)

**Problem**: Given a non-empty string `s` and an abbreviation `abbr`, determine if the string matches the abbreviation.

**Approach**: Two-pointer approach to navigate through both the word and abbreviation, handling numeric characters separately.

**Time Complexity**: O(n) where n is the length of the string.

**Space Complexity**: O(1) - constant extra space.

```cpp
bool validWordAbbreviation(string word, string abbr) {
    int i = 0; // pointer for word
    int j = 0; // pointer for abbr
    
    while (i < word.length() && j < abbr.length()) {
        // If characters match, move both pointers
        if (word[i] == abbr[j]) {
            i++;
            j++;
            continue;
        }
        
        // If not a digit or starts with 0, abbreviation is invalid
        if (!isdigit(abbr[j]) || abbr[j] == '0') {
            return false;
        }
        
        // Parse the number from abbreviation
        int num = 0;
        while (j < abbr.length() && isdigit(abbr[j])) {
            num = num * 10 + (abbr[j] - '0');
            j++;
        }
        
        // Skip 'num' characters in the word
        i += num;
    }
    
    // Both strings should be fully consumed
    return i == word.length() && j == abbr.length();
}
```

## 2. Next Permutation (LC31)

**Problem**: Implement next permutation, which rearranges numbers into the lexicographically next greater permutation.

**Approach**: Find the first decreasing element from right, find the next larger element, swap them, and reverse the suffix.

**Time Complexity**: O(n) - Single pass algorithm.

**Space Complexity**: O(1) - In-place operation.

```cpp
void nextPermutation(vector<int>& nums) {
    int n = nums.size();
    int i = n - 2;
    
    // Find the first decreasing element from right
    while (i >= 0 && nums[i] >= nums[i + 1]) {
        i--;
    }
    
    if (i >= 0) {
        // Find the next larger element
        int j = n - 1;
        while (nums[j] <= nums[i]) {
            j--;
        }
        
        // Swap them
        swap(nums[i], nums[j]);
    }
    
    // Reverse the suffix
    reverse(nums.begin() + i + 1, nums.end());
}
```

## 3. Diagonal Traverse II (LC1424)

**Problem**: Return all elements of a 2D matrix in diagonal order from bottom-left to top-right.

**Approach**: Group elements by the sum of their indices (row + col), then traverse these groups in the required order.

**Time Complexity**: O(n) where n is the total number of elements.

**Space Complexity**: O(n) for storing the result.

```cpp
vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
    // Map to store elements grouped by (row + col)
    unordered_map<int, vector<int>> diagonals;
    int maxKey = 0;
    
    // Group elements by diagonal (row + col)
    for (int row = 0; row < nums.size(); row++) {
        for (int col = 0; col < nums[row].size(); col++) {
            int key = row + col;
            diagonals[key].push_back(nums[row][col]);
            maxKey = max(maxKey, key);
        }
    }
    
    // Build the result array
    vector<int> result;
    for (int key = 0; key <= maxKey; key++) {
        // For each diagonal, add elements from bottom to top
        // (elements are added in reverse order in the group)
        for (int i = diagonals[key].size() - 1; i >= 0; i--) {
            result.push_back(diagonals[key][i]);
        }
    }
    
    return result;
}

// Alternative implementation with BFS-like approach
vector<int> findDiagonalOrder2(vector<vector<int>>& nums) {
    vector<int> result;
    queue<pair<int, int>> q;
    q.push({0, 0});
    
    while (!q.empty()) {
        auto [row, col] = q.front();
        q.pop();
        
        result.push_back(nums[row][col]);
        
        // If we're at the first column and there's a row below, 
        // add the element below to queue
        if (col == 0 && row + 1 < nums.size()) {
            q.push({row + 1, col});
        }
        
        // If there's an element to the right in the current row, 
        // add it to queue
        if (col + 1 < nums[row].size()) {
            q.push({row, col + 1});
        }
    }
    
    return result;
}
```

## 4. Add Strings (LC415)

**Problem**: Given two non-negative integers as strings, return their sum as a string without using built-in big integer libraries.

**Approach**: Add digits from right to left, keeping track of carry.

**Time Complexity**: O(max(n, m)) where n and m are the lengths of the input strings.

**Space Complexity**: O(max(n, m)) for the result.

```cpp
string addStrings(string num1, string num2) {
    string result;
    int carry = 0;
    int i = num1.length() - 1;
    int j = num2.length() - 1;
    
    // Add digits from right to left
    while (i >= 0 || j >= 0 || carry > 0) {
        int digit1 = (i >= 0) ? (num1[i--] - '0') : 0;
        int digit2 = (j >= 0) ? (num2[j--] - '0') : 0;
        
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        
        // Add current digit to front of result
        result = to_string(sum % 10) + result;
    }
    
    return result;
}
```

## 5. Maximum Swap (LC670)

**Problem**: Given a non-negative integer, you may swap digits at most once to get the maximum valued number.

**Approach**: Find the rightmost occurrence of each digit and swap the leftmost digit with the largest digit to its right.

**Time Complexity**: O(n) where n is the number of digits.

**Space Complexity**: O(1) - We only need space for 10 possible digits.

```cpp
int maximumSwap(int num) {
    // Convert to string for easy digit manipulation
    string numStr = to_string(num);
    
    // Track the last position of each digit
    vector<int> lastPos(10, -1);
    for (int i = 0; i < numStr.size(); i++) {
        lastPos[numStr[i] - '0'] = i;
    }
    
    // Find a digit that can be swapped for a larger one
    for (int i = 0; i < numStr.size(); i++) {
        // Try to swap with largest possible digit to the right
        for (int d = 9; d > numStr[i] - '0'; d--) {
            if (lastPos[d] > i) {
                // Found a larger digit to the right, swap and return
                swap(numStr[i], numStr[lastPos[d]]);
                return stoi(numStr);
            }
        }
    }
    
    // No swap made, return original number
    return num;
}
```

## 6. Missing Ranges (LC163)

**Problem**: Given a sorted integer array where the range of elements are [lower, upper] inclusive, return its missing ranges.

**Approach**: Compare adjacent elements to find gaps and format the ranges.

**Time Complexity**: O(n) where n is the length of the array.

**Space Complexity**: O(n) for the result in the worst case.

```cpp
vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
    vector<string> result;
    
    // Helper function to format range
    auto formatRange = [](int start, int end) {
        if (start == end) {
            return to_string(start);
        } else {
            return to_string(start) + "->" + to_string(end);
        }
    };
    
    // Handle empty array case
    if (nums.empty()) {
        result.push_back(formatRange(lower, upper));
        return result;
    }
    
    // Check if there's a range before first element
    if (lower < nums[0]) {
        result.push_back(formatRange(lower, nums[0] - 1));
    }
    
    // Check ranges between elements
    for (int i = 1; i < nums.size(); i++) {
        // Skip duplicates
        if (nums[i] == nums[i-1] || nums[i] == nums[i-1] + 1) continue;
        
        result.push_back(formatRange(nums[i-1] + 1, nums[i] - 1));
    }
    
    // Check if there's a range after last element
    if (nums.back() < upper) {
        result.push_back(formatRange(nums.back() + 1, upper));
    }
    
    return result;
}
```

## 7. Custom Sort String (LC791)

**Problem**: Sort a string according to the order defined by another string.

**Approach**: Count frequencies of characters in the target string, then build the result according to the custom order.

**Time Complexity**: O(S + T) where S and T are the lengths of the order and target strings.

**Space Complexity**: O(T) for storing character counts.

```cpp
string customSortString(string order, string s) {
    // Count frequency of each character in s
    vector<int> count(26, 0);
    for (char c : s) {
        count[c - 'a']++;
    }
    
    string result;
    
    // Add characters in order of the 'order' string
    for (char c : order) {
        result.append(count[c - 'a'], c);  // Append 'count[c-'a']' copies of c
        count[c - 'a'] = 0;  // Mark as processed
    }
    
    // Add any remaining characters not in 'order'
    for (char c = 'a'; c <= 'z'; c++) {
        result.append(count[c - 'a'], c);
    }
    
    return result;
}
```

## 8. Valid Number (LC65)

**Problem**: Validate if a string is a valid number (decimal or integer).

**Approach**: Use state transitions to check validity. Define rules for digits, sign, decimal point, and exponent.

**Time Complexity**: O(n) where n is the length of the string.

**Space Complexity**: O(1) - constant extra space.

```cpp
bool isNumber(string s) {
    bool seenDigit = false;
    bool seenExponent = false;
    bool seenDot = false;
    
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        
        // Handle digits
        if (isdigit(c)) {
            seenDigit = true;
        }
        // Handle sign
        else if (c == '+' || c == '-') {
            // Sign must be first char or after exponent
            if (i > 0 && (s[i-1] != 'e' && s[i-1] != 'E')) {
                return false;
            }
        }
        // Handle dot
        else if (c == '.') {
            // Can't have multiple dots or dot after exponent
            if (seenDot || seenExponent) {
                return false;
            }
            seenDot = true;
        }
        // Handle exponent
        else if (c == 'e' || c == 'E') {
            // Can't have multiple exponents or exponent without digits
            if (seenExponent || !seenDigit) {
                return false;
            }
            seenExponent = true;
            // Reset digit flag for digits after exponent
            seenDigit = false;
        }
        else {
            // Invalid character
            return false;
        }
    }
    
    // Must have at least one digit
    return seenDigit;
}
```

## 9. Remove All Adjacent Duplicates In String (LC1047)

**Problem**: Remove all adjacent duplicate characters in the string.

**Approach**: Use stack or string-as-stack to track characters and remove when duplicates are found.

**Time Complexity**: O(n) where n is the length of the string.

**Space Complexity**: O(n) for the result.

```cpp
string removeDuplicates(string s) {
    string result;
    
    for (char c : s) {
        if (!result.empty() && result.back() == c) {
            // Current char matches the last one in result, remove it
            result.pop_back();
        } else {
            // Add to result
            result.push_back(c);
        }
    }
    
    return result;
}
```

## 10. Valid Palindrome II (LC680)

**Problem**: Determine if a string can become a palindrome by removing at most one character.

**Approach**: Use two pointers from both ends. When mismatch found, check if skipping either character makes a palindrome.

**Time Complexity**: O(n) where n is the length of the string.

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

## 11. Dot Product of Two Sparse Vectors (LC1570)

**Problem**: Calculate the dot product of two sparse vectors.

**Approach**: Use a hash map to store non-zero elements, then multiply only non-zero elements.

**Time Complexity**: O(n) for construction, O(min(nonzeros1, nonzeros2)) for dot product.

**Space Complexity**: O(nonzeros) - only store non-zero elements.

```cpp
class SparseVector {
private:
    // {index: value} for non-zero elements
    unordered_map<int, int> nonZeroElements;

public:
    SparseVector(vector<int> &nums) {
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != 0) {
                nonZeroElements[i] = nums[i];
            }
        }
    }
    
    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec) {
        int result = 0;
        
        // Iterate through the map with fewer elements
        const unordered_map<int, int>& smallerMap = 
            (nonZeroElements.size() < vec.nonZeroElements.size()) ? 
            nonZeroElements : vec.nonZeroElements;
        
        const unordered_map<int, int>& largerMap = 
            (nonZeroElements.size() < vec.nonZeroElements.size()) ? 
            vec.nonZeroElements : nonZeroElements;
        
        // Only compute product for indices present in both vectors
        for (const auto& [index, value] : smallerMap) {
            if (largerMap.count(index)) {
                result += value * largerMap.at(index);
            }
        }
        
        return result;
    }
};

// Alternative implementation with array
class SparseVector2 {
private:
    vector<pair<int, int>> nonZeros;  // (index, value) pairs

public:
    SparseVector2(vector<int> &nums) {
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != 0) {
                nonZeros.emplace_back(i, nums[i]);
            }
        }
    }
    
    int dotProduct(SparseVector2& vec) {
        int result = 0;
        int p1 = 0, p2 = 0;
        
        // Two-pointer approach assuming nonZeros are sorted by index
        while (p1 < nonZeros.size() && p2 < vec.nonZeros.size()) {
            if (nonZeros[p1].first == vec.nonZeros[p2].first) {
                // Same index, multiply values
                result += nonZeros[p1].second * vec.nonZeros[p2].second;
                p1++;
                p2++;
            } else if (nonZeros[p1].first < vec.nonZeros[p2].first) {
                // Advance in first vector
                p1++;
            } else {
                // Advance in second vector
                p2++;
            }
        }
        
        return result;
    }
};
```

These implementations provide efficient solutions to the additional array and string problems you requested. Each solution follows the pattern of clear problem statements, optimal approaches, time and space complexity analysis, and well-commented C++ code.
