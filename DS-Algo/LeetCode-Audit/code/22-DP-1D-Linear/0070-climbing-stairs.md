# 70. Climbing Stairs

[Problem](https://leetcode.com/problems/climbing-stairs/) · Easy · DP: 1D / Linear → Fibonacci

LeetCode tags: math, dynamic-programming, memoization

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2023-03-11 09:51 IST · Wrong Answer · C++

[submission 913013853](https://leetcode.com/submissions/detail/913013853/) · tests 43/45

Failing input:

```text
44
```

Expected:

```text
1134903170
```

Your output:

```text
134903163
```

```cpp
class Solution {

private:
long long mod = 1000000007;
const static int N = 100007;
int dp[N];
public:


int recursive(int n){
    if(n<=1)
        return 1;
    if(dp[n]!= -1)
        return dp[n];
    
    dp[n] = (recursive(n-1) + recursive(n-2))%mod ;

    return dp[n];
}
    int climbStairs(int n) {
        std::fill(dp, dp+n+1, -1);
        return recursive(n);
    }
};
```

## Attempt 2 · 2023-03-11 09:52 IST · Accepted · C++

[submission 913014080](https://leetcode.com/submissions/detail/913014080/) · tests 45/45 · runtime 0 ms (beats 100%)

```cpp
class Solution {

private:
long long mod = 1000000007;
const static int N = 100007;
int dp[N];
public:


int recursive(int n){
    if(n<=1)
        return 1;
    if(dp[n]!= -1)
        return dp[n];
    
    dp[n] = (recursive(n-1) + recursive(n-2));

    return dp[n];
}
    int climbStairs(int n) {
        std::fill(dp, dp+n+1, -1);
        return recursive(n);
    }
};
```
