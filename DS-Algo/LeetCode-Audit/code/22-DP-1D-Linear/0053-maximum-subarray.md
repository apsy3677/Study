# 53. Maximum Subarray

[Problem](https://leetcode.com/problems/maximum-subarray/) · Medium · DP: 1D / Linear → Kadane

LeetCode tags: array, divide-and-conquer, dynamic-programming

Attempts since Mar 2023: 4 · accepted: 4 · failed before first AC: 0

## Attempt 1 · 2023-05-20 11:08 IST · Accepted · C++

[submission 953718903](https://leetcode.com/submissions/detail/953718903/) · tests 210/210 · runtime 110 ms (beats 4.6%)

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& arr) {
        if(arr.size() ==0) return 0;
        int currSum = arr[0];
        int sum = arr[0];

        for(int i=1;i<arr.size();i++){
            sum = max(arr[i], 
                    max(currSum + arr[i], sum));
            currSum = max(arr[i], currSum+arr[i]);
        }
        return sum;
    }
};
```

## Attempt 2 · 2023-05-20 11:10 IST · Accepted · C++

[submission 953719677](https://leetcode.com/submissions/detail/953719677/) · tests 210/210 · runtime 122 ms (beats 4.6%)

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& arr) {
        if(arr.size() ==0) return 0;
        int currSum = arr[0];
        int sum = arr[0];

        for(int i=1;i<arr.size();i++){
            currSum = max(arr[i], currSum+arr[i]);
            sum = max(currSum , sum);
        }
        return sum;
    }
};
```

## Attempt 3 · 2023-05-20 13:54 IST · Accepted · C++

[submission 953789974](https://leetcode.com/submissions/detail/953789974/) · tests 210/210 · runtime 134 ms (beats 4.6%)

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& arr) {
        if(arr.size() ==0) return 0;
        int currSum = arr[0];
        int sum = arr[0];

        for(int i=1;i<arr.size();i++){
            currSum = max(arr[i], currSum+arr[i]);
            sum = max(currSum , sum);
        }
        return sum;
    }
};
```

## Attempt 4 · 2025-03-22 06:37 IST · Accepted · C++

[submission 1581828977](https://leetcode.com/submissions/detail/1581828977/) · tests 210/210 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ans = INT_MIN;
        int curr = 0;
        for(auto num : nums) {
            curr = max(curr + num, num);
            ans = max(ans, curr);
        } 
        return ans;  
    }
};
```
