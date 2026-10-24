# 1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit

[Problem](https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/) · Medium · Sliding Window → Window with min/max deques

LeetCode tags: array, queue, sliding-window, heap-priority-queue, ordered-set, monotonic-queue

Attempts since Mar 2023: 3 · accepted: 1 · failed before first AC: 2

## Attempt 1 · 2023-03-16 19:03 IST · Wrong Answer · C++

[submission 916283389](https://leetcode.com/submissions/detail/916283389/) · tests 60/61

Failing input:

```text
[2,2,2,4,4,2,5,5,5,5,5,2]
2
```

Expected:

```text
6
```

Your output:

```text
7
```

```cpp
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int left =0, right=0, ans = 0;
        multiset<int> st;
        for(int i=0;i<nums.size();i++){
            st.insert(nums[i]);
            // find min & max in set
            int minn = *st.begin();
            int maxx = *st.rbegin();

            while(maxx-minn > limit){
                // delete elements from st
                st.erase(nums[left++]); // move window to right
                minn = *st.begin();
                maxx = *st.rbegin();
            }

            if(abs(maxx - minn) <= limit){
                ans = max(ans, (int)st.size());
            }
            
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-03-16 19:11 IST · Wrong Answer · C++

[submission 916287128](https://leetcode.com/submissions/detail/916287128/) · tests 60/61

Failing input:

```text
[2,2,2,4,4,2,5,5,5,5,5,2]
2
```

Expected:

```text
6
```

Your output:

```text
7
```

```cpp
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int left =0, right=0, ans = 0;
        multiset<int> st;
        for(int i=0;i<nums.size();i++){
            st.insert(nums[i]);
            // find min & max in set
            int minn = *st.begin();
            int maxx = *st.rbegin();

            while(!st.empty() && maxx-minn > limit){
                // delete elements from st
                st.erase(nums[left++]); // move window to right
                minn = *st.begin();
                maxx = *st.rbegin();
            }
 
            ans = max(ans, (int)st.size());   
        }
        return ans;
    }
};
```

## Attempt 3 · 2023-03-16 19:14 IST · Accepted · C++

[submission 916288522](https://leetcode.com/submissions/detail/916288522/) · tests 61/61 · runtime 224 ms (beats 5.1%)

```cpp
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int left =0, right=0, ans = 0;
        multiset<int> st;
        for(int i=0;i<nums.size();i++){
            st.insert(nums[i]);
            // find min & max in set
            int minn = *st.begin();
            int maxx = *st.rbegin();

            while(!st.empty() && maxx-minn > limit){
                // delete elements from st
                st.erase(st.find(nums[left++])); // move window to right
                minn = *st.begin();
                maxx = *st.rbegin();
            }
 
            ans = max(ans, i-left +1);   
        }
        return ans;
    }
};
```
