# 1043. Partition Array for Maximum Sum

[Problem](https://leetcode.com/problems/partition-array-for-maximum-sum/) · Medium · DP: Partition / Interval (MCM) → Front partition DP

LeetCode tags: array, dynamic-programming

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-05-04 10:48 IST · Accepted · C++

[submission 944176802](https://leetcode.com/submissions/detail/944176802/) · tests 52/52 · runtime 26 ms (beats 10.9%)

```cpp
class Solution {
    int f(int i, vector<int> &arr, int k, vector<int> &dp){
        
        if(i==arr.size()) return 0;

        if(dp[i] != -1) return dp[i];
        // partition by ind
        int maxi = -1e9;
        int maxSum = 0, len=0;
        for(int ind =i; ind < min(i+k, (int)arr.size()) ;ind++){
            maxi = max(arr[ind], maxi);
            len++;
            int sum = maxi * (len) + f(ind+1,arr,k,dp);
            maxSum = max(maxSum, sum);
        }
        return dp[i]=maxSum;
    }
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        vector<int> dp(arr.size(),-1);
        return f(0,arr,k,dp);
    }
};
```

## Attempt 2 · 2023-05-04 10:50 IST · Accepted · C++

[submission 944177839](https://leetcode.com/submissions/detail/944177839/) · tests 52/52 · runtime 41 ms (beats 9.0%)

```cpp
class Solution {
    int f(int i, vector<int> &arr, int k, vector<int> &dp){
        
        if(i==arr.size()) return 0;

        if(dp[i] != -1) return dp[i];
        // partition by ind
        int maxi = -1e9;
        int maxSum = 0, len=0;
        for(int ind =i; ind < min(i+k, (int)arr.size()) ;ind++){
            maxi = max(arr[ind], maxi);
            len++;
            int sum = maxi * (len) + f(ind+1,arr,k,dp);
            maxSum = max(maxSum, sum);
        }
        return dp[i]=maxSum;
    }
    int tabulation(vector<int>& arr, int k){
        int n = arr.size();
        vector<int> dp(arr.size() +1 ,0);
        dp[n] =0;

        for(int i=n-1;i>=0;i--){
            int maxi = -1e9;
            int maxSum = 0, len=0;
            for(int ind =i; ind < min(i+k, n) ;ind++){
                maxi = max(arr[ind], maxi);
                len++;
                int sum = maxi * (len) + dp[ind+1];
                maxSum = max(maxSum, sum);
            }
            dp[i]=maxSum;
        }
        return dp[0];
    }
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        vector<int> dp(arr.size(),-1);
        tabulation(arr,k);
        return f(0,arr,k,dp);
    }
};
```

## Attempt 3 · 2023-05-04 10:51 IST · Accepted · C++

[submission 944177961](https://leetcode.com/submissions/detail/944177961/) · runtime 13 ms

_Code not returned by LeetCode._
