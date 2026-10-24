# 442. Find All Duplicates in an Array

[Problem](https://leetcode.com/problems/find-all-duplicates-in-an-array/) · Medium · Arrays, Hashing & Sorting → Index marking

LeetCode tags: array, hash-table, sorting

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-05-24 08:45 IST · Accepted · C++

[submission 956177792](https://leetcode.com/submissions/detail/956177792/) · tests 28/28 · runtime 60 ms (beats 18.0%)

```cpp
class Solution {
public:
    vector<int> cyclicSort(vector<int> &arr){
        int i=0;
        while(i<arr.size()){
            int correct = arr[i]-1;
            if(arr[i] != arr[correct]){
                swap(arr[i], arr[correct]);
            }
            else{
                i++;
            }
        }
        vector<int> ans;
        for(int i=0;i<arr.size();i++){
            if(arr[i] != i+1)
                ans.push_back(arr[i]);
        }
        return ans;
    }
    vector<int> findDuplicates(vector<int>& nums) {
        return cyclicSort(nums);
    }
};
```
