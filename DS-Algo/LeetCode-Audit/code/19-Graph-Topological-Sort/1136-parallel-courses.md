# 1136. Parallel Courses

[Problem](https://leetcode.com/problems/parallel-courses/) · Medium · Graph: Topological Sort → Kahn by levels

LeetCode tags: graph, topological-sort, directed-acyclic-graph

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-03-24 20:06 IST · Accepted · C++

[submission 921336511](https://leetcode.com/submissions/detail/921336511/) · tests 39/39 · runtime 78 ms (beats 5.1%)

```cpp
class Solution {
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        // UF
        // detect cycle : yes, -1
        // looks connected components problem
        // else 
        // Topological Sorting

        vector<int> inDegree(n,0);
        vector<vector<int>> graph(n+1);

        for(auto edge : relations){
            graph[edge[0]-1].push_back(edge[1]-1);
            inDegree[edge[1]-1]++;
        }
        int ans =0;
        int taken =0;

        vector<int> qu;

        for(int i=0;i<n;i++){
            if(inDegree[i]==0) qu.push_back(i);
        }

        while(!qu.empty()){
            ans++;
            vector<int> nextQu;

            for(auto x: qu){
                taken++;

                for(auto endNode : graph[x]){
                    inDegree[endNode]--;
                    if(inDegree[endNode] ==0){
                        nextQu.push_back(endNode);
                    }
                }
            }
            qu = nextQu;
        }
        

        return taken == n ? ans  : -1;

    }
};
```

## Attempt 2 · 2023-03-24 20:20 IST · Accepted · C++

[submission 921343418](https://leetcode.com/submissions/detail/921343418/) · tests 39/39 · runtime 72 ms (beats 5.1%)

```cpp
class Solution {
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        // UF
        // detect cycle : yes, -1
        // looks connected components problem
        // else 
        // Topological Sorting

        vector<int> inDegree(n,0);
        vector<vector<int>> graph(n+1);

        for(auto edge : relations){
            graph[edge[0]-1].push_back(edge[1]-1);
            inDegree[edge[1]-1]++;
        }
        

        queue<int> qu;

        for(int i=0;i<n;i++){
            if(inDegree[i]==0) qu.push(i);
        }
        int ans =0;
        int taken =0;

        while(!qu.empty()){
            int sz = qu.size();
            ans++;
            while(sz--){
                int top = qu.front();
                qu.pop();
                taken++;
                for(auto endNode: graph[top]){
                    inDegree[endNode]--;
                    if(inDegree[endNode]==0){
                        qu.push(endNode);
                    }
                }
            }
            // vector<int> nextQu;

            // for(auto x: qu){
            //     taken++;

            //     for(auto endNode : graph[x]){
            //         inDegree[endNode]--;
            //         if(inDegree[endNode] ==0){
            //             nextQu.push_back(endNode);
            //         }
            //     }
            // }
            // qu = nextQu;
        }
        

        return taken == n ? ans  : -1;

    }
};
```
