# 424. Longest Repeating Character Replacement

[Problem](https://leetcode.com/problems/longest-repeating-character-replacement/) · Medium · Sliding Window → Variable window, max frequency

LeetCode tags: hash-table, string, sliding-window

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2025-03-22 23:43 IST · Accepted · C++

[submission 1582535874](https://leetcode.com/submissions/detail/1582535874/) · tests 49/49 · runtime 2 ms (beats 70.3%)

```cpp
class Solution {
public:
    int characterReplacement(string s, int k) {
        // keep a window l,r
        // window is good, if replacing k chars still keeps the window valid.
        int n = s.size(), maxl = 0, ans = 0;
        int l = 0, r = 0; 
        unordered_map<char , int> count;

        while(r < n){
            count[s[r]]++;
            maxl = max(maxl, count[s[r]]);

            if((r - l + 1) - maxl > k){
                count[s[l]]--;
                l++;
            }

            ans = max(ans, r-l+1);
            r++;
        }

        return ans;
    }
};
```

## Attempt 2 · 2025-03-22 23:48 IST · Accepted · C++

[submission 1582540804](https://leetcode.com/submissions/detail/1582540804/) · tests 49/49 · runtime 15 ms (beats 16.1%)

```cpp
class Solution {
public:
    int characterReplacement(string s, int k) {
        // keep a window l,r
        // window is good, if replacing k chars still keeps the window valid.
        int n = s.size(), maxl = 0, ans = 0;
        int l = 0, r = 0; 
        unordered_map<char , int> count;

        while(r < n){
            count[s[r]]++;
            // get this maxl from all elements of count map.
            maxl = max(maxl, count[s[r]]);

            if((r - l + 1) - maxl > k){
                count[s[l]]--;
                l++;
            }

            ans = max(ans, r-l+1);
            r++;
        }

        return ans;
    }
};
```
