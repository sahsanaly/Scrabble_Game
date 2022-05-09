#ifndef ASSIGN2_GAMELOOP_H
#define ASSIGN2_GAMELOOP_H

#include <string>
#include <memory>
#include "Player.h"
#include "Board.h"
#include "Bag.h"

typedef std::tuple<Letter, char, int> PlacedTile;

class GameLoop
{
public:
    // Default loader
    GameLoop();
    // Save game loader
    GameLoop(std::string saveFileName);

    ~GameLoop();
    // Main game loop.
    // Loops until either:
    //      A player wins
    //      The players quit early
    //      The game is saved to a file
    void mainLoop();

private:
    // Making these pointers allows them to be initialised in the constructor, rather than before.
    // If there is a better solution, it should be taken.
    std::vector<std::shared_ptr<Player>> players;

    Board board;
    Bag bag;

    // Parse the inital command
    // Get additional commands until place done is received
    // Check the placed tiles to ensure they meet placing rules
    // Put tiles onto the board if they meet placing rules
    // If the tiles breach placing rules, return false, otherwise return true
    bool placeTile(std::vector<std::string> initialCommand, std::shared_ptr<Player> activePlayer);

    // Since some of the logic in placeTile needs to be performed in several
    // logical places, we split some of the code into a seperate function to
    // prevent code duplication
    bool processPlacementInput(std::vector<std::string> inputString, std::vector<std::tuple<Letter, char, int>> &placedTiles, bool &done);

    // Check if the tile indicated is valid
    // If yes, replace it and return true
    // If no, return false
    bool replaceTile(std::vector<std::string> initialCommand, std::shared_ptr<Player> activePlayer);

    // Save the game to indicated save file
    bool saveGame(std::vector<std::string> initialCommand);
};

#endif