
#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include "Tile.h"
#include "Hand.h"

class Player
{
public:
   Player(std::string name);
   Player(Player &other);
   Player(std::string name, std::string score, std::string handString);
   ~Player();

   // Given a certain tile, adds tile to hand.
   void drawTile(std::shared_ptr<Tile> tile);

   // Remove a certain tile from the hand and return it
   std::shared_ptr<Tile> takeTile(std::shared_ptr<Tile> tile);

   // Remove a certain tile from the hand and return it
   std::shared_ptr<Tile> takeTile(Letter letter);

   // Returns the Player's Hand.
   std::shared_ptr<Hand> getHand();

   // Adds to the player's score.
   void addScore(int numScoreToAdd);

   // Return the player's score.
   int getScore();

   // Prints the hand for reading.
   void printHand();

   // String representation of object
   operator std::string();

   // Get the name of the player.
   std::string getName();

private:
   // Player's Hand
   std::shared_ptr<Hand> hand;

   // Player's score
   int score;

   // Name of Player
   std::string name;
};

#endif // ASSIGN2_PLAYER_H
