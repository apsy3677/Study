# 1606. Find Servers That Handled Most Number of Requests

[Problem](https://leetcode.com/problems/find-servers-that-handled-most-number-of-requests/) · Hard · Heap / Top-K → Heap + ordered set

LeetCode tags: array, heap-priority-queue, simulation, ordered-set

Attempts since Mar 2023: 6 · accepted: 3 · failed before first AC: 3

## Attempt 1 · 2023-05-05 16:18 IST · Wrong Answer · C++

[submission 944900894](https://leetcode.com/submissions/detail/944900894/) · tests 4/108

Failing input:

```text
3
[1,2,3,4,8,9,10]
[5,2,10,3,1,2,2]
```

Expected:

```text
[1]
```

Your output:

```text
[0,1]
```

```cpp
class Solution {
public:
    typedef pair<long long, int> PLL;
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        vector<int> busyLoad(k, 0);
        unordered_map<int, int> st;
        for(int i=0;i<k;i++) st[i] =1;
        
        priority_queue<PLL, vector<PLL>, greater<PLL> > pq;
        
        for(int i=0;i<k;i++){
            int s = arrival[i];
            int e = s + load[i];
            st.erase(i);
            busyLoad[i]++;
            pq.push({s+load[i], i});
        }
        for(int i=k;i<arrival.size();i++){
            int s = arrival[i];
            int e = s + load[i];
            int rs = i%k;
            while(!pq.empty() && s >= pq.top().first){
                int server  = pq.top().second;
                pq.pop();
                st[server] = 1;
            }
            if(st.empty()) continue; // discard request if all are busy
            if(st.count(rs)){
                st.erase(rs);
                busyLoad[rs]++;
                pq.push({s+load[rs], rs});
            }
            else{
                bool handled = false;
                for(auto key = rs+1; key<k ;key++){
                    if(st.count(rs)){
                        st[rs]=1;
                        break;
                    }
                }
                if(!handled){
                    for(auto key = 0; key<rs ;key++){
                        if(st.count(rs)){
                            st[rs]=1;
                            break;
                        }
                    }
                }
            }
        }
        vector<int> ans;
        int maxi = 0;
        for(int i=0;i<k;i++){
            if(maxi < busyLoad[i]){
                maxi = busyLoad[i];
                // ans.clear();
                // ans.push_back(i);
            }
            
            // ans.push_back(i);
        }
        for(int i=0; i<k; i++){
            if(maxi == busyLoad[i]){
                ans.push_back(i);
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-05-05 17:59 IST · Runtime Error · C++

[submission 944941314](https://leetcode.com/submissions/detail/944941314/) · tests 5/108

Failing input:

```text
3
[1]
[1000000000]
```

Expected:

```text
[0]
```

Runtime error:

```text
=================================================================
==22==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x602000000974 at pc 0x00000034f89a bp 0x7ffd0a63dad0 sp 0x7ffd0a63dac8
READ of size 4 at 0x602000000974 thread T0
    #2 0x7ff3f78da082  (/lib/x86_64-linux-gnu/libc.so.6+0x24082)
0x602000000974 is located 0 bytes to the right of 4-byte region [0x602000000970,0x602000000 ... [1532 more chars]
```

```cpp
class Solution {
public:
    typedef pair<long long, int> PLL;
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        vector<int> busyLoad(k, 0);
        map<int, int> st;
        for(int i=0;i<k;i++) st[i] =1;
        
        priority_queue<PLL, vector<PLL>, greater<PLL> > pq;
        for(auto it : st){
            cout<<it.first<<"|";
        }
        cout<<" :: ";
        for(int i=0;i<k;i++){
            int s = arrival[i];
            int e = s + load[i];
            st.erase(i);
            busyLoad[i]++;
            pq.push({s+load[i], i});
        }
        for(int i=k;i<arrival.size();i++){
            int s = arrival[i];
            int e = s + load[i];
            int rs = i%k;
            
            while(!pq.empty() && s >= pq.top().first){
                int server  = pq.top().second;
                pq.pop();
                st[server] = 1;
            }
            for(auto it : st){
                cout<<it.first<<"|";
            }
            cout<<" :: ";
            if(st.empty()) continue; // discard request if all are busy
            // if(st.count(rs)){
            //     st.erase(rs);
            //     busyLoad[rs]++;
            //     pq.push({s+load[i], rs});
            // }
            // else
            {
                cout<<"binary Search ";
                bool handled = false;
                auto ptr = st.lower_bound(rs);
                if(ptr == st.end()){
                    ptr = st.begin();
                }
                int id = (*ptr).first;
                st.erase(id);
                busyLoad[id]++;
                pq.push({s + load[i], id});
            }
        }
        vector<int> ans;
        int maxi = 0; 
        cout<<"MAXI ";
        for(int i=0;i<k;i++){
            cout<<busyLoad[i]<<"|";
            if(maxi < busyLoad[i]){
                maxi = busyLoad[i];
                // ans.clear();
                // ans.push_back(i);
            }
            
            // ans.push_back(i);
        }
        for(int i=0; i<k; i++){
            if(maxi == busyLoad[i]){
                ans.push_back(i);
            }
        }
        return ans;
    }
};
```

## Attempt 3 · 2023-05-05 18:00 IST · Time Limit Exceeded · C++

[submission 944941874](https://leetcode.com/submissions/detail/944941874/) · tests 98/108

Failing input:

```text
3832
[2,4,33,36,45,46,61,71,75,87,91,92,129,133,135,140,149,164,185,195,204,213,221,225,227,232,249,275,277,315,316,321,331,337,345,354,381,385,394,422,446,479,491,499,530,534,544,549,550,553,559,599,608,610,634,648,650,657,671,677,678,697,699,718,730,737,742,747,759,769,770,777,779,784,807,813,815,834,838,840,853,865,873,876,886,907,908,911,932,938,940,941,963,975,1017,1027,1030,1036,1046,1052,10 ... [50619 more chars]
```

Expected:

```text
[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,1 ... [3319 more chars]
```

```cpp
class Solution {
public:
    typedef pair<long long, int> PLL;
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        vector<int> busyLoad(k, 0);
        map<int, int> st;
        for(int i=0;i<k;i++) st[i] =1;
        
        priority_queue<PLL, vector<PLL>, greater<PLL> > pq;
        for(auto it : st){
            cout<<it.first<<"|";
        }
        cout<<" :: ";
        for(int i=0;i<min(k, int(arrival.size()));i++){
            int s = arrival[i];
            int e = s + load[i];
            st.erase(i);
            busyLoad[i]++;
            pq.push({s+load[i], i});
        }
        for(int i=k;i<arrival.size();i++){
            int s = arrival[i];
            int e = s + load[i];
            int rs = i%k;
            
            while(!pq.empty() && s >= pq.top().first){
                int server  = pq.top().second;
                pq.pop();
                st[server] = 1;
            }
            for(auto it : st){
                cout<<it.first<<"|";
            }
            cout<<" :: ";
            if(st.empty()) continue; // discard request if all are busy
            // if(st.count(rs)){
            //     st.erase(rs);
            //     busyLoad[rs]++;
            //     pq.push({s+load[i], rs});
            // }
            // else
            {
                cout<<"binary Search ";
                bool handled = false;
                auto ptr = st.lower_bound(rs);
                if(ptr == st.end()){
                    ptr = st.begin();
                }
                int id = (*ptr).first;
                st.erase(id);
                busyLoad[id]++;
                pq.push({s + load[i], id});
            }
        }
        vector<int> ans;
        int maxi = 0; 
        cout<<"MAXI ";
        for(int i=0;i<k;i++){
            cout<<busyLoad[i]<<"|";
            if(maxi < busyLoad[i]){
                maxi = busyLoad[i];
                // ans.clear();
                // ans.push_back(i);
            }
            
            // ans.push_back(i);
        }
        for(int i=0; i<k; i++){
            if(maxi == busyLoad[i]){
                ans.push_back(i);
            }
        }
        return ans;
    }
};
```

## Attempt 4 · 2023-05-05 18:01 IST · Accepted · C++

[submission 944942305](https://leetcode.com/submissions/detail/944942305/) · tests 108/108 · runtime 468 ms (beats 5.1%)

```cpp
class Solution {
public:
    typedef pair<long long, int> PLL;
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        vector<int> busyLoad(k, 0);
        map<int, int> st;
        for(int i=0;i<k;i++) st[i] =1;
        
        priority_queue<PLL, vector<PLL>, greater<PLL> > pq;
        // for(auto it : st){
        //     cout<<it.first<<"|";
        // }
        // cout<<" :: ";
        for(int i=0;i<min(k, int(arrival.size()));i++){
            int s = arrival[i];
            int e = s + load[i];
            st.erase(i);
            busyLoad[i]++;
            pq.push({s+load[i], i});
        }
        for(int i=k;i<arrival.size();i++){
            int s = arrival[i];
            int e = s + load[i];
            int rs = i%k;
            
            while(!pq.empty() && s >= pq.top().first){
                int server  = pq.top().second;
                pq.pop();
                st[server] = 1;
            }
            // for(auto it : st){
            //     cout<<it.first<<"|";
            // }
            // cout<<" :: ";
            if(st.empty()) continue; // discard request if all are busy
            // if(st.count(rs)){
            //     st.erase(rs);
            //     busyLoad[rs]++;
            //     pq.push({s+load[i], rs});
            // }
            // else
            {
                // cout<<"binary Search ";
                bool handled = false;
                auto ptr = st.lower_bound(rs);
                if(ptr == st.end()){
                    ptr = st.begin();
                }
                int id = (*ptr).first;
                st.erase(id);
                busyLoad[id]++;
                pq.push({s + load[i], id});
            }
        }
        vector<int> ans;
        int maxi = 0; 
        // cout<<"MAXI ";
        for(int i=0;i<k;i++){
            // cout<<busyLoad[i]<<"|";
            if(maxi < busyLoad[i]){
                maxi = busyLoad[i];
                // ans.clear();
                // ans.push_back(i);
            }
            
            // ans.push_back(i);
        }
        for(int i=0; i<k; i++){
            if(maxi == busyLoad[i]){
                ans.push_back(i);
            }
        }
        return ans;
    }
};
```

## Attempt 5 · 2023-05-05 18:04 IST · Accepted · C++

[submission 944943301](https://leetcode.com/submissions/detail/944943301/) · tests 108/108 · runtime 432 ms (beats 5.1%)

```cpp
class Solution {
public:
    typedef pair<long long, int> PLL;
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        vector<int> busyLoad(k, 0);
        map<int, int> st;
        for(int i=0;i<k;i++) st[i] =1;
        
        priority_queue<PLL, vector<PLL>, greater<PLL> > pq;
        for(int i=0;i<min(k, int(arrival.size()));i++){
            int s = arrival[i];
            int e = s + load[i];
            st.erase(i);
            busyLoad[i]++;
            pq.push({s+load[i], i});
        }
        for(int i=k;i<arrival.size();i++){
            int s = arrival[i];
            int e = s + load[i];
            int rs = i%k;
            
            while(!pq.empty() && s >= pq.top().first){
                int server  = pq.top().second;
                pq.pop();
                st[server] = 1;
            }
            if(!st.empty())  // discard request if all are busy
            {
                // cout<<"binary Search ";
                bool handled = false;
                auto ptr = st.lower_bound(rs);
                if(ptr == st.end()){
                    ptr = st.begin();
                }
                int id = (*ptr).first;
                st.erase(id);
                busyLoad[id]++;
                pq.push({s + load[i], id});
            }
        }
        vector<int> ans;
        int maxi = *max_element(busyLoad.begin(), busyLoad.end()); 
        for(int i=0; i<k; i++){
            if(maxi == busyLoad[i]){
                ans.push_back(i);
            }
        }
        return ans;
    }
};
```

## Attempt 6 · 2023-05-05 18:38 IST · Accepted · C++

[submission 944957969](https://leetcode.com/submissions/detail/944957969/) · tests 108/108 · runtime 458 ms (beats 5.1%)

```cpp
class Solution {
public:
    typedef pair<long long, int> PLL;
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        vector<int> busyLoad(k, 0);
        set<int> st;
        for(int i=0;i<k;i++) st.insert(i);
        
        priority_queue<PLL, vector<PLL>, greater<PLL> > pq;
        for(int i=0;i<min(k, int(arrival.size()));i++){
            int s = arrival[i];
            int e = s + load[i];
            st.erase(i);
            busyLoad[i]++;
            pq.push({s+load[i], i});
        }
        for(int i=k;i<arrival.size();i++){
            int s = arrival[i];
            int e = s + load[i];
            int rs = i%k;
            
            while(!pq.empty() && s >= pq.top().first){
                int server  = pq.top().second;
                pq.pop();
                st.insert(server);
            }
            if(!st.empty())  // discard request if all are busy
            {
                // cout<<"binary Search ";
                bool handled = false;
                auto ptr = st.lower_bound(rs);
                if(ptr == st.end()){
                    ptr = st.begin();
                }
                int id = (*ptr);
                st.erase(id);
                busyLoad[id]++;
                pq.push({s + load[i], id});
            }
        }
        vector<int> ans;
        int maxi = *max_element(busyLoad.begin(), busyLoad.end()); 
        for(int i=0; i<k; i++){
            if(maxi == busyLoad[i]){
                ans.push_back(i);
            }
        }
        return ans;
    }
};
```
