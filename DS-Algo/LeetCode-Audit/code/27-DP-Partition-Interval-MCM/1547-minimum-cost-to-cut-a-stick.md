# 1547. Minimum Cost to Cut a Stick

[Problem](https://leetcode.com/problems/minimum-cost-to-cut-a-stick/) · Hard · DP: Partition / Interval (MCM) → Interval DP (MCM)

LeetCode tags: array, dynamic-programming, sorting

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-04-03 11:25 IST · Accepted · C++

[submission 927021105](https://leetcode.com/submissions/detail/927021105/) · tests 100/100 · runtime 118 ms (beats 5.2%)

```cpp
class Solution {
public:
    int f(int i, int j, vector<int> &cuts,  vector<vector<int>> &dp){
        
        // base case
        if(i>j)
            return 0;
            
        if(dp[i][j]!=-1)
            return dp[i][j];
        
        int mini = INT_MAX;
        
        for(int ind=i; ind<=j; ind++){
            
            int ans = cuts[j+1] - cuts[i-1] +
                        f(i,ind-1,cuts,dp) +
                        f(ind+1,j,cuts,dp);
            
            mini = min(mini, ans);
            
        }
        
        return dp[i][j] = mini;
    }

    int minCost(int n, vector<int>& cuts) {
        int c = cuts.size();
        cuts.push_back(0);
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());

        vector<vector<int>> dp(c+1, vector<int>(c+1, -1));
        return f(1,c,cuts,dp);
    }
};
```

## Attempt 2 · 2023-05-04 08:47 IST · Accepted · C++

[submission 944131291](https://leetcode.com/submissions/detail/944131291/) · tests 100/100 · runtime 144 ms (beats 5.2%)

```cpp
class Solution {
public:
    int f(int i, int j, vector<int>& arr, vector<vector<int>> & dp){
    if(i>j) return 0;
    if(dp[i][j] != -1) return dp[i][j];
    int mini = 1e9;
    for(int k=i;k<=j;k++){
        int steps = arr[j+1] - arr[i-1]  /* This will be different for diff question*/
                + f(i,k-1,arr,dp) + f(k+1,j,arr,dp);
        mini = min(mini, steps);
    }
    return dp[i][j] = mini;
}

    int minCost(int n, vector<int>& cuts) {
        int c = cuts.size();
        cuts.push_back(0);
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());

        vector<vector<int>> dp(c+1, vector<int>(c+1, -1));
        return f(1,c,cuts,dp);
    }
};
```

## Attempt 3 · 2023-05-04 08:50 IST · Accepted · C++

[submission 944132427](https://leetcode.com/submissions/detail/944132427/) · tests 100/100 · runtime 143 ms (beats 5.2%)

```cpp
class Solution {
public:
    int f(int i, int j, vector<int>& arr, vector<vector<int>> & dp){
        if(i>j) return 0;
        if(dp[i][j] != -1) return dp[i][j];
        int mini = 1e9;
        for(int k=i;k<=j;k++){
            int steps = arr[j+1] - arr[i-1]  /* This will be different for diff question*/
                    + f(i,k-1,arr,dp) + f(k+1,j,arr,dp); // cut has been made at k so we need to solve for i to k-1 and k+1 to j
            mini = min(mini, steps);
        }
        return dp[i][j] = mini;
    }

    int minCost(int n, vector<int>& cuts) {
        int c = cuts.size();
        cuts.push_back(0);
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());

        vector<vector<int>> dp(c+1, vector<int>(c+1, -1));
        return f(1,c,cuts,dp);
    }
};
```
