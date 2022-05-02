#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include <vector>
#include "Tile.h"
#include <string>

class Board
{
public:
    Tile getTile(char coord1, int coord2);
    void setTile(char coord1, int coord2, Tile tile);
    std::string convertToString();

private:
    std::vector<std::vector<Tile>> board;
};

#endif