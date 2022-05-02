
#ifndef ASSIGN2_BAG_H
#define ASSIGN2_BAG_H

#include "LinkedList.h"
#include <iostream>

class Bag
{
public:
   Bag();
   Bag(Bag &other);
   ~Bag();

   // Add specific tile to the tail of the Bag
   bool addTile(Tile* tile);
   
   // Grab the head tile.
   Tile* drawTile();

   // Shuffle the bag (by default during initiation)
   bool shuffle();

   // Convert Bag to string
   std::string getAsString();

   LinkedList tilesInBag;
};

#endif