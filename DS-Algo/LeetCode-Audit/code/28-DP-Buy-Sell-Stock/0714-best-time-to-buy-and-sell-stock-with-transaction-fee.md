# 714. Best Time to Buy and Sell Stock with Transaction Fee

[Problem](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/) · Medium · DP: Buy & Sell Stock → State machine

LeetCode tags: array, dynamic-programming, greedy

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-05-03 13:48 IST · Accepted · C++

[submission 943695800](https://leetcode.com/submissions/detail/943695800/) · tests 44/44 · runtime 275 ms (beats 5.3%)

```cpp
class Solution {
public:
int rec(int ind, int buy, int fee, vector<int>& prices, vector<vector<int>> &dp){
        if(ind >= prices.size()) return 0;
        if(dp[ind][buy] != -1) return dp[ind][buy];
        int profit =0;
        if(buy){
            profit = max(-prices[ind] + rec(ind+1, !buy, fee, prices, dp),
                            0 + rec(ind+1, buy, fee, prices, dp));
        }
        else{
            profit = max(prices[ind] -fee + rec(ind+1, !buy, fee, prices, dp),
                            0 + rec(ind+1, buy, fee, prices, dp));
        }
        return dp[ind][buy] = profit;
    }
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int> (2,-1));
        return rec(0, 1, fee, prices, dp);
    }
};
```
