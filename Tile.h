
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <iostream>

// Define a Letter type
typedef char Letter;

// Define a Value type
typedef int Value;

class Tile
{
public:
   Tile();
   Tile(Letter letter);
   Letter letter;
   int getValue();

   operator std::string();
};

#endif // ASSIGN2_TILE_H
