
#include "Hand.h"
#include "GameLoop.h"
#include "LinkedList.h"
#include "utils.h"
#include "eof_exception.h"

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
      try
      {
         // Print Menu
         std::cout
             << "Menu" << std::endl
             << "----" << std::endl
             << "1. New Game" << std::endl
             << "2. Load Game" << std::endl
             << "3. Credits (Show student information)" << std::endl
             << "4. Quit" << std::endl
             << "5. DEBUG: Player + Hand Test" << std::endl;

         // Get user input
         std::string rawUserInput;

         // Prevents the weird repeating buffer issue
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
            // Declaring a pointer allows us to create a memory space outside
            // the try block, without executing the default constructor
            std::shared_ptr<GameLoop> game;
            // Load a game
            std::cout << "Enter the filename from which load a game" << std::endl;
            std::string filename = userInput();
            bool successfulLoad = true;
            try
            {
               game = std::make_shared<GameLoop>(filename);
            }
            // Use the
            catch (std::exception &unused)
            {
               std::cout << "That savefile is invalid. Please select a valid savefile" << std::endl;
               successfulLoad = false;
            }

            if (successfulLoad)
            {
               std::cout << "Starting mainLoop" << std::endl;
               game->mainLoop();
            }
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
         else if (intUserInput == 5)
         {
            std::cout << "Running List, Player, Hand test..." << std::endl;

            std::shared_ptr<Player> player = std::make_shared<Player>("Potato");
            std::shared_ptr<Hand> hand = player->getHand();

            std::cout << "// Test printing an empty hand //" << std::endl;
            hand->getTilesInHand()->print();
            std::cout << std::endl;

            std::cout << "// Test inserting tiles and printing out Player //" << std::endl;
            std::shared_ptr<Tile> newTile = std::make_shared<Tile>('A');
            std::shared_ptr<Tile> newTile2 = std::make_shared<Tile>('A');
            std::shared_ptr<Tile> newTile3 = std::make_shared<Tile>('C');
            player->drawTile(newTile);
            player->drawTile(newTile2);
            player->drawTile(newTile3);

            std::cout << std::string(*player) << std::endl;
            std::cout << std::endl;

            std::cout << "// Test getting frequency of letters in Hand... //" << std::endl;
            std::cout << "A: " << hand->getNumberOfTilesWithLetter('A') << std::endl;
            std::cout << "B: " << hand->getNumberOfTilesWithLetter('B') << std::endl;
            std::cout << "C: " << hand->getNumberOfTilesWithLetter('C') << std::endl;

            std::cout << "// Test loading... //" << std::endl;
            GameLoop gameLoop = GameLoop("test");

            std::cout << std::endl
                      << "Tests complete! Terminating...";
            terminate = true;
         }
         else
         {
            std::cout << "Invalid input, please input a valid number between 1-4" << std::endl;
         }

         std::cout << std::endl;
      }
      // If the user ever enters an EOF character, execution will jump back to here and terminate
      catch (eof_exception &unused)
      {
         terminate = true;
      }
   }

   return EXIT_SUCCESS;
}
