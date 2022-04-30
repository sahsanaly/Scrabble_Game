
#include "Tile.h"

Tile::Tile()
{
    // Store the letter and value
    this->letter = ' ';
    this->value = 0;
}

Tile::Tile(Letter letter, int value)
{
    // Store the letter and value
    this->letter = letter;
    this->value = value;
}

// Empty... for now?
