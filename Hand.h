
#ifndef ASSIGN2_HAND_H
#define ASSIGN2_HAND_H

#include "LinkedList.h"
#include <iostream>

class Hand
{
public:
   Hand();
   Hand(Hand &other);
   ~Hand();

   // Add specific tile to hand
   void addTile(std::shared_ptr<Tile> tile);
   
   // Remove tile from hand
   void removeTile(Letter letter);
   
   // Remove tile from hand
   void removeTile(std::shared_ptr<Tile> tile);
   
   // Find the first tile with the desired letter and return its pointer. Return NULL if not found.
   std::shared_ptr<Tile> getTile(Letter letter);

   // Get number of tiles
   int getNumberOfTilesWithLetter(Letter letter);

   // Return all tiles in this hand.
   std::shared_ptr<LinkedList> getTilesInHand();
   
   // Print the String format of the Hand.
   void print();

   // String representation of object
   operator std::string();

private:
   // List of Tiles in Hand
   std::shared_ptr<LinkedList> tilesInHand;
};

#endif //ASSIGN2_HAND_H