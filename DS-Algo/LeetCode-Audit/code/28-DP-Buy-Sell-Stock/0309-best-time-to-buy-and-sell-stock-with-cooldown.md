# 309. Best Time to Buy and Sell Stock with Cooldown

[Problem](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/) · Medium · DP: Buy & Sell Stock → State machine

LeetCode tags: array, dynamic-programming

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-05-03 13:46 IST · Accepted · C++

[submission 943694651](https://leetcode.com/submissions/detail/943694651/) · tests 210/210 · runtime 9 ms (beats 6.1%)

```cpp
class Solution {
public:
    int rec(int ind, int buy, vector<int>& prices, vector<vector<int>> &dp){
        if(ind >= prices.size()) return 0;
        if(dp[ind][buy] != -1) return dp[ind][buy];
        int profit =0;
        if(buy){
            profit = max(-prices[ind] + rec(ind+1, !buy, prices, dp),
                            0 + rec(ind+1, buy, prices, dp));
        }
        else{
            profit = max(prices[ind] + rec(ind+2, !buy, prices, dp),
                            0 + rec(ind+1, buy, prices, dp));
        }
        return dp[ind][buy] = profit;
    }

    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int> (2,-1));
        return rec(0, 1, prices, dp);
    }
};
```
