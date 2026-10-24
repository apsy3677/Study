# 645. Set Mismatch

[Problem](https://leetcode.com/problems/set-mismatch/) · Easy · Arrays, Hashing & Sorting → Index marking

LeetCode tags: array, hash-table, bit-manipulation, sorting

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-05-24 08:56 IST · Accepted · C++

[submission 956181760](https://leetcode.com/submissions/detail/956181760/) · tests 49/49 · runtime 38 ms (beats 16.8%)

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
        for(int i=0;i<arr.size();i++){
            if(arr[i] != i+1)
                return {arr[i], i+1};
        }
        return {};
    }
    vector<int> findErrorNums(vector<int>& nums) {
        return cyclicSort(nums);
    }
};
```
