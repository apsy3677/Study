# 287. Find the Duplicate Number

[Problem](https://leetcode.com/problems/find-the-duplicate-number/) · Medium · Two Pointers → Floyd cycle detection

LeetCode tags: array, two-pointers, binary-search, bit-manipulation, pigeonhole-principle, floyds-cycle-finding-algorithm

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-05-24 08:42 IST · Accepted · C++

[submission 956176711](https://leetcode.com/submissions/detail/956176711/) · tests 58/58 · runtime 131 ms (beats 5.0%)

```cpp
class Solution {
public:
    int cyclicSort(vector<int> &arr){
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
                return arr[i];
        }
        return arr.size();
    }
    int findDuplicate(vector<int>& arr) {
        return cyclicSort(arr);
    }
};
```
