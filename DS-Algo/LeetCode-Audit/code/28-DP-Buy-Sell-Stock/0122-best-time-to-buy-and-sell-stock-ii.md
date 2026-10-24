# 122. Best Time to Buy and Sell Stock II

[Problem](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/) · Medium · DP: Buy & Sell Stock → Unlimited transactions

LeetCode tags: array, dynamic-programming, greedy

Attempts since Mar 2023: 7 · accepted: 6 · failed before first AC: 0

## Attempt 1 · 2023-03-13 18:39 IST · Accepted · C++

[submission 914371049](https://leetcode.com/submissions/detail/914371049/) · tests 200/200 · runtime 18 ms (beats 5.1%)

```cpp
class Solution {
public:
    int rec(int n, int buy, vector<int> &prices, vector<vector<int>> &dp){
        if(n >= prices.size())
            return 0; // after day n 0 profit
        int f1 = 0, f2 =0;

        if(dp[n][buy] != -1){
            return dp[n][buy];
        }

        if(buy ==0){
            f1 = 0+ rec(n+1, 0, prices, dp);
            f2 = -prices[n]+ rec(n+1, 1, prices, dp); // sell
        }
        if(buy ==1){
            f1 = 0+ rec(n+1, 1, prices, dp);
            f2 = prices[n]+ rec(n+1, 0, prices, dp);
        }
        return dp[n][buy] = max(f1, f2);
    }
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n==0)
            return 0;
        vector<vector<int>> dp (n+1, vector<int> (2, -1));

        return rec(0, 0, prices, dp);
    }
};
```

## Attempt 2 · 2023-03-13 18:40 IST · Accepted · C++

[submission 914371469](https://leetcode.com/submissions/detail/914371469/) · tests 200/200 · runtime 16 ms (beats 8.1%)

```cpp
class Solution {
public:
    int rec(int n, int buy, vector<int> &prices, vector<vector<int>> &dp){
        if(n >= prices.size())
            return 0; // after day n 0 profit
        int f1 = 0, f2 =0;

        if(dp[n][buy] != -1){
            return dp[n][buy];
        }

        if(buy ==0){
            f1 = 0+ rec(n+1, 0, prices, dp);
            f2 = -prices[n]+ rec(n+1, 1, prices, dp); // sell
        }
        if(buy ==1){
            f1 = 0+ rec(n+1, 1, prices, dp);
            f2 = prices[n]+ rec(n+1, 0, prices, dp);
        }
        return dp[n][buy] = max(f1, f2);
    }
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        // if(n==0)
        //     return 0;
        vector<vector<int>> dp (n+1, vector<int> (2, -1));

        return rec(0, 0, prices, dp);
    }
};
```

## Attempt 3 · 2023-03-13 18:54 IST · Accepted · C++

[submission 914377601](https://leetcode.com/submissions/detail/914377601/) · tests 200/200 · runtime 11 ms (beats 26.7%)

```cpp
class Solution {
public:
    int rec(int n, int buy, vector<int> &prices, vector<vector<int>> &dp){
        if(n >= prices.size())
            return 0; // after day n 0 profit
        int f1 = 0, f2 =0;

        if(dp[n][buy] != -1){
            return dp[n][buy];
        }

        if(buy ==0){
            f1 = 0+ rec(n+1, 0, prices, dp);
            f2 = -prices[n]+ rec(n+1, 1, prices, dp); // sell
        }
        if(buy ==1){
            f1 = 0+ rec(n+1, 1, prices, dp);
            f2 = prices[n]+ rec(n+1, 0, prices, dp);
        }
        return dp[n][buy] = max(f1, f2);
    }

    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n==0)
            return 0;

        int peak = prices[0], valley = prices[0], prof =0;

        int i=0;

        while(i < n-1){
            while(i<n-1 && prices[i]>=prices[i+1])
                i++;
            valley = prices[i];
            while(i<n-1 && prices[i] <= prices[i+1])
                i++;
            
            peak = prices[i];
            prof += peak -valley;
        }
        return prof;

        // vector<vector<int>> dp (n+1, vector<int> (2, -1));

        // return rec(0, 0, prices, dp);
    }
};
```

## Attempt 4 · 2023-05-03 11:55 IST · Time Limit Exceeded · C++

[submission 943647202](https://leetcode.com/submissions/detail/943647202/) · tests 198/200

Failing input:

```text
[397,6621,4997,7506,8918,1662,9187,3278,3890,514,18,9305,93,5508,3031,2692,6019,1134,1691,4949,5071,799,8953,7882,4273,302,6753,4657,8368,3942,1982,5117,563,3332,2623,9482,4994,8163,9112,5236,5029,5483,4542,1474,991,3925,4166,3362,5059,5857,4663,6482,3008,3616,4365,3634,270,1118,8291,4990,1413,273,107,1976,9957,9083,7810,4952,7246,3275,6540,2275,8758,7434,3750,6101,1359,4268,5815,2771,126,478,9253 ... [4497 more chars]
```

Expected:

```text
1697678
```

```cpp
class Solution {
public:
    int rec(int n, int buy, vector<int> &prices, vector<vector<int>> &dp){
        if(n >= prices.size())
            return 0; // after day n 0 profit
        int f1 = 0, f2 =0;

        if(dp[n][buy] != -1){
            return dp[n][buy];
        }

        if(buy ==0){
            f1 = 0+ rec(n+1, 0, prices, dp);
            f2 = -prices[n]+ rec(n+1, 1, prices, dp); // sell
        }
        if(buy ==1){
            f1 = 0+ rec(n+1, 1, prices, dp);
            f2 = prices[n]+ rec(n+1, 0, prices, dp);
        }
        return dp[n][buy] = max(f1, f2);
    }

    int rec1(int ind, bool buy, vector<int> &prices, vector<vector<int>> &dp){
        if(ind ==prices.size()) return 0;// last indx finished can't buy or sell now

        int profit = 0;
        if(buy){
            // we can only buy here
            // take or not take this option
            profit = max(-prices[ind] + rec1(ind+1, !buy, prices,dp), /*buy the stock*/
                                    0 + rec1(ind+1, buy, prices, dp)); // did not buy today
        }
        else{
            profit = max(prices[ind] + rec1(ind+1, !buy, prices,dp), /*sell the stock*/
                                    0 + rec1(ind+1, buy, prices, dp)); // did not sell today
        }
        return profit;
    }

    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n==0)
            return 0;

        // int peak = prices[0], valley = prices[0], prof =0;

        // int i=0;

        // while(i < n-1){
        //     while(i<n-1 && prices[i]>=prices[i+1])
        //         i++;
        //     valley = prices[i];
        //     while(i<n-1 && prices[i] <= prices[i+1])
        //         i++;
            
        //     peak = prices[i];
        //     prof += peak -valley;
        // }
        // return prof;

        vector<vector<int>> dp (n+1, vector<int> (2, -1));

        return rec1(0, 1, prices, dp);
    }
};
```

## Attempt 5 · 2023-05-03 11:58 IST · Accepted · C++

[submission 943648381](https://leetcode.com/submissions/detail/943648381/) · tests 200/200 · runtime 12 ms (beats 20.9%)

```cpp
class Solution {
public:
    int rec(int n, int buy, vector<int> &prices, vector<vector<int>> &dp){
        if(n >= prices.size())
            return 0; // after day n 0 profit
        int f1 = 0, f2 =0;

        if(dp[n][buy] != -1){
            return dp[n][buy];
        }

        if(buy ==0){
            f1 = 0+ rec(n+1, 0, prices, dp);
            f2 = -prices[n]+ rec(n+1, 1, prices, dp); // sell
        }
        if(buy ==1){
            f1 = 0+ rec(n+1, 1, prices, dp);
            f2 = prices[n]+ rec(n+1, 0, prices, dp);
        }
        return dp[n][buy] = max(f1, f2);
    }

    int rec1(int ind, bool buy, vector<int> &prices, vector<vector<int>> &dp){
        if(ind ==prices.size()) return 0;// last indx finished can't buy or sell now

        if(dp[ind][buy] != -1) return dp[ind][buy];

        int profit = 0;
        if(buy){
            // we can only buy here
            // take or not take this option
            profit = max(-prices[ind] + rec1(ind+1, !buy, prices,dp), /*buy the stock*/
                                    0 + rec1(ind+1, buy, prices, dp)); // did not buy today
        }
        else{
            profit = max(prices[ind] + rec1(ind+1, !buy, prices,dp), /*sell the stock*/
                                    0 + rec1(ind+1, buy, prices, dp)); // did not sell today
        }
        return dp[ind][buy] = profit;
    }

    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n==0)
            return 0;

        // int peak = prices[0], valley = prices[0], prof =0;

        // int i=0;

        // while(i < n-1){
        //     while(i<n-1 && prices[i]>=prices[i+1])
        //         i++;
        //     valley = prices[i];
        //     while(i<n-1 && prices[i] <= prices[i+1])
        //         i++;
            
        //     peak = prices[i];
        //     prof += peak -valley;
        // }
        // return prof;

        vector<vector<int>> dp (n+1, vector<int> (2, -1));

        return rec1(0, 1, prices, dp);
        // return rec(0, 0, prices, dp);
    }
};
```

## Attempt 6 · 2023-05-03 11:58 IST · Accepted · C++

[submission 943648655](https://leetcode.com/submissions/detail/943648655/) · tests 200/200 · runtime 22 ms (beats 5.1%)

```cpp
class Solution {
public:
    int rec(int n, int buy, vector<int> &prices, vector<vector<int>> &dp){
        if(n >= prices.size())
            return 0; // after day n 0 profit
        int f1 = 0, f2 =0;

        if(dp[n][buy] != -1){
            return dp[n][buy];
        }

        if(buy ==0){
            f1 = 0+ rec(n+1, 0, prices, dp);
            f2 = -prices[n]+ rec(n+1, 1, prices, dp); // sell
        }
        if(buy ==1){
            f1 = 0+ rec(n+1, 1, prices, dp);
            f2 = prices[n]+ rec(n+1, 0, prices, dp);
        }
        return dp[n][buy] = max(f1, f2);
    }

    int rec1(int ind, bool buy, vector<int> &prices, vector<vector<int>> &dp){
        if(ind ==prices.size()) return 0;// last indx finished can't buy or sell now

        if(dp[ind][buy] != -1) return dp[ind][buy];

        int profit = 0;
        if(buy){
            // we can only buy here
            // take or not take this option
            profit = max(-prices[ind] + rec1(ind+1, !buy, prices,dp), /*buy the stock*/
                                    0 + rec1(ind+1, buy, prices, dp)); // did not buy today
        }
        else{
            profit = max(prices[ind] + rec1(ind+1, !buy, prices,dp), /*sell the stock*/
                                    0 + rec1(ind+1, buy, prices, dp)); // did not sell today
        }
        return dp[ind][buy] = profit;
    }

    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        // int peak = prices[0], valley = prices[0], prof =0;

        // int i=0;

        // while(i < n-1){
        //     while(i<n-1 && prices[i]>=prices[i+1])
        //         i++;
        //     valley = prices[i];
        //     while(i<n-1 && prices[i] <= prices[i+1])
        //         i++;
            
        //     peak = prices[i];
        //     prof += peak -valley;
        // }
        // return prof;

        vector<vector<int>> dp (n+1, vector<int> (2, -1));

        return rec1(0, 1, prices, dp);
        // return rec(0, 0, prices, dp);
    }
};
```

## Attempt 7 · 2023-05-03 12:15 IST · Accepted · C++

[submission 943656453](https://leetcode.com/submissions/detail/943656453/) · tests 200/200 · runtime 20 ms (beats 5.1%)

```cpp
class Solution {
public:
    int rec(int n, int buy, vector<int> &prices, vector<vector<int>> &dp){
        if(n >= prices.size())
            return 0; // after day n 0 profit
        int f1 = 0, f2 =0;

        if(dp[n][buy] != -1){
            return dp[n][buy];
        }

        if(buy ==0){
            f1 = 0+ rec(n+1, 0, prices, dp);
            f2 = -prices[n]+ rec(n+1, 1, prices, dp); // sell
        }
        if(buy ==1){
            f1 = 0+ rec(n+1, 1, prices, dp);
            f2 = prices[n]+ rec(n+1, 0, prices, dp);
        }
        return dp[n][buy] = max(f1, f2);
    }

    int rec1(int ind, bool buy, vector<int> &prices, vector<vector<int>> &dp){
        if(ind ==prices.size()) return 0;// last indx finished can't buy or sell now

        if(dp[ind][buy] != -1) return dp[ind][buy];

        int profit = 0;
        if(buy){
            // we can only buy here
            // take or not take this option
            profit = max(-prices[ind] + rec1(ind+1, !buy, prices,dp), /*buy the stock*/
                                    0 + rec1(ind+1, buy, prices, dp)); // did not buy today
        }
        else{
            profit = max(prices[ind] + rec1(ind+1, !buy, prices,dp), /*sell the stock*/
                                    0 + rec1(ind+1, buy, prices, dp)); // did not sell today
        }
        return dp[ind][buy] = profit;
    }

    int tabulationSpaceOptimized(vector<int>& prices) {
        int n = prices.size();

        vector<vector<int>> dp(n+1, vector<int> (2,0));
        vector<int> prev(2,0), cur(2,0);
        prev[0] = prev[1] = 0;

        for(int ind= n-1;ind>=0;ind--){
            for(int buy = 0;buy<2;buy++){
                int profit = 0;
                if(buy == 1){
                    // we can only buy here
                    // take or not take this option
                    profit = max(-prices[ind] + prev[0], /*buy the stock*/
                                            0 + prev[1]); // did not buy today
                }
                else{
                    profit = max(prices[ind] + prev[1], /*sell the stock*/
                                        0    + prev[0]); // did not sell today
                }
                cur[buy] = profit;
            }
            prev = cur;
        }
        return prev[1]; // as we called function in rec like rec1(0,1)
    }

    int tabulation(vector<int>& prices) {
        int n = prices.size();

        vector<vector<int>> dp(n+1, vector<int> (2,0));
        dp[n][0] = dp[n][1] = 0;

        for(int ind= n-1;ind>=0;ind--){
            for(int buy = 0;buy<2;buy++){
                int profit = 0;
                if(buy == 1){
                    // we can only buy here
                    // take or not take this option
                    profit = max(-prices[ind] + dp[ind+1][0], /*buy the stock*/
                                            0 + dp[ind+1][1]); // did not buy today
                }
                else{
                    profit = max(prices[ind] + dp[ind+1][1], /*sell the stock*/
                                        0    + dp[ind+1][0]); // did not sell today
                }
                dp[ind][buy] = profit;
            }
        }
        return dp[0][1]; // as we called function in rec like rec1(0,1)
    }
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp (n+1, vector<int> (2, -1));

        // return rec1(0, 1, prices, dp);

        // Tabulation

        return tabulationSpaceOptimized(prices);
        // return tabulation(prices);


        // return rec(0, 0, prices, dp);

        // int peak = prices[0], valley = prices[0], prof =0;

        // int i=0;

        // while(i < n-1){
        //     while(i<n-1 && prices[i]>=prices[i+1])
        //         i++;
        //     valley = prices[i];
        //     while(i<n-1 && prices[i] <= prices[i+1])
        //         i++;
            
        //     peak = prices[i];
        //     prof += peak -valley;
        // }
        // return prof;

        
    }
};
```
