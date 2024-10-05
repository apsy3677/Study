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
    unique_ptr<Piece> piece;
    int id;

public:
    Player(string inName, unique_ptr<Piece> p) : name(inName), piece(std::move(p)), id(getId()) {}
    static int getId() {
        static int id = 0;
        return id++;
    }
    // unique_ptr<Piece> getPiece() {
    //     return piece;
    // }
};

class Board {
    // 2D array of nxm 
    // Each point can contain a piece
    vector<vector< unique_ptr<Piece> >> board;
    int size;

public:
    Board (int sz) {
        size = sz;
        // board.resize(size, vector<unique_ptr<Piece>>(size));
    }
};

class Game {
    // look back what is better, Player, Player * or Player& or using unique pointers
    vector< unique_ptr<Player> > players; 
    unique_ptr<Board> board;

public:
    // Play
    Game () {
        initGame();
    }

    void initGame() {
        // create 2 pieces
        // create 2 players
        // create Board
        // Piece *p1 = new PieceX();
        // Piece *p2 = new PieceO();
        auto p1 = make_unique< PieceX> ();
        auto p2 = make_unique< PieceO> ();

        players.push_back(make_unique <Player> ("P1", move(p1))); // initialize using initialzer list
        players.push_back(make_unique <Player> ("P2", move(p2)));

        board = make_unique<Board>(3);
    }
};

int main() {
    cout << "LLD of TicTacToe Game using unique Pointers !!" <<endl;
    return 0;
}