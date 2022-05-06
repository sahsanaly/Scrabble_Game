#include "GameLoop.h"
#include <iostream>
#include "userInput.h"

#define NUM_PLAYERS 2

// std::vector<std::string> splitString(std::string inputString, char splittingChar)
// {
// }

GameLoop::GameLoop()
{
    std::cout << "Starting a new game" << std::endl;
    std::cout << std::endl;

    for (int playerIndex = 0; playerIndex < NUM_PLAYERS; playerIndex++)
    {
        // TODO: Still need to check playername is valid
        std::cout << "Enter a name for player " << playerIndex + 1 << " (uppercase characters only)" << std::endl;
        std::string player1Name = userInput();
        this->players.push_back(std::make_shared<Player>(player1Name));
        std::cout << std::endl;
    }

    std::cout << "Let's Play!" << std::endl;

    // Set up the bag
    //                  A, B, C, D,  E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
    const int quantities[] = {9, 2, 2, 4, 12, 2, 3, 2, 9, 1, 1, 4, 2, 6, 8, 2, 1, 6, 4, 6, 4, 2, 2, 1, 2, 1};

    // This magical code uses int->char conversions to create the correct number of each tile
    for (int charIndex = 0; charIndex < 26; charIndex++)
    {
        for (int i = 0; i < quantities[charIndex]; i++)
        {
            // 65 is the ascii value of A. This generates the relevant character based on charIndex
            bag.addTile(std::make_shared<Tile>((Letter)65 + charIndex));
        }
    }

    bag.shuffle();
}

GameLoop::~GameLoop()
{
    this->players.clear();
}

void GameLoop::mainLoop()
{
    bool terminate = false;
    while (!terminate)
    {
        for (int playerIndex = 0; playerIndex < NUM_PLAYERS; playerIndex++)
        {
            std::shared_ptr<Player> activePlayer = this->players[playerIndex];

            std::string command = userInput();
            std::string commandKeyword = command.substr(0, command.find(' '));

            // Store the validness of the input into a seperate variable,
            // since all code paths have the possibility to be incorrect.
            bool validInput;

            if (commandKeyword == "place")
            {
                validInput = this->placeTile(command);
            }
            else if (commandKeyword == "replace")
            {
                validInput = this->replaceTile(command);
            }
            else if (commandKeyword == "pass")
            {
                validInput = true;
                // Passing is just doing nothing, so we do nothing
                // We will eventually need to track when a player passes,
                // since the game ends if a player passes twice
            }
            else
            {
                validInput = false;
            }

            if (!validInput)
            {
                std::cout << "Please enter a valid place, replace, or pass command" << std::endl;
            }
        }
    }
}

bool GameLoop::placeTile(std::string initialInput)
{
}