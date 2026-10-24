# 332. Reconstruct Itinerary

[Problem](https://leetcode.com/problems/reconstruct-itinerary/) · Hard · Graph: General BFS/DFS → Eulerian path (Hierholzer)

LeetCode tags: array, string, depth-first-search, graph, sorting, heap-priority-queue, eulerian-circuit, eulerian-path, semi-eulerian-graph

Attempts since Mar 2023: 5 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-03-21 15:06 IST · Accepted · C++

[submission 919393964](https://leetcode.com/submissions/detail/919393964/) · tests 80/80 · runtime 30 ms (beats 5.3%)

```cpp
class Solution {
    vector<vector<int>> gr;
    map<string, multiset<string>> graph;
    map<string, vector<bool>> visited;
    map<string,int> look;

    vector<string> route;
public:
    void traverse(string origin){

        auto &it = graph[origin];
        int i=0;
        while(it.size()){
            string next = *it.begin();
            
            if(!visited[origin][i]){
                visited[origin][i] =true;
                it.erase(it.begin());
                traverse(next);   
            }
                
            i++;
        }
        route.push_back(origin);
    }
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        
        for(auto ticket : tickets){
            graph[ticket[0]].insert(ticket[1]);
        }
        for(auto &row : graph){
            visited[row.first] = vector<bool>(row.second.size(), false);
        }
        // visited["JFK"]
        traverse("JFK");
        reverse(route.begin(), route.end());
        return route;
    }
};
```

## Attempt 2 · 2023-03-22 22:02 IST · Wrong Answer · C++

[submission 920225879](https://leetcode.com/submissions/detail/920225879/) · tests 4/80

Failing input:

```text
[["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
```

Expected:

```text
["JFK","ATL","JFK","SFO","ATL","SFO"]
```

Your output:

```text
["JFK","ATL","JFK","ATL","JFK"]
```

```cpp
class Solution {
    vector<vector<int>> gr;
    map<string, multiset<string>> graph;
    map<string, vector<bool>> visited;
    map<string,int> look;

    vector<string> route;
    int flights;
public:
    void traverse(string origin){
        if(route.size() == flights +1){
            return;
        }
        auto &it = graph[origin];
        int i=0;
        int n = it.size();
        cout<<origin;
        cout<<"Bool Array :: ";
        for(auto &row : visited){
            // visited[row.first] = vector<bool>(row.second.size()+1, false);
            for(int i=0;i<row.second.size();i++){
                cout<<row.second[i]<<":";
            }
            cout<<"|";
        }
        for(i=0;i<n;i++){
            string next = *it.begin();
            
            if(!visited[origin][i]){
                visited[origin][i] =true;
                // it.erase(it.begin());
                cout<<":"<<next;
                traverse(next);
                cout<<'|';   
            }
              
        }
        
        route.push_back(origin);
    }
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        flights = tickets.size();
        for(auto ticket : tickets){
            graph[ticket[0]].insert(ticket[1]);
        }
        for(auto &row : graph){
            visited[row.first] = vector<bool>(row.second.size(), false);
        }
        cout<<"Bool Array :: ";
        for(auto &row : visited){
            // visited[row.first] = vector<bool>(row.second.size()+1, false);
            for(int i=0;i<row.second.size();i++){
                cout<<row.second[i]<<":";
            }
            cout<<"|";
        }
        // visited["JFK"]
        traverse("JFK");
        reverse(route.begin(), route.end());
        return route;
    }
};
```

## Attempt 3 · 2023-03-22 22:05 IST · Wrong Answer · C++

[submission 920227119](https://leetcode.com/submissions/detail/920227119/) · tests 4/80

Failing input:

```text
[["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
```

Expected:

```text
["JFK","ATL","JFK","SFO","ATL","SFO"]
```

Your output:

```text
["JFK","ATL","JFK","ATL","JFK"]
```

```cpp
class Solution {
    vector<vector<int>> gr;
    map<string, multiset<string>> graph;
    map<string, vector<bool>> visited;
    map<string,int> look;

    vector<string> route;
    int flights;
public:
    void traverse(string origin){
        if(route.size() == flights +1){
            return;
        }
        auto &it = graph[origin];
        int i=0;
        int n = it.size();
        cout<<origin;
        cout<<"Bool Array :: ";
        for(auto &row : visited){
            // visited[row.first] = vector<bool>(row.second.size()+1, false);
            for(int i=0;i<row.second.size();i++){
                cout<<row.second[i]<<":";
            }
            cout<<"|";
        }
        for(i=0;i<n;i++){
            string next = *it.begin();
            
            if(!visited[origin][i]){
                visited[origin][i] =true;
                // it.erase(it.begin());
                cout<<":"<<next;
                traverse(next);
                cout<<'|';   
            }
              
        }
        
        route.push_back(origin);
    }
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        flights = tickets.size();
        for(auto ticket : tickets){
            graph[ticket[0]].insert(ticket[1]);
        }
        for(auto &row : graph){
            visited[row.first] = vector<bool>(row.second.size(), false);
        }
        cout<<"Bool Array :: ";
        for(auto &row : visited){
            // visited[row.first] = vector<bool>(row.second.size()+1, false);
            for(int i=0;i<row.second.size();i++){
                cout<<row.second[i]<<":";
            }
            cout<<"|";
        }
        // visited["JFK"]
        traverse("JFK");
        reverse(route.begin(), route.end());
        return route;
    }
};
```

## Attempt 4 · 2023-03-22 22:05 IST · Accepted · C++

[submission 920227362](https://leetcode.com/submissions/detail/920227362/) · tests 80/80 · runtime 34 ms (beats 5.3%)

```cpp
class Solution {
    vector<vector<int>> gr;
    map<string, multiset<string>> graph;
    map<string, vector<bool>> visited;
    map<string,int> look;

    vector<string> route;
public:
    void traverse(string origin){

        auto &it = graph[origin];
        int i=0;
        while(it.size()){
            string next = *it.begin();
            
            if(!visited[origin][i]){
                visited[origin][i] =true;
                it.erase(it.begin());
                traverse(next);   
            }
                
            i++;
        }
        route.push_back(origin);
    }
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        
        for(auto ticket : tickets){
            graph[ticket[0]].insert(ticket[1]);
        }
        for(auto &row : graph){
            visited[row.first] = vector<bool>(row.second.size(), false);
        }
        // visited["JFK"]
        traverse("JFK");
        reverse(route.begin(), route.end());
        return route;
    }
};
```

## Attempt 5 · 2023-12-29 04:18 IST · Accepted · Python3

[submission 1130928739](https://leetcode.com/submissions/detail/1130928739/) · tests 81/81 · runtime 84 ms (beats 15.7%)

```python
class Solution:
    def findItinerary(self, tickets: List[List[str]]) -> List[str]:
        # def findItinerary(tickets):
        # Create a graph from tickets
        graph = defaultdict(list)
        for src, dest in sorted(tickets, reverse=True):
            graph[src].append(dest)

        # Greedy DFS to find itinerary
        def dfs(airport):
            while graph[airport]:
                dfs(graph[airport].pop())
            itinerary.append(airport)

        itinerary = []
        dfs("JFK")
        return itinerary[::-1]
```
