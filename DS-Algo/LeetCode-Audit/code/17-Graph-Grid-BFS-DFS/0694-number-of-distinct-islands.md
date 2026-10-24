# 694. Number of Distinct Islands

[Problem](https://leetcode.com/problems/number-of-distinct-islands/) · Medium · Graph: Grid BFS/DFS → Shape signature

LeetCode tags: array, hash-table, depth-first-search, breadth-first-search, union-find, sorting, matrix, hash-function

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-04-29 12:01 IST · Accepted · C++

[submission 941417839](https://leetcode.com/submissions/detail/941417839/) · tests 759/759 · runtime 296 ms (beats 5.6%)

```cpp
class Solution {
    vector<vector<int>> diff = {{0,1}, {0,-1}, {1,0}, {-1,0}};

    void dfs(int x, int y, vector<vector<int>>& vis, vector<vector<int>>& grid, vector<pair<int,int>> &island, int r, int c){
        int n = grid.size();
        int m = grid[0].size();
        cout<<x<<"|"<<y<<"|"<<grid[x][y]<<" ";
        vis[x][y]=1;
        island.push_back({x-r, y-c});
        int dx[] ={-1,0,1,0};
        int dy[] ={0,-1,0,1};
        for(int i=0;i<4;i++){
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx>=0 && nx<n && ny>=0 && ny<m && !vis[nx][ny] && grid[nx][ny]){
                // cout<<nx<<"|"<<ny<<"|"<<grid[nx][ny]<<" ";
                dfs(nx, ny, vis, grid, island, r, c);
            }
        }
    }
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<int>> vis(n, vector<int>(m, 0));
        set<vector<pair<int,int>>> st;

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(!vis[i][j] && grid[i][j]==1){
                    vector<pair<int,int>> island;
                    cout<<"DFS ";
                    dfs(i,j,vis,grid,island,i,j);
                    st.insert(island);
                    cout<<"island ";
                    for(auto [f,s]: island) 
                        cout<<f<<"|"<<s<<" ";
                    cout<<"::";
                }
            }
        }
        return st.size();
    }
};
```

## Attempt 2 · 2023-10-18 14:19 IST · Accepted · C++

[submission 1078223567](https://leetcode.com/submissions/detail/1078223567/) · tests 759/759 · runtime 53 ms (beats 11.7%)

```cpp
class Solution {

private: 
    void dfs(pair<int,int> node, vector<vector<int>>& grid, vector<vector<int>>& vis, pair<int,int> base, set<pair<int,int>>& str) {
        int n = grid.size();
        int m = grid[0].size();
        vis[node.first][node.second] = 1;
        str.insert({(node.first - base.first), (node.second - base.second)});
        int delRow[] = {-1, 0, 1, 0};
        int delCol[] = {0, 1, 0, -1};
        for (int i=0;i<4;i++) {
            int row = node.first + delRow[i];
            int col = node.second + delCol[i];
            if(isValid(row, col, n, m) && grid[row][col] == 1 && vis[row][col] == 0) {
                dfs({row,col}, grid, vis, base, str);
            }
        }
    }

    bool isValid(int x, int y, int n, int m) {
        return x>=0 && x<n && y>=0 && y<m;
    }
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> vis(n , vector<int> (m, 0));
        set<set<pair<int,int>>> di;
        for(int i=0;i<n;i++) {
            for (int j=0;j<m;j++) {
                if(vis[i][j] != 1 && grid[i][j] == 1) {
                    set<pair<int,int>> str;
                    dfs({i,j}, grid, vis, {i,j}, str);
                    di.insert(str);
                }
            }
        }
        return di.size();
    }
};
```
