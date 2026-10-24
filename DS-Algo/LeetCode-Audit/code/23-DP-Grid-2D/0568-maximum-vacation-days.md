# 568. Maximum Vacation Days

[Problem](https://leetcode.com/problems/maximum-vacation-days/) · Hard · DP: Grid / 2D → Week x city DP

LeetCode tags: array, dynamic-programming, matrix

Attempts since Mar 2023: 3 · accepted: 2 · failed before first AC: 1

## Attempt 1 · 2023-03-23 18:54 IST · Time Limit Exceeded · C++

[submission 920722046](https://leetcode.com/submissions/detail/920722046/) · tests 37/57

Failing input:

```text
[[0,0,0,1,1,1,0,1,1,1,0,0,1,1,1,1,0,1,0,1,1,0,1,1,1,0,1,1,1,1,0,1,0,1,0,0,1,0,1,1,1,0,0,1,1,1,0,1,0,0,0,1,1,0,1,1,1,0,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,1,1,1,0,1,1,1,0,0,0,0,1,1,0,0,1,0],[1,0,1,1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,1,1,1,0,1,0,1,1,0,1,0,0,1,1,0,1,1,0,1,0,1,0,0,0,1,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,0,1,0,1,1,1,0,0,1,1,0, ... [30403 more chars]
```

Expected:

```text
104
```

```cpp
class Solution {
public:
    int dfs(int week, int city, vector<vector<int>>& flights, vector<vector<int>>& days){
        if(week == days[0].size()){
            return 0;
        }
        int n = flights.size();
        int maxvac =0;

        // all flights that can be taken
        for(int i=0;i<n;i++){
            if(i==city || flights[city][i]==1){
                int vac = days[i][week];
                // go to next city i, take vac there
                vac += dfs(week+1, i, flights, days);
                maxvac = max(maxvac, vac);
            }
        }
        return maxvac;
    }
    int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days) {
        
        return dfs(0, 0, flights, days);
    }
};
```

## Attempt 2 · 2023-03-23 18:57 IST · Accepted · C++

[submission 920723582](https://leetcode.com/submissions/detail/920723582/) · tests 57/57 · runtime 277 ms (beats 9.1%)

```cpp
class Solution {
public:
    int dfs(int week, int city, vector<vector<int>>& flights, vector<vector<int>>& days, vector<vector<int>>& dp){
        if(week == days[0].size()){
            return 0;
        }
        if(dp[city][week] != -1){
            return dp[city][week];
        }
        int n = flights.size();
        int maxvac =0;

        // all flights that can be taken
        for(int i=0;i<n;i++){
            if(i==city || flights[city][i]==1){
                int vac = days[i][week];
                // go to next city i, take vac there
                vac += dfs(week+1, i, flights, days, dp);
                maxvac = max(maxvac, vac);
            }
        }
        return dp[city][week] = maxvac;
    }
    int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days) {
        int n = flights.size();
        int k = days[0].size();
        vector<vector<int>> dp(n, vector<int>(k,-1));
        return dfs(0, 0, flights, days, dp);
    }
};
```

## Attempt 3 · 2023-03-23 19:02 IST · Accepted · C++

[submission 920726001](https://leetcode.com/submissions/detail/920726001/) · tests 57/57 · runtime 253 ms (beats 9.1%)

```cpp
class Solution {
public:
    int dfs(int week, int city, vector<vector<int>>& flights, vector<vector<int>>& days, vector<vector<int>>& dp){
        if(week == days[0].size()){
            return 0;
        }
        if(dp[city][week] != -1){
            return dp[city][week];
        }
        int n = flights.size();
        int maxvac =0;

        // all flights that can be taken
        for(int i=0;i<n;i++){
            if(i==city || flights[city][i]==1){
                int vac = days[i][week];
                // go to next city i, take vac there
                vac += dfs(week+1, i, flights, days, dp);
                maxvac = max(maxvac, vac);
            }
        }
        return dp[city][week] = maxvac;
    }
    int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days) {
        int n = flights.size();
        int k = days[0].size();
        vector<vector<int>> dp(n, vector<int>(k,-1));
        return dfs(0, 0, flights, days, dp);
    }
};
```
