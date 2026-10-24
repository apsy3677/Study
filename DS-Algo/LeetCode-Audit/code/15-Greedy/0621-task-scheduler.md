# 621. Task Scheduler

[Problem](https://leetcode.com/problems/task-scheduler/) · Medium · Greedy → Counting formula

LeetCode tags: array, hash-table, greedy, sorting, heap-priority-queue, counting

Attempts since Mar 2023: 4 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-03-22 01:42 IST · Accepted · C++

[submission 919736147](https://leetcode.com/submissions/detail/919736147/) · tests 71/71 · runtime 79 ms (beats 7.0%)

```cpp
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        map<char, int> mp, lastTasks;
        int m =tasks.size();
        for(int i=0;i<tasks.size();i++){
            mp[tasks[i]]++;
        }
        vector<int> fre;
        int ans =0;
        for(auto &x : mp){
            fre.push_back(x.second);
        }
        sort(fre.begin(), fre.end(), greater<int>());

        int f_max = fre[0];
        int idletime = (f_max -1)*n;
        
        for(int i=1;i<fre.size();i++){
            idletime -= min(f_max-1, fre[i]);
        }
        if(idletime < 0)
            idletime =0;
        
        return tasks.size() + idletime;

        // deque<char> dq;

        // while(m--){
        //     // chose one task to complete
        //     // find out time required
        //     char chosen;
        //     int taskTypes = mp.size();
        //     if(taskTypes >= n){

        //     }
        //     if(!dq.empty())
        //         dq.pop_front();
        //     dq.push_back(chosen);
        // }
        // return ans;

    }
};
```

## Attempt 2 · 2023-03-22 01:44 IST · Wrong Answer · C++

[submission 919736885](https://leetcode.com/submissions/detail/919736885/) · tests 60/71

Failing input:

```text
["A","A","A","B","B","B"]
0
```

Expected:

```text
6
```

Your output:

```text
4
```

```cpp
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        map<char, int> mp, lastTasks;
        int m =tasks.size();
        for(int i=0;i<tasks.size();i++){
            mp[tasks[i]]++;
        }
        vector<int> fre;
        int ans =0;
        for(auto &x : mp){
            fre.push_back(x.second);
        }
        sort(fre.begin(), fre.end(), greater<int>());

        int f_max = fre[0];
        int idletime = (f_max -1)*n;
        
        for(int i=1;i<fre.size();i++){
            idletime -= min(f_max-1, fre[i]);
        }
        // if(idletime < 0)
        //     idletime =0;
        
        return tasks.size() + idletime;

        // deque<char> dq;

        // while(m--){
        //     // chose one task to complete
        //     // find out time required
        //     char chosen;
        //     int taskTypes = mp.size();
        //     if(taskTypes >= n){

        //     }
        //     if(!dq.empty())
        //         dq.pop_front();
        //     dq.push_back(chosen);
        // }
        // return ans;

    }
};
```

## Attempt 3 · 2023-03-22 01:57 IST · Accepted · C++

[submission 919742388](https://leetcode.com/submissions/detail/919742388/) · tests 71/71 · runtime 83 ms (beats 6.9%)

```cpp
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        map<char, int> mp, lastTasks;
        int m =tasks.size();
        for(int i=0;i<tasks.size();i++){
            mp[tasks[i]]++;
        }
        vector<int> fre;
        int ans =0, f_max =0;
        for(auto &x : mp){
            fre.push_back(x.second);
            f_max = max(f_max, x.second);
        }
        sort(fre.begin(), fre.end(), greater<int>());
        int n_max =0;
        for(auto x: fre){
            if(x == f_max)
                n_max++;
        }
        ans = max((int)tasks.size(), (f_max-1)*(n+1) + n_max);
        return ans;

        
        int idletime = (f_max -1)*n;
        
        for(int i=1;i<fre.size();i++){
            idletime -= min(f_max-1, fre[i]);
        }
        if(idletime < 0)
            idletime =0;
        
        return tasks.size() + idletime;

        // deque<char> dq;

        // while(m--){
        //     // chose one task to complete
        //     // find out time required
        //     char chosen;
        //     int taskTypes = mp.size();
        //     if(taskTypes >= n){

        //     }
        //     if(!dq.empty())
        //         dq.pop_front();
        //     dq.push_back(chosen);
        // }
        // return ans;

    }
};
```

## Attempt 4 · 2023-03-22 22:08 IST · Accepted · C++

[submission 920229298](https://leetcode.com/submissions/detail/920229298/) · tests 71/71 · runtime 65 ms (beats 7.3%)

```cpp
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        map<char, int> mp, lastTasks;
        int m =tasks.size();
        for(int i=0;i<tasks.size();i++){
            mp[tasks[i]]++;
        }
        vector<int> fre;
        int ans =0, f_max =0;
        for(auto &x : mp){
            fre.push_back(x.second);
            f_max = max(f_max, x.second);
        }
        sort(fre.begin(), fre.end(), greater<int>());
        int n_max =0;
        for(auto x: fre){
            if(x == f_max)
                n_max++;
        }
        ans = max((int)tasks.size(), (f_max-1)*(n+1) + n_max);
        return ans;

        
        int idletime = (f_max -1)*n;
        
        for(int i=1;i<fre.size();i++){
            idletime -= min(f_max-1, fre[i]);
        }
        if(idletime < 0)
            idletime =0;
        
        return tasks.size() + idletime;

        // deque<char> dq;

        // while(m--){
        //     // chose one task to complete
        //     // find out time required
        //     char chosen;
        //     int taskTypes = mp.size();
        //     if(taskTypes >= n){

        //     }
        //     if(!dq.empty())
        //         dq.pop_front();
        //     dq.push_back(chosen);
        // }
        // return ans;

    }
};
```
