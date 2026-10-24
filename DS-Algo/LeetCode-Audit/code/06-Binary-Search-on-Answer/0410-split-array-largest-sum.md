# 410. Split Array Largest Sum

[Problem](https://leetcode.com/problems/split-array-largest-sum/) · Hard · Binary Search on Answer → Minimise the max partition

LeetCode tags: array, binary-search, dynamic-programming, greedy, prefix-sum

Attempts since Mar 2023: 4 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-05-22 18:45 IST · Accepted · C++

[submission 955117798](https://leetcode.com/submissions/detail/955117798/) · tests 31/31 · runtime 3 ms (beats 8.0%)

```cpp
class Solution {
public:
    bool split(vector<int>& arr, int k, int threshold){
        int curr = 0;
        int count = 0;
        for(auto x: arr){
            // curr += x;
            if(x + curr > threshold){
                if(x > threshold) return false;
                count++;
                curr = x;
            }
            else{
                curr += x;
            }
        }
        cout<<count<<" :: ";
        if(curr != 0) count++;
        return count <= k;
    }
    int splitArray(vector<int>& arr, int k) {
        int low = 0, high = 0;
        for(auto x : arr ){
            high += x;
            low = max(low, x);
        }
        int ans = INT_MAX;
        while(low <= high){
            int mid = low + ((high-low)>>1);
            cout<<mid<<" | ";
            bool canSplit = split(arr,k, mid); // threshold is mid
            if(canSplit){
                ans = mid;
                high = mid-1;
                cout<<"high "<<high<<" ";
            }
            else{
                low = mid+1;
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-05-22 18:49 IST · Accepted · C++

[submission 955119547](https://leetcode.com/submissions/detail/955119547/) · tests 31/31 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    bool split(vector<int>& arr, int k, int threshold){
        int curr = 0;
        int count = 0;
        for(auto x: arr){
            if(x > threshold) return false;
            if(x + curr > threshold){
                count++;
                curr = x;
            }
            else{
                curr += x;
            }
        }
        // cout<<count<<" :: ";
        if(curr != 0) count++;
        return count <= k;
    }
    int splitArray(vector<int>& arr, int k) {
        int low = 0, high = 0;
        for(auto x : arr ){
            high += x;
            low = max(low, x);
        }
        int ans = INT_MAX;
        while(low <= high){
            int mid = low + ((high-low)>>1);
            bool canSplit = split(arr,k, mid); // threshold is mid
            if(canSplit){
                ans = mid;
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        return ans;
    }
};
```

## Attempt 3 · 2023-05-22 19:16 IST · Time Limit Exceeded · C++

[submission 955133867](https://leetcode.com/submissions/detail/955133867/) · tests 12/31

Failing input:

```text
[5334,6299,4199,9663,8945,3566,9509,3124,6026,6250,7475,5420,9201,9501,38,5897,4411,6638,9845,161,9563,8854,3731,5564,5331,4294,3275,1972,1521,2377,3701,6462,6778,187,9778,758,550,7510,6225,8691,3666,4622,9722,8011,7247,575,5431,4777,4032,8682,5888,8047,3562,9462,6501,7855,505,4675,6973,493,1374,3227,1244,7364,2298,3244,8627,5102,6375,8653,1820,3857,7195,7830,4461,7821,5037,2918,4279,2791,1500,985 ... [1271 more chars]
```

Expected:

```text
194890
```

```cpp
class Solution {
    vector<int> prefix;
public:
    bool split(vector<int>& arr, int k, int threshold){
        int curr = 0;
        int count = 0;
        for(auto x: arr){
            if(x > threshold) return false;
            if(x + curr > threshold){
                count++;
                curr = x;
            }
            else{
                curr += x;
            }
        }
        // cout<<count<<" :: ";
        if(curr != 0) count++;
        return count <= k;
    }
    int f(int index, int k, vector<int> &arr){
        int n = arr.size();
        if(n==index){
            if(k==0) return 0;
            else return INT_MAX;
        }
        if(k==1){
            return prefix[n] - prefix[index];
        }
        int ans = INT_MAX;
        for(int i=index ; i<n;i++){
            int sum = prefix[i+1] - prefix[index];
            int maxSumSubArr = max(sum, f(i+1, k-1, arr));

            ans = min(ans, maxSumSubArr );
        }
        return ans;
    }
    int splitArray(vector<int>& arr, int k) {
        int n = arr.size();
        prefix.resize(n+1, 0);
        for(int i=1;i<=n;i++){
            prefix[i] = prefix[i-1] + arr[i-1];
        }
        return f(0, k, arr);
        //splitArrayBS(arr,k);
    }
    int splitArrayBS(vector<int>& arr, int k) {
        int low = 0, high = 0;
        for(auto x : arr ){
            high += x;
            low = max(low, x);
        }
        int ans = INT_MAX;
        while(low <= high){
            int mid = low + ((high-low)>>1);

            bool canSplit = split(arr,k, mid); // threshold is mid
            if(canSplit){
                ans = mid;
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        return ans;
    }
};
```

## Attempt 4 · 2023-05-22 19:18 IST · Accepted · C++

[submission 955134998](https://leetcode.com/submissions/detail/955134998/) · tests 31/31 · runtime 988 ms (beats 4.9%)

```cpp
class Solution {
    vector<int> prefix;
    vector<vector<int>> dp;
public:
    bool split(vector<int>& arr, int k, int threshold){
        int curr = 0;
        int count = 0;
        for(auto x: arr){
            if(x > threshold) return false;
            if(x + curr > threshold){
                count++;
                curr = x;
            }
            else{
                curr += x;
            }
        }
        // cout<<count<<" :: ";
        if(curr != 0) count++;
        return count <= k;
    }
    int f(int index, int k, vector<int> &arr){
        int n = arr.size();
        if(n==index){
            if(k==0) return 0;
            else return INT_MAX;
        }
        if(dp[index][k] !=-1) return dp[index][k];
        if(k==1){
            return prefix[n] - prefix[index];
        }
        int ans = INT_MAX;
        for(int i=index ; i<n;i++){
            int sum = prefix[i+1] - prefix[index];
            int maxSumSubArr = max(sum, f(i+1, k-1, arr));

            ans = min(ans, maxSumSubArr );
        }
        return dp[index][k] = ans;
    }
    int splitArray(vector<int>& arr, int k) {
        int n = arr.size();
        prefix.resize(n+1, 0);
        dp.resize(n+1, vector<int> (k+1, -1));
        for(int i=1;i<=n;i++){
            prefix[i] = prefix[i-1] + arr[i-1];
        }
        return f(0, k, arr);
        //splitArrayBS(arr,k);
    }
    int splitArrayBS(vector<int>& arr, int k) {
        int low = 0, high = 0;
        for(auto x : arr ){
            high += x;
            low = max(low, x);
        }
        int ans = INT_MAX;
        while(low <= high){
            int mid = low + ((high-low)>>1);

            bool canSplit = split(arr,k, mid); // threshold is mid
            if(canSplit){
                ans = mid;
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        return ans;
    }
};
```
