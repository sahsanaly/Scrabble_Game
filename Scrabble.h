#include <string>

class Player;
class Board;
class Bag;

class Scrabble
{
public:
    // Default loader
    Scrabble();
    // Save game loader
    Scrabble(std::string saveFileName);
    // Main game loop.
    // Loops until either:
    //      A player wins
    //      The players quit early
    //      The game is saved to a file
    void mainLoop();

private:
    Player player1;
    Player player2;
    Board board;
    Bag bag;

    // Parse the inital command
    // Get additional commands until place done is received
    // Check the placed tiles to ensure they meet placing rules
    // Put tiles onto the board if they meet placing rules
    // If the tiles breach placing rules, return false, otherwise return true
    bool placeTile(std::string initialCommand);

    // Check if the tile indicated is valid
    // If yes, replace it and return true
    // If no, return false
    bool replaceTile(std::string initialCommand);

    // Save the game to indicated save file
    bool saveGame(std::string initialCommand);
};