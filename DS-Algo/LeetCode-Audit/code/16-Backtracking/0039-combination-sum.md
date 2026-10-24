# 39. Combination Sum

[Problem](https://leetcode.com/problems/combination-sum/) · Medium · Backtracking → Combinations with reuse

LeetCode tags: array, backtracking

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-04-28 10:13 IST · Accepted · C++

[submission 940926587](https://leetcode.com/submissions/detail/940926587/) · tests 160/160 · runtime 485 ms (beats 5.1%)

```cpp
class Solution {
public:
    void rec(int idx, vector<int>& ds, vector<vector<int>>& res, vector<int>& candidates, int target){
        cout<<"idx|target:"<<idx<<"|"<<target<<":";
        if(idx == candidates.size()){
            
            if(target == 0){
                cout<<"::found:";
                res.push_back(ds);
                cout<<"::printed:";
            }
            return ;
        }
        if(target >= candidates[idx] ){
            ds.push_back(candidates[idx]);
            rec(idx, ds, res, candidates, target-candidates[idx]);
            ds.pop_back();
        }
        cout<<"call idx+1 "<<idx<<"call ";
        rec(idx+1, ds, res, candidates, target);

    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> ds;
        vector<vector<int>> res;
        sort(candidates.begin(), candidates.end());
        rec(0,ds,res,candidates,target);
        return res;
    }
};
```

## Attempt 2 · 2024-10-23 12:06 IST · Accepted · C++

[submission 1431182072](https://leetcode.com/submissions/detail/1431182072/) · tests 160/160 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    void sol1(int idx, int sum, vector<int>& ds, vector<vector<int>>& res, vector<int>& candidates, int target) {
        if(idx == candidates.size() || sum == target) {
            if (sum == target) {
                res.push_back(ds);
            }
            return;
        }
        if (sum + candidates[idx] <= target) {
            ds.push_back(candidates[idx]);
            // take once or multiple times.
            sol1(idx, sum+candidates[idx], ds, res, candidates, target);
            ds.pop_back();
        }
        // Not take
        sol1(idx+1, sum, ds, res, candidates, target);
    }
    void rec(int idx, vector<int>& ds, vector<vector<int>>& res, vector<int>& candidates, int target){
        cout<<"idx|target:"<<idx<<"|"<<target<<":";
        if(idx == candidates.size()){
            
            if(target == 0){
                cout<<"::found:";
                res.push_back(ds);
                cout<<"::printed:";
            }
            return ;
        }
        if(target >= candidates[idx] ){
            ds.push_back(candidates[idx]);
            rec(idx, ds, res, candidates, target-candidates[idx]);
            ds.pop_back();
        }
        cout<<"call idx+1 "<<idx<<"call ";
        rec(idx+1, ds, res, candidates, target);

    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> ds;
        vector<vector<int>> res;
        sort(candidates.begin(), candidates.end());
        // rec(0,ds,res,candidates,target);
        int sum = 0;
        sol1(0,sum, ds,res,candidates,target);
        return res;
    }
};
```
