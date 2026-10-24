# 20. Valid Parentheses

[Problem](https://leetcode.com/problems/valid-parentheses/) · Easy · Stack → Bracket matching

LeetCode tags: string, stack, bracket-sequences

Attempts since Mar 2023: 5 · accepted: 3 · failed before first AC: 2

## Attempt 1 · 2023-03-06 22:53 IST · Wrong Answer · C++

[submission 910304068](https://leetcode.com/submissions/detail/910304068/) · tests 5/92

Failing input:

```text
"["
```

Expected:

```text
false
```

Your output:

```text
true
```

```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for(char x: s){
            if(x == '(' || x== '{' || x == '[')
                st.push(x);
            else{
                char popped = st.top();
                st.pop();
                
                if(x == ')' && popped != '('){
                    return false;
                }
                else if(x == '}' && popped != '{')
                    return false;
                else if(x == ']' && popped != '[')
                    return false;
            }
        }
        return true;
    }
};
```

## Attempt 2 · 2023-03-06 22:54 IST · Runtime Error · C++

[submission 910304549](https://leetcode.com/submissions/detail/910304549/) · tests 6/92

Failing input:

```text
"]"
```

Expected:

```text
false
```

Runtime error:

```text
AddressSanitizer:DEADLYSIGNAL
=================================================================
==34==ERROR: AddressSanitizer: SEGV on unknown address (pc 0x0000003449e3 bp 0x7ffdd31285b0 sp 0x7ffdd3128420 T0)
==34==The signal is caused by a READ memory access.
==34==Hint: this fault was caused by a dereference of a high value address (see register values below).  Dissassemble the provided pc to l ... [159 more chars]
```

```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for(char x: s){
            if(x == '(' || x== '{' || x == '[')
                st.push(x);
            else{
                char popped = st.top();
                st.pop();
                
                if(x == ')' && popped != '('){
                    return false;
                }
                else if(x == '}' && popped != '{')
                    return false;
                else if(x == ']' && popped != '[')
                    return false;
            }
        }

        return st.empty() ? true : false;
    }
};
```

## Attempt 3 · 2023-03-06 22:58 IST · Accepted · C++

[submission 910307496](https://leetcode.com/submissions/detail/910307496/) · tests 92/92 · runtime 5 ms (beats 0.9%)

```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for(char x: s){
            if(x == '(' || x== '{' || x == '[')
                st.push(x);
            else if (!st.empty()){
                char popped = st.top();
                st.pop();
                
                if(x == ')' && popped != '('){
                    return false;
                }
                else if(x == '}' && popped != '{')
                    return false;
                else if(x == ']' && popped != '[')
                    return false;
            }
            else{
                return false;
            }
        }

        return st.empty() ? true : false;
    }
};
```

## Attempt 4 · 2023-03-07 00:38 IST · Accepted · C++

[submission 910367099](https://leetcode.com/submissions/detail/910367099/) · tests 92/92 · runtime 4 ms (beats 1.3%)

```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for(char x: s){
            if(x == '(' || x== '{' || x == '[')
                st.push(x);
            else if (!st.empty()){
                char popped = st.top();
                st.pop();
                
                if(x == ')' && popped != '('){
                    return false;
                }
                else if(x == '}' && popped != '{')
                    return false;
                else if(x == ']' && popped != '[')
                    return false;
            }
            else{
                return false;
            }
        }

        return st.empty() ? true : false;
    }
};
```

## Attempt 5 · 2024-01-27 22:53 IST · Accepted · Python3

[submission 1158444134](https://leetcode.com/submissions/detail/1158444134/) · tests 96/96 · runtime 40 ms (beats 3.7%)

```python
class Solution:
    def isValid(self, s: str) -> bool:
        
        stack =[]
        bracket_map = {'(':')','{':'}','[':']'}
        for l in s:
            if l in '({[':
                stack.append(l)
            else:
                if not (stack and bracket_map[stack.pop()] == l):
                    return False
                # print(stack)
        return len(stack) ==0
```
