# 2345. Finding the Number of Visible Mountains

[Problem](https://leetcode.com/problems/finding-the-number-of-visible-mountains/) · Medium · Monotonic Stack / Deque → Sort + stack

LeetCode tags: array, stack, sorting, monotonic-stack

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2023-03-24 11:40 IST · Wrong Answer · C++

[submission 921134643](https://leetcode.com/submissions/detail/921134643/) · tests 6/46

Failing input:

```text
[[3,19],[39,7],[15,39],[23,13],[8,28],[2,26],[38,15],[38,7],[16,17]]
```

Expected:

```text
1
```

Your output:

```text
8
```

```cpp
class Solution {
public:
    int visibleMountains(vector<vector<int>>& peaks) {
        stack<int> st;
        int n = peaks.size();
        if(n<=1)
            return 1;
        sort(peaks.begin(), peaks.end());
        int ans =0;
        st.push(0);

        for(int i=1;i<n;i++){
            int x = peaks[i][0];
            int y = peaks[i][1];

            if(st.empty()){
                st.push(i);
                continue;
            }
            // check if curr x,y hides some other mountains
            while(!st.empty()){
                int idx = st.top();
                int k1 = (x - peaks[idx][0]);
                int k2 = (y - peaks[idx][1]);
                if(k1 == k2 & y <=peaks[idx][1] ){
                    // st.pop();
                    // can't push this to stack
                    break;
                } 
                else if(k1 == k2 & y > peaks[idx][1] ){
                    // st.pop();
                    // can't push this to stack
                    st.pop();
                    st.push(i);
                }
                else{
                    st.push(i);
                }  
            }
        }
        return st.size()-1;
    }
};
```

## Attempt 2 · 2023-03-24 13:33 IST · Accepted · C++

[submission 921180925](https://leetcode.com/submissions/detail/921180925/) · tests 46/46 · runtime 743 ms (beats 13.2%)

```cpp
class Solution {
public:
    int solve (vector<vector<int>>& peaks){
        
        int n = peaks.size();
        if(n<=1)
            return 1;

        vector<vector<int>> vec(n, vector<int> (2, 0));
        // for(int i=0;i<n;i++){
        //     int x = peaks[i][0] - peaks[i][1];
        //     int y = peaks[i][0] + peaks [i][1];
        //     vec[i][0] = x;
        //     vec[i][1] = y;

        // }
        for (int i = 0; i < n; i++) {
            vec[i][0] = peaks[i][0] - peaks[i][1];
            vec[i][1] = peaks[i][0] + peaks[i][1];
        }
        sort(vec.begin(), vec.end());

        stack<pair<int,int>> st;
        int repeat =0;
        // st.push({vec[0][0], vec[0][1]});

        for(int i=0;i<n;i++){
            int x = vec[i][0];
            int y = vec[i][1];

            while(!st.empty() && (x == st.top().first && y == st.top().second)){
                repeat++;
                // continue;
            }
            // remove from st if triangle is smaller
            while(!st.empty() && (x <= st.top().first && y >= st.top().second)){
                st.pop();
            }
            if(!st.empty() && (x >= st.top().first && y <= st.top().second)){
                continue;
            }
            // st.push({x,y});
            st.push({vec[i][0], vec[i][1]});
        }

        return max(0, (int)st.size() - repeat);
    }
    int visibleMountains(vector<vector<int>>& peaks) {

        return solve1(peaks);
        // return solve(peaks);

    }

    int solve1(vector<vector<int>>& peaks){
        int n = peaks.size();
        vector<vector<int>> intervals (n, vector<int> (2, 0));
        stack<vector<int>> st;
        int repeated = 0;
        
        // Conversion to intervals
        // Store left and right of each triangle, instead of center and height
        for (int i = 0; i < n; i++) {
            intervals[i][0] = peaks[i][0] - peaks[i][1];
            intervals[i][1] = peaks[i][0] + peaks[i][1];
        }
        
        // Sort the intervals by their start time
        sort(intervals.begin(), intervals.end());
        
        for (int i = 0; i < n; i++) {
            // Keep track of repeated intervals
            if (!st.empty() && st.top()[1] == intervals[i][1] && st.top()[0] == intervals[i][0]) {
                repeated++;
            }
            
            // If the new interval can hide old intervals, then pop those old intervals
            while (!st.empty() && st.top()[0] >= intervals[i][0] && st.top()[1] <= intervals[i][1]) {
                st.pop();
            } 
            
            // If the new interval can't hide the top (peak) interval of the stack, then skip it
            if (!st.empty() && st.top()[0] <= intervals[i][0] && st.top()[1] >= intervals[i][1]) {
                continue;
            }
            
            // Otherwise, push it
            st.push(intervals[i]);
        }
        
        // We can't have negative number of visible mountains
        return max((int)st.size() - repeated, 0);
    }
};
```
