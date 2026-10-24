# 731. My Calendar II

[Problem](https://leetcode.com/problems/my-calendar-ii/) · Medium · Intervals & Sweep Line → Overlap tracking

LeetCode tags: array, binary-search, design, segment-tree, prefix-sum, ordered-set

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2024-03-24 12:27 IST · Accepted · C++

[submission 1212363104](https://leetcode.com/submissions/detail/1212363104/) · tests 97/97 · runtime 167 ms (beats 7.7%)

```cpp
class MyCalendarTwo {
    map<int, int> bookings;
public:
    MyCalendarTwo() {
        
    }
    
    bool book(int start, int end) {
        bookings[start]++;
        bookings[end]--;
        int concurrentBookings = 0;
        for(auto [_, count] : bookings) {
            concurrentBookings += count;
            if (concurrentBookings > 2) {
                bookings[start]--;
                bookings[end]++;
                return false;
            }
        }
        return true;
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */
```

## Attempt 2 · 2024-03-24 12:32 IST · Accepted · C++

[submission 1212366671](https://leetcode.com/submissions/detail/1212366671/) · tests 97/97 · runtime 177 ms (beats 7.3%)

```cpp
class MyCalendarTwo {
    map<int, int> bookings;
public:
    MyCalendarTwo() {
        
    }
    
    bool book(int start, int end) {
        bookings[start]++;
        bookings[end]--;
        int concurrentBookings = 0;
        for(auto &[_, count] : bookings) {
            concurrentBookings += count;
            if (concurrentBookings > 2) {
                bookings[start]--;
                bookings[end]++;
                return false;
            }
        }
        return true;
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */
```

## Attempt 3 · 2025-04-16 17:24 IST · Accepted · C++

[submission 1608485018](https://leetcode.com/submissions/detail/1608485018/) · tests 97/97 · runtime 112 ms (beats 29.3%)

```cpp
class MyCalendarTwo {
    map<int, int> bookings;
public:
    MyCalendarTwo() {
        
    }
    
    bool book(int startTime, int endTime) {
        bookings[startTime]++;
        bookings[endTime]--;
        int curr = 0;
        bool ans = true;
        for (auto &[_, count] : bookings) {
            curr += count; // current bookings
            if (curr > 2)  { 
                bookings[startTime]--;
                bookings[endTime]++;
               return false;
            }
        }
        return ans;
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(startTime,endTime);
 */
```
