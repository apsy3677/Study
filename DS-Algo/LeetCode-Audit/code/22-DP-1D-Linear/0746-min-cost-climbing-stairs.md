# 746. Min Cost Climbing Stairs

[Problem](https://leetcode.com/problems/min-cost-climbing-stairs/) · Easy · DP: 1D / Linear → Stairs

LeetCode tags: array, dynamic-programming

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2025-01-24 14:48 IST · Time Limit Exceeded · C++

[submission 1518876174](https://leetcode.com/submissions/detail/1518876174/) · tests 259/285

Failing input:

```text
[841,462,566,398,243,248,238,650,989,576,361,126,334,729,446,897,953,38,195,679,65,707,196,705,569,275,259,872,630,965,978,109,56,523,851,887,91,544,598,963,305,481,959,560,454,883,50,216,732,572,511,156,177,831,122,667,548,978,771,880,922,777,990,498,525,317,469,151,874,202,519,139,670,341,514,469,858,913,94,849,839,813,664,163,3,802,21,634,944,901,446,186,843,742,330,610,932,614,625,169,833,4,81 ... [3491 more chars]
```

Expected:

```text
209040
```

```cpp
class Solution {
public:
int rec(int start, vector<int>& cost) {
    if (start >= cost.size()) {
        return 0;
    }
    int step1 = cost[start] + rec(start+1, cost);
    int step2 = cost[start] + rec(start+2, cost);

    return min(step1, step2);
}
    int minCostClimbingStairs(vector<int>& cost) {
        return min(rec(0, cost), rec(1,cost));
    }
};
```

## Attempt 2 · 2025-01-24 14:53 IST · Accepted · C++

[submission 1518880175](https://leetcode.com/submissions/detail/1518880175/) · tests 285/285 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
int rec(int start, vector<int>& cost, vector<int>& dp) {
    if (start >= cost.size()) {
        return 0;
    }
    if (dp[start] != -1) {
        return dp[start];
    }
    int step1 = cost[start] + rec(start+1, cost, dp);
    int step2 = cost[start] + rec(start+2, cost, dp);

    return dp[start] = min(step1, step2);
}
    int minCostClimbingStairs(vector<int>& cost) {
        vector<int> dp(cost.size(), -1);
        return min(rec(0, cost, dp), rec(1,cost, dp));
    }
};
```
