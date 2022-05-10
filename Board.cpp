#include "Board.h"
#include <iostream>
#include <sstream>
#include "defines.h"
#include "utils.h"

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

std::vector<std::shared_ptr<Tile>> Board::getWord(char coord1, int coord2, bool letterDirection)
{
    std::vector<std::shared_ptr<Tile>> returnValue;
    // Go in the characterDirection
    if (!letterDirection)
    {
        // Get the characters behind the coords
        int intIndex = coord2 - 1;
        while (intIndex >= 0 && this->getTile(coord1, intIndex)->letter != 0)
        {
            // This is inefficient, but it ensures that the tiles will be in the correct order
            returnValue.insert(returnValue.begin(), this->getTile(coord1, intIndex));
            intIndex--;
        }

        // Get the character(s) at, and in front the coords
        intIndex = coord2;
        while (intIndex <= BOARD_SIZE && this->getTile(coord1, intIndex)->letter != 0)
        {
            // This is inefficient, but it ensures that the tiles will be in the correct order
            returnValue.push_back(this->getTile(coord1, intIndex));
            intIndex++;
        }
    }
    // Go in the integerDirection
    else
    {
        // Get the characters behind the coords
        int charIndex = coord1 - 1;
        while (charIndex >= 65 && this->getTile(charIndex, coord2)->letter != 0)
        {
            // This is inefficient, but it ensures that the tiles will be in the correct order
            returnValue.insert(returnValue.begin(), this->getTile(charIndex, coord2));
            charIndex--;
        }

        // Get the character(s) at, and in front the coords
        charIndex = coord1;
        while (charIndex <= 65 + BOARD_SIZE && this->getTile(charIndex, coord2)->letter != 0)
        {
            // This is inefficient, but it ensures that the tiles will be in the correct order
            returnValue.push_back(this->getTile(charIndex, coord2));
            charIndex++;
        }
    }

    return returnValue;
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

Board::Board(std::string constructionString)
{
    this->board = std::vector<std::vector<std::shared_ptr<Tile>>>();

    std::vector<std::string> vectorStrings = splitString(constructionString, '\n');

    // Iterate over the actual board size
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        this->board.push_back(std::vector<std::shared_ptr<Tile>>());

        for (int j = 0; j < BOARD_SIZE; j++)
        {
            this->board[i].push_back(std::make_shared<Tile>(char(0)));

            char tileLetter = vectorStrings[i + 2][(4 * j) + 4];

            if (!isalpha(tileLetter))
            {
                this->setTile(i + 65, j, std::make_shared<Tile>());
            }
            else
            {
                this->setTile(i + 65, j, std::make_shared<Tile>(tileLetter));
            }
        }
    }
}