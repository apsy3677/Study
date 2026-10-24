# 167. Two Sum II - Input Array Is Sorted

[Problem](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) · Medium · Two Pointers → Opposite ends

LeetCode tags: array, two-pointers, binary-search

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-05-21 09:15 IST · Accepted · C++

[submission 954265686](https://leetcode.com/submissions/detail/954265686/) · tests 23/23 · runtime 12 ms (beats 2.4%)

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& arr, int sum) {
        int left =0, right = arr.size() -1;

        while(left < right){
            
            if(arr[left] + arr[right] == sum){
                return {left+1, right+1};
                left++;
            }
            else if(arr[left] + arr[right] < sum) left++;
            else right--;
        }

        return {};
    }
};
```

## Attempt 2 · 2024-03-25 19:53 IST · Accepted · C++

[submission 1213523765](https://leetcode.com/submissions/detail/1213523765/) · tests 23/23 · runtime 11 ms (beats 2.4%)

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& arr, int sum) {
        int left =0, right = arr.size() -1;

        while(left < right){
            if(arr[left] + arr[right] == sum){
                return {left+1, right+1};
                left++;
            }
            else if(arr[left] + arr[right] < sum) left++;
            else right--;
        }

        return {};
    }
};
```
