# Stack-Based Problems

## 1. Minimum Remove to Make Valid Parentheses (LC1249)

**Problem**: Remove the minimum number of parentheses to make the string valid.

**Approach**: Use stack to track mismatched parentheses, then build the result string without invalid ones.

**Time Complexity**: O(n) - Two passes through the string.

**Space Complexity**: O(n) for the stack and result.

```cpp
string minRemoveToMakeValid(string s) {
    stack<int> st;  // Stack to store indices of unmatched '('
    unordered_set<int> indicesToRemove;  // Indices to remove
    
    // First pass: identify invalid parentheses
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            st.push(i);
        } else if (s[i] == ')') {
            if (st.empty()) {
                // Unmatched ')' - mark for removal
                indicesToRemove.insert(i);
            } else {
                // Matched with a previous '('
                st.pop();
            }
        }
    }
    
    // Any '(' left in stack are unmatched - mark for removal
    while (!st.empty()) {
        indicesToRemove.insert(st.top());
        st.pop();
    }
    
    // Build result string excluding marked indices
    string result;
    for (int i = 0; i < s.length(); i++) {
        if (indicesToRemove.find(i) == indicesToRemove.end()) {
            result += s[i];
        }
    }
    
    return result;
}
```

## 2. Simplify Path (LC71)

**Problem**: Simplify a Unix-style file path.

**Approach**: Use stack to track directories, handling ".", ".." and empty components.

**Time Complexity**: O(n) where n is the length of the path.

**Space Complexity**: O(n) for the stack and result.

```cpp
string simplifyPath(string path) {
    stack<string> st;
    stringstream ss(path);
    string component;
    
    // Split by '/' and process each component
    while (getline(ss, component, '/')) {
        if (component == "" || component == ".") {
            // Ignore empty components and current directory
            continue;
        } else if (component == "..") {
            // Go up one directory
            if (!st.empty()) {
                st.pop();
            }
        } else {
            // Valid directory or file
            st.push(component);
        }
    }
    
    // Build the simplified path
    string result;
    vector<string> components;
    
    // Extract components from stack
    while (!st.empty()) {
        components.push_back(st.top());
        st.pop();
    }
    
    // Reverse and join with '/'
    for (int i = components.size() - 1; i >= 0; i--) {
        result += "/" + components[i];
    }
    
    // Handle empty result (root)
    return result.empty() ? "/" : result;
}
```

## 3. Basic Calculator II (LC227)

**Problem**: Implement a basic calculator to evaluate a simple expression string containing numbers and operators `+`, `-`, `*`, `/`.

**Approach**: Use stack to handle operator precedence. Evaluate `*` and `/` immediately, and defer `+` and `-` for later.

**Time Complexity**: O(n) - One pass through the string.

**Space Complexity**: O(n) for the stack.

```cpp
int calculate(string s) {
    stack<int> st;
    int num = 0;
    char op = '+';  // Default starting operator
    
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        
        if (isdigit(c)) {
            // Build multi-digit number
            num = num * 10 + (c - '0');
        }
        
        // Process operator or end of string
        if ((!isdigit(c) && c != ' ') || i == s.length() - 1) {
            // Apply previous operator to current number
            if (op == '+') {
                st.push(num);
            } else if (op == '-') {
                st.push(-num);
            } else if (op == '*') {
                int prev = st.top();
                st.pop();
                st.push(prev * num);
            } else if (op == '/') {
                int prev = st.top();
                st.pop();
                st.push(prev / num);
            }
            
            // Reset for next number
            op = c;
            num = 0;
        }
    }
    
    // Sum all values in stack
    int result = 0;
    while (!st.empty()) {
        result += st.top();
        st.pop();
    }
    
    return result;
}
```

## 4. Minimum Add to Make Parentheses Valid (LC921)

**Problem**: Find the minimum number of parentheses to add to make a string of parentheses valid.

**Approach**: Count open and close mismatches.

**Time Complexity**: O(n) - One pass through the string.

**Space Complexity**: O(1) - Only counters, no stack needed.

```cpp
int minAddToMakeValid(string s) {
    int openNeeded = 0;  // Missing open brackets
    int openCount = 0;   // Current count of open brackets
    
    for (char c : s) {
        if (c == '(') {
            openCount++;
        } else {  // c == ')'
            if (openCount > 0) {
                openCount--;  // Match with an existing open bracket
            } else {
                openNeeded++;  // Need to add an open bracket
            }
        }
    }
    
    // Any unmatched open brackets need closing brackets
    return openNeeded + openCount;
}
```

## 5. Remove All Adjacent Duplicates In String (LC1047)

**Problem**: Remove all adjacent duplicate characters in the string, repeating until no duplicates remain.

**Approach**: Use stack to track characters and remove when duplicates are found.

**Time Complexity**: O(n) - One pass through the string.

**Space Complexity**: O(n) for the stack or result string.

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

## Key Patterns for Stack Problems

1. **Parentheses Matching**:
   - Track opening brackets in stack, match with closing brackets
   - Use for validating expressions, finding unmatched pairs

2. **Next/Previous Greater/Smaller Element**:
   - Use monotonic stack (increasing/decreasing order)
   - Allows O(n) solution for problems requiring comparison with previous elements

3. **Path Parsing**:
   - Split by delimiter, handle special components like ".."
   - Build result by processing components sequentially

4. **Expression Evaluation**:
   - Two-stack approach for complex expressions (operators and operands)
   - Single-pass evaluation by handling operator precedence

5. **Nested Structure Traversal**:
   - Use stack for depth tracking in nested structures
   - Flatten nested structures by traversal with depth information

Remember that stack problems often involve tracking state or history, looking for patterns or matching pairs, and processing elements in a specific order. The key insight is usually figuring out exactly what information to store in the stack.
