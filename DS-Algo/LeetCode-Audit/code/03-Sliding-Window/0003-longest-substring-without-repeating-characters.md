# 3. Longest Substring Without Repeating Characters

[Problem](https://leetcode.com/problems/longest-substring-without-repeating-characters/) · Medium · Sliding Window → Variable window, unique chars

LeetCode tags: hash-table, string, sliding-window

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-03-25 12:10 IST · Accepted · C++

[submission 921690096](https://leetcode.com/submissions/detail/921690096/) · tests 987/987 · runtime 31 ms (beats 71.3%)

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        map<char,int> mp;
        int l=0,r=0;
        int ans =0;
        for(int i=0;i<s.size();i++){
            char ch = s[i];
            mp[ch]++;
            r++;
            if(mp[ch] == 1){
                ans = max(ans, r-l);
                continue;
            }
            // remove ch char from window

            while(l<=r && mp[ch]>1){
                mp[s[l]]--;
                l++;
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-11-18 06:05 IST · Accepted · Python3

[submission 1101104428](https://leetcode.com/submissions/detail/1101104428/) · tests 987/987 · runtime 91 ms (beats 99.9%)

```python
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        left = right =0
        chars = Counter()
        res = 0
        while right < len(s):
            r = s[right]
            chars[r] +=1

            while chars[r]>1:
                l = s[left]
                chars[l] -=1
                left +=1
            
            res = max(res, right-left+1)

            right +=1
        return res
```
