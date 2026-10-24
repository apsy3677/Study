# 46. Permutations

[Problem](https://leetcode.com/problems/permutations/) · Medium · Backtracking → Permutations

LeetCode tags: array, backtracking

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-03-22 13:36 IST · Accepted · C++

[submission 919996508](https://leetcode.com/submissions/detail/919996508/) · tests 26/26 · runtime 4 ms (beats 9.4%)

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
        if(used[i] ){
            continue;
        }
        used[i] = true;
        temp.push_back(arr[i]);
        backtrack(i+1, temp, used, arr);
        temp.pop_back();
        used[i] = false;
    }
}
    vector<vector<int>> permute(vector<int>& arr) {
        vector<int> temp;
        vector<bool> used(arr.size(), false);

        backtrack(0,temp, used, arr);
        return permutations;
    }
};
```

## Attempt 2 · 2023-04-28 11:39 IST · Accepted · C++

[submission 940957460](https://leetcode.com/submissions/detail/940957460/) · tests 26/26 · runtime 8 ms (beats 5.1%)

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
            if(used[i] ){
                continue;
            }
            used[i] = true;
            temp.push_back(arr[i]);
            backtrack(i+1, temp, used, arr);
            temp.pop_back();
            used[i] = false;
        }
    }

    void permute1(int idx, vector<int> &arr){
        if(idx == arr.size()){
            permutations.push_back(arr);
            return;
        }

        for(int i = idx; i < arr.size();i++){
            swap(arr[idx], arr[i]);
            permute1(idx+1, arr);
            swap(arr[idx],arr[i]);
        }
    }

    vector<vector<int>> permute(vector<int>& arr) {
        vector<int> temp;
        vector<bool> used(arr.size(), false);

        // backtrack(0,temp, used, arr);
        permute1(0, arr);
        return permutations;
    }
};
```
