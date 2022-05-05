#ifndef ASSIGN2_USERINPUT_H
#define ASSIGN2_USERINPUT_H

#include <iostream>
#include "userInput.h"

std::string userInput()
{
    std::cout << "> ";
    std::string returnValue;
    std::cin >> returnValue;
    return returnValue;
}

#endif