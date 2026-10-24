# 933. Number of Recent Calls

[Problem](https://leetcode.com/problems/number-of-recent-calls/) · Easy · Design → Queue

LeetCode tags: design, queue, data-stream

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-09-13 00:36 IST · Accepted · C++

[submission 1047767716](https://leetcode.com/submissions/detail/1047767716/) · tests 68/68 · runtime 134 ms (beats 5.7%)

```cpp
class RecentCounter {
    queue<int> record;
public:
    RecentCounter() {
    }
    
    int ping(int t) {
        while(!record.empty() && (t - record.front()>3000)) {
            record.pop();
        }
        record.push(t);
        return record.size();
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
```
