# 465. Optimal Account Balancing

[Problem](https://leetcode.com/problems/optimal-account-balancing/) · Hard · Backtracking → Debt-settlement search

LeetCode tags: array, dynamic-programming, backtracking, bit-manipulation, bitmask

Attempts since Mar 2023: 3 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-03-26 00:40 IST · Accepted · C++

[submission 922029790](https://leetcode.com/submissions/detail/922029790/) · tests 36/36 · runtime 19 ms (beats 15.1%)

```cpp
class Solution {
public:
    int dfs(int index, vector<int> &debt){
        if(index == debt.size()) return 0;
        if(debt[index] ==0) return dfs(index+1, debt);

        // try all possiblities with debt[index]
        int ans = INT_MAX;
        for(int i=index+1;i<debt.size();i++){
            if(debt[i]*debt[index]<0){
                // cout<<index<<" trans "<<i<<"|";
                debt[i] += debt[index];
                ans = min(ans, 1+dfs(index +1, debt));
                debt[i] -= debt[index];
            }
        }
        // cout<<"index|ans:"<<index<<" "<<ans<<"||";
        return ans;
    }
    int minTransfers(vector<vector<int>>& transactions) {
        // 0 -1 10
        // 2 -0 5 
        // 0 +5 , 1 -10, 2 +5
        // p1 gives 5 5 each to both 0 & 2

        // [[0,1,10],[1,0,1],[1,2,5],[2,0,5]]
        // [0 +4], [1 -4] [2, 0]

        // for each person who needs to give, give all of them
        unordered_map<int,int> mp;
        for(auto tran : transactions){
            mp[tran[0]]-=tran[2];
            mp[tran[1]]+=tran[2];
        }
        vector<int> debt;
        // cout<<" Debt Elements ";
        for(auto [_,val] : mp){
            if(val != 0)
                debt.push_back(val);
        }
        // cout<<" Debt Elements Count";
        return dfs(0, debt);
    }
};
```

## Attempt 2 · 2023-03-26 00:43 IST · Wrong Answer · C++

[submission 922031211](https://leetcode.com/submissions/detail/922031211/) · tests 27/36

Failing input:

```text
[[0,3,2],[1,4,3],[2,3,2],[2,4,2]]
```

Expected:

```text
3
```

Your output:

```text
4
```

```cpp
class Solution {
public:
    int dfs(int index, vector<int> &debt, vector<int> &dp){
        if(index == debt.size()) return 0;
        if(dp[index] != -1) return dp[index];
        if(debt[index] ==0) return dfs(index+1, debt, dp);

        // try all possiblities with debt[index]
        int ans = INT_MAX;
        for(int i=index+1;i<debt.size();i++){
            if(debt[i]*debt[index]<0){
                // cout<<index<<" trans "<<i<<"|";
                debt[i] += debt[index];
                ans = min(ans, 1+dfs(index +1, debt, dp));
                debt[i] -= debt[index];
            }
        }
        // cout<<"index|ans:"<<index<<" "<<ans<<"||";
        return dp[index] = ans;
    }
    int minTransfers(vector<vector<int>>& transactions) {
        // 0 -1 10
        // 2 -0 5 
        // 0 +5 , 1 -10, 2 +5
        // p1 gives 5 5 each to both 0 & 2

        // [[0,1,10],[1,0,1],[1,2,5],[2,0,5]]
        // [0 +4], [1 -4] [2, 0]

        // for each person who needs to give, give all of them
        unordered_map<int,int> mp;
        for(auto tran : transactions){
            mp[tran[0]]-=tran[2];
            mp[tran[1]]+=tran[2];
        }
        vector<int> debt;
        // cout<<" Debt Elements ";
        for(auto [_,val] : mp){
            if(val != 0)
                debt.push_back(val);
        }
        vector<int> dp(debt.size()+5, -1);
        // cout<<" Debt Elements Count";
        return dfs(0, debt, dp);
    }
};
```

## Attempt 3 · 2023-03-26 00:44 IST · Accepted · C++

[submission 922031653](https://leetcode.com/submissions/detail/922031653/) · tests 36/36 · runtime 22 ms (beats 13.8%)

```cpp
class Solution {
public:
    int dfs(int index, vector<int> &debt, vector<int> &dp){
        if(index == debt.size()) return 0;
        if(dp[index] != -1) return dp[index];
        if(debt[index] ==0) return dfs(index+1, debt, dp);

        // try all possiblities with debt[index]
        int ans = INT_MAX;
        for(int i=index+1;i<debt.size();i++){
            if(debt[i]*debt[index]<0){
                // cout<<index<<" trans "<<i<<"|";
                debt[i] += debt[index];
                ans = min(ans, 1+dfs(index +1, debt, dp));
                debt[i] -= debt[index];
            }
        }
        // cout<<"index|ans:"<<index<<" "<<ans<<"||";
        return ans;
    }
    int minTransfers(vector<vector<int>>& transactions) {
        // 0 -1 10
        // 2 -0 5 
        // 0 +5 , 1 -10, 2 +5
        // p1 gives 5 5 each to both 0 & 2

        // [[0,1,10],[1,0,1],[1,2,5],[2,0,5]]
        // [0 +4], [1 -4] [2, 0]

        // for each person who needs to give, give all of them
        unordered_map<int,int> mp;
        for(auto tran : transactions){
            mp[tran[0]]-=tran[2];
            mp[tran[1]]+=tran[2];
        }
        vector<int> debt;
        // cout<<" Debt Elements ";
        for(auto [_,val] : mp){
            if(val != 0)
                debt.push_back(val);
        }
        vector<int> dp(debt.size()+5, -1);
        // cout<<" Debt Elements Count";
        return dfs(0, debt, dp);
    }
};
```
