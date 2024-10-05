#include <bits/stdc++.h>

using namespace std;

// TicTacToe
// Piece X,0
// Board
// Player

enum PieceType{
    NONE,
    X,
    O
};

class Piece {
    PieceType pieceType;

public:
    Piece (PieceType p) : pieceType(p) {}
};

class PieceX : public Piece{
    
public :
    PieceX () : Piece(X) {}
};

class PieceO : public Piece{
    
public :
    PieceO () : Piece(O) {
        
    }
};

class Player {
    string name;
    Piece *piece;
    int id;

public:
    Player(string inName, Piece * p) {
        piece = p;
        name = inName;
        id = getId();
    }
    static int getId() {
        static int id = 0;
        return id++;
    }
    Piece* getPiece() {
        return piece;
    }
};

class Board {
    // 2D array of nxm 
    // Each point can contain a piece
    vector<vector<Piece *>> board;
    int size;

public:
    Board (int sz) {
        size = sz;
        board.resize(size, vector<Piece *>(size, nullptr));
    }
};

class Game {
    // look back what is better, Player, Player * or Player& or using unique pointers
    list<Player *> players; 
    Board *board;

public:
    // Play
    Game () {
        initGame();
    }

    void initGame() {
        // create 2 pieces
        // create 2 players
        // create Board
        Piece *p1 = new PieceX();
        Piece *p2 = new PieceO();

        players.push_back(new Player("P1", p1)); // initialize using initialzer list
        players.push_back(new Player("P2", p2));

        board = new Board(3);
    }
};

int main() {
    cout << "LLD of TicTacToe Game!!" <<endl;
    return 0;
}