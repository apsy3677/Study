# 567. Permutation in String

[Problem](https://leetcode.com/problems/permutation-in-string/) · Medium · Sliding Window → Fixed window counts

LeetCode tags: hash-table, two-pointers, string, sliding-window

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2025-03-22 22:57 IST · Accepted · C++

[submission 1582490159](https://leetcode.com/submissions/detail/1582490159/) · tests 108/108 · runtime 3 ms (beats 64.6%)

```cpp
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.size() > s2.size()) {
            return false;
        }
        unordered_map<char, int> mp, mp2;
        for (auto ch : s1) mp[ch]++;

        int l = 0, r = s1.size();
        for(int i=0 ; i<s1.size();i++) {
            mp2[s2[i]]++;
        }
        if (mp == mp2) return true;

        for(int i= s1.size(), l=0; i<s2.size() ; i++) {
            mp2[s2[i]]++;
            char ch = s2[l];
            mp2[s2[l]]--; l++;
            if (mp2[ch] == 0) mp2.erase(ch);
            if (mp == mp2) return true;
        }
        return false;
    }
};
```
