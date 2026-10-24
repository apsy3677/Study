# 1463. Cherry Pickup II

[Problem](https://leetcode.com/problems/cherry-pickup-ii/) · Hard · DP: Grid / 2D → Two robots (3D state)

LeetCode tags: array, dynamic-programming, matrix

Attempts since Mar 2023: 7 · accepted: 6 · failed before first AC: 0

## Attempt 1 · 2023-03-12 15:44 IST · Accepted · C++

[submission 913747384](https://leetcode.com/submissions/detail/913747384/) · tests 59/59 · runtime 565 ms (beats 5.0%)

```cpp
class Solution {
public:
    int n,m;
    vector<vector<vector<vector<int>>>> dp;
    vector<int> move = {-1,0,1};
    int recur(int x, int y, int x1, int y1, vector<vector<int>>& grid ){
        if(x>=n || y>=m || x1>=n ||y1>=m || x<0 || y<0 || x1<0 ||y1<0 ){
            return 0;
        }
        if(dp[x][y][x1][y1] != -1)
            return dp[x][y][x1][y1];
        int ans = grid[x][y] + (x1 ==x && y==y1 ? 0 : grid[x1][y1]);
        if(x==n-1){
            dp[x][y][x1][y1] = ans;
            return ans;
        }
        
        int max_ans =0;
        for(int i=0;i<move.size();i++){
            int dy = move[i];
            for(int j=0;j<move.size();j++){
                max_ans = max(max_ans, recur(x+1,y+dy,x1+1,y1+move[j],grid));
            }
        }

        dp[x][y][x1][y1] = ans + max_ans;
        return dp[x][y][x1][y1];
    }

    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();
        m = grid[0].size();
        dp.resize(n+1, vector<vector<vector<int>>>(m+1, vector<vector<int>>(n+1, vector<int>(m+1, -1))));

        int ans = recur(0,0,0,m-1,grid);
        return ans;
    }
};
```

## Attempt 2 · 2023-03-12 17:00 IST · Accepted · C++

[submission 913776663](https://leetcode.com/submissions/detail/913776663/) · tests 59/59 · runtime 142 ms (beats 5.0%)

```cpp
class Solution {
public:
    int n,m;
    vector<vector<vector<vector<int>>>> dp;
    vector<int> move = {-1,0,1};
    int recur(int x, int y, int x1, int y1, vector<vector<int>>& grid ){
        if(x>=n || y>=m || x1>=n ||y1>=m || x<0 || y<0 || x1<0 ||y1<0 ){
            return 0;
        }
        if(dp[x][y][x1][y1] != -1)
            return dp[x][y][x1][y1];
        int ans = grid[x][y] + (x1 ==x && y==y1 ? 0 : grid[x1][y1]);
        if(x==n-1){
            dp[x][y][x1][y1] = ans;
            return ans;
        }
        
        int max_ans =0;
        for(int i=0;i<move.size();i++){
            int dy = move[i];
            for(int j=0;j<move.size();j++){
                max_ans = max(max_ans, recur(x+1,y+dy,x1+1,y1+move[j],grid));
            }
        }
 
        dp[x][y][x1][y1] = ans + max_ans;
        return dp[x][y][x1][y1];
    }



    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();
        m = grid[0].size();
        return iter(grid);
        // dp.resize(n+1, vector<vector<vector<int>>>(m+1, vector<vector<int>>(n+1, vector<int>(m+1, -1))));

        // int ans = recur(0,0,0,m-1,grid);
        // return ans;
    }

    int iter(vector<vector<int>>& grid){
        n = grid.size();
        m = grid[0].size();
        vector<vector<vector<int>>> 
        dp(n+1, vector<vector<int>>(m+1, vector<int>(m+1,0)));
        for(int i=n-1;i>=0;i--){
            for(int j=m-1;j>=0;j--){
                for(int k=m-1;k>=0;k--){
                    int ans =0;
                    ans += grid[i][j] + (j!=k ? grid[i][k] : 0);

                    if(i==n-1){
                        dp[i][j][k] = ans;
                        continue;
                    }
                    int max_ans =0;
                    for(int y=j-1;y<=j+1;y++){
                        for(int y1=k-1;y1<=k+1;y1++){
                            if(y>=0 && y<m && y1>=0 &&y1<m){
                                max_ans = max(max_ans, dp[i+1][y][y1]);
                            }
                        }
                    }
                    ans+= max_ans;
                    dp[i][j][k] = ans;
                }
            }
        }
        return dp[0][0][m-1];
        
    }
};
```

## Attempt 3 · 2023-04-02 10:54 IST · Accepted · C++

[submission 926397708](https://leetcode.com/submissions/detail/926397708/) · tests 59/59 · runtime 591 ms (beats 5.0%)

```cpp
class Solution {
public:
    int n,m;
    vector<vector<vector<vector<int>>>> dp;
    vector<int> move = {-1,0,1};
    int recur(int x, int y, int x1, int y1, vector<vector<int>>& grid ){
        if(x>=n || y>=m || x1>=n ||y1>=m || x<0 || y<0 || x1<0 ||y1<0 ){
            return 0;
        }
        if(dp[x][y][x1][y1] != -1)
            return dp[x][y][x1][y1];
        int ans = grid[x][y] + (x1 ==x && y==y1 ? 0 : grid[x1][y1]);
        if(x==n-1){
            dp[x][y][x1][y1] = ans;
            return ans;
        }
        
        int max_ans =0;
        for(int i=0;i<move.size();i++){
            int dy = move[i];
            for(int j=0;j<move.size();j++){
                max_ans = max(max_ans, recur(x+1,y+dy,x1+1,y1+move[j],grid));
            }
        }
 
        dp[x][y][x1][y1] = ans + max_ans;
        return dp[x][y][x1][y1];
    }



    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();
        m = grid[0].size();
        // return iter(grid);
        dp.resize(n+1, vector<vector<vector<int>>>(m+1, vector<vector<int>>(n+1, vector<int>(m+1, -1))));

        int ans = recur(0,0,0,m-1,grid);
        return ans;
    }

    int iter(vector<vector<int>>& grid){
        n = grid.size();
        m = grid[0].size();
        vector<vector<vector<int>>> 
        dp(n+1, vector<vector<int>>(m+1, vector<int>(m+1,0)));
        for(int i=n-1;i>=0;i--){
            for(int j=m-1;j>=0;j--){
                for(int k=m-1;k>=0;k--){
                    int ans =0;
                    ans += grid[i][j] + (j!=k ? grid[i][k] : 0);

                    if(i==n-1){
                        dp[i][j][k] = ans;
                        continue;
                    }
                    int max_ans =0;
                    for(int y=j-1;y<=j+1;y++){
                        for(int y1=k-1;y1<=k+1;y1++){
                            if(y>=0 && y<m && y1>=0 &&y1<m){
                                max_ans = max(max_ans, dp[i+1][y][y1]);
                            }
                        }
                    }
                    ans+= max_ans;
                    dp[i][j][k] = ans;
                }
            }
        }
        return dp[0][0][m-1];
        
    }
};
```

## Attempt 4 · 2023-04-02 11:09 IST · Accepted · C++

[submission 926405109](https://leetcode.com/submissions/detail/926405109/) · tests 59/59 · runtime 136 ms (beats 5.0%)

```cpp
class Solution {
public:
    int n,m;
    vector<vector<vector<vector<int>>>> dp;
    vector<int> move = {-1,0,1};
    int recur(int x, int y, int x1, int y1, vector<vector<int>>& grid ){
        if(x>=n || y>=m || x1>=n ||y1>=m || x<0 || y<0 || x1<0 ||y1<0 ){
            return 0;
        }
        if(dp[x][y][x1][y1] != -1)
            return dp[x][y][x1][y1];
        int ans = grid[x][y] + (x1 ==x && y==y1 ? 0 : grid[x1][y1]);
        if(x==n-1){
            dp[x][y][x1][y1] = ans;
            return ans;
        }
        
        int max_ans =0;
        for(int i=0;i<move.size();i++){
            int dy = move[i];
            for(int j=0;j<move.size();j++){
                max_ans = max(max_ans, recur(x+1,y+dy,x1+1,y1+move[j],grid));
            }
        }
 
        dp[x][y][x1][y1] = ans + max_ans;
        return dp[x][y][x1][y1];
    }



    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();
        m = grid[0].size();
        return iter(grid);
        // dp.resize(n+1, vector<vector<vector<int>>>(m+1, vector<vector<int>>(n+1, vector<int>(m+1, -1))));

        // int ans = recur(0,0,0,m-1,grid);
        // return ans;
    }

    int iter(vector<vector<int>>& grid){
        n = grid.size();
        m = grid[0].size();
        vector<vector<vector<int>>> 
        dp(n+1, vector<vector<int>>(m+1, vector<int>(m+1,0)));

        vector<vector<int>> prev(m+1, vector<int>(m+1, 0)), curr(m+1, vector<int>(m+1, 0));
        for(int i=n-1;i>=0;i--){
            for(int j=m-1;j>=0;j--){
                for(int k=m-1;k>=0;k--){
                    int ans =0;
                    ans += grid[i][j] + (j!=k ? grid[i][k] : 0);

                    if(i==n-1){
                        curr[j][k] = ans;
                        // dp[i][j][k] = ans;
                        continue;
                    }
                    int max_ans =0;
                    for(int y=j-1;y<=j+1;y++){
                        for(int y1=k-1;y1<=k+1;y1++){
                            if(y>=0 && y<m && y1>=0 &&y1<m){
                                max_ans = max(max_ans, prev[y][y1]);
                                // max_ans = max(max_ans, dp[i+1][y][y1]);
                            }
                        }
                    }
                    ans+= max_ans;
                    curr[j][k] = ans;
                    // dp[i][j][k] = ans;
                }
            }
            prev = curr;
        }
        return prev[0][m-1];
        
    }
};
```

## Attempt 5 · 2023-05-02 07:35 IST · Time Limit Exceeded · C++

[submission 942944541](https://leetcode.com/submissions/detail/942944541/) · tests 58/59

Failing input:

```text
[[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, ... [9541 more chars]
```

Expected:

```text
0
```

```cpp
class Solution {
public:
    int n,m;
    // vector<vector<vector<vector<int>>>> dp;
    vector<vector<vector<int>>> memo;

    int striver(int r, int c1, int c2, vector<vector<int>>& grid){
        // base case
        if(c1 <0 || c2< 0 || c1 >=m || c2>=m){
            // out of bound
            return -1e8;
        }
        if(r == n-1){
            return memo[r][c1][c2] = c1 == c2 ? grid[r][c1] : grid[r][c1] + grid[r][c2];
        }
        if(memo[r][c1][c2] != -1) return memo[r][c1][c2];

        int maxi = -1e8;
        for(int nc1=-1 ; nc1<=1;nc1++){
            for(int nc2=-1; nc2<=1;nc2++){
                int total = 0;
                if(c1 == c2){
                    total = grid[r][c1];
                }
                else{
                    total = grid[r][c1] + grid[r][c2];
                }
                total += striver(r+1, c1 + nc1, c2 + nc2, grid);
                maxi = max(total, maxi);
            }
        }
        cout<<r<<"|"<<c1<<"|"<<c2<<"::"<<maxi<<" ";

        return memo[r][c1][c2] = maxi;
    }

    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();
        m = grid[0].size();

        memo.resize(n+1, vector<vector<int>>(m+1, vector<int>(m+1,-1)));
        return striver(0,0,m-1,grid);
        // return iter(grid);
        // dp.resize(n+1, vector<vector<vector<int>>>(m+1, vector<vector<int>>(n+1, vector<int>(m+1, -1))));

        // int ans = recur(0,0,0,m-1,grid);
        // return ans;
    }

    int iter(vector<vector<int>>& grid){
        n = grid.size();
        m = grid[0].size();
        vector<vector<vector<int>>> 
        dp(n+1, vector<vector<int>>(m+1, vector<int>(m+1,0)));

        vector<vector<int>> prev(m+1, vector<int>(m+1, 0)), curr(m+1, vector<int>(m+1, 0));
        for(int i=n-1;i>=0;i--){
            for(int j=m-1;j>=0;j--){
                for(int k=m-1;k>=0;k--){
                    int ans =0;
                    ans += grid[i][j] + (j!=k ? grid[i][k] : 0);

                    if(i==n-1){
                        curr[j][k] = ans;
                        // dp[i][j][k] = ans;
                        continue;
                    }
                    int max_ans =0;
                    for(int y=j-1;y<=j+1;y++){
                        for(int y1=k-1;y1<=k+1;y1++){
                            if(y>=0 && y<m && y1>=0 &&y1<m){
                                max_ans = max(max_ans, prev[y][y1]);
                                // max_ans = max(max_ans, dp[i+1][y][y1]);
                            }
                        }
                    }
                    ans+= max_ans;
                    curr[j][k] = ans;
                    // dp[i][j][k] = ans;
                }
            }
            prev = curr;
        }
        return prev[0][m-1];
        
    }
};
```

## Attempt 6 · 2023-05-02 07:37 IST · Accepted · C++

[submission 942944998](https://leetcode.com/submissions/detail/942944998/) · tests 59/59 · runtime 173 ms (beats 5.0%)

```cpp
class Solution {
public:
    int n,m;
    // vector<vector<vector<vector<int>>>> dp;
    vector<vector<vector<int>>> memo;

    int striver(int r, int c1, int c2, vector<vector<int>>& grid){
        // base case
        if(c1 <0 || c2< 0 || c1 >=m || c2>=m){
            // out of bound
            return -1e8;
        }
        if(r == n-1){
            return memo[r][c1][c2] = c1 == c2 ? grid[r][c1] : grid[r][c1] + grid[r][c2];
        }
        if(memo[r][c1][c2] != -1) return memo[r][c1][c2];

        int maxi = -1e8;
        for(int nc1=-1 ; nc1<=1;nc1++){
            for(int nc2=-1; nc2<=1;nc2++){
                int total = 0;
                if(c1 == c2){
                    total = grid[r][c1];
                }
                else{
                    total = grid[r][c1] + grid[r][c2];
                }
                total += striver(r+1, c1 + nc1, c2 + nc2, grid);
                maxi = max(total, maxi);
            }
        }
        // cout<<r<<"|"<<c1<<"|"<<c2<<"::"<<maxi<<" ";

        return memo[r][c1][c2] = maxi;
    }

    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();
        m = grid[0].size();

        memo.resize(n+1, vector<vector<int>>(m+1, vector<int>(m+1,-1)));
        return striver(0,0,m-1,grid);
        // return iter(grid);
        // dp.resize(n+1, vector<vector<vector<int>>>(m+1, vector<vector<int>>(n+1, vector<int>(m+1, -1))));

        // int ans = recur(0,0,0,m-1,grid);
        // return ans;
    }

    int iter(vector<vector<int>>& grid){
        n = grid.size();
        m = grid[0].size();
        vector<vector<vector<int>>> 
        dp(n+1, vector<vector<int>>(m+1, vector<int>(m+1,0)));

        vector<vector<int>> prev(m+1, vector<int>(m+1, 0)), curr(m+1, vector<int>(m+1, 0));
        for(int i=n-1;i>=0;i--){
            for(int j=m-1;j>=0;j--){
                for(int k=m-1;k>=0;k--){
                    int ans =0;
                    ans += grid[i][j] + (j!=k ? grid[i][k] : 0);

                    if(i==n-1){
                        curr[j][k] = ans;
                        // dp[i][j][k] = ans;
                        continue;
                    }
                    int max_ans =0;
                    for(int y=j-1;y<=j+1;y++){
                        for(int y1=k-1;y1<=k+1;y1++){
                            if(y>=0 && y<m && y1>=0 &&y1<m){
                                max_ans = max(max_ans, prev[y][y1]);
                                // max_ans = max(max_ans, dp[i+1][y][y1]);
                            }
                        }
                    }
                    ans+= max_ans;
                    curr[j][k] = ans;
                    // dp[i][j][k] = ans;
                }
            }
            prev = curr;
        }
        return prev[0][m-1];
        
    }
};
```

## Attempt 7 · 2023-05-02 07:52 IST · Accepted · C++

[submission 942950556](https://leetcode.com/submissions/detail/942950556/) · tests 59/59 · runtime 295 ms (beats 5.0%)

```cpp
class Solution {
public:
    int n,m;
    // vector<vector<vector<vector<int>>>> dp;
    vector<vector<vector<int>>> memo;

    int striver(int r, int c1, int c2, vector<vector<int>>& grid){
        // base case
        if(c1 <0 || c2< 0 || c1 >=m || c2>=m){
            // out of bound
            return -1e8;
        }
        if(r == n-1){
            return memo[r][c1][c2] = c1 == c2 ? grid[r][c1] : grid[r][c1] + grid[r][c2];
        }
        if(memo[r][c1][c2] != -1) return memo[r][c1][c2];

        int maxi = -1e8;
        for(int nc1=-1 ; nc1<=1;nc1++){
            for(int nc2=-1; nc2<=1;nc2++){
                int total = 0;
                if(c1 == c2){
                    total = grid[r][c1];
                }
                else{
                    total = grid[r][c1] + grid[r][c2];
                }
                total += striver(r+1, c1 + nc1, c2 + nc2, grid);
                maxi = max(total, maxi);
            }
        }
        // cout<<r<<"|"<<c1<<"|"<<c2<<"::"<<maxi<<" ";

        return memo[r][c1][c2] = maxi;
    }

    int tabulation(vector<vector<int>>& grid){
        n = grid.size();
        m = grid[0].size();
        // write base case
        vector<vector<vector<int>>> 
        dp(n+1, vector<vector<int>>(m+1, vector<int>(m+1,0)));

        for(int c1 = 0;c1<m;c1++){
            for(int c2=0;c2<m;c2++){
                if(c1 == c2){
                    dp[n-1][c1][c2] = grid[n-1][c1];
                }
                else{
                    dp[n-1][c1][c2] = grid[n-1][c1] + grid[n-1][c2];
                }
            }
        }
        // express every state in for loop
        // states r, c1,c2

        for(int r=n-2;r>=0;r--){
            for(int c1 = 0;c1<m;c1++){
                for(int c2=0;c2<m;c2++){
                    int maxi = -1e8;
                    for(int nc1=-1 ; nc1<=1;nc1++){
                        for(int nc2=-1; nc2<=1;nc2++){
                            int total = 0;
                            if(c1 == c2){
                                total = grid[r][c1];
                            }
                            else{
                                total = grid[r][c1] + grid[r][c2];
                            }
                            if(c1 + nc1 >=0 && c1+nc1 <m && c2+nc2 >=0 && c2+nc2 <m){
                                total += dp[r+1][c1+nc1][c2+nc2];
                                maxi = max(total, maxi);
                            }
                        }
                    }
                    dp[r][c1][c2] = maxi;
                }
            }
        }
             
        return dp[0][0][m-1];
    }
    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();
        m = grid[0].size();

        return tabulation(grid);

        // memo.resize(n+1, vector<vector<int>>(m+1, vector<int>(m+1,-1)));
        // return striver(0,0,m-1,grid);
    }

    int iter(vector<vector<int>>& grid){
        n = grid.size();
        m = grid[0].size();
        vector<vector<vector<int>>> 
        dp(n+1, vector<vector<int>>(m+1, vector<int>(m+1,0)));

        vector<vector<int>> prev(m+1, vector<int>(m+1, 0)), curr(m+1, vector<int>(m+1, 0));
        for(int i=n-1;i>=0;i--){
            for(int j=m-1;j>=0;j--){
                for(int k=m-1;k>=0;k--){
                    int ans =0;
                    ans += grid[i][j] + (j!=k ? grid[i][k] : 0);

                    if(i==n-1){
                        curr[j][k] = ans;
                        // dp[i][j][k] = ans;
                        continue;
                    }
                    int max_ans =0;
                    for(int y=j-1;y<=j+1;y++){
                        for(int y1=k-1;y1<=k+1;y1++){
                            if(y>=0 && y<m && y1>=0 &&y1<m){
                                max_ans = max(max_ans, prev[y][y1]);
                                // max_ans = max(max_ans, dp[i+1][y][y1]);
                            }
                        }
                    }
                    ans+= max_ans;
                    curr[j][k] = ans;
                    // dp[i][j][k] = ans;
                }
            }
            prev = curr;
        }
        return prev[0][m-1];
        
    }
};
```
