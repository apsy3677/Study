# 1155. Number of Dice Rolls With Target Sum

[Problem](https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/) · Medium · DP: Knapsack / Subset → Bounded count

LeetCode tags: dynamic-programming

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-04-01 23:54 IST · Accepted · C++

[submission 926123214](https://leetcode.com/submissions/detail/926123214/) · tests 65/65 · runtime 31 ms (beats 8.1%)

```cpp
// class Solution {
//     int N = 1e9 + 7;
//     vector<vector<int>> dp;
// public:

//     int recur(int diceIdx, int sum, int n, int k, int target){
//         if(target < sum) return 0;
//         if(diceIdx == n && target != sum) return 0;
//         if(diceIdx == n && target == sum) return 1;

//         if(dp[diceIdx][target] != -1) return dp[diceIdx][sum];
//         int ans =0;

//         for(int i=1;i<=k;i++){
//             int useK = recur(diceIdx+1, sum +i, n,k,target);
//             // dp[diceIdx][target] = useK;
//             ans = (ans + useK ) %N;
//         }
//         // return ans;
//         return dp[diceIdx][sum] = ans;
//     }
//     int numRollsToTarget(int n, int k, int target) {
//         dp.resize(n+1, vector<int>(target +1,-1));
//         return recur(0,0,n,k, target);
//     }
// };
class Solution {
public:
    const int MOD = 1e9 + 7;
    
    int waysToTarget(vector<vector<int>>& memo, int diceIndex, int n, int currSum, int target, int k) {
        // All the n dice are traversed, the sum must be equal to target for valid combination
        if (diceIndex == n) {
            return currSum == target;
        }

        // We have already calculated the answer so no need to go into recursion
        if (memo[diceIndex][currSum] != -1) {
            return memo[diceIndex][currSum];
        }
		
        int ways = 0;
        // Iterate over the possible face value for current dice
        for (int i = 1; i <= min(k, target - currSum); i++) {
            ways = (ways + waysToTarget(memo, diceIndex + 1, n, currSum + i, target, k)) % MOD;
        }
        return memo[diceIndex][currSum] = ways;
    }
    
    int numRollsToTarget(int n, int k, int target) {
        vector<vector<int>> memo(n + 1, vector<int>(target + 1, -1));
        return waysToTarget(memo, 0, n, 0, target, k);
    }
};
```

## Attempt 2 · 2023-04-02 00:36 IST · Accepted · C++

[submission 926143507](https://leetcode.com/submissions/detail/926143507/) · tests 65/65 · runtime 125 ms (beats 5.2%)

```cpp
class Solution {
    int N = 1e9 + 7;
    // vector<vector<int>> dp;
public:

    int recur(vector<vector<int>> &dp, int diceIdx, int sum, int n, int k, int target){
        // if(target < sum) return 0;
        if(diceIdx == n  ) return target == sum;
        // if(diceIdx == n && target != sum) return 0;
        // if(diceIdx == n && target == sum) return 1;

        if(dp[diceIdx][target] != -1) return dp[diceIdx][sum];
        int ans =0;

        for(int i=1;i<= min(k,target -sum);i++){
            // int useK = recur(dp, diceIdx+1, sum +i, n,k,target);
            // dp[diceIdx][target] = useK;
            // ans = (ans + useK ) %N;
            ans = (ans + recur(dp, diceIdx+1, sum +i, n,k,target) ) %N;
        }
        // return ans;
        return dp[diceIdx][sum] = ans;
    }
    // int numRollsToTarget(int n, int k, int target) {
    int numRollsToTarget(int d, int f, int target) {
        // dp.resize(n+1, vector<int>(target +1,-1));
        // vector<vector<int>> dp(n+1, vector<int>(target +1,-1));
        // return recur(dp,0,0,n,k, target);

        // Bottom Up
        int m=1000000007;
        vector<vector<int> > dp(d+1, vector<int>(target+1, 0));
        dp[0][0]=1;
        for(int i=1; i<=d; i++){
            for(int j=1; j<=target; j++){
                for(int k=1; k<=f; k++){
                    if(k<=j)
                        dp[i][j]=((dp[i][j]%m)+(dp[i-1][j-k]%m))%m;
                }
            }
        }
        return dp[d][target];
    }
};
// class Solution {
// public:
//     const int MOD = 1e9 + 7;
    
//     int waysToTarget(vector<vector<int>>& memo, int diceIndex, int n, int currSum, int target, int k) {
//         // All the n dice are traversed, the sum must be equal to target for valid combination
//         if (diceIndex == n) {
//             return currSum == target;
//         }

//         // We have already calculated the answer so no need to go into recursion
//         if (memo[diceIndex][currSum] != -1) {
//             return memo[diceIndex][currSum];
//         }
		
//         int ways = 0;
//         // Iterate over the possible face value for current dice
//         for (int i = 1; i <= min(k, target - currSum); i++) {
//             ways = (ways + waysToTarget(memo, diceIndex + 1, n, currSum + i, target, k)) % MOD;
//         }
//         return memo[diceIndex][currSum] = ways;
//     }
    
//     int numRollsToTarget(int n, int k, int target) {
//         vector<vector<int>> memo(n + 1, vector<int>(target + 1, -1));
//         return waysToTarget(memo, 0, n, 0, target, k);
//     }
// };
```
