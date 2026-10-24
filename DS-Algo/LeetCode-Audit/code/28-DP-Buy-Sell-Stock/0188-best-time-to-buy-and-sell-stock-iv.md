# 188. Best Time to Buy and Sell Stock IV

[Problem](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/) · Hard · DP: Buy & Sell Stock → At most k transactions

LeetCode tags: array, dynamic-programming

Attempts since Mar 2023: 5 · accepted: 4 · failed before first AC: 0

## Attempt 1 · 2023-05-03 12:37 IST · Accepted · C++

[submission 943666197](https://leetcode.com/submissions/detail/943666197/) · tests 210/210 · runtime 38 ms (beats 12.3%)

```cpp
class Solution {
public:
int rec1(int ind, bool buy, int k, vector<int> &prices, vector<vector<vector<int>>> &dp){
        if(ind ==prices.size()) return 0;// last indx finished can't buy or sell now
        if(k==0) return 0;

        if(dp[ind][buy][k] != -1) return dp[ind][buy][k];

        int profit = 0;
        if(buy){
            // we can only buy here
            // take or not take this option
            profit = max(-prices[ind] + rec1(ind+1, !buy, k, prices,dp), /*buy the stock*/
                                    0 + rec1(ind+1, buy, k, prices, dp)); // did not buy today
        }
        else{
            profit = max(prices[ind] + rec1(ind+1, !buy, k-1, prices,dp), /*sell the stock*/
                                    0 + rec1(ind+1, buy, k, prices, dp)); // did not sell today
        }
        return dp[ind][buy][k] = profit;
    }
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (k+1,-1)));

        return rec1(0,1,k,prices,dp);
    }
};
```

## Attempt 2 · 2023-05-03 12:54 IST · Accepted · C++

[submission 943673458](https://leetcode.com/submissions/detail/943673458/) · tests 210/210 · runtime 61 ms (beats 6.5%)

```cpp
class Solution {
public:
int rec1(int ind, bool buy, int k, vector<int> &prices, vector<vector<vector<int>>> &dp){
        if(ind ==prices.size()) return 0;// last indx finished can't buy or sell now
        if(k==0) return 0;

        if(dp[ind][buy][k] != -1) return dp[ind][buy][k];

        int profit = 0;
        if(buy){
            // we can only buy here
            // take or not take this option
            profit = max(-prices[ind] + rec1(ind+1, !buy, k, prices,dp), /*buy the stock transaction is not complete yet therefore k remains k*/
                                    0 + rec1(ind+1, buy, k, prices, dp)); // did not buy today
        }
        else{
            profit = max(prices[ind] + rec1(ind+1, !buy, k-1, prices,dp), /*sell the stock*/
                                    0 + rec1(ind+1, buy, k, prices, dp)); // did not sell today
        }
        return dp[ind][buy][k] = profit;
    }
    int tabulation(int cap, vector<int>& prices){
        int n = prices.size();
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>> (2, vector<int> (cap+2,-1)));

        for(int i=0;i<2;i++){
            for(int j=0;j<=cap;j++){
                dp[n][i][j] = 0;
            }
        }
        for(int ind= n-1;ind>=0;ind--){
            for(int buy = 1;buy>=0;buy--){
                for(int k = 1;k<=cap;k++){
                    int profit = 0;
                    if(buy){
                        // we can only buy here
                        // take or not take this option
                        profit = max(-prices[ind] + dp[ind+1][!buy][k], /*buy the stock transaction is not complete yet therefore k remains k*/
                                                0 + dp[ind+1][buy][k]); // did not buy today
                    }
                    else{
                        profit = max(prices[ind] + dp[ind+1][!buy][k-1], /*sell the stock & trans decreases*/
                                                0 + dp[ind+1][buy][k]); // did not sell today
                    }
                    dp[ind][buy][k] = profit;
                }
            }
        }
        return dp[0][1][cap];
    }
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (k+1,-1)));
        tabulation(k, prices);
        return rec1(0,1,k,prices,dp);
    }
};
```

## Attempt 3 · 2023-05-03 13:08 IST · Wrong Answer · C++

[submission 943679163](https://leetcode.com/submissions/detail/943679163/) · tests 176/210

Failing input:

```text
2
[2,1,4,5,2,9,7]
```

Expected:

```text
11
```

Your output:

```text
10
```

```cpp
class Solution {
public:
int rec1(int ind, bool buy, int k, vector<int> &prices, vector<vector<vector<int>>> &dp){
        if(ind ==prices.size()) return 0;// last indx finished can't buy or sell now
        if(k==0) return 0;

        if(dp[ind][buy][k] != -1) return dp[ind][buy][k];

        int profit = 0;
        if(buy){
            // we can only buy here
            // take or not take this option
            profit = max(-prices[ind] + rec1(ind+1, !buy, k, prices,dp), /*buy the stock transaction is not complete yet therefore k remains k*/
                                    0 + rec1(ind+1, buy, k, prices, dp)); // did not buy today
        }
        else{
            profit = max(prices[ind] + rec1(ind+1, !buy, k-1, prices,dp), /*sell the stock*/
                                    0 + rec1(ind+1, buy, k, prices, dp)); // did not sell today
        }
        return dp[ind][buy][k] = profit;
    }

    int tabulationSpaceOptimized(int cap, vector<int>& prices){
        int n = prices.size();
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>> (2, vector<int> (cap+1,0)));
        vector<vector<int>> prev(2,vector<int>(cap+1,0)), cur(2,vector<int>(cap+1,0));

        for(int buy=0;buy<2;buy++){
            prev[buy][0] = 0;
        }

        for(int i=0;i<2;i++){
            for(int j=0;j<=cap;j++){
                prev[i][j] = 0;
            }
        }
        for(int ind= n-1;ind>=0;ind--){
            for(int buy = 1;buy>=0;buy--){
                for(int k = 1;k<=cap;k++){
                    int profit = 0;
                    if(buy){
                        // we can only buy here
                        // take or not take this option
                        profit = max(-prices[ind] + prev[0][k], /*buy the stock transaction is not complete yet therefore k remains k*/
                                                0 + prev[buy][k]); // did not buy today
                    }
                    else{
                        profit = max(prices[ind] + prev[0][k-1], /*sell the stock & trans decreases*/
                                                0 + prev[buy][k]); // did not sell today
                    }
                    cur[buy][k] = profit;
                }
            }
        }
        return prev[1][cap];
    }

    int tabulation(int cap, vector<int>& prices){
        int n = prices.size();
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>> (2, vector<int> (cap+2,-1)));

        for(int i=0;i<2;i++){
            for(int j=0;j<=cap;j++){
                dp[n][i][j] = 0;
            }
        }
        for(int ind= n-1;ind>=0;ind--){
            for(int buy = 1;buy>=0;buy--){
                for(int k = 1;k<=cap;k++){
                    int profit = 0;
                    if(buy){
                        // we can only buy here
                        // take or not take this option
                        profit = max(-prices[ind] + dp[ind+1][!buy][k], /*buy the stock transaction is not complete yet therefore k remains k*/
                                                0 + dp[ind+1][buy][k]); // did not buy today
                    }
                    else{
                        profit = max(prices[ind] + dp[ind+1][!buy][k-1], /*sell the stock & trans decreases*/
                                                0 + dp[ind+1][buy][k]); // did not sell today
                    }
                    dp[ind][buy][k] = profit;
                }
            }
        }
        return dp[0][1][cap];
    }
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (k+1,-1)));
        return tabulation(k, prices);
        return rec1(0,1,k,prices,dp);
    }
};
```

## Attempt 4 · 2023-05-03 13:16 IST · Accepted · C++

[submission 943682206](https://leetcode.com/submissions/detail/943682206/) · tests 210/210 · runtime 31 ms (beats 12.5%)

```cpp
class Solution {
public:
int rec1(int ind, bool buy, int k, vector<int> &prices, vector<vector<vector<int>>> &dp){
        if(ind ==prices.size()) return 0;// last indx finished can't buy or sell now
        if(k==0) return 0;

        if(dp[ind][buy][k] != -1) return dp[ind][buy][k];

        int profit = 0;
        if(buy){
            // we can only buy here
            // take or not take this option
            profit = max(-prices[ind] + rec1(ind+1, !buy, k, prices,dp), /*buy the stock transaction is not complete yet therefore k remains k*/
                                    0 + rec1(ind+1, buy, k, prices, dp)); // did not buy today
        }
        else{
            profit = max(prices[ind] + rec1(ind+1, !buy, k-1, prices,dp), /*sell the stock*/
                                    0 + rec1(ind+1, buy, k, prices, dp)); // did not sell today
        }
        return dp[ind][buy][k] = profit;
    }

    int tabulationSpaceOptimized(int cap, vector<int>& prices){
        int n = prices.size();
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>> (2, vector<int> (cap+1,0)));
        vector<vector<int>> prev(2,vector<int>(cap+1,0)), cur(2,vector<int>(cap+1,0));

        for(int buy=0;buy<2;buy++){
            prev[buy][0] = 0;
        }

        for(int i=0;i<2;i++){
            for(int j=0;j<=cap;j++){
                prev[i][j] = 0;
            }
        }
        for(int ind= n-1;ind>=0;ind--){
            for(int buy = 1;buy>=0;buy--){
                for(int k = 1;k<=cap;k++){
                    int profit = 0;
                    if(buy){
                        // we can only buy here
                        // take or not take this option
                        profit = max(-prices[ind] + prev[0][k], /*buy the stock transaction is not complete yet therefore k remains k*/
                                                0 + prev[buy][k]); // did not buy today
                    }
                    else{
                        profit = max(prices[ind] + prev[0][k-1], /*sell the stock & trans decreases*/
                                                0 + prev[buy][k]); // did not sell today
                    }
                    cur[buy][k] = profit;
                }
            }
        }
        return prev[1][cap];
    }

    int tabulation(int cap, vector<int>& prices){
        int n = prices.size();
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>> (2, vector<int> (cap+2,0)));

        // for(int i=0;i<=n;i++){
        //     for(int buy=0;buy<2;buy++){
        //         dp[i][buy][0] = 0;
        //     }
        // }
        for(int i=0;i<2;i++){
            for(int j=0;j<=cap;j++){
                dp[n][i][j] = 0;
            }
        }
        for(int ind= n-1;ind>=0;ind--){
            for(int buy = 1;buy>=0;buy--){
                for(int k = 1;k<=cap;k++){
                    int profit = 0;
                    if(buy){
                        // we can only buy here
                        // take or not take this option
                        profit = max(-prices[ind] + dp[ind+1][!buy][k], /*buy the stock transaction is not complete yet therefore k remains k*/
                                                0 + dp[ind+1][buy][k]); // did not buy today
                    }
                    else{
                        profit = max(prices[ind] + dp[ind+1][!buy][k-1], /*sell the stock & trans decreases*/
                                                0 + dp[ind+1][buy][k]); // did not sell today
                    }
                    dp[ind][buy][k] = profit;
                }
            }
        }
        return dp[0][1][cap];
    }
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (k+1,-1)));
        return tabulation(k, prices);
        return rec1(0,1,k,prices,dp);
    }
};
```

## Attempt 5 · 2023-05-03 13:27 IST · Accepted · C++

[submission 943687014](https://leetcode.com/submissions/detail/943687014/) · tests 210/210 · runtime 21 ms (beats 13.6%)

```cpp
class Solution {
public:
int rec1(int ind, bool buy, int k, vector<int> &prices, vector<vector<vector<int>>> &dp){
        if(ind ==prices.size()) return 0;// last indx finished can't buy or sell now
        if(k==0) return 0;

        if(dp[ind][buy][k] != -1) return dp[ind][buy][k];

        int profit = 0;
        if(buy){
            // we can only buy here
            // take or not take this option
            profit = max(-prices[ind] + rec1(ind+1, !buy, k, prices,dp), /*buy the stock transaction is not complete yet therefore k remains k*/
                                    0 + rec1(ind+1, buy, k, prices, dp)); // did not buy today
        }
        else{
            profit = max(prices[ind] + rec1(ind+1, !buy, k-1, prices,dp), /*sell the stock*/
                                    0 + rec1(ind+1, buy, k, prices, dp)); // did not sell today
        }
        return dp[ind][buy][k] = profit;
    }

    int tabulationSpaceOptimized(int cap, vector<int>& prices){
        int n = prices.size();
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>> (2, vector<int> (cap+1,0)));
        vector<vector<int>> prev(2,vector<int>(cap+1,0)), cur(2,vector<int>(cap+1,0));

        for(int buy=0;buy<2;buy++){
            prev[buy][0] = 0;
        }

        for(int i=0;i<2;i++){
            for(int j=0;j<=cap;j++){
                prev[i][j] = 0;
            }
        }
        for(int ind= n-1;ind>=0;ind--){
            for(int buy = 1;buy>=0;buy--){
                for(int k = 1;k<=cap;k++){
                    int profit = 0;
                    if(buy){
                        // we can only buy here
                        // take or not take this option
                        profit = max(-prices[ind] + prev[!buy][k], /*buy the stock transaction is not complete yet therefore k remains k*/
                                                0 + prev[buy][k]); // did not buy today
                    }
                    else{
                        profit = max(prices[ind] + prev[!buy][k-1], /*sell the stock & trans decreases*/
                                                0 + prev[buy][k]); // did not sell today
                    }
                    cur[buy][k] = profit;
                }
            }
            prev = cur;
        }
        return prev[1][cap];
    }

    int tabulation(int cap, vector<int>& prices){
        int n = prices.size();
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>> (2, vector<int> (cap+2,0)));

        // for(int i=0;i<=n;i++){
        //     for(int buy=0;buy<2;buy++){
        //         dp[i][buy][0] = 0;
        //     }
        // }
        for(int i=0;i<2;i++){
            for(int j=0;j<=cap;j++){
                dp[n][i][j] = 0;
            }
        }
        for(int ind= n-1;ind>=0;ind--){
            for(int buy = 1;buy>=0;buy--){
                for(int k = 1;k<=cap;k++){
                    int profit = 0;
                    if(buy){
                        // we can only buy here
                        // take or not take this option
                        profit = max(-prices[ind] + dp[ind+1][!buy][k], /*buy the stock transaction is not complete yet therefore k remains k*/
                                                0 + dp[ind+1][buy][k]); // did not buy today
                    }
                    else{
                        profit = max(prices[ind] + dp[ind+1][!buy][k-1], /*sell the stock & trans decreases*/
                                                0 + dp[ind+1][buy][k]); // did not sell today
                    }
                    dp[ind][buy][k] = profit;
                }
            }
        }
        return dp[0][1][cap];
    }
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (k+1,-1)));
        return tabulationSpaceOptimized(k, prices);
        return tabulation(k, prices);
        return rec1(0,1,k,prices,dp);
    }
};
```
