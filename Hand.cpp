#include "Hand.h"
#include <iostream>

Hand::Hand()
{
    this->tilesInHand = std::make_shared<LinkedList>();
}

Hand::Hand(Hand &other)
{
    this->tilesInHand = other.getTilesInHand();
}

Hand::~Hand()
{
    // Using smart pointers, so no need to give deconstruct instructions.
}

void Hand::addTile(std::shared_ptr<Tile> tile)
{
    tilesInHand->insert(0, tile);
    return;
}

void Hand::removeTile(Letter letter) 
{
    // Search for the first tile with given letter.
    int indexTileInHand = tilesInHand->search(letter);

    tilesInHand->remove(indexTileInHand);
    return;
}

void Hand::removeTile(std::shared_ptr<Tile> tile) 
{
    removeTile(tile->letter);
    return;
}

std::shared_ptr<Tile> Hand::getTile(Letter letter) 
{
    std::shared_ptr<Tile> tileToAdd = nullptr;

    int indexTile = this->tilesInHand->search(letter);

    bool tileFound = (indexTile != -1);

    if (tileFound)
    {
        tileToAdd = tilesInHand->get(indexTile);
    }

    return tileToAdd;
}

std::shared_ptr<LinkedList> Hand::getTilesInHand()
{
    return tilesInHand;
}

int Hand::getNumberOfTilesWithLetter(Letter letter)
{
    return this->tilesInHand->getNumOfOccurrences(letter);
}

Hand::operator std::string()
{
    std::string handInfoAsString = "";

    handInfoAsString = std::string(*tilesInHand);

    return handInfoAsString;
}

void Hand::print()
{
    std::cout << std::string(*this) << std::endl;
    return;
}