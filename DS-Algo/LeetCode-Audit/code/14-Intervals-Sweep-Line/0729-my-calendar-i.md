# 729. My Calendar I

[Problem](https://leetcode.com/problems/my-calendar-i/) · Medium · Intervals & Sweep Line → Ordered-map booking

LeetCode tags: array, binary-search, design, segment-tree, ordered-set

Attempts since Mar 2023: 8 · accepted: 6 · failed before first AC: 1

## Attempt 1 · 2023-03-24 14:51 IST · Wrong Answer · C++

[submission 921210126](https://leetcode.com/submissions/detail/921210126/) · tests 1/107

Failing input:

```text
["MyCalendar","book","book","book","book","book","book","book","book","book","book"]
[[],[47,50],[33,41],[39,45],[33,42],[25,32],[26,35],[19,25],[3,8],[8,13],[18,27]]
```

Expected:

```text
[null,true,true,false,false,true,false,true,true,true,false]
```

Your output:

```text
[null,true,false,false,false,false,false,false,false,false,false]
```

```cpp
class MyCalendar {
public:
    map<int,int> mp;
    map<int,int> :: iterator first_iter(int start){
        // find first lower bound of start if present
        auto it = mp.lower_bound(start);

        if(it != mp.begin() && prev(it)->second > start){
            it--;
        }
        return it;
    }
    MyCalendar() {
        
    }
    
    bool book(int start, int end) {
        auto it = first_iter(start);

        // check if start, end is overlapping some existing events 
        //  (start, end)  (first,second)
        
        while(it != mp.end() && it->second >= start ){
            return false;
        }

        mp[start] = end;
        return true;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
```

## Attempt 2 · 2023-03-24 15:00 IST · Accepted · C++

[submission 921213542](https://leetcode.com/submissions/detail/921213542/) · tests 107/107 · runtime 59 ms (beats 18.9%)

```cpp
class MyCalendar {
public:
    map<int,int> mp;
    map<int,int> :: iterator first_iter(int start){
        // find first lower bound of start if present
        auto it = mp.lower_bound(start);

        if(it != mp.begin() && prev(it)->second > start){
            it--;
        }
        return it;
    }
    MyCalendar() {
        
    }
    
    bool book(int start, int end) {
        auto it = first_iter(start);

        // check if start, end is overlapping some existing events 
        //  (start, end)  (first,second)
        
        while(it != mp.end() && it->first < end ){
            return false;
        }

        mp[start] = end;
        return true;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
```

## Attempt 3 · 2024-03-24 10:58 IST · Accepted · C++

[submission 1212298002](https://leetcode.com/submissions/detail/1212298002/) · tests 107/107 · runtime 68 ms (beats 17.6%)

```cpp
class MyCalendar {
public:
    set<pair<int, int>> cal;
    
    MyCalendar() {
        
    }
    // bool bookUsingCal(int start, int end) {
    bool book(int start, int end) {
        pair<int,int> event{start,end};
        auto nEvent = cal.lower_bound(event);

        // next event s1 >= start and s1 < end :: illegal case
        if(nEvent != cal.end() && nEvent->first < end) {
            return false;
        }
        // look for previous element
        if(nEvent != cal.begin()) {
            auto pEvent = prev(nEvent);
            if (pEvent->second > start) {
                return false;
            }
        }
        cal.insert(event);
        return true;
    }

    // bool book(int start, int end) {
    //     return bookUsingCal(start, end);

    //     auto it = first_iter(start);

    //     // check if start, end is overlapping some existing events 
    //     //  (start, end)  (first,second) here first is <=start
    //     // if end > first
        
    //     while(it != mp.end() && it->first < end ){
    //         return false;
    //     }

    //     mp[start] = end;
    //     return true;
    // }
    map<int,int> mp;
    map<int,int> :: iterator first_iter(int start){
        // find first lower bound of start if present
        auto it = mp.lower_bound(start);

        if(it != mp.begin() && prev(it)->second > start){
            it--;
        }
        return it;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
```

## Attempt 4 · 2024-03-24 10:59 IST · Accepted · C++

[submission 1212298466](https://leetcode.com/submissions/detail/1212298466/) · tests 107/107 · runtime 60 ms (beats 18.6%)

```cpp
class MyCalendar {
public:
    set<pair<int, int>> cal;
    
    MyCalendar() {
        
    }
    bool bookUsingCal(int start, int end) {
        pair<int,int> event{start,end};
        auto nEvent = cal.lower_bound(event);

        // next event s1 >= start and s1 < end :: illegal case
        if(nEvent != cal.end() && nEvent->first < end) {
            return false;
        }
        // look for previous element
        if(nEvent != cal.begin()) {
            auto pEvent = prev(nEvent);
            if (pEvent->second > start) {
                return false;
            }
        }
        cal.insert(event);
        return true;
    }

    bool book(int start, int end) {
        return bookUsingCal(start, end);

        auto it = first_iter(start);

        // check if start, end is overlapping some existing events 
        //  (start, end)  (first,second) here first is <=start
        // if end > first
        
        while(it != mp.end() && it->first < end ){
            return false;
        }

        mp[start] = end;
        return true;
    }
    map<int,int> mp;
    map<int,int> :: iterator first_iter(int start){
        // find first lower bound of start if present
        auto it = mp.lower_bound(start);

        if(it != mp.begin() && prev(it)->second > start){
            it--;
        }
        return it;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
```

## Attempt 5 · 2024-03-24 11:02 IST · Accepted · C++

[submission 1212300930](https://leetcode.com/submissions/detail/1212300930/) · tests 107/107 · runtime 60 ms (beats 18.6%)

```cpp
class MyCalendar {
public:
    set<pair<int, int>> cal;
    
    MyCalendar() {
        
    }
    bool bookUsingCal(int start, int end) {
        pair<int,int> event{start,end};
        auto nEvent = cal.lower_bound(event);

        // next event s1 >= start and s1 < end :: illegal case
        if(nEvent != cal.end() && nEvent->first < end) {
            return false;
        }
        // look for previous element
        if(nEvent != cal.begin()) {
            auto pEvent = prev(nEvent);
            if (pEvent->second > start) {
                return false;
            }
        }
        cal.insert(event);
        return true;
    }

    bool book(int start, int end) {
        // return bookUsingCal(start, end);

        auto it = first_iter(start);

        // check if start, end is overlapping some existing events 
        //  (start, end)  (first,second) here first is <=start
        // if end > first
        
        while(it != mp.end() && it->first < end ){
            return false;
        }

        mp[start] = end;
        return true;
    }
    map<int,int> mp;
    map<int,int> :: iterator first_iter(int start){
        // find first lower bound of start if present
        auto it = mp.lower_bound(start);

        if(it != mp.begin() && prev(it)->second > start){
            it--;
        }
        return it;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
```

## Attempt 6 · 2024-03-24 11:19 IST · Wrong Answer · C++

[submission 1212313042](https://leetcode.com/submissions/detail/1212313042/) · tests 1/107

Failing input:

```text
["MyCalendar","book","book","book","book","book","book","book","book","book","book"]
[[],[47,50],[33,41],[39,45],[33,42],[25,32],[26,35],[19,25],[3,8],[8,13],[18,27]]
```

Expected:

```text
[null,true,true,false,false,true,false,true,true,true,false]
```

Your output:

```text
[null,true,false,false,false,false,false,false,false,false,false]
```

```cpp
class MyCalendar {
public:
    set<pair<int, int>> cal;
    
    MyCalendar() {
        
    }
    bool bookUsingCal(int start, int end) {
        pair<int,int> event{start,end};
        auto nEvent = cal.lower_bound(event);

        // next event s1 >= start and s1 < end :: illegal case
        if(nEvent != cal.end() && nEvent->first < end) {
            return false;
        }
        // look for previous element
        if(nEvent != cal.begin()) {
            auto pEvent = prev(nEvent);
            if (pEvent->second > start) {
                return false;
            }
        }
        cal.insert(event);
        return true;
    }

    bool book(int start, int end) {
        // return bookUsingCal(start, end);

        auto it = first_iter(start);

        // check if start, end is overlapping some existing events 
        //  (start, end)  (first,second) here first is <=start
        // if end > first
        
        if(it != mp.end() && (it->second > start || it->first < end) ){
            return false;
        }

        mp[start] = end;
        return true;
    }
    map<int,int> mp;
    map<int,int> :: iterator first_iter(int start){
        // find first lower bound of start if present
        auto it = mp.lower_bound(start);
        if(it != mp.begin() && prev(it)->second > start){
            it--;
        }
        return it;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
```

## Attempt 7 · 2024-03-24 11:22 IST · Accepted · C++

[submission 1212315380](https://leetcode.com/submissions/detail/1212315380/) · tests 107/107 · runtime 76 ms (beats 16.9%)

```cpp
class MyCalendar {
public:
    set<pair<int, int>> cal;
    
    MyCalendar() {
        
    }
    bool bookUsingCal(int start, int end) {
        pair<int,int> event{start,end};
        auto nEvent = cal.lower_bound(event);

        // next event s1 >= start and s1 < end :: illegal case
        if(nEvent != cal.end() && nEvent->first < end) {
            return false;
        }
        // look for previous element
        if(nEvent != cal.begin()) {
            auto pEvent = prev(nEvent);
            if (pEvent->second > start) {
                return false;
            }
        }
        cal.insert(event);
        return true;
    }

    bool book(int start, int end) {
        // return bookUsingCal(start, end);

        auto it = first_iter(start);

        // check if start, end is overlapping some existing events 
        //  (start, end)  (first,second) here first is <=start
        // if end > first
        
        if(it != mp.end() && (it->first < end) ){
            return false;
        }

        mp[start] = end;
        return true;
    }
    map<int,int> mp;
    map<int,int> :: iterator first_iter(int start){
        // find first lower bound of start if present
        auto it = mp.lower_bound(start);
        if(it != mp.begin() && prev(it)->second > start){
            it--;
        }
        return it;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
```

## Attempt 8 · 2025-04-16 17:23 IST · Accepted · C++

[submission 1608484538](https://leetcode.com/submissions/detail/1608484538/) · tests 107/107 · runtime 135 ms (beats 13.0%)

```cpp
class MyCalendar {
    map <int, int> bookings;
public:
    MyCalendar() {
        
    }
    
    bool book(int startTime, int endTime) {
        bookings[startTime]++;
        bookings[endTime]--;
        int curr = 0;
        bool ans = true;
        for (auto &[_, count] : bookings) {
            curr += count; // current bookings
            if (curr > 1)  { 
                bookings[startTime]--;
                bookings[endTime]++;
               return false;
            }
        }
        
        return ans;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(startTime,endTime);
 */
```
