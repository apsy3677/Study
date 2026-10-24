# 210. Course Schedule II

[Problem](https://leetcode.com/problems/course-schedule-ii/) · Medium · Graph: Topological Sort → Kahn order

LeetCode tags: depth-first-search, breadth-first-search, graph, topological-sort

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-25 13:37 IST · Accepted · C++

[submission 921728668](https://leetcode.com/submissions/detail/921728668/) · tests 45/45 · runtime 32 ms (beats 5.1%)

```cpp
class Solution {
public:
    vector<int> findOrder(int n, vector<vector<int>>& prerequisites) {
        vector<int> ans, inDegree(n, 0);

        vector<vector<int>> graph(n);

        for(auto edge : prerequisites){
            int from = edge[1];
            int to = edge[0];

            graph[from].push_back(to);
            inDegree[to]++;
        }

        queue<int> qu;

        for(int i=0;i<n;i++){
            if(inDegree[i]==0) qu.push(i);
        }
        int taken =0;
        while(!qu.empty()){
            int sz = qu.size();
            while(sz--){
                int v = qu.front();
                qu.pop();
                taken++;
                ans.push_back(v);

                for(auto end: graph[v]){
                    inDegree[end]--;
                    if(inDegree[end] ==0){
                        qu.push(end);
                    }
                }
            }
        }

        if(ans.size() == n){
            return ans;
        }
        else{
            return vector<int>();
        }
    }
};
```
