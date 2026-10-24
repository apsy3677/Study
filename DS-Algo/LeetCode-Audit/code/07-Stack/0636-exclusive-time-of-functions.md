# 636. Exclusive Time of Functions

[Problem](https://leetcode.com/problems/exclusive-time-of-functions/) · Medium · Stack → Call-stack simulation

LeetCode tags: array, stack

Attempts since Mar 2023: 5 · accepted: 5 · failed before first AC: 0

## Attempt 1 · 2023-03-22 02:51 IST · Accepted · C++

[submission 919762915](https://leetcode.com/submissions/detail/919762915/) · tests 120/120 · runtime 17 ms (beats 13.1%)

```cpp
class Solution {
    struct func{
        int id;
        int start;
        int end;
    };
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> ans(n);
        stack< pair<int,int> > st;
        int prevTime =0;
        for(auto &s : logs ){
            int id = stoi(s.substr(0, s.find(':')) );
            int time =stoi(s.substr(s.rfind(':') +1 ));

            bool end = s.find('e') != -1 ? true : false ;

            if(end){
                st.pop();
                ans[id] += (time - prevTime) +1;
                prevTime = time + 1;
            }
            else{
                if(!st.empty()){
                    ans[st.top().first] += (time - prevTime);
                    
                }
                st.push({id,time});
                prevTime = time;
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-03-22 22:09 IST · Accepted · C++

[submission 920229426](https://leetcode.com/submissions/detail/920229426/) · tests 120/120 · runtime 25 ms (beats 8.4%)

```cpp
class Solution {
    struct func{
        int id;
        int start;
        int end;
    };
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> ans(n);
        stack< pair<int,int> > st;
        int prevTime =0;
        for(auto &s : logs ){
            int id = stoi(s.substr(0, s.find(':')) );
            int time =stoi(s.substr(s.rfind(':') +1 ));

            bool end = s.find('e') != -1 ? true : false ;

            if(end){
                st.pop();
                ans[id] += (time - prevTime) +1;
                prevTime = time + 1;
            }
            else{
                if(!st.empty()){
                    ans[st.top().first] += (time - prevTime);
                    
                }
                st.push({id,time});
                prevTime = time;
            }
        }
        return ans;
    }
};
```

## Attempt 3 · 2023-12-11 02:13 IST · Accepted · Python3

[submission 1116724578](https://leetcode.com/submissions/detail/1116724578/) · tests 120/120 · runtime 72 ms (beats 5.0%)

```python
class Solution:
    def exclusiveTime(self, n: int, logs: List[str]) -> List[int]:
        time_units= [0]*n
        call_stack = []

        last_time = 0
        # for each function call
        for func in logs:
            fid, interval, start = func.split(':')
            fid = int(fid)
            start = int(start)

            # if it is start interval update the units from here till last function call for last fid that is it ran for this many units
            if interval =='start':

                # if there was any previous function call in progress
                if call_stack:
                    time_units[call_stack[-1]] += start - last_time
                # push function call on stack
                call_stack.append(fid)

                # sometimes last call is not available at top of stack after some pop() so you need to keep track of last time
                last_time = start
            # end 
            else:
                # for end it means total units till end of the interval - 2 - 2 means 1 unit 
                time_units[call_stack.pop()] += start - last_time +1
                # and next start will be from 3 
                # because after end it consumes that complete interval
                last_time = start +1
        return time_units
```

## Attempt 4 · 2024-01-04 01:43 IST · Accepted · Python3

[submission 1135984677](https://leetcode.com/submissions/detail/1135984677/) · tests 120/120 · runtime 72 ms (beats 5.0%)

```python
class Solution:
    def exclusiveTime(self, n: int, logs: List[str]) -> List[int]:
        time_units= [0]*n
        call_stack = []

        last_time = 0
        # for each function call
        for func in logs:
            fid, interval, start = func.split(':')
            fid = int(fid)
            start = int(start)

            # if it is start interval update the units from here till last function call for last fid that is it ran for this many units
            if interval =='start':

                # if there was any previous function call in progress
                if call_stack:
                    time_units[call_stack[-1]] += start - last_time
                # push function call on stack
                call_stack.append(fid)

                # sometimes last call is not available at top of stack after some pop() so you need to keep track of last time
                last_time = start
            # end 
            else:
                # for end it means total units till end of the interval - 2 - 2 means 1 unit 
                time_units[call_stack.pop()] += start - last_time +1
                # and next start will be from 3 
                # because after end it consumes that complete interval
                last_time = start +1
        return time_units


    def exclusiveTime(self, n: int, logs: List[str]) -> List[int]:
        call_stack = []
        last_time = 0
        function_times = [0] *n
        for log in logs:
            fid,interval,start = log.split(':')
            start = int(start)
            fid = int(fid)

            if interval =='start':
                # if function call in progress, update time 
                if call_stack:
                    function_times[call_stack[-1]] += start - last_time

                call_stack.append(fid)
                last_time = start
            else:
                #end
                function_times[call_stack.pop()] += start - last_time +1

                last_time = start + 1

        return function_times
```

## Attempt 5 · 2025-07-06 16:35 IST · Accepted · C++

[submission 1688323984](https://leetcode.com/submissions/detail/1688323984/) · tests 120/120 · runtime 7 ms (beats 37.1%)

```cpp
class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> res(n, 0);
        stack<int> st;
        int prev = 0;
        for(auto log : logs) {
            stringstream ss(log);
            string id, start, time_;
            std::getline(ss, id, ':');
            std::getline(ss, start, ':');
            std::getline(ss, time_);

            int id_int = std::stoi(id);
            int time_int = std::stoi(time_);

            if (start == "start") {
                if (!st.empty()) {
                    res[st.top()] += (time_int) - prev;
                }
                st.push(id_int);
                prev = time_int;
            } else {
                res[st.top()] += (time_int +1) - prev;
                prev = time_int + 1;

                st.pop();
            }
        }

        return res;
    }
};
```
