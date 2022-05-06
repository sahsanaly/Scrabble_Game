
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
   bool drawTile(std::shared_ptr<Tile> tile);
   // Places a certain tile from the hand.
   std::shared_ptr<Tile> placeTile(char letter);

   std::shared_ptr<Hand> getHand();
   // Prints the hand for reading.
   void readHand();
   // Adds to the player's score.
   bool addPoints();
   // Return the player's score.
   int getScore();

   std::string getAsString();

private:
   std::shared_ptr<Hand> hand;
   int score;
   std::string name;
};

#endif // ASSIGN2_PLAYER_H
