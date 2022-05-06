
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"
#include <memory>

class Node
{
public:
   Node(std::shared_ptr<Tile> tile, std::shared_ptr<Node> next, std::shared_ptr<Node> prev);
   Node(Node &other);
   ~Node();

   // The Tile that the Node contains
   std::shared_ptr<Tile> tile;

   // The next Node in the List
   std::shared_ptr<Node> next;

   // The previous Node in the List
   std::shared_ptr<Node> prev;
};

#endif // ASSIGN2_NODE_H
