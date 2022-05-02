
#ifndef ASSIGN2_HAND_H
#define ASSIGN2_HAND_H

#include "LinkedList.h"

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

private:
   LinkedList tilesInHand;
};

#endif //ASSIGN2_HAND_H