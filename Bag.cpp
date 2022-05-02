#include "Bag.h"

Bag::Bag()
{
    tilesInBag = LinkedList();
}

Bag::~Bag()
{
}

bool Bag::addTile(std::shared_ptr<Tile> tile)
{
    tilesInBag.insert(tilesInBag.getLength(), tile);
    return true;
}

std::shared_ptr<Tile> Bag::drawTile()
{
    std::shared_ptr<Tile> returnValue = tilesInBag.get(0);
    tilesInBag.remove(0);
    return returnValue;
}