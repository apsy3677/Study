# 2402. Meeting Rooms III

[Problem](https://leetcode.com/problems/meeting-rooms-iii/) · Hard · Heap / Top-K → Two-heap simulation

LeetCode tags: array, hash-table, sorting, heap-priority-queue, simulation

Attempts since Mar 2023: 7 · accepted: 4 · failed before first AC: 1

## Attempt 1 · 2023-03-24 00:24 IST · Time Limit Exceeded · C++

[submission 920905017](https://leetcode.com/submissions/detail/920905017/) · tests 0/82

Failing input:

```text
2
[[0,10],[1,5],[2,7],[3,4]]
```

Expected:

```text
0
```

```cpp
class Solution {
    typedef pair<int,int> PII;
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        sort(meetings.begin(), meetings.end());

        vector<int> used(n, 0);
        priority_queue<int, vector<int>, greater<int>> rooms;
        priority_queue<PII, vector<PII>, greater<PII>> endTimes;

        for(int i=0;i<n;i++){
            rooms.push(i);
        }

        int i=0;
        int ans =0;
        int end =0;
        int start_ =0;
        while(i < meetings.size()){
            int start = meetings[i][0];
            int finish = meetings[i][1];
            // find a free room
            start_= max(start, start_);
            // traverse and end all meetings finished by time start
            while(!endTimes.empty()){
                PII top = endTimes.top();
                if(top.first <= start_){
                    endTimes.pop();
                    rooms.push(top.second);
                }
            }
            int freeRoom =0;
                // endTimes.push(make_pair(finish, freeRoom));
            if(rooms.size()>0){
                freeRoom = rooms.top();
                rooms.pop();
                cout<<endTimes.size();
                endTimes.push(make_pair(finish, freeRoom));
                
            }
            else if(!endTimes.empty()){
                // finish a meeting which is closest
                PII top = endTimes.top();
                endTimes.pop();
                rooms.push(top.second);
                freeRoom = rooms.top();
                rooms.pop();
                endTimes.push({top.second + finish -start, freeRoom});
            }
            cout<<"Out of While Loop";
            used[freeRoom]++;
            i++;
        }
        ans = 0;
        for(int i=1; i<n; i++){
            if(used[ans] < used[i])
                ans =i;
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-03-24 00:27 IST · Accepted · C++

[submission 920906718](https://leetcode.com/submissions/detail/920906718/) · tests 82/82 · runtime 639 ms (beats 5.0%)

```cpp
class Solution {
    typedef pair<int,int> PII;
public:
    int book(int n, vector<vector<int>>& meetings){
        sort(meetings.begin(), meetings.end());
        
        /* Create a priority queue for engaged rooms. Each node of PQ will store {current_meeting_ending_time, room_number} */
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> engaged;
        
        /* Create a priority queue for non-engaged rooms. Each node of PQ will store {room_number} */
        priority_queue<int, vector<int>, greater<int>> unused;
        
        /* Frequency map to store the frequency of meetings in each room */
        unordered_map<int, int> freq;
        
        /* Currently all the rooms are mepty */
        for(int i = 0; i < n; i++) {
            unused.push(i);
        }
        
        for(auto x:meetings) {
            int s = x[0], e = x[1];
            
            /* Move the meeting rooms in engaged, with ending_time <= s, to unused */ 
            while(engaged.size() > 0 && engaged.top().first <= s) {
                int room = engaged.top().second;
                engaged.pop();
                
                unused.push(room);
            }
            
            /* If there are multiple empty rooms, choose the one with lower room_number */
            if(unused.size() > 0) 
            {
                int room = unused.top();
                unused.pop();
                
                freq[abs(room)] += 1;
                
                /* Mark the room as engaged */
                engaged.push({e, room});
            }
            /* If there are no empty rooms, wait for the engaged room with nearest ending time to empty */
            else 
            {
                pair<long long, int> topmost = engaged.top();
                engaged.pop();
            
                freq[abs(topmost.second)] += 1;
                
                /* Since duration has to be the same, the newEnd will be sum(end_time_of_the_prev_meeting, duration) */ 
                long long newEnd = topmost.first;
                newEnd += (e - s);
                
                /* Mark the room as engaged */
                engaged.push({newEnd, topmost.second});
            }
        }
        
        /* Find the lowest room_number with maximum frequency */
        int maxi = 0;
        for(int i = 1; i < n; i++) {
            if(freq[i] > freq[maxi])
                maxi = i;
        }
        return maxi;
    }
    int mostBooked(int n, vector<vector<int>>& meetings) {

        return book(n, meetings);

        sort(meetings.begin(), meetings.end());

        vector<int> used(n, 0);
        priority_queue<int, vector<int>, greater<int>> rooms;
        priority_queue<PII, vector<PII>, greater<PII>> endTimes;

        for(int i=0;i<n;i++){
            rooms.push(i);
        }

        int i=0;
        int ans =0;
        int end =0;
        int start_ =0;
        while(i < meetings.size()){
            int start = meetings[i][0];
            int finish = meetings[i][1];
            // find a free room
            start_= max(start, start_);
            // traverse and end all meetings finished by time start
            while(!endTimes.empty()){
                PII top = endTimes.top();
                if(top.first <= start_){
                    endTimes.pop();
                    rooms.push(top.second);
                }
            }
            int freeRoom =0;
                // endTimes.push(make_pair(finish, freeRoom));
            if(rooms.size()>0){
                freeRoom = rooms.top();
                rooms.pop();
                cout<<endTimes.size();
                endTimes.push(make_pair(finish, freeRoom));
                
            }
            else if(!endTimes.empty()){
                // finish a meeting which is closest
                PII top = endTimes.top();
                endTimes.pop();
                rooms.push(top.second);
                freeRoom = rooms.top();
                rooms.pop();
                endTimes.push({top.second + finish -start, freeRoom});
            }
            cout<<"Out of While Loop";
            used[freeRoom]++;
            i++;
        }
        ans = 0;
        for(int i=1; i<n; i++){
            if(used[ans] < used[i])
                ans =i;
        }
        return ans;
    }
};
```

## Attempt 3 · 2023-04-02 01:50 IST · Runtime Error · C++

[submission 926173772](https://leetcode.com/submissions/detail/926173772/) · tests 72/82

Failing input:

```text
10
[[1,300001],[2,300002],[3,300003],[4,300004],[5,300005],[6,300006],[7,300007],[8,300008],[9,300009],[10,300010],[11,300011],[12,300012],[13,300013],[14,300014],[15,300015],[16,300016],[17,300017],[18,300018],[19,300019],[20,300020],[21,300021],[22,300022],[23,300023],[24,300024],[25,300025],[26,300026],[27,300027],[28,300028],[29,300029],[30,300030],[31,300031],[32,300032],[33,300033],[34,30003 ... [1188653 more chars]
```

Expected:

```text
1
```

Runtime error:

```text
Line 121: Char 42: runtime error: signed integer overflow: 2147400001 + 371581 cannot be represented in type 'int' (solution.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:130:42
```

```cpp
class Solution {
    typedef pair<int,int> PII;
public:
    int book(int n, vector<vector<int>>& meetings){
        sort(meetings.begin(), meetings.end());
        
        /* Create a priority queue for engaged rooms. Each node of PQ will store {current_meeting_ending_time, room_number} */
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> engaged;
        
        /* Create a priority queue for non-engaged rooms. Each node of PQ will store {room_number} */
        priority_queue<int, vector<int>, greater<int>> unused;
        
        /* Frequency map to store the frequency of meetings in each room */
        unordered_map<int, int> freq;
        
        /* Currently all the rooms are mepty */
        for(int i = 0; i < n; i++) {
            unused.push(i);
        }
        
        for(auto x:meetings) {
            int s = x[0], e = x[1];
            
            /* Move the meeting rooms in engaged, with ending_time <= s, to unused */ 
            while(engaged.size() > 0 && engaged.top().first <= s) {
                int room = engaged.top().second;
                engaged.pop();
                
                unused.push(room);
            }
            
            /* If there are multiple empty rooms, choose the one with lower room_number */
            if(unused.size() > 0) 
            {
                int room = unused.top();
                unused.pop();
                
                freq[abs(room)] += 1;
                
                /* Mark the room as engaged */
                engaged.push({e, room});
            }
            /* If there are no empty rooms, wait for the engaged room with nearest ending time to empty */
            else 
            {
                pair<long long, int> topmost = engaged.top();
                engaged.pop();
            
                freq[abs(topmost.second)] += 1;
                
                /* Since duration has to be the same, the newEnd will be sum(end_time_of_the_prev_meeting, duration) */ 
                long long newEnd = topmost.first;
                newEnd += (e - s);
                
                /* Mark the room as engaged */
                engaged.push({newEnd, topmost.second});
            }
        }
        
        /* Find the lowest room_number with maximum frequency */
        int maxi = 0;
        for(int i = 1; i < n; i++) {
            if(freq[i] > freq[maxi])
                maxi = i;
        }
        return maxi;
    }
    int mostBooked(int n, vector<vector<int>>& meetings) {

        // return book(n, meetings);

        sort(meetings.begin(), meetings.end());

        vector<int> used(n, 0);
        priority_queue<int, vector<int>, greater<int>> rooms;
        // priority_queue<PII, vector<PII>, greater<PII>> endTimes;
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> endTimes;

        for(int i=0;i<n;i++){
            rooms.push(i);
        }

        int i=0;
        int ans =0;
        int end =0;
        int start_ =0;
        for(auto &x : meetings){
            int start = x[0];
            int finish = x[1];
            // find a free room
            // start_= max(start, start_);
            // traverse and end all meetings finished by time start
            while(!endTimes.empty() && endTimes.top().first <= start){
                PII top = endTimes.top();
                endTimes.pop();
                rooms.push(top.second);
                // if(top.first <= start){
                //     endTimes.pop();
                //     rooms.push(top.second);
                // }
            }
            int freeRoom =0;
                // endTimes.push(make_pair(finish, freeRoom));
            if(rooms.size()>0){
                freeRoom = rooms.top();
                rooms.pop();
                cout<<endTimes.size();
                endTimes.push({finish, freeRoom});
                used[freeRoom]++;
                
            }
            else if(!endTimes.empty()){
            // else{
                // finish a meeting which is closest
                PII top = endTimes.top();
                endTimes.pop();
                rooms.push(top.second);
                freeRoom = rooms.top();
                used[freeRoom]++;
                rooms.pop();
                endTimes.push({top.first + finish -start, freeRoom});
            }
            cout<<"Out of While Loop";
            // used[freeRoom]++;
            i++;
        }
        ans = 0;
        for(int i=1; i<n; i++){
            if(used[ans] < used[i])
                ans =i;
        }
        return ans;
    }
};
```

## Attempt 4 · 2023-05-05 15:16 IST · Runtime Error · C++

[submission 944875062](https://leetcode.com/submissions/detail/944875062/) · tests 72/82

Failing input:

```text
10
[[1,300001],[2,300002],[3,300003],[4,300004],[5,300005],[6,300006],[7,300007],[8,300008],[9,300009],[10,300010],[11,300011],[12,300012],[13,300013],[14,300014],[15,300015],[16,300016],[17,300017],[18,300018],[19,300019],[20,300020],[21,300021],[22,300022],[23,300023],[24,300024],[25,300025],[26,300026],[27,300027],[28,300028],[29,300029],[30,300030],[31,300031],[32,300032],[33,300033],[34,30003 ... [1188653 more chars]
```

Expected:

```text
1
```

Runtime error:

```text
Line 105: Char 35: runtime error: signed integer overflow: 2147400001 + 300000 cannot be represented in type 'int' (solution.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:114:35
```

```cpp
class Solution {
    typedef pair<int,int> PII;
public:
    int book(int n, vector<vector<int>>& meetings){
        sort(meetings.begin(), meetings.end());
        
        /* Create a priority queue for engaged rooms. Each node of PQ will store {current_meeting_ending_time, room_number} */
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> engaged;
        
        /* Create a priority queue for non-engaged rooms. Each node of PQ will store {room_number} */
        priority_queue<int, vector<int>, greater<int>> unused;
        
        /* Frequency map to store the frequency of meetings in each room */
        unordered_map<int, int> freq;
        
        /* Currently all the rooms are mepty */
        for(int i = 0; i < n; i++) {
            unused.push(i);
        }
        
        for(auto x:meetings) {
            int s = x[0], e = x[1];
            
            /* Move the meeting rooms in engaged, with ending_time <= s, to unused */ 
            while(engaged.size() > 0 && engaged.top().first <= s) {
                int room = engaged.top().second;
                engaged.pop();
                
                unused.push(room);
            }
            
            /* If there are multiple empty rooms, choose the one with lower room_number */
            if(unused.size() > 0) 
            {
                int room = unused.top();
                unused.pop();
                
                freq[abs(room)] += 1;
                
                /* Mark the room as engaged */
                engaged.push({e, room});
            }
            /* If there are no empty rooms, wait for the engaged room with nearest ending time to empty */
            else 
            {
                pair<long long, int> topmost = engaged.top();
                engaged.pop();
            
                freq[abs(topmost.second)] += 1;
                
                /* Since duration has to be the same, the newEnd will be sum(end_time_of_the_prev_meeting, duration) */ 
                long long newEnd = topmost.first;
                newEnd += (e - s);
                
                /* Mark the room as engaged */
                engaged.push({newEnd, topmost.second});
            }
        }
        
        /* Find the lowest room_number with maximum frequency */
        int maxi = 0;
        for(int i = 1; i < n; i++) {
            if(freq[i] > freq[maxi])
                maxi = i;
        }
        return maxi;
    }
    int mostBooked(int n, vector<vector<int>>& meetings) {

        // return book(n, meetings);

        sort(meetings.begin(), meetings.end());

        vector<int> used(n, 0);
        priority_queue<int, vector<int>, greater<int>> pqRooms;
        priority_queue<PII, vector<PII>, greater<PII>> pq;
        // priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> endTimes;
        vector<int> meetingsHeld(n+1,0);
        for(int i=0;i<n;i++){
            pqRooms.push(i);
        }
        // pq.push({meetings[0][1], 0});
        // meetingsHeld[0]++;

        for(int i=0;i<meetings.size();i++){
            int start = meetings[i][0];
            int end = meetings[i][1];

            // finish meetings before this time
            while(!pq.empty() && start >= pq.top().first){
                int room = pq.top().second;
                pq.pop();
                pqRooms.push(room);
            }
            if(!pqRooms.empty()){
                int room = pqRooms.top();
                pqRooms.pop();
                pq.push({end, room});
                meetingsHeld[room]++;
            }
            else{
                auto it = pq.top(); pq.pop();

                meetingsHeld[it.second]++;
                pq.push({it.first + (end-start), it.second});
                
            }
            
        }

        int maxi =0, ans =0;
        for(int i=0;i<n;i++){
            if(maxi < meetingsHeld[i]){
                maxi = meetingsHeld[i];
                ans = i;
            }
        }
        return ans;
    }
};
```

## Attempt 5 · 2023-05-05 15:17 IST · Accepted · C++

[submission 944875573](https://leetcode.com/submissions/detail/944875573/) · tests 82/82 · runtime 568 ms (beats 5.0%)

```cpp
class Solution {
    typedef pair<long long,int> PII;
public:
    int book(int n, vector<vector<int>>& meetings){
        sort(meetings.begin(), meetings.end());
        
        /* Create a priority queue for engaged rooms. Each node of PQ will store {current_meeting_ending_time, room_number} */
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> engaged;
        
        /* Create a priority queue for non-engaged rooms. Each node of PQ will store {room_number} */
        priority_queue<int, vector<int>, greater<int>> unused;
        
        /* Frequency map to store the frequency of meetings in each room */
        unordered_map<int, int> freq;
        
        /* Currently all the rooms are mepty */
        for(int i = 0; i < n; i++) {
            unused.push(i);
        }
        
        for(auto x:meetings) {
            int s = x[0], e = x[1];
            
            /* Move the meeting rooms in engaged, with ending_time <= s, to unused */ 
            while(engaged.size() > 0 && engaged.top().first <= s) {
                int room = engaged.top().second;
                engaged.pop();
                
                unused.push(room);
            }
            
            /* If there are multiple empty rooms, choose the one with lower room_number */
            if(unused.size() > 0) 
            {
                int room = unused.top();
                unused.pop();
                
                freq[abs(room)] += 1;
                
                /* Mark the room as engaged */
                engaged.push({e, room});
            }
            /* If there are no empty rooms, wait for the engaged room with nearest ending time to empty */
            else 
            {
                pair<long long, int> topmost = engaged.top();
                engaged.pop();
            
                freq[abs(topmost.second)] += 1;
                
                /* Since duration has to be the same, the newEnd will be sum(end_time_of_the_prev_meeting, duration) */ 
                long long newEnd = topmost.first;
                newEnd += (e - s);
                
                /* Mark the room as engaged */
                engaged.push({newEnd, topmost.second});
            }
        }
        
        /* Find the lowest room_number with maximum frequency */
        int maxi = 0;
        for(int i = 1; i < n; i++) {
            if(freq[i] > freq[maxi])
                maxi = i;
        }
        return maxi;
    }
    int mostBooked(int n, vector<vector<int>>& meetings) {

        // return book(n, meetings);

        sort(meetings.begin(), meetings.end());

        vector<int> used(n, 0);
        priority_queue<int, vector<int>, greater<int>> pqRooms;
        priority_queue<PII, vector<PII>, greater<PII>> pq;
        // priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> endTimes;
        vector<int> meetingsHeld(n+1,0);
        for(int i=0;i<n;i++){
            pqRooms.push(i);
        }
        // pq.push({meetings[0][1], 0});
        // meetingsHeld[0]++;

        for(int i=0;i<meetings.size();i++){
            int start = meetings[i][0];
            int end = meetings[i][1];

            // finish meetings before this time
            while(!pq.empty() && start >= pq.top().first){
                int room = pq.top().second;
                pq.pop();
                pqRooms.push(room);
            }
            if(!pqRooms.empty()){
                int room = pqRooms.top();
                pqRooms.pop();
                pq.push({end, room});
                meetingsHeld[room]++;
            }
            else{
                auto it = pq.top(); pq.pop();

                meetingsHeld[it.second]++;
                pq.push({it.first + (end-start), it.second});
                
            }
            
        }

        int maxi =0, ans =0;
        for(int i=0;i<n;i++){
            if(maxi < meetingsHeld[i]){
                maxi = meetingsHeld[i];
                ans = i;
            }
        }
        return ans;
    }
};
```

## Attempt 6 · 2023-05-05 15:26 IST · Accepted · C++

[submission 944879115](https://leetcode.com/submissions/detail/944879115/) · tests 82/82 · runtime 585 ms (beats 5.0%)

```cpp
class Solution {
    typedef pair<long long,int> PII;
public:
    int book(int n, vector<vector<int>>& meetings){
        sort(meetings.begin(), meetings.end());
        
        /* Create a priority queue for engaged rooms. Each node of PQ will store {current_meeting_ending_time, room_number} */
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> engaged;
        
        /* Create a priority queue for non-engaged rooms. Each node of PQ will store {room_number} */
        priority_queue<int, vector<int>, greater<int>> unused;
        
        /* Frequency map to store the frequency of meetings in each room */
        unordered_map<int, int> freq;
        
        /* Currently all the rooms are mepty */
        for(int i = 0; i < n; i++) {
            unused.push(i);
        }
        
        for(auto x:meetings) {
            int s = x[0], e = x[1];
            
            /* Move the meeting rooms in engaged, with ending_time <= s, to unused */ 
            while(engaged.size() > 0 && engaged.top().first <= s) {
                int room = engaged.top().second;
                engaged.pop();
                
                unused.push(room);
            }
            
            /* If there are multiple empty rooms, choose the one with lower room_number */
            if(unused.size() > 0) 
            {
                int room = unused.top();
                unused.pop();
                
                freq[abs(room)] += 1;
                
                /* Mark the room as engaged */
                engaged.push({e, room});
            }
            /* If there are no empty rooms, wait for the engaged room with nearest ending time to empty */
            else 
            {
                pair<long long, int> topmost = engaged.top();
                engaged.pop();
            
                freq[abs(topmost.second)] += 1;
                
                /* Since duration has to be the same, the newEnd will be sum(end_time_of_the_prev_meeting, duration) */ 
                long long newEnd = topmost.first;
                newEnd += (e - s);
                
                /* Mark the room as engaged */
                engaged.push({newEnd, topmost.second});
            }
        }
        
        /* Find the lowest room_number with maximum frequency */
        int maxi = 0;
        for(int i = 1; i < n; i++) {
            if(freq[i] > freq[maxi])
                maxi = i;
        }
        return maxi;
    }
    int mostBooked(int n, vector<vector<int>>& meetings) {

        // return book(n, meetings);

        sort(meetings.begin(), meetings.end());

        vector<int> used(n, 0);
        priority_queue<int, vector<int>, greater<int>> pqRooms;
        priority_queue<PII, vector<PII>, greater<PII>> pq;
        // priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> endTimes;
        vector<int> meetingsHeld(n+1,0);
        for(int i=1;i<n;i++){
            pqRooms.push(i);
        }
        pq.push({meetings[0][1], 0});
        meetingsHeld[0]++;

        for(int i=1;i<meetings.size();i++){
            int start = meetings[i][0];
            int end = meetings[i][1];

            // finish meetings before this time
            while(!pq.empty() && start >= pq.top().first){
                int room = pq.top().second;
                pq.pop();
                pqRooms.push(room);
            }
            if(!pqRooms.empty()){
                int room = pqRooms.top();
                pqRooms.pop();
                pq.push({end, room});
                meetingsHeld[room]++;
            }
            else{
                auto it = pq.top(); pq.pop();

                meetingsHeld[it.second]++;
                pq.push({it.first + (end-start), it.second});
                
            }
            
        }

        int maxi =0, ans =0;
        for(int i=0;i<n;i++){
            if(maxi < meetingsHeld[i]){
                maxi = meetingsHeld[i];
                ans = i;
            }
        }
        return ans;
    }
};
```

## Attempt 7 · 2023-05-05 15:26 IST · Accepted · C++

[submission 944879357](https://leetcode.com/submissions/detail/944879357/) · tests 82/82 · runtime 559 ms (beats 5.0%)

```cpp
class Solution {
    typedef pair<long long,int> PII;
public:
    int book(int n, vector<vector<int>>& meetings){
        sort(meetings.begin(), meetings.end());
        
        /* Create a priority queue for engaged rooms. Each node of PQ will store {current_meeting_ending_time, room_number} */
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> engaged;
        
        /* Create a priority queue for non-engaged rooms. Each node of PQ will store {room_number} */
        priority_queue<int, vector<int>, greater<int>> unused;
        
        /* Frequency map to store the frequency of meetings in each room */
        unordered_map<int, int> freq;
        
        /* Currently all the rooms are mepty */
        for(int i = 0; i < n; i++) {
            unused.push(i);
        }
        
        for(auto x:meetings) {
            int s = x[0], e = x[1];
            
            /* Move the meeting rooms in engaged, with ending_time <= s, to unused */ 
            while(engaged.size() > 0 && engaged.top().first <= s) {
                int room = engaged.top().second;
                engaged.pop();
                
                unused.push(room);
            }
            
            /* If there are multiple empty rooms, choose the one with lower room_number */
            if(unused.size() > 0) 
            {
                int room = unused.top();
                unused.pop();
                
                freq[abs(room)] += 1;
                
                /* Mark the room as engaged */
                engaged.push({e, room});
            }
            /* If there are no empty rooms, wait for the engaged room with nearest ending time to empty */
            else 
            {
                pair<long long, int> topmost = engaged.top();
                engaged.pop();
            
                freq[abs(topmost.second)] += 1;
                
                /* Since duration has to be the same, the newEnd will be sum(end_time_of_the_prev_meeting, duration) */ 
                long long newEnd = topmost.first;
                newEnd += (e - s);
                
                /* Mark the room as engaged */
                engaged.push({newEnd, topmost.second});
            }
        }
        
        /* Find the lowest room_number with maximum frequency */
        int maxi = 0;
        for(int i = 1; i < n; i++) {
            if(freq[i] > freq[maxi])
                maxi = i;
        }
        return maxi;
    }
    int mostBooked(int n, vector<vector<int>>& meetings) {

        // return book(n, meetings);

        sort(meetings.begin(), meetings.end());

        vector<int> used(n, 0);
        priority_queue<int, vector<int>, greater<int>> pqRooms;
        priority_queue<PII, vector<PII>, greater<PII>> pq; // {LL,int}
        vector<int> meetingsHeld(n+1,0);
        for(int i=1;i<n;i++){
            pqRooms.push(i);
        }
        pq.push({meetings[0][1], 0});
        meetingsHeld[0]++;

        for(int i=1;i<meetings.size();i++){
            int start = meetings[i][0];
            int end = meetings[i][1];

            // finish meetings before this time
            while(!pq.empty() && start >= pq.top().first){
                int room = pq.top().second;
                pq.pop();
                pqRooms.push(room);
            }
            if(!pqRooms.empty()){
                int room = pqRooms.top();
                pqRooms.pop();
                pq.push({end, room});
                meetingsHeld[room]++;
            }
            else{
                auto it = pq.top(); pq.pop();

                meetingsHeld[it.second]++;
                pq.push({it.first + (end-start), it.second});
                
            }
            
        }

        int maxi =0, ans =0;
        for(int i=0;i<n;i++){
            if(maxi < meetingsHeld[i]){
                maxi = meetingsHeld[i];
                ans = i;
            }
        }
        return ans;
    }
};
```
