# 787. Cheapest Flights Within K Stops

[Problem](https://leetcode.com/problems/cheapest-flights-within-k-stops/) · Medium · Graph: Shortest Path → Bellman-Ford / BFS with k stops

LeetCode tags: dynamic-programming, depth-first-search, breadth-first-search, graph, heap-priority-queue, shortest-path

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-04-30 13:35 IST · Accepted · C++

[submission 942009113](https://leetcode.com/submissions/detail/942009113/) · tests 52/52 · runtime 29 ms (beats 10.8%)

```cpp
class Solution {
    typedef pair<int,pair<int,int>> piii;
    typedef pair<int,int> pii;
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // priority_queue<piii, vector<piii>, greater<piii>> pq;
        queue<piii> qu;
        vector<pii> adj[n];
        vector<int> dist(n, 1e9);

        for(auto flight : flights){
            adj[flight[0]].push_back({flight[1], flight[2]});
        }
        qu.push({0,{src,0}});

        while(!qu.empty()){
            int sz = qu.size();
            while(sz--){
                auto it = qu.front(); qu.pop();
                int stops = it.first;
                int node = it.second.first;
                int price = it.second.second;

                if(stops > k) continue;

                for(auto it : adj[node]){
                    int adjNode = it.first;
                    int edgeWt = it.second;

                    // <=k coz k are stops in between and dest can be another
                    if(price + edgeWt < dist[adjNode] && stops <=k){
                        dist[adjNode]= price + edgeWt;
                        qu.push({stops+1, {adjNode, dist[adjNode]}});
                    }
                }
            }
        }
        if(dist[dst] == 1e9) return -1;
        return dist[dst];
    }
};
```

## Attempt 2 · 2023-04-30 13:38 IST · Accepted · C++

[submission 942009995](https://leetcode.com/submissions/detail/942009995/) · tests 52/52 · runtime 24 ms (beats 11.2%)

```cpp
class Solution {
    typedef pair<int,pair<int,int>> piii;
    typedef pair<int,int> pii;
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // priority_queue<piii, vector<piii>, greater<piii>> pq;
        queue<piii> qu;
        vector<pii> adj[n];
        vector<int> dist(n, 1e9);

        for(auto flight : flights){
            adj[flight[0]].push_back({flight[1], flight[2]});
        }
        qu.push({0,{src,0}});

        // E = flights.size() TC
        while(!qu.empty()){
            int sz = qu.size();
            while(sz--){
                auto it = qu.front(); qu.pop();
                int stops = it.first;
                int node = it.second.first;
                int price = it.second.second;

                if(stops > k) continue;

                for(auto it : adj[node]){
                    int adjNode = it.first;
                    int edgeWt = it.second;

                    // <=k coz k are stops in between and dest can be another
                    if(price + edgeWt < dist[adjNode] && stops <=k){
                        dist[adjNode]= price + edgeWt;
                        qu.push({stops+1, {adjNode, dist[adjNode]}});
                    }
                }
            }
        }
        if(dist[dst] == 1e9) return -1;
        return dist[dst];
    }
};
```
