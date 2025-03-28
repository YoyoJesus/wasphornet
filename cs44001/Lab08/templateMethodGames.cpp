// Games, Template Method example
// Mikhail Nesterenko
// 2/4/2014

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>

using std::cout; using std::endl; using std::cin;
using std::string;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game{
public:
   Game():playersCount_(0), movesCount_(0), playerWon_(noWinner){}

   // template method
   void playGame(const int playersCount = 0) {
      playersCount_ = playersCount;
      movesCount_=0;

      initializeGame();

      for(int i=0; !endOfGame(); i = (i+1) % playersCount_ ){
	 makeMove(i);
	 if (i==playersCount_-1) 
	    ++movesCount_; 
      }
      printWinner();
   }

   virtual ~Game(){}

protected:
   // primitive operations
   virtual void initializeGame() = 0;
   virtual void makeMove(int player) = 0;
   virtual void printWinner() = 0;
   virtual bool endOfGame() { return playerWon_ != noWinner;} // this is a hook
                   // returns true if winner is decided
   static const int noWinner=-1;

   int playersCount_;
   int movesCount_;
   int playerWon_;
};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly: public Game {
public:  
   // implementing concrete methods
   void initializeGame(){
      playersCount_ = rand() % numPlayers_ + 1 ; // initialize players
   }

   void makeMove(int player) {
      if (movesCount_ > minMoves_){ 
	 const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
	 if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Monopoly, player "<< playerWon_<< " won in "
	   << movesCount_<< " moves." << endl;
   }

private:
   static const int numPlayers_ = 8; // max number of players
   static const int minMoves_ = 20; // nobody wins before minMoves_
   static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess: public Game {
public:
   void initializeGame(){
      playersCount_ = numPlayers_; // initalize players
      for(int i=0; i < numPlayers_; ++i) 
	     experience_[i] = rand() % maxExperience_ + 1 ; 
   }

   void makeMove(int player){
      if (movesCount_ > minMoves_){
	 const int chance = (rand() % maxMoves_) / experience_[player];
	 if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Chess, player " << playerWon_ 
	   << " with experience " << experience_[playerWon_]
	   << " won in "<< movesCount_ << " moves over"
	   << " player with experience " << experience_[playerWon_== 0 ? 1:0] 
           << endl;
   }

private:
   static const int numPlayers_ = 2;
   static const int minMoves_ = 5; // nobody wins before minMoves_
   static const int maxMoves_ = 100; // somebody wins before maxMoves_
   static const int maxExperience_ = 5; // player's experience
                              // the higher, the greater probability of winning
   int experience_[numPlayers_]; 
};

// Rock Paper Scissors
class RPS: public Game {
public:
   void initializeGame(){
      playersCount_ = numPlayers_; // initialize players
      movesCount_ = moves_;
      // player 1 is pc & player 2 is user
   }

   void makeMove(int player){
      if (player == 0) {
         char moves[] = {'r', 'p', 's'};
         playerMoves_[player] = moves[rand() % 3];

      } else {
         cout << "Human, (r)ock, (p)aper, or (s)cissors? ";
         cin >> playerMoves_[player];

         checkWin();
      }
   }

   // print the winner of the game
   void printWinner() {
      if (playerWon_ == 0) {
         cout << "Computer selected " << convertChar(playerMoves_[0]) << ". You lost!" << endl;
      } else if (playerWon_ == 1) {
         cout << "Computer selected " << convertChar(playerMoves_[0]) << ". You Won!" << endl;
      }
   }

   // formating function to convert char to string
   string convertChar(char c) {
      if (c == 'r') {
         return "rock";
      } else if (c == 'p') {
         return "paper";
      } else {
         return "scissors";
      }
   }

   // helper function to check who won - more abstracted
   void checkWin() {
      // check if the pc or user won
      if (playerMoves_[0] == 'r' && playerMoves_[1] == 's') {
         playerWon_ = 0;
      } else if (playerMoves_[0] == 's' && playerMoves_[1] == 'p') {
         playerWon_ = 0;
      } else if (playerMoves_[0] == 'p' && playerMoves_[1] == 'r') {
         playerWon_ = 0;
      } else if (playerMoves_[0] == playerMoves_[1]) {
         // Tie - game is not over
         cout << "Computer selected " << convertChar(playerMoves_[0]) << ". Tie Game, play again"<< endl;
      } else {
         playerWon_ = 1;
      }
   }

private:
   //pc = 0, user = 1
   static const int numPlayers_ = 2;

   // only one move per game
   static const int moves_ = 1;

   // rock beats scissors, scissors beats paper, paper beats rock
   // store the moves of the players
   char playerMoves_[numPlayers_];
};

int main() {
   srand(time(nullptr));

   Game* gp = nullptr;
/*
   // play chess 7 times
   for (int i = 0; i < 7; ++i){ 
      gp = new Chess;
      gp -> playGame(); 
      delete gp;
   }
      

   // play monopoly 7 times
   for (int i = 0; i < 7; ++i){
      gp = new Monopoly;
      gp -> playGame(); 
      delete gp;
   }
*/
   // play rock paper scissors 7 times
   for (int i = 0; i < 7; ++i){
      gp = new RPS;
      gp -> playGame(); 
      delete gp;
   }
}
