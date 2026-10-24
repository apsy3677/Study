# 1679. Max Number of K-Sum Pairs

[Problem](https://leetcode.com/problems/max-number-of-k-sum-pairs/) · Medium · Two Pointers → Sort + two pointers

LeetCode tags: array, hash-table, two-pointers, sorting

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2023-08-24 23:43 IST · Wrong Answer · C++

[submission 1030750698](https://leetcode.com/submissions/detail/1030750698/) · tests 25/51

Failing input:

```text
[2,5,4,4,1,3,4,4,1,4,4,1,2,1,2,2,3,2,4,2]
3
```

Expected:

```text
4
```

Your output:

```text
3
```

```cpp
class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        map<int, int> count;
        count[nums[0]] = 1;
        int n=nums.size(), ans=0;
        for (int i=1;i<n;i++) {
            if(count.find(k-nums[i]) != count.end()) {
                count[k-nums[i]] = count[k-nums[i]] -1;
                if(count[k-nums[i]] == 0) {
                    count.erase(k-nums[i]);
                }
                ans++;
            } else {
                count[nums[i]] = 1;
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-08-24 23:46 IST · Accepted · C++

[submission 1030753639](https://leetcode.com/submissions/detail/1030753639/) · tests 51/51 · runtime 207 ms (beats 5.1%)

```cpp
class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        map<int, int> count;
        count[nums[0]] = 1;
        int n=nums.size(), ans=0;
        for (int i=1;i<n;i++) {
            if(count.find(k-nums[i]) != count.end()) {
                count[k-nums[i]] = count[k-nums[i]] -1;
                if(count[k-nums[i]] == 0) {
                    count.erase(k-nums[i]);
                }
                ans++;
            } else {
                if(count.find(nums[i]) != count.end()) {
                    count[nums[i]] = count[nums[i]] + 1;
                } else {
                    count[nums[i]] = 1;
                }
            }
        }
        return ans;
    }
};
```
