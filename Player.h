
#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include "Tile.h"
#include "Hand.h"

class Player
{
public:
   Player();
   Player(Player &other);
   ~Player();

   bool drawTile(Tile* tile);
   bool placeTile(char letter);

   Hand* getHand();

   void readHand();

private:
    Hand* hand;
};

#endif // ASSIGN2_PLAYER_H
