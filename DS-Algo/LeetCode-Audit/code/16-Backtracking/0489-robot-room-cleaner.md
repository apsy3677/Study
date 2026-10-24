# 489. Robot Room Cleaner

[Problem](https://leetcode.com/problems/robot-room-cleaner/) · Hard · Backtracking → Interactive DFS

LeetCode tags: backtracking, interactive

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-12-26 00:04 IST · Accepted · Python3

[submission 1128338242](https://leetcode.com/submissions/detail/1128338242/) · tests 29/29 · runtime 57 ms (beats 81.6%)

```python
class Solution1:       
    def cleanRoom(self, robot):
        """
        :type robot: Robot
        :rtype: None
        1. use dfs  to exhaustively explore all paths from the current cell
        to ensure no cell is left backtrack to previous cell
        2. since we don't have access to the robots position we will keep track of its position relative to the starting posisiton. this is don using x,y and direction
        3. for consistency and simplicity, you an use turnRight to explore all directions
        """
        def go_back():
            robot.turnRight()
            robot.turnRight()
            robot.move()
            robot.turnRight()
            robot.turnRight()
            
        def backtrack(cell = (0, 0), d = 0):
            print('cleaning cell', cell)

            # 1. mark visited and clean
            visited.add(cell)
            robot.clean()

            # 1. explore all directions
            # 2. going clockwise : 0: 'up', 1: 'right', 2: 'down', 3: 'left'
            for i in range(4):

                # 3. new direction                 
                new_d = (d + i) % 4
                new_cell = (cell[0] + directions[new_d][0], \
                            cell[1] + directions[new_d][1])


                # 3. if new cell can be  
                if not new_cell in visited and robot.move():
                    backtrack(new_cell, new_d)
                    go_back()
                
                # turn the robot following chosen direction : new_d -> clockwise
                print('turining right', cell)
                robot.turnRight()
    
        # going clockwise : 0: 'up', 1: 'right', 2: 'down', 3: 'left'
        directions = [(-1, 0), (0, 1), (1, 0), (0, -1)]
        visited = set()
        backtrack()


class Solution:       
    def cleanRoom(self, robot):
        """
        :type robot: Robot
        :rtype: None
        1. use dfs  to exhaustively explore all paths from the current cell
        to ensure no cell is left backtrack to previous cell
        2. since we don't have access to the robots position we will keep track of its position relative to the starting posisiton. this is don using x,y and direction
        3. for consistency and simplicity, you an use turnRight to explore all directions
        """

        def go_back():
            robot.turnRight()
            robot.turnRight()
            robot.move()
            robot.turnRight()
            robot.turnRight()


        # clockwise directions
        directions = [(-1, 0), (0,1), (1,0),(0,-1)]
        visited = set()
        def dfs(x, y, direction):

            # clean current cell and add to visited
            visited.add((x,y))
            robot.clean()

            # move in all directions
            for i in range(4):
                new_direction = (direction + i) % 4
                new_x, new_y = x + directions[new_direction][0], y + directions[new_direction][1]

                if (new_x,new_y) not in visited and robot.move():
                    dfs(new_x,new_y, new_direction)
                    go_back()

                robot.turnRight()

        
        dfs(0,0,0)
```
