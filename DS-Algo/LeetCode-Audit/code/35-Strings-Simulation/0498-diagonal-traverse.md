# 498. Diagonal Traverse

[Problem](https://leetcode.com/problems/diagonal-traverse/) · Medium · Strings & Simulation → Matrix simulation

LeetCode tags: array, matrix, simulation

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-11-26 23:07 IST · Accepted · Python3

[submission 1106907486](https://leetcode.com/submissions/detail/1106907486/) · tests 32/32 · runtime 153 ms (beats 8.4%)

```python
class Solution:
    def findDiagonalOrder(self, mat: List[List[int]]) -> List[int]:
        if not mat or not mat[0]:
            return []

        rows, cols = len(mat), len(mat[0])
        result, row, col = [], 0, 0

        for _ in range(rows * cols):
            result.append(mat[row][col])
            if (row + col) % 2 == 0:  # moving upwards
                if col == cols - 1:
                    row += 1
                elif row == 0:
                    col += 1
                else:
                    row -= 1
                    col += 1
            else:  # moving downwards
                if row == rows - 1:
                    col += 1
                elif col == 0:
                    row += 1
                else:
                    row += 1
                    col -= 1

        return result
```

## Attempt 2 · 2023-11-26 23:33 IST · Accepted · Python3

[submission 1106922663](https://leetcode.com/submissions/detail/1106922663/) · tests 32/32 · runtime 181 ms (beats 8.4%)

```python
class Solution:
    def findDiagonalOrder1(self, mat: List[List[int]]) -> List[int]:
        if not mat or not mat[0]:
            return []

        rows, cols = len(mat), len(mat[0])
        result, row, col = [], 0, 0

        for _ in range(rows * cols):
            result.append(mat[row][col])
            if (row + col) % 2 == 0:  # moving upwards
                if col == cols - 1:
                    row += 1
                elif row == 0:
                    col += 1
                else:
                    row -= 1
                    col += 1
            else:  # moving downwards
                if row == rows - 1:
                    col += 1
                elif col == 0:
                    row += 1
                else:
                    row += 1
                    col -= 1

        return result

    def findDiagonalOrder(self, mat: List[List[int]]) -> List[int]:
        if not mat and not mat[0]:
            return []

        diagonals= defaultdict(list)
        for i in range(len(mat)):
            for j in range(len(mat[0])):
                diagonals[i+j].append(mat[i][j])

        print(diagonals)
        result = []

        for k in range(len(mat)+len(mat[0])):
            if k%2==0:
                result.extend(diagonals[k][::-1])
            else:
                result.extend(diagonals[k])

        return result
```

## Attempt 3 · 2023-12-05 02:25 IST · Accepted · Python3

[submission 1112438365](https://leetcode.com/submissions/detail/1112438365/) · tests 32/32 · runtime 166 ms (beats 8.4%)

```python
class Solution:

    def findDiagonalOrder1(self, mat: List[List[int]]) -> List[int]:
        '''
        approach 1 : for each diagonal, find the head r,c which will be on row 0 and last column
        run until hit the boundary of left and bottom and go on adding elements to intermediate diagonal array
        clear diagonal after adding to result .clear() to avoid new list creation
        it uses intermediate space for saving diagonal required for reversing

        approach 2: with no extra space. 
        iterate through all elements but the order will be decided by the rules for traversal

        - initially direction is going up, then for odd and even based on 
        '''

        # 1. validate input
        if not mat or not mat[0]:
            return []

        # total rows and cols and new row and col at each step
        rows, cols = len(mat), len(mat[0])
        result, row, col = [], 0, 0

        # run loop for total elements, but decide indexes based on direction
        for _ in range(rows * cols):
            result.append(mat[row][col])

            # even cell is going in the upward direction
            # but direction will be changed on top row and last col
            if (row + col) % 2 == 0:  # moving upwards
                if col == cols - 1:
                    row += 1
                elif row == 0:
                    col += 1
                else:
                    row -= 1
                    col += 1
            
            # downward going cell will change directions at first column and last row
            else:  # moving downwards
                if row == rows - 1:
                    col += 1
                elif col == 0:
                    row += 1
                else:
                    row += 1
                    col -= 1

        return result

    def findDiagonalOrder(self, mat: List[List[int]]) -> List[int]:
        if not mat and not mat[0]:
            return []

        diagonals= defaultdict(list)
        for i in range(len(mat)):
            for j in range(len(mat[0])):
                diagonals[i+j].append(mat[i][j])

        print(diagonals)
        result = []

        for k in range(len(mat)+len(mat[0])):
            if k%2==0:
                result.extend(diagonals[k][::-1])
            else:
                result.extend(diagonals[k])

        return result


    def findDiagonalOrder(self, mat: List[List[int]]) -> List[int]:
        '''
        diagonals have r-c value same
        antidiagonals have r+c values same

        for each diagonal find the head element and traverse from top/right to left/bottom

        time- O(NM)
        space - maximum will be diagonal entries which will be min(M, N)
        '''
        N = len(mat)
        M = len(mat[0])
        result, intermediate = [], []
        for d in range(M+N-1):
            
            intermediate.clear()
            
            # find head cell
            # all heads are either on first row(0) or on last column M-1
            r = 0 if d<M else d-M+1
            c = d if d<M else M-1

            while r<N and c>-1:
                intermediate.append(mat[r][c])
                r+=1
                c-=1
            
            if d&1:
                result.extend(intermediate)
            else:
                result.extend(intermediate[::-1])
                
        return result
```
