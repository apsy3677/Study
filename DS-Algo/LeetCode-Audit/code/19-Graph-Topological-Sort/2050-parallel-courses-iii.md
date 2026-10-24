# 2050. Parallel Courses III

[Problem](https://leetcode.com/problems/parallel-courses-iii/) · Hard · Graph: Topological Sort → Longest path in DAG

LeetCode tags: array, dynamic-programming, graph, topological-sort, directed-acyclic-graph

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-05-05 10:23 IST · Accepted · C++

[submission 944738156](https://leetcode.com/submissions/detail/944738156/) · tests 42/42 · runtime 421 ms (beats 5.0%)

```cpp
class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        queue<int> q;
        vector<vector<int>> adj(n+1);
        vector<int> rest(n+1,0);
        vector<int> indeg(n+1);
        for(int i = 0;i<relations.size();i++)
        {
            adj[relations[i][0]].push_back(relations[i][1]);
            indeg[relations[i][1]]++;
        }
        for(int i=1;i<=n;i++)
        {
            if(indeg[i] == 0)
            {
                q.push(i);
                rest[i] = time[i-1];
            }
        }
        int result = 0;
        while(q.empty() == 0)
        {
            int size = q.size();
            while(size--)
            {
                int u = q.front();
                q.pop();
             
                for(int v:adj[u])
                {
                    indeg[v]--;
                    rest[v] = max(rest[v],rest[u]+time[v-1]);
                    if(indeg[v] == 0)
                    {
                        q.push(v);
                    }
                }    
            }
            
        }
        result = *max_element(rest.begin(),rest.end());
        return result;
    }
};
```
