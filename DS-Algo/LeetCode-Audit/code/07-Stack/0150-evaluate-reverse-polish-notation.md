# 150. Evaluate Reverse Polish Notation

[Problem](https://leetcode.com/problems/evaluate-reverse-polish-notation/) · Medium · Stack → Postfix evaluation

LeetCode tags: array, math, stack

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2025-03-23 00:44 IST · Accepted · C++

[submission 1582588929](https://leetcode.com/submissions/detail/1582588929/) · tests 21/21 · runtime 0 ms (beats 100%)

```cpp
// class Solution {
// public:
//     int evalRPN(vector<string>& tokens) {
//         stack<int> st;
//         for (auto token : tokens) {
//             int operand, op1, op2 ;
//             switch (token) {
//                 case "+" :
//                     //op1
//                     op1 = st.top(); st.pop(); 
//                     op2 = st.top(); st.pop(); 
//                     operand = op1 + op2;
//                     st.push(operand);
//                     break;
//                 case "-" :
//                     op1 = st.top(); st.pop(); 
//                     op2 = st.top(); st.pop(); 
//                     operand = op1 - op2;
//                     st.push(operand);
//                     break;
//                 case "*" :
//                     op1 = st.top(); st.pop(); 
//                     op2 = st.top(); st.pop(); 
//                     operand = op1 * op2;
//                     st.push(operand);
//                     break;
//                 case "/" :
//                     op1 = st.top(); st.pop(); 
//                     op2 = st.top(); st.pop(); 
//                     operand = op1 / op2;
//                     st.push(operand);
//                     break;
//                 default :
//                     // its and operand;
//                     operand = stoi(token);
//                     st.push(operand);
//             }
//         }
//         return st.top();
//     }
// };

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for (auto token : tokens) {
            int operand, op1, op2;
            if (token == "+") {
                op1 = st.top(); st.pop();
                op2 = st.top(); st.pop();
                operand = op2 + op1;
                st.push(operand);
            } else if (token == "-") {
                op1 = st.top(); st.pop();
                op2 = st.top(); st.pop();
                operand = op2 - op1;
                st.push(operand);
            } else if (token == "*") {
                op1 = st.top(); st.pop();
                op2 = st.top(); st.pop();
                operand = op2 * op1;
                st.push(operand);
            } else if (token == "/") {
                op1 = st.top(); st.pop();
                op2 = st.top(); st.pop();
                operand = op2 / op1;
                st.push(operand);
            } else {
                // It's an operand
                operand = stoi(token);
                st.push(operand);
            }
        }
        return st.top();
    }
};
```

## Attempt 2 · 2025-03-23 00:47 IST · Accepted · C++

[submission 1582591241](https://leetcode.com/submissions/detail/1582591241/) · tests 21/21 · runtime 4 ms (beats 18.3%)

```cpp
// class Solution {
// public:
//     int evalRPN(vector<string>& tokens) {
//         stack<int> st;
//         for (auto token : tokens) {
//             int operand, op1, op2 ;
//             switch (token) {
//                 case "+" :
//                     //op1
//                     op1 = st.top(); st.pop(); 
//                     op2 = st.top(); st.pop(); 
//                     operand = op1 + op2;
//                     st.push(operand);
//                     break;
//                 case "-" :
//                     op1 = st.top(); st.pop(); 
//                     op2 = st.top(); st.pop(); 
//                     operand = op1 - op2;
//                     st.push(operand);
//                     break;
//                 case "*" :
//                     op1 = st.top(); st.pop(); 
//                     op2 = st.top(); st.pop(); 
//                     operand = op1 * op2;
//                     st.push(operand);
//                     break;
//                 case "/" :
//                     op1 = st.top(); st.pop(); 
//                     op2 = st.top(); st.pop(); 
//                     operand = op1 / op2;
//                     st.push(operand);
//                     break;
//                 default :
//                     // its and operand;
//                     operand = stoi(token);
//                     st.push(operand);
//             }
//         }
//         return st.top();
//     }
// };

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        unordered_map<string, function<int(int, int)>> operations = {
            {"+", [](int a, int b) { return a + b; }},
            {"-", [](int a, int b) { return a - b; }},
            {"*", [](int a, int b) { return a * b; }},
            {"/", [](int a, int b) { return a / b; }}
        };

        for (auto token : tokens) {
            if (operations.count(token)) {
                int op1 = st.top(); st.pop();
                int op2 = st.top(); st.pop();
                st.push(operations[token](op2, op1));
            } else {
                st.push(stoi(token));
            }
        }
        return st.top();
    }
};
```
