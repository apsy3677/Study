# 724. Find Pivot Index

[Problem](https://leetcode.com/problems/find-pivot-index/) · Easy · Prefix Sum & Difference Array → Prefix sum

LeetCode tags: array, prefix-sum

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-03-06 21:15 IST · Accepted · C++

[submission 910244350](https://leetcode.com/submissions/detail/910244350/) · tests 746/746 · runtime 31 ms (beats 9.4%)

```cpp
class Solution {
public:
    int pivotIndex(vector<int>& arr) {
        vector<int> ls(arr.size()), rs(arr.size());

        for(int i=1;i<arr.size();i++){
            ls[i]+= ls[i-1]+arr[i-1];
        }
        int n= arr.size();
        for(int i=n-2;i>=0;i--){
            rs[i] = rs[i+1] + arr[i+1];
        }
        int ans =-1;

        for(int i=0;i<n;i++){
            if(ls[i] == rs[i]){
                return i;
            }
        }

        return ans;
    }
};
```

## Attempt 2 · 2023-09-01 23:14 IST · Accepted · C++

[submission 1037856937](https://leetcode.com/submissions/detail/1037856937/) · tests 746/746 · runtime 22 ms (beats 9.4%)

```cpp
class Solution {
public:
    int pivotIndex(vector<int>& arr) {
        int sum = 0, n= arr.size();
        for(int i=0;i<n;i++){
            sum=sum+arr[i];
        }
        int ls=0;
        for(int i=0;i<n;i++){
            if(ls == sum-ls-arr[i]){
                return i;
            }
            ls=ls+arr[i];
        }

        return -1;
    }
};
```
