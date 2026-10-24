# 238. Product of Array Except Self

[Problem](https://leetcode.com/problems/product-of-array-except-self/) · Medium · Prefix Sum & Difference Array → Prefix/suffix product

LeetCode tags: array, prefix-sum

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-08-23 19:56 IST · Accepted · C++

[submission 1029614944](https://leetcode.com/submissions/detail/1029614944/) · tests 22/22 · runtime 27 ms (beats 6.2%)

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        int countZero = 0, totalProduct = 1;
        for(int i=0;i<n;i++) {
            if(nums[i] == 0) {
                countZero++;
            } else {
                totalProduct = totalProduct * nums[i];
            }
        }
        if(countZero>1) {
            vector<int> result(n, 0);
            return result;
        } else if (countZero == 1) {
            vector<int> result;
            for (int i=0;i<n ;i++) {
                if( nums[i]==0 ) {
                    result.push_back(totalProduct);
                } else {
                    result.push_back(0);
                }
            }
            return result;
        } else {
            vector<int> result;
            for (int i=0;i<n ;i++) {
                result.push_back(totalProduct/nums[i]);
            }
            return result;
        }
    }
};
```

## Attempt 2 · 2023-08-23 20:02 IST · Accepted · C++

[submission 1029620534](https://leetcode.com/submissions/detail/1029620534/) · tests 22/22 · runtime 25 ms (beats 6.2%)

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        int right=1;
        vector<int> result(n, 1);
        for(int i=1;i<n;i++) {
            result[i] = result[i-1] * nums[i-1];
        }
        for (int j=n-1;j>=0;j--) {
            result[j] = result[j] * right;
            right = right * nums[j];
        }
        return result;
    }
};
```
