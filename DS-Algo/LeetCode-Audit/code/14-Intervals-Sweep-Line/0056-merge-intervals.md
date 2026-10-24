# 56. Merge Intervals

[Problem](https://leetcode.com/problems/merge-intervals/) · Medium · Intervals & Sweep Line → Sort and merge

LeetCode tags: array, sorting, quicksort

Attempts since Mar 2023: 16 · accepted: 12 · failed before first AC: 0

## Attempt 1 · 2023-03-07 01:41 IST · Accepted · C++

[submission 910396906](https://leetcode.com/submissions/detail/910396906/) · tests 170/170 · runtime 38 ms (beats 5.1%)

```cpp
#include<bits/stdc++.h>
class Solution {
public:
    static bool sortcol0(const vector<int> &v1, const vector<int>& v2){
        return v1[0] < v2[0];
    }
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector< vector<int> >  output;
        sort(intervals.begin(), intervals.end(), sortcol0);
        
        for(auto interval : intervals){
            if(output.empty() || output.back()[1] < interval[0]){
                output.push_back(interval);
            }
            else{
                output.back()[1] = max(output.back()[1], interval[1]);
            }
        }

        return output;
    }
};
```

## Attempt 2 · 2023-03-07 01:42 IST · Accepted · C++

[submission 910397138](https://leetcode.com/submissions/detail/910397138/) · tests 170/170 · runtime 43 ms (beats 5.1%)

```cpp
#include<bits/stdc++.h>
class Solution {
public:
    static bool sortcol0(const vector<int> &v1, const vector<int>& v2){
        return v1[0] < v2[0];
    }
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector< vector<int> >  output;
        sort(intervals.begin(), intervals.end());
        
        for(auto interval : intervals){
            if(output.empty() || output.back()[1] < interval[0]){
                output.push_back(interval);
            }
            else{
                output.back()[1] = max(output.back()[1], interval[1]);
            }
        }

        return output;
    }
};
```

## Attempt 3 · 2023-03-22 22:10 IST · Accepted · C++

[submission 920230058](https://leetcode.com/submissions/detail/920230058/) · tests 170/170 · runtime 43 ms (beats 5.1%)

```cpp
#include<bits/stdc++.h>
class Solution {
public:
    static bool sortcol0(const vector<int> &v1, const vector<int>& v2){
        return v1[0] < v2[0];
    }
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector< vector<int> >  output;
        sort(intervals.begin(), intervals.end());
        
        for(auto interval : intervals){
            if(output.empty() || output.back()[1] < interval[0]){
                output.push_back(interval);
            }
            else{
                output.back()[1] = max(output.back()[1], interval[1]);
            }
        }

        return output;
    }
};
```

## Attempt 4 · 2023-05-20 16:01 IST · Wrong Answer · C++

[submission 953843345](https://leetcode.com/submissions/detail/953843345/) · tests 63/170

Failing input:

```text
[[1,4],[2,3]]
```

Expected:

```text
[[1,4]]
```

Your output:

```text
[[1,3]]
```

```cpp
#include<bits/stdc++.h>
class Solution {
public:
    static bool sortcol0(const vector<int> &v1, const vector<int>& v2){
        return v1[0] < v2[0];
    }
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> merged;
        if(intervals.empty()) return merged;
        sort(intervals.begin(), intervals.end(), [](const vector<int> a, const vector<int> b){
            return a[0] < b[0];
        });

        merged.push_back( { intervals[0][0], intervals[0][1] } );

        for(int i=1;i<intervals.size();i++){
            if(intervals[i][0] > merged.back()[1]){
                merged.push_back( { intervals[i][0], intervals[i][1]});
            }
            else{
                merged.back()[1] = intervals[i][1];
            }
        }
        return merged;
        // vector< vector<int> >  output;
        // sort(intervals.begin(), intervals.end());
        
        // for(auto interval : intervals){
        //     if(output.empty() || output.back()[1] < interval[0]){
        //         output.push_back(interval);
        //     }
        //     else{
        //         output.back()[1] = max(output.back()[1], interval[1]);
        //     }
        // }

        // return output;
    }
};
```

## Attempt 5 · 2023-05-20 16:03 IST · Accepted · C++

[submission 953844178](https://leetcode.com/submissions/detail/953844178/) · tests 170/170 · runtime 226 ms (beats 5.0%)

```cpp
#include<bits/stdc++.h>
class Solution {
public:
    static bool sortcol0(const vector<int> &v1, const vector<int>& v2){
        return v1[0] < v2[0];
    }
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> merged;
        if(intervals.empty()) return merged;
        sort(intervals.begin(), intervals.end(), [](const vector<int> a, const vector<int> b){
            if(a[0] == b[0]) return a[1]<b[1];
            return a[0] < b[0];
        });

        merged.push_back( { intervals[0][0], intervals[0][1] } );

        for(int i=1;i<intervals.size();i++){
            if(intervals[i][0] > merged.back()[1]){
                merged.push_back( { intervals[i][0], intervals[i][1]});
            }
            else{
                merged.back()[1] = max(intervals[i][1], merged.back()[1]);
            }
        }
        return merged;
        // vector< vector<int> >  output;
        // sort(intervals.begin(), intervals.end());
        
        // for(auto interval : intervals){
        //     if(output.empty() || output.back()[1] < interval[0]){
        //         output.push_back(interval);
        //     }
        //     else{
        //         output.back()[1] = max(output.back()[1], interval[1]);
        //     }
        // }

        // return output;
    }
};
```

## Attempt 6 · 2023-05-20 16:04 IST · Accepted · C++

[submission 953844515](https://leetcode.com/submissions/detail/953844515/) · tests 170/170 · runtime 37 ms (beats 5.1%)

```cpp
#include<bits/stdc++.h>
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> merged;
        if(intervals.empty()) return merged;
        sort(intervals.begin(), intervals.end());

        merged.push_back( { intervals[0][0], intervals[0][1] } );

        for(int i=1;i<intervals.size();i++){
            if(intervals[i][0] > merged.back()[1]){
                merged.push_back( { intervals[i][0], intervals[i][1]});
            }
            else{
                merged.back()[1] = max(intervals[i][1], merged.back()[1]);
            }
        }
        return merged;
    }
};
```

## Attempt 7 · 2023-11-16 08:07 IST · Accepted · Python

[submission 1099770280](https://leetcode.com/submissions/detail/1099770280/) · tests 170/170 · runtime 101 ms (beats 5.1%)

```python
class Solution(object):
    def merge(self, intervals):
        """
        :type intervals: List[List[int]]
        :rtype: List[List[int]]
        """
        intervals.sort()
        mergedList = [intervals[0]]
        for i in range(1, len(intervals)):
            # if overlap
            if intervals[i][0] <= mergedList[-1][1]:
                mergedList[-1][1] = max(mergedList[-1][1], intervals[i][1])
            else:
                mergedList.append(intervals[i])
            
        return mergedList
```

## Attempt 8 · 2023-11-22 08:40 IST · Wrong Answer · Python3

[submission 1103883604](https://leetcode.com/submissions/detail/1103883604/) · tests 10/170

Failing input:

```text
[[1,4],[0,4]]
```

Expected:

```text
[[0,4]]
```

Your output:

```text
[[1,4]]
```

```python
class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        mergedIntervals = []

        for interval in intervals:
            if len(mergedIntervals)>0 and interval[0] <= mergedIntervals[-1][1]:
                mergedIntervals[-1][1] = interval[1]
            else:
                mergedIntervals.append(interval)

        return mergedIntervals
```

## Attempt 9 · 2023-11-22 08:41 IST · Runtime Error · Python3

[submission 1103884052](https://leetcode.com/submissions/detail/1103884052/) · tests 0/170

Failing input:

```text
[[1,3],[2,6],[8,10],[15,18]]
```

Expected:

```text
[[1,6],[8,10],[15,18]]
```

Runtime error:

```text
SyntaxError: invalid syntax
                      ^
    intervals.sort(key: lambda x: x[0])
Line 5  (Solution.py)
```

```python
class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        mergedIntervals = []

        intervals.sort(key: lambda x: x[0])

        for interval in intervals:
            if len(mergedIntervals)>0 and interval[0] <= mergedIntervals[-1][1]:
                mergedIntervals[-1][1] = interval[1]
            else:
                mergedIntervals.append(interval)

        return mergedIntervals
```

## Attempt 10 · 2023-11-22 08:41 IST · Wrong Answer · Python3

[submission 1103884172](https://leetcode.com/submissions/detail/1103884172/) · tests 63/170

Failing input:

```text
[[1,4],[2,3]]
```

Expected:

```text
[[1,4]]
```

Your output:

```text
[[1,3]]
```

```python
class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        mergedIntervals = []

        intervals.sort(key= lambda x: x[0])

        for interval in intervals:
            if len(mergedIntervals)>0 and interval[0] <= mergedIntervals[-1][1]:
                mergedIntervals[-1][1] = interval[1]
            else:
                mergedIntervals.append(interval)

        return mergedIntervals
```

## Attempt 11 · 2023-11-22 08:42 IST · Accepted · Python3

[submission 1103884432](https://leetcode.com/submissions/detail/1103884432/) · tests 170/170 · runtime 133 ms (beats 5.0%)

```python
class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        mergedIntervals = []

        intervals.sort(key= lambda x: x[0])

        for interval in intervals:
            if len(mergedIntervals)>0 and interval[0] <= mergedIntervals[-1][1]:
                mergedIntervals[-1][1] = max(interval[1], mergedIntervals[-1][1])
            else:
                mergedIntervals.append(interval)

        return mergedIntervals
```

## Attempt 12 · 2023-12-04 21:19 IST · Accepted · Python3

[submission 1112254485](https://leetcode.com/submissions/detail/1112254485/) · tests 170/170 · runtime 112 ms (beats 5.0%)

```python
class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        mergedIntervals = []

        # 1. sort for all interval related problems 
        # to be able to process, you need it in some order to make decision
        intervals.sort(key= lambda x: x[0])


        for interval in intervals:

            # take care of first interval 
            # if overlap between start of current interval and end of last interval
            if len(mergedIntervals)>0 and interval[0] <= mergedIntervals[-1][1]:

                # assign max of end interval for union merge
                # the start remains same in this case but if there are two lists that has to be merged,
                # you might need to update start interval as well
                mergedIntervals[-1][1] = max(interval[1], mergedIntervals[-1][1])
            else:
                mergedIntervals.append(interval)

        return mergedIntervals
```

## Attempt 13 · 2023-12-04 21:20 IST · Accepted · Python3

[submission 1112254617](https://leetcode.com/submissions/detail/1112254617/) · tests 170/170 · runtime 135 ms (beats 5.0%)

```python
class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        mergedIntervals = []

        # 1. sort for all interval related problems 
        # to be able to process, you need it in some order to make decision
        intervals.sort(key= lambda x: x[0])


        for interval in intervals:

            # take care of first interval 
            # if overlap between start of current interval and end of last interval
            if len(mergedIntervals)>0 and interval[0] <= mergedIntervals[-1][1]:

                # assign max of end interval for union merge
                # the start remains same in this case but if there are two lists that has to be merged,
                # you might need to update start interval as well
                mergedIntervals[-1][1] = max(interval[1], mergedIntervals[-1][1])
            else:
                mergedIntervals.append(interval)

        return mergedIntervals
```

## Attempt 14 · 2024-03-22 09:54 IST · Accepted · C++

[submission 1210567878](https://leetcode.com/submissions/detail/1210567878/) · tests 170/170 · runtime 28 ms (beats 5.2%)

```cpp
#include<bits/stdc++.h>
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.empty()) return {};
        vector<vector<int>> merged;

        sort(intervals.begin(), intervals.end());

        merged.push_back( { intervals[0][0], intervals[0][1] } );

        for(int i=1;i<intervals.size();i++){
            if(intervals[i][0] > merged.back()[1]){
                merged.push_back( { intervals[i][0], intervals[i][1]});
            }
            else{
                merged.back()[1] = max(intervals[i][1], merged.back()[1]);
            }
        }
        return merged;
    }
};
```

## Attempt 15 · 2024-03-22 09:56 IST · Accepted · C++

[submission 1210568771](https://leetcode.com/submissions/detail/1210568771/) · tests 170/170 · runtime 24 ms (beats 5.3%)

```cpp
#include<bits/stdc++.h>
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.empty()) return {};
        vector<vector<int>> merged;

        sort(intervals.begin(), intervals.end());

        merged.push_back( { intervals[0][0], intervals[0][1] } );

        for(int i=1;i<intervals.size();i++){
            if(intervals[i][0] > merged.back()[1]){
                merged.push_back( { intervals[i][0], intervals[i][1]});
            }
            else{
                merged.back()[1] = max(intervals[i][1], merged.back()[1]);
            }
        }
        return merged;
    }
};
```

## Attempt 16 · 2025-07-07 23:06 IST · Accepted · C++

[submission 1689875947](https://leetcode.com/submissions/detail/1689875947/) · tests 171/171 · runtime 3 ms (beats 90.8%)

```cpp
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};
    
        // Sort by start time
        sort(intervals.begin(), intervals.end());
        
        vector<vector<int>> merged;
        merged.push_back(intervals[0]);
        
        for (int i = 1; i < intervals.size(); i++) {
            // If current interval overlaps with the last merged interval
            if (intervals[i][0] <= merged.back()[1]) {
                // Merge by updating the end time
                merged.back()[1] = max(merged.back()[1], intervals[i][1]);
            } else {
                // No overlap, add new interval
                merged.push_back(intervals[i]);
            }
        }
        
        return merged;
    }
};
```
