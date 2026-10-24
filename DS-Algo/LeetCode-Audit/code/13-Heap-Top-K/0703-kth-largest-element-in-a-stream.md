# 703. Kth Largest Element in a Stream

[Problem](https://leetcode.com/problems/kth-largest-element-in-a-stream/) · Easy · Heap / Top-K → Size-k min-heap

LeetCode tags: tree, design, binary-search-tree, heap-priority-queue, binary-tree, data-stream

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-05-19 10:51 IST · Accepted · C++

[submission 953140991](https://leetcode.com/submissions/detail/953140991/) · tests 10/10 · runtime 36 ms (beats 5.2%)

```cpp
class KthLargest {
    // TC O(K)
    priority_queue<int, vector<int>, greater<int>> pq;
    int capacity;
public:
    KthLargest(int K, vector<int>& arr) {
        this->capacity = K;

        for(int i=0;i<arr.size();i++){
            this->add(arr[i]);
            // pq.push(arr[i]);
            // if(pq.size() > capacity){
            //     pq.pop(); // remove smallest element
            // }
        }
    }
    
    int add(int num) {

        pq.push(num); 
        // important to insert element first as we want to keep track of all the elements of the stream
        if(pq.size() > capacity){
            pq.pop();
        }
        return pq.top(); // return the kth Largest Element
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
```

## Attempt 2 · 2023-05-20 13:43 IST · Accepted · C++

[submission 953785839](https://leetcode.com/submissions/detail/953785839/) · tests 10/10 · runtime 28 ms (beats 5.2%)

```cpp
class KthLargest {
    // TC O(K)
    priority_queue<int, vector<int>, greater<int>> pq;
    int capacity;
public:
    KthLargest(int K, vector<int>& arr) {
        this->capacity = K;

        for(int i=0;i<arr.size();i++){
            this->add(arr[i]);
            // pq.push(arr[i]);
            // if(pq.size() > capacity){
            //     pq.pop(); // remove smallest element
            // }
        }
    }
    
    int add(int num) {

        pq.push(num); 
        // important to insert element first as we want to keep track of all the elements of the stream
        if(pq.size() > capacity){
            pq.pop();
        }
        return pq.top(); // return the kth Largest Element
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
```
