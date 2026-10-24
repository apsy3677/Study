# 399. Evaluate Division

[Problem](https://leetcode.com/problems/evaluate-division/) · Medium · Graph: General BFS/DFS → Weighted graph DFS

LeetCode tags: array, string, depth-first-search, breadth-first-search, union-find, graph, shortest-path, bellman-ford-algorithm, floyd-warshall-algorithm

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-03-21 18:58 IST · Accepted · C++

[submission 919497161](https://leetcode.com/submissions/detail/919497161/) · tests 24/24 · runtime 6 ms (beats 2.4%)

```cpp
class Solution {
    typedef pair<string,double> PSD;
    map<string, vector< PSD > >graph;
    
public:
    double dfs(string a, string b, double prod, map<string,bool> &visited){
        visited[a] = true;
        double ans = -1.0;
        
        vector< PSD > &child = graph[a];
        for(auto x : child){

            if(x.first == b){
                ans = prod*x.second;
                break;
            }
            if(visited[x.first]){
                continue;
            }
            ans = dfs(x.first, b, prod*x.second, visited);
            if(ans != -1.0){
                break;
            }
        }
        visited[a] = false;
        return ans;
    }
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        
        for(int i=0;i<equations.size();i++){
            string a = equations[i][0], b = equations[i][1];
            double val = values[i];
            graph[a].push_back({b, val});
            graph[b].push_back({a, 1.0/val});
        }

        vector<double> ans;
        for(int i=0;i<queries.size();i++){
            double res = -1.0;
            string a = queries[i][0], 
                   b = queries[i][1];
            if(graph.find(a) == graph.end() || graph.find(b) == graph.end()){
                ans.push_back(res);
                continue;
            }
            else if(a == b){
                ans.push_back(1.0);
                continue;
            }
            else{
                map<string, bool> visited;
                res = dfs(a,b, 1.0, visited);
            }
            // res = dfs()
            ans.push_back(res);
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-03-21 18:59 IST · Accepted · C++

[submission 919497511](https://leetcode.com/submissions/detail/919497511/) · tests 24/24 · runtime 0 ms (beats 100%)

```cpp
class Solution {
    typedef pair<string,double> PSD;
    map<string, vector< PSD > >graph;
    
public:
    double dfs(string a, string b, double prod, map<string,bool> &visited){
        visited[a] = true;
        double ans = -1.0;
        
        vector< PSD > &child = graph[a];
        for(auto x : child){

            if(x.first == b){
                return prod*x.second;
                // break;
            }
            if(visited[x.first]){
                continue;
            }
            ans = dfs(x.first, b, prod*x.second, visited);
            if(ans != -1.0){
                break;
            }
        }
        visited[a] = false;
        return ans;
    }
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        
        for(int i=0;i<equations.size();i++){
            string a = equations[i][0], b = equations[i][1];
            double val = values[i];
            graph[a].push_back({b, val});
            graph[b].push_back({a, 1.0/val});
        }

        vector<double> ans;
        for(int i=0;i<queries.size();i++){
            double res = -1.0;
            string a = queries[i][0], 
                   b = queries[i][1];
            if(graph.find(a) == graph.end() || graph.find(b) == graph.end()){
                ans.push_back(res);
                continue;
            }
            else if(a == b){
                ans.push_back(1.0);
                continue;
            }
            else{
                map<string, bool> visited;
                res = dfs(a,b, 1.0, visited);
            }
            // res = dfs()
            ans.push_back(res);
        }
        return ans;
    }
};
```

## Attempt 3 · 2023-03-22 22:07 IST · Accepted · C++

[submission 920228516](https://leetcode.com/submissions/detail/920228516/) · tests 24/24 · runtime 0 ms (beats 100%)

```cpp
class Solution {
    typedef pair<string,double> PSD;
    map<string, vector< PSD > >graph;
    
public:
    double dfs(string a, string b, double prod, map<string,bool> &visited){
        visited[a] = true;
        double ans = -1.0;
        
        vector< PSD > &child = graph[a];
        for(auto x : child){

            if(x.first == b){
                return prod*x.second;
                // break;
            }
            if(visited[x.first]){
                continue;
            }
            ans = dfs(x.first, b, prod*x.second, visited);
            if(ans != -1.0){
                break;
            }
        }
        visited[a] = false;
        return ans;
    }
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        
        for(int i=0;i<equations.size();i++){
            string a = equations[i][0], b = equations[i][1];
            double val = values[i];
            graph[a].push_back({b, val});
            graph[b].push_back({a, 1.0/val});
        }

        vector<double> ans;
        for(int i=0;i<queries.size();i++){
            double res = -1.0;
            string a = queries[i][0], 
                   b = queries[i][1];
            if(graph.find(a) == graph.end() || graph.find(b) == graph.end()){
                ans.push_back(res);
                continue;
            }
            else if(a == b){
                ans.push_back(1.0);
                continue;
            }
            else{
                map<string, bool> visited;
                res = dfs(a,b, 1.0, visited);
            }
            // res = dfs()
            ans.push_back(res);
        }
        return ans;
    }
};
```
