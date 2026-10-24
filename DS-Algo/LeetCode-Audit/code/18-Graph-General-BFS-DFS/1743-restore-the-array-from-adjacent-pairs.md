# 1743. Restore the Array From Adjacent Pairs

[Problem](https://leetcode.com/problems/restore-the-array-from-adjacent-pairs/) · Medium · Graph: General BFS/DFS → Walk from degree-1 end

LeetCode tags: array, hash-table, depth-first-search

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-27 00:12 IST · Accepted · C++

[submission 922602314](https://leetcode.com/submissions/detail/922602314/) · tests 46/46 · runtime 1226 ms (beats 5.1%)

```cpp
class Solution {
public:
    vector<int> restoreArray(vector<vector<int>>& pairs) {
        map<int, vector<int>> graph;
        map<int, int> inDegree;

        for(auto x: pairs){
            graph[x[0]].push_back(x[1]);
            graph[x[1]].push_back(x[0]);
            inDegree[x[0]]++;
            inDegree[x[1]]++;
        }
        // for(auto [v, c]: graph){
        //     for(auto end : c){
        //         inDegree[end]++;
        //     }
        // }
        queue<int> qu;
        set<int> seen;
        for(auto [k, v] : inDegree){
            if(v == 1){
                qu.push(k);
                seen.insert(k);
                break;
            }
        }
        vector<int> ans;
        while(!qu.empty()){
            int sz = qu.size();
            while(sz--){
                int top = qu.front();
                qu.pop();
                ans.push_back(top);
                for(auto end: graph[top]){
                    inDegree[end]--;
                    if( seen.find(end) == seen.end()){
                        seen.insert(end);
                        qu.push(end);
                    }
                }
            }
        }

        return ans;
    }
};
```
