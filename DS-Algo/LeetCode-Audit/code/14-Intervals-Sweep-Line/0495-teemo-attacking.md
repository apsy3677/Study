# 495. Teemo Attacking

[Problem](https://leetcode.com/problems/teemo-attacking/) · Easy · Intervals & Sweep Line → Overlap sum

LeetCode tags: array, simulation

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2024-03-23 11:43 IST · Accepted · C++

[submission 1211418907](https://leetcode.com/submissions/detail/1211418907/) · tests 40/40 · runtime 47 ms (beats 2.1%)

```cpp
class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        vector<pair<int,bool>> points;

        for(auto time : timeSeries) {
            int end = time + duration;
            points.push_back({time, false});
            points.push_back({end, true});
        }
        sort(points.begin(), points.end());
        int totTime =0;
        int count = 0;
        pair <int, bool> prev;
        for(auto &point : points){
            if(count) {
                totTime += point.first - prev.first; 
            }
            point.second ? count-- : count++;
            prev = point;
        }
        return totTime;
    }
};
```
