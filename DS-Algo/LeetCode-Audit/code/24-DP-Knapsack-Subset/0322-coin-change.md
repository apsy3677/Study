# 322. Coin Change

[Problem](https://leetcode.com/problems/coin-change/) · Medium · DP: Knapsack / Subset → Unbounded, min count

LeetCode tags: array, dynamic-programming, breadth-first-search, knapsack-problem, complete-knapsack

Attempts since Mar 2023: 3 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-03-13 01:51 IST · Accepted · C++

[submission 914009174](https://leetcode.com/submissions/detail/914009174/) · tests 189/189 · runtime 110 ms (beats 5.6%)

```cpp
class Solution {
public:

    int minimumElementsUtil(vector<int>& arr, int ind, int T, vector<vector<int>>& dp){
        
        if(ind ==0 ){
            if(T%arr[0]==0){
                return T/arr[ind];
            }
            else
            return 1e9;
        }
        if(dp[ind][T]!=-1)
        return dp[ind][T];
        
        int nottaken = 0 + minimumElementsUtil(arr, ind-1, T, dp);
        int taken = 1e9;
        if(arr[ind]<=T){
            taken = 1+ minimumElementsUtil(arr, ind, T- arr[ind], dp);
        }
        return dp[ind][T] = min(taken, nottaken);
    }
    int coinChange(vector<int>& arr, int T) {
        int n= arr.size();
    
        vector<vector<int>> dp(n,vector<int>(T+1,-1));
        int ans =  minimumElementsUtil(arr, n-1, T, dp);
        if(ans >= 1e9) return -1;
        return ans;
    }
};
```

## Attempt 2 · 2023-03-13 01:52 IST · Wrong Answer · C++

[submission 914009772](https://leetcode.com/submissions/detail/914009772/) · tests 51/189

Failing input:

```text
[186,419,83,408]
6249
```

Expected:

```text
20
```

Your output:

```text
-1
```

```cpp
class Solution {
public:

    int minimumElementsUtil(vector<int>& arr, int ind, int T, vector<vector<int>>& dp){
        
        if(ind ==0 ){
            if(T%arr[0]==0){
                return T/arr[ind];
            }
            else
            return 1e9;
        }
        if(dp[ind][T]!=-1)
        return dp[ind][T];
        
        int nottaken = 0 + minimumElementsUtil(arr, ind-1, T, dp);
        int taken = 1e9;
        if(arr[ind]<=T){
            taken = T/arr[ind] + minimumElementsUtil(arr, ind-1, T- arr[ind]*(T/arr[ind]), dp);
        }
        return dp[ind][T] = min(taken, nottaken);
    }
    int coinChange(vector<int>& arr, int T) {
        int n= arr.size();
    
        vector<vector<int>> dp(n,vector<int>(T+1,-1));
        int ans =  minimumElementsUtil(arr, n-1, T, dp);
        if(ans >= 1e9) return -1;
        return ans;
    }
};
```

## Attempt 3 · 2023-03-13 01:53 IST · Accepted · C++

[submission 914009950](https://leetcode.com/submissions/detail/914009950/) · tests 189/189 · runtime 100 ms (beats 5.7%)

```cpp
class Solution {
public:

    int minimumElementsUtil(vector<int>& arr, int ind, int T, vector<vector<int>>& dp){
        
        if(ind ==0 ){
            if(T%arr[0]==0){
                return T/arr[ind];
            }
            else
            return 1e9;
        }
        if(dp[ind][T]!=-1)
        return dp[ind][T];
        
        int nottaken = 0 + minimumElementsUtil(arr, ind-1, T, dp);
        int taken = 1e9;
        if(arr[ind]<=T){
            taken = 1 + minimumElementsUtil(arr, ind, T- arr[ind], dp);
        }
        return dp[ind][T] = min(taken, nottaken);
    }
    int coinChange(vector<int>& arr, int T) {
        int n= arr.size();
    
        vector<vector<int>> dp(n,vector<int>(T+1,-1));
        int ans =  minimumElementsUtil(arr, n-1, T, dp);
        if(ans >= 1e9) return -1;
        return ans;
    }
};
```
