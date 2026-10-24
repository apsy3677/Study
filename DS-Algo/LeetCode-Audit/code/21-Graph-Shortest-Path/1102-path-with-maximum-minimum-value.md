# 1102. Path With Maximum Minimum Value

[Problem](https://leetcode.com/problems/path-with-maximum-minimum-value/) · Medium · Graph: Shortest Path → Max-min Dijkstra

LeetCode tags: array, binary-search, depth-first-search, breadth-first-search, union-find, heap-priority-queue, matrix, dijkstra

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-03-24 15:47 IST · Accepted · C++

[submission 921232137](https://leetcode.com/submissions/detail/921232137/) · tests 85/85 · runtime 370 ms (beats 14.7%)

```cpp
// class Solution {
// public:
//     bool bfs (){
//         nt n = grid.size();
//         int m = grid[0].size();

//         vector<vector<int>> diff = {{0,1}, {0,-1}, {1,0}, {-1,0}};
//         vector<vector<int>> vis(n, vector<int> (m, 0));
//         qu.push({0,0,grid[0][0]});
//         vis[0][0] =1;

//         int ans = 0;
//         while(!qu.empty()){
//             int sz = qu.size();
//             // sz =0;
//             for(int i=0;i<sz;i++){
//                 auto &t = qu.front();
//                 qu.pop();

//                 int x = t[0], y=t[1];

//                 int pathMin = t[3];

//                 if(x==n-1 && y==n-1){
//                     ans = max(ans, pathMin);
//                     continue;
//                 }

//                 for(int i=0;i<diff.size();i++){
//                     int newX = x + diff[i][0];
//                     int newY = y + diff[i][1];
//                     if(newX<0 || newX>=n || newY<0 || newY>=m || vis[newX][newY]){
//                         continue;
//                     vis[newX][newY] = 1;
//                     qu.push({newX, newY, min(pathMin, grid[newX][newY])});
//                 }
//                 }

//             }
//         }
//     }
//     int maximumMinimumPath(vector<vector<int>>& grid) {
//         queue<vector<int>> qu;

//         int n = grid.size();
//         int m = grid[0].size();

//         vector<vector<int>> diff = {{0,1}, {0,-1}, {1,0}, {-1,0}};
//         vector<vector<int>> vis(n, vector<int> (m, 0));
//         qu.push({0,0,grid[0][0]});
//         vis[0][0] =1;

//         int ans = 0;
//         while(!qu.empty()){
//             int sz = qu.size();
//             // sz =0;
//             for(int i=0;i<sz;i++){
//                 auto &t = qu.front();
//                 qu.pop();

//                 int x = t[0], y=t[1];

//                 int pathMin = t[3];

//                 if(x==n-1 && y==n-1){
//                     ans = max(ans, pathMin);
//                     continue;
//                 }

//                 for(int i=0;i<diff.size();i++){
//                     int newX = x + diff[i][0];
//                     int newY = y + diff[i][1];
//                     if(newX<0 || newX>=n || newY<0 || newY>=m || vis[newX][newY]){
//                         continue;
//                     vis[newX][newY] = 1;
//                     qu.push({newX, newY, min(pathMin, grid[newX][newY])});
//                 }
//                 }

//             }
//         }

//         return ans;
//     }
// };

class Solution {
private:
    const int dir[5] = {0, 1, 0, -1, 0};
    
    int rSize, cSize;
    
    struct Slot {
    public:
        int r, c, m;
        
        bool operator < (const Slot &otherSlot) const {
            return m < otherSlot.m;
        }
        
        Slot(int _r, int _c, int _m) {
            r = _r;
            c = _c;
            m = _m;
        }
    };
    
    bool outOfBound(int r, int c) {
        if (r < 0 || c < 0 || r >= rSize || c >= cSize) return true;
        return false;
    }
    
    bool reachGoal(int r, int c) {
        return (r == rSize - 1 && c == cSize - 1);
    }
public:
    int maximumMinimumPath(vector<vector<int>>& grid) {
        rSize = grid.size();
        cSize = grid[0].size();
        
        priority_queue<Slot> priQ;
        vector<vector<bool>> memo (rSize, vector<bool> (cSize, false));
        
        priQ.emplace(0, 0, grid[0][0]);
        
        while (!priQ.empty()) {
            int currR = priQ.top().r;
            int currC = priQ.top().c;
            int currM = priQ.top().m;
            
            priQ.pop();
            
            if (memo[currR][currC]) continue;
            if (reachGoal(currR, currC)) return currM;
            
            memo[currR][currC] = true;
            
            for (int i = 0; i < 4; i++) {
                int nextR = currR + dir[i];
                int nextC = currC + dir[i + 1];
                
                if (outOfBound(nextR, nextC)) continue;
                if (memo[nextR][nextC]) continue;
                
                priQ.emplace(nextR, nextC, min(currM, grid[nextR][nextC]));
            }
        }
        
        return -1; // exception, cannot reach goal
    }
};
```

## Attempt 2 · 2023-03-24 17:18 IST · Accepted · C++

[submission 921265807](https://leetcode.com/submissions/detail/921265807/) · tests 85/85 · runtime 379 ms (beats 14.7%)

```cpp
class Solution {
public:
struct PQNode{
    int r,c,min;

    bool operator < (const PQNode & other)const{
        return min < other.min;
    }
    PQNode(int _r, int _c, int _min):r(_r), c(_c), min(_min){

    }
};
    bool bfs (vector<vector<int>>& grid){
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<int>> diff = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        vector<vector<int>> vis(n, vector<int> (m, 0));
        queue<vector<int>> qu;
        qu.push({0,0,grid[0][0]});
        vis[0][0] =1;

        int ans = 0;
        while(!qu.empty()){
            int sz = qu.size();
            // sz =0;
            for(int i=0;i<sz;i++){
                auto &t = qu.front();
                qu.pop();

                int x = t[0], y=t[1];

                int pathMin = t[3];

                if(x==n-1 && y==n-1){
                    ans = max(ans, pathMin);
                    continue;
                }

                for(int i=0;i<diff.size();i++){
                    int newX = x + diff[i][0];
                    int newY = y + diff[i][1];
                    if(newX<0 || newX>=n || newY<0 || newY>=m || vis[newX][newY])
                        continue;
                    vis[newX][newY] = 1;
                    qu.push({newX, newY, min(pathMin, grid[newX][newY])});
                
                }

            }
        }
        return -1;
    }
    static bool comp(const vector<int> &a, const vector<int> &b){
        return a[2]<b[2];
    }
    int maximumMinimumPath(vector<vector<int>>& grid) {

        int n = grid.size();
        int m = grid[0].size();

        // return bfs(grid);

        vector<vector<int>> diff = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        vector<vector<int>> vis(n, vector<int> (m, 0));

        priority_queue<PQNode> qu;

        qu.push(PQNode(0,0,grid[0][0]));
        // vis[0][0] =1;

        int ans = 0;
        while(!qu.empty()){
            // int sz = qu.size();
            // sz =0;
            // for(int i=0;i<sz;i++){
                auto t = qu.top();
                qu.pop();

                int x = t.r, y=t.c;

                int pathMin = t.min;
                if(x<0 || x>=n || y<0 || y>=m || vis[x][y]){
                    continue;
                }
                
                if(x==n-1 && y==m-1){
                    return pathMin;
                    // ans = max(ans, pathMin);
                    // return ans;
                }
                vis[x][y] = 1;
                for(int i=0;i<diff.size();i++){
                    int newX = x + diff[i][0];
                    int newY = y + diff[i][1];
                    if(newX<0 || newX>=n || newY<0 || newY>=m || vis[newX][newY]){
                        continue;
                    }
                    // vis[newX][newY] = 1;
                    qu.push(PQNode(newX, newY, min(pathMin, grid[newX][newY])));
                }

            // }
        }

        return ans;
    }
};

// class Solution {
// private:
//     const int dir[5] = {0, 1, 0, -1, 0};
    
//     int rSize, cSize;
    
//     struct Slot {
//     public:
//         int r, c, m;
        
//         bool operator < (const Slot &otherSlot) const {
//             return m < otherSlot.m;
//         }
        
//         Slot(int _r, int _c, int _m) {
//             r = _r;
//             c = _c;
//             m = _m;
//         }
//     };
    
//     bool outOfBound(int r, int c) {
//         if (r < 0 || c < 0 || r >= rSize || c >= cSize) return true;
//         return false;
//     }
    
//     bool reachGoal(int r, int c) {
//         return (r == rSize - 1 && c == cSize - 1);
//     }
// public:
//     int maximumMinimumPath(vector<vector<int>>& grid) {
//         rSize = grid.size();
//         cSize = grid[0].size();
        
//         priority_queue<Slot> priQ;
//         vector<vector<bool>> memo (rSize, vector<bool> (cSize, false));
        
//         priQ.emplace(0, 0, grid[0][0]);
        
//         while (!priQ.empty()) {
//             int currR = priQ.top().r;
//             int currC = priQ.top().c;
//             int currM = priQ.top().m;
            
//             priQ.pop();
            
//             if (memo[currR][currC]) continue;
//             if (reachGoal(currR, currC)) return currM;
            
//             memo[currR][currC] = true;
            
//             for (int i = 0; i < 4; i++) {
//                 int nextR = currR + dir[i];
//                 int nextC = currC + dir[i + 1];
                
//                 if (outOfBound(nextR, nextC)) continue;
//                 if (memo[nextR][nextC]) continue;
                
//                 priQ.emplace(nextR, nextC, min(currM, grid[nextR][nextC]));
//             }
//         }
        
//         return -1; // exception, cannot reach goal
//     }
// };
```
