# 981. Time Based Key-Value Store

[Problem](https://leetcode.com/problems/time-based-key-value-store/) · Medium · Design → Map + binary search

LeetCode tags: hash-table, string, binary-search, design

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2025-03-23 01:21 IST · Accepted · C++

[submission 1582616066](https://leetcode.com/submissions/detail/1582616066/) · tests 53/53 · runtime 50 ms (beats 63.8%)

```cpp
class TimeMap {
    map<string, map<int, string>> ds;
public:
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        ds[key][timestamp] = value;
    }
    
    string get(string key, int timestamp) {
        if (ds.count(key) == 0) return "";

        auto iter =  ds[key].upper_bound(timestamp);

        if (iter == ds[key].begin()) return "";
        iter--;
        return iter->second;
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
```

## Attempt 2 · 2025-03-23 01:21 IST · Accepted · C++

[submission 1582616736](https://leetcode.com/submissions/detail/1582616736/) · tests 53/53 · runtime 72 ms (beats 30.1%)

```cpp
class TimeMap {
    map<string, map<int, string>> ds;
public:
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        ds[key][timestamp] = value;
    }
    
    string get(string key, int timestamp) {
        // if (ds.count(key) == 0) return "";

        auto iter =  ds[key].upper_bound(timestamp);
        if (iter == ds[key].begin()) return "";
        iter--;
        return iter->second;
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
```
