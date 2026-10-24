# 348. Design Tic-Tac-Toe

[Problem](https://leetcode.com/problems/design-tic-tac-toe/) · Medium · Design → Row/column counters

LeetCode tags: array, hash-table, design, matrix, simulation

Attempts since Mar 2023: 7 · accepted: 4 · failed before first AC: 1

## Attempt 1 · 2023-11-24 20:05 IST · Runtime Error · Python

[submission 1105503344](https://leetcode.com/submissions/detail/1105503344/) · tests 0/33

Failing input:

```text
["TicTacToe","move","move","move","move","move","move","move"]
[[3],[0,0,1],[0,2,2],[2,2,1],[1,1,2],[2,0,1],[1,0,2],[2,1,1]]
```

Expected:

```text
[null,0,0,0,0,0,0,1]
```

Runtime error:

```text
NameError: global name 'n' is not defined
    if row+col == n-1:
Line 30 in move (Solution.py)
    __Deserializer__()._deserialize(json.dumps(p[2], escape_forward_slashes=False), "integer"))
Line 54 in __helper_select_method__ (Solution.py)
    ret.append(__DriverSolution__().__helper_select_method__(method, params[index], obj))
Line 91 in _driver (Solution.py)
    _driver()
Line 99 in <module> (S ... [11 more chars]
```

```python
class TicTacToe(object):

    def __init__(self, n):
        """
        :type n: int
        """
        self.cols= [0]*n
        self.rows = [0]*n
        self.antidiag = 0
        self.diag = 0
        self.n = n
        

    def move(self, row, col, player):
        """
        :type row: int
        :type col: int
        :type player: int
        :rtype: int
        """

        # keep track for  player one
        currentPlayer = 1 if player == 1 else -1

        self.rows[row] += currentPlayer
        self.cols[col]+= currentPlayer

        if row-col==0:
            self.diag+= currentPlayer
        if row+col == n-1:
            self.antidiag += currentPlayer

        if (abs(self.rows[row]) == n or abs(self.cols[col]) == n or abs(self.diag)==n or abs(self.antidiag) ==n):
            return player

        return 0

        


# Your TicTacToe object will be instantiated and called as such:
# obj = TicTacToe(n)
# param_1 = obj.move(row,col,player)
```

## Attempt 2 · 2023-11-24 20:05 IST · Accepted · Python

[submission 1105503568](https://leetcode.com/submissions/detail/1105503568/) · tests 33/33 · runtime 54 ms (beats 96.6%)

```python
class TicTacToe(object):

    def __init__(self, n):
        """
        :type n: int
        """
        self.cols= [0]*n
        self.rows = [0]*n
        self.antidiag = 0
        self.diag = 0
        self.n = n
        

    def move(self, row, col, player):
        """
        :type row: int
        :type col: int
        :type player: int
        :rtype: int
        """

        # keep track for  player one
        currentPlayer = 1 if player == 1 else -1

        self.rows[row] += currentPlayer
        self.cols[col]+= currentPlayer

        if row-col==0:
            self.diag+= currentPlayer
        if row+col == self.n-1:
            self.antidiag += currentPlayer

        if (abs(self.rows[row]) == self.n or abs(self.cols[col]) == self.n or abs(self.diag)==self.n or abs(self.antidiag) ==self.n):
            return player

        return 0

        


# Your TicTacToe object will be instantiated and called as such:
# obj = TicTacToe(n)
# param_1 = obj.move(row,col,player)
```

## Attempt 3 · 2023-12-05 06:10 IST · Accepted · Python

[submission 1112525137](https://leetcode.com/submissions/detail/1112525137/) · tests 33/33 · runtime 61 ms (beats 82.8%)

```python
class TicTacToe(object):
    '''
    approach 1 - create a board n*n and for each move check all row, col, diagonal(row=col), antidiagonal(col= n-row-1) or row+col = n-1
    space O(n^2)
    time O(n)

    approach2 - keep list of rows, cols, and variable diag and antidiag
    to keep track of how many moves players has made in total 
    space - O(n)
    time O(1)

    '''
    def __init__(self, n):
        """
        :type n: int
        """
        self.cols= [0]*n
        self.rows = [0]*n
        self.antidiag = 0
        self.diag = 0
        self.n = n
        

    def move(self, row, col, player):
        """
        :type row: int
        :type col: int
        :type player: int
        :rtype: int
        """

        # keep track for  player one
        currentPlayer = 1 if player == 1 else -1

        # for each player update the rows, col
        self.rows[row] += currentPlayer
        self.cols[col]+= currentPlayer

        # if move is on diag and antidiag
        if row-col==0:
            self.diag+= currentPlayer
        if row+col == self.n-1:
            self.antidiag += currentPlayer

        # either it will be -N or N when one of the player wins
        # the player who played the current move will win
        if (abs(self.rows[row]) == self.n or abs(self.cols[col]) == self.n or abs(self.diag)==self.n or abs(self.antidiag) ==self.n):
            return player

        # other wise no one won on this move
        return 0

        


# Your TicTacToe object will be instantiated and called as such:
# obj = TicTacToe(n)
# param_1 = obj.move(row,col,player)
```

## Attempt 4 · 2023-12-25 02:38 IST · Accepted · Python3

[submission 1127697547](https://leetcode.com/submissions/detail/1127697547/) · tests 33/33 · runtime 82 ms (beats 59.5%)

```python
class TicTacToe:

    def __init__(self, n: int):
        '''
        approach 1 - on each move, verify that move's row, col, diagonal, antidiagonal to check if the player has won else return -1
        row - for each column in that row, if all matches
        col- for each row in that col
        diagonal - has row == col - so check for row, row or col, col
        anti - r+c = n so chek row , M-r

        space - maintain complete board and keep player moves updated in each 

        '''
        self.board = [[0]*n for _ in range(n)]
        self.size = n

    def move(self, row: int, col: int, player: int) -> int:
        
        # if any match, return player number else return 0
        
        # 1. update the board
        self.board[row][col] = player

        # 2. check row, col
        if all(self.board[row][i] == player for i in range(self.size)) or all(self.board[i][col] == player for i in range(self.size)):
            return player

        # 3. check if its a diagonal(row == col) and if player got complete diag
        if row == col and all([self.board[i][i] == player for i in range(self.size)]):
    
            return player

        # check if antidiagonal(row-col == n - 1) and if player got complete anti diag
        if row + col == self.size -1 and all([self.board[i][self.size-1-i] ==player for i in range(self.size)]):
            return player
        
        return 0
        


# Your TicTacToe object will be instantiated and called as such:
# obj = TicTacToe(n)
# param_1 = obj.move(row,col,player)
```

## Attempt 5 · 2023-12-25 03:00 IST · Wrong Answer · Python3

[submission 1127705937](https://leetcode.com/submissions/detail/1127705937/) · tests 31/33

Failing input:

```text
["TicTacToe","move","move","move"]
[[2],[0,1,2],[1,0,1],[1,1,2]]
```

Expected:

```text
[null,0,0,2]
```

Your output:

```text
[null,0,0,0]
```

```python
class TicTacToe1:

    def __init__(self, n: int):
        '''
        approach 1 - on each move, verify that move's row, col, diagonal, antidiagonal to check if the player has won else return -1
        row - for each column in that row, if all matches
        col- for each row in that col
        diagonal - has row == col - so check for row, row or col, col
        anti - r+c = n so chek row , M-r

        space - maintain complete board and keep player moves updated in each 

        '''
        self.board = [[0]*n for _ in range(n)]
        self.size = n

    def move(self, row: int, col: int, player: int) -> int:
        
        # if any match, return player number else return 0

        # 1. update the board
        self.board[row][col] = player

        # 2. check row, col
        if all(self.board[row][i] == player for i in range(self.size)) or all(self.board[i][col] == player for i in range(self.size)):
            return player

        # 3. check if its a diagonal(row == col) and if player got complete diag
        if row == col and all([self.board[i][i] == player for i in range(self.size)]):
    
            return player

        # check if antidiagonal(row-col == n - 1) and if player got complete anti diag
        if row + col == self.size -1 and all([self.board[i][self.size-1-i] ==player for i in range(self.size)]):
            return player
        
        return 0
        

class TicTacToe:

    def __init__(self, n: int):
        '''
        approach 2: instead of creating a board and verfying row, col ..
        keep a count of each player moves in that row(n), col(n) diag(1) or antidiag(1)

        '''
        self.rows = [0]* n
        self.cols = [0]* n
        self.size = n 
        self.diagonal = 0
        self.antidiag = 0

    def move(self, row: int, col: int, player: int) -> int:
        playerValue = 1 if player == 1 else -1

        self.rows[row] += playerValue
        self.cols[col] += playerValue

        if row == col:
            self.diagonal += playerValue

        if row + col == self.size  - 1 :
            self.antidiag += playerValue

        if (abs(self.rows[row]) == self.size or abs(self.cols[col] == self.size) or abs(self.diagonal) == self.size or abs(self.antidiag) == self.size):
            print('returning', player)
            return player
        return 0
        


# Your TicTacToe object will be instantiated and called as such:
# obj = TicTacToe(n)
# param_1 = obj.move(row,col,player)
```

## Attempt 6 · 2023-12-25 03:03 IST · Runtime Error · Python3

[submission 1127706807](https://leetcode.com/submissions/detail/1127706807/) · tests 0/33

Failing input:

```text
["TicTacToe","move","move","move","move","move","move","move"]
[[3],[0,0,1],[0,2,2],[2,2,1],[1,1,2],[2,0,1],[1,0,2],[2,1,1]]
```

Expected:

```text
[null,0,0,0,0,0,0,1]
```

Runtime error:

```text
SyntaxError: unmatched ')'
                                                                                                                                                   ^
    if (abs(self.rows[row]) == self.size or abs(self.cols[col]) == self.size) or abs(self.diagonal) == self.size or abs(self.antidiag) == self.size):
Line 66  (Solution.py)
```

```python
class TicTacToe1:

    def __init__(self, n: int):
        '''
        approach 1 - on each move, verify that move's row, col, diagonal, antidiagonal to check if the player has won else return -1
        row - for each column in that row, if all matches
        col- for each row in that col
        diagonal - has row == col - so check for row, row or col, col
        anti - r+c = n so chek row , M-r

        space - maintain complete board and keep player moves updated in each 

        '''
        self.board = [[0]*n for _ in range(n)]
        self.size = n

    def move(self, row: int, col: int, player: int) -> int:
        
        # if any match, return player number else return 0

        # 1. update the board
        self.board[row][col] = player

        # 2. check row, col
        if all(self.board[row][i] == player for i in range(self.size)) or all(self.board[i][col] == player for i in range(self.size)):
            return player

        # 3. check if its a diagonal(row == col) and if player got complete diag
        if row == col and all([self.board[i][i] == player for i in range(self.size)]):
    
            return player

        # check if antidiagonal(row-col == n - 1) and if player got complete anti diag
        if row + col == self.size -1 and all([self.board[i][self.size-1-i] ==player for i in range(self.size)]):
            return player
        
        return 0
        

class TicTacToe:

    def __init__(self, n: int):
        '''
        approach 2: instead of creating a board and verfying row, col ..
        keep a count of each player moves in that row(n), col(n) diag(1) or antidiag(1)

        '''
        self.rows = [0]* n
        self.cols = [0]* n
        self.size = n 
        self.diagonal = 0
        self.antidiag = 0

    def move(self, row: int, col: int, player: int) -> int:
        playerValue = 1 if player == 1 else -1

        self.rows[row] += playerValue
        self.cols[col] += playerValue

        if row == col:
            self.diagonal += playerValue

        if row + col == self.size  - 1 :
            self.antidiag += playerValue

        if (abs(self.rows[row]) == self.size or abs(self.cols[col]) == self.size) or abs(self.diagonal) == self.size or abs(self.antidiag) == self.size):
            # print('returning', player)
            return player
        return 0
        


# Your TicTacToe object will be instantiated and called as such:
# obj = TicTacToe(n)
# param_1 = obj.move(row,col,player)
```

## Attempt 7 · 2023-12-25 03:03 IST · Accepted · Python3

[submission 1127706827](https://leetcode.com/submissions/detail/1127706827/) · tests 33/33 · runtime 76 ms (beats 84.3%)

```python
class TicTacToe1:

    def __init__(self, n: int):
        '''
        approach 1 - on each move, verify that move's row, col, diagonal, antidiagonal to check if the player has won else return -1
        row - for each column in that row, if all matches
        col- for each row in that col
        diagonal - has row == col - so check for row, row or col, col
        anti - r+c = n so chek row , M-r

        space - maintain complete board and keep player moves updated in each 

        '''
        self.board = [[0]*n for _ in range(n)]
        self.size = n

    def move(self, row: int, col: int, player: int) -> int:
        
        # if any match, return player number else return 0

        # 1. update the board
        self.board[row][col] = player

        # 2. check row, col
        if all(self.board[row][i] == player for i in range(self.size)) or all(self.board[i][col] == player for i in range(self.size)):
            return player

        # 3. check if its a diagonal(row == col) and if player got complete diag
        if row == col and all([self.board[i][i] == player for i in range(self.size)]):
    
            return player

        # check if antidiagonal(row-col == n - 1) and if player got complete anti diag
        if row + col == self.size -1 and all([self.board[i][self.size-1-i] ==player for i in range(self.size)]):
            return player
        
        return 0
        

class TicTacToe:

    def __init__(self, n: int):
        '''
        approach 2: instead of creating a board and verfying row, col ..
        keep a count of each player moves in that row(n), col(n) diag(1) or antidiag(1)

        '''
        self.rows = [0]* n
        self.cols = [0]* n
        self.size = n 
        self.diagonal = 0
        self.antidiag = 0

    def move(self, row: int, col: int, player: int) -> int:
        playerValue = 1 if player == 1 else -1

        self.rows[row] += playerValue
        self.cols[col] += playerValue

        if row == col:
            self.diagonal += playerValue

        if row + col == self.size  - 1 :
            self.antidiag += playerValue

        if (abs(self.rows[row]) == self.size or abs(self.cols[col]) == self.size or abs(self.diagonal) == self.size or abs(self.antidiag) == self.size):
            # print('returning', player)
            return player
        return 0
        


# Your TicTacToe object will be instantiated and called as such:
# obj = TicTacToe(n)
# param_1 = obj.move(row,col,player)
```
