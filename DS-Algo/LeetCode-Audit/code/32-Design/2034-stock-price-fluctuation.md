# 2034. Stock Price Fluctuation 

[Problem](https://leetcode.com/problems/stock-price-fluctuation/) · Medium · Design → Map + lazy heaps

LeetCode tags: hash-table, design, heap-priority-queue, data-stream, ordered-set

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-25 02:20 IST · Accepted · C++

[submission 921515192](https://leetcode.com/submissions/detail/921515192/) · tests 18/18 · runtime 529 ms (beats 5.1%)

```cpp
class StockPrice {
    int latestTime;
    map<int,int> timeStampPriceMap;
    map<int,int> priceFreq;
public:
    StockPrice() {
        latestTime =0;
    }
    
    void update(int timestamp, int price) {
        latestTime = max(latestTime, timestamp);

        if(timeStampPriceMap.count(timestamp) !=0){
            int oldPrice = timeStampPriceMap[timestamp];
            priceFreq[oldPrice]--;
            if(priceFreq[oldPrice] == 0){
                priceFreq.erase(oldPrice);
            }
        }
        //
        timeStampPriceMap[timestamp] = price;
        priceFreq[price]++;
    }
    
    int current() {
        return timeStampPriceMap[latestTime];
    }
    
    int maximum() {
        return priceFreq.rbegin()->first;
    }
    
    int minimum() {
        return priceFreq.begin()->first;
    }
};

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */
```
