#include "card.h"

//=================================================================================================CARD IMPLEMENTATION
card::card(int rank, suitType suit)
{
    this->rank = static_cast<rankType>(rank);
    this->suit = static_cast<suitType>(suit);
}
//Getters
suitType card::getSuit() const {return this->suit;}
rankType card::getRank() const {return this->rank;}


