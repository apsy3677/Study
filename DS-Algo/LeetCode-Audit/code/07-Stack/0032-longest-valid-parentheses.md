# 32. Longest Valid Parentheses

[Problem](https://leetcode.com/problems/longest-valid-parentheses/) · Hard · Stack → Index stack

LeetCode tags: string, dynamic-programming, stack, bracket-sequences

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-03-20 16:41 IST · Accepted · C++

[submission 918711517](https://leetcode.com/submissions/detail/918711517/) · tests 231/231 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    int longestValidParentheses(string s) {
        int ans = 0;
        int tempAns =0 ;
        stack<int> st;
        st.push(-1);
        for(int i=0;i<s.size();i++){
            if(s[i] == '('){
                st.push(i);
            }
            else{
                st.pop();
                if(!st.empty()){
                    
                    ans = max(ans, i - st.top());
                }
                else{
                    st.push(i);
                }
            }
        }
        
        return ans;
    }
};
```

## Attempt 2 · 2023-03-20 16:52 IST · Accepted · C++

[submission 918716653](https://leetcode.com/submissions/detail/918716653/) · tests 231/231 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    int longestValidParentheses(string s) {

        int l=0, r= 0;
        int ans = 0;

        for(int i=0;i<s.size();i++){
            if(s[i] == '('){
                l++;
            }
            else
                r++;
            
            if(l==r){
                ans = max(ans, 2*l);
            }
            else if(r>l){
                l=r=0;
            }
        }
        l=r=0;
        for(int i=s.size()-1;i>=0;i--){
            if(s[i] == '('){
                l++;
            }
            else
                r++;
            
            if(l==r){
                ans = max(ans, 2*l);
            }
            else if(r<l){
                l=r=0;
            }
        }

        return ans;
        int tempAns =0 ;
        stack<int> st;
        st.push(-1);
        for(int i=0;i<s.size();i++){
            if(s[i] == '('){
                st.push(i);
            }
            else{
                st.pop();
                if(!st.empty()){
                    
                    ans = max(ans, i - st.top());
                }
                else{
                    st.push(i);
                }
            }
        }
        
        return ans;
    }
};
```
