# 1494. Parallel Courses II

[Problem](https://leetcode.com/problems/parallel-courses-ii/) · Hard · DP: Bitmask → Bitmask DP over courses

LeetCode tags: dynamic-programming, bit-manipulation, graph, bitmask, directed-acyclic-graph

Attempts since Mar 2023: 1 · accepted: 0 · failed before first AC: 1

## Attempt 1 · 2023-03-24 21:43 IST · Wrong Answer · C++

[submission 921383571](https://leetcode.com/submissions/detail/921383571/) · tests 69/81

Failing input:

```text
13
[[12,8],[2,4],[3,7],[6,8],[11,8],[9,4],[9,7],[12,4],[11,4],[6,4],[1,4],[10,7],[10,4],[1,7],[1,8],[2,7],[8,4],[10,8],[12,7],[5,4],[3,4],[11,7],[7,4],[13,4],[9,8],[13,8]]
9
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
    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
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
            int sz = min((int)qu.size(), k);

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
        }
        

        return taken == n ? ans  : -1;
    }
};
```
