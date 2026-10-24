# 51. N-Queens

[Problem](https://leetcode.com/problems/n-queens/) · Hard · Backtracking → Constraint placement

LeetCode tags: array, backtracking, algorithm-x

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-04-28 12:29 IST · Accepted · C++

[submission 940976386](https://leetcode.com/submissions/detail/940976386/) · tests 9/9 · runtime 8 ms (beats 13.1%)

```cpp
class Solution {
public:
    bool validMove(int n, int x, int y){
        return (x <n && x>=0 && y<n && y>=0);
    }
    bool check(vector<string> &board, int n, int x, int y, int dx, int dy){
        bool ret = true;
        while(validMove(n, x, y)){
            x += dx;
            y += dy;
            if(board[x][y] == 'Q'){
                return false;
            }
        }
        return ret;
    }

    bool valid(vector<string> &board, int n, int x, int y){
        bool ret = true;

        return true;
    }
    bool isValid(vector<string> &board, int n, int x, int y){
        int r = x, c=y;

        // left up diagonal
        while(r >=0 && c>=0){
            if(board[r][c] == 'Q') return false;
            r--, c--;
        }
        r = x, c=y;
        // left bottom diagonal
        while(r <n && c>=0){
            if(board[r][c] == 'Q') return false;
            r++, c--;
        }
        r = x, c=y;
        // left row 
        while(c>=0){
            if(board[r][c] == 'Q') return false;
            c--;
        }
        return true;
    }
    void NQueen(int idx, int n, vector<string> &board, vector<vector<string>> & ans){
        if(idx == n){
            // if(valid(board, n)){
                ans.push_back(board);
            // }
            return;
        }

        for(int r=0;r<n;r++){
            // for(int c=0;c<n;c++){
                // if(board[r][c] == 'Q') continue;
                // place queen in column
            if(isValid(board,n,r,idx)){
                board[r][idx] = 'Q';
                NQueen(idx+1,n,board,ans);
                board[r][idx] = '.';
            }
                
            // }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        string s(n,'.');
        vector<string> board(n, s);

        NQueen(0, n, board, ans);

        return ans;
    }
};
```

## Attempt 2 · 2023-04-28 12:40 IST · Accepted · C++

[submission 940980279](https://leetcode.com/submissions/detail/940980279/) · tests 9/9 · runtime 8 ms (beats 13.1%)

```cpp
class Solution {
    vector<int> leftRow, upperDiagonal, lowerDiagonal;
public:
    bool validMove(int n, int x, int y){
        return (x <n && x>=0 && y<n && y>=0);
    }
    bool check(vector<string> &board, int n, int x, int y, int dx, int dy){
        bool ret = true;
        while(validMove(n, x, y)){
            x += dx;
            y += dy;
            if(board[x][y] == 'Q'){
                return false;
            }
        }
        return ret;
    }

    bool valid(vector<string> &board, int n, int x, int y){
        bool ret = true;

        return true;
    }
    bool isValid(vector<string> &board, int n, int x, int y){
        int r = x, c=y;

        // left up diagonal
        while(r >=0 && c>=0){
            if(board[r][c] == 'Q') return false;
            r--, c--;
        }
        r = x, c=y;
        // left bottom diagonal
        while(r <n && c>=0){
            if(board[r][c] == 'Q') return false;
            r++, c--;
        }
        r = x, c=y;
        // left row 
        while(c>=0){
            if(board[r][c] == 'Q') return false;
            c--;
        }
        return true;
    }
    void NQueen(int idx, int n, vector<string> &board, vector<vector<string>> & ans){
        if(idx == n){
            // if(valid(board, n)){
                ans.push_back(board);
            // }
            return;
        }

        for(int r=0;r<n;r++){
            // for(int c=0;c<n;c++){
                // if(board[r][c] == 'Q') continue;
                // place queen in column
            if(isValid(board,n,r,idx)){
                board[r][idx] = 'Q';
                NQueen(idx+1,n,board,ans);
                board[r][idx] = '.';
            }
                
            // }
        }
    }

    void NQueen1(int idx, int n, vector<string> &board, vector<vector<string>> & ans){
        if(idx == n){
            // if(valid(board, n)){
                ans.push_back(board);
            // }
            return;
        }

        for(int r=0;r<n;r++){
           // idx is column 
            if(leftRow[r] ==0  && lowerDiagonal[r + idx] ==0 
                && upperDiagonal[n-1 + idx -r] == 0){
                board[r][idx] = 'Q';
                leftRow[r] = 1;
                lowerDiagonal[r+idx] =1;
                upperDiagonal[n-1 + idx -r]=1;

                NQueen(idx+1,n,board,ans);

                board[r][idx] = '.';
                leftRow[r] = 0;
                lowerDiagonal[r+idx] =0;
                upperDiagonal[n-1 + idx -r]=0;
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        string s(n,'.');
        vector<string> board(n, s);

        leftRow.resize(n,0);
        upperDiagonal.resize(2*n-1, 0);
        lowerDiagonal.resize(2*n-1, 0);

        NQueen1(0, n, board, ans);
        // NQueen(0, n, board, ans);

        return ans;
    }
};
```
