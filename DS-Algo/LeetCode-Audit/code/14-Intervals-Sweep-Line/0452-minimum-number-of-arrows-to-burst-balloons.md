# 452. Minimum Number of Arrows to Burst Balloons

[Problem](https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/) · Medium · Intervals & Sweep Line → Greedy by end

LeetCode tags: array, greedy, sorting

Attempts since Mar 2023: 3 · accepted: 1 · failed before first AC: 2

## Attempt 1 · 2024-03-23 11:02 IST · Wrong Answer · C++

[submission 1211394392](https://leetcode.com/submissions/detail/1211394392/) · tests 48/50

Failing input:

```text
[[-2147483648,2147483647]]
```

Expected:

```text
1
```

Your output:

```text
0
```

```cpp
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty()) return 0;

        sort(points.begin(), points.end(), [](vector<int> &v1, vector<int> &v2){
            if (v1[1] == v2[1]) {
                return v1[0] < v2[0];
            }
            return v1[1] < v2[1];
        });
        int ans = 0;
        long long endd = INT_MIN;
        for( auto &point : points) {
            if (point[0] > endd){
                ans++;
                endd = point[1];
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2024-03-23 11:03 IST · Runtime Error · C++

[submission 1211394578](https://leetcode.com/submissions/detail/1211394578/) · tests 0/50

Failing input:

```text
[[10,16],[2,8],[1,6],[7,12]]
```

Expected:

```text
2
```

Runtime error:

```text
Line 13: Char 34: runtime error: signed integer overflow: -2147483648 - 5 cannot be represented in type 'int' (solution.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:22:34
```

```cpp
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty()) return 0;

        sort(points.begin(), points.end(), [](vector<int> &v1, vector<int> &v2){
            if (v1[1] == v2[1]) {
                return v1[0] < v2[0];
            }
            return v1[1] < v2[1];
        });
        int ans = 0;
        long long endd = INT_MIN -5 ;
        for( auto &point : points) {
            if (point[0] > endd){
                ans++;
                endd = point[1];
            }
        }
        return ans;
    }
};
```

## Attempt 3 · 2024-03-23 11:03 IST · Accepted · C++

[submission 1211394901](https://leetcode.com/submissions/detail/1211394901/) · tests 50/50 · runtime 267 ms (beats 5.6%)

```cpp
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty()) return 0;

        sort(points.begin(), points.end(), [](vector<int> &v1, vector<int> &v2){
            if (v1[1] == v2[1]) {
                return v1[0] < v2[0];
            }
            return v1[1] < v2[1];
        });
        int ans = 0;
        long long endd = INT_MIN - 5LL ;
        for( auto &point : points) {
            if (point[0] > endd){
                ans++;
                endd = point[1];
            }
        }
        return ans;
    }
};
```
