# 359. Logger Rate Limiter

[Problem](https://leetcode.com/problems/logger-rate-limiter/) · Easy · Design → Map of last timestamps

LeetCode tags: hash-table, design, data-stream

Attempts since Mar 2023: 5 · accepted: 5 · failed before first AC: 0

## Attempt 1 · 2023-03-06 23:46 IST · Accepted · C++

[submission 910337699](https://leetcode.com/submissions/detail/910337699/) · tests 20/20 · runtime 92 ms (beats 5.2%)

```cpp
class Logger {
public:
    string lastmsg;
    int timestamp;
    pair<int, string> msg;

    set<string> msgSet;
    deque< pair<int, string> > msgQueue;

    Logger() {
        
    }
    
    bool shouldPrintMessage(int timestamp, string message) {
        
        while(msgQueue.size()>0){
            pair<int, string> curr = msgQueue.front();
            if(timestamp - curr.first >= 10){
                msgQueue.pop_front();
                msgSet.erase(curr.second);
            }
            else{
                break;
            }
        }
        if(msgSet.find(message) == msgSet.end()){
            pair<int, string> newMsgg = {timestamp, message};
            msgQueue.push_back(newMsgg);
            msgSet.insert(message);
            return true;
        }
        else{
            return false;
        }
    }
};

/**
 * Your Logger object will be instantiated and called as such:
 * Logger* obj = new Logger();
 * bool param_1 = obj->shouldPrintMessage(timestamp,message);
 */
```

## Attempt 2 · 2023-03-06 23:53 IST · Accepted · C++

[submission 910342011](https://leetcode.com/submissions/detail/910342011/) · tests 20/20 · runtime 70 ms (beats 5.2%)

```cpp
class Logger {
public:
    string lastmsg;
    int timestamp;
    pair<int, string> msg;

    set<string> msgSet;
    deque< pair<int, string> > msgQueue;

    map<string, int> msgMap;

    Logger() {
        
    }
    
    bool shouldPrintMessage(int timestamp, string message) {
        
        if(msgMap.find(message) == msgMap.end()){
            msgMap[message] = timestamp;
            return true;
        }

        if(timestamp - msgMap[message] >= 10){
            msgMap[message] = timestamp;
            return true;
        }
        else{
            return false;
        }

        // while(msgQueue.size()>0){
        //     pair<int, string> curr = msgQueue.front();
        //     if(timestamp - curr.first >= 10){
        //         msgQueue.pop_front();
        //         msgSet.erase(curr.second);
        //     }
        //     else{
        //         break;
        //     }
        // }
        // if(msgSet.find(message) == msgSet.end()){
        //     pair<int, string> newMsgg = {timestamp, message};
        //     msgQueue.push_back(newMsgg);
        //     msgSet.insert(message);
        //     return true;
        // }
        // else{
        //     return false;
        // }
    }
};

/**
 * Your Logger object will be instantiated and called as such:
 * Logger* obj = new Logger();
 * bool param_1 = obj->shouldPrintMessage(timestamp,message);
 */
```

## Attempt 3 · 2023-03-07 00:38 IST · Accepted · C++

[submission 910367286](https://leetcode.com/submissions/detail/910367286/) · tests 20/20 · runtime 76 ms (beats 5.2%)

```cpp
class Logger {
public:
    string lastmsg;
    int timestamp;
    pair<int, string> msg;

    set<string> msgSet;
    deque< pair<int, string> > msgQueue;

    map<string, int> msgMap;

    Logger() {
        
    }
    
    bool shouldPrintMessage(int timestamp, string message) {
        
        if(msgMap.find(message) == msgMap.end()){
            msgMap[message] = timestamp;
            return true;
        }

        if(timestamp - msgMap[message] >= 10){
            msgMap[message] = timestamp;
            return true;
        }
        else{
            return false;
        }

        // while(msgQueue.size()>0){
        //     pair<int, string> curr = msgQueue.front();
        //     if(timestamp - curr.first >= 10){
        //         msgQueue.pop_front();
        //         msgSet.erase(curr.second);
        //     }
        //     else{
        //         break;
        //     }
        // }
        // if(msgSet.find(message) == msgSet.end()){
        //     pair<int, string> newMsgg = {timestamp, message};
        //     msgQueue.push_back(newMsgg);
        //     msgSet.insert(message);
        //     return true;
        // }
        // else{
        //     return false;
        // }
    }
};

/**
 * Your Logger object will be instantiated and called as such:
 * Logger* obj = new Logger();
 * bool param_1 = obj->shouldPrintMessage(timestamp,message);
 */
```

## Attempt 4 · 2023-04-26 16:16 IST · Accepted · C++

[submission 940008445](https://leetcode.com/submissions/detail/940008445/) · tests 20/20 · runtime 83 ms (beats 5.2%)

```cpp
class Logger {
public:
    string lastmsg;
    int timestamp;
    pair<int, string> msg;

    set<string> msgSet;
    deque< pair<int, string> > msgQueue;

    map<string, int> msgMap;

    Logger() {
        
    }
    
    bool shouldPrintMessage(int timestamp, string message) {
        
        if(msgMap.find(message) == msgMap.end()){
            msgMap[message] = timestamp;
            return true;
        }

        if(timestamp - msgMap[message] >= 10){
            msgMap[message] = timestamp;
            return true;
        }
        else{
            return false;
        }

        // while(msgQueue.size()>0){
        //     pair<int, string> curr = msgQueue.front();
        //     if(timestamp - curr.first >= 10){
        //         msgQueue.pop_front();
        //         msgSet.erase(curr.second);
        //     }
        //     else{
        //         break;
        //     }
        // }
        // if(msgSet.find(message) == msgSet.end()){
        //     pair<int, string> newMsgg = {timestamp, message};
        //     msgQueue.push_back(newMsgg);
        //     msgSet.insert(message);
        //     return true;
        // }
        // else{
        //     return false;
        // }
    }
};

/**
 * Your Logger object will be instantiated and called as such:
 * Logger* obj = new Logger();
 * bool param_1 = obj->shouldPrintMessage(timestamp,message);
 */
```

## Attempt 5 · 2023-04-26 16:19 IST · Accepted · C++

[submission 940009478](https://leetcode.com/submissions/detail/940009478/) · tests 20/20 · runtime 81 ms (beats 5.2%)

```cpp
class Logger {
    map<string, int> msgs;
public:
    Logger() {
        
    }
    
    bool shouldPrintMessage(int timestamp, string message) {
        if(msgs.count(message) == 0 || timestamp - msgs[message] >= 10){
            msgs[message] = timestamp;
            return true;
        }
        return false;
    }
};

/**
 * Your Logger object will be instantiated and called as such:
 * Logger* obj = new Logger();
 * bool param_1 = obj->shouldPrintMessage(timestamp,message);
 */
```
