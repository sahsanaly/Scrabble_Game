
#ifndef ASSIGN2_BAG_H
#define ASSIGN2_BAG_H

#include "LinkedList.h"
#include <iostream>

class Bag
{
public:
   Bag();
   Bag(std::string constructionString);
   ~Bag();

   // Add specific tile to the tail of the Bag
   bool addTile(std::shared_ptr<Tile> tile);

   // Grab the head tile.
   std::shared_ptr<Tile> drawTile();

   // Shuffle the bag (by default during initiation)
   void shuffle();

   // String representation of Bag
   operator std::string();

private:
   LinkedList tilesInBag;
};

#endif