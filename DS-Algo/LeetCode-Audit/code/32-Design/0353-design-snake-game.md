# 353. Design Snake Game

[Problem](https://leetcode.com/problems/design-snake-game/) · Medium · Design → Deque + set

LeetCode tags: array, hash-table, design, queue, simulation

Attempts since Mar 2023: 3 · accepted: 2 · failed before first AC: 1

## Attempt 1 · 2023-04-26 13:58 IST · Wrong Answer · C++

[submission 939955592](https://leetcode.com/submissions/detail/939955592/) · tests 82/446

Failing input:

```text
["SnakeGame","move","move","move","move","move","move","move","move","move","move","move","move","move","move","move"]
[[3,3,[[2,0],[0,0],[0,2],[0,1],[2,2],[0,1]]],["D"],["D"],["R"],["U"],["U"],["L"],["D"],["R"],["R"],["U"],["L"],["L"],["D"],["R"],["U"]]
```

Expected:

```text
[null,0,1,1,1,1,2,2,2,2,3,4,4,4,4,-1]
```

Your output:

```text
[null,0,1,1,1,1,2,2,2,2,3,4,4,4,4,4]
```

```cpp
class SnakeGame {
    pair<int,int> head;
    // map<pair<int,int>, int> snake;
    deque<pair<int,int>> snake;
    int rows, cols;
    vector<vector<int>> food;
    int score;
    int foodId;
public:
    SnakeGame(int width, int height, vector<vector<int>>& ff) {
        rows = height;
        cols = width;
        food = ff;
        head = {0,0};
        snake.push_back(head);
        score = 0;
        foodId = 0;
    }
    
    bool outOfBound(int x, int y){
        if(x<0 || x>=rows || y<0 ||y>=cols){
            return true;
        }
        return false;
    }

    bool isInvalid(int x, int y){
        for(auto [r,c] : snake){
            if(r==x && c == y){
                return true;
            }
        }
        return false;
    }

    int move(string direction) {
        int x = head.first, y = head.second;
        char dir = direction[0];
        switch(dir){
            case 'L': y--;break;
            case 'R': y++;break;
            case 'U': x--;break;
            case 'D': x++;break;
            default: break;
        }
        // if(outOfBound(x,y) || isInvalid(x, y)){
        if(outOfBound(x,y)){
            return -1;
        }
        head = {x,y};
        if(foodId < food.size() && x == food[foodId][0] && y== food[foodId][1]){
            
            snake.push_back(head);
            score ++;
            foodId++;
        }
        else{
            snake.pop_front();
        }
        
        return score;
    }
};

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame* obj = new SnakeGame(width, height, food);
 * int param_1 = obj->move(direction);
 */
```

## Attempt 2 · 2023-04-26 14:15 IST · Accepted · C++

[submission 939962357](https://leetcode.com/submissions/detail/939962357/) · tests 446/446 · runtime 131 ms (beats 23.7%)

```cpp
// // #include <algorithm.h>

// class SnakeGame {
//     pair<int,int> head;
//     // map<pair<int,int>, int> snake;
//     list<pair<int,int>> snake;
//     int rows, cols;
//     vector<vector<int>> food;
//     int score;
//     int foodId;
// public:
//     SnakeGame(int width, int height, vector<vector<int>>& ff) {
//         rows = height;
//         cols = width;
//         food = ff;
//         head = {0,0};
//         snake.push_back(head);
//         score = 0;
//         foodId = 0;
//     }
    
//     bool outOfBound(int x, int y){
//         if(x<0 || x>=rows || y<0 ||y>=cols){
//             return true;
//         }
//         return false;
//     }

//     bool isInvalid(int x, int y){
//         // for(auto [r,c] : snake){
//         //     if(r==x && c == y){
//         //         return true;
//         //     }
//         // }
//         // if(find(snake.begin(),snake.end(), {x,y})!=snake.end())
//         //     return true;
//         for(auto it = snake.begin(); it!=snake.end();it++){
//             if(it->first == x && it->second == y) 
//             return true;
//         }
//         return false;
//     }

//     int move(string direction) {
//         int x = head.first, y = head.second;
//         char dir = direction[0];
//         switch(dir){
//             case 'L': y--;break;
//             case 'R': y++;break;
//             case 'U': x--;break;
//             case 'D': x++;break;
//             default: break;
//         }
//         // if(outOfBound(x,y) || isInvalid(x, y)){
//         if(outOfBound(x,y)){
//             return -1;
//         }
//         head = {x,y};
//         if(foodId < food.size() && x == food[foodId][0] && y== food[foodId][1]){
            
//             snake.push_back({x,y});
//             score ++;
//             foodId++;
//         }
//         else{
//             snake.pop_front();
//         }
//         if(isInvalid(x, y)){
//             return -1;
//         }
//         return score;
//     }
// };

// /**
//  * Your SnakeGame object will be instantiated and called as such:
//  * SnakeGame* obj = new SnakeGame(width, height, food);
//  * int param_1 = obj->move(direction);
//  */
class SnakeGame {
    int WIDTH;
    int HEIGHT;
    // left, top: (x,y) = (0,0);
    // (0,0) (1,0) (2,0)
    // (0,1) (1,1) (2,1)
    // (0,2) (1,2) (2,2)
    struct location{
        int x;  // row
        int y;  // col
        bool operator==(const location& rhs){
            return (x==rhs.x) && (y==rhs.y);
        }
    };
    
    deque<location> food_location;
    deque<location> snake;
public:
    SnakeGame(int width, int height, vector<vector<int>>& food) {
        WIDTH = width;
        HEIGHT = height;
        for(int i=0;i<food.size();i++)
            food_location.push_back({.x = food[i][1],.y =food[i][0]});
        snake.push_back({.x=0,.y=0});
    }
    
    int move(string direction) {
        location new_head = snake.front();

        // detect if snake get out of bound 
        if(direction == "L"){
            new_head.x -= 1;
        }else if (direction == "R"){
            new_head.x += 1;
        }else if( direction == "U"){
            new_head.y -= 1;
        } else if(direction == "D"){
            new_head.y += 1;   
        }
        if( new_head.x < 0 || new_head.x >= WIDTH || new_head.y < 0 || new_head.y >= HEIGHT )
            return -1;
        
        // if snake get food else pop tail
        if(food_location.size()>0 && new_head==food_location.front()){
            food_location.pop_front();
        }else{
            snake.pop_back();
        }
        // if snake hit body (after move)
        // if check snake hit body before calculate get food & pop tail, need skip check tail location
        if(find(snake.begin(),snake.end(), new_head)!=snake.end())
            return -1;
        
        snake.push_front(new_head);

        return snake.size()-1;
    }
};
```

## Attempt 3 · 2023-04-26 16:12 IST · Accepted · C++

[submission 940007168](https://leetcode.com/submissions/detail/940007168/) · tests 446/446 · runtime 124 ms (beats 25.9%)

```cpp
// // #include <algorithm.h>

// class SnakeGame {
//     pair<int,int> head;
//     // map<pair<int,int>, int> snake;
//     list<pair<int,int>> snake;
//     int rows, cols;
//     vector<vector<int>> food;
//     int score;
//     int foodId;
// public:
//     SnakeGame(int width, int height, vector<vector<int>>& ff) {
//         rows = height;
//         cols = width;
//         food = ff;
//         head = {0,0};
//         snake.push_back(head);
//         score = 0;
//         foodId = 0;
//     }
    
//     bool outOfBound(int x, int y){
//         if(x<0 || x>=rows || y<0 ||y>=cols){
//             return true;
//         }
//         return false;
//     }

//     bool isInvalid(int x, int y){
//         // for(auto [r,c] : snake){
//         //     if(r==x && c == y){
//         //         return true;
//         //     }
//         // }
//         // if(find(snake.begin(),snake.end(), {x,y})!=snake.end())
//         //     return true;
//         for(auto it = snake.begin(); it!=snake.end();it++){
//             if(it->first == x && it->second == y) 
//             return true;
//         }
//         return false;
//     }

//     int move(string direction) {
//         int x = head.first, y = head.second;
//         char dir = direction[0];
//         switch(dir){
//             case 'L': y--;break;
//             case 'R': y++;break;
//             case 'U': x--;break;
//             case 'D': x++;break;
//             default: break;
//         }
//         // if(outOfBound(x,y) || isInvalid(x, y)){
//         if(outOfBound(x,y)){
//             return -1;
//         }
//         head = {x,y};
//         if(foodId < food.size() && x == food[foodId][0] && y== food[foodId][1]){
            
//             snake.push_back({x,y});
//             score ++;
//             foodId++;
//         }
//         else{
//             snake.pop_front();
//         }
//         if(isInvalid(x, y)){
//             return -1;
//         }
//         return score;
//     }
// };

// /**
//  * Your SnakeGame object will be instantiated and called as such:
//  * SnakeGame* obj = new SnakeGame(width, height, food);
//  * int param_1 = obj->move(direction);
//  */
class SnakeGame {
    int WIDTH;
    int HEIGHT;
    // left, top: (x,y) = (0,0);
    // (0,0) (1,0) (2,0)
    // (0,1) (1,1) (2,1)
    // (0,2) (1,2) (2,2)
    struct location{
        int x;  // row
        int y;  // col
        bool operator==(const location& rhs){
            return (x==rhs.x) && (y==rhs.y);
        }
    };
    
    deque<location> food_location;
    deque<location> snake;
public:
    SnakeGame(int width, int height, vector<vector<int>>& food) {
        WIDTH = width;
        HEIGHT = height;
        for(int i=0;i<food.size();i++)
            food_location.push_back({.x = food[i][1],.y =food[i][0]});
        snake.push_back({.x=0,.y=0});
    }
    
    int move(string direction) {
        location new_head = snake.front();

        // detect if snake get out of bound 
        if(direction == "L"){
            new_head.x -= 1;
        }else if (direction == "R"){
            new_head.x += 1;
        }else if( direction == "U"){
            new_head.y -= 1;
        } else if(direction == "D"){
            new_head.y += 1;   
        }
        if( new_head.x < 0 || new_head.x >= WIDTH || new_head.y < 0 || new_head.y >= HEIGHT )
            return -1;
        
        // if snake get food else pop tail
        if(food_location.size()>0 && new_head==food_location.front()){
            food_location.pop_front();
        }else{
            snake.pop_back();
        }
        // if snake hit body (after move)
        // if check snake hit body before calculate get food & pop tail, need skip check tail location
        if(find(snake.begin(),snake.end(), new_head)!=snake.end())
            return -1;
        
        snake.push_front(new_head);

        return snake.size()-1;
    }
};
```
