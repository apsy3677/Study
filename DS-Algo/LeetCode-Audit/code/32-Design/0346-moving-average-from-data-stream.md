# 346. Moving Average from Data Stream

[Problem](https://leetcode.com/problems/moving-average-from-data-stream/) · Easy · Design → Queue

LeetCode tags: array, design, queue, data-stream

Attempts since Mar 2023: 5 · accepted: 5 · failed before first AC: 0

## Attempt 1 · 2023-04-25 17:56 IST · Accepted · C++

[submission 939486498](https://leetcode.com/submissions/detail/939486498/) · tests 11/11 · runtime 26 ms (beats 5.5%)

```cpp
class MovingAverage {
    int capacity;
    list<int> dq;
    long long sum;

public:
    void _cleanup(){
        while(dq.size() > capacity){
            sum -= dq.front();
            dq.pop_front();
        }
    }
    MovingAverage(int size) {
        capacity = size;
        sum =0;
    }
    
    double next(int val) {
        sum += val;
        dq.push_back(val);

        _cleanup();
        double n = (dq.size());
        return double(sum)/n;
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */
```

## Attempt 2 · 2023-04-25 17:56 IST · Accepted · C++

[submission 939486602](https://leetcode.com/submissions/detail/939486602/) · tests 11/11 · runtime 30 ms (beats 5.5%)

```cpp
class MovingAverage {
    int capacity;
    list<int> dq;
    long long sum;

public:
    void _cleanup(){
        while(dq.size() > capacity){
            sum -= dq.front();
            dq.pop_front();
        }
    }
    MovingAverage(int size) {
        capacity = size;
        sum =0;
    }
    
    double next(int val) {
        sum += val;
        dq.push_back(val);

        _cleanup();
        double n = (dq.size());
        return double(sum)/n;
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */
```

## Attempt 3 · 2023-11-27 08:26 IST · Accepted · Python3

[submission 1107144810](https://leetcode.com/submissions/detail/1107144810/) · tests 11/11 · runtime 72 ms (beats 5.2%)

```python
class MovingAverage:
    def __init__(self, size: int):
        self.size = size
        self.queue = deque()
        self.window_sum = 0

    def next(self, val: int) -> float:
        self.queue.append(val)
        self.window_sum += val

        if len(self.queue) > self.size:
            self.window_sum -= self.queue.popleft()

        return self.window_sum/len(self.queue)
```

## Attempt 4 · 2023-12-05 03:00 IST · Accepted · Python3

[submission 1112453515](https://leetcode.com/submissions/detail/1112453515/) · tests 11/11 · runtime 66 ms (beats 5.2%)

```python
class MovingAverage:
    '''
   approach1: ever expanding array without deletions and sum as sum(arrat[-size:])
   time complexity - O(k)
   space - all elements 

   approach2: double ended queue
   delete from one end add add from other end
   when size exceeds, pop and make it k
   time O(1) space O(K)

   approach3: circular queue
   keep head pointer where next value should be inserted and rotate it


    '''
    def __init__(self, size: int):
        self.queue = [0]*size
        self.head = 0
        self.window_sum = 0
        self.count=0
        self.size= size

    def next(self, val: int) -> float:
        # check when to delete element 
        # next element to delete would be pointed to by head
        # which will overwrite it with new value

        # keep count to find average when less than size
        if self.count >= self.size:
            self.window_sum -= self.queue[self.head]
        else:
            self.count+=1

        # assign value to head
        self.queue[self.head]  = val

        # increase head 
        self.head = (self.head +1)% self.size

        # add window_sum
        self.window_sum +=val

        # calculate average
        return self.window_sum / self.count
```

## Attempt 5 · 2023-12-31 03:33 IST · Accepted · Python3

[submission 1132518060](https://leetcode.com/submissions/detail/1132518060/) · tests 11/11 · runtime 112 ms (beats 5.2%)

```python
class MovingAverage1:
    '''
   approach1: ever expanding array without deletions and sum as sum(arrat[-size:])
   time complexity - O(k)
   space - all elements 

   approach2: double ended queue
   delete from one end add add from other end
   when size exceeds, pop and make it k
   time O(1) space O(K)

   approach3: circular queue
   keep head pointer where next value should be inserted and rotate it


    '''
    def __init__(self, size: int):
        self.queue = [0]*size
        self.head = 0
        self.window_sum = 0
        self.count=0
        self.size= size

    def next(self, val: int) -> float:
        # check when to delete element 
        # next element to delete would be pointed to by head
        # which will overwrite it with new value

        # keep count to find average when less than size
        if self.count >= self.size:
            self.window_sum -= self.queue[self.head]
        else:
            self.count+=1

        # assign value to head
        self.queue[self.head]  = val

        # increase head 
        self.head = (self.head +1)% self.size

        # add window_sum
        self.window_sum +=val

        # calculate average
        return self.window_sum / self.count


class MovingAverage:
    '''

    '''
    def __init__(self, size: int):
        self.queue = deque()
        self.size = size
        self.window = 0 
        self.window_sum = 0

    def next(self, val: int) -> float:
        self.queue.append(val)
        self.window +=1
        self.window_sum += val
        if self.window > self.size:
            self.window_sum -= self.queue.popleft()
        
        return self.window_sum/min(self.window, self.size )
```
