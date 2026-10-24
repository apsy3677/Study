# 253. Meeting Rooms II

[Problem](https://leetcode.com/problems/meeting-rooms-ii/) · Medium · Intervals & Sweep Line → Min-heap of end times

LeetCode tags: array, two-pointers, greedy, sorting, heap-priority-queue, prefix-sum

Attempts since Mar 2023: 19 · accepted: 13 · failed before first AC: 4

## Attempt 1 · 2023-03-22 00:51 IST · Wrong Answer · C++

[submission 919711707](https://leetcode.com/submissions/detail/919711707/) · tests 35/78

Failing input:

```text
[[2,7]]
```

Expected:

```text
1
```

Your output:

```text
0
```

```cpp
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<int> start(n), end(n);

        for(int i=0;i<n;i++){
            start[i] = intervals[i][0];
            end[i] = intervals[i][1];
        }

        sort(start.begin(), start.end());
        sort(end.begin(), end.end());

        int i=0, j=0, ans =0, rooms=0;

        while(i<n){
            rooms++;
            if(start[i] > end[j]){
                
                
                rooms--;
                ans = max(ans, rooms);
                j++;
            }
            i++;
            
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-03-22 00:51 IST · Wrong Answer · C++

[submission 919711890](https://leetcode.com/submissions/detail/919711890/) · tests 35/78

Failing input:

```text
[[2,7]]
```

Expected:

```text
1
```

Your output:

```text
0
```

```cpp
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<int> start(n), end(n);

        for(int i=0;i<n;i++){
            start[i] = intervals[i][0];
            end[i] = intervals[i][1];
        }

        sort(start.begin(), start.end());
        sort(end.begin(), end.end());

        int i=0, j=0, ans =0, rooms=0;

        while(i<n){
            rooms++;
            while(start[i] > end[j]){
                
                
                rooms--;
                ans = max(ans, rooms);
                j++;
            }
            i++;
            
        }
        return ans;
    }
};
```

## Attempt 3 · 2023-03-22 00:52 IST · Wrong Answer · C++

[submission 919712264](https://leetcode.com/submissions/detail/919712264/) · tests 42/78

Failing input:

```text
[[5,8],[6,8]]
```

Expected:

```text
2
```

Your output:

```text
1
```

```cpp
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<int> start(n), end(n);

        for(int i=0;i<n;i++){
            start[i] = intervals[i][0];
            end[i] = intervals[i][1];
        }

        sort(start.begin(), start.end());
        sort(end.begin(), end.end());

        int i=0, j=0, ans =1, rooms=0;

        while(i<n){
            rooms++;
            while(start[i] > end[j]){
                
                
                rooms--;
                ans = max(ans, rooms);
                j++;
            }
            i++;
            
        }
        return ans;
    }
};
```

## Attempt 4 · 2023-03-22 00:53 IST · Wrong Answer · C++

[submission 919712810](https://leetcode.com/submissions/detail/919712810/) · tests 65/78

Failing input:

```text
[[13,15],[1,13]]
```

Expected:

```text
1
```

Your output:

```text
2
```

```cpp
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<int> start(n), end(n);

        for(int i=0;i<n;i++){
            start[i] = intervals[i][0];
            end[i] = intervals[i][1];
        }

        sort(start.begin(), start.end());
        sort(end.begin(), end.end());

        int i=0, j=0, ans =1, rooms=0;

        while(i<n){
            rooms++;
            while(start[i] > end[j]){
                
                
                rooms--;
                
                j++;
            }
            ans = max(ans, rooms);
            i++;
            
        }
        return ans;
    }
};
```

## Attempt 5 · 2023-03-22 00:53 IST · Accepted · C++

[submission 919713087](https://leetcode.com/submissions/detail/919713087/) · tests 78/78 · runtime 18 ms (beats 6.8%)

```cpp
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<int> start(n), end(n);

        for(int i=0;i<n;i++){
            start[i] = intervals[i][0];
            end[i] = intervals[i][1];
        }

        sort(start.begin(), start.end());
        sort(end.begin(), end.end());

        int i=0, j=0, ans =1, rooms=0;

        while(i<n){
            rooms++;
            while(start[i] >= end[j]){
                
                
                rooms--;
                
                j++;
            }
            ans = max(ans, rooms);
            i++;
            
        }
        return ans;
    }
};
```

## Attempt 6 · 2023-03-22 01:00 IST · Accepted · C++

[submission 919716470](https://leetcode.com/submissions/detail/919716470/) · tests 78/78 · runtime 10 ms (beats 10.6%)

```cpp
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<int> start(n), end(n);

        for(int i=0;i<n;i++){
            start[i] = intervals[i][0];
            end[i] = intervals[i][1];
        }

        sort(start.begin(), start.end());
        sort(end.begin(), end.end());

        int i=0, j=0, ans =1, rooms=0, used=0;

        while(i<n){
            
            if(start[i] >= end[j]){
                used--;
                j++;
            }
            used++;
            // ans = max(ans, rooms);
            i++;
            
        }
        return used;
    }
};
```

## Attempt 7 · 2023-03-22 01:01 IST · Accepted · C++

[submission 919716679](https://leetcode.com/submissions/detail/919716679/) · tests 78/78 · runtime 15 ms (beats 7.5%)

```cpp
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<int> start(n), end(n);

        for(int i=0;i<n;i++){
            start[i] = intervals[i][0];
            end[i] = intervals[i][1];
        }

        sort(start.begin(), start.end());
        sort(end.begin(), end.end());

        int i=0, j=0, ans =1, rooms=0, used=0;

        while(i<n){
            used++;
            if(start[i] >= end[j]){
                used--;
                j++;
            }
            
            // ans = max(ans, rooms);
            i++;
            
        }
        return used;
    }
};
```

## Attempt 8 · 2023-03-22 22:08 IST · Accepted · C++

[submission 920229186](https://leetcode.com/submissions/detail/920229186/) · tests 78/78 · runtime 11 ms (beats 9.8%)

```cpp
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<int> start(n), end(n);

        for(int i=0;i<n;i++){
            start[i] = intervals[i][0];
            end[i] = intervals[i][1];
        }

        sort(start.begin(), start.end());
        sort(end.begin(), end.end());

        int i=0, j=0, ans =1, rooms=0, used=0;

        while(i<n){
            used++;
            if(start[i] >= end[j]){
                used--;
                j++;
            }
            
            // ans = max(ans, rooms);
            i++;
            
        }
        return used;
    }
};
```

## Attempt 9 · 2023-05-05 14:43 IST · Accepted · C++

[submission 944860535](https://leetcode.com/submissions/detail/944860535/) · tests 78/78 · runtime 22 ms (beats 6.6%)

```cpp
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if(intervals.size()==0) return 0;
        priority_queue<int, vector<int>, greater<int> > pq;

        sort(intervals.begin(), intervals.end(), 
            [](vector<int> &a, vector<int> &b){
                return a[0]<b[0];
        });

        pq.push(intervals[0][1]);
        int rooms = pq.size();
        for(int i=1;i<intervals.size();i++){
            int end = pq.top();
            if(intervals[i][0] >= end){
                pq.pop();
            }
            pq.push(intervals[i][1]);
        }
        return pq.size();
    }
    int minMeetingRoomsUsingEndTime(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<int> start(n), end(n);

        for(int i=0;i<n;i++){
            start[i] = intervals[i][0];
            end[i] = intervals[i][1];
        }

        sort(start.begin(), start.end());
        sort(end.begin(), end.end());

        int i=0, j=0, ans =1, rooms=0, used=0;

        while(i<n){
            used++;
            if(start[i] >= end[j]){
                used--;
                j++;
            }
            
            // ans = max(ans, rooms);
            i++;
            
        }
        return used;
    }
};
```

## Attempt 10 · 2023-11-28 07:04 IST · Wrong Answer · Python3

[submission 1107813825](https://leetcode.com/submissions/detail/1107813825/) · tests 65/78

Failing input:

```text
[[13,15],[1,13]]
```

Expected:

```text
1
```

Your output:

```text
2
```

```python
class Solution:
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        if not intervals:
            return 0
        
        free_rooms= []

        intervals.sort()

        for interval in intervals:
            if free_rooms and free_rooms[0] < interval[0]:
                heapq.heappop(free_rooms)
            heapq.heappush(free_rooms, interval[1])
        return len(free_rooms)
```

## Attempt 11 · 2023-11-28 07:04 IST · Accepted · Python3

[submission 1107813904](https://leetcode.com/submissions/detail/1107813904/) · tests 78/78 · runtime 82 ms (beats 6.7%)

```python
class Solution:
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        if not intervals:
            return 0
        
        free_rooms= []

        intervals.sort()

        for interval in intervals:
            if free_rooms and free_rooms[0] <= interval[0]:
                heapq.heappop(free_rooms)
            heapq.heappush(free_rooms, interval[1])
        return len(free_rooms)
```

## Attempt 12 · 2024-01-23 06:11 IST · Accepted · Python3

[submission 1154103319](https://leetcode.com/submissions/detail/1154103319/) · tests 79/79 · runtime 89 ms (beats 6.7%)

```python
class Solution:
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        if not intervals:
            return 0
        
        free_rooms= []

        intervals.sort()

        for interval in intervals:
            if free_rooms and free_rooms[0] <= interval[0]:
                heapq.heappop(free_rooms)
            heapq.heappush(free_rooms, interval[1])
        return len(free_rooms)


    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort(key = lambda x: x[0])
        rooms = []
        for interval in intervals:
            if rooms[0] <=interval[0]:
                heapq.heapop(rooms)

            heapq.heappush(rooms, interval[1])

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        if not intervals:
            return 0

        used_rooms = 0

        starting_times = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)

        end_pointer = 0
        start_pointer = 0

        while start_pointer < L:
            if starting_times[start_pointer] >= end_timings[end_pointer]:
                used_rooms -=1
                end_pointer +=1
            start_pointer+=1
            used_rooms +=1

        return used_rooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()
        free_rooms = [] # keep end time
        for interval in intervals:
            # if no conflict - allocate this room
            if free_rooms and free_rooms[0] <= interval[0]:
                heapq.heappop(free_rooms)
            # insert interval
            heapq.heappush(free_rooms, interval[1])
        return len(free_rooms)

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()

        start_timings = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)

        start_pointer = 0
        end_pointer = 0
        used_rooms = 0
        
        while start_pointer < L:
            # if no overlap or conflic
            if start_timings[start_pointer] >= end_timings[end_pointer]:
                used_rooms -=1
                end_pointer +=1

            # iterate new interval
            start_pointer +=1
            used_rooms +=1

        return used_rooms
            
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()
        rooms = []
        maxRooms = 0
        for interval in intervals:
            # find rooms 
            rooms = [room for room in rooms if interval[0] < room]
            
            # add to rooms
            rooms.append((interval[1]))
            # print(interval, rooms)
            maxRooms = max(len(rooms), maxRooms)

        return maxRooms
```

## Attempt 13 · 2024-01-23 06:20 IST · Accepted · Python3

[submission 1154107750](https://leetcode.com/submissions/detail/1154107750/) · tests 79/79 · runtime 71 ms (beats 6.7%)

```python
class Solution:
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        if not intervals:
            return 0
        
        free_rooms= []

        intervals.sort()

        for interval in intervals:
            if free_rooms and free_rooms[0] <= interval[0]:
                heapq.heappop(free_rooms)
            heapq.heappush(free_rooms, interval[1])
        return len(free_rooms)


    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort(key = lambda x: x[0])
        rooms = []
        for interval in intervals:
            if rooms[0] <=interval[0]:
                heapq.heapop(rooms)

            heapq.heappush(rooms, interval[1])

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        if not intervals:
            return 0

        used_rooms = 0

        starting_times = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)

        end_pointer = 0
        start_pointer = 0

        while start_pointer < L:
            if starting_times[start_pointer] >= end_timings[end_pointer]:
                used_rooms -=1
                end_pointer +=1
            start_pointer+=1
            used_rooms +=1

        return used_rooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()
        free_rooms = [] # keep end time
        for interval in intervals:
            # if no conflict - allocate this room
            if free_rooms and free_rooms[0] <= interval[0]:
                heapq.heappop(free_rooms)
            # insert interval
            heapq.heappush(free_rooms, interval[1])
        return len(free_rooms)

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()

        start_timings = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)

        start_pointer = 0
        end_pointer = 0
        used_rooms = 0
        
        while start_pointer < L:
            # if no overlap or conflic
            if start_timings[start_pointer] >= end_timings[end_pointer]:
                used_rooms -=1
                end_pointer +=1

            # iterate new interval
            start_pointer +=1
            used_rooms +=1

        return used_rooms
            
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()
        rooms = []
        maxRooms = 0
        for interval in intervals:
            # remove meetings that have ended before this meeting
            rooms = [room for room in rooms if interval[0] < room]
            
            # add to rooms
            rooms.append((interval[1]))
            # print(interval, rooms)
            maxRooms = max(len(rooms), maxRooms)

        return maxRooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()

        start_timings = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)

        start_pointer = 0
        end_pointer = 0
        used_rooms = 0
        maxRooms = 0
        while start_pointer < L:
            # if overlap
            if start_timings[start_pointer] < end_timings[end_pointer]:
                used_rooms +=1
                start_pointer +=1
            else:
                # no overlap
                end_pointer +=1
                used_rooms -=1
            maxRooms = max(maxRooms, used_rooms)
        
        return maxRooms

        return maxRooms
```

## Attempt 14 · 2024-01-30 00:29 IST · Accepted · Python3

[submission 1160366589](https://leetcode.com/submissions/detail/1160366589/) · tests 79/79 · runtime 74 ms (beats 6.7%)

```python
class Solution:
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        if not intervals:
            return 0
        
        free_rooms= []

        intervals.sort()

        for interval in intervals:
            if free_rooms and free_rooms[0] <= interval[0]:
                heapq.heappop(free_rooms)
            heapq.heappush(free_rooms, interval[1])
        return len(free_rooms)


    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort(key = lambda x: x[0])
        rooms = []
        for interval in intervals:
            if rooms[0] <=interval[0]:
                heapq.heapop(rooms)

            heapq.heappush(rooms, interval[1])

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        if not intervals:
            return 0

        used_rooms = 0

        starting_times = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)

        end_pointer = 0
        start_pointer = 0

        while start_pointer < L:
            if starting_times[start_pointer] >= end_timings[end_pointer]:
                used_rooms -=1
                end_pointer +=1
            start_pointer+=1
            used_rooms +=1

        return used_rooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()
        free_rooms = [] # keep end time
        for interval in intervals:
            # if no conflict - allocate this room
            if free_rooms and free_rooms[0] <= interval[0]:
                heapq.heappop(free_rooms)
            # insert interval
            heapq.heappush(free_rooms, interval[1])
        return len(free_rooms)

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()

        start_timings = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)

        start_pointer = 0
        end_pointer = 0
        used_rooms = 0
        
        while start_pointer < L:
            # if no overlap or conflic
            if start_timings[start_pointer] >= end_timings[end_pointer]:
                used_rooms -=1
                end_pointer +=1

            # iterate new interval
            start_pointer +=1
            used_rooms +=1

        return used_rooms
            
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()
        rooms = []
        maxRooms = 0
        for interval in intervals:
            # remove meetings that have ended before this meeting
            rooms = [room for room in rooms if interval[0] < room]
            
            # add to rooms
            rooms.append((interval[1]))
            # print(interval, rooms)
            maxRooms = max(len(rooms), maxRooms)

        return maxRooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()

        start_timings = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)
        print(start_timings, end_timings)
        start_pointer = 0
        end_pointer = 0
        used_rooms = 0
        maxRooms = 0
        while start_pointer < L:
            # if overlap
            if start_timings[start_pointer] < end_timings[end_pointer]:
                used_rooms +=1
                start_pointer +=1
            else:
                # no overlap
                end_pointer +=1
                used_rooms -=1
            print(start_pointer, end_pointer, used_rooms)
            maxRooms = max(maxRooms, used_rooms)
        
        return maxRooms

        return maxRooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        start_timings = sorted([interval[0] for interval in intervals])
        end_timings = sorted([interval[1] for interval in intervals])

        rooms = 0
        end_pointer = 0 
        start_pointer = 0
        while start_pointer < len(start_timings):
            if start_timings[start_pointer] >= end_timings[end_pointer]:
                rooms-=1
                end_pointer +=1

            rooms+=1
            start_pointer +=1
        return rooms
```

## Attempt 15 · 2024-02-06 23:20 IST · Accepted · Python3

[submission 1168041195](https://leetcode.com/submissions/detail/1168041195/) · tests 79/79 · runtime 70 ms (beats 6.7%)

```python
class Solution:
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        if not intervals:
            return 0
        
        free_rooms= []

        intervals.sort()

        for interval in intervals:
            if free_rooms and free_rooms[0] <= interval[0]:
                heapq.heappop(free_rooms)
            heapq.heappush(free_rooms, interval[1])
        return len(free_rooms)


    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort(key = lambda x: x[0])
        rooms = []
        for interval in intervals:
            if rooms[0] <=interval[0]:
                heapq.heapop(rooms)

            heapq.heappush(rooms, interval[1])

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        if not intervals:
            return 0

        used_rooms = 0

        starting_times = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)

        end_pointer = 0
        start_pointer = 0

        while start_pointer < L:
            if starting_times[start_pointer] >= end_timings[end_pointer]:
                used_rooms -=1
                end_pointer +=1
            start_pointer+=1
            used_rooms +=1

        return used_rooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()
        free_rooms = [] # keep end time
        for interval in intervals:
            # if no conflict - allocate this room
            if free_rooms and free_rooms[0] <= interval[0]:
                heapq.heappop(free_rooms)
            # insert interval
            heapq.heappush(free_rooms, interval[1])
        return len(free_rooms)

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()

        start_timings = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)

        start_pointer = 0
        end_pointer = 0
        used_rooms = 0
        
        while start_pointer < L:
            # if no overlap or conflic
            if start_timings[start_pointer] >= end_timings[end_pointer]:
                used_rooms -=1
                end_pointer +=1

            # iterate new interval
            start_pointer +=1
            used_rooms +=1

        return used_rooms
            
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()
        rooms = []
        maxRooms = 0
        for interval in intervals:
            # remove meetings that have ended before this meeting
            rooms = [room for room in rooms if interval[0] < room]
            
            # add to rooms
            rooms.append((interval[1]))
            # print(interval, rooms)
            maxRooms = max(len(rooms), maxRooms)

        return maxRooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()

        start_timings = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)
        print(start_timings, end_timings)
        start_pointer = 0
        end_pointer = 0
        used_rooms = 0
        maxRooms = 0
        while start_pointer < L:
            # if overlap
            if start_timings[start_pointer] < end_timings[end_pointer]:
                used_rooms +=1
                start_pointer +=1
            else:
                # no overlap
                end_pointer +=1
                used_rooms -=1
            print(start_pointer, end_pointer, used_rooms)
            maxRooms = max(maxRooms, used_rooms)
        
        return maxRooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()

        start_timings = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)
        print(start_timings, end_timings)
        start_pointer = 0
        end_pointer = 0
        used_rooms = 0
        maxRooms = 0
        while start_pointer < L:
            # if overlap
            if start_timings[start_pointer] >= end_timings[end_pointer]:
                used_rooms -=1
                end_pointer +=1

            start_pointer +=1
            used_rooms +=1
            print(start_pointer, end_pointer, used_rooms)
            maxRooms = max(maxRooms, used_rooms)
        
        return maxRooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        start_timings = sorted([interval[0] for interval in intervals])
        end_timings = sorted([interval[1] for interval in intervals])

        rooms = 0
        end_pointer = 0 
        start_pointer = 0
        while start_pointer < len(start_timings):
            if start_timings[start_pointer] >= end_timings[end_pointer]:
                rooms-=1
                end_pointer +=1
            
            rooms+=1
            print(rooms)
            start_pointer +=1
        return rooms

    def minMeetingRooms3(self, intervals: List[List[int]]) -> int:
        rooms = []
        intervals.sort()

        for interval in intervals:
            while rooms and interval[0] >= rooms[0]:
                print('popping interval', rooms[0])
                heapq.heappop(rooms)
            
            heapq.heappush(rooms, interval[1])
            print(rooms)

        return len(rooms)
```

## Attempt 16 · 2024-02-06 23:20 IST · Wrong Answer · Python3

[submission 1168041343](https://leetcode.com/submissions/detail/1168041343/) · tests 57/79

Failing input:

```text
[[13,15],[1,13],[6,9]]
```

Expected:

```text
2
```

Your output:

```text
1
```

```python
class Solution:
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        if not intervals:
            return 0
        
        free_rooms= []

        intervals.sort()

        for interval in intervals:
            if free_rooms and free_rooms[0] <= interval[0]:
                heapq.heappop(free_rooms)
            heapq.heappush(free_rooms, interval[1])
        return len(free_rooms)


    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort(key = lambda x: x[0])
        rooms = []
        for interval in intervals:
            if rooms[0] <=interval[0]:
                heapq.heapop(rooms)

            heapq.heappush(rooms, interval[1])

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        if not intervals:
            return 0

        used_rooms = 0

        starting_times = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)

        end_pointer = 0
        start_pointer = 0

        while start_pointer < L:
            if starting_times[start_pointer] >= end_timings[end_pointer]:
                used_rooms -=1
                end_pointer +=1
            start_pointer+=1
            used_rooms +=1

        return used_rooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()
        free_rooms = [] # keep end time
        for interval in intervals:
            # if no conflict - allocate this room
            if free_rooms and free_rooms[0] <= interval[0]:
                heapq.heappop(free_rooms)
            # insert interval
            heapq.heappush(free_rooms, interval[1])
        return len(free_rooms)

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()

        start_timings = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)

        start_pointer = 0
        end_pointer = 0
        used_rooms = 0
        
        while start_pointer < L:
            # if no overlap or conflic
            if start_timings[start_pointer] >= end_timings[end_pointer]:
                used_rooms -=1
                end_pointer +=1

            # iterate new interval
            start_pointer +=1
            used_rooms +=1

        return used_rooms
            
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()
        rooms = []
        maxRooms = 0
        for interval in intervals:
            # remove meetings that have ended before this meeting
            rooms = [room for room in rooms if interval[0] < room]
            
            # add to rooms
            rooms.append((interval[1]))
            # print(interval, rooms)
            maxRooms = max(len(rooms), maxRooms)

        return maxRooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()

        start_timings = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)
        print(start_timings, end_timings)
        start_pointer = 0
        end_pointer = 0
        used_rooms = 0
        maxRooms = 0
        while start_pointer < L:
            # if overlap
            if start_timings[start_pointer] < end_timings[end_pointer]:
                used_rooms +=1
                start_pointer +=1
            else:
                # no overlap
                end_pointer +=1
                used_rooms -=1
            print(start_pointer, end_pointer, used_rooms)
            maxRooms = max(maxRooms, used_rooms)
        
        return maxRooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()

        start_timings = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)
        print(start_timings, end_timings)
        start_pointer = 0
        end_pointer = 0
        used_rooms = 0
        maxRooms = 0
        while start_pointer < L:
            # if overlap
            if start_timings[start_pointer] >= end_timings[end_pointer]:
                used_rooms -=1
                end_pointer +=1

            start_pointer +=1
            used_rooms +=1
            print(start_pointer, end_pointer, used_rooms)
            maxRooms = max(maxRooms, used_rooms)
        
        return maxRooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        start_timings = sorted([interval[0] for interval in intervals])
        end_timings = sorted([interval[1] for interval in intervals])

        rooms = 0
        end_pointer = 0 
        start_pointer = 0
        while start_pointer < len(start_timings):
            if start_timings[start_pointer] >= end_timings[end_pointer]:
                rooms-=1
                end_pointer +=1
            
            rooms+=1
            print(rooms)
            start_pointer +=1
        return rooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        rooms = []
        intervals.sort()

        for interval in intervals:
            while rooms and interval[0] >= rooms[0]:
                print('popping interval', rooms[0])
                heapq.heappop(rooms)
            
            heapq.heappush(rooms, interval[1])
            print(rooms)

        return len(rooms)
```

## Attempt 17 · 2024-02-06 23:32 IST · Accepted · Python3

[submission 1168053663](https://leetcode.com/submissions/detail/1168053663/) · tests 79/79 · runtime 79 ms (beats 6.7%)

```python
class Solution:
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        if not intervals:
            return 0
        
        free_rooms= []

        intervals.sort()

        for interval in intervals:
            if free_rooms and free_rooms[0] <= interval[0]:
                heapq.heappop(free_rooms)
            heapq.heappush(free_rooms, interval[1])
        return len(free_rooms)


    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort(key = lambda x: x[0])
        rooms = []
        for interval in intervals:
            if rooms[0] <=interval[0]:
                heapq.heapop(rooms)

            heapq.heappush(rooms, interval[1])

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        if not intervals:
            return 0

        used_rooms = 0

        starting_times = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)

        end_pointer = 0
        start_pointer = 0

        while start_pointer < L:
            if starting_times[start_pointer] >= end_timings[end_pointer]:
                used_rooms -=1
                end_pointer +=1
            start_pointer+=1
            used_rooms +=1

        return used_rooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()
        free_rooms = [] # keep end time
        for interval in intervals:
            # if no conflict - allocate this room
            if free_rooms and free_rooms[0] <= interval[0]:
                heapq.heappop(free_rooms)
            # insert interval
            heapq.heappush(free_rooms, interval[1])
        return len(free_rooms)

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()

        start_timings = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)

        start_pointer = 0
        end_pointer = 0
        used_rooms = 0
        
        while start_pointer < L:
            # if no overlap or conflic
            if start_timings[start_pointer] >= end_timings[end_pointer]:
                used_rooms -=1
                end_pointer +=1

            # iterate new interval
            start_pointer +=1
            used_rooms +=1

        return used_rooms
            
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()
        rooms = []
        maxRooms = 0
        for interval in intervals:
            # remove meetings that have ended before this meeting
            rooms = [room for room in rooms if interval[0] < room]
            
            # add to rooms
            rooms.append((interval[1]))
            # print(interval, rooms)
            maxRooms = max(len(rooms), maxRooms)

        return maxRooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()

        start_timings = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)
        print(start_timings, end_timings)
        start_pointer = 0
        end_pointer = 0
        used_rooms = 0
        maxRooms = 0
        while start_pointer < L:
            # if overlap
            if start_timings[start_pointer] < end_timings[end_pointer]:
                used_rooms +=1
                start_pointer +=1
            else:
                # no overlap
                end_pointer +=1
                used_rooms -=1
            print(start_pointer, end_pointer, used_rooms)
            maxRooms = max(maxRooms, used_rooms)
        
        return maxRooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()

        start_timings = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)
        print(start_timings, end_timings)
        start_pointer = 0
        end_pointer = 0
        used_rooms = 0
        maxRooms = 0
        while start_pointer < L:
            # if overlap
            if start_timings[start_pointer] >= end_timings[end_pointer]:
                used_rooms -=1
                end_pointer +=1

            start_pointer +=1
            used_rooms +=1
            print(start_pointer, end_pointer, used_rooms)
            maxRooms = max(maxRooms, used_rooms)
        
        return maxRooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        start_timings = sorted([interval[0] for interval in intervals])
        end_timings = sorted([interval[1] for interval in intervals])

        rooms = 0
        end_pointer = 0 
        start_pointer = 0
        while start_pointer < len(start_timings):
            if start_timings[start_pointer] >= end_timings[end_pointer]:
                rooms-=1
                end_pointer +=1
            
            rooms+=1
            print(rooms)
            start_pointer +=1
        return rooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        rooms = []
        intervals.sort()

        for interval in intervals:
            # 
            print('popping interval', rooms)
            while rooms and interval[0] >= rooms[0]:
                heapq.heappop(rooms)
            
            heapq.heappush(rooms, interval[1])
            print(rooms)

        return len(rooms)

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        rooms = [] # min-heap
        max_rooms = 0
        intervals.sort()
        for interval in intervals:
            # clear
            while rooms and interval[0] >= rooms[0] :
                heapq.heappop(rooms)

            # allocate
            heapq.heappush(rooms, interval[1])
            max_rooms = max(max_rooms, len(rooms))
            # print(rooms)
            # print(max_rooms)
        return max_rooms
```

## Attempt 18 · 2024-02-06 23:43 IST · Accepted · Python3

[submission 1168065445](https://leetcode.com/submissions/detail/1168065445/) · tests 79/79 · runtime 81 ms (beats 6.7%)

```python
class Solution:
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        if not intervals:
            return 0
        
        free_rooms= []

        intervals.sort()

        for interval in intervals:
            if free_rooms and free_rooms[0] <= interval[0]:
                heapq.heappop(free_rooms)
            heapq.heappush(free_rooms, interval[1])
        return len(free_rooms)


    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort(key = lambda x: x[0])
        rooms = []
        for interval in intervals:
            if rooms[0] <=interval[0]:
                heapq.heapop(rooms)

            heapq.heappush(rooms, interval[1])

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        if not intervals:
            return 0

        used_rooms = 0

        starting_times = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)

        end_pointer = 0
        start_pointer = 0

        while start_pointer < L:
            if starting_times[start_pointer] >= end_timings[end_pointer]:
                used_rooms -=1
                end_pointer +=1
            start_pointer+=1
            used_rooms +=1

        return used_rooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()
        free_rooms = [] # keep end time
        for interval in intervals:
            # if no conflict - allocate this room
            if free_rooms and free_rooms[0] <= interval[0]:
                heapq.heappop(free_rooms)
            # insert interval
            heapq.heappush(free_rooms, interval[1])
        return len(free_rooms)

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()

        start_timings = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)

        start_pointer = 0
        end_pointer = 0
        used_rooms = 0
        
        while start_pointer < L:
            # if no overlap or conflic
            if start_timings[start_pointer] >= end_timings[end_pointer]:
                used_rooms -=1
                end_pointer +=1

            # iterate new interval
            start_pointer +=1
            used_rooms +=1

        return used_rooms
            
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()
        rooms = []
        maxRooms = 0
        for interval in intervals:
            # remove meetings that have ended before this meeting
            rooms = [room for room in rooms if interval[0] < room]
            
            # add to rooms
            rooms.append((interval[1]))
            # print(interval, rooms)
            maxRooms = max(len(rooms), maxRooms)

        return maxRooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()

        start_timings = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)
        print(start_timings, end_timings)
        start_pointer = 0
        end_pointer = 0
        used_rooms = 0
        maxRooms = 0
        while start_pointer < L:
            # if overlap
            if start_timings[start_pointer] < end_timings[end_pointer]:
                used_rooms +=1
                start_pointer +=1
            else:
                # no overlap
                end_pointer +=1
                used_rooms -=1
            print(start_pointer, end_pointer, used_rooms)
            maxRooms = max(maxRooms, used_rooms)
        
        return maxRooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        intervals.sort()

        start_timings = sorted(i[0] for i in intervals)
        end_timings = sorted(i[1] for i in intervals)

        L = len(intervals)
        print(start_timings, end_timings)
        start_pointer = 0
        end_pointer = 0
        used_rooms = 0
        maxRooms = 0
        while start_pointer < L:
            # if overlap
            if start_timings[start_pointer] >= end_timings[end_pointer]:
                used_rooms -=1
                end_pointer +=1

            start_pointer +=1
            used_rooms +=1
            print(start_pointer, end_pointer, used_rooms)
            maxRooms = max(maxRooms, used_rooms)
        
        return maxRooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        start_timings = sorted([interval[0] for interval in intervals])
        end_timings = sorted([interval[1] for interval in intervals])
        max_rooms = 0
        rooms = 0
        end_pointer = 0 
        start_pointer = 0
        print(start_timings, end_timings)
        while start_pointer < len(start_timings):
            while start_timings[start_pointer] >= end_timings[end_pointer]:
                rooms-=1
                end_pointer +=1
            
            rooms+=1
            max_rooms = max(max_rooms, rooms)
            print(start_pointer, end_pointer, rooms)
            start_pointer +=1
        return max_rooms

    def minMeetingRooms3(self, intervals: List[List[int]]) -> int:
        rooms = []
        intervals.sort()

        for interval in intervals:
            # 
            print('popping interval', rooms)
            while rooms and interval[0] >= rooms[0]:
                heapq.heappop(rooms)
            
            heapq.heappush(rooms, interval[1])
            print(rooms)

        return len(rooms)

    def minMeetingRooms3(self, intervals: List[List[int]]) -> int:
        rooms = [] # min-heap
        max_rooms = 0
        intervals.sort()
        for interval in intervals:
            # clear
            while rooms and interval[0] >= rooms[0] :
                heapq.heappop(rooms)

            # allocate
            heapq.heappush(rooms, interval[1])

            max_rooms = max(max_rooms, len(rooms))
        return max_rooms

    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        start_timings = sorted([interval[0] for interval in intervals])
        end_timings = sorted([interval[1] for interval in intervals])

        start_indx = 0
        end_indx = 0
        used_rooms = 0
        max_rooms = 0

        while start_indx < len(intervals):
            # clear all completed before this interval
            while end_indx < len(intervals) and end_timings[end_indx] <= start_timings[start_indx]:
                used_rooms -=1
                end_indx +=1

            used_rooms +=1
            start_indx +=1
            max_rooms = max(max_rooms, used_rooms)

        return max_rooms
```

## Attempt 19 · 2024-03-23 13:03 IST · Accepted · C++

[submission 1211468058](https://leetcode.com/submissions/detail/1211468058/) · tests 79/79 · runtime 7 ms (beats 20.4%)

```cpp
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        return minMeetingRoomsUsingEndTime(intervals);
        if(intervals.size()==0) return 0;
        priority_queue<int, vector<int>, greater<int> > pq;

        sort(intervals.begin(), intervals.end(), 
            [](vector<int> &a, vector<int> &b){
                return a[0]<b[0];
        });

        pq.push(intervals[0][1]);
        int rooms = pq.size();
        for(int i=1;i<intervals.size();i++){
            int end = pq.top();
            if(intervals[i][0] >= end){
                pq.pop();
            }
            pq.push(intervals[i][1]);
        }
        return pq.size();
    }
    int minMeetingRoomsUsingEndTime(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<int> start(n), end(n);

        for(int i=0;i<n;i++){
            start[i] = intervals[i][0];
            end[i] = intervals[i][1];
        }

        sort(start.begin(), start.end());
        sort(end.begin(), end.end());

        int i=0, j=0, used=0;

        while(i<n){
            used++;
            if(start[i] >= end[j]){
                used--;
                j++;
            }
            // ans = max(ans, rooms);
            i++;
        }
        return used;
    }
};
```
