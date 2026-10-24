# 759. Employee Free Time

[Problem](https://leetcode.com/problems/employee-free-time/) · Hard · Intervals & Sweep Line → Merge then find gaps

LeetCode tags: array, sweep-line, sorting, heap-priority-queue

Attempts since Mar 2023: 4 · accepted: 4 · failed before first AC: 0

## Attempt 1 · 2023-03-22 11:15 IST · Accepted · C++

[submission 919932005](https://leetcode.com/submissions/detail/919932005/) · tests 52/52 · runtime 36 ms (beats 7.5%)

```cpp
/*
// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};
*/
class Node{
    public:
    int start;
    int empIdx;
    int intervalIdx;
    
    Node(int st, int emp, int interval){
        start = st;
        empIdx = emp;
        intervalIdx = interval;
    }
};

static bool  operator > (const Node & self, const Node & other){
    return self.start > other.start;
}
static bool  operator < (const Node & self, const Node & other){
    return self.start < other.start;
}
class Solution {
    
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> arr) {
        // sort intervals
        // calculate intervals in btwn common 

        priority_queue<Node, vector<Node>, greater<Node> > pq;
        vector<Interval> ans;

        // push first intervals of each employee

        for(int i=0;i<arr.size();i++){
            int start = arr[i][0].start;
            int empIdx = i;
            int intervalIdx = 0;

            pq.push( Node(start, empIdx, intervalIdx));
        }

        int end = arr[pq.top().empIdx][0].end;

        while(!pq.empty()){
            
            Node curr = pq.top();
            pq.pop();

            if(curr.start > end){
                ans.push_back(Interval(end, curr.start));
                end = max(end, arr[curr.empIdx][curr.intervalIdx].end);
            }
            else{
                end = max(end, arr[curr.empIdx][curr.intervalIdx].end);
            }

            // Add next node from list used so far
            if(curr.intervalIdx +1 < arr[curr.empIdx].size()){
                // push Node
                int st = arr[curr.empIdx][curr.intervalIdx+1].start;
                pq.push(Node(st, curr.empIdx, curr.intervalIdx+1));
            }
        }

        return ans;
    }
};
```

## Attempt 2 · 2023-03-22 11:39 IST · Accepted · C++

[submission 919943695](https://leetcode.com/submissions/detail/919943695/) · tests 52/52 · runtime 35 ms (beats 8.7%)

```cpp
/*
// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};
*/

class Node{
    public:
    int start;
    int empIdx;
    int intervalIdx;
    
    Node(int st, int emp, int interval){
        start = st;
        empIdx = emp;
        intervalIdx = interval;
    }

    // bool  operator> (const Node & other){
    //     return start > other.start;
    // }

    // bool  operator< ( const Node & other){
    //     return start < other.start;
    // }

};

static bool  operator > (const Node & self, const Node & other){
    return self.start > other.start;
}
static bool  operator < (const Node & self, const Node & other){
    return self.start < other.start;
}
class Solution {
    
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> arr) {
        // sort intervals
        // calculate intervals in btwn common 

        priority_queue<Node, vector<Node>, greater<Node> > pq;
        vector<Interval> ans;

        // push first intervals of each employee

        for(int i=0;i<arr.size();i++){
            int start = arr[i][0].start;
            int empIdx = i;
            int intervalIdx = 0;

            pq.push( Node(start, empIdx, intervalIdx));
        }

        int end = arr[pq.top().empIdx][0].end;

        while(!pq.empty()){
            
            Node curr = pq.top();
            pq.pop();

            if(curr.start > end){
                ans.push_back(Interval(end, curr.start));
                end = max(end, arr[curr.empIdx][curr.intervalIdx].end);
            }
            else{
                end = max(end, arr[curr.empIdx][curr.intervalIdx].end);
            }

            // Add next node from list used so far
            if(curr.intervalIdx +1 < arr[curr.empIdx].size()){
                // push Node
                int st = arr[curr.empIdx][curr.intervalIdx+1].start;
                pq.push(Node(st, curr.empIdx, curr.intervalIdx+1));
            }
        }

        return ans;
    }
};
```

## Attempt 3 · 2023-03-22 22:09 IST · Accepted · C++

[submission 920229589](https://leetcode.com/submissions/detail/920229589/) · tests 52/52 · runtime 41 ms (beats 5.2%)

```cpp
/*
// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};
*/

class Node{
    public:
    int start;
    int empIdx;
    int intervalIdx;
    
    Node(int st, int emp, int interval){
        start = st;
        empIdx = emp;
        intervalIdx = interval;
    }

    // bool  operator> (const Node & other){
    //     return start > other.start;
    // }

    // bool  operator< ( const Node & other){
    //     return start < other.start;
    // }

};

static bool  operator > (const Node & self, const Node & other){
    return self.start > other.start;
}
static bool  operator < (const Node & self, const Node & other){
    return self.start < other.start;
}
class Solution {
    
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> arr) {
        // sort intervals
        // calculate intervals in btwn common 

        priority_queue<Node, vector<Node>, greater<Node> > pq;
        vector<Interval> ans;

        // push first intervals of each employee

        for(int i=0;i<arr.size();i++){
            int start = arr[i][0].start;
            int empIdx = i;
            int intervalIdx = 0;

            pq.push( Node(start, empIdx, intervalIdx));
        }

        int end = arr[pq.top().empIdx][0].end;

        while(!pq.empty()){
            
            Node curr = pq.top();
            pq.pop();

            if(curr.start > end){
                ans.push_back(Interval(end, curr.start));
                end = max(end, arr[curr.empIdx][curr.intervalIdx].end);
            }
            else{
                end = max(end, arr[curr.empIdx][curr.intervalIdx].end);
            }

            // Add next node from list used so far
            if(curr.intervalIdx +1 < arr[curr.empIdx].size()){
                // push Node
                int st = arr[curr.empIdx][curr.intervalIdx+1].start;
                pq.push(Node(st, curr.empIdx, curr.intervalIdx+1));
            }
        }

        return ans;
    }
};
```

## Attempt 4 · 2024-03-23 14:13 IST · Accepted · C++

[submission 1211504428](https://leetcode.com/submissions/detail/1211504428/) · tests 52/52 · runtime 15 ms (beats 95.9%)

```cpp
/*
// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};
*/

class Node{
    public:
    int start;
    int empIdx;
    int intervalIdx;
    
    Node(int st, int emp, int interval){
        start = st;
        empIdx = emp;
        intervalIdx = interval;
    }

    // bool  operator> (const Node & other){
    //     return start > other.start;
    // }

    // bool  operator< ( const Node & other){
    //     return start < other.start;
    // }

};

static bool  operator > (const Node & self, const Node & other){
    return self.start > other.start;
}
static bool  operator < (const Node & self, const Node & other){
    return self.start < other.start;
}
class Solution {
    
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> arr) {
        // sort intervals
        // calculate intervals in btwn common 

        priority_queue<Node, vector<Node>, greater<Node> > pq;
        vector<Interval> ans;

        // push first intervals of each employee

        for(int i=0;i<arr.size();i++){
            int start = arr[i][0].start;
            int empIdx = i;
            int intervalIdx = 0;

            pq.push( Node(start, empIdx, intervalIdx));
        }

        int end = arr[pq.top().empIdx][0].end;
        // int end = INT_MIN;

        while(!pq.empty()){
            
            Node curr = pq.top();
            pq.pop();

            if(curr.start > end){
                ans.push_back(Interval(end, curr.start));
            }
            end = max(end, arr[curr.empIdx][curr.intervalIdx].end);

            // Add next node from list used so far
            if(curr.intervalIdx +1 < arr[curr.empIdx].size()){
                // push Node
                int st = arr[curr.empIdx][curr.intervalIdx+1].start;
                pq.push(Node(st, curr.empIdx, curr.intervalIdx+1));
            }
        }

        return ans;
    }
};
```
