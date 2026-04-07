/* Program name: main.cpp
* Author: Caio Souza
* Date last updated: 10/11/2023
* Purpose: Final Project -> Write an Osmosis card game using CSCI 201 concepts
*/
#include <iostream>
#include <limits>
#include <vector>

#include <iomanip>

#include "card.h"
#include "stockpile.h"
#include "foundation.h"
#include "game.h"


void mainMenu();
int validChoice();
void resetStream();

int main()
{
    std::string playAgain = "Y";

    while(playAgain[0] == 'Y')
    {
        mainMenu();

        game g;
        std::cout << g << std::endl;

            while (!g.getWon() && !g.getStandStill())//if won or standstill is changed, break out
            {
                try
                {
                    std::cout << Y << std::setw(120) << std::setfill('-') << W << std::endl;
                    std::cout << "\nWhat do you do?" << std::endl;//$
                    g.play();
                    g.checkState();//checks for available moves
                }
                catch(std::invalid_argument e)//catch for invalid moves
                {
                    std::cerr << "\n\n" + R + "!!!WARNING!!! " + Y + "Invalid Move -> " + W + e.what() /* << R + " !!!WARNING!!! " + W */<< std::endl;
                }
                catch(std::string strThrow)//catch for in game help and early quit
                {
                    if (strThrow == "QUIT")
                    {    
                        std::cout << R << "Quiting this game now." << W << std::endl;
                        break;
                    }
                    std::cout << "\n\n" + strThrow << std::endl;
                }
                
                std::cout << g << std::endl;
        
                //check win/loss condition
                if(g.getStandStill())
                    std::cout << R +"Oh bully, you lose.... There are no more valid moves." + W << std::endl;
            
                else if(g.getWon())
                    std::cout << R +"Oh, sweet sweet victory, YOU WON!" + W << std::endl;
            }

            std::cout << "Well, that was fun. Wanna play again? (y/n)" << std::endl;
            std::getline(std::cin, playAgain);
            toUpper(playAgain);
    }

    std::cout << "OK, bye o/" << std::endl;

    return 0;
}

void resetStream()
{
    std::cout << "Invalid entry.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

 
int validChoice()
{
    std::cout << "\nPick an option?";
    int choice;
    std::cin >> choice;

    while (!std::cin || choice < 1 || choice > 5)
    {
        if (!std::cin)
            resetStream();
        else
            std::cout << "Chose from the menu options, pick any number you see in the list.\n";
    
        std::cout << "\nPick an option?";
        std::cin >> choice;
    }
    return choice;
}

void mainMenu()
{   
    std::cout << "Hi, welcome to Osmosis!\n" << std::endl;

    std::string menu = "1 - Let's play!!!\n"
                       "2 - What in the flying-donut is Osmosis?\n"
                       "3 - How to play it?\n"
                       "4 - About this project.\n"
                       "5 - Quit.\n";

    std::cout << menu << std::endl;
    int choice = validChoice();

    while (choice > 1 && choice <= 5)
    {
        switch (choice)
        {
            case 2: std::cout << Y << game::read("osmosis") << W << std::endl; break;
            case 3: std::cout << Y << game::read("instructions") << W << std::endl; break;
            case 4: std::cout << Y << game::read("about") << W << std::endl; break;
            case 5: std::cout << R << "Quitting now" << W; exit(1);
        }

        std::cout << menu << std::endl;
        choice = validChoice();

    }
    resetStream();//this clears anything resting in std::cin, it was causing problems internally
} 