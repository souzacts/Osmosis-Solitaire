#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <fstream>


#include "card.h"
#include "stockpile.h"
#include "foundation.h"

const int SIZE = 4;
const std::set<std::string> tags {"1", "Q", "A", "Z", "2", "W", "S", "X"};//used to check command validity in play()

class game
{
    public:
        //Constr.
            game();
            ~game();
        //Getters
            bool getWon() {return won;};
            bool getStandStill() {return standStill;};

        //Static Functions
            static std::string gameMenu(std::string);
            static std::string read(std::string);

        //Functionality
            void buildAndShuffle();
            void buildLayout();
            std::string printTable() const;

            void play();
            void peel();
            void redeal();

            void checkState();

            friend std::ostream& operator<<(std::ostream&, const game&);

    private:

        std::vector<std::vector<card>> d;//for deck and waste pile
        std::vector<stockpile> s;
        std::vector<foundation*> f;
        bool won;
        bool standStill;
};

//Aid Functions
std::string colorfy(const card& c);
void toUpper(std::string& x);
std::string inGameHelp(std::string);

#endif