
#include "LinkedList.h"
#include <iostream>
#include <stdexcept>
#include "utils.h"

LinkedList::LinkedList()
{
}

LinkedList::~LinkedList()
{
   // Smart pointers mostly take care of this, but will not delete themselves if they
   // still have references to each other. We can ensure they don't by setting the references to null.
   std::shared_ptr<Node> currentNode = this->head;
   while (currentNode != nullptr)
   {
      std::shared_ptr<Node> nextNode = currentNode->next;
      currentNode->prev = nullptr;
      currentNode->next = nullptr;
      currentNode->tile = nullptr;
      currentNode = nextNode;
   }
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
// Returns -1 if not found.
int LinkedList::search(std::shared_ptr<Tile> tile)
{
   int returnValue;

   returnValue = search(tile->letter);

   return returnValue;
}

int LinkedList::search(Letter letter)
{
   int returnValue;
   if (this->head != nullptr)
   {
      std::shared_ptr<Node> current = this->head;
      int index = 0;
      while (current->next != nullptr && current->tile->letter != letter)
      {
         current = current->next;
         index++;
      }

      // If the index reached the end of the list, the search term is either the last one, or
      // not in the list. This checks which.
      if (index == this->length && this->head->tile->letter != letter)
      {
         returnValue = -1;
      }
      else
      {
         returnValue = index;
      }
   }
   else
   {
      returnValue = -1;
   }
   return returnValue;
}

int LinkedList::getNumOfOccurrences(Letter letter)
{
   int numOccurrences = 0;

   if (this->head != nullptr)
   {
      std::shared_ptr<Node> current = this->head;
      // Check if the head has the same letter
      if (current->tile->letter == letter)
      {
         numOccurrences++;
      }

      // Loop through the rest of the list.
      while (current->next != nullptr)
      {
         current = current->next;

         if (current->tile->letter == letter)
         {
            numOccurrences++;
         }
      }
   }
   return numOccurrences;
}

void LinkedList::remove(int index)
{
   if (index > this->length && index >= 0)
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
   if (index - 1 > this->length || index < 0)
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
   if (index < this->length && index >= 0)
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

LinkedList::operator std::string()
{
   std::string linkedListAsString = "";

   for (int i = 0; i < this->getLength(); i++)
   {
      Letter letter = this->get(i)->letter;
      int score = this->get(i)->getValue();
      linkedListAsString = linkedListAsString + letter + "-" + std::to_string(score);
      if (i != this->getLength() - 1)
      {
         linkedListAsString = linkedListAsString + ", ";
      }
   }

   return linkedListAsString;
}

// Inverse of the string conversion function
LinkedList::LinkedList(std::string constructionString)
{
   // Splitting by space rather than comma puts the tile character at the start of the string
   std::vector<std::string> tileStrings = splitString(constructionString, ' ');

   for (std::string tileString : tileStrings)
   {
      this->insert(this->getLength(), std::make_shared<Tile>(tileString[0]));
   }
}

void LinkedList::print()
{
   std::string linkedListAsString = std::string(*this);
   if (linkedListAsString != "")
   {
      std::cout << linkedListAsString << std::endl;
   }
   else
   {
      std::cout << "Empty List" << std::endl;
   }
}