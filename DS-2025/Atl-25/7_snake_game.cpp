/*
 * Atlassian Interview: Game of Snake
 * 
 * PROBLEM STATEMENT:
 * Implement the classic Snake game logic for a 2D board of arbitrary size.
 * 
 * Basic Rules:
 * - Snake can move up, down, left, or right
 * - Snake's initial size is 3 and grows by 1 every 5 moves
 * - Game ends when snake hits itself or boundaries
 * - Every time moveSnake() is called, snake moves in specified direction
 * 
 * Interface:
 * - moveSnake(snakeDirection)
 * - isGameOver()
 * 
 * Changes:
 * 1. Make scale-up 2 optional (remove path parameters from router)
 * 2. Optional: Snake grows when it eats food rather than every 5 moves
 *    Food is dropped at random position on board
 * 
 * SOLUTION APPROACH:
 * 1. Use deque<Position> for snake body (efficient head/tail operations)
 * 2. Use set<Position> for O(1) collision detection
 * 3. Growth mechanisms:
 *    - Time-based: grow every N moves
 *    - Food-based: grow when snake head reaches food position
 * 4. Collision detection: check boundaries and self-collision
 * 5. Direction validation: prevent moving in opposite direction
 * 6. Food generation: random position not occupied by snake
 * 
 * Time Complexity: O(1) for move operations, O(n) for collision detection
 * Space Complexity: O(n) where n is snake length
 */

#include <iostream>
#include <vector>
#include <deque>
#include <random>
#include <ctime>
#include <set>

using namespace std;

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

struct Position {
    int x, y;
    
    Position(int x = 0, int y = 0) : x(x), y(y) {}
    
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator<(const Position& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

class SnakeGame {
private:
    deque<Position> snake;
    Position food;
    Direction currentDirection;
    bool gameOver;
    int boardWidth, boardHeight;
    int moveCount;
    int growthInterval;
    bool hasFoodOnBoard;
    mt19937 rng;
    set<Position> snakePositions; // For O(1) collision detection
    
public:
    // Basic constructor for original requirements
    SnakeGame(int width = 20, int height = 20) 
        : boardWidth(width), boardHeight(height), gameOver(false), 
          moveCount(0), growthInterval(5), hasFoodOnBoard(false), 
          currentDirection(RIGHT), rng(time(nullptr)) {
        
        // Initialize snake with size 3 in the middle of the board
        int startX = width / 2;
        int startY = height / 2;
        
        snake.push_back(Position(startX, startY));     // Head
        snake.push_back(Position(startX - 1, startY)); // Body
        snake.push_back(Position(startX - 2, startY)); // Tail
        
        // Update position set
        for (const auto& pos : snake) {
            snakePositions.insert(pos);
        }
    }
    
    // Constructor with food-based growth (Change #2)
    SnakeGame(int width, int height, bool foodBasedGrowth) 
        : SnakeGame(width, height) {
        
        if (foodBasedGrowth) {
            growthInterval = INT_MAX; // Disable time-based growth
            generateFood();
        }
    }
    
    void moveSnake(Direction direction) {
        if (gameOver) return;
        
        // Prevent moving in opposite direction
        if (isOppositeDirection(direction, currentDirection)) {
            direction = currentDirection;
        }
        
        currentDirection = direction;
        Position head = snake.front();
        Position newHead = getNextPosition(head, direction);
        
        // Check boundary collision
        if (isOutOfBounds(newHead)) {
            gameOver = true;
            return;
        }
        
        // Check self collision
        if (snakePositions.count(newHead)) {
            gameOver = true;
            return;
        }
        
        // Move snake
        snake.push_front(newHead);
        snakePositions.insert(newHead);
        
        bool shouldGrow = false;
        
        // Check if food was eaten (food-based growth)
        if (hasFoodOnBoard && newHead == food) {
            shouldGrow = true;
            hasFoodOnBoard = false;
            generateFood();
        }
        
        // Check if should grow (time-based growth)
        moveCount++;
        if (!shouldGrow && moveCount % growthInterval == 0) {
            shouldGrow = true;
        }
        
        if (!shouldGrow) {
            // Remove tail
            Position tail = snake.back();
            snake.pop_back();
            snakePositions.erase(tail);
        }
    }
    
    bool isGameOver() const {
        return gameOver;
    }
    
    // Additional useful methods
    int getSnakeLength() const {
        return snake.size();
    }
    
    vector<Position> getSnakePositions() const {
        return vector<Position>(snake.begin(), snake.end());
    }
    
    Position getFoodPosition() const {
        return food;
    }
    
    bool hasFoodAvailable() const {
        return hasFoodOnBoard;
    }
    
    int getMoveCount() const {
        return moveCount;
    }
    
    Direction getCurrentDirection() const {
        return currentDirection;
    }
    
    // Reset game
    void resetGame() {
        snake.clear();
        snakePositions.clear();
        gameOver = false;
        moveCount = 0;
        hasFoodOnBoard = false;
        currentDirection = RIGHT;
        
        // Reinitialize snake
        int startX = boardWidth / 2;
        int startY = boardHeight / 2;
        
        snake.push_back(Position(startX, startY));
        snake.push_back(Position(startX - 1, startY));
        snake.push_back(Position(startX - 2, startY));
        
        for (const auto& pos : snake) {
            snakePositions.insert(pos);
        }
    }
    
    // Print game state (for debugging)
    void printGameState() {
        cout << "\n=== Game State ===" << endl;
        for (int y = 0; y < boardHeight; y++) {
            for (int x = 0; x < boardWidth; x++) {
                Position current(x, y);
                
                if (current == snake.front()) {
                    cout << "H "; // Head
                } else if (snakePositions.count(current)) {
                    cout << "S "; // Snake body
                } else if (hasFoodOnBoard && current == food) {
                    cout << "F "; // Food
                } else {
                    cout << ". "; // Empty
                }
            }
            cout << endl;
        }
        
        cout << "Snake Length: " << getSnakeLength() << endl;
        cout << "Move Count: " << moveCount << endl;
        cout << "Game Over: " << (gameOver ? "Yes" : "No") << endl;
        if (hasFoodOnBoard) {
            cout << "Food at: (" << food.x << ", " << food.y << ")" << endl;
        }
    }

private:
    Position getNextPosition(const Position& current, Direction dir) {
        Position next = current;
        
        switch (dir) {
            case UP:    next.y--; break;
            case DOWN:  next.y++; break;
            case LEFT:  next.x--; break;
            case RIGHT: next.x++; break;
        }
        
        return next;
    }
    
    bool isOutOfBounds(const Position& pos) {
        return pos.x < 0 || pos.x >= boardWidth || pos.y < 0 || pos.y >= boardHeight;
    }
    
    bool isOppositeDirection(Direction dir1, Direction dir2) {
        return (dir1 == UP && dir2 == DOWN) ||
               (dir1 == DOWN && dir2 == UP) ||
               (dir1 == LEFT && dir2 == RIGHT) ||
               (dir1 == RIGHT && dir2 == LEFT);
    }
    
    void generateFood() {
        if (snakePositions.size() >= boardWidth * boardHeight) {
            // Board is full, can't place food
            return;
        }
        
        Position newFood;
        do {
            newFood.x = rng() % boardWidth;
            newFood.y = rng() % boardHeight;
        } while (snakePositions.count(newFood));
        
        food = newFood;
        hasFoodOnBoard = true;
    }
};

// Advanced Snake Game with additional features
class AdvancedSnakeGame : public SnakeGame {
private:
    int score;
    int level;
    int speedMultiplier;
    
public:
    AdvancedSnakeGame(int width = 20, int height = 20) 
        : SnakeGame(width, height, true), score(0), level(1), speedMultiplier(1) {}
    
    void moveSnake(Direction direction) override {
        int oldLength = getSnakeLength();
        SnakeGame::moveSnake(direction);
        
        // Update score if snake grew
        if (getSnakeLength() > oldLength) {
            score += 10 * level;
            
            // Level up every 5 food items
            if (score > 0 && score % 50 == 0) {
                level++;
                speedMultiplier++;
            }
        }
    }
    
    int getScore() const {
        return score;
    }
    
    int getLevel() const {
        return level;
    }
    
    int getSpeedMultiplier() const {
        return speedMultiplier;
    }
    
    void printAdvancedGameState() {
        printGameState();
        cout << "Score: " << score << endl;
        cout << "Level: " << level << endl;
        cout << "Speed: " << speedMultiplier << "x" << endl;
    }
};

// Test functions
void testBasicSnakeGame() {
    cout << "\n=== Testing Basic Snake Game ===" << endl;
    
    SnakeGame game(10, 10);
    
    cout << "Initial state:" << endl;
    game.printGameState();
    
    // Move snake around
    vector<Direction> moves = {RIGHT, RIGHT, DOWN, DOWN, LEFT, UP};
    
    for (Direction move : moves) {
        if (!game.isGameOver()) {
            cout << "\nMoving " << (move == UP ? "UP" : move == DOWN ? "DOWN" : 
                                   move == LEFT ? "LEFT" : "RIGHT") << endl;
            game.moveSnake(move);
            game.printGameState();
        }
    }
}

void testGrowthMechanism() {
    cout << "\n=== Testing Growth Mechanism ===" << endl;
    
    SnakeGame game(15, 15);
    
    cout << "Initial length: " << game.getSnakeLength() << endl;
    
    // Move 5 times to trigger growth
    for (int i = 0; i < 6; i++) {
        game.moveSnake(RIGHT);
        cout << "After move " << (i + 1) << ", length: " << game.getSnakeLength() << endl;
    }
}

void testCollisions() {
    cout << "\n=== Testing Collision Detection ===" << endl;
    
    SnakeGame game(5, 5); // Small board for easy collision
    
    // Move until boundary collision
    cout << "Moving right until boundary collision:" << endl;
    while (!game.isGameOver()) {
        game.moveSnake(RIGHT);
        cout << "Move " << game.getMoveCount() << ", Game Over: " << game.isGameOver() << endl;
    }
    
    // Test self collision
    game.resetGame();
    cout << "\nTesting self collision:" << endl;
    
    vector<Direction> selfCollisionMoves = {RIGHT, RIGHT, DOWN, LEFT, UP};
    for (Direction move : selfCollisionMoves) {
        if (!game.isGameOver()) {
            game.moveSnake(move);
            cout << "After move, Game Over: " << game.isGameOver() << endl;
        }
    }
}

void testFoodBasedGrowth() {
    cout << "\n=== Testing Food-Based Growth ===" << endl;
    
    SnakeGame game(10, 10, true); // Enable food-based growth
    
    cout << "Initial state with food:" << endl;
    game.printGameState();
    
    // Try to reach food
    Position foodPos = game.getFoodPosition();
    Position snakeHead = game.getSnakePositions()[0];
    
    cout << "Food is at (" << foodPos.x << ", " << foodPos.y << ")" << endl;
    cout << "Snake head at (" << snakeHead.x << ", " << snakeHead.y << ")" << endl;
    
    // Simple pathfinding to food
    int initialLength = game.getSnakeLength();
    int moves = 0;
    
    while (!game.isGameOver() && moves < 20) {
        snakeHead = game.getSnakePositions()[0];
        
        Direction nextMove = RIGHT;
        if (snakeHead.x < foodPos.x) nextMove = RIGHT;
        else if (snakeHead.x > foodPos.x) nextMove = LEFT;
        else if (snakeHead.y < foodPos.y) nextMove = DOWN;
        else if (snakeHead.y > foodPos.y) nextMove = UP;
        
        game.moveSnake(nextMove);
        moves++;
        
        if (game.getSnakeLength() > initialLength) {
            cout << "Snake grew! Length is now " << game.getSnakeLength() << endl;
            game.printGameState();
            break;
        }
    }
}

void testAdvancedFeatures() {
    cout << "\n=== Testing Advanced Features ===" << endl;
    
    AdvancedSnakeGame game(8, 8);
    
    // Simulate eating several food items
    for (int i = 0; i < 10 && !game.isGameOver(); i++) {
        Position foodPos = game.getFoodPosition();
        Position head = game.getSnakePositions()[0];
        
        // Simple movement toward food
        if (head.x < foodPos.x) game.moveSnake(RIGHT);
        else if (head.x > foodPos.x) game.moveSnake(LEFT);
        else if (head.y < foodPos.y) game.moveSnake(DOWN);
        else if (head.y > foodPos.y) game.moveSnake(UP);
        else game.moveSnake(RIGHT); // Random move if at food position
        
        cout << "Score: " << game.getScore() << ", Level: " << game.getLevel() << endl;
    }
    
    game.printAdvancedGameState();
}

int main() {
    testBasicSnakeGame();
    testGrowthMechanism();
    testCollisions();
    testFoodBasedGrowth();
    testAdvancedFeatures();
    
    return 0;
}
