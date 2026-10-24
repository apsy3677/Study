# 1561. Maximum Number of Coins You Can Get

[Problem](https://leetcode.com/problems/maximum-number-of-coins-you-can-get/) · Medium · Greedy → Sort + pick

LeetCode tags: array, math, greedy, sorting, game-theory

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-05-02 17:55 IST · Accepted · C++

[submission 943198196](https://leetcode.com/submissions/detail/943198196/) · tests 116/116 · runtime 148 ms (beats 5.0%)

```cpp
class Solution {
public:
    int maxCoins(vector<int>& piles) {
        sort(piles.begin(), piles.end());
        int ans =0;
        int n = piles.size();
        for(int i=n/3;i<piles.size();i+=2){
            ans += piles[i];
        }
        return ans;
    }
};
```
