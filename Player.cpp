#include "Player.h"

// These functions are by no means complete. Just something to try and make the main loop run.
// Tear them out and do them properly when implementing this file please.
Player::Player(std::string name)
{
    this->name = name;
    this->score = 0;
    this->hand = std::make_shared<Hand>();
}

Player::Player(Player &other)
{
    this->name = other.name;
    this->score = other.score;
    this->hand = std::make_shared<Hand>(*other.hand);
}

Player::~Player()
{
    // Not necessary due to use of smart pointers
}

void Player::drawTile(std::shared_ptr<Tile> tile)
{
    this->hand->addTile(tile);
}

std::shared_ptr<Tile> Player::removeTile(std::shared_ptr<Tile> tile)
{
    this->hand->removeTile(tile);

    return tile;
}

std::shared_ptr<Tile> Player::removeTile(char letter)
{
    std::shared_ptr<Tile> tileToPlace = this->hand->getTile(letter);

    removeTile(tileToPlace);

    return tileToPlace;
}

std::shared_ptr<Hand> Player::getHand()
{
    return this->hand;
}

int Player::getScore()
{
    return this->score;
}

void Player::addScore(int numScoreToAdd)
{
    this->score = score + numScoreToAdd;
}

void Player::printHand()
{
    this->hand->print();
}

Player::operator std::string()
{
    std::string playerAsString = "";
    playerAsString.append(name);
    playerAsString.append("\n");
    playerAsString.append(std::to_string(score));
    playerAsString.append("\n");
    playerAsString.append(std::string(*this->hand));

    return playerAsString;
}

std::string Player::getName()
{
    return this->name;
}