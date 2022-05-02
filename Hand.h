
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
   bool addTile(Tile* tile);
   // Remove tile from hand
   bool removeTile(Tile* tile);
   
   // Find the first tile with the desired letter and return its pointer. Return NULL if not found.
   Tile* getTile(char letter);

   // Convert Hand to string of tiles and return it
   std::string getAsString();
   
   std::string print();

private:
   LinkedList tilesInHand;
};

#endif //ASSIGN2_HAND_H