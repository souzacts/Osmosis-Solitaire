#ifndef STOCKPILE_H
#define STOCKPILE_H

#include <set>
#include <vector>
#include <stdexcept>
#include "card.h"

const int SP_SIZE = 4;//default size for stockpile when game starts


class stockpile
{
    public:
    
    //Constr. & Destr.
        stockpile(){};
        stockpile(std::vector<card>&);
        stockpile(const stockpile&);
        ~stockpile();

    //Getters
        const card& getCard() const;
        const bool isEmpty() const {return empty;}
        //const int getSize() const {return size;}

    //Functionality
        void removeCard();
        void addCard(card&);

    //Operators
        void operator+(std::vector<card>&);//take from waste to addCard
        void operator--() {removeCard();};

    private:
        card** pile;
        int size;
        bool empty;

};

#endif