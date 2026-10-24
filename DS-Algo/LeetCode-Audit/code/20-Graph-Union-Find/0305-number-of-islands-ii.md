# 305. Number of Islands II

[Problem](https://leetcode.com/problems/number-of-islands-ii/) · Hard · Graph: Union-Find → Online DSU

LeetCode tags: array, hash-table, union-find

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2023-04-30 18:51 IST · Wrong Answer · C++

[submission 942114115](https://leetcode.com/submissions/detail/942114115/) · tests 70/162

Failing input:

```text
2
2
[[0,0],[1,1],[0,1]]
```

Expected:

```text
[1,2,1]
```

Your output:

```text
[1,2,2]
```

```cpp
//User function Template for C++
class DisjointSet {
public:
    vector<int> rank, parent, size;
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
public:
    vector<int> numIslands2(int n, int m, vector<vector<int>>& positions) {
        DisjointSet ds ((m)*(n));
        vector<vector<int>> grid(n, vector<int>(m,0));
        int comps =0;
        int dx[] = {-1,0,1,0};
        int dy[] = {0,-1,0,1};
        vector<int> ans;
        for(auto pos : positions){
            int r = pos[0];
            int c = pos[1];
            int u = r*m + c;
            grid[r][c] = 1;
            bool alone = true;
            for(int i=0;i<4;i++){
                int nr = r + dx[i];
                int nc = c + dy[i];
                int v = nr*m + nc;
                if(nr<0 || nr>=n || nc <0 || nc>=m) continue;

                if(grid[nr][nc] == 1){
                    alone = false;
                    ds.unionBySize(u, v);
                }
            }
            if(alone)
                comps++;
            ans.push_back(comps);
             
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-04-30 19:06 IST · Accepted · C++

[submission 942119013](https://leetcode.com/submissions/detail/942119013/) · tests 162/162 · runtime 113 ms (beats 9.7%)

```cpp
//User function Template for C++
class DisjointSet {
public:
    vector<int> rank, parent, size;
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
public:
    vector<int> numIslands2(int n, int m, vector<vector<int>>& positions) {
        DisjointSet ds (m*n);
        vector<vector<int>> grid(n, vector<int>(m,0));
        int comps = 0;
        int dx[] = {-1,0,1,0};
        int dy[] = {0,-1,0,1};
        vector<int> ans;
        for(auto pos : positions){
            int r = pos[0];
            int c = pos[1];
            int u = r*m + c;
            if(grid[r][c] == 1){
                ans.push_back(comps);
                continue;
            }
            grid[r][c] = 1;
            bool alone = true;
            comps++;
            for(int i=0;i<4;i++){
                int nr = r + dx[i];
                int nc = c + dy[i];
                int v = nr*m + nc;
                if(nr<0 || nr>=n || nc <0 || nc>=m) continue;

                if(grid[nr][nc] == 1){
                    alone = false;
                    if(ds.findUPar(u) != ds.findUPar(v)){
                        ds.unionBySize(u, v);
                        comps--;
                    }
                }
            }
            // if(alone)
            //     comps++;
            // else{
            //     comps;
            // }
            ans.push_back(comps);
             
        }
        return ans;
    }
};
```
