# 1048. Longest String Chain

[Problem](https://leetcode.com/problems/longest-string-chain/) · Medium · DP: LIS Family → Chain by predecessor

LeetCode tags: array, hash-table, two-pointers, string, dynamic-programming, sorting

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-04-02 00:55 IST · Accepted · C++

[submission 926152010](https://leetcode.com/submissions/detail/926152010/) · tests 84/84 · runtime 147 ms (beats 34.2%)

```cpp
class Solution {
public:
    int longestStrChain(vector<string>& words) {
        
        map<string,int> dp;
        if(words.size() <=1) return words.size();
        int ans = 1;
        sort(words.begin(), words.end(), [](const string &s, const string t){
            return s.size() < t.size();
        });

        for(int i=0;i<words.size();i++){
            dp[words[i]] =1;

            for(int j=0;j<words[i].size();j++){
                string pred = words[i].substr(0,j) + words[i].substr(j+1);
                if(dp.count(pred) != 0){
                    dp[words[i]] = max(dp[words[i]], dp[pred]+1);
                    ans = max(ans, dp[words[i]]);
                }
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-04-03 00:47 IST · Accepted · C++

[submission 926805414](https://leetcode.com/submissions/detail/926805414/) · tests 84/84 · runtime 137 ms (beats 35.3%)

```cpp
class Solution {
public:
    int solve(vector<string>& words){
        map<string,int> dp;
        if(words.size() <=1) return words.size();
        int ans = 1;
        sort(words.begin(), words.end(), [](const string &s, const string t){
            return s.size() < t.size();
        });

        for(int i=0;i<words.size();i++){
            dp[words[i]] =1;

            for(int j=0;j<words[i].size();j++){
                string pred = words[i].substr(0,j) + words[i].substr(j+1);
                if(dp.count(pred) != 0){
                    dp[words[i]] = max(dp[words[i]], dp[pred]+1);
                    ans = max(ans, dp[words[i]]);
                }
            }
        }
        return ans;
    }
    int longestStrChain(vector<string>& words) {
        int n = words.size();
        sort(words.begin(), words.end(), [](const string &s, const string t){
            return s.size() < t.size();
        });

        vector<int> dp(n,1);
    
        int maxi = 1;
        
        for(int i=0; i<=n-1; i++){
            
            for(int prev_index = 0; prev_index <=i-1; prev_index ++){
                
                if( compare(words[i], words[prev_index]) && 1 + dp[prev_index] > dp[i]){
                    dp[i] = 1 + dp[prev_index];
                }
            }
            
            if(dp[i] > maxi)
                maxi = dp[i];
        }
        return maxi;
        
    }

    bool compare(string& s1, string& s2){
    if(s1.size() != s2.size() + 1) return false;
    
    int first = 0;
    int second = 0;
    
    while(first < s1.size()){
        if(second < s2.size() && s1[first] == s2[second]){
            first ++;
            second ++;
        }
        else first ++;
    }
    if(first == s1.size() && second == s2.size()) return true;
    else return false; 
}
};
```
