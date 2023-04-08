#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Game;

class Player
{
   int id;

   int getUniqueid()
   {
      static int totalPlayers = 0;
      return totalPlayers++;
   }
public:
   static const int MAX_ROLLS_ALLOWED = 23; // 10 turns (max 2 in each turn) + (3 maximum allowed in last turn if all are strikes)
   int score;
   vector<int> rolls;
   bool firstRoll;
   int frameIndex;
   string name;
   bool canPlay;
   int current;

   Player(string name)
   {
      this->name = name;
      id = getUniqueid();
      score = 0;
      rolls.clear();
      rolls.resize(MAX_ROLLS_ALLOWED,0);
      firstRoll = true;
      frameIndex = 0;
      canPlay = true;
      current = 0;
   }

   void updateScore()
   {
      if( isStrike() )
      {
         score += 20;
         rolls[ current++ ] = 0;
         frameIndex += 2;

         if(frameIndex >= MAX_ROLLS_ALLOWED )
         {
            canPlay = false;
         }
      }
      else
      {
         if( frameIndex >= MAX_ROLLS_ALLOWED - 1 )
         {
            score += rolls[ frameIndex ];
            canPlay = false;
         }
         else if( firstRoll ) firstRoll = false;
         else
         {
            if( isSpare() ) score += 5;
            score += ( rolls[ frameIndex ] + rolls[ frameIndex + 1 ] );
            frameIndex += 2;
            firstRoll = true;
            if(frameIndex >= MAX_ROLLS_ALLOWED -3 )
            {
               canPlay = false;
            }
         }
      }
   }

   void roll(int pins)
   {
      if( !canPlay ) return;
      rolls[ current++ ] = pins;
      updateScore();
   }
   bool isStrike()
   {
      return firstRoll && rolls[ frameIndex ] == 10;
   }
   bool isSpare()
   {
      return rolls[ frameIndex ] + rolls[ frameIndex + 1 ] == 10;
   }
};

class GameSession
{
public:
   vector<Player> players;
   int id;
   int laneNumber;

   int getUniqueId()
   {
      static int gameSession = 1;
      return gameSession++;
   }

   void makeRoll(const Player& player, int pins)
   {
      for(Player &p : players )
      {
         if(p.name == player.name )
         {
            p.roll(pins);
         }
      }
   }

   GameSession()
   {
      laneNumber = -1;
      id = getUniqueId();
      players.clear();
   }
   bool declareWinner();
   
};

class Game
{
   unordered_map<int, GameSession> gameSessions;
public:
   vector<int> lanes;
   static int totalLanes;

   Game()
   {
      totalLanes = 2; // given by interviewer

   }
   void roll(int gameSessionId, Player & player, int pins)
   {
      GameSession& gameSession = gameSessions[ gameSessionId ];
      gameSession.makeRoll( player, pins );
   }
   int createSession( vector<Player> &players )
   {
      if( totalLanes == 0)
      {
         cout << "All Lanes are occupied \n";
         return 0;
      }
      GameSession game_session;
      game_session.players = players;
      game_session.laneNumber = totalLanes--;
      gameSessions[ game_session.id ] = game_session;
      return game_session.id;
   }
   bool declareWinner(int gameSessionId )
   {
      bool winnerFlag = gameSessions[ gameSessionId ].declareWinner();
      if(!winnerFlag )
      {
         cout << "No Winners Yet\n";
         return winnerFlag;
      }
      return winnerFlag;
   }
   
};

int Game::totalLanes = 2;

bool GameSession :: declareWinner()
{
   int maxScore = 0;
   // Player winner;
   Player* winner = nullptr;

   for( Player& p : players )
   {
      if( p.canPlay )
      {
         cout << "Player " << p.name << " hasn't completed yet. Current Score : " << p.score << endl;
         return false;
      }
      if( p.score > maxScore )
      {
         maxScore = p.score;
         winner = &p;
      }
   }
   if( winner )
   {
      cout << "Winner is " << winner->name << " score is " << winner->score << endl;
   }
   // Game finished increase the lane
   Game::totalLanes++;
   return true;
}

int main()
{
   cout << " Bowling Game \n";

   vector<Player> players = { Player( "P1" ), Player( "P2" ), Player( "P3" ), Player( "P4" ) };
   Game game;
   int index = game.createSession( players );

   vector<int> s1, s2, s3, s4;
   int score = 0;

   for(int i=0;i<20;i++ )
   {
      score = abs( rand() % 11 ); s1.push_back( score ); game.roll( index, players[ 0 ], score );
      score = abs( rand() % 11 ); s2.push_back( score ); game.roll( index, players[ 1 ], score );
      score = abs( rand() % 11 ); s3.push_back( score ); game.roll( index, players[ 2 ], score );
      score = abs( rand() % 11 ); s4.push_back( score ); game.roll( index, players[ 3 ], score );
   }

   auto print = [&]( vector<int> &vec, Player & p )
   {
      cout << "Player " << p.name<<":: ";
      for( int x : vec )
         cout << x << " ";
      cout << endl;
   };

   print( s1, players[ 0 ] );
   print( s2, players[ 1 ] );
   print( s3, players[ 2 ] );
   print( s4, players[ 3 ] ); 

   cout << Game::totalLanes << " Total Lanes \n";

   game.declareWinner( index );
   cout << Game::totalLanes << " Total Lanes \n";
   game.createSession(players); 
   cout << Game::totalLanes << " Total Lanes \n";
   game.createSession(players);
   game.createSession(players);
   // game.createSession(players);
   // game.createSession(players);
   // game.createSession(players);
   // game.createSession(players);

   return 0;
}