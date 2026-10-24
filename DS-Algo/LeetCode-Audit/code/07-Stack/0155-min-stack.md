# 155. Min Stack

[Problem](https://leetcode.com/problems/min-stack/) · Medium · Stack → Stack with running min

LeetCode tags: stack, design

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2025-03-23 01:25 IST · Accepted · C++

[submission 1582619549](https://leetcode.com/submissions/detail/1582619549/) · tests 31/31 · runtime 6 ms (beats 100%)

```cpp
class MinStack {
public:
    vector< pair<int,int> > s;
	
    MinStack() { }
    
    void push(int val) {
        if(s.empty())
            s.push_back({val,val});
        else
            s.push_back({val,min(s.back().second,val)});    
    }
    
    void pop() { s.pop_back(); }
    
    int top() { return s.back().first; }
    
    int getMin() { return s.back().second; }
};
```
