
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

// A list of Tiles
class LinkedList
{
public:
   LinkedList();
   ~LinkedList();
   int getLength();
   Tile *get(int index);
   int search(Tile *tile);
   void remove(int index);
   void insert(int index, Tile *tile);
   void print();

private:
   Node *traverse(int index);
   Node *head;
   Node *tail;
   int length;
};

#endif // ASSIGN2_LINKEDLIST_H
