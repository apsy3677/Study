#include<iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// class snake and ladders can be pair<int,int> 

class Player
{
   
public:
   string name;
   int id;
   int position;
   int getUniqueId()
   {
      static int playersCount = 1;
      return playersCount++;
   }

   Player(string name)
   {
      this->name = name;
      id = getUniqueId();
      position = 0;
   }
};

class Board
{
   vector<Player> &players;
   unordered_map<int, int> snakesAndLadders;
   int currTurn;
   Player* winner;
   const int END_POSITION;

public:
   // vector<Player> players; // if used like this then it creates a copy 
   Board( vector<Player> &players_, const vector< pair<int,int> >& snakes, const vector< pair<int, int> >& ladders, int N ): END_POSITION(N), players( players_ )
   {
      // this->players = players;
      this->currTurn = 0;
      this->winner = nullptr;

      for(auto pair : snakes )
      {
         snakesAndLadders[ pair.first ] = pair.second;
      }
      for( auto pair : ladders )
      {
         snakesAndLadders[ pair.first ] = pair.second;
      }
   }

   void nextPlayer()
   {
      currTurn++;
      currTurn %= players.size();
   }

   bool roll(Player &p, int diceValue)
   {
      if( winner != nullptr || diceValue > 6 || diceValue < 1 || players[ currTurn ].id != p.id )
         return false;

      int dest = players[ currTurn ].position + diceValue;

      if(dest <= END_POSITION )
      {
         if( snakesAndLadders.find(dest) != snakesAndLadders.end() )
         {
            players[ currTurn ].position = snakesAndLadders[ dest ];
         }
         else
         {
            players[ currTurn ].position = dest;
         }
      }

      if( dest == END_POSITION )
      {
         cout << " Destination Reached :: " << players[ currTurn ].name<<endl;
         winner = &players[ currTurn ];
         cout << " All Scores of Players :: \n";

         for( auto p : players )
         {
            cout << p.name << "::" << p.position << " ";
         }
      }
      nextPlayer();
      return true;
   }

   Player * getWinner()
   {
      return winner;
   }
};

int main()
{
   std::cout << "Snakes And Ladders" << endl;

   Player p1( "P1" ), p2( "P2" ), p3( "P3" ), p4( "P4" ), p5( "P5" );

   const vector < pair<int, int> > snakes = {{11,5}, {29,8}, {98,65}, {76, 43}};
   const vector < pair<int, int> > ladders = {{13,55}, {36,58}, {70,85}, {88, 99}};
   vector<Player> players = { p1, p2,p3,p4,p5 };
   // vector<Player> players = { Player( "P1" ), Player( "P2" ) , Player( "P3" ) , Player( "P4" ) , Player( "P5" ) };
   const int N  = 100; // board length

   Board board(players, snakes, ladders, N);

   while( board.getWinner() == nullptr )
   {
      for (auto& player : players)
      {
         const int diceVal = ( rand() % 6 ) + 1;
         board.roll(player, diceVal );
      }
   }

   cout << " the winner is " << board.getWinner()->name;

   cout << " All Scores of Players :: \n";

   for(auto &p : players )
   {
      cout << p.name<<"::"<<p.position << " ";
   }

   return 0;
}