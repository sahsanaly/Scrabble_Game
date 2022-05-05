#include "Bag.h"
#include <memory>
#include <random>

Bag::Bag()
{
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

void Bag::shuffle()
{
    // This shuffles the bag in place. It's quite complex.
    // The idea to the method is this:
    //      Virtually partition the bag into two parts: storage and shuffled
    //      Pick a random element of the storage part and move it to the shuffled part
    //      Repeat until all elements are in the shuffled part

    for (int virtualBoundary = 0; virtualBoundary < this->tilesInBag.getLength(); virtualBoundary++)
    {
        int storageSize = this->tilesInBag.getLength() - virtualBoundary;

        int indexToMove = (std::rand() % (storageSize)) + virtualBoundary;

        std::shared_ptr<Tile> tile = this->tilesInBag.get(indexToMove);
        this->tilesInBag.remove(indexToMove);
        this->tilesInBag.insert(0, tile);
    }
}