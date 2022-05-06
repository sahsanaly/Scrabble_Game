#include "GameLoop.h"
#include <iostream>
#include "userInput.h"

#define NUM_PLAYERS 2

// Splits a string, using a specified character as the delimiter between substrings
// Utility function used for parsing user input
std::vector<std::string> splitString(std::string inputString, char splittingChar)
{
    std::vector<std::string> returnValue;
    int processedIndex = 0;

    while ((std::size_t)processedIndex < inputString.length())
    {
        int splittingCharIndex = inputString.find(splittingChar, processedIndex);
        returnValue.push_back(inputString.substr(processedIndex, splittingCharIndex));
        processedIndex = splittingCharIndex;
    }

    return returnValue;
}

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

            std::vector<std::string> command = splitString(userInput(), ' ');

            // Store the validness of the input into a seperate variable,
            // since all code paths have the possibility to be incorrect.
            bool validInput;

            if (command[0] == "place")
            {
                validInput = this->placeTile(command);
            }
            else if (command[0] == "replace")
            {
                validInput = this->replaceTile(command);
            }
            else if (command[0] == "pass")
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

// Another utility function to encapsulate input processing
// This exists to reduce code duplication, since this action
// must be performed in several logical places
bool GameLoop::processPlacementInput(std::vector<std::string> initialInput, std::vector<std::tuple<Letter, char, int>> &placedTiles, bool &done)
{
    bool isSuccessful = true;
    // All place operation must have 4 words.
    // Therefore, if there is not, it is invalid.
    if (initialInput.size() != 4)
    {
        // The only exception to this is the "place Done" command.
        if (initialInput.size() == 2 && initialInput[0] == "place" && initialInput[1] == "Done")
        {
            done = true;
        }
        else
        {
            isSuccessful = false;
        }
    }
    else
    {
        // The first word must be "place".
        if (initialInput[0] != "place")
        {
            isSuccessful = false;
        }
        // The third word must be "at"
        else if (initialInput[2] != "at")
        {
            isSuccessful = false;
        }
        // The second word must be 1 character long
        else if (initialInput[1].size() != 1)
        {
            isSuccessful = false;
        }
        // The second word must consist of a single uppercase letter
        else if (!isalpha(initialInput[1][0]) || !isupper(initialInput[1][0]))
        {
            isSuccessful = false;
        }
        // The fourth word must be either 2 or 3 characters long
        else if (initialInput[3].size() != 2 && initialInput[3].size() != 3)
        {
            isSuccessful = false;
        }
        // The fourth word's first character must be an uppercase letter, while the second character must be a number
        else if (!isalpha(initialInput[1][0]) || !isupper(initialInput[1][0]) || !isdigit(initialInput[1][1]))
        {
            isSuccessful = false;
        }
        // If the fourth word has a third character, it must be a number
        else if (initialInput[3].size() == 3)
        {
            if (!isdigit(initialInput[1][2]))
            {
                isSuccessful = false;
            }
        }
        // The input is valid. Now to parse and process
        else
        {
            char letterToPlace = initialInput[1][0];
            char coord1 = initialInput[3][0];
            char coord2 = std::stoi(initialInput[3].substr(1));
            std::tuple<Letter, char, int> tupleToInsert = {letterToPlace, coord1, coord2};
            placedTiles.push_back(tupleToInsert);
        }
    }

    return isSuccessful;
}

bool GameLoop::placeTile(std::vector<std::string> initialInput)
{
    bool isSuccessful = true;
    bool isDone = false;

    // Tuple to store placed tiles for post-validation.
    // Tuples are TileLetter, coord1, coord2
    std::vector<std::tuple<Letter, char, int>> placedTiles;

    isSuccessful = this->processPlacementInput(initialInput, placedTiles, isDone);

    // If the first command is invalid, return to the main turn loop
    while (isSuccessful && !isDone)
    {
        // Once we have entered the placement loop, if an invalid command is entered,
        // ask for a valid one and do not return to the main loop until done
        bool isValidInput = this->processPlacementInput(initialInput, placedTiles, isDone);
        if (!isValidInput)
        {
            std::cout << "Please enter a valid placement command" << std::endl;
        }
    }

    // If tiles have been entered successfully, check that the combination is valid (straight lines only)
    if (isSuccessful)
    {
        bool allAreSameLetter = true;
        for (int i = 0; (std::size_t)i < placedTiles.size() && allAreSameLetter; i++)
        {
            allAreSameLetter = std::get<1>(placedTiles[i]) == std::get<1>(placedTiles[0]);
        }

        bool allAreSameNumber = true;
        for (int i = 0; (std::size_t)i < placedTiles.size() && allAreSameNumber; i++)
        {
            allAreSameNumber = std::get<2>(placedTiles[i]) == std::get<2>(placedTiles[0]);
        }

        // All tiles must be on the same line
        isSuccessful = allAreSameLetter || allAreSameNumber;
    }

    // TODO: Check that the tiles are placed in valid spaces (no blank spaces between them)
    // TODO: Place the tiles on the board if valid

    return isSuccessful;
}