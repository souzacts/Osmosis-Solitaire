#include "stockpile.h"
#include <iostream>

//=================================================================================================STOCKPILES IMPLEMENTATION
//================================================================================================= CONSTR. & DESTR.

//------------Constructor
stockpile::stockpile(std::vector<card>& deck)
{
    size = SP_SIZE;
    pile = new card*[size];  

    for(int i=0;i<this->size;i++)
    {
        this->pile[i] = new card(deck.back());
        deck.pop_back();
    }

    empty = false;
}
//------------Copy Constructor
stockpile::stockpile(const stockpile& thatStockpile)//this might not be needed $
{
    this->size = thatStockpile.size;
    this->pile = new card*[this->size];

    for (int i=0;i<this->size;i++)
        this->pile[i] = new card(*thatStockpile.pile[i]);

    empty = false;
}
//------------Destructor
stockpile::~stockpile()
{
    for (int i=0;i<this->size;i++)
        delete this->pile[i];

    delete[] pile;
}
//=================================================================================================GETTERS
const card& stockpile::getCard() const 
{   
    if (!empty)//if !empty, returns top card
        return *pile[size-1];
    else
        throw std::invalid_argument("Stockpile is empty, there's no card to play.");
}
//=================================================================================================FUNCTIONALITY
void stockpile::removeCard()
{
    if(empty)
        throw std::invalid_argument("Stockpile is empty, there is nothing to remove");

    size--;
    card** temp;

    if (size != 0)
    {
        temp = new card*[size];

        for (int i=0;i<size;i++)
            temp[i] = new card(*pile[i]);

        for (int i=0;i<size+1;i++)
            delete pile[i];

        delete[] pile;

        pile = temp;
    }
    else
    {
        empty = true;
        delete pile[0];
        delete[] pile;
        pile = nullptr;
    }

}

void stockpile::addCard(card& cardToAdd)
{
    if(empty)
    {
        size++;
        pile = new card*[size];
        pile[0] = new card(cardToAdd);
        empty = false;
    }
    else
        throw std::invalid_argument("Stockpile must be empty for you to play onto it");

}
//=================================================================================================OPERATORS
void stockpile::operator+(std::vector<card>& w)
{
    addCard(w.back());
    w.pop_back();
}

