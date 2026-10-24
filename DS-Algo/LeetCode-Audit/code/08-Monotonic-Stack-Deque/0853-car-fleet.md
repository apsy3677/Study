# 853. Car Fleet

[Problem](https://leetcode.com/problems/car-fleet/) · Medium · Monotonic Stack / Deque → Sort + stack of arrival times

LeetCode tags: array, stack, sorting, monotonic-stack

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2025-03-23 00:20 IST · Accepted · C++

[submission 1582569036](https://leetcode.com/submissions/detail/1582569036/) · tests 48/48 · runtime 27 ms (beats 97.8%)

```cpp
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        // 10 8 5 3 0
        // 2  4 1 3 1 
        // 1  1 7 3 12 : Times to reach end Dis/speed

        //10 8, after 1 hr
        // 5 3, after 7 hours
        // 0  , after 12 hrs.
        int n = speed.size();
        vector<pair<int,double>> cars(n);

        for(int i=0;i<n;i++) {
            cars[i] = {position[i], (target-position[i])/(double)speed[i]};
        }
        sort(cars.begin(), cars.end());
        int ans = 0;
        int i= n-1;
        for ( i= n-1;i >0 ;i--) {
            if (cars[i].second < cars[i-1].second) {
                ans ++; // this fleet starts here, and next ones
            } else {
                cars[i-1].second = cars[i].second;
            }
        }
        return ans + (i == 0 ? 1 : 0);
    }
};
```

## Attempt 2 · 2025-03-23 00:24 IST · Accepted · C++

[submission 1582572955](https://leetcode.com/submissions/detail/1582572955/) · tests 48/48 · runtime 30 ms (beats 94.6%)

```cpp
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        // 10 8 5 3 0
        // 2  4 1 3 1 
        // 1  1 7 3 12 : Times to reach end Dis/speed

        //10 8, after 1 hr
        // 5 3, after 7 hours
        // 0  , after 12 hrs.
        int n = speed.size();
        vector<pair<int,double>> cars(n);

        for(int i=0;i<n;i++) {
            cars[i] = {position[i], (target-position[i])/(double)speed[i]};
        }
        sort(cars.begin(), cars.end());
        int ans = 0;

        // int i= n-1;
        // for ( i= n-1;i >0 ;i--) {
        //     if (cars[i].second < cars[i-1].second) {
        //         ans ++; // this fleet starts here, and next ones
        //     } else {
        //         cars[i-1].second = cars[i].second;
        //     }
        // }
        // return ans + (i == 0 ? 1 : 0);

        // using stack
        stack<double> s;
        for (int i=n-1;i>=0;i--) {
            if (s.empty() || (cars[i].second > s.top())) {
                s.push(cars[i].second);
            }
        }
        return s.size();
    }
};
```

## Attempt 3 · 2025-03-23 00:30 IST · Accepted · C++

[submission 1582577529](https://leetcode.com/submissions/detail/1582577529/) · tests 48/48 · runtime 32 ms (beats 91.7%)

```cpp
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        // 10 8 5 3 0
        // 2  4 1 3 1 
        // 1  1 7 3 12 : Times to reach end Dis/speed

        //10 8, after 1 hr
        // 5 3, after 7 hours
        // 0  , after 12 hrs.
        int n = speed.size();
        vector<pair<int,double>> cars(n);

        for(int i=0;i<n;i++) {
            cars[i] = {position[i], (target-position[i])/(double)speed[i]};
        }
        sort(cars.begin(), cars.end());
        int ans = 0;

        // int i= n-1;
        // for ( i= n-1;i >0 ;i--) {
        //     if (cars[i].second < cars[i-1].second) {
        //         ans ++; // this fleet starts here, and next ones
        //     } else {
        //         cars[i-1].second = cars[i].second;
        //     }
        // }
        // return ans + (i == 0 ? 1 : 0);

        // using stack
        stack<double> s;
        for (int i=n-1;i>=0;i--) {
            // only push if its a first car
            // Or if its a new car, and its reaching time is greater then the last reached fleet time.
            if (s.empty() || (cars[i].second > s.top())) {
                s.push(cars[i].second);
            }
        }
        return s.size();
    }
};
```
