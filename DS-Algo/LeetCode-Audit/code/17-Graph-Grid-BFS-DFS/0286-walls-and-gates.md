# 286. Walls and Gates

[Problem](https://leetcode.com/problems/walls-and-gates/) · Medium · Graph: Grid BFS/DFS → Multi-source BFS

LeetCode tags: array, breadth-first-search, matrix

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-03-22 22:40 IST · Accepted · C++

[submission 920247509](https://leetcode.com/submissions/detail/920247509/) · tests 62/62 · runtime 36 ms (beats 18.9%)

```cpp
class Solution {
public:
    vector<vector<int>> diff = {{0,-1}, {0,1}, {-1,0}, {1,0}};
    void wallsAndGates(vector<vector<int>>& rooms) {
        
        // implement bfs from each gate
        // cout<<"INT_MAX "<<INT_MAX;
        int n =rooms.size();
        if(n==0)
            return;
        int m = rooms[0].size();

        queue<pair<int,int>> qu;

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(rooms[i][j] == 0){
                    qu.push({i,j});
                }
            }
        }
        pair<int,int> curr;
        while(!qu.empty()){
            int sz = qu.size();
            for(int i=0;i<sz;i++){
                curr = qu.front();
                // row is curr.first, col is curr.second
                qu.pop();

                for(int j=0;j<diff.size();j++){
                    int r = curr.first + diff[j][0];
                    int c = curr.second+ diff[j][1];

                    if(r<0 || r>=n || c<0 || c>=m || rooms[r][c] != INT_MAX){
                        continue;
                    }
                    rooms[r][c] = rooms[curr.first][curr.second] +1;

                    qu.push({r,c});

                }
                // traverse all children
            }
        }
    }
};
```

## Attempt 2 · 2023-03-22 22:41 IST · Accepted · C++

[submission 920247969](https://leetcode.com/submissions/detail/920247969/) · tests 62/62 · runtime 32 ms (beats 20.6%)

```cpp
class Solution {
public:
    vector<vector<int>> diff = {{0,-1}, {0,1}, {-1,0}, {1,0}};
    void wallsAndGates(vector<vector<int>>& rooms) {
        
        // implement bfs from each gate
        // cout<<"INT_MAX "<<INT_MAX;
        int n =rooms.size();
        if(n==0)
            return;
        int m = rooms[0].size();

        queue<pair<int,int>> qu;

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(rooms[i][j] == 0){
                    qu.push({i,j});
                }
            }
        }
        pair<int,int> curr;
        while(!qu.empty()){
            int sz = qu.size();
            for(int i=0;i<sz;i++){
                curr = qu.front();
                // row is curr.first, col is curr.second
                qu.pop();

                for(int j=0;j<diff.size();j++){
                    int r = curr.first + diff[j][0];
                    int c = curr.second+ diff[j][1];

                    if(r<0 || r>=n || c<0 || c>=m || rooms[r][c] != INT_MAX){
                        continue;
                    }
                    rooms[r][c] = rooms[curr.first][curr.second] +1;

                    qu.push({r,c});

                }
                // traverse all children
            }
        }
    }
};
```
