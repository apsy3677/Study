# 121. Best Time to Buy and Sell Stock

[Problem](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) · Easy · DP: Buy & Sell Stock → Single transaction

LeetCode tags: array, dynamic-programming

Attempts since Mar 2023: 7 · accepted: 6 · failed before first AC: 0

## Attempt 1 · 2023-03-13 18:10 IST · Accepted · C++

[submission 914358315](https://leetcode.com/submissions/detail/914358315/) · tests 211/211 · runtime 142 ms (beats 6.6%)

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<int> profit(n, 0);
        profit[0] = prices[0];
        int ans = 0;
        for(int i=1;i<prices.size();i++){
            ans = max(ans, prices[i] - profit[i-1]);
            profit[i] = min(prices[i],profit[i-1]);
            
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-03-13 18:12 IST · Accepted · C++

[submission 914359211](https://leetcode.com/submissions/detail/914359211/) · tests 211/211 · runtime 149 ms (beats 6.6%)

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int ans = 0, mini =prices[0];
        for(int i=1;i<prices.size();i++){
            ans = max(ans, prices[i] - mini);
            mini = min(mini, prices[i]);
            
        }
        return ans;
    }
};
```

## Attempt 3 · 2024-03-18 00:32 IST · Wrong Answer · Python3

[submission 1206590419](https://leetcode.com/submissions/detail/1206590419/) · tests 89/212

Failing input:

```text
[7,1,5,3,6,4]
```

Expected:

```text
5
```

Your output:

```text
3
```

```python
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        min_price = float('inf')
        max_profit = 0         
        for price in prices:
            if price < min_price:
                min_price = price
            else:
                max_profit = price - min_price
            print(min_price,max_profit)
        return max_profit
```

## Attempt 4 · 2024-03-18 00:32 IST · Accepted · Python3

[submission 1206590904](https://leetcode.com/submissions/detail/1206590904/) · tests 212/212 · runtime 703 ms (beats 5.0%)

```python
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        min_price = float('inf')
        max_profit = 0         
        for price in prices:
            if price < min_price:
                min_price = price
            else:
                if price - min_price > max_profit:
                    max_profit = price - min_price
            # print(min_price,max_profit)
        return max_profit
```

## Attempt 5 · 2025-03-22 06:43 IST · Accepted · C++

[submission 1581831075](https://leetcode.com/submissions/detail/1581831075/) · tests 212/212 · runtime 7 ms (beats 6.6%)

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int profit = 0;
        vector<int> rightMax(prices.size());
        int maxx = INT_MIN;
        for(int i= prices.size()-1 ; i>=0 ; i--) {
            maxx = max(maxx, prices[i]);
            rightMax[i] = maxx;
        }
        for(int i =0;i<prices.size();i++) {
            profit = max(profit, rightMax[i] - prices[i]);
        }
        return profit;
    }
};
```

## Attempt 6 · 2025-07-07 22:36 IST · Accepted · C++

[submission 1689835363](https://leetcode.com/submissions/detail/1689835363/) · tests 212/212 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
    
        int minPrice = INT_MAX;
        int maxProfit = 0;
        
        for (int price : prices) {
            // Update minimum price seen so far
            minPrice = min(minPrice, price);
            
            // Update maximum profit if selling at current price
            maxProfit = max(maxProfit, price - minPrice);
        }
        
        return maxProfit;
    }
};
```

## Attempt 7 · 2025-07-07 23:08 IST · Accepted · C++

[submission 1689878369](https://leetcode.com/submissions/detail/1689878369/) · tests 212/212 · runtime 4 ms (beats 17.0%)

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
    
        int minPrice = INT_MAX;
        int maxProfit = 0;
        
        for (int price : prices) {
            // Update minimum price seen so far
            minPrice = min(minPrice, price);
            
            // Update maximum profit if selling at current price
            maxProfit = max(maxProfit, price - minPrice);
        }
        
        return maxProfit;
    }
};
```
