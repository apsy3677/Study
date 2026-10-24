# 419. Battleships in a Board

[Problem](https://leetcode.com/problems/battleships-in-a-board/) · Medium · Graph: Grid BFS/DFS → Count heads

LeetCode tags: array, depth-first-search, matrix

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-04-02 01:02 IST · Accepted · C++

[submission 926154720](https://leetcode.com/submissions/detail/926154720/) · tests 27/27 · runtime 6 ms (beats 3.0%)

```cpp
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        int ans = 0;
        for (int i = 0; i < board.size(); i++)
            for (int j = 0; j < board[0].size(); j++)
                if ('X' == board[i][j] && (!i || '.' == board[i - 1][j]) && (!j || '.' == board[i][j - 1]))
                    ans++;
        return ans;
    }
};
```

## Attempt 2 · 2023-04-02 01:03 IST · Accepted · C++

[submission 926155176](https://leetcode.com/submissions/detail/926155176/) · tests 27/27 · runtime 12 ms (beats 3.0%)

```cpp
// class Solution {
// public:
//     int countBattleships(vector<vector<char>>& board) {
//         int ans = 0;
//         for (int i = 0; i < board.size(); i++)
//             for (int j = 0; j < board[0].size(); j++)
//                 if ('X' == board[i][j] && (!i || '.' == board[i - 1][j]) && (!j || '.' == board[i][j - 1]))
//                     ans++;
//         return ans;
//     }

// };
class Solution {
    void dfs(vector<vector<char>>& board, int i, int j){
        if (i<0 || i>=board.size() || j<0 || j>=board[0].size() ) return;
        if (board[i][j]=='.') return;
        board[i][j]='.';
        dfs(board, i-1, j);
        dfs(board, i+1, j);
        dfs(board, i, j-1);
        dfs(board, i, j+1);
    }
    
public:
    int countBattleships(vector<vector<char>>& board) {
        if (board.size()==0) return 0;
        int count = 0;
        for (int i=0; i<board.size(); i++){
            for (int j=0; j<board[0].size();j++){
                if(board[i][j]=='X') {
                    count++;
                    dfs(board, i, j);//sink the ship
                }
            }
        }
        return count;
    }
};
```
