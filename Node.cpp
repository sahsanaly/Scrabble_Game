
#include "Node.h"

Node::Node(std::shared_ptr<Tile> tile, std::shared_ptr<Node> next, std::shared_ptr<Node> prev)
{
   this->tile = tile;
   this->next = next;
   this->prev = prev;
}

Node::Node(Node &other)
{
   this->tile = other.tile;
   this->next = other.next;
   this->prev = other.prev;
}

Node::~Node()
{
   // Smart pointers deal with everything
}