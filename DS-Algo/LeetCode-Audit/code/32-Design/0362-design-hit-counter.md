# 362. Design Hit Counter

[Problem](https://leetcode.com/problems/design-hit-counter/) · Medium · Design → Queue / circular buckets

LeetCode tags: array, binary-search, design, queue, data-stream

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-03-27 00:34 IST · Accepted · C++

[submission 922612814](https://leetcode.com/submissions/detail/922612814/) · tests 24/24 · runtime 0 ms (beats 100%)

```cpp
class HitCounter {
public:
    deque<int> dq;

    HitCounter() {
        
    }
    
    void hit(int timestamp) {
        while(!dq.empty() && (timestamp - dq.front() >= 300)){
            dq.pop_front();
        }
        dq.push_back(timestamp);
    }
    
    int getHits(int timestamp) {
        while(!dq.empty() && (timestamp - dq.front() >= 300)){
            dq.pop_front();
        }
        return dq.size();
    }
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter* obj = new HitCounter();
 * obj->hit(timestamp);
 * int param_2 = obj->getHits(timestamp);
 */
```

## Attempt 2 · 2023-04-26 16:21 IST · Accepted · C++

[submission 940010469](https://leetcode.com/submissions/detail/940010469/) · tests 24/24 · runtime 0 ms (beats 100%)

```cpp
class HitCounter {
public:
    deque<int> dq;

    HitCounter() {
        
    }
    void cleanup(int timestamp){
        while(!dq.empty() && (timestamp - dq.front() >= 300)){
            dq.pop_front();
        }
    }
    void hit(int timestamp) {
        cleanup(timestamp);
        dq.push_back(timestamp);
    }
    
    int getHits(int timestamp) {
        cleanup(timestamp);
        return dq.size();
    }
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter* obj = new HitCounter();
 * obj->hit(timestamp);
 * int param_2 = obj->getHits(timestamp);
 */
```

## Attempt 3 · 2023-04-26 16:22 IST · Accepted · C++

[submission 940010613](https://leetcode.com/submissions/detail/940010613/) · tests 24/24 · runtime 0 ms (beats 100%)

```cpp
class HitCounter {
public:
    deque<int> dq;

    HitCounter() {
        
    }
    void cleanup(int timestamp){
        while(!dq.empty() && (timestamp - dq.front() >= 300)){
            dq.pop_front();
        }
    }
    void hit(int timestamp) {
        cleanup(timestamp);
        dq.push_back(timestamp);
    }
    
    int getHits(int timestamp) {
        cleanup(timestamp);
        return dq.size();
    }
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter* obj = new HitCounter();
 * obj->hit(timestamp);
 * int param_2 = obj->getHits(timestamp);
 */
```
