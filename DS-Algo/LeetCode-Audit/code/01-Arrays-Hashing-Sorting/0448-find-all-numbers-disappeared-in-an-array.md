# 448. Find All Numbers Disappeared in an Array

[Problem](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/) · Easy · Arrays, Hashing & Sorting → Index marking

LeetCode tags: array, hash-table

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-05-24 08:35 IST · Accepted · C++

[submission 956174180](https://leetcode.com/submissions/detail/956174180/) · tests 33/33 · runtime 61 ms (beats 12.8%)

```cpp
class Solution {
public:
    vector<int> cyclicSort(vector<int> &arr){
        int i=0;

        while(i< arr.size()){
            int correct = arr[i] -1;

            if(arr[i] != arr[correct]){
                swap(arr[i], arr[correct]);
            }
            else{
                i++;
            }
        }
        vector<int> ans;
        for(int i=0;i<arr.size();i++){
            if(arr[i] != (i+1)){
                ans.push_back(i+1);
            }
        }
        return ans;
    }
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        return cyclicSort(nums);
    }
};
```
