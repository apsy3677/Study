# 409. Longest Palindrome

[Problem](https://leetcode.com/problems/longest-palindrome/) · Easy · Arrays, Hashing & Sorting → Frequency count

LeetCode tags: hash-table, string, greedy

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-05-20 09:05 IST · Accepted · C++

[submission 953676078](https://leetcode.com/submissions/detail/953676078/) · tests 95/95 · runtime 7 ms (beats 2.1%)

```cpp
class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> map;

        for(auto c : s){
            map[c]++;
        }
        int ans = 0;
        bool odd = false;
        for(auto &[c, count] : map ){
            ans += count;
            if(count & 1){
                ans += (odd ? -1 : 0);
                odd = true;
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-05-20 13:53 IST · Accepted · C++

[submission 953789716](https://leetcode.com/submissions/detail/953789716/) · tests 95/95 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> map;

        for(auto c : s){
            map[c]++;
        }
        int ans = 0;
        bool odd = false;
        for(auto &[c, count] : map ){
            ans += count;
            if(count & 1){
                ans += (odd ? -1 : 0);
                odd = true;
            }
        }
        return ans;
    }
};
```
