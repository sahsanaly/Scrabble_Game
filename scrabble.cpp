
#include "GameLoop.h"
#include "LinkedList.h"
#include "userInput.h"

#include <iostream>

#define EXIT_SUCCESS 0

int main(void)
{
   // Print banner
   std::cout << "Welcome to Scrabble!" << std::endl;
   std::cout << "-------------------" << std::endl;

   bool terminate = false;

   // Main loop
   while (!terminate)
   {
      // Print Menu
      std::cout
          << "Menu" << std::endl
          << "----" << std::endl
          << "1. New Game" << std::endl
          << "2. Load Game" << std::endl
          << "3. Credits (Show student information)" << std::endl
          << "4. Quit" << std::endl;

      // Get user input
      std::string rawUserInput;

      // Prevents the wierd repeating buffer issue
      int intUserInput = 0;
      try
      {
         rawUserInput = userInput();
         intUserInput = std::stoi(rawUserInput);
      }
      catch (std::invalid_argument &unused)
      {
         // Nothing needs to be done, userInput defaults to 0, which will trigger the "invalid input" condition
      }
      std::cout << std::endl;

      if (intUserInput == 1)
      {
         GameLoop game;
         game.mainLoop();
      }
      else if (intUserInput == 2)
      {
         // Load a game
         std::cout << "Not yet implemented!" << std::endl;
      }
      else if (intUserInput == 3)
      {
         // Print credits
         std::cout
             << "--------------------------------------" << std::endl
             << "Name: Syed Ali" << std::endl
             << "Student ID: s3736294" << std::endl
             << "Email: s3736294@student.rmit.edu.au" << std::endl
             << std::endl
             << "Name: Mitchell Reid" << std::endl
             << "Student ID: s3901557" << std::endl
             << "Email: s3901557@student.rmit.edu.au" << std::endl
             << std::endl
             << "Name: Tsz Him Matthew Cheung" << std::endl
             << "Student ID: s3902085" << std::endl
             << "Email: s3902085@student.rmit.edu.au" << std::endl
             << std::endl
             << "Name: Spencer Morrison" << std::endl
             << "Student ID: s3906025" << std::endl
             << "Email: s3906025@student.rmit.edu.au" << std::endl
             << "--------------------------------------" << std::endl;
      }
      else if (intUserInput == 4)
      {
         // Quit
         std::cout << "Goodbye" << std::endl;
         terminate = true;
      }
      else
      {
         std::cout << "Invalid input, please input a valid number between 1-4" << std::endl;
      }

      std::cout << std::endl;
   }

   return EXIT_SUCCESS;
}
