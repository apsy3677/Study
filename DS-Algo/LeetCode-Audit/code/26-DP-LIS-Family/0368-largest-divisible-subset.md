# 368. Largest Divisible Subset

[Problem](https://leetcode.com/problems/largest-divisible-subset/) · Medium · DP: LIS Family → LIS variant + reconstruction

LeetCode tags: array, math, dynamic-programming, sorting

Attempts since Mar 2023: 3 · accepted: 2 · failed before first AC: 1

## Attempt 1 · 2023-04-03 00:54 IST · Wrong Answer · C++

[submission 926808530](https://leetcode.com/submissions/detail/926808530/) · tests 26/49

Failing input:

```text
[5,9,18,54,108,540,90,180,360,720]
```

Expected:

```text
[9,18,90,180,360,720]
```

Your output:

```text
[9,18,54,108,540,90,180,360,720]
```

```cpp
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& arr) {
        int n = arr.size();
        vector<int> dp(n,1);
        vector<int> hash(n,1);
        
        for(int i=0; i<=n-1; i++){
            
            hash[i] = i; // initializing with current index
            for(int prev_index = 0; prev_index <=i-1; prev_index ++){
                
                if( ( arr[i]%arr[prev_index] ==0 || arr[prev_index]%arr[i] ==0 ) && 1 + dp[prev_index] > dp[i]){
                    dp[i] = 1 + dp[prev_index];
                    hash[i] = prev_index;
                }
            }
        }
        
        int ans = -1;
        int lastIndex =-1;
        
        for(int i=0; i<=n-1; i++){
            if(dp[i]> ans){
                ans = dp[i];
                lastIndex = i;
            }
        }
        
        vector<int> temp;
        temp.push_back(arr[lastIndex]);
        
        while(hash[lastIndex] != lastIndex){ // till not reach the initialization value
            lastIndex = hash[lastIndex];
            temp.push_back(arr[lastIndex]);    
        }
        
        // reverse the array 
        reverse(temp.begin(),temp.end());
        return temp;
    }
};
```

## Attempt 2 · 2023-04-03 00:58 IST · Accepted · C++

[submission 926810782](https://leetcode.com/submissions/detail/926810782/) · tests 49/49 · runtime 106 ms (beats 5.1%)

```cpp
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& arr) {
        int n = arr.size();
        vector<int> dp(n,0);
        vector<int> hash(n,1);

        sort(arr.begin(), arr.end(), greater<>());
        
        for(int i=0; i<=n-1; i++){
            
            hash[i] = i; // initializing with current index
            for(int prev_index = 0; prev_index <=i-1; prev_index ++){
                
                if( ( arr[i]%arr[prev_index] ==0 || arr[prev_index]%arr[i] ==0 ) && 1 + dp[prev_index] > dp[i]){
                    dp[i] = 1 + dp[prev_index];
                    hash[i] = prev_index;
                }
            }
        }
        
        int ans = -1;
        int lastIndex =-1;
        
        for(int i=0; i<=n-1; i++){
            if(dp[i]> ans){
                ans = dp[i];
                lastIndex = i;
            }
        }
        
        vector<int> temp;
        temp.push_back(arr[lastIndex]);
        
        while(hash[lastIndex] != lastIndex){ // till not reach the initialization value
            lastIndex = hash[lastIndex];
            temp.push_back(arr[lastIndex]);    
        }
        
        // reverse the array 
        // reverse(temp.begin(),temp.end());
        return temp;
    }
};
```

## Attempt 3 · 2023-05-04 06:45 IST · Accepted · C++

[submission 944094141](https://leetcode.com/submissions/detail/944094141/) · tests 49/49 · runtime 72 ms (beats 8.1%)

```cpp
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& arr) {
        int n = arr.size();
        vector<int> dp(n,0);
        vector<int> hash(n,1);

        sort(arr.begin(), arr.end(), greater<>());
        
        for(int i=0; i<=n-1; i++){
            
            hash[i] = i; // initializing with current index
            for(int prev_index = 0; prev_index <=i-1; prev_index ++){
                
                if( (  arr[prev_index]%arr[i] ==0 ) && 1 + dp[prev_index] > dp[i]){
                    dp[i] = 1 + dp[prev_index];
                    hash[i] = prev_index;
                }
            }
        }
        
        int ans = -1;
        int lastIndex =-1;
        
        for(int i=0; i<=n-1; i++){
            if(dp[i]> ans){
                ans = dp[i];
                lastIndex = i;
            }
        }
        
        vector<int> temp;
        temp.push_back(arr[lastIndex]);
        
        while(hash[lastIndex] != lastIndex){ // till not reach the initialization value
            lastIndex = hash[lastIndex];
            temp.push_back(arr[lastIndex]);    
        }
        
        // reverse the array 
        // reverse(temp.begin(),temp.end());
        return temp;
    }
};
```
