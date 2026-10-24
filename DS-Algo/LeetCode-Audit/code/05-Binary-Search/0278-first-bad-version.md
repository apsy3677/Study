# 278. First Bad Version

[Problem](https://leetcode.com/problems/first-bad-version/) · Easy · Binary Search → First true

LeetCode tags: binary-search, interactive

Attempts since Mar 2023: 5 · accepted: 4 · failed before first AC: 0

## Attempt 1 · 2023-12-31 08:25 IST · Accepted · Python3

[submission 1132654946](https://leetcode.com/submissions/detail/1132654946/) · tests 24/24 · runtime 49 ms (beats 23.9%)

```python
# The isBadVersion API is already defined for you.
# def isBadVersion(version: int) -> bool:

class Solution:
    def firstBadVersion(self, n: int) -> int:
        l = 0
        r = n
        
        while l < r:
            mid = (l+r)//2
            if isBadVersion(mid):
                r = mid
            else:
                l = mid + 1
            
            # print(l, r, mid)
            
        # print(l)
        return l
```

## Attempt 2 · 2024-03-24 13:13 IST · Accepted · C++

[submission 1212396090](https://leetcode.com/submissions/detail/1212396090/) · tests 24/24 · runtime 2 ms (beats 52.9%)

```cpp
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int left = 1, right = n;
        int ans = -1;
        while(left <= right) {
            int mid = left + (right-left)/2;
            if(isBadVersion(mid)){
                ans = mid;
                right = mid-1;
            }
            else{
                left = mid+1;
            }
        }
        return ans;
    }
};
```

## Attempt 3 · 2024-03-24 13:15 IST · Accepted · C++

[submission 1212396995](https://leetcode.com/submissions/detail/1212396995/) · tests 24/24 · runtime 0 ms (beats 100%)

```cpp
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int left = 1, right = n;
        // int ans = -1;
        while(left <= right) {
            int mid = left + (right-left)/2;
            if(isBadVersion(mid)){
                // ans = mid;
                right = mid-1;
            }
            else{
                left = mid+1;
            }
        }
        return left;
    }
};
```

## Attempt 4 · 2024-03-24 13:15 IST · Wrong Answer · C++

[submission 1212397199](https://leetcode.com/submissions/detail/1212397199/) · tests 16/24

Failing input:

```text
3
2
```

Expected:

```text
2
```

Your output:

```text
1
```

```cpp
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int left = 1, right = n;
        // int ans = -1;
        while(left < right) {
            int mid = left + (right-left)/2;
            if(isBadVersion(mid)){
                // ans = mid;
                right = mid-1;
            }
            else{
                left = mid+1;
            }
        }
        return left;
    }
};
```

## Attempt 5 · 2024-03-24 13:18 IST · Accepted · C++

[submission 1212399382](https://leetcode.com/submissions/detail/1212399382/) · tests 24/24 · runtime 0 ms (beats 100%)

```cpp
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int left = 1, right = n;
        // int ans = -1;
        while(left < right) {
            int mid = left + (right-left)/2;
            if(isBadVersion(mid)){
                // ans = mid;
                right = mid;
            }
            else{
                left = mid+1;
            }
        }
        return left;
    }
};
```
