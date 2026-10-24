# 1377. Frog Position After T Seconds

[Problem](https://leetcode.com/problems/frog-position-after-t-seconds/) · Hard · Graph: General BFS/DFS → BFS with probability

LeetCode tags: tree, depth-first-search, breadth-first-search, graph

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-03-11 14:25 IST · Accepted · C++

[submission 913125591](https://leetcode.com/submissions/detail/913125591/) · tests 204/204 · runtime 15 ms (beats 11.0%)

```cpp
class Solution {
public:
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        vector<double> prob(n+1,0.0);
        vector<bool> visited(n+1,false);
        vector< vector <int> > graph(n+1);

        for(int i=0;i<edges.size();i++){
            graph[edges[i][0]].push_back(edges[i][1]);
            graph[edges[i][1]].push_back(edges[i][0]);
        }
        queue<int> qu;
        qu.push(1);
        prob[1]=1.0;

        while(!qu.empty() && t--){
            int sz = qu.size();
            for(int i=0;i<sz ;i++){
                int v= qu.front();
                qu.pop();
                visited[v] = true;
                int ed_count=0;
                for(auto x: graph[v]){
                    if(!visited[x])
                        ed_count++;
                }

                for(auto x: graph[v]){
                    if(!visited[x]){
                        visited[x]=true;
                        qu.push(x);
                        prob[x] = prob[v]/ed_count;
                    }
                }
                if(ed_count > 0){
                    prob[v] = 0.0;
                }

            }
            
        }
        return prob[target];
    }
};
```

## Attempt 2 · 2023-03-11 15:24 IST · Accepted · C++

[submission 913148665](https://leetcode.com/submissions/detail/913148665/) · tests 204/204 · runtime 26 ms (beats 5.1%)

```cpp
class Solution {
public:

    vector<bool> visited;
    vector< vector <int> > graph;
    double dfs(int v, int t, int target){
        
        int edges = graph[v].size();
        edges = v==1 ? edges: edges -1; // choices to go next
        visited[v] = true;
        if(t == 0 || edges == 0){
            return v==target ? 1.0 : 0.0; 
        }
        double prob =0.0;
        for(auto child: graph[v]){
            if(!visited[child]){
                prob += dfs(child, t-1, target);
            }
        }
        return prob/edges;

    }
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        vector<double> prob(n+1,0.0);
        visited = vector<bool> (n+1,false);
        graph.resize(n+1, vector<int>());

        for(int i=0;i<edges.size();i++){
            graph[edges[i][0]].push_back(edges[i][1]);
            graph[edges[i][1]].push_back(edges[i][0]);
        }

        // dfs solution
        return dfs(1,t,target);

        queue<int> qu;
        qu.push(1);
        prob[1]=1.0;

        while(!qu.empty() && t--){
            int sz = qu.size();
            for(int i=0;i<sz ;i++){
                int v= qu.front();
                qu.pop();
                visited[v] = true;
                int ed_count=0;
                for(auto x: graph[v]){
                    if(!visited[x])
                        ed_count++;
                }

                for(auto x: graph[v]){
                    if(!visited[x]){
                        visited[x]=true;
                        qu.push(x);
                        prob[x] = prob[v]/ed_count;
                    }
                }
                if(ed_count > 0){
                    prob[v] = 0.0;
                }

            }
            
        }
        return prob[target];
    }
};
```
