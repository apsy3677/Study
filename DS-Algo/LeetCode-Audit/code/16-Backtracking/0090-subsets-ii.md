# 90. Subsets II

[Problem](https://leetcode.com/problems/subsets-ii/) · Medium · Backtracking → Subsets with duplicates

LeetCode tags: array, backtracking, bit-manipulation

Attempts since Mar 2023: 3 · accepted: 2 · failed before first AC: 1

## Attempt 1 · 2023-03-22 13:04 IST · Wrong Answer · C++

[submission 919983739](https://leetcode.com/submissions/detail/919983739/) · tests 15/20

Failing input:

```text
[4,4,4,1,4]
```

Expected:

```text
[[],[1],[1,4],[1,4,4],[1,4,4,4],[1,4,4,4,4],[4],[4,4],[4,4,4],[4,4,4,4]]
```

Your output:

```text
[[],[4],[4,4],[4,4,4],[4,4,4,1],[4,4,4,1,4],[4,4,4,4],[4,4,1],[4,4,1,4],[4,4,4],[4,1],[4,1,4],[4,4],[1],[1,4],[4]]
```

```cpp
class Solution {
    vector<vector<int>> subsets;
public:
    void backtrack(int index, vector<int> &set, vector<int> arr){
        subsets.push_back(set);

        for(int i= index;i<arr.size();i++){
            if(i != index && arr[i] == arr[i-1]){
                continue;
            }
            set.push_back(arr[i]);
            backtrack(i+1, set, arr);
            set.pop_back();
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& arr) {
        vector<int> set;
        // sort(arr.begin(), arr.end());

        backtrack(0, set, arr);
        return subsets;
    }
};
```

## Attempt 2 · 2023-03-22 13:05 IST · Accepted · C++

[submission 919984029](https://leetcode.com/submissions/detail/919984029/) · tests 20/20 · runtime 0 ms (beats 100%)

```cpp
class Solution {
    vector<vector<int>> subsets;
public:
    void backtrack(int index, vector<int> &set, vector<int> arr){
        subsets.push_back(set);

        for(int i= index;i<arr.size();i++){
            if(i != index && arr[i] == arr[i-1]){
                continue;
            }
            set.push_back(arr[i]);
            backtrack(i+1, set, arr);
            set.pop_back();
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& arr) {
        vector<int> set;
        sort(arr.begin(), arr.end());

        backtrack(0, set, arr);
        return subsets;
    }
};
```

## Attempt 3 · 2023-04-28 11:10 IST · Accepted · C++

[submission 940946848](https://leetcode.com/submissions/detail/940946848/) · tests 20/20 · runtime 3 ms (beats 29.8%)

```cpp
class Solution {
    vector<vector<int>> subsets;
public:
    void backtrack(int index, vector<int> &set, vector<int> arr){
        subsets.push_back(set);

        for(int i= index;i<arr.size();i++){
            if(i > index && arr[i] == arr[i-1]){
                continue;
            }
            set.push_back(arr[i]);
            backtrack(i+1, set, arr);
            set.pop_back();
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& arr) {
        vector<int> set;
        sort(arr.begin(), arr.end());

        backtrack(0, set, arr);
        return subsets;
    }
};
```
