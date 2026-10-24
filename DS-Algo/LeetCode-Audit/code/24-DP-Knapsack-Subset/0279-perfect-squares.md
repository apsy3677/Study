# 279. Perfect Squares

[Problem](https://leetcode.com/problems/perfect-squares/) · Medium · DP: Knapsack / Subset → Unbounded, min count

LeetCode tags: math, dynamic-programming, breadth-first-search, knapsack-problem, complete-knapsack

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-03-23 15:05 IST · Accepted · C++

[submission 920629581](https://leetcode.com/submissions/detail/920629581/) · tests 588/588 · runtime 5 ms (beats 96.3%)

```cpp
class Solution {
public:
    bool isSquare(int n){
        for(int i=1;i*i <=n ; i++){
            if(i*i == n) 
                return true;  
        }
        return false;
        // int sq= sqrt(n);
        // return n == sq*sq;
    }
    int numSquares(int n) {
        
        while(n%4 ==0)
            n=n/4;
        if(n%8 ==7) 
            return 4;
        
        if(isSquare(n))
            return 1;
        
        for(int i=1;i*i<=n;i++){
            if(isSquare(n-i*i))
                return 2;
        }
        return 3;
    }
};
```

## Attempt 2 · 2023-03-23 15:17 IST · Accepted · C++

[submission 920634738](https://leetcode.com/submissions/detail/920634738/) · tests 588/588 · runtime 348 ms (beats 10.3%)

```cpp
class Solution {
public:
    bool isSquare(int n){
        for(int i=1;i*i <=n ; i++){
            if(i*i == n) 
                return true;  
        }
        return false;
        // int sq= sqrt(n);
        // return n == sq*sq;
    }
    int ansAlgo(int n){
        while(n%4 ==0)
            n=n/4;
        if(n%8 ==7) 
            return 4;
        
        if(isSquare(n))
            return 1;
        
        for(int i=1;i*i<=n;i++){
            if(isSquare(n-i*i))
                return 2;
        }
        return 3;
    }
    int numSquares(int n) {
        vector<int> dp(n+1, INT_MAX);
        int s_n = (int)sqrt(n) +1;

        vector<int> sq(s_n);

        for(int i=1;i*i <=n;i++){
            sq[i] = i*i;
        }
        dp[0]=0;
        for(int i=1;i<=n;i++){
            
            for(int j=1;j<s_n;j++){
                if(sq[j] > i){
                    break;
                }
                dp[i] = min(dp[i], 1+ dp[i-sq[j]]);
            }
        }
        return dp[n];
    }
};
```

## Attempt 3 · 2023-03-23 15:29 IST · Accepted · C++

[submission 920639644](https://leetcode.com/submissions/detail/920639644/) · tests 588/588 · runtime 349 ms (beats 10.3%)

```cpp
class Solution {
public:
    bool isSquare(int n){
        for(int i=1;i*i <=n ; i++){
            if(i*i == n) 
                return true;  
        }
        return false;
        // int sq= sqrt(n);
        // return n == sq*sq;
    }
    int ansAlgo(int n){
        while(n%4 ==0)
            n=n/4;
        if(n%8 ==7) 
            return 4;
        
        if(isSquare(n))
            return 1;
        
        for(int i=1;i*i<=n;i++){
            if(isSquare(n-i*i))
                return 2;
        }
        return 3;
    }
    int numSquares(int n) {
        vector<int> dp(n+1, INT_MAX);
        int s_n = (int)sqrt(n) +1;

        vector<int> sq(s_n);

        for(int i=1;i*i <=n;i++){
            sq[i] = i*i;
        }
        dp[0]=0;
        for(int i=1;i<=n;i++){
            
            for(int j=1;j<s_n;j++){
                if(sq[j] > i){
                    break;
                }
                dp[i] = min(dp[i], 1+ dp[i-sq[j]]);
            }
        }
        return dp[n];
    }
};
```
