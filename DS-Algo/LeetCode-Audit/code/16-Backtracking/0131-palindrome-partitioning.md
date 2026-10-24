# 131. Palindrome Partitioning

[Problem](https://leetcode.com/problems/palindrome-partitioning/) · Medium · Backtracking → Partition backtracking

LeetCode tags: string, dynamic-programming, backtracking

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-04-28 15:05 IST · Accepted · C++

[submission 941029531](https://leetcode.com/submissions/detail/941029531/) · tests 32/32 · runtime 115 ms (beats 12.4%)

```cpp
class Solution {
public:
    bool isPallindrome(string &s, int start, int end){
        while(start < end){
            if(s[start++] != s[end--]) return false;
        }
        return true;
    }
    void rec(int idx, string &s, vector<string> &path, vector<vector<string>> &res){
        if(idx == s.size()){
            res.push_back(path);
            return;
        }

        for(int i=idx; i<s.size();i++){
            if(isPallindrome(s, idx, i)){
                path.push_back(s.substr(idx, i-idx+1));
                rec(i+1, s, path, res);
                path.pop_back();
            }
        }
    }
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans;
        vector<string> path;

        rec(0, s, path, ans);
        return ans;
    }
};
```
