# 78. Subsets

[Problem](https://leetcode.com/problems/subsets/) · Medium · Backtracking → Subsets

LeetCode tags: array, backtracking, bit-manipulation

Attempts since Mar 2023: 4 · accepted: 4 · failed before first AC: 0

## Attempt 1 · 2023-03-22 12:35 IST · Accepted · C++

[submission 919970680](https://leetcode.com/submissions/detail/919970680/) · tests 10/10 · runtime 5 ms (beats 5.3%)

```cpp
class Solution {
    vector<vector<int>> sets;
public:
    void rec(int n, vector<int> path, vector<int> &arr){
        if(n<0){
            sets.push_back(vector<int> (path.rbegin(), path.rend() ) );
            return;
        }
        // dont take
        rec(n-1, path, arr);
        // take element
        path.push_back(arr[n]);
        rec(n-1, path, arr);
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> path;
        int n= nums.size();
        if(n==0)
            return sets;
        rec(n-1,path, nums);

        return sets;
    }
};
```

## Attempt 2 · 2023-03-22 22:10 IST · Accepted · C++

[submission 920229956](https://leetcode.com/submissions/detail/920229956/) · tests 10/10 · runtime 5 ms (beats 5.3%)

```cpp
class Solution {
    vector<vector<int>> sets;
public:
    void rec(int n, vector<int> path, vector<int> &arr){
        if(n<0){
            sets.push_back(vector<int> (path.rbegin(), path.rend() ) );
            return;
        }
        // dont take
        rec(n-1, path, arr);
        // take element
        path.push_back(arr[n]);
        rec(n-1, path, arr);
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> path;
        int n= nums.size();
        if(n==0)
            return sets;
        rec(n-1,path, nums);

        return sets;
    }
};
```

## Attempt 3 · 2023-04-28 11:04 IST · Accepted · C++

[submission 940944580](https://leetcode.com/submissions/detail/940944580/) · tests 10/10 · runtime 9 ms (beats 5.3%)

```cpp
class Solution {
    vector<vector<int>> sets;
public:
    void rec(int n, vector<int> path, vector<int> &arr){
        if(n<0){
            sets.push_back(vector<int> (path.rbegin(), path.rend() ) );
            return;
        }
        // dont take
        rec(n-1, path, arr);
        // take element
        path.push_back(arr[n]);
        rec(n-1, path, arr);
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> path;
        int n= nums.size();
        if(n==0)
            return sets;
        rec(n-1,path, nums);

        return sets;
    }
};
```

## Attempt 4 · 2023-04-28 11:08 IST · Accepted · C++

[submission 940946290](https://leetcode.com/submissions/detail/940946290/) · tests 10/10 · runtime 4 ms (beats 9.5%)

```cpp
class Solution {
    vector<vector<int>> sets;
public:
    void rec(int idx, vector<int> &path, vector<int> &arr){
        cout<<idx<<" ";
        if(idx >= arr.size()){
            sets.push_back(path);
            return;
        }
        // dont take
        rec(idx+1, path, arr);

        // take element
        path.push_back(arr[idx]);
        rec(idx+1, path, arr);
        path.pop_back();
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> path;
        int n= nums.size();
        if(n==0)
            return sets;
        rec(0, path, nums);

        return sets;
    }
};
```
