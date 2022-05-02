#include <vector>
#include "Tile.h"
#include <string>
#define BOARD_SIZE

class Board
{
public:
    Tile getTile(char coord1, int coord2);
    void setTile(char coord1, int coord2, Tile tile);
    std::string convertToString();

private:
    std::vector<std::vector<Tile>> board;
};