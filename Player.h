
#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include "Tile.h"
#include "Hand.h"

class Player
{
public:
   Player(std::string name);
   Player(Player &other);
   ~Player();

   // Given a certain tile, adds tile to hand.
   void drawTile(std::shared_ptr<Tile> tile);

   // Remove a certain tile from the hand and return it
   std::shared_ptr<Tile> placeTile(Letter letter);

   // Adds to the player's score.
   void addScore(int numScoreToAdd);
   
   // Returns the Player's Hand.
   std::shared_ptr<Hand> getHand();

   // Return the player's score.
   int getScore();

   // Prints the hand for reading.
   void printHand();

   // Return a String version of the class.
   std::string getAsString();

private:
   std::shared_ptr<Hand> hand;
   int score;
   std::string name;
};

#endif // ASSIGN2_PLAYER_H
