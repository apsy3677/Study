# 69. Sqrt(x)

[Problem](https://leetcode.com/problems/sqrtx/) · Easy · Binary Search on Answer → Integer square root

LeetCode tags: math, binary-search, newtons-method

Attempts since Mar 2023: 4 · accepted: 3 · failed before first AC: 1

## Attempt 1 · 2024-03-24 12:47 IST · Runtime Error · C++

[submission 1212377477](https://leetcode.com/submissions/detail/1212377477/)

_Code not returned by LeetCode._

## Attempt 2 · 2024-03-24 12:48 IST · Accepted · C++

[submission 1212378377](https://leetcode.com/submissions/detail/1212378377/) · tests 1017/1017 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    int mySqrt(int x) {
        
        if (x==0) return 0;
        
//         1-----------x
//         Answer lies between 1 to x
        int left=1, right = x;
        
        while(left <= right) {
            long long mid = left + (right-left)/2;
            
            if(mid*mid == x) return mid;
            else if(mid*mid < x) left = mid + 1;
            else right = mid -1;
        }
        return right;
    }
};
```

## Attempt 3 · 2024-03-24 12:51 IST · Accepted · C++

[submission 1212380433](https://leetcode.com/submissions/detail/1212380433/) · tests 1017/1017 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    int mySqrt(int x) {
        
        // if (x==0) return 0;
        
//         1-----------x
//         Answer lies between 1 to x
        int left=1, right = x;
        
        while(left <= right) {
            long long mid = left + (right-left)/2;
            
            if(mid*mid == x) return mid;
            else if(mid*mid < x) left = mid + 1;
            else right = mid -1;
        }
        return right;
    }
};
```

## Attempt 4 · 2024-03-24 12:51 IST · Accepted · C++

[submission 1212380641](https://leetcode.com/submissions/detail/1212380641/) · tests 1017/1017 · runtime 5 ms (beats 18.2%)

```cpp
class Solution {
public:
    int mySqrt(int x) {
        
//         1-----------x
//         Answer lies between 1 to x
        int left=1, right = x;
        
        while(left <= right) {
            long long mid = left + (right-left)/2;
            
            if(mid*mid == x) return mid;
            else if(mid*mid < x) left = mid + 1;
            else right = mid -1;
        }
        return right;
    }
};
```
