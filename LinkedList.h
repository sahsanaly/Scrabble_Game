
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <memory>

// A list of Tiles
class LinkedList
{
public:
   LinkedList();
   // Inverse of the string representation.
   LinkedList(std::string constructionString);
   ~LinkedList();

   // Get length of object
   int getLength();

   // Get tile at index
   std::shared_ptr<Tile> get(int index);

   // Index first tile with letter (of tile)
   int search(std::shared_ptr<Tile> tile);

   // Index first tile with letter
   int search(Letter letter);

   // Get the number of tiles that match the letter.
   int getNumOfOccurrences(Letter letter);

   // Remove tile at index
   void remove(int index);

   // Insert a tile at index
   void insert(int index, std::shared_ptr<Tile> tile);

   // String representation of object
   operator std::string();

   // Print String representation of object
   void print();

private:
   // Move from the head or tail (whichever is closer) to the Node at index
   std::shared_ptr<Node> traverse(int index);

   // The first Node in the List
   std::shared_ptr<Node> head = nullptr;

   // The final Node in the List
   std::shared_ptr<Node> tail = nullptr;

   // Length of List
   int length = 0;
};

#endif // ASSIGN2_LINKEDLIST_H
