#ifndef CARD_H
#define CARD_H

#include <string>
#include <map>

//string manipulators for colored text, used throughout the program
const std::string B  = "\033[30m";//black
const std::string R  = "\033[31m";//red
const std::string Y  = "\033[33m";//yellow
const std::string G  = "\033[32m";//green
const std::string Bu = "\033[34m";//blue
const std::string W  = "\033[0m";//default

enum suitType {HEARTS, DIAMONDS, CLUBS, SPADES};
enum rankType {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};

const std::map<suitType, std::string> suitStr
{
    {HEARTS,   R + "♥" + W},
    {DIAMONDS, R + "♦" + W},
    {CLUBS,    B + "♣" + W},
    {SPADES,   B + "♠" + W}

};
const std::map<rankType, std::string> rankStr
{
    {ACE ,  "A"},
    {TWO,   "2"},
    {THREE, "3"},
    {FOUR,  "4"},
    {FIVE,  "5"},
    {SIX,   "6"},
    {SEVEN, "7"},
    {EIGHT, "8"},
    {NINE,  "9"},
    {TEN,   "10"},
    {JACK,  "J"},
    {QUEEN, "Q"},
    {KING,  "K"},
};

class card
{
    public:

    //Constr.
        card(int rank, suitType suit);
    
    //Getters
        rankType getRank() const;
        suitType getSuit() const;

    protected:

    //Members
        rankType rank;
        suitType suit;
};

#endif