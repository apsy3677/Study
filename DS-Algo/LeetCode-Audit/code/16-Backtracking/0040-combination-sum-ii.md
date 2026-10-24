# 40. Combination Sum II

[Problem](https://leetcode.com/problems/combination-sum-ii/) · Medium · Backtracking → Combinations with duplicates

LeetCode tags: array, backtracking

Attempts since Mar 2023: 4 · accepted: 2 · failed before first AC: 1

## Attempt 1 · 2023-04-28 10:31 IST · Time Limit Exceeded · C++

[submission 940932971](https://leetcode.com/submissions/detail/940932971/) · tests 172/176

Failing input:

```text
[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
30
```

Expected:

```text
[[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]]
```

```cpp
class Solution {
public:
void rec(int idx, int prev, vector<int>& ds, set<vector<int>>& res, vector<int>& candidates, int target){
        if(idx == candidates.size()){
            
            if(target == 0){
                res.insert(ds);
                
            }
			return ;
        }
        
        if(target >= candidates[idx] ){
            ds.push_back(candidates[idx]);
            // int prev = idx>0 ? candidates[idx-1] : INT_MAX;
            // if(prev != candidates[idx])
            // if(prev !=-1 && candidates[idx] == candidates[prev])
            // return;
            rec(idx + 1, idx, ds, res, candidates, target-candidates[idx]);
            ds.pop_back();
        }
        rec(idx+1, prev, ds, res, candidates, target);

    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> ds;
        vector<vector<int>> res;
        set<vector<int>> resSet;

        sort(candidates.begin(), candidates.end());
        rec(0,-1,ds,resSet,candidates,target);
        res = vector<vector<int>>(resSet.begin(), resSet.end());
        return res;
    }
};
```

## Attempt 2 · 2023-04-28 10:51 IST · Accepted · C++

[submission 940939809](https://leetcode.com/submissions/detail/940939809/) · tests 176/176 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
void rec(int idx, vector<int>& ds, vector<vector<int>>& res, vector<int>& candidates, int target){
        
        if(target == 0){
            res.push_back(ds);
            return ;
        }
			
        for(int i = idx; i<candidates.size();i++){
            if(i>idx && candidates[i] == candidates[i-1]) continue;
            if(candidates[i] > target) break;
            ds.push_back(candidates[i]);
            rec(i + 1, ds, res, candidates, target-candidates[i]);
            ds.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> ds;
        vector<vector<int>> res;
        set<vector<int>> resSet;

        sort(candidates.begin(), candidates.end());
        rec(0,ds,res,candidates,target);
        // res = vector<vector<int>>(resSet.begin(), resSet.end());
        return res;
    }
};
```

## Attempt 3 · 2024-10-23 12:17 IST · Wrong Answer · C++

[submission 1431189911](https://leetcode.com/submissions/detail/1431189911/) · tests 75/176

Failing input:

```text
[3,1,3,5,1,1]
8
```

Expected:

```text
[[1,1,1,5],[1,1,3,3],[3,5]]
```

Your output:

```text
[[1,1,1,5],[1,1,3,3],[3,5],[3,5]]
```

```cpp
class Solution {
public:
void rec(int idx, vector<int>& ds, vector<vector<int>>& res, vector<int>& candidates, int target){
        
        if(target == 0){
            res.push_back(ds);
            return ;
        }
			
        for(int i = idx; i<candidates.size();i++){
            if(i>idx && candidates[i] == candidates[i-1]) continue;
            if(candidates[i] > target) break;
            ds.push_back(candidates[i]);
            rec(i + 1, ds, res, candidates, target-candidates[i]);
            ds.pop_back();
        }
    }
    void sol1(int idx, int sum, vector<int>& ds, vector<vector<int>>& res, vector<int>& candidates, int target) {
        if(idx == candidates.size() || sum == target) {
            if (sum == target) {
                res.push_back(ds);
            }
            return;
        }
        for(int i= idx; i<candidates.size();i++) {
            if (i>idx && candidates[i]== candidates[idx]) continue;
            if (sum + candidates[i] <= target) {
                ds.push_back(candidates[i]);
                // take once or multiple times.
                sol1(i+1, sum+candidates[i], ds, res, candidates, target);
                ds.pop_back();
            }
            // Not take
            // sol1(i+1, sum, ds, res, candidates, target);
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> ds;
        vector<vector<int>> res;
        set<vector<int>> resSet;

        sort(candidates.begin(), candidates.end());
        // rec(0,ds,res,candidates,target);
        // res = vector<vector<int>>(resSet.begin(), resSet.end());
        int sum = 0;
        sol1(0,sum, ds,res,candidates,target);
        return res;
    }
};
```

## Attempt 4 · 2024-10-23 12:17 IST · Accepted · C++

[submission 1431190430](https://leetcode.com/submissions/detail/1431190430/) · tests 176/176 · runtime 3 ms (beats 35.0%)

```cpp
class Solution {
public:
void rec(int idx, vector<int>& ds, vector<vector<int>>& res, vector<int>& candidates, int target){
        
        if(target == 0){
            res.push_back(ds);
            return ;
        }
			
        for(int i = idx; i<candidates.size();i++){
            if(i>idx && candidates[i] == candidates[i-1]) continue;
            if(candidates[i] > target) break;
            ds.push_back(candidates[i]);
            rec(i + 1, ds, res, candidates, target-candidates[i]);
            ds.pop_back();
        }
    }
    void sol1(int idx, int sum, vector<int>& ds, vector<vector<int>>& res, vector<int>& candidates, int target) {
        if(idx == candidates.size() || sum == target) {
            if (sum == target) {
                res.push_back(ds);
            }
            return;
        }
        for(int i= idx; i<candidates.size();i++) {
            if (i>idx && candidates[i]== candidates[i-1]) continue;
            if (sum + candidates[i] <= target) {
                ds.push_back(candidates[i]);
                // take once or multiple times.
                sol1(i+1, sum+candidates[i], ds, res, candidates, target);
                ds.pop_back();
            }
            // Not take
            // sol1(i+1, sum, ds, res, candidates, target);
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> ds;
        vector<vector<int>> res;
        set<vector<int>> resSet;

        sort(candidates.begin(), candidates.end());
        // rec(0,ds,res,candidates,target);
        // res = vector<vector<int>>(resSet.begin(), resSet.end());
        int sum = 0;
        sol1(0,sum, ds,res,candidates,target);
        return res;
    }
};
```
