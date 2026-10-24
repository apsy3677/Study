# 79. Word Search

[Problem](https://leetcode.com/problems/word-search/) · Medium · Backtracking → Grid DFS backtracking

LeetCode tags: array, string, backtracking, depth-first-search, matrix

Attempts since Mar 2023: 15 · accepted: 7 · failed before first AC: 3

## Attempt 1 · 2023-03-27 01:11 IST · Time Limit Exceeded · C++

[submission 922629003](https://leetcode.com/submissions/detail/922629003/) · tests 47/85

Failing input:

```text
[["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"]]
"AAAAAAAAAAAABAA"
```

Expected:

```text
false
```

```cpp
class Solution {
public:
    vector<vector<int>> diff = {{0,1},{0,-1},{1,0},{-1,0}};
    bool dfs(int x, int y, int index, vector<vector<char>>& board, string &word){
        int n = board.size();
        int m = board[0].size();
        if(index == word.size()) return true;
        if(x<0 || x>=n || y<0 || y>=m || board[x][y] != word[index]) return false;

        // if(w == word) return true;
        bool ret = false;
        board[x][y] = '#';
        for(auto d : diff){
            int newX = x + d[0];
            int newY = y + d[1];

            ret = dfs(newX, newY, index +1,board, word);
            if(ret) break;
        }
        board[x][y] = word[index];
        return ret;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size();
        int m = board[0].size();

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(board[i][j] == word[0]){
                    //start dfs
                    bool ret = dfs(i,j,0,board,word);
                    if(ret) return ret;
                }
            }
        }
        return false;
    }
};
```

## Attempt 2 · 2023-03-27 01:13 IST · Time Limit Exceeded · C++

[submission 922629944](https://leetcode.com/submissions/detail/922629944/) · tests 47/85

Failing input:

```text
[["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"]]
"AAAAAAAAAAAABAA"
```

Expected:

```text
false
```

```cpp
class Solution {
public:
    vector<vector<int>> diff = {{0,1},{0,-1},{1,0},{-1,0}};
    bool dfs(int x, int y, int index, vector<vector<char>>& board, string &word){
        int n = board.size();
        int m = board[0].size();
        if(index == word.size()) return true;
        if(x<0 || x>=n || y<0 || y>=m || board[x][y] != word[index]) return false;

        // if(w == word) return true;
        bool ret = false;
        board[x][y] = '#';
        for(auto d : diff){
            int newX = x + d[0];
            int newY = y + d[1];

            ret = dfs(newX, newY, index +1,board, word);
            if(ret) return true;
        }
        board[x][y] = word[index];
        return ret;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size();
        int m = board[0].size();

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(board[i][j] == word[0]){
                    //start dfs
                    bool ret = dfs(i,j,0,board,word);
                    if(ret) return ret;
                }
            }
        }
        return false;
    }
};
```

## Attempt 3 · 2023-03-27 01:16 IST · Time Limit Exceeded · C++

[submission 922631220](https://leetcode.com/submissions/detail/922631220/) · tests 47/85

Failing input:

```text
[["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"]]
"AAAAAAAAAAAABAA"
```

Expected:

```text
false
```

```cpp
class Solution {
public:
    vector<vector<int>> diff = {{0,1},{0,-1},{1,0},{-1,0}};
    bool dfs(int x, int y, int index, vector<vector<char>>& board, string &word){
        int n = board.size();
        int m = board[0].size();
        if(index == word.size()) return true;
        if(x<0 || x>=n || y<0 || y>=m || board[x][y] != word[index]) return false;

        // if(w == word) return true;
        bool ret = false;
        board[x][y] = '#';
        for(auto d : diff){
            int newX = x + d[0];
            int newY = y + d[1];
            if(x<0 || x>=n || y<0 || y>=m) return false;
            ret = dfs(newX, newY, index +1, board, word);
            if(ret) return true;
        }
        board[x][y] = word[index];
        return ret;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size();
        int m = board[0].size();

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(board[i][j] == word[0]){
                    //start dfs
                    bool ret = dfs(i,j,0,board,word);
                    if(ret) return ret;
                }
            }
        }
        return false;
    }
};
```

## Attempt 4 · 2023-03-27 01:20 IST · Accepted · C++

[submission 922632774](https://leetcode.com/submissions/detail/922632774/) · tests 85/85 · runtime 646 ms (beats 32.2%)

```cpp
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
    for (unsigned int i = 0; i < board.size(); i++) 
        for (unsigned int j = 0; j < board[0].size(); j++) 
            if (dfs(board, i, j, word))
                return true;
    return false;
}

bool dfs(vector<vector<char>>& board, int i, int j, string& word) {
    if (!word.size())
        return true;
    if (i<0 || i>=board.size() || j<0 || j>=board[0].size() || board[i][j] != word[0])  
        return false;
    char c = board[i][j];
    board[i][j] = '*';
    string s = word.substr(1);
    bool ret = dfs(board, i-1, j, s) || dfs(board, i+1, j, s) || dfs(board, i, j-1, s) || dfs(board, i, j+1, s);
    board[i][j] = c;
    return ret;
}
    vector<vector<int>> diff = {{0,1},{0,-1},{1,0},{-1,0}};
    // bool dfs(int x, int y, int index, vector<vector<char>>& board, string &word){
    //     int n = board.size();
    //     int m = board[0].size();
    //     if(index == word.size()) return true;
    //     if(x<0 || x>=n || y<0 || y>=m || board[x][y] != word[index]) return false;

    //     // if(w == word) return true;
    //     bool ret = false;
    //     board[x][y] = '#';
    //     for(auto d : diff){
    //         int newX = x + d[0];
    //         int newY = y + d[1];
    //         if(x<0 || x>=n || y<0 || y>=m) return false;
    //         ret = dfs(newX, newY, index +1, board, word);
    //         if(ret) return true;
    //     }
    //     board[x][y] = word[index];
    //     return ret;
    // }
    // bool exist(vector<vector<char>>& board, string word) {
    //     int n = board.size();
    //     int m = board[0].size();

    //     for(int i=0;i<n;i++){
    //         for(int j=0;j<m;j++){
    //             if(board[i][j] == word[0]){
    //                 //start dfs
    //                 bool ret = dfs(i,j,0,board,word);
    //                 if(ret) return ret;
    //             }
    //         }
    //     }
    //     return false;
    // }
};
```

## Attempt 5 · 2023-03-27 01:23 IST · Wrong Answer · C++

[submission 922634309](https://leetcode.com/submissions/detail/922634309/) · tests 78/85

Failing input:

```text
[["a","b"],["c","d"]]
"abcd"
```

Expected:

```text
false
```

Your output:

```text
true
```

```cpp
class Solution {
public:
    vector<vector<int>> diff = {{0,1},{0,-1},{1,0},{-1,0}};
    bool dfs(int x, int y, int index, vector<vector<char>>& board, string &word){
        int n = board.size();
        int m = board[0].size();
        if(index == word.size()) return true;
        if(x<0 || x>=n || y<0 || y>=m || board[x][y] != word[index]) return false;

        // if(w == word) return true;
        bool ret = false;
        char ch = board[x][y];
        board[x][y] = '#';
        word = word.substr(1);
        for(auto d : diff){
            int newX = x + d[0];
            int newY = y + d[1];
            if(x<0 || x>=n || y<0 || y>=m) return false;
            ret = dfs(newX, newY, index, board, word);
            if(ret) return true;
        }
        board[x][y] = ch;
        return ret;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size();
        int m = board[0].size();

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(board[i][j] == word[0]){
                    //start dfs
                    string w = word;
                    bool ret = dfs(i,j,0,board,w);
                    if(ret) return ret;
                }
            }
        }
        return false;
    }
};
```

## Attempt 6 · 2023-03-27 01:28 IST · Time Limit Exceeded · C++

[submission 922636168](https://leetcode.com/submissions/detail/922636168/) · tests 47/85

Failing input:

```text
[["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"]]
"AAAAAAAAAAAABAA"
```

Expected:

```text
false
```

```cpp
class Solution {
public:
    vector<vector<int>> diff = {{0,1},{0,-1},{1,0},{-1,0}};
    bool dfs(int x, int y, int index, vector<vector<char>>& board, string &word){
        int n = board.size();
        int m = board[0].size();
        if(index == word.size()) return true;
        if(x<0 || x>=n || y<0 || y>=m || board[x][y] != word[index]) return false;

        // if(w == word) return true;
        bool ret = false;
        char ch = board[x][y];
        board[x][y] = '#';
        string s = word.substr(1);
        for(auto d : diff){
            int newX = x + d[0];
            int newY = y + d[1];
            // if(x<0 || x>=n || y<0 || y>=m) return false;
            ret = ret || dfs(newX, newY, index, board, s);
            if(ret) return true;
        }
        board[x][y] = ch;
        return ret;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size();
        int m = board[0].size();
        string w = word;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(dfs(i,j,0,board,w)){
                    return true;
                }
            }
        }
        return false;
    }
};
```

## Attempt 7 · 2023-03-27 01:31 IST · Time Limit Exceeded · C++

[submission 922637263](https://leetcode.com/submissions/detail/922637263/) · tests 47/85

Failing input:

```text
[["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"]]
"AAAAAAAAAAAABAA"
```

Expected:

```text
false
```

```cpp
class Solution {
public:
    vector<vector<int>> diff = {{0,1},{0,-1},{1,0},{-1,0}};
    bool dfs(int x, int y, vector<vector<char>>& board, string &word){
        int n = board.size();
        int m = board[0].size();
        if(!word.size()) return true;
        if(x<0 || x>=n || y<0 || y>=m || board[x][y] != word[0]) return false;

        // if(w == word) return true;
        bool ret = false;
        char ch = board[x][y];
        board[x][y] = '#';
        string s = word.substr(1);
        for(auto d : diff){
            int newX = x + d[0];
            int newY = y + d[1];
            // if(x<0 || x>=n || y<0 || y>=m) return false;
            ret = ret || dfs(newX, newY, board, s);
            if(ret) return true;
        }
        board[x][y] = ch;
        return ret;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size();
        int m = board[0].size();
        string w = word;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(dfs(i,j,board,w)){
                    return true;
                }
            }
        }
        return false;
    }
};
```

## Attempt 8 · 2023-11-24 22:54 IST · Accepted · Python3

[submission 1105588401](https://leetcode.com/submissions/detail/1105588401/) · tests 86/86 · runtime 6964 ms (beats 5.0%)

```python
class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        path = set()
        N = len(board)
        M = len(board[0])
        def backtrack(r,c,idx):
            # as I go on adding idx will increase
            #1. check solution
            if len(word) == idx:
                return True

            #2. check valid
            if not(0<=r<N and 0<=c<M and board[r][c] == word[idx] and (r,c) not in path):
                return False

            #3. add path
            path.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if backtrack(nr,nc, idx+1):
                    return True

            #5. backtrack
            path.remove((r,c))

            return False

        for i in range(N):
            for j in range(M):
                if word[0] == board[i][j] and backtrack(i,j,0):
                    return True
        return False
```

## Attempt 9 · 2023-11-24 23:04 IST · Accepted · Python3

[submission 1105593548](https://leetcode.com/submissions/detail/1105593548/) · tests 86/86 · runtime 5822 ms (beats 7.9%)

```python
class Solution:
    def exist1(self, board: List[List[str]], word: str) -> bool:
        path = set()
        N = len(board)
        M = len(board[0])
        def backtrack(r,c,idx):
            # as I go on adding idx will increase
            #1. check solution
            if len(word) == idx:
                return True

            #2. check valid
            if not(0<=r<N and 0<=c<M and board[r][c] == word[idx] and (r,c) not in path):
                return False

            #3. add path
            path.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if backtrack(nr,nc, idx+1):
                    return True

            #5. backtrack
            path.remove((r,c))

            return False

        for i in range(N):
            for j in range(M):
                if word[0] == board[i][j] and backtrack(i,j,0):
                    return True
        return False


    def exist(self, board: List[List[str]], word: str) -> bool:
        N = len(board)
        M = len(board[0])
        def backtrack(r,c,idx):
            # as I go on adding idx will increase
            #1. check solution
            if len(word) == idx:
                return True

            #2. check valid
            if not(0<=r<N and 0<=c<M and board[r][c] == word[idx]):
                return False

            #3. add path
            board[r][c] ='#'
            # path.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if backtrack(nr,nc, idx+1):
                    return True

            #5. backtrack
            board[r][c] = word[idx]
            # path.remove((r,c))

            return False

        for i in range(N):
            for j in range(M):
                if word[0] == board[i][j] and backtrack(i,j,0):
                    # print(board)
                    return True 

        # print(board)
        return False
```

## Attempt 10 · 2024-01-16 09:54 IST · Wrong Answer · Python3

[submission 1147477040](https://leetcode.com/submissions/detail/1147477040/) · tests 86/87

Failing input:

```text
[["a"]]
"a"
```

Expected:

```text
true
```

Your output:

```text
false
```

```python
class Solution:
    def exist1(self, board: List[List[str]], word: str) -> bool:
        path = set()
        N = len(board)
        M = len(board[0])
        def backtrack(r,c,idx):
            # as I go on adding idx will increase
            #1. check solution
            if len(word) == idx:
                return True

            #2. check valid
            if not(0<=r<N and 0<=c<M and board[r][c] == word[idx] and (r,c) not in path):
                return False

            #3. add path
            path.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if backtrack(nr,nc, idx+1):
                    return True

            #5. backtrack by removing cell from the visited set
            path.remove((r,c))

            return False

        for i in range(N):
            for j in range(M):
                if word[0] == board[i][j] and backtrack(i,j,0):
                    return True
        return False


    def exist(self, board: List[List[str]], word: str) -> bool:
        N = len(board)
        M = len(board[0])
        def backtrack(r,c,idx):
            # as I go on adding idx will increase
            #1. check solution
            if len(word) == idx:
                return True

            #2. check valid
            if not(0<=r<N and 0<=c<M and board[r][c] == word[idx]):
                return False

            #3. add path
            board[r][c] ='#'
            # path.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if backtrack(nr,nc, idx+1):
                    return True

            #5. backtrack
            board[r][c] = word[idx]
            # path.remove((r,c))

            return False

        for i in range(N):
            for j in range(M):
                if word[0] == board[i][j] and backtrack(i,j,0):
                    # print(board)
                    return True 

        # print(board)
        return False  
    
    def exist(self, board: List[List[str]], word: str) -> bool:
        M = len(board)
        N = len(board[0])
        # visited = set()
        def backtrack(r,c,idx):
            # if (r,c) in visited:
            #     return 

            if idx == len(word):
                return True

            if word[idx] != board[r][c]:
                return
        
            # visited.add((r,c))
            board[r][c] ='#'

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<M and 0<=nc<N:
                    if backtrack(nr,nc,idx+1):
                        return True
            
            board[r][c] = word[idx]
            
            return False
            
        words = []
        for r in range(M):
            for c in range(N):
                if board[r][c] == word[0] and backtrack(r,c,0):
                    return True

        return words
```

## Attempt 11 · 2024-01-16 10:03 IST · Accepted · Python3

[submission 1147483129](https://leetcode.com/submissions/detail/1147483129/) · tests 87/87 · runtime 4113 ms (beats 41.8%)

```python
class Solution:
    def exist1(self, board: List[List[str]], word: str) -> bool:
        path = set()
        N = len(board)
        M = len(board[0])
        def backtrack(r,c,idx):
            # as I go on adding idx will increase
            #1. check solution
            if len(word) == idx:
                return True

            #2. check valid
            if not(0<=r<N and 0<=c<M and board[r][c] == word[idx] and (r,c) not in path):
                return False

            #3. add path
            path.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if backtrack(nr,nc, idx+1):
                    return True

            #5. backtrack by removing cell from the visited set
            path.remove((r,c))

            return False

        for i in range(N):
            for j in range(M):
                if word[0] == board[i][j] and backtrack(i,j,0):
                    return True
        return False


    def exist(self, board: List[List[str]], word: str) -> bool:
        N = len(board)
        M = len(board[0])
        def backtrack(r,c,idx):
            # as I go on adding idx will increase
            #1. check solution
            if len(word) == idx:
                return True

            #2. check valid
            if not(0<=r<N and 0<=c<M and board[r][c] == word[idx]):
                return False

            #3. add path
            board[r][c] ='#'
            # path.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if backtrack(nr,nc, idx+1):
                    return True

            #5. backtrack
            board[r][c] = word[idx]
            # path.remove((r,c))

            return False

        for i in range(N):
            for j in range(M):
                if word[0] == board[i][j] and backtrack(i,j,0):
                    # print(board)
                    return True 

        # print(board)
        return False  
    
    def exist(self, board: List[List[str]], word: str) -> bool:
        M = len(board)
        N = len(board[0])
        # visited = set()
        def backtrack(r,c,idx):
            # if (r,c) in visited:
            #     return 

            if idx == len(word):
                return True

            if not (0<=r<M and 0<=c<N and word[idx] == board[r][c]):
                return 
        
            # visited.add((r,c))
            board[r][c] ='#'

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if backtrack(nr,nc,idx+1):
                    return True
            
            board[r][c] = word[idx]
            
            return False
            
        words = []
        for r in range(M):
            for c in range(N):
                if board[r][c] == word[0] and backtrack(r,c,0):
                    return True

        return words
```

## Attempt 12 · 2024-01-24 00:31 IST · Wrong Answer · Python3

[submission 1154895301](https://leetcode.com/submissions/detail/1154895301/) · tests 86/87

Failing input:

```text
[["a"]]
"a"
```

Expected:

```text
true
```

Your output:

```text
false
```

```python
class Solution:
    def exist1(self, board: List[List[str]], word: str) -> bool:
        path = set()
        N = len(board)
        M = len(board[0])
        def backtrack(r,c,idx):
            # as I go on adding idx will increase
            #1. check solution
            if len(word) == idx:
                return True

            #2. check valid
            if not(0<=r<N and 0<=c<M and board[r][c] == word[idx] and (r,c) not in path):
                return False

            #3. add path
            path.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if backtrack(nr,nc, idx+1):
                    return True

            #5. backtrack by removing cell from the visited set
            path.remove((r,c))

            return False

        for i in range(N):
            for j in range(M):
                if word[0] == board[i][j] and backtrack(i,j,0):
                    return True
        return False


    def exist(self, board: List[List[str]], word: str) -> bool:
        N = len(board)
        M = len(board[0])
        def backtrack(r,c,idx):
            # as I go on adding idx will increase
            #1. check solution
            if len(word) == idx:
                return True

            #2. check valid
            if not(0<=r<N and 0<=c<M and board[r][c] == word[idx]):
                return False

            #3. add path
            board[r][c] ='#'
            # path.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if backtrack(nr,nc, idx+1):
                    return True

            #5. backtrack
            board[r][c] = word[idx]
            # path.remove((r,c))

            return False

        for i in range(N):
            for j in range(M):
                if word[0] == board[i][j] and backtrack(i,j,0):
                    # print(board)
                    return True 

        # print(board)
        return False  
    
    def exist(self, board: List[List[str]], word: str) -> bool:
        M = len(board)
        N = len(board[0])
        # visited = set()
        def backtrack(r,c,idx):
            # if (r,c) in visited:
            #     return 

            if idx == len(word):
                return True

            # it is necessary to use valid cell condition here 
            # other wise it won't work for single cell and single letter
            # it will match but it won't go inside 
            if not (0<=r<M and 0<=c<N and word[idx] == board[r][c]):
                return 
        
            # visited.add((r,c))
            board[r][c] ='#'

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if backtrack(nr,nc,idx+1):
                    return True
            
            board[r][c] = word[idx]
            
            return False
            
        words = []
        for r in range(M):
            for c in range(N):
                if board[r][c] == word[0] and backtrack(r,c,0):
                    return True

        return words

    def exist(self, board: List[List[str]], word: str) -> bool:
        def search(r,c, idx):
            if idx == len(word):
                return True

            if word[idx] != board[r][c]:
                return False

            temp = board[r][c]
            board[r][c] ='#'
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]:
                if 0<=nr<len(board) and 0<=nc<len(board[0]):
                    if search(nr,nc,idx+1):
                        return True
            board[r][c] =temp

            return False

        for r in range(len(board)):
            for c in range(len(board[0])):
                if board[r][c] == word[0]:
                    if search(r,c,0):
                        return True
        return False
```

## Attempt 13 · 2024-01-24 00:32 IST · Accepted · Python3

[submission 1154896180](https://leetcode.com/submissions/detail/1154896180/) · tests 87/87 · runtime 3950 ms (beats 47.1%)

```python
class Solution:
    def exist1(self, board: List[List[str]], word: str) -> bool:
        path = set()
        N = len(board)
        M = len(board[0])
        def backtrack(r,c,idx):
            # as I go on adding idx will increase
            #1. check solution
            if len(word) == idx:
                return True

            #2. check valid
            if not(0<=r<N and 0<=c<M and board[r][c] == word[idx] and (r,c) not in path):
                return False

            #3. add path
            path.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if backtrack(nr,nc, idx+1):
                    return True

            #5. backtrack by removing cell from the visited set
            path.remove((r,c))

            return False

        for i in range(N):
            for j in range(M):
                if word[0] == board[i][j] and backtrack(i,j,0):
                    return True
        return False


    def exist(self, board: List[List[str]], word: str) -> bool:
        N = len(board)
        M = len(board[0])
        def backtrack(r,c,idx):
            # as I go on adding idx will increase
            #1. check solution
            if len(word) == idx:
                return True

            #2. check valid
            if not(0<=r<N and 0<=c<M and board[r][c] == word[idx]):
                return False

            #3. add path
            board[r][c] ='#'
            # path.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if backtrack(nr,nc, idx+1):
                    return True

            #5. backtrack
            board[r][c] = word[idx]
            # path.remove((r,c))

            return False

        for i in range(N):
            for j in range(M):
                if word[0] == board[i][j] and backtrack(i,j,0):
                    # print(board)
                    return True 

        # print(board)
        return False  
    
    def exist(self, board: List[List[str]], word: str) -> bool:
        M = len(board)
        N = len(board[0])
        # visited = set()
        def backtrack(r,c,idx):
            # if (r,c) in visited:
            #     return 

            if idx == len(word):
                return True

            # it is necessary to use valid cell condition here 
            # other wise it won't work for single cell and single letter
            # it will match but it won't go inside 
            if not (0<=r<M and 0<=c<N and word[idx] == board[r][c]):
                return 
        
            # visited.add((r,c))
            board[r][c] ='#'

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if backtrack(nr,nc,idx+1):
                    return True
            
            board[r][c] = word[idx]
            
            return False
            
        words = []
        for r in range(M):
            for c in range(N):
                if board[r][c] == word[0] and backtrack(r,c,0):
                    return True

        return words

    def exist1(self, board: List[List[str]], word: str) -> bool:
        def search(r,c, idx):
            if idx == len(word):
                return True

            if word[idx] != board[r][c]:
                return False

            temp = board[r][c]
            board[r][c] ='#'
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]:
                if 0<=nr<len(board) and 0<=nc<len(board[0]):
                    if search(nr,nc,idx+1):
                        return True
            board[r][c] =temp

            return False

        for r in range(len(board)):
            for c in range(len(board[0])):
                if board[r][c] == word[0]:
                    if search(r,c,0):
                        return True
        return False
```

## Attempt 14 · 2024-01-24 00:33 IST · Accepted · Python3

[submission 1154897535](https://leetcode.com/submissions/detail/1154897535/) · tests 87/87 · runtime 3924 ms (beats 48.1%)

```python
class Solution:
    def exist1(self, board: List[List[str]], word: str) -> bool:
        path = set()
        N = len(board)
        M = len(board[0])
        def backtrack(r,c,idx):
            # as I go on adding idx will increase
            #1. check solution
            if len(word) == idx:
                return True

            #2. check valid
            if not(0<=r<N and 0<=c<M and board[r][c] == word[idx] and (r,c) not in path):
                return False

            #3. add path
            path.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if backtrack(nr,nc, idx+1):
                    return True

            #5. backtrack by removing cell from the visited set
            path.remove((r,c))

            return False

        for i in range(N):
            for j in range(M):
                if word[0] == board[i][j] and backtrack(i,j,0):
                    return True
        return False


    def exist(self, board: List[List[str]], word: str) -> bool:
        N = len(board)
        M = len(board[0])
        def backtrack(r,c,idx):
            # as I go on adding idx will increase
            #1. check solution
            if len(word) == idx:
                return True

            #2. check valid
            if not(0<=r<N and 0<=c<M and board[r][c] == word[idx]):
                return False

            #3. add path
            board[r][c] ='#'
            # path.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if backtrack(nr,nc, idx+1):
                    return True

            #5. backtrack
            board[r][c] = word[idx]
            # path.remove((r,c))

            return False

        for i in range(N):
            for j in range(M):
                if word[0] == board[i][j] and backtrack(i,j,0):
                    # print(board)
                    return True 

        # print(board)
        return False  
    
    def exist(self, board: List[List[str]], word: str) -> bool:
        M = len(board)
        N = len(board[0])
        # visited = set()
        def backtrack(r,c,idx):
            # if (r,c) in visited:
            #     return 

            if idx == len(word):
                return True

            # it is necessary to use valid cell condition here 
            # other wise it won't work for single cell and single letter
            # it will match but it won't go inside 
            if not (0<=r<M and 0<=c<N and word[idx] == board[r][c]):
                return 
        
            # visited.add((r,c))
            board[r][c] ='#'

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if backtrack(nr,nc,idx+1):
                    return True
            
            board[r][c] = word[idx]
            
            return False
            
        words = []
        for r in range(M):
            for c in range(N):
                if board[r][c] == word[0] and backtrack(r,c,0):
                    return True

        return words

    def exist1(self, board: List[List[str]], word: str) -> bool:
        def search(r,c, idx):
            if idx == len(word):
                return True

            if not(0<=r<len(board) and 0<=c<len(board[0]) and word[idx] == board[r][c]):
                return False

            temp = board[r][c]
            board[r][c] ='#'
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]:
                if search(nr,nc,idx+1):
                    return True
            board[r][c] =temp

            return False

        for r in range(len(board)):
            for c in range(len(board[0])):
                if board[r][c] == word[0]:
                    if search(r,c,0):
                        return True
        return False
```

## Attempt 15 · 2024-01-24 00:34 IST · Accepted · Python3

[submission 1154897690](https://leetcode.com/submissions/detail/1154897690/) · tests 87/87 · runtime 4296 ms (beats 33.5%)

```python
class Solution:
    def exist1(self, board: List[List[str]], word: str) -> bool:
        path = set()
        N = len(board)
        M = len(board[0])
        def backtrack(r,c,idx):
            # as I go on adding idx will increase
            #1. check solution
            if len(word) == idx:
                return True

            #2. check valid
            if not(0<=r<N and 0<=c<M and board[r][c] == word[idx] and (r,c) not in path):
                return False

            #3. add path
            path.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if backtrack(nr,nc, idx+1):
                    return True

            #5. backtrack by removing cell from the visited set
            path.remove((r,c))

            return False

        for i in range(N):
            for j in range(M):
                if word[0] == board[i][j] and backtrack(i,j,0):
                    return True
        return False


    def exist(self, board: List[List[str]], word: str) -> bool:
        N = len(board)
        M = len(board[0])
        def backtrack(r,c,idx):
            # as I go on adding idx will increase
            #1. check solution
            if len(word) == idx:
                return True

            #2. check valid
            if not(0<=r<N and 0<=c<M and board[r][c] == word[idx]):
                return False

            #3. add path
            board[r][c] ='#'
            # path.add((r,c))

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if backtrack(nr,nc, idx+1):
                    return True

            #5. backtrack
            board[r][c] = word[idx]
            # path.remove((r,c))

            return False

        for i in range(N):
            for j in range(M):
                if word[0] == board[i][j] and backtrack(i,j,0):
                    # print(board)
                    return True 

        # print(board)
        return False  
    
    def exist(self, board: List[List[str]], word: str) -> bool:
        M = len(board)
        N = len(board[0])
        # visited = set()
        def backtrack(r,c,idx):
            # if (r,c) in visited:
            #     return 

            if idx == len(word):
                return True

            # it is necessary to use valid cell condition here 
            # other wise it won't work for single cell and single letter
            # it will match but it won't go inside 
            if not (0<=r<M and 0<=c<N and word[idx] == board[r][c]):
                return 
        
            # visited.add((r,c))
            board[r][c] ='#'

            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if backtrack(nr,nc,idx+1):
                    return True
            
            board[r][c] = word[idx]
            
            return False
            
        words = []
        for r in range(M):
            for c in range(N):
                if board[r][c] == word[0] and backtrack(r,c,0):
                    return True

        return words

    def exist(self, board: List[List[str]], word: str) -> bool:
        def search(r,c, idx):
            if idx == len(word):
                return True

            if not(0<=r<len(board) and 0<=c<len(board[0]) and word[idx] == board[r][c]):
                return False

            temp = board[r][c]
            board[r][c] ='#'
            for nr,nc in [(r+1,c),(r,c+1),(r-1,c),(r,c-1)]:
                if search(nr,nc,idx+1):
                    return True
            board[r][c] =temp

            return False

        for r in range(len(board)):
            for c in range(len(board[0])):
                if board[r][c] == word[0]:
                    if search(r,c,0):
                        return True
        return False
```
