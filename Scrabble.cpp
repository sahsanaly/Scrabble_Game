#include "Scrabble.h"
#include <iostream>
#include "userInput.h"

Scrabble::Scrabble()
{
    std::cout << "Starting a new game" << std::endl;
    std::cout << std::endl;

    // TODO: Still need to check playername is valid
    std::cout << "Enter a name for player 1 (uppercase characters only)" << std::endl;
    std::string player1Name = userInput();
    this->player1 = std::make_shared<Player>(player1Name);
    std::cout << std::endl;

    // TODO: Still need to check playername is valid
    std::cout << "Enter a name for player 2 (uppercase characters only)" << std::endl;
    std::string player2Name = userInput();
    this->player2 = std::make_shared<Player>(player2Name);
    std::cout << std::endl;

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

Scrabble::~Scrabble()
{
    this->player1 = nullptr;
    this->player2 = nullptr;
}

void Scrabble::mainLoop()
{
}