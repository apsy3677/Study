# 735. Asteroid Collision

[Problem](https://leetcode.com/problems/asteroid-collision/) · Medium · Stack → Collision stack

LeetCode tags: array, stack, simulation

Attempts since Mar 2023: 3 · accepted: 2 · failed before first AC: 1

## Attempt 1 · 2023-09-12 20:31 IST · Runtime Error · C++

[submission 1047550220](https://leetcode.com/submissions/detail/1047550220/) · tests 3/275

Failing input:

```text
[-2,-1,1,2]
```

Expected:

```text
[-2,-1,1,2]
```

Runtime error:

```text
Line 171: Char 16: runtime error: reference binding to misaligned address 0xbebebebebebec0ba for type 'int', which requires 4 byte alignment (stl_deque.h)
0xbebebebebebec0ba: note: pointer points here
<memory cannot be printed>
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior /usr/bin/../lib/gcc/x86_64-linux-gnu/9/../../../../include/c++/9/bits/stl_deque.h:180:16
```

```cpp
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> ans;
        for (auto ast: asteroids) {
            if(ast>0) {
                ans.push(ast);
            } else {
                while(!ans.empty()) {
                    if(ans.top() < (-1*ast) )
                        ans.pop();
                    else 
                        break;
                }
                if(ans.top() == (-1*ast) ){
                    ans.pop();
                } else if(ans.empty()) {
                    ans.push(ast);
                } 
            }
        }
        vector<int> finalResult;
        while(!ans.empty()) {
            finalResult.push_back(ans.top());
            ans.pop();
        }
        reverse(finalResult.begin(), finalResult.end());
        return finalResult;
    }
};
```

## Attempt 2 · 2023-09-12 20:46 IST · Accepted · C++

[submission 1047562175](https://leetcode.com/submissions/detail/1047562175/) · tests 275/275 · runtime 7 ms (beats 5.5%)

```cpp
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> ans;
        for (auto ast: asteroids) {
            bool flag = true;
            while(!ans.empty() && (ans.top() > 0 && ast < 0)) {
                if(abs(ans.top()) < abs(ast)) {
                    ans.pop();
                } else if (abs(ans.top()) == abs(ast)) {
                    ans.pop();
                    flag = false;
                    break;
                } else {
                    flag = false;
                    break;
                }
            }
            if(flag) {
                ans.push(ast);
            }
        }
        vector<int> finalResult;
        while(!ans.empty()) {
            finalResult.push_back(ans.top());
            ans.pop();
        }
        reverse(finalResult.begin(), finalResult.end());
        return finalResult;
    }
};
```

## Attempt 3 · 2023-09-12 20:54 IST · Accepted · C++

[submission 1047569035](https://leetcode.com/submissions/detail/1047569035/) · tests 275/275 · runtime 10 ms (beats 5.5%)

```cpp
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> ans;
        for (auto ast: asteroids) {
            if(ast>0) {
                ans.push(ast);
            } else {
                bool flag = true;
                while(!ans.empty() && !(ans.top()<0)) {
                    if(abs(ans.top()) < abs(ast))
                        ans.pop();
                    else if(abs(ans.top()) == abs(ast) ){
                        flag = false;
                        ans.pop();
                        break;
                    }  else {
                        flag = false;
                        break;
                    }
                }
                if(flag) {
                    ans.push(ast);
                } 
            }
        }
        vector<int> finalResult;
        while(!ans.empty()) {
            finalResult.push_back(ans.top());
            ans.pop();
        }
        reverse(finalResult.begin(), finalResult.end());
        return finalResult;
    }
};
```
