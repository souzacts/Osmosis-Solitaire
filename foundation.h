#ifndef FOUNDATION_H
#define FOUNDATION_H

#include <vector>
#include <set>
#include <sstream>

#include "card.h"
#include "stockpile.h"


class foundation
{
    public:
        
        //Constr. & Destr.
            foundation(){};
            foundation(std::vector<card>&);
            virtual ~foundation();//to clear the static sets for a new game

        //Getters
            const suitType getSuit() const {return suit;}
            rankType getLead() const {return leadRank;};
        
        //Functionality
            virtual void addCard(card);
            virtual bool canReceive(card&) const;
        
        //Aid
            void operator+(std::vector<card>&);//to play from waste to foundations
            void operator+(stockpile&);//to play from stockpiles to foundation
            friend std::ostream& operator<<(std::ostream&, const foundation&);
            virtual std::string toString() const;

        //Static public members
            static std::set<rankType> allowed;
            static std::set<suitType> taken;
            static rankType leadRank;

        protected:
            suitType suit;
};

class lowFoundation: public foundation
{
    public:
        //Constr. & Destr.
            lowFoundation();
            ~lowFoundation();

        //Functionality
            void addCard(card);
            bool canReceive(card&) const;
            
        //Aid
            friend std::ostream& operator<<(std::ostream&, const lowFoundation&);
            std::string toString() const;

    protected:

        std::set<rankType> contents;
        bool isEmpty;
};
#endif