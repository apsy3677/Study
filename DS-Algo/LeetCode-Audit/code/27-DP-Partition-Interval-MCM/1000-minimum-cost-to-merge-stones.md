# 1000. Minimum Cost to Merge Stones

[Problem](https://leetcode.com/problems/minimum-cost-to-merge-stones/) · Hard · DP: Partition / Interval (MCM) → Interval DP

LeetCode tags: array, dynamic-programming, prefix-sum

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-05-17 14:34 IST · Accepted · C++

[submission 951963971](https://leetcode.com/submissions/detail/951963971/) · tests 84/84 · runtime 49 ms (beats 5.1%)

```cpp
class Solution {
public:
    int rec(int i, int j, int piles, vector<int> &prefix, int k, unordered_map<string, int> &dp){
        if(i>=j) return 0;
        string key = to_string(i) + '|' + to_string(j) + '|' + to_string(piles);
        if(dp.find(key) != dp.end()) return dp[key];
        int ans = 1e8;

        for(int ind = i;ind<j;ind += k-1){
            int tmp = rec(i, ind, piles, prefix, k, dp) + rec(ind+1, j, piles, prefix, k, dp);
            ans = min(ans, tmp);
        }
        if((j-i)%(k-1)==0){
            ans += prefix[j+1]-prefix[i];
        }
        
        return dp[key] = ans;
    }
    int mergeStones(vector<int>& stones, int k) {
        int n = stones.size();
        if( (n-1)%(k-1) != 0) return -1;

        vector<int> prefix(n+1, 0);
        for(int i=1;i<=n;i++){
            prefix[i] = stones[i-1] + prefix[i-1] ;
        }
        unordered_map<string, int> dp;
        // prefix [i] = sum of elemtns ffrom index 0 to i

        int ans = 1e8;
        ans = rec(0, n-1, k, prefix, k, dp);

        return ans;
    }
};
```
