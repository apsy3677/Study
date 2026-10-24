# 1249. Minimum Remove to Make Valid Parentheses

[Problem](https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/) · Medium · Stack → Index stack

LeetCode tags: string, stack

Attempts since Mar 2023: 5 · accepted: 4 · failed before first AC: 0

## Attempt 1 · 2023-11-21 05:02 IST · Accepted · Python3

[submission 1103050513](https://leetcode.com/submissions/detail/1103050513/) · tests 62/62 · runtime 89 ms (beats 10.0%)

```python
class Solution:
    def minRemoveToMakeValid(self, s: str) -> str:
        stack = []
        indexes_to_remove = set()
        for i,c in enumerate(s):
            if c=='(':
                stack.append(i)
            if c ==')':
                if not stack:
                    indexes_to_remove.add(i)
                else:
                    stack.pop()
        
        indexes_to_remove = indexes_to_remove.union(set(stack))

        return "".join([c for i, c in enumerate(s) if i not in indexes_to_remove])
```

## Attempt 2 · 2023-12-04 09:43 IST · Accepted · Python3

[submission 1111899189](https://leetcode.com/submissions/detail/1111899189/) · tests 62/62 · runtime 115 ms (beats 9.3%)

```python
class Solution:
    def minRemoveToMakeValid3(self, s: str) -> str:
        ## identifying number of brackets to remove can be done with a single variable and a loop
        ## finding valid strings by removing requires a stack or reversing the string and finding the excess )

        
        # while traversing when you encounter ) you can decide if it is excess
        # but you can't decide if ( is excess until the end

        # 1. stack to keep track of open parenthesis
        # set to keep track of invalid brackets - closing brackets
        indexes_to_remove = set()
        stack = []

        for i, l in enumerate(s):
            if l =='(': stack.append(i)
            elif l ==')':
                if not stack:
                    indexes_to_remove.add(i)
                else:
                    stack.pop()
        
        # union stack and indexes to remove using union 
        # O(X+Y) operation which is total N
        indexes_to_remove = indexes_to_remove.union(set(stack))
        
        result = []
        for i,c in enumerate(s):
            if i not in indexes_to_remove:
                result.append(c)
        
        return ''.join(result)


    
    def minRemoveToMakeValid(self, s: str) -> str:
        def delete_invalid(s, open_sym, close_sym):
            balance = 0
            sb = []
            for i,l in enumerate(s):
                if l ==open_sym: balance +=1
                if l==close_sym:
                    if balance<=0:
                        continue
                    balance -=1
                sb.append(l)
            return ''.join(sb)

        s = delete_invalid(s, '(',')')
        s = delete_invalid(s[::-1], ')','(')
        return s[::-1]
```

## Attempt 3 · 2024-02-05 21:31 IST · Accepted · Python3

[submission 1166928511](https://leetcode.com/submissions/detail/1166928511/) · tests 62/62 · runtime 1082 ms (beats 5.0%)

```python
class Solution:
    def minRemoveToMakeValid3(self, s: str) -> str:
        ## identifying number of brackets to remove can be done with a single variable and a loop
        ## finding valid strings by removing requires a stack or reversing the string and finding the excess )

        
        # while traversing when you encounter ) you can decide if it is excess
        # but you can't decide if ( is excess until the end

        # 1. stack to keep track of open parenthesis
        # set to keep track of invalid brackets - closing brackets
        indexes_to_remove = set() # excess closing
        stack = [] # balances opens - finally unmatched opens

        for i, l in enumerate(s):
            if l =='(': stack.append(i)
            elif l ==')':
                if not stack:
                    indexes_to_remove.add(i)
                else:
                    stack.pop()
        
        # union stack and indexes to remove using union 
        # O(X+Y) operation which is total N
        indexes_to_remove = indexes_to_remove.union(set(stack))
        
        result = []
        for i,c in enumerate(s):
            if i not in indexes_to_remove:
                result.append(c)
        
        return ''.join(result)


    
    def minRemoveToMakeValid6(self, s: str) -> str:
        def delete_invalid(s, open_sym, close_sym):
            balance = 0
            sb = []
            for i,l in enumerate(s):
                if l ==open_sym: balance +=1
                if l==close_sym:
                    if balance<=0:
                        continue
                    balance -=1
                sb.append(l)
            return ''.join(sb)

        s = delete_invalid(s, '(',')')
        s = delete_invalid(s[::-1], ')','(')
        return s[::-1]

    def minRemoveToMakeValid(self, s: str) -> str:
        results =[]

        def isValid(s):
            bal = 0
            for l in s:
                if l =='(': bal+=1
                if l==')':
                    if bal <=0:
                        return False
                    bal -=1
            return bal ==0

        total = len(s)

        def backtrack(start, s):
            nonlocal total
            if isValid(s):
                print('found',s)
                results.append(s)
                return

            # if start ==  total

            for i in range(start, len(s)):
                if s[i] in '()':
                    print('calling',s[:i]+s[i+1:])
                    backtrack(i+1, s[:i]+s[i+1:])


        backtrack(0, list(s))

    def minRemoveToMakeValid(self, s: str) -> str:
        indexes_to_remove = set()
        stack = []
        for index, l in enumerate(s):
            if l == '(': stack.append(index)
            if l ==')': 
                if stack:
                    stack.pop()
                else:
                    indexes_to_remove.add(index)

        # indexes_to_remove = indexes_to_remove.union(set(stack)) 
        # print('here')
        result = []
        for i in range(len(s)):
            if i not in indexes_to_remove and i not in set(stack):
                result.append(s[i])

        return ''.join(result)

    def minRemoveToMakeValid2(self, s: str) -> str:
        def deleteInvalid(s, open_sym, close_sym):
            unbalanced_open=0
            balanced_string = []
            for i, l in enumerate(s):
                if l == open_sym:
                    unbalanced_open +=1
                if l == close_sym:
                    if unbalanced_open <=0:
                        continue
                    unbalanced_open -=1
                balanced_string.append(l)
            
            return ''.join(balanced_string)
        
        s= deleteInvalid(s, '(',')')
        s = deleteInvalid(s[::-1], ')','(')

        return s[::-1]
```

## Attempt 4 · 2025-07-16 12:25 IST · Wrong Answer · C++

[submission 1699730806](https://leetcode.com/submissions/detail/1699730806/) · tests 40/62

Failing input:

```text
")(r)t()))y))))e())))))))()(()()(()())()(bzqi(j))l))()))z)d)(()((()()))m)())(()((())((()())()())))()()(())()(((v)))t((())((f)))(()))m)))((a))(())))))(((((l((()(()))(())((()()(()))))v())()(((()(((((()(()()())())p)u(()ea())(()()(())))()()()())(()if)(s((()(x(())w(u((()((()()))()k))))))((())()((()((())(((()((((()h)((())((d)(q())())n()(()))())))(()((()()())u)w((()())())(r()q(())()(((i)(k()))(()()))((() ... [602 more chars]
```

Expected:

```text
"(r)t()ye()()(()()(()())()(bzqi(j))l)()zd(()((()()))m)()(()((())((()())()())))()()(())()(((v)))t((())((f)))(())m((a))(())(l((()(()))(())((()()(()))))v())()()((((()(()()())())p)u(()ea())(()()(())))()()()())(()if)s((()(x(())w(u((()((()()))()k))))))(())()((()((())(((()((((()h)((())((d)(q())())n()(()))())))(()((()()())u)w((()())())(r()q(())()(((i)(k()))(()()))((()))))))()())()(p))))f()(()())v(())()((( ... [541 more chars]
```

Your output:

```text
"(r)t()ye()()()()(()())()(bzqi(j))l)()zd(()((()()))m)()(()((())((()())()())))()()(())()(((v)))t((())((f)))(())m((a))(())(((((l((()(()))(())((()()(()))))v())()(((()(((((()(()()())())p)u(()ea())(()()(())))()()()())(()if)(s((()(x(())w(u((()((()()))()k))))))((())()((()((())(((()((((()h)((())((d)(q())())n()(()))())))(()((()()())u)w((()())())(r()q(())()(((i)(k()))(()()))((()))))))()())()(p))))(f()(((((( ... [573 more chars]
```

```cpp
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        if(s.empty()) return "";
        stack<char> st;
        set<int> index;
        for(int i=0;i < s.size() ; i++) {
            char ch = s[i];
            if (ch == '(') {
                st.push(i);
            } else if (ch == ')'){
                if (!st.empty()) {
                    st.pop();
                } else{
                    index.insert(i);
                }
            }
        }
        while(!st.empty()) {
            index.insert(st.top());
            st.pop();
        }
        string result;
        for(int i =0; i<s.size(); i++) {
            if (index.count(i) == 0) {
                result += s[i];
            }
        }
        return result;
    }
};
```

## Attempt 5 · 2025-07-16 12:26 IST · Accepted · C++

[submission 1699732158](https://leetcode.com/submissions/detail/1699732158/) · tests 62/62 · runtime 5 ms (beats 77.5%)

```cpp
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        if(s.empty()) return "";
        stack<int> st;
        set<int> index;
        for(int i=0;i < s.size() ; i++) {
            char ch = s[i];
            if (ch == '(') {
                st.push(i);
            } else if (ch == ')'){
                if (!st.empty()) {
                    st.pop();
                } else{
                    index.insert(i);
                }
            }
        }
        while(!st.empty()) {
            index.insert(st.top());
            st.pop();
        }
        string result;
        for(int i =0; i<s.size(); i++) {
            if (index.count(i) == 0) {
                result += s[i];
            }
        }
        return result;
    }
};
```
