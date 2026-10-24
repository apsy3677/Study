# 539. Minimum Time Difference

[Problem](https://leetcode.com/problems/minimum-time-difference/) · Medium · Arrays, Hashing & Sorting → Sort, circular difference

LeetCode tags: array, math, string, sorting

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2023-04-01 13:57 IST · Wrong Answer · C++

[submission 925790048](https://leetcode.com/submissions/detail/925790048/) · tests 94/113

Failing input:

```text
["12:12","00:13"]
```

Expected:

```text
719
```

Your output:

```text
695
```

```cpp
class Solution {
public:
    int findMinDifference(vector<string>& time) {
        
        vector<int> mins;
        int ans = INT_MAX;

        for(auto t : time){
            int timeInMins = stoi(t.substr(0,2)) * 60 + stoi(t.substr(3,2));
            mins.push_back(timeInMins);
        }
        sort(mins.begin(), mins.end());

        for(int i=0;i<time.size()-1;i++){
            ans = min(ans, abs(mins[i+1] -mins[i]));
        }
        ans = min(ans, abs(mins[time.size()-1] - 24*60 + mins[0]));
        return ans;
    }
};
```

## Attempt 2 · 2023-04-01 14:07 IST · Accepted · C++

[submission 925793890](https://leetcode.com/submissions/detail/925793890/) · tests 113/113 · runtime 27 ms (beats 7.3%)

```cpp
class Solution {
public:
    int findMinDifference(vector<string>& time) {
        
        vector<int> mins;
        int ans = INT_MAX;

        for(auto t : time){
            int timeInMins = stoi(t.substr(0,2)) * 60 + stoi(t.substr(3,2));
            mins.push_back(timeInMins);
        }
        sort(mins.begin(), mins.end());

        for(int i=0;i<time.size()-1;i++){
            ans = min(ans, abs(mins[i+1] -mins[i]));
            cout<<mins[i+1] -mins[i] <<" ";
        }
        ans = min(ans, abs(mins[time.size()-1] - (24*60 + mins[0])));
        cout<<"||"<<mins[time.size()-1]<<"-"<<24*60 + mins[0]<<"="<<abs(mins[time.size()-1] - (24*60 + mins[0])) <<" ";
        return ans;
    }
};
```
