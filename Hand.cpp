#include "Hand.h"
#include <iostream>

Hand::Hand() 
{
    this->tilesInHand = LinkedList();
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
    tilesInHand.insert(0, tile);
    return;
}

void Hand::removeTile(std::shared_ptr<Tile> tile) 
{
    int indexTileInHand = tilesInHand.search(tile);

    tilesInHand.remove(indexTileInHand);
    return;
}

std::shared_ptr<Tile> Hand::getTile(Letter letter) 
{
    std::shared_ptr<Tile> tileToAdd = nullptr;

    for (int i = 0; i < tilesInHand.getLength(); i++) {
        std::shared_ptr<Tile> tile = tilesInHand.get(i);

        bool tileMatchesLetter = (tile->letter == letter);

        if (tileMatchesLetter) {
            tileToAdd = tile;
        }
    }

    return tileToAdd;
}

LinkedList Hand::getTilesInHand()
{
    return tilesInHand;
}

std::string Hand::getAsString() 
{
    std::string handInfoAsString = "";

    for (int i = 0; i < tilesInHand.getLength(); i++) {
        Letter letter = tilesInHand.get(i)->letter;
        handInfoAsString = handInfoAsString + letter;
    }

    return handInfoAsString;
}

void Hand::print()
{
    std::string stringToPrint = getAsString();
    
    std::cout << stringToPrint << std::endl;

    return;
}