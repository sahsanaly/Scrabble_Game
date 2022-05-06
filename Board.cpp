#include "Board.h"
#include <iostream>
#include <sstream>

#define BOARD_SIZE 15

Board::Board()
{
    this->board = std::vector<std::vector<std::shared_ptr<Tile>>>();

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        this->board.push_back(std::vector<std::shared_ptr<Tile>>());
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            this->board[i].push_back(std::make_shared<Tile>(char(0)));
        }
    }
}

std::shared_ptr<Tile> Board::getTile(char coord1, int coord2)
{
    // This line converts the char coord to a integer cooord
    int coord1Int = coord1 - 65;

    return this->board[coord1Int][coord2];
}

void Board::setTile(char coord1, int coord2, std::shared_ptr<Tile> tile)
{
    // This line converts the char coord to a integer cooord
    int coord1Int = coord1 - 65;

    this->board[coord1Int][coord2] = tile;
}

std::string Board::convertToString()
{
    std::stringstream output;

    output << ' ';
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (long unsigned int j = 0; j < 4 - std::to_string(i).size(); j++)
        {
            output << ' ';
        }
        output << i + 1;
    }

    output << std::endl;
    output << "  -";
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        output << "----";
    }
    output << std::endl;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        output << std::string(1, i + 65);
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            char tile = this->board[i][j]->letter;
            if (tile == 0)
            {
                output << " |  ";
            }
            else
            {
                output << " | " << tile;
            }
        }
        output << " |" << std::endl;
    }

    return output.str();
}