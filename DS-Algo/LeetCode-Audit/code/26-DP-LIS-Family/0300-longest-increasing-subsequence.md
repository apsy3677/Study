# 300. Longest Increasing Subsequence

[Problem](https://leetcode.com/problems/longest-increasing-subsequence/) · Medium · DP: LIS Family → LIS (patience sort)

LeetCode tags: array, binary-search, dynamic-programming, longest-increasing-subsequence

Attempts since Mar 2023: 7 · accepted: 7 · failed before first AC: 0

## Attempt 1 · 2023-03-23 16:28 IST · Accepted · C++

[submission 920663705](https://leetcode.com/submissions/detail/920663705/) · tests 54/54 · runtime 1368 ms (beats 5.0%)

```cpp
class Solution {
public:
    int LIS (int index, int prev_Idx, vector<vector<int>> &dp, vector<int>& arr){
        int n = arr.size();
        if(index == n){
            return 0;
        }
        if(dp[index][prev_Idx+1] != -1){
            return dp[index][prev_Idx +1];
        }
        // take or not take
        int notTake = 0 + LIS(index+1, prev_Idx, dp, arr);

        int take =0;

        if(prev_Idx ==-1 || arr[index] > arr[prev_Idx]){
            take = 1 + LIS(index+1, index, dp, arr);
        }
        
        return dp[index][prev_Idx+1] = max(take, notTake);

    }
    int lengthOfLIS(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n+1, vector<int>(n+2, -1));
        return LIS(0,-1,dp,arr);
        // return dp[n-1][n];
    }
};
```

## Attempt 2 · 2023-05-03 18:56 IST · Accepted · C++

[submission 943813582](https://leetcode.com/submissions/detail/943813582/) · tests 54/54 · runtime 1055 ms (beats 5.0%)

```cpp
class Solution {
public:
    int LIS (int index, int prev_Idx, vector<vector<int>> &dp, vector<int>& arr){
        int n = arr.size();
        if(index == n){
            return 0;
        }
        if(dp[index][prev_Idx+1] != -1){
            return dp[index][prev_Idx +1];
        }
        // take or not take
        int notTake = 0 + LIS(index+1, prev_Idx, dp, arr);

        int take =0;

        if(prev_Idx ==-1 || arr[index] > arr[prev_Idx]){
            take = 1 + LIS(index+1, index, dp, arr);
        }
        
        return dp[index][prev_Idx+1] = max(take, notTake);

    }
    int lis (vector<int>& arr){
        int n = arr.size();
        vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        for(int i=0;i<n;i++){

        }
        for(int ind= n-1;ind>=0;ind--){
            for(int prev= ind-1; prev>=-1 ; prev--){
                // take or not take
                int notTake = 0 + dp[ind+1][prev+1];

                int take =0;
                if(prev ==-1 || arr[ind] > arr[prev]){
                    take = 1 + dp[ind+1][ind+1];
                }
                
                dp[ind][prev+1] = max(take, notTake);
            }
        }
        return dp[0][0];

    }
    int lengthOfLIS(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n+1, vector<int>(n+2, -1));
        return lis(arr);
        // return LIS(0,-1,dp,arr);
        // return dp[n-1][n];
    }
};
```

## Attempt 3 · 2023-05-03 18:58 IST · Accepted · C++

[submission 943814542](https://leetcode.com/submissions/detail/943814542/) · tests 54/54 · runtime 728 ms (beats 5.0%)

```cpp
class Solution {
public:
    int LIS (int index, int prev_Idx, vector<vector<int>> &dp, vector<int>& arr){
        int n = arr.size();
        if(index == n){
            return 0;
        }
        if(dp[index][prev_Idx+1] != -1){
            return dp[index][prev_Idx +1];
        }
        // take or not take
        int notTake = 0 + LIS(index+1, prev_Idx, dp, arr);

        int take =0;

        if(prev_Idx ==-1 || arr[index] > arr[prev_Idx]){
            take = 1 + LIS(index+1, index, dp, arr);
        }
        
        return dp[index][prev_Idx+1] = max(take, notTake);

    }
    int lis (vector<int>& arr){
        int n = arr.size();
        // vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        vector<int> next(n+1, 0), cur(n+1);
        for(int i=0;i<n;i++){

        }
        for(int ind= n-1;ind>=0;ind--){
            for(int prev= ind-1; prev>=-1 ; prev--){
                // take or not take
                int notTake = 0 + next[prev+1];

                int take =0;
                if(prev ==-1 || arr[ind] > arr[prev]){
                    take = 1 + next[ind+1];
                }
                
                cur[prev+1] = max(take, notTake);
            }
            next = cur;
        }
        return next[0];
    }
    int lengthOfLIS(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n+1, vector<int>(n+2, -1));
        return lis(arr);
        // return LIS(0,-1,dp,arr);
        // return dp[n-1][n];
    }
};
```

## Attempt 4 · 2023-05-03 19:03 IST · Accepted · C++

[submission 943816431](https://leetcode.com/submissions/detail/943816431/) · tests 54/54 · runtime 495 ms (beats 22.9%)

```cpp
class Solution {
public:
    int LIS (int index, int prev_Idx, vector<vector<int>> &dp, vector<int>& arr){
        int n = arr.size();
        if(index == n){
            return 0;
        }
        if(dp[index][prev_Idx+1] != -1){
            return dp[index][prev_Idx +1];
        }
        // take or not take
        int notTake = 0 + LIS(index+1, prev_Idx, dp, arr);

        int take =0;

        if(prev_Idx ==-1 || arr[index] > arr[prev_Idx]){
            take = 1 + LIS(index+1, index, dp, arr);
        }
        
        return dp[index][prev_Idx+1] = max(take, notTake);

    }
    int lis (vector<int>& arr){
        int n = arr.size();
        // vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        // TC O(N)
        // SC O(2*N)
        vector<int> next(n+1, 0), cur(n+1);
        for(int i=0;i<n;i++){

        }
        for(int ind= n-1;ind>=0;ind--){
            for(int prev= ind-1; prev>=-1 ; prev--){
                // take or not take
                int notTake = 0 + next[prev+1];

                int take =0;
                if(prev ==-1 || arr[ind] > arr[prev]){
                    take = 1 + next[ind+1];
                }
                
                cur[prev+1] = max(take, notTake);
            }
            next = cur;
        }
        return next[0];
    }

    int lis1Array (vector<int>& arr){
        int n = arr.size();
        // vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        // TC O(N)
        // SC O(2*N)
        vector<int> dp(n, 1);
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                if(arr[i]> arr[j] && dp[j] + 1 > dp[i]){
                    dp[i] = dp[j]+1;
                }
            }
        }
        int maxi =0;
        for(int i=0;i<n;i++){
            maxi = max(maxi, dp[i]);
        }
        return maxi;
    }

    int lengthOfLIS(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n+1, vector<int>(n+2, -1));
        return lis1Array(arr);
        return lis(arr);
        // return LIS(0,-1,dp,arr);
        // return dp[n-1][n];
    }
};
```

## Attempt 5 · 2023-05-03 19:04 IST · Accepted · C++

[submission 943817237](https://leetcode.com/submissions/detail/943817237/) · tests 54/54 · runtime 376 ms (beats 26.8%)

```cpp
class Solution {
public:
    int LIS (int index, int prev_Idx, vector<vector<int>> &dp, vector<int>& arr){
        int n = arr.size();
        if(index == n){
            return 0;
        }
        if(dp[index][prev_Idx+1] != -1){
            return dp[index][prev_Idx +1];
        }
        // take or not take
        int notTake = 0 + LIS(index+1, prev_Idx, dp, arr);

        int take =0;

        if(prev_Idx ==-1 || arr[index] > arr[prev_Idx]){
            take = 1 + LIS(index+1, index, dp, arr);
        }
        
        return dp[index][prev_Idx+1] = max(take, notTake);

    }
    int lis (vector<int>& arr){
        int n = arr.size();
        // vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        // TC O(N)
        // SC O(2*N)
        vector<int> next(n+1, 0), cur(n+1);
        for(int i=0;i<n;i++){

        }
        for(int ind= n-1;ind>=0;ind--){
            for(int prev= ind-1; prev>=-1 ; prev--){
                // take or not take
                int notTake = 0 + next[prev+1];

                int take =0;
                if(prev ==-1 || arr[ind] > arr[prev]){
                    take = 1 + next[ind+1];
                }
                
                cur[prev+1] = max(take, notTake);
            }
            next = cur;
        }
        return next[0];
    }

    int lis1Array (vector<int>& arr){
        int n = arr.size();
        // vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        // TC O(N)
        // SC O(2*N)

        int maxi =0;
        vector<int> dp(n, 1);
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                if(arr[i]> arr[j] && dp[j] + 1 > dp[i]){
                    dp[i] = dp[j]+1;
                }
            }
            maxi = max(maxi, dp[i]);
        }
        return maxi;
    }

    int lengthOfLIS(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n+1, vector<int>(n+2, -1));
        return lis1Array(arr);
        return lis(arr);
        // return LIS(0,-1,dp,arr);
        // return dp[n-1][n];
    }
};
```

## Attempt 6 · 2023-05-03 19:21 IST · Accepted · C++

[submission 943824540](https://leetcode.com/submissions/detail/943824540/) · tests 54/54 · runtime 394 ms (beats 26.2%)

```cpp
class Solution {
public:
    int LIS (int index, int prev_Idx, vector<vector<int>> &dp, vector<int>& arr){
        int n = arr.size();
        if(index == n){
            return 0;
        }
        if(dp[index][prev_Idx+1] != -1){
            return dp[index][prev_Idx +1];
        }
        // take or not take
        int notTake = 0 + LIS(index+1, prev_Idx, dp, arr);

        int take =0;

        if(prev_Idx ==-1 || arr[index] > arr[prev_Idx]){
            take = 1 + LIS(index+1, index, dp, arr);
        }
        
        return dp[index][prev_Idx+1] = max(take, notTake);

    }
    int lis (vector<int>& arr){
        int n = arr.size();
        // vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        // TC O(N)
        // SC O(2*N)
        vector<int> next(n+1, 0), cur(n+1);
        for(int i=0;i<n;i++){

        }
        for(int ind= n-1;ind>=0;ind--){
            for(int prev= ind-1; prev>=-1 ; prev--){
                // take or not take
                int notTake = 0 + next[prev+1];

                int take =0;
                if(prev ==-1 || arr[ind] > arr[prev]){
                    take = 1 + next[ind+1];
                }
                
                cur[prev+1] = max(take, notTake);
            }
            next = cur;
        }
        return next[0];
    }

    int lis1Array (vector<int>& arr){
        int n = arr.size();
        // vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        // TC O(N)
        // SC O(2*N)

        int maxi = 1, maxiInd = 0;
        vector<int> dp(n, 1), hash(n);
        for(int i=0;i<n;i++){
            hash[i] = i;
            for(int j=0;j<i;j++){
                if(arr[i]> arr[j] && dp[j] + 1 > dp[i]){
                    dp[i] = dp[j]+1;
                    hash[i] = j;
                }
            }
            if(dp[i] > maxi){
                maxi = dp[i];
                maxiInd = i;
            }
        }
        vector<int> lisArr;
        while(hash[maxiInd] != maxiInd){
            lisArr.push_back(arr[maxiInd]);
            maxiInd = hash[maxiInd];
        }
        lisArr.push_back(arr[maxiInd]);
        reverse(lisArr.begin(), lisArr.end());
        for(auto x: lisArr) cout<<x<<" ";
        return maxi;
    }

    int lengthOfLIS(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n+1, vector<int>(n+2, -1));
        return lis1Array(arr);
        return lis(arr);
        // return LIS(0,-1,dp,arr);
        // return dp[n-1][n];
    }
};
```

## Attempt 7 · 2023-05-04 06:34 IST · Accepted · C++

[submission 944091398](https://leetcode.com/submissions/detail/944091398/) · tests 54/54 · runtime 91 ms (beats 40.3%)

```cpp
class Solution {
public:
    int LIS (int index, int prev_Idx, vector<vector<int>> &dp, vector<int>& arr){
        int n = arr.size();
        if(index == n){
            return 0;
        }
        if(dp[index][prev_Idx+1] != -1){
            return dp[index][prev_Idx +1];
        }
        // take or not take
        int notTake = 0 + LIS(index+1, prev_Idx, dp, arr);

        int take =0;

        if(prev_Idx ==-1 || arr[index] > arr[prev_Idx]){
            take = 1 + LIS(index+1, index, dp, arr);
        }
        
        return dp[index][prev_Idx+1] = max(take, notTake);

    }
    int lis (vector<int>& arr){
        int n = arr.size();
        // vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        // TC O(N)
        // SC O(2*N)
        vector<int> next(n+1, 0), cur(n+1);
        for(int i=0;i<n;i++){

        }
        for(int ind= n-1;ind>=0;ind--){
            for(int prev= ind-1; prev>=-1 ; prev--){
                // take or not take
                int notTake = 0 + next[prev+1];

                int take =0;
                if(prev ==-1 || arr[ind] > arr[prev]){
                    take = 1 + next[ind+1];
                }
                
                cur[prev+1] = max(take, notTake);
            }
            next = cur;
        }
        return next[0];
    }

    int lis1Array (vector<int>& arr){
        int n = arr.size();
        // vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        // TC O(N)
        // SC O(2*N)

        int maxi = 1, maxiInd = 0;
        vector<int> dp(n, 1), hash(n);
        for(int i=0;i<n;i++){
            hash[i] = i;
            for(int j=0;j<i;j++){
                if(arr[i]> arr[j] && dp[j] + 1 > dp[i]){
                    dp[i] = dp[j]+1;
                    hash[i] = j;
                }
            }
            if(dp[i] > maxi){
                maxi = dp[i];
                maxiInd = i;
            }
        }
        vector<int> lisArr;
        while(hash[maxiInd] != maxiInd){
            lisArr.push_back(arr[maxiInd]);
            maxiInd = hash[maxiInd];
        }
        lisArr.push_back(arr[maxiInd]);
        reverse(lisArr.begin(), lisArr.end());
        for(auto x: lisArr) cout<<x<<" ";
        return maxi;
    }
    int lis_lower_bound(vector<int> &arr){
        int len = 1;
        vector<int> res;
        res.push_back(arr[0]);
        for(int i=1;i<arr.size();i++){
            if(arr[i] > res.back()) res.push_back(arr[i]);
            else{
                int idx=lower_bound(res.begin(), res.end(), arr[i]) - res.begin();
                res[idx] = arr[i];
            }
        }
        return res.size();
    }
    int lengthOfLIS(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n+1, vector<int>(n+2, -1));
        return lis_lower_bound(arr);
        return lis1Array(arr);
        return lis(arr);
        // return LIS(0,-1,dp,arr);
        // return dp[n-1][n];
    }
};
```
