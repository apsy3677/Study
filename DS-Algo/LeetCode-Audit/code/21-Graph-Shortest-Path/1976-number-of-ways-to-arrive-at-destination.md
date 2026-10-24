# 1976. Number of Ways to Arrive at Destination

[Problem](https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/) · Medium · Graph: Shortest Path → Dijkstra + path count

LeetCode tags: dynamic-programming, graph, topological-sort, shortest-path, dijkstra

Attempts since Mar 2023: 3 · accepted: 1 · failed before first AC: 2

## Attempt 1 · 2023-04-30 14:25 IST · Runtime Error · C++

[submission 942025469](https://leetcode.com/submissions/detail/942025469/) · tests 37/54

Failing input:

```text
69
[[1,0,2009],[2,1,9303],[0,3,15992],[3,2,4680],[4,2,12382],[3,4,7702],[4,1,21685],[4,0,23694],[2,5,16321],[4,5,3939],[0,5,27633],[0,6,13594],[6,2,2282],[4,7,1180],[7,2,13562],[7,3,8882],[8,3,11853],[8,4,4151],[0,8,27845],[8,5,212],[8,1,25836],[9,1,262],[8,10,2187],[10,2,18720],[10,6,16438],[10,1,28023],[10,7,5158],[10,0,30032],[3,10,14040],[9,10,27761],[10,5,2399],[10,4,6338],[2,11,25138],[11,5, ... [18038 more chars]
```

Expected:

```text
878220613
```

Runtime error:

```text
Line 32: Char 49: runtime error: signed integer overflow: 1266132950 + 1306823095 cannot be represented in type 'int' (solution.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:41:49
```

```cpp
class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        typedef pair<int,int> pii;
        vector<pii> adj[n];
        for(auto it : roads){
            adj[it[0]].push_back({it[1], it[2]});
            adj[it[1]].push_back({it[0], it[2]});
        }
        vector<int> ways(n,0), dist(n, 1e9);
        int mod = 1e9 + 7;
        ways[0]=1;
        dist[0]=0;
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push({0,0});

        while(!pq.empty()){
            auto it = pq.top(); pq.pop();
            int node = it.second;
            int dis = it.first;

            for(auto iter : adj[node]){
                int adjNode = iter.first;
                int edgeWt = iter.second;

                if(dis + edgeWt < dist[adjNode]){
                    dist[adjNode] = dis+edgeWt;
                    pq.push({dist[adjNode], adjNode});
                    ways[adjNode] = ways[node];
                }
                else if(dis + edgeWt == dist[adjNode]){
                    ways[adjNode] = (ways[node] + ways[adjNode]);
                }
            }
        }
        return ways[n-1]%mod;
    }
};
```

## Attempt 2 · 2023-04-30 14:26 IST · Wrong Answer · C++

[submission 942025751](https://leetcode.com/submissions/detail/942025751/) · tests 52/54

Failing input:

```text
200
[[0,1,1000000000],[1,2,1000000000],[2,3,1000000000],[3,4,1000000000],[4,5,1000000000],[5,6,1000000000],[6,7,1000000000],[7,8,1000000000],[8,9,1000000000],[9,10,1000000000],[10,11,1000000000],[11,12,1000000000],[12,13,1000000000],[13,14,1000000000],[14,15,1000000000],[15,16,1000000000],[16,17,1000000000],[17,18,1000000000],[18,19,1000000000],[19,20,1000000000],[20,21,1000000000],[21,22,10000000 ... [3566 more chars]
```

Expected:

```text
1
```

Your output:

```text
0
```

```cpp
class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        typedef pair<int,int> pii;
        vector<pii> adj[n];
        for(auto it : roads){
            adj[it[0]].push_back({it[1], it[2]});
            adj[it[1]].push_back({it[0], it[2]});
        }
        vector<int> ways(n,0), dist(n, 1e9);
        int mod = 1e9 + 7;
        ways[0]=1;
        dist[0]=0;
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push({0,0});

        while(!pq.empty()){
            auto it = pq.top(); pq.pop();
            int node = it.second;
            int dis = it.first;

            for(auto iter : adj[node]){
                int adjNode = iter.first;
                int edgeWt = iter.second;

                if(dis + edgeWt < dist[adjNode]){
                    dist[adjNode] = dis+edgeWt;
                    pq.push({dist[adjNode], adjNode});
                    ways[adjNode] = ways[node];
                }
                else if(dis + edgeWt == dist[adjNode]){
                    ways[adjNode] = (ways[node] + ways[adjNode])%mod;
                }
            }
        }
        return ways[n-1]%mod;
    }
};
```

## Attempt 3 · 2023-04-30 14:32 IST · Accepted · C++

[submission 942027719](https://leetcode.com/submissions/detail/942027719/) · tests 54/54 · runtime 86 ms (beats 5.3%)

```cpp
class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        typedef pair<long long,int> pii;
        vector<pii> adj[n];
        for(auto it : roads){
            adj[it[0]].push_back({it[1], it[2]});
            adj[it[1]].push_back({it[0], it[2]});
        }
        vector<long long> ways(n,0), dist(n, 1e18);
        int mod = 1e9 + 7;
        ways[0]=1;
        dist[0]=0;
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push({0,0});

        while(!pq.empty()){
            auto it = pq.top(); pq.pop();
            int node = it.second;
            long long dis = it.first;

            for(auto iter : adj[node]){
                int adjNode = iter.first;
                int edgeWt = iter.second;

                if((dis + edgeWt) < dist[adjNode]){
                    dist[adjNode] = dis+edgeWt;
                    pq.push({dist[adjNode], adjNode});
                    ways[adjNode] = ways[node];
                }
                else if(dis + edgeWt == dist[adjNode]){
                    ways[adjNode] = (ways[node] + ways[adjNode])%mod;
                }
            }
        }
        return (int)(ways[n-1]%mod);
    }
};
```
