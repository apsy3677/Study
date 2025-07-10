# More Array and String Problems

## 1. Longest Common Prefix (LC14)

**Problem**: Write a function to find the longest common prefix string amongst an array of strings. If there is no common prefix, return an empty string "".

**Approach**: Vertical scanning - Compare characters at the same position for all strings.

**Time Complexity**: O(S) where S is the sum of all characters in all strings.

**Space Complexity**: O(1) - constant extra space.

```cpp
string longestCommonPrefix(vector<string>& strs) {
    if (strs.empty()) return "";
    
    for (int i = 0; i < strs[0].length(); i++) {
        char c = strs[0][i];
        for (int j = 1; j < strs.size(); j++) {
            // If we've reached the end of any string or found a different character
            if (i == strs[j].length() || strs[j][i] != c) {
                return strs[0].substr(0, i);
            }
        }
    }
    return strs[0]; // All strings are identical to the first string
}
```

## 2. String to Integer (atoi) (LC8)

**Problem**: Implement the `myAtoi(string s)` function, which converts a string to a 32-bit signed integer.

**Approach**: Parse the string character by character, handling whitespace, sign, and overflow cases.

**Time Complexity**: O(n) where n is the length of the string.

**Space Complexity**: O(1) - constant extra space.

```cpp
int myAtoi(string s) {
    int i = 0;
    int sign = 1;
    long long result = 0; // Using long long to handle overflow
    
    // Skip leading whitespace
    while (i < s.length() && s[i] == ' ') {
        i++;
    }
    
    // Check for sign
    if (i < s.length() && (s[i] == '+' || s[i] == '-')) {
        sign = (s[i] == '-') ? -1 : 1;
        i++;
    }
    
    // Process digits
    while (i < s.length() && isdigit(s[i])) {
        result = result * 10 + (s[i] - '0');
        
        // Check for overflow
        if (result * sign > INT_MAX) return INT_MAX;
        if (result * sign < INT_MIN) return INT_MIN;
        
        i++;
    }
    
    return result * sign;
}
```

## 3. Count and Say (LC38)

**Problem**: The count-and-say sequence is a sequence of digit strings defined by the recursive formula:
- countAndSay(1) = "1"
- countAndSay(n) is the way you would "say" the digit string from countAndSay(n-1).

For example, the saying and conversion for digit string "3322251":
Two 3's, three 2's, one 5, and one 1 becomes "23321511".

**Approach**: Iterative approach to build each term of the sequence.

**Time Complexity**: O(n * L) where n is the input number and L is the maximum length of the sequence.

**Space Complexity**: O(L) where L is the length of the result string.

```cpp
string countAndSay(int n) {
    if (n == 1) return "1";
    
    string result = "1";
    
    for (int i = 2; i <= n; i++) {
        string newResult = "";
        char currentChar = result[0];
        int count = 1;
        
        for (int j = 1; j < result.length(); j++) {
            if (result[j] == currentChar) {
                count++;
            } else {
                // Add count and character to new result
                newResult += to_string(count) + currentChar;
                currentChar = result[j];
                count = 1;
            }
        }
        
        // Add the last group
        newResult += to_string(count) + currentChar;
        result = newResult;
    }
    
    return result;
}
```

## 4. ZigZag Conversion (LC6)

**Problem**: The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this:
```
P   A   H   N
A P L S I I G
Y   I   R
```
And then read line by line: "PAHNAPLSIIGYIR". Write the code that will take a string and make this conversion given a number of rows.

**Approach**: Use a mathematical pattern to determine where each character should go.

**Time Complexity**: O(n) where n is the length of the string.

**Space Complexity**: O(n) to store the result string.

```cpp
string convert(string s, int numRows) {
    if (numRows == 1 || numRows >= s.length()) return s;
    
    vector<string> rows(numRows);
    int currentRow = 0;
    bool goingDown = false;
    
    for (char c : s) {
        rows[currentRow] += c;
        
        // Change direction at the top or bottom rows
        if (currentRow == 0 || currentRow == numRows - 1) {
            goingDown = !goingDown;
        }
        
        currentRow += goingDown ? 1 : -1;
    }
    
    string result;
    for (string row : rows) {
        result += row;
    }
    
    return result;
}
```

## 5. Longest Substring with At Most K Distinct Characters (LC340)

**Problem**: Given a string s and an integer k, return the length of the longest substring of s that contains at most k distinct characters.

**Approach**: Sliding window with a hashmap to track character frequencies.

**Time Complexity**: O(n) where n is the length of the string.

**Space Complexity**: O(k) where k is the maximum number of distinct characters.

```cpp
int lengthOfLongestSubstringKDistinct(string s, int k) {
    if (s.empty() || k == 0) return 0;
    
    unordered_map<char, int> charCount;
    int left = 0;
    int maxLength = 0;
    
    for (int right = 0; right < s.length(); right++) {
        charCount[s[right]]++;
        
        // Shrink the window if we have more than k distinct characters
        while (charCount.size() > k) {
            charCount[s[left]]--;
            if (charCount[s[left]] == 0) {
                charCount.erase(s[left]);
            }
            left++;
        }
        
        maxLength = max(maxLength, right - left + 1);
    }
    
    return maxLength;
}
```

## 6. Text Justification (LC68)

**Problem**: Given an array of words and a width maxWidth, format the text such that each line has exactly maxWidth characters and is fully (left and right) justified.

**Approach**: Greedy approach to fill lines with as many words as possible.

**Time Complexity**: O(n) where n is the total number of characters across all words.

**Space Complexity**: O(n) for storing the result.

```cpp
vector<string> fullJustify(vector<string>& words, int maxWidth) {
    vector<string> result;
    int i = 0;
    
    while (i < words.size()) {
        // Calculate how many words fit on the current line
        int j = i;
        int lineLength = 0;
        
        while (j < words.size() && lineLength + words[j].length() + (j - i) <= maxWidth) {
            lineLength += words[j].length();
            j++;
        }
        
        // Calculate spaces
        int spacesNeeded = maxWidth - lineLength;
        int numWords = j - i;
        
        string line;
        
        // Last line or only one word on the line - left justified
        if (j == words.size() || numWords == 1) {
            for (int k = i; k < j; k++) {
                line += words[k];
                if (k < j - 1) {
                    line += " ";
                    spacesNeeded--;
                }
            }
            // Add remaining spaces to the end
            line += string(spacesNeeded, ' ');
        } else {
            // Middle lines with multiple words - fully justified
            int spacesBetweenWords = spacesNeeded / (numWords - 1);
            int extraSpaces = spacesNeeded % (numWords - 1);
            
            for (int k = i; k < j; k++) {
                line += words[k];
                
                if (k < j - 1) {
                    int spacesToAdd = spacesBetweenWords + (extraSpaces-- > 0 ? 1 : 0);
                    line += string(spacesToAdd, ' ');
                }
            }
        }
        
        result.push_back(line);
        i = j;
    }
    
    return result;
}
```

## 7. Integer to English Words (LC273)

**Problem**: Convert a non-negative integer to its English words representation.

**Approach**: Divide and conquer by breaking the number into chunks of thousands.

**Time Complexity**: O(log n) where n is the input integer.

**Space Complexity**: O(1) as we use a fixed set of string literals.

```cpp
string numberToWords(int num) {
    if (num == 0) return "Zero";
    
    vector<string> thousands = {"", "Thousand", "Million", "Billion"};
    vector<string> ones = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
                           "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    vector<string> tens = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    
    function<string(int)> helper = [&](int n) {
        if (n == 0) return string("");
        else if (n < 20) return ones[n] + " ";
        else if (n < 100) return tens[n / 10] + " " + helper(n % 10);
        else return ones[n / 100] + " Hundred " + helper(n % 100);
    };
    
    string result;
    int i = 0;
    
    while (num > 0) {
        if (num % 1000 != 0) {
            result = helper(num % 1000) + thousands[i] + (i > 0 ? " " : "") + result;
        }
        num /= 1000;
        i++;
    }
    
    // Remove trailing space
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    
    return result;
}
```

## 8. Minimum Window Substring (LC76)

**Problem**: Given two strings s and t, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".

**Approach**: Sliding window with character frequency tracking.

**Time Complexity**: O(s + t) where s and t are the lengths of the strings.

**Space Complexity**: O(t) for storing character counts.

```cpp
string minWindow(string s, string t) {
    if (s.empty() || t.empty()) return "";
    
    unordered_map<char, int> targetCount;
    for (char c : t) {
        targetCount[c]++;
    }
    
    int required = targetCount.size();
    int formed = 0;
    int left = 0;
    int right = 0;
    
    unordered_map<char, int> windowCount;
    int minLen = INT_MAX;
    int minLeft = 0;
    
    while (right < s.length()) {
        // Add the current character to our window
        char c = s[right];
        windowCount[c]++;
        
        // If we've satisfied the count for this character in t
        if (targetCount.count(c) && windowCount[c] == targetCount[c]) {
            formed++;
        }
        
        // Try to minimize the window by moving left pointer
        while (left <= right && formed == required) {
            c = s[left];
            
            // Update minimum window
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minLeft = left;
            }
            
            // Remove the leftmost character
            windowCount[c]--;
            if (targetCount.count(c) && windowCount[c] < targetCount[c]) {
                formed--;
            }
            
            left++;
        }
        
        right++;
    }
    
    return minLen == INT_MAX ? "" : s.substr(minLeft, minLen);
}
```
