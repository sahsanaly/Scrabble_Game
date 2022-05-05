
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
   void removeTile(std::shared_ptr<Tile> tile);
   
   // Find the first tile with the desired letter and return its pointer. Return NULL if not found.
   std::shared_ptr<Tile> getTile(Letter letter);

   // Convert Hand to string of tiles and return it
   std::string getAsString();

   // Return all tiles in this hand.
   LinkedList getTilesInHand();
   
   void print();

private:
   LinkedList tilesInHand;
};

#endif //ASSIGN2_HAND_H