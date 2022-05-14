#include "Hand.h"
#include <iostream>

Hand::Hand()
{
    this->tilesInHand = std::make_shared<LinkedList>();
    this->lengthHand = 0;       //num of the tiles in hand
}

Hand::Hand(Hand &other)
{
    this->tilesInHand = other.getTilesInHand();
    this->lengthHand = other.lengthHand;
}

Hand::Hand(std::string constructionString)
{
    this->tilesInHand = std::make_shared<LinkedList>(constructionString);
    this->lengthHand = this->tilesInHand->getLength();
}

Hand::~Hand()
{
    this->tilesInHand = nullptr;
}

void Hand::addTile(std::shared_ptr<Tile> tile)
{
    tilesInHand->insert(tilesInHand->getLength(), tile);
    ++lengthHand;
    return;
}

void Hand::removeTile(Letter letter)
{
    // Search for the first tile with given letter.
    int indexTileInHand = tilesInHand->search(letter);

    tilesInHand->remove(indexTileInHand);
    --this->lengthHand;
    return;
}

void Hand::removeTile(std::shared_ptr<Tile> tile)
{
    removeTile(tile->letter);
    --lengthHand;
    return;
}

int Hand::getHandLength(){

    return this->lengthHand;        //number of tiles in hand
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