# 128. Longest Consecutive Sequence

[Problem](https://leetcode.com/problems/longest-consecutive-sequence/) · Medium · Arrays, Hashing & Sorting → Hash set run starts

LeetCode tags: array, hash-table, union-find

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2025-03-22 22:06 IST · Time Limit Exceeded · C++

[submission 1582444889](https://leetcode.com/submissions/detail/1582444889/) · tests 78/81

Failing input:

```text
[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127 ... [188495 more chars]
```

Expected:

```text
25001
```

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> s;
        for (auto num : nums) {
            s.insert(num);
        }
        int ans = 0;

        for (auto num : nums) {
            if (s.find(num -1) == s.end()) {
                int curr = num;
                int len = 1;
                while (s.find(curr + 1) != s.end()){
                    curr++;
                    len++;
                }
                ans = max(ans, len);
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2025-03-22 22:17 IST · Accepted · C++

[submission 1582453958](https://leetcode.com/submissions/detail/1582453958/) · tests 81/81 · runtime 207 ms (beats 5.1%)

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        // unordered_set<int> s;
        set<int> s;
        for (auto num : nums) {
            s.insert(num);
        }
        int ans = 0;

        for (auto num : s) {
            if (s.find(num -1) == s.end()) {
                int curr = num;
                int len = 1;
                while (s.find(curr + 1) != s.end()){
                    curr++;
                    len++;
                }
                ans = max(ans, len);
            }
        }
        return ans;
    }
};
```
