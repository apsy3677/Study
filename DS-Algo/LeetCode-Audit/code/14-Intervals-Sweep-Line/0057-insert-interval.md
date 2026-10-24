# 57. Insert Interval

[Problem](https://leetcode.com/problems/insert-interval/) · Medium · Intervals & Sweep Line → Insert and merge

LeetCode tags: array

Attempts since Mar 2023: 5 · accepted: 4 · failed before first AC: 1

## Attempt 1 · 2024-03-22 10:56 IST · Compile Error · C++

[submission 1210609059](https://leetcode.com/submissions/detail/1210609059/)

Your output:

```text
{"compile_error": "Line 5: Char 53: error: expected ';' after return statement\n    5 |         if (intervals.empty()) {return {newInterval}};\n      |                                                     ^\n      |                                                     ;"}
```

Compile error:

```text
Line 5: Char 53: error: expected ';' after return statement
    5 |         if (intervals.empty()) {return {newInterval}};
      |                                                     ^
      |                                                     ;
```

```cpp
class Solution {
    
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        
        if (intervals.empty()) {return {newInterval}};
        vector<vector<int>> ans;

        int i=0, n = intervals.size();
        // No overlap
        while (i<n && intervals[i][1] < newInterval[0]) {
            ans.push_back(intervals[i]);
            i++;
        }
        // overlapping and merge
        // newInterval start is > interval ka start from above loop
        // newInterval end >= curr interval ka start, then these intervals are merging.

        while (i<n && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        ans.push_back(newInterval);

        while (i<n) {
            ans.push_back(intervals[i++]);
        }

        return ans;
    }
};
```

## Attempt 2 · 2024-03-22 10:57 IST · Accepted · C++

[submission 1210609802](https://leetcode.com/submissions/detail/1210609802/) · tests 157/157 · runtime 7 ms (beats 6.1%)

```cpp
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        
        if (intervals.empty()) {return {newInterval}; }
        vector<vector<int>> ans;

        int i=0, n = intervals.size();
        // No overlap
        while (i<n && intervals[i][1] < newInterval[0]) {
            ans.push_back(intervals[i]);
            i++;
        }
        // overlapping and merge
        // newInterval start is > interval ka start from above loop
        // newInterval end >= curr interval ka start, then these intervals are merging.

        while (i<n && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        ans.push_back(newInterval);

        while (i<n) {
            ans.push_back(intervals[i++]);
        }

        return ans;
    }
};
```

## Attempt 3 · 2024-03-22 11:08 IST · Accepted · C++

[submission 1210617518](https://leetcode.com/submissions/detail/1210617518/) · tests 157/157 · runtime 7 ms (beats 6.1%)

```cpp
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        
        if (intervals.empty()) {return {newInterval}; }
        vector<vector<int>> ans;

        int i=0, n = intervals.size();
        // No overlap
        while (i<n && intervals[i][1] < newInterval[0]) {
            ans.push_back(intervals[i]);
            i++;
        }
        // overlapping and merge
        // newInterval start is > interval ka start from above loop
        // newInterval end >= curr interval ka start, then these intervals are merging.

        while (i<n && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        ans.push_back(newInterval);

        while (i<n) {
            ans.push_back(intervals[i++]);
        }

        return ans;
    }
};
```

## Attempt 4 · 2024-03-23 09:38 IST · Accepted · C++

[submission 1211347334](https://leetcode.com/submissions/detail/1211347334/) · tests 157/157 · runtime 9 ms (beats 6.1%)

```cpp
class Solution {
public:
vector<vector<int>> insert1(vector<vector<int>>& intervals, vector<int>& newInterval) {
        // If the intervals vector is empty, return a vector containing the newInterval
        if (intervals.empty()) {
            return {newInterval};
        }

        int n = intervals.size();
        int target = newInterval[0];
        int left = 0, right = n - 1;

        // Binary search to find the position to insert newInterval
        while (left <= right) {
            int mid = (left + right) / 2;
            if (intervals[mid][0] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        // Insert newInterval at the found position
        cout << "Insert at pos : " << left <<" :: ";

        // Merge overlapping intervals
        vector<vector<int>> res;
        for (int i=0; i<n && i<left; i++) {
            res.push_back(intervals[i]);
        }
        // insert newInterval
        if (!res.empty() && res.back()[1] >= newInterval[0]) {
            res.back()[1] = max(res.back()[1], newInterval[1]);
        } else {
            res.push_back(newInterval);
        }

        for (int i=left; i<n ; i++) {
            if (!res.empty() && res.back()[1] >= intervals[i][0]) {
                res.back()[1] = max(res.back()[1], intervals[i][1]);
            } else {
                res.push_back(intervals[i]);
            }
        }
        // for (const auto& interval : intervals) {
        //     // If res is empty or there is no overlap, add the interval to the result
        //     if (res.empty() || res.back()[1] < interval[0]) {
        //         res.push_back(interval);
        //     // If there is an overlap, merge the intervals by updating the end of the last interval in res
        //     } else {
        //         res.back()[1] = max(res.back()[1], interval[1]);
        //     }
        // }

        return res;
    }
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        
        return insert1(intervals, newInterval);

        if (intervals.empty()) {return {newInterval}; }
        vector<vector<int>> ans;

        int i=0, n = intervals.size();
        // No overlap
        while (i<n && intervals[i][1] < newInterval[0]) {
            ans.push_back(intervals[i]);
            i++;
        }
        // overlapping and merge
        // newInterval start is > interval ka start from above loop
        // newInterval end >= curr interval ka start, then these intervals are merging.

        while (i<n && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        ans.push_back(newInterval);

        while (i<n) {
            ans.push_back(intervals[i++]);
        }

        return ans;
    }
};
```

## Attempt 5 · 2024-03-23 13:19 IST · Accepted · C++

[submission 1211476832](https://leetcode.com/submissions/detail/1211476832/) · tests 157/157 · runtime 11 ms (beats 6.1%)

```cpp
class Solution {
public:
vector<vector<int>> insert1(vector<vector<int>>& intervals, vector<int>& newInterval) {
        // If the intervals vector is empty, return a vector containing the newInterval
        if (intervals.empty()) {
            return {newInterval};
        }

        int n = intervals.size();
        int target = newInterval[0];
        int left = 0, right = n - 1;

        // Binary search to find the position to insert newInterval
        while (left <= right) {
            int mid = (left + right) / 2;
            if (intervals[mid][0] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        // Insert newInterval at the found position
        // cout << "Insert at pos : " << left <<" :: ";

        // Merge overlapping intervals
        vector<vector<int>> res;
        for (int i=0; i<n && i<left; i++) {
            res.push_back(intervals[i]);
        }
        // insert newInterval
        if (!res.empty() && res.back()[1] >= newInterval[0]) {
            res.back()[1] = max(res.back()[1], newInterval[1]);
        } else {
            res.push_back(newInterval);
        }

        for (int i=left; i<n ; i++) {
            if (!res.empty() && res.back()[1] >= intervals[i][0]) {
                res.back()[1] = max(res.back()[1], intervals[i][1]);
            } else {
                res.push_back(intervals[i]);
            }
        }

        return res;
    }
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        
        return insert1(intervals, newInterval);

        if (intervals.empty()) {return {newInterval}; }
        vector<vector<int>> ans;

        int i=0, n = intervals.size();
        // No overlap
        while (i<n && intervals[i][1] < newInterval[0]) {
            ans.push_back(intervals[i]);
            i++;
        }
        // overlapping and merge
        // newInterval start is > interval ka start from above loop
        // newInterval end >= curr interval ka start, then these intervals are merging.

        while (i<n && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        ans.push_back(newInterval);

        while (i<n) {
            ans.push_back(intervals[i++]);
        }

        return ans;
    }
};
```
