# 123. Best Time to Buy and Sell Stock III

[Problem](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/) · Hard · DP: Buy & Sell Stock → At most 2 transactions

LeetCode tags: array, dynamic-programming

Attempts since Mar 2023: 5 · accepted: 5 · failed before first AC: 0

## Attempt 1 · 2023-05-03 12:36 IST · Accepted · C++

[submission 943665836](https://leetcode.com/submissions/detail/943665836/) · tests 214/214 · runtime 781 ms (beats 5.0%)

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
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (3,-1)));

        return rec1(0,1,2,prices,dp);
    }
};
```

## Attempt 2 · 2023-05-03 12:54 IST · Accepted · C++

[submission 943673522](https://leetcode.com/submissions/detail/943673522/) · tests 214/214 · runtime 1556 ms (beats 5.0%)

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
    int tabulation(int cap, vector<int>& prices){
        int n = prices.size();
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>> (2, vector<int> (cap+1,0)));

        for(int i=0;i<=n;i++){
            for(int buy=0;buy<2;buy++){
                dp[i][buy][0] = 0;
            }
        }

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
                        profit = max(-prices[ind] + dp[ind+1][0][k], /*buy the stock transaction is not complete yet therefore k remains k*/
                                                0 + dp[ind+1][buy][k]); // did not buy today
                    }
                    else{
                        profit = max(prices[ind] + dp[ind+1][0][k-1], /*sell the stock & trans decreases*/
                                                0 + dp[ind+1][buy][k]); // did not sell today
                    }
                    dp[ind][buy][k] = profit;
                }
            }
        }
        return dp[0][1][cap];
    }
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (2+1,-1)));
        tabulation(2, prices);

        return rec1(0,1,2,prices,dp);
    }
};
```

## Attempt 3 · 2023-05-03 13:03 IST · Accepted · C++

[submission 943677205](https://leetcode.com/submissions/detail/943677205/) · tests 214/214 · runtime 1406 ms (beats 5.0%)

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
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>> (2, vector<int> (cap+1,0)));

        for(int i=0;i<=n;i++){
            for(int buy=0;buy<2;buy++){
                dp[i][buy][0] = 0;
            }
        }

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
                        profit = max(-prices[ind] + dp[ind+1][0][k], /*buy the stock transaction is not complete yet therefore k remains k*/
                                                0 + dp[ind+1][buy][k]); // did not buy today
                    }
                    else{
                        profit = max(prices[ind] + dp[ind+1][0][k-1], /*sell the stock & trans decreases*/
                                                0 + dp[ind+1][buy][k]); // did not sell today
                    }
                    dp[ind][buy][k] = profit;
                }
            }
        }
        return dp[0][1][cap];
    }
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (2+1,-1)));
        tabulationSpaceOptimized(2, prices);

        return rec1(0,1,2,prices,dp);
    }
};
```

## Attempt 4 · 2023-05-03 13:10 IST · Accepted · C++

[submission 943680000](https://leetcode.com/submissions/detail/943680000/) · tests 214/214 · runtime 1342 ms (beats 5.0%)

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
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>> (2, vector<int> (cap+1,0)));

        for(int i=0;i<=n;i++){
            for(int buy=0;buy<2;buy++){
                dp[i][buy][0] = 0;
            }
        }

        for(int i=0;i<2;i++){
            for(int j=0;j<=cap;j++){
                dp[n][i][j] = 0;
            }
        }
        for(int ind= n-1;ind>=0;ind--){
            for(int buy = 0;buy<2;buy++){
                for(int k = 1;k<=cap;k++){
                    int profit = 0;
                    if(buy){
                        // we can only buy here
                        // take or not take this option
                        profit = max(-prices[ind] + dp[ind+1][0][k], /*buy the stock transaction is not complete yet therefore k remains k*/
                                                0 + dp[ind+1][buy][k]); // did not buy today
                    }
                    else{
                        profit = max(prices[ind] + dp[ind+1][1][k-1], /*sell the stock & trans decreases*/
                                                0 + dp[ind+1][buy][k]); // did not sell today
                    }
                    dp[ind][buy][k] = profit;
                }
            }
        }
        return dp[0][1][cap];
    }
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (2+1,-1)));
        return tabulation(2, prices);
        return tabulationSpaceOptimized(2, prices);

        return rec1(0,1,2,prices,dp);
    }
};
```

## Attempt 5 · 2023-05-03 13:17 IST · Accepted · C++

[submission 943682793](https://leetcode.com/submissions/detail/943682793/) · tests 214/214 · runtime 759 ms (beats 5.0%)

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
    int tabulationSpaceOptimized(int cap, vector<int>& prices){
        int n = prices.size();
        // vector<vector<vector<int>>> dp(n+1, vector<vector<int>> (2, vector<int> (cap+1,0)));
        vector<vector<int>> prev(2, vector<int> (cap+1,0)), cur(2, vector<int> (cap+1,0));
        for(int buy=0;buy<2;buy++){
            prev[buy][0] = 0;
        }

        for(int i=0;i<2;i++){
            for(int j=0;j<=cap;j++){
                prev[i][j] = 0;
            }
        }
        for(int ind= n-1;ind>=0;ind--){
            for(int buy = 0;buy<2;buy++){
                for(int k = 1;k<=cap;k++){
                    int profit = 0;
                    if(buy){
                        // we can only buy here
                        // take or not take this option
                        profit = max(-prices[ind] + prev[0][k], /*buy the stock transaction is not complete yet therefore k remains k*/
                                                0 + prev[buy][k]); // did not buy today
                    }
                    else{
                        profit = max(prices[ind] + prev[1][k-1], /*sell the stock & trans decreases*/
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
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>> (2, vector<int> (cap+1,0)));

        for(int i=0;i<=n;i++){
            for(int buy=0;buy<2;buy++){
                dp[i][buy][0] = 0;
            }
        }

        for(int i=0;i<2;i++){
            for(int j=0;j<=cap;j++){
                dp[n][i][j] = 0;
            }
        }
        for(int ind= n-1;ind>=0;ind--){
            for(int buy = 0;buy<2;buy++){
                for(int k = 1;k<=cap;k++){
                    int profit = 0;
                    if(buy){
                        // we can only buy here
                        // take or not take this option
                        profit = max(-prices[ind] + dp[ind+1][0][k], /*buy the stock transaction is not complete yet therefore k remains k*/
                                                0 + dp[ind+1][buy][k]); // did not buy today
                    }
                    else{
                        profit = max(prices[ind] + dp[ind+1][1][k-1], /*sell the stock & trans decreases*/
                                                0 + dp[ind+1][buy][k]); // did not sell today
                    }
                    dp[ind][buy][k] = profit;
                }
            }
        }
        return dp[0][1][cap];
    }
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (2+1,-1)));
        // return tabulation(2, prices);
        return tabulationSpaceOptimized(2, prices);

        return rec1(0,1,2,prices,dp);
    }
};
```
