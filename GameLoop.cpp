#include "GameLoop.h"
#include <iostream>
#include <fstream>
#include "userInput.h"
#include <algorithm>

#define NUM_PLAYERS 2

// Splits a string, using a specified character as the delimiter between substrings
// Utility function used for parsing user input
std::vector<std::string> splitString(std::string inputString, char splittingChar)
{
    std::vector<std::string> returnValue;
    int processedIndex = 0;

    bool terminate = false;
    while (!terminate)
    {
        int splittingCharIndex = inputString.find(splittingChar, processedIndex + 1);
        std::string word = inputString.substr(processedIndex, splittingCharIndex - processedIndex);
        returnValue.push_back(word);
        if (splittingCharIndex == -1)
        {
            terminate = true;
        }
        processedIndex = splittingCharIndex + 1;
    }

    return returnValue;
}

GameLoop::GameLoop()
{
    std::cout << "Starting a new game" << std::endl;
    std::cout << std::endl;

    currentPlayerIndex = 0;

    for (int playerIndex = 0; playerIndex < NUM_PLAYERS; playerIndex++)
    {
        std::cout << "Enter a name for player " << playerIndex + 1 << " (uppercase characters only)" << std::endl;

        std::string playerName = userInput();

        bool isPlayerNameValid = false;

        while (!isPlayerNameValid)
        {
            isPlayerNameValid = true;
            if (playerName.length() <= 0)
            {
                isPlayerNameValid = false;
            }
            else
            {
                for (long unsigned int i = 0; i < playerName.length(); i++)
                {
                    char charInName = playerName.at(i);
                    if (!isupper(charInName))
                    {
                        isPlayerNameValid = false;
                    }
                }
            }
            if (!isPlayerNameValid)
            {
                std::cout << "The name you entered was not in uppercase (or you didn't enter anything!)." << std::endl
                          << "Please try again." << std::endl;
                playerName = userInput();
            }
        }

        this->players.push_back(std::make_shared<Player>(playerName));
        std::cout << std::endl;
    }

    std::cout << "Let's Play!" << std::endl
              << std::endl;

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

    for (std::shared_ptr<Player> player : this->players)
    {
        for (int i = 0; i < 7; i++)
        {
            std::shared_ptr<Tile> tile = this->bag.drawTile();
            player->drawTile(tile);
        }
    }
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
        std::shared_ptr<Player> currentPlayer = this->players[currentPlayerIndex];

        // Output prompt
        std::cout << currentPlayer->getName() << ", it's your turn" << std::endl;
        for (int printingIndex = 0; printingIndex < NUM_PLAYERS; printingIndex++)
        {
            std::cout << "Score for " << this->players[printingIndex]->getName() << ": " << this->players[printingIndex]->getScore() << std::endl;
        }
        std::cout << this->board.convertToString() << std::endl;
        std::cout << "Your hand is" << std::endl;
        currentPlayer->printHand();

        // Store the validness of the input into a seperate variable,
        // since all code paths have the possibility to be incorrect.
        bool validInput = false;
        bool repeatTurn = false;

        while ((!validInput) || repeatTurn)
        {
            std::vector<std::string> command = splitString(userInput(), ' ');

            std::string commandType = command[0];
            repeatTurn = false;

            if (commandType == "place")
            {
                validInput = this->placeTile(command, currentPlayer);
            }
            else if (commandType == "replace")
            {
                validInput = this->replaceTile(command, currentPlayer);
            }
            else if (commandType == "pass")
            {
                validInput = true;
                // Passing is just doing nothing, so we do nothing
                // We will eventually need to track when a player passes,
                // since the game ends if a player passes twice
            }
            else if (commandType == "save")
            {
                validInput = this->saveGame(command);
                if (validInput)
                {
                    std::cout << std::endl
                              << "Game successfully saved"
                              << std::endl
                              << std::endl;
                }
                repeatTurn = true;
            }
            else
            {
                validInput = false;
            }

            if (!validInput)
            {
                std::cout << "Please enter a valid place, replace, or pass command" << std::endl;
            }
            else if (!repeatTurn)
            {
                currentPlayerIndex += 1;
            }
        }
    }
}

// Another utility function to encapsulate input processing
// This exists to reduce code duplication, since this action
// must be performed in several logical places
bool GameLoop::processPlacementInput(std::vector<std::string> initialInput, std::vector<PlacedTile> &placedTiles, bool &done)
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
        else if (!isalpha(initialInput[3][0]) || !isupper(initialInput[3][0]) || !isdigit(initialInput[3][1]))
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
            int coord2 = std::stoi(initialInput[3].substr(1));
            PlacedTile tupleToInsert = {letterToPlace, coord1, coord2 - 1};
            placedTiles.push_back(tupleToInsert);
        }
    }

    return isSuccessful;
}

bool sortingTileCharComparison(PlacedTile i, PlacedTile j)
{
    return std::get<1>(i) < std::get<1>(j);
}

bool sortingTileIntComparison(PlacedTile i, PlacedTile j)
{
    return std::get<2>(i) < std::get<2>(j);
}

bool GameLoop::placeTile(std::vector<std::string> initialInput, std::shared_ptr<Player> currentPlayer)
{
    bool isSuccessful = true;
    bool isDone = false;

    // Tuple to store placed tiles for post-validation.
    // Tuples are TileLetter, coord1, coord2
    std::vector<PlacedTile> placedTiles;

    isSuccessful = this->processPlacementInput(initialInput, placedTiles, isDone);

    // If the first command is invalid, return to the main turn loop
    while (isSuccessful && !isDone)
    {
        // Once we have entered the placement loop, if an invalid command is entered,
        // ask for a valid one and do not return to the main loop until done
        std::vector<std::string> initialInput = splitString(userInput(), ' ');
        bool isValidInput = this->processPlacementInput(initialInput, placedTiles, isDone);
        if (!isValidInput)
        {
            std::cout << "Please enter a valid placement command" << std::endl;
        }
    }

    // If tiles have been entered successfully, check that the combination is valid (straight lines only, no gaps between letters)
    // These variables are placed outside the block so that they can be used later on
    bool allAreSameLetter = true;
    bool allAreSameNumber = true;
    if (isSuccessful)
    {
        // Determine whether the tiles are in a line.
        for (int i = 0; (std::size_t)i < placedTiles.size() && allAreSameLetter; i++)
        {
            allAreSameLetter = std::get<1>(placedTiles[i]) == std::get<1>(placedTiles[0]);
        }

        for (int i = 0; (std::size_t)i < placedTiles.size() && allAreSameNumber; i++)
        {
            allAreSameNumber = std::get<2>(placedTiles[i]) == std::get<2>(placedTiles[0]);
        }

        // If the tiles are in a line, check there are no gaps between the tiles
        if (allAreSameLetter)
        {
            // Sort the placedTiles
            std::sort(placedTiles.begin(), placedTiles.begin() + placedTiles.size(), sortingTileIntComparison);

            int placedTilesIndex = 0;
            for (int i = std::get<2>(placedTiles[0]); i < std::get<2>(placedTiles[placedTiles.size() - 1]) && isSuccessful; i++)
            {
                // If there is a space unaccounted for by the tiles we place, check there is a tile there on the board
                if (std::get<2>(placedTiles[placedTilesIndex]) != i)
                {
                    // If there is no tile there on the board, the placement is invalid
                    if (this->board.getTile(std::get<1>(placedTiles[0]), i)->letter == 0)
                    {
                        isSuccessful = false;
                    }
                }
                else
                {
                    placedTilesIndex++;
                }
            }
        }
        else if (allAreSameNumber)
        {
            // Sort the placedTiles
            std::sort(placedTiles.begin(), placedTiles.begin() + placedTiles.size(), sortingTileCharComparison);

            int placedTilesIndex = 0;
            for (int i = std::get<1>(placedTiles[0]); i < std::get<1>(placedTiles[placedTiles.size() - 1]) && isSuccessful; i++)
            {
                // If there is a space unaccounted for by the tiles we place, check there is a tile there on the board
                if (std::get<1>(placedTiles[placedTilesIndex]) != i)
                {
                    // If there is no tile there on the board, the placement is invalid
                    if (this->board.getTile(i, std::get<2>(placedTiles[0]))->letter == 0)
                    {
                        isSuccessful = false;
                    }
                }
                else
                {
                    placedTilesIndex++;
                }
            }
        }
        // Or if they aren't in a line at all, set successful to false
        else
        {
            isSuccessful = false;
        }
    }

    // Check the player has enough tiles to place everything
    for (char i = 'A'; i <= 'Z' && isSuccessful; i++)
    {
        int total = 0;
        for (PlacedTile tileToBePlaced : placedTiles)
        {
            if (std::get<0>(tileToBePlaced) == i)
            {
                total++;
            }
        }

        isSuccessful = currentPlayer->getHand()->getNumberOfTilesWithLetter(i) >= total;
    }

    if (isSuccessful)
    {
        std::cout << "potato" << std::endl;
        std::tuple<char, int> startTuple = {std::get<1>(placedTiles[0]), std::get<2>(placedTiles[0])};
        std::tuple<char, int> endTuple = {std::get<1>(placedTiles[placedTiles.size() - 1]), std::get<2>(placedTiles[placedTiles.size() - 1])};

        isSuccessful = isAdjacent(startTuple, endTuple);

    }
    

    if (isSuccessful)
    {
        for (PlacedTile tileToBePlaced : placedTiles)
        {
            // Place the tile on the board
            std::shared_ptr<Tile> tile = currentPlayer->takeTile(std::get<0>(tileToBePlaced));
            // activePlayer->addScore(tile->getValue());
            this->board.setTile(std::get<1>(tileToBePlaced), std::get<2>(tileToBePlaced), tile);

            // Repopulate the user's hand
            std::shared_ptr<Tile> newTile = this->bag.drawTile();
            currentPlayer->drawTile(newTile);

            // Calculate the points for any perpendicular words
            std::vector<std::shared_ptr<Tile>> possibleFormedWord = this->board.getWord(std::get<1>(tileToBePlaced), std::get<2>(tileToBePlaced), allAreSameLetter);
            // If the "word" length is 1, it's not a formed word
            if (possibleFormedWord.size() > 1)
            {
                for (std::shared_ptr<Tile> wordTile : possibleFormedWord)
                {
                    currentPlayer->addScore(wordTile->getValue());
                }
            }
        }

        // Add the score for formed word
        std::vector<std::shared_ptr<Tile>> formedWord = this->board.getWord(std::get<1>(placedTiles[0]), std::get<2>(placedTiles[0]), !allAreSameLetter);
        // If the "word" length is 1, it's not a formed word
        if (formedWord.size() > 1)
        {
            for (std::shared_ptr<Tile> wordTile : formedWord)
            {
                currentPlayer->addScore(wordTile->getValue());
            }
        }
    }

    return isSuccessful;
}

bool GameLoop::replaceTile(std::vector<std::string> initialCommand, std::shared_ptr<Player> currentPlayer)
{
    bool isSuccessful = true;
    Letter letterToReplace;

    // All replace commands must be two words long
    if (initialCommand.size() != 2)
    {
        isSuccessful = false;
    }
    else
    {
        letterToReplace = initialCommand[1][0];

        // The second word must be a single character
        if (initialCommand[1].size() != 1 || !isupper(letterToReplace))
        {
            isSuccessful = false;
        }
        else
        {
            // Find and replace the tile with the given letter.
            std::shared_ptr<Tile> tileToReplace = currentPlayer->takeTile(letterToReplace);

            // If no tile has the given letter, then the operation is unsuccessful.
            // Otherwise, complete the operation.
            if (tileToReplace == nullptr)
            {
                isSuccessful = false;
            }
            else
            {
                // Move the tile back to the bag.
                this->bag.addTile(tileToReplace);
                currentPlayer->drawTile(this->bag.drawTile());
            }
        }
    }

    return isSuccessful;
}

bool GameLoop::saveGame(std::vector<std::string> initialCommand)
{
    std::string filename = initialCommand[1];
    bool isSuccessful = false;
    try
    {
        std::ofstream outfile;

        outfile.open("saves/" + filename + ".txt");

        for (int i = 0; i < static_cast<int>(players.size()); i++)
        {
            std::shared_ptr<Player> player = players.at(i);
            outfile << std::string(*player) << std::endl;
        }

        outfile << board.convertToString();

        outfile << std::string(bag) << std::endl;

        std::shared_ptr<Player> currentPlayer = this->players[currentPlayerIndex];

        outfile << currentPlayer->getName();

        if (outfile.bad())
        {
            isSuccessful = false;
        }
        else
        {
            isSuccessful = true;
        }
    }
    catch (const std::exception &e)
    {
        isSuccessful = false;
    }

    return isSuccessful;
}

bool GameLoop::isAdjacent(std::tuple<char, int> startPos, std::tuple<char, int> endPos)
{
    //Need to take perameter of position of all placed tiles.
    //Then check all tiles directly adjecent to placed tiles.
    //If any adjacent tiles have tiles present, if they do return true.
    //Else if first turn of the game make sure word is placed center of board.

    //TODO: If board is empty, make sure at least one tile is on the center of the board.
    bool validWord = false;

    char startChar = std::get<0>(startPos);
    int startInt = std::get<1>(startPos);
    char endChar = std::get<0>(endPos);
    int endInt = std::get<1>(endPos);
    std::vector<std::tuple<char, int>> toCheck;
    // If the center tile is empty, center tile must be used.
    
    
    

    if (startChar == endChar)
    {
        std::cout << "samechar" << std::endl;
        if (this->board.getTile('H', 8) == 0 && startChar == 'H' && startInt <= 8 && endInt >= 8){

            std::cout << "samechar center" << std::endl;
            std::tuple<char, int> tupleToInsert = {startChar, startInt - 1};
            toCheck.push_back(tupleToInsert);

            tupleToInsert = {startChar, endInt + 1};
            toCheck.push_back(tupleToInsert);

            for (int i = startInt; i <= endInt; i++)
            {
                tupleToInsert = {startChar - 1, i};
                toCheck.push_back(tupleToInsert);
                tupleToInsert = {startChar + 1, i};
                toCheck.push_back(tupleToInsert);
            }
        }
        
    }else{
        std::cout << "sameint" << std::endl;
        if (this->board.getTile('H', 8) == 0 && startInt == 8 && startChar <= 'H' && endChar >= 'H'){
            std::cout << "sameint center" << std::endl;
            std::tuple<char, int> tupleToInsert = {startChar - 1, startInt};
            toCheck.push_back(tupleToInsert);

            tupleToInsert = {startChar + 1, endInt};
            toCheck.push_back(tupleToInsert);

            for (int i = startChar; i <= endChar; i++)
            {
                tupleToInsert = {i, startInt - 1};
                toCheck.push_back(tupleToInsert);
                tupleToInsert = {i, startInt + 1};
                toCheck.push_back(tupleToInsert);
            }
        }
    }

    for (std::tuple<char, int> tileToCheck : toCheck)
    {
        if (this->board.getTile(std::get<0>(tileToCheck), std::get<1>(tileToCheck)) != 0)
        {
            validWord = true;
        }
        
    }
    
    return validWord;
    
}