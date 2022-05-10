#include <iostream>
#include <vector>
#include "utils.h"

std::string userInput()
{
    std::cout << "> ";
    std::string returnValue;
    std::getline(std::cin, returnValue);
    return returnValue;
}

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