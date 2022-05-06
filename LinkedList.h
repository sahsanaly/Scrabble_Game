
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <memory>

// A list of Tiles
class LinkedList
{
public:
   LinkedList();
   ~LinkedList();
   int getLength();
   std::shared_ptr<Tile> get(int index);
   int search(std::shared_ptr<Tile> tile);
   int search(Letter letter);
   int getNumOfOccurrences(Letter letter);
   void remove(int index);
   void insert(int index, std::shared_ptr<Tile> tile);
   void print();

private:
   std::shared_ptr<Node> traverse(int index);
   std::shared_ptr<Node> head;
   std::shared_ptr<Node> tail;
   int length;
};

#endif // ASSIGN2_LINKEDLIST_H
