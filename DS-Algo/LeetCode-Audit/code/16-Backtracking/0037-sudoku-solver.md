# 37. Sudoku Solver

[Problem](https://leetcode.com/problems/sudoku-solver/) · Hard · Backtracking → Constraint search

LeetCode tags: array, hash-table, backtracking, matrix, algorithm-x, dancing-links

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-04-28 13:18 IST · Accepted · C++

[submission 940993417](https://leetcode.com/submissions/detail/940993417/) · tests 6/6 · runtime 52 ms (beats 95.7%)

```cpp
class Solution {
public:
    bool isValid (vector<vector<char>>& board, int r, int c, char ch){
        for(int i=0;i<9;i++){
            // check row and col
            if(board[r][i] == ch ||
               board[i][c] == ch) 
               return false;
            
            if(board[3*(r/3) + i/3][3*(c/3) + i%3] == ch)
                return false;
        }
        return true;
    }
    bool solve (vector<vector<char>>& board){
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[0].size();j++){

                if(board[i][j] == '.'){

                    for(char c='1';c<='9';c++){
                        if(isValid(board, i, j, c)){
                            board[i][j] = c;

                            if(solve(board)){
                                return true;
                            }
                            else{
                                board[i][j] = '.';
                            }
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }
};
```
