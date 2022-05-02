
#include "LinkedList.h"
#include <iostream>
#include <stdexcept>

LinkedList::LinkedList()
{
   this->head = nullptr;
   this->tail = nullptr;
   this->length = 0;
}

LinkedList::~LinkedList()
{
   // Smart pointers take care of this for us
}

int LinkedList::getLength()
{
   return this->length;
}

// Returns the Tile at index.
std::shared_ptr<Tile> LinkedList::get(int index)
{
   return this->traverse(index)->tile;
}

// Returns the index of the indicated tile. Only the letter is compared, not the value
int LinkedList::search(std::shared_ptr<Tile> tile)
{
   int returnValue;
   if (this->head != nullptr)
   {
      std::shared_ptr<Node> current = this->head;
      int index = 0;
      while (current->next != nullptr && current->tile->letter != tile->letter)
      {
         current = current->next;
      }
      returnValue = index;
   }
   else
   {
      returnValue = -1;
   }
   return returnValue;
}

void LinkedList::remove(int index)
{
   if (index > this->length && index > 0)
   {
      throw std::out_of_range("Index out of range");
   }
   else
   {
      // The special cases are when the length is 1, or the index is either 0 or length.
      // Handle length == 1 first
      if (this->length == 1)
      {
         this->head = nullptr;
         this->tail = nullptr;
      }
      // Handle index == 0 first
      else if (index == 0)
      {
         std::shared_ptr<Node> deltetionNode = this->head;
         deltetionNode->next->prev = nullptr;
         this->head = deltetionNode->next;
      }
      // Next handle index == length
      else if (index == this->length - 1)
      {
         std::shared_ptr<Node> deltetionNode = this->tail;
         deltetionNode->prev->next = nullptr;
         this->tail = deltetionNode->prev;
      }
      // Otherwise traverse to the insertion point, and insert.
      else
      {
         // We can use the code from this.traverse() to perform the traversal
         std::shared_ptr<Node> deletionNode = this->traverse(index);
         std::cout << this->length << std::endl;
         deletionNode->next->prev = deletionNode->prev;
         deletionNode->prev->next = deletionNode->next;
      }

      // Decrement the length
      length--;
   }
}

// Inserts inserts the given tile such that it will be found at the given index
void LinkedList::insert(int index, std::shared_ptr<Tile> tile)
{
   std::shared_ptr<Node> insertedNode = std::make_shared<Node>(tile, nullptr, nullptr);
   if (index - 1 > this->length && index > 0)
   {
      throw std::out_of_range("Index out of range");
   }
   else
   {
      // The special cases are when the list is empty, or index is either 0 or length.
      // Handle empty list
      if (this->length == 0)
      {
         this->head = insertedNode;
         this->tail = insertedNode;
      }
      // Handle index == 0
      else if (index == 0)
      {
         this->head->prev = insertedNode;
         insertedNode->next = this->head;
         this->head = insertedNode;
      }
      // Next handle index == length
      else if (index == this->length)
      {
         this->tail->next = insertedNode;
         insertedNode->prev = this->tail;
         this->tail = insertedNode;
      }
      // Otherwise traverse to the insertion point, and insert.
      else
      {
         // We can use the code from this.traverse() to perform the traversal
         // referenceNode will be the node immediately before the inserted node
         std::shared_ptr<Node> next = this->traverse(index);
         std::shared_ptr<Node> prev = next->prev;

         prev->next = insertedNode;
         next->prev = insertedNode;
         insertedNode->next = next;
         insertedNode->prev = prev;
      }

      // Increment the length
      length++;
   }
}

// Internal function to traverse to the node at index
std::shared_ptr<Node> LinkedList::traverse(int index)
{
   std::shared_ptr<Node> returnValue;
   if (index < this->length && index > 0)
   {
      // If the index is closer to the length, descend. If the index is closer to 0, ascend.
      if (this->length - index < this->length / 2)
      {
         // Since the index is less than the length, we don't need to check for nullptrs
         // Therefore, we will simply use a for loop.
         std::shared_ptr<Node> current = this->tail;
         for (int i = this->length - 1; i > index; i--)
         {
            current = current->prev;
         }

         returnValue = current;
      }
      else
      {
         // Since the index is less than the length, we don't need to check for nullptrs
         // Therefore, we will simply use a for loop.
         std::shared_ptr<Node> current = this->head;
         for (int i = 0; i < index; i++)
         {
            current = current->next;
         }

         returnValue = current;
      }
   }
   else
   {
      throw std::out_of_range("Index out of range");
   }

   return returnValue;
}

void LinkedList::print()
{
   if (this->head != nullptr)
   {
      std::shared_ptr<Node> current = this->head;
      while (current->next != nullptr)
      {
         std::cout << current->tile->letter << " ";
         current = current->next;
      }
      std::cout << current->tile->letter << " ";
      std::cout << std::endl;
   }
   else
   {
      std::cout << "Empty List" << std::endl;
   }
}