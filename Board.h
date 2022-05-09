#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include <vector>
#include "Tile.h"
#include <memory>
#include <string>

class Board
{
public:
    Board();
    std::shared_ptr<Tile> getTile(char coord1, int coord2);
    void setTile(char coord1, int coord2, std::shared_ptr<Tile> tile);
    std::string convertToString();

    // Returns a list of the "word" in the letterDirection or intDirection, that intersects (coord1, coord2)
    std::vector<std::shared_ptr<Tile>> getWord(char coord1, int coord2, bool letterDirection);

private:
    std::vector<std::vector<std::shared_ptr<Tile>>> board;
};

#endif