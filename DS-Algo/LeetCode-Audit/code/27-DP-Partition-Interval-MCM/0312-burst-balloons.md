# 312. Burst Balloons

[Problem](https://leetcode.com/problems/burst-balloons/) · Hard · DP: Partition / Interval (MCM) → Interval DP (MCM)

LeetCode tags: array, dynamic-programming

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-04-03 11:47 IST · Accepted · C++

[submission 927031206](https://leetcode.com/submissions/detail/927031206/) · tests 73/73 · runtime 660 ms (beats 5.1%)

```cpp
class Solution {
public:
    int f(vector<int>& arr, int i, int j, vector<vector<int>>& dp){
    
        // base condition
        if(i>=j) return 0;
        // if(i == j)
        //     return arr[i-1]*arr[i]*arr[i+1]; //0;
            
        if(dp[i][j]!=-1)
            return dp[i][j];
        
        int mini = INT_MIN;
        
        // partioning loop
        for(int k = i; k< j; k++){
            
            // int ans = f(arr,i,k,dp) + f(arr, k+1,j,dp) + arr[i-1]*arr[k]*arr[j+1];
            int ans = f(arr,i,k,dp) + f(arr, k+1,j,dp) + arr[i-1]*arr[k]*arr[j];
            
            mini = max(mini,ans);
            // dp[i][j] = mini;
        }
        
        return dp[i][j] = mini;
    }
    int maxCoins(vector<int>& arr) {
        
        arr.insert(arr.begin(), 1);
        arr.push_back(1);
        int n = arr.size();
        vector<vector<int>> dp(n+1, vector<int>(n+1, -1));
        return f(arr, 1, n-1, dp);
    }
};
```

## Attempt 2 · 2023-04-03 11:58 IST · Accepted · C++

[submission 927036759](https://leetcode.com/submissions/detail/927036759/) · tests 73/73 · runtime 567 ms (beats 5.1%)

```cpp
class Solution {
public:
    int f(vector<int>& arr, int i, int j, vector<vector<int>>& dp){
    
        // base condition
        if(i == j)
            return 0; // single matrix /ballon so no operation required
            
        if(dp[i][j]!=-1)
            return dp[i][j];
        
        int mini = INT_MIN;
        
        // partioning loop
        for(int k = i; k<= j-1; k++){
            
            int ans = f(arr,i,k,dp) + f(arr, k+1,j,dp) + arr[i-1]*arr[k]*arr[j];
            mini = max(mini,ans);
            // dp[i][j] = mini;
        }
        
        return dp[i][j] = mini;
    }
    int maxCoins(vector<int>& arr) {
        
        arr.insert(arr.begin(), 1);
        arr.push_back(1);
        int n = arr.size();
        vector<vector<int>> dp(n+1, vector<int>(n+1, -1));
        return f(arr, 1, n-1, dp);
    }
};
```

## Attempt 3 · 2023-05-04 08:57 IST · Accepted · C++

[submission 944134740](https://leetcode.com/submissions/detail/944134740/) · tests 73/73 · runtime 818 ms (beats 5.1%)

```cpp
class Solution {
public:
    // int f(vector<int>& arr, int i, int j, vector<vector<int>>& dp){
    
    //     // base condition
    //     if(i == j)
    //         return 0; // single matrix /ballon so no operation required
            
    //     if(dp[i][j]!=-1)
    //         return dp[i][j];
        
    //     int mini = INT_MIN;
        
    //     // partioning loop
    //     for(int k = i; k<= j-1; k++){
            
    //         int ans = f(arr,i,k,dp) + f(arr, k+1,j,dp) + arr[i-1]*arr[k]*arr[j];
    //         mini = max(mini,ans);
    //         // dp[i][j] = mini;
    //     }
        
    //     return dp[i][j] = mini;
    // }
    int maxCoins(vector<int>& arr) {
        
        arr.insert(arr.begin(), 1);
        arr.push_back(1);
        int n = arr.size();
        vector<vector<int>> dp(n+1, vector<int>(n+1, -1));
        return f(1, n-1, arr, dp);
        // return f(arr, 1, n-1, dp);
    }
    int f(int i, int j, vector<int>& arr, vector<vector<int>> & dp){
        if(i==j) return 0;
        if(dp[i][j] != -1) return dp[i][j];
        int maxi = -1e9;
        for(int k=i;k<=j-1;k++){
            int steps = arr[i-1]*arr[k]*arr[j]  /* This will be different for diff question*/
                    + f(i,k,arr,dp) + f(k+1,j,arr,dp);
            maxi = max(maxi, steps);
        }
        return dp[i][j] = maxi;
    }
};
```
