# 252. Meeting Rooms

[Problem](https://leetcode.com/problems/meeting-rooms/) · Easy · Intervals & Sweep Line → Sort and check overlap

LeetCode tags: array, sorting, quicksort

Attempts since Mar 2023: 3 · accepted: 1 · failed before first AC: 2

## Attempt 1 · 2023-05-05 13:22 IST · Runtime Error · C++

[submission 944826655](https://leetcode.com/submissions/detail/944826655/) · tests 2/78

Failing input:

```text
[]
```

Expected:

```text
true
```

Runtime error:

```text
Line 1034: Char 9: runtime error: reference binding to null pointer of type 'std::vector<int, std::allocator<int>>' (stl_vector.h)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior /usr/bin/../lib/gcc/x86_64-linux-gnu/9/../../../../include/c++/9/bits/stl_vector.h:1043:9
```

```cpp
class Solution {
    static bool cmp(vector<int> &a, vector<int> &b){
        return a[0]<b[0];
    }
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp);
        int end = intervals[0][1];
        for(int i=1;i<intervals.size();i++){
            if(intervals[i][0] <= end){
                return false;
            }
            end = max(end, intervals[i][1]);
        }
        return true;
    }
};
```

## Attempt 2 · 2023-05-05 13:23 IST · Wrong Answer · C++

[submission 944826968](https://leetcode.com/submissions/detail/944826968/) · tests 74/78

Failing input:

```text
[[13,15],[1,13]]
```

Expected:

```text
true
```

Your output:

```text
false
```

```cpp
class Solution {
    static bool cmp(vector<int> &a, vector<int> &b){
        return a[0]<b[0];
    }
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp);
        if(intervals.size() ==0) return true;
        int end = intervals[0][1];
        for(int i=1;i<intervals.size();i++){
            if(intervals[i][0] <= end){
                return false;
            }
            end = max(end, intervals[i][1]);
        }
        return true;
    }
};
```

## Attempt 3 · 2023-05-05 13:24 IST · Accepted · C++

[submission 944827224](https://leetcode.com/submissions/detail/944827224/) · tests 78/78 · runtime 22 ms (beats 5.8%)

```cpp
class Solution {
    static bool cmp(vector<int> &a, vector<int> &b){
        return a[0]<b[0];
    }
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp);
        if(intervals.size() ==0) return true;
        int end = intervals[0][1];
        for(int i=1;i<intervals.size();i++){
            if(intervals[i][0] < end){
                return false;
            }
            end = max(end, intervals[i][1]);
        }
        return true;
    }
};
```
