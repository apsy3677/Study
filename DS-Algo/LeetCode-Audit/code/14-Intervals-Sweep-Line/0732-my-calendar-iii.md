# 732. My Calendar III

[Problem](https://leetcode.com/problems/my-calendar-iii/) · Hard · Intervals & Sweep Line → Sweep-line counts

LeetCode tags: binary-search, design, segment-tree, prefix-sum, ordered-set

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2024-03-24 12:32 IST · Accepted · C++

[submission 1212366736](https://leetcode.com/submissions/detail/1212366736/) · tests 98/98 · runtime 76 ms (beats 15.2%)

```cpp
class MyCalendarThree {
    map<int, int> bookings;
public:
    MyCalendarThree() {
        
    }
    
    int book(int start, int end) {
        bookings[start]++;
        bookings[end]--;
        int concurrentBookings = 0;
        int maxCouncurrentBookings = 0;
        for(auto &[_, count] : bookings) {
            concurrentBookings += count;
            maxCouncurrentBookings = max (concurrentBookings,
                                        maxCouncurrentBookings);
        }
        return maxCouncurrentBookings;
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(startTime,endTime);
 */
```

## Attempt 2 · 2024-03-24 12:38 IST · Accepted · C++

[submission 1212370935](https://leetcode.com/submissions/detail/1212370935/) · tests 98/98 · runtime 79 ms (beats 15.2%)

```cpp
class MyCalendarThree {
    map<int, int> bookings;
public:
    MyCalendarThree() {
        
    }
    
    int book(int start, int end) {
        bookings[start]++;
        bookings[end]--;
        int concurrentBookings = 0;
        int maxCouncurrentBookings = 0;
        for(auto &[_, count] : bookings) {
            concurrentBookings += count;
            maxCouncurrentBookings = max (concurrentBookings,
                                        maxCouncurrentBookings);
        }
        return maxCouncurrentBookings;
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(startTime,endTime);
 */
```

## Attempt 3 · 2025-04-16 17:16 IST · Accepted · C++

[submission 1608480201](https://leetcode.com/submissions/detail/1608480201/) · tests 98/98 · runtime 48 ms (beats 48.6%)

```cpp
class MyCalendarThree {
    map <int, int> bookings;
public:
    MyCalendarThree() {
        
    }
    
    int book(int startTime, int endTime) {
        bookings[startTime]++;
        bookings[endTime]--;
        int ans = 0, curr = 0;
        for (auto &[_, count] : bookings) {
            curr += count; // current bookings
            ans = max(ans, curr);
        }
        
        return ans;
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(startTime,endTime);
 */
```
