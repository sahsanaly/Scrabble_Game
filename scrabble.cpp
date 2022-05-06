#include "LinkedList.h"
#include "Hand.h"

#include <iostream>

#define EXIT_SUCCESS 0

// I typed out the values, not really sure where to put them though. Leaving them here till we have a use for them.
/* // Define the letter values
    std::map<Letter, int> letter_values = {
        {'A', 1},
        {'E', 1},
        {'I', 1},
        {'O', 1},
        {'U', 1},
        {'L', 1},
        {'N', 1},
        {'S', 1},
        {'T', 1},
        {'R', 1},
        {'D', 2},
        {'G', 2},
        {'B', 3},
        {'C', 3},
        {'M', 3},
        {'P', 3},
        {'F', 4},
        {'H', 4},
        {'V', 4},
        {'W', 4},
        {'Y', 4},
        {'K', 5},
        {'J', 8},
        {'X', 8},
        {'Q', 10},
        {'Z', 10},
    };
    */

int main(void)
{
   LinkedList *list = new LinkedList();
   delete list;

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
      int userInput = 0;
      try
      {
         std::cin >> rawUserInput;
         userInput = std::stoi(rawUserInput);
      }
      catch (std::invalid_argument &unused)
      {
         // Nothing needs to be done, userInput defaults to 0, which will trigger the "invalid input" condition
      }
      std::cout << std::endl;

      if (userInput == 1)
      {
         // Create a new game
         std::cout << "Not yet implemented!" << std::endl;
      }
      else if (userInput == 2)
      {
         // Load a game
         std::cout << "Not yet implemented!" << std::endl;
      }
      else if (userInput == 3)
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
      else if (userInput == 4)
      {
         // Quit
         std::cout << "Goodbye" << std::endl;
         terminate = true;
      }
      else if (userInput == 5)
      {
         std::cout << "Running Hand test..." << std::endl;
         std::shared_ptr<Hand> testHand = std::make_shared<Hand>();

         std::shared_ptr<Tile> newTile = std::make_shared<Tile>('a');
         
         testHand->addTile(newTile);
         std::cout << testHand->getAsString() << std::endl;

         // std::cout << newTile->letter << std::endl;
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
