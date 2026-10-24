# 815. Bus Routes

[Problem](https://leetcode.com/problems/bus-routes/) · Hard · Graph: General BFS/DFS → BFS over routes

LeetCode tags: array, hash-table, breadth-first-search

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-03-23 02:10 IST · Accepted · C++

[submission 920357910](https://leetcode.com/submissions/detail/920357910/) · tests 46/46 · runtime 427 ms (beats 28.7%)

```cpp
class Solution {
public:
    //to find out whether bus stops has any element common or not 
    bool connected(vector<int> a,vector<int> b){
        int i=0,j=0;
        while(i<a.size()&&j<b.size()){
            if(a[i]==b[j]) return 1;
            else if(a[i]<b[j]) i++;
            else j++;
        }
        return 0;
    }
    //for finding if this stop is includes in route or not
    bool present(vector<int> a,int s){
        int i=0,h=a.size()-1;
        while(i<=h){
            int m=i+(h-i)/2;
            if(a[m]==s) return 1;
            else if(a[m]<s) i=m+1;
            else h=m-1;
        }
        return 0;
    }
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        unordered_map<int,vector<int>> m;
        int n=routes.size();
        if(source==target) return 0;
        for(int i=0;i<n;i++){
            sort(routes[i].begin(),routes[i].end()); 
        }
        //making a graph of bus stops if they have an stop in common
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(connected(routes[i],routes[j])){
                    m[i].push_back(j);
                    m[j].push_back(i);
                }
            }
        }
        //applying BFS on BUS STOPS
        queue<int> q;
        vector<bool> vis(n,0);
        for(int i=0;i<n;i++){
            if(present(routes[i],source)){
                vis[i]=1;
                q.push(i); 
            }
        }
        int ans=1;
        while(!q.empty()){
            int s=q.size();
            while(s--){
               int x1=q.front();q.pop();
                if(present(routes[x1],target)){
                    return ans;
                }
                for(auto x:m[x1]){
                    if(!vis[x]){
                        q.push(x);
                        vis[x]=1;
                    }
                }
            }
            ans++;
        }
        return -1;
    }
};
```

## Attempt 2 · 2023-03-23 02:10 IST · Accepted · C++

[submission 920358035](https://leetcode.com/submissions/detail/920358035/) · tests 46/46 · runtime 427 ms (beats 28.7%)

```cpp
class Solution {
public:
    //to find out whether bus stops has any element common or not 
    bool connected(vector<int> a,vector<int> b){
        int i=0,j=0;
        while(i<a.size()&&j<b.size()){
            if(a[i]==b[j]) return 1;
            else if(a[i]<b[j]) i++;
            else j++;
        }
        return 0;
    }
    //for finding if this stop is includes in route or not
    bool present(vector<int> a,int s){
        int i=0,h=a.size()-1;
        while(i<=h){
            int m=i+(h-i)/2;
            if(a[m]==s) return 1;
            else if(a[m]<s) i=m+1;
            else h=m-1;
        }
        return 0;
    }
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        unordered_map<int,vector<int>> m;
        int n=routes.size();
        if(source==target) return 0;
        for(int i=0;i<n;i++){
            sort(routes[i].begin(),routes[i].end()); 
        }
        //making a graph of bus stops if they have an stop in common
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(connected(routes[i],routes[j])){
                    m[i].push_back(j);
                    m[j].push_back(i);
                }
            }
        }
        //applying BFS on BUS STOPS
        queue<int> q;
        vector<bool> vis(n,0);
        for(int i=0;i<n;i++){
            if(present(routes[i],source)){
                vis[i]=1;
                q.push(i); 
            }
        }
        int ans=1;
        while(!q.empty()){
            int s=q.size();
            while(s--){
               int x1=q.front();q.pop();
                if(present(routes[x1],target)){
                    return ans;
                }
                for(auto x:m[x1]){
                    if(!vis[x]){
                        q.push(x);
                        vis[x]=1;
                    }
                }
            }
            ans++;
        }
        return -1;
    }
};
```
