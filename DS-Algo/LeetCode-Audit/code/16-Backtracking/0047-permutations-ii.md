# 47. Permutations II

[Problem](https://leetcode.com/problems/permutations-ii/) · Medium · Backtracking → Permutations with duplicates

LeetCode tags: array, backtracking, sorting

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2023-03-22 13:46 IST · Wrong Answer · C++

[submission 920000533](https://leetcode.com/submissions/detail/920000533/) · tests 17/33

Failing input:

```text
[3,3,0,3]
```

Expected:

```text
[[0,3,3,3],[3,0,3,3],[3,3,0,3],[3,3,3,0]]
```

Your output:

```text
[[3,3,0,3],[3,3,3,0],[3,0,3,3],[3,0,3,3],[3,3,3,0],[3,3,0,3],[0,3,3,3],[0,3,3,3],[0,3,3,3],[3,3,3,0],[3,3,0,3],[3,0,3,3]]
```

```cpp
class Solution {
    vector<vector<int>> permutations;
public:
    void backtrack(int index, vector<int>& temp, vector<bool> & used, vector<int> &arr){
        if(temp.size() == arr.size()){
            permutations.push_back(temp);
            return;
        }

        for(int i=0;i<arr.size();i++){
            // chose elements which are not chosen already
            if(used[i] || (i>0 && used[i-1] && arr[i] == arr[i-1])){
                continue;
            }
            used[i] = true;
            temp.push_back(arr[i]);
            backtrack(i+1, temp, used, arr);
            temp.pop_back();
            used[i] = false;
    }
    }
    vector<vector<int>> permuteUnique(vector<int>& arr) {
        vector<int> temp;
        vector<bool> used(arr.size(), false);

        backtrack(0,temp, used, arr);
        return permutations;
    }
};
```

## Attempt 2 · 2023-03-22 13:47 IST · Accepted · C++

[submission 920000773](https://leetcode.com/submissions/detail/920000773/) · tests 33/33 · runtime 7 ms (beats 27.4%)

```cpp
class Solution {
    vector<vector<int>> permutations;
public:
    void backtrack(int index, vector<int>& temp, vector<bool> & used, vector<int> &arr){
        if(temp.size() == arr.size()){
            permutations.push_back(temp);
            return;
        }

        for(int i=0;i<arr.size();i++){
            // chose elements which are not chosen already
            if(used[i] || (i>0 && used[i-1] && arr[i] == arr[i-1])){
                continue;
            }
            used[i] = true;
            temp.push_back(arr[i]);
            backtrack(i+1, temp, used, arr);
            temp.pop_back();
            used[i] = false;
    }
    }
    vector<vector<int>> permuteUnique(vector<int>& arr) {
        vector<int> temp;
        vector<bool> used(arr.size(), false);

        sort(arr.begin(), arr.end());
        backtrack(0,temp, used, arr);
        return permutations;
    }
};
```
