# 334. Increasing Triplet Subsequence

[Problem](https://leetcode.com/problems/increasing-triplet-subsequence/) · Medium · Greedy → Two running minimums

LeetCode tags: array, greedy, longest-increasing-subsequence

Attempts since Mar 2023: 4 · accepted: 2 · failed before first AC: 1

## Attempt 1 · 2023-08-23 20:27 IST · Wrong Answer · C++

[submission 1029640980](https://leetcode.com/submissions/detail/1029640980/) · tests 73/80

Failing input:

```text
[1,2,1,3]
```

Expected:

```text
true
```

Your output:

```text
false
```

```cpp
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size();
        vector<int> left(n, INT_MAX),right(n, INT_MIN);
        for(int i=1;i<n;i++) {
            left[i] = min(left[i-1], nums[i-1]);
            right[n-1-i]=max(right[n-i], nums[n-i]);
            if(nums[i]>left[i] && nums[i]<right[i]) {
                return true;
            }
        }
        return false;
    }
};
```

## Attempt 2 · 2023-08-23 20:30 IST · Accepted · C++

[submission 1029643835](https://leetcode.com/submissions/detail/1029643835/) · tests 80/80 · runtime 119 ms (beats 5.0%)

```cpp
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size();
        vector<int> left(n, INT_MAX),right(n, INT_MIN);
        for(int i=1;i<n;i++) {
            left[i] = min(left[i-1], nums[i-1]);
            right[n-1-i]=max(right[n-i], nums[n-i]);
        }
        for (int i=1;i<n-1;i++) {
            if(nums[i]>left[i] && nums[i]<right[i]) {
                return true;
            }
        }
        return false;
    }
};
```

## Attempt 3 · 2023-08-23 20:38 IST · Wrong Answer · C++

[submission 1029650064](https://leetcode.com/submissions/detail/1029650064/) · tests 73/80

Failing input:

```text
[0,4,2,1,0,-1,-3]
```

Expected:

```text
false
```

Your output:

```text
true
```

```cpp
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size(), minimum=INT_MAX, maximum=INT_MIN;
        vector<bool> left(n, false),right(n, false);
        for(int i=1;i<n;i++) {
            minimum = min(minimum, nums[i-1]);
            if(nums[i]>minimum) {
                left[i]=true;
            }
            maximum=max(maximum, nums[n-i]);
            if(nums[i]<maximum) {
                right[n-1-i] = true;
            }
        }
        for (int i=1;i<n-1;i++) {
            if(left[i] && right[i]) {
                return true;
            }
        }
        return false;
    }
};
```

## Attempt 4 · 2023-08-23 20:41 IST · Accepted · C++

[submission 1029652848](https://leetcode.com/submissions/detail/1029652848/) · tests 80/80 · runtime 101 ms (beats 5.0%)

```cpp
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size(), minimum=INT_MAX, maximum=INT_MIN;
        vector<bool> left(n, false),right(n, false);
        for(int i=1;i<n;i++) {
            minimum = min(minimum, nums[i-1]);
            if(nums[i]>minimum) {
                left[i]=true;
            }
            maximum=max(maximum, nums[n-i]);
            if(nums[n-1-i]<maximum) {
                right[n-1-i] = true;
            }
        }
        for (int i=1;i<n-1;i++) {
            if(left[i] && right[i]) {
                return true;
            }
        }
        return false;
    }
};
```
