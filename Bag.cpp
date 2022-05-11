#include "Bag.h"
#include <memory>
#include <random>

Bag::Bag()
{
}

Bag::Bag(std::string constructionString)
{
    this->tilesInBag = std::make_shared<LinkedList>(constructionString);
}

Bag::~Bag()
{
}

bool Bag::addTile(std::shared_ptr<Tile> tile)
{
    tilesInBag->insert(tilesInBag->getLength(), tile);
    return true;
}

std::shared_ptr<Tile> Bag::drawTile()
{
    std::shared_ptr<Tile> returnValue = tilesInBag->get(0);
    tilesInBag->remove(0);
    return returnValue;
}

void Bag::shuffle()
{
    // This shuffles the bag in place. It's quite complex.
    // The idea to the method is this:
    //      Virtually partition the bag into two parts: storage and shuffled
    //      Pick a random element of the storage part and move it to the shuffled part
    //      Repeat until all elements are in the shuffled part

    int min = 0;
    int max = this->tilesInBag->getLength() - 1;

    // creating an engine which shuffles the deck different everytime
    std::random_device engine;
    std::uniform_int_distribution<int> uniform_dist(min, max);

    int value;
    for (int i = 0; i < this->tilesInBag->getLength(); i++)
    {
        value = uniform_dist(engine);

        std::shared_ptr<Tile> tile = this->tilesInBag->get(value);
        this->tilesInBag->remove(value);
        this->tilesInBag->insert(0, tile);
    }
}

Bag::operator std::string()
{
    return std::string(*tilesInBag);
}