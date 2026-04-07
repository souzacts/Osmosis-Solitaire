#include "foundation.h"

//=================================================================================================foundation IMPLEMENTATION
//Initialization of static members
std::set<rankType> foundation::allowed;
std::set<suitType> foundation::taken;
rankType foundation::leadRank;
//=================================================================================================foundation CONSTR. & DESTR.
//takes the deck by reference and draws top card to initialize the top foundation, deck is updated via pop_back()
foundation::foundation(std::vector<card>& deck)
{
    card draw = deck.back();
    deck.pop_back();

    suit = draw.getSuit();
    leadRank = draw.getRank();

    allowed.insert(draw.getRank());
    taken.insert(draw.getSuit());
}

foundation::~foundation()
{
    allowed.clear();
    taken.clear();
}

//=================================================================================================foundation FUNCTIONALITY
//checks if suit is the same, if so insert into allowed. deletion of card is done in overloaded operators
void foundation::addCard(card cardToAdd)
{
    if (cardToAdd.getSuit() != this->suit)
        throw std::invalid_argument("Suit does not match");

    allowed.insert(cardToAdd.getRank());
}
//used by checkState() to see if cards are playable
bool foundation::canReceive(card& c) const
{
    //as this is for top foundation, just check if same suit and go
    if (c.getSuit() == this->suit)
        return true;
    
    return false;
}
//overloads to handle card addition to foundation and deletion of added card
void foundation:: operator+(std::vector<card>& w)//to play from waste 
{
    addCard(w.back());
    w.pop_back();
}
void foundation:: operator+(stockpile& s)//to play from stockpile 
{
    addCard(s.getCard());
    --s;
}

//=================================================================================================foundation OPERATOR & toString()

std::ostream& operator<<(std::ostream& out, const foundation& f) {return out << f.toString();}
std::string foundation::toString() const
{
    std::string color = suit == HEARTS || suit == DIAMONDS ? R : B;//set up color to print
    std::ostringstream out;
    out << color;
    int count = 0;
    for (const rankType& element : allowed)
    {
        if (count > 0)
        out << ", ";

        out << rankStr.at(element);

        count++;
    }

    if (allowed.size() == 13)//$
        out << Y << " [FULL]";

    out << W;
    return out.str();    
}

//=================================================================================================lowFoundation IMPLEMENTATION
//=================================================================================================lowFoundation CONSTR.

lowFoundation::lowFoundation()
{
    //default constructor will initialize lowfoundations with appropriate suit, keeping it empty but ready to be played on
    isEmpty = true;

    if (taken.count(HEARTS) == 0)
    {
        this->suit = HEARTS;
        taken.insert(HEARTS);
        return;
    }
    else if (taken.count(DIAMONDS) == 0)
    {
        this->suit = DIAMONDS;
        taken.insert(DIAMONDS);
        return;
    }
    else if (taken.count(CLUBS) == 0)
    {
        this->suit = CLUBS;
        taken.insert(CLUBS);
        return;
    }
    else if (taken.count(SPADES) == 0)
    {
        this->suit = SPADES;
        taken.insert(SPADES);
        return;
    }
}
//=================================================================================================lowFoundation FUNCTIONALITY
void lowFoundation::addCard(card cardToAdd)
{
    if (isEmpty)//if empty, gotta check suit and lead rank
    {
        if (cardToAdd.getSuit() != this->suit)
            throw std::invalid_argument("Suit does not match");

        if (cardToAdd.getRank() != leadRank)
            throw std::invalid_argument("To start a foundation you must start with the leading rank");
    }
    else //if not empty check suit and cards played in top foundation
    {
        if (cardToAdd.getSuit() != this->suit)
            throw std::invalid_argument("Suit does not match");
            
            //can only add cards that are in topfoundation
        if (allowed.count(cardToAdd.getRank()) == 0)
            throw std::invalid_argument("You must only play ranks that were already played in the top foundation");
    }

    //if nothing was thrown this will trigger and store rank in foundation
    contents.insert(cardToAdd.getRank());
    isEmpty = false;
}

bool lowFoundation::canReceive(card& c) const
{
    //for lowFoundations card needs to be same suit and also rank must be present in top foundation
    if (c.getSuit() == this->suit)
        if (allowed.count(c.getRank()) > 0 && !contents.empty())   //second condition ensures lowfoudation is already open(lead was played)
            return true;
        
    return false;
}
//=================================================================================================lowFoundation OPERATORS & toString()
std::ostream& operator<<(std::ostream& out, const lowFoundation& f) {return out << f.toString();}
std::string lowFoundation::toString() const
{
    std::ostringstream out;
    std::string color = suit == HEARTS || suit == DIAMONDS ? R : B;

    //startard msg to print for empty foundation, showing lead rank
    if (isEmpty)
        return color + "You must play a " + rankStr.at(leadRank) + " of " + suitStr.at(suit) + color + " to start this foundation." + W ;

    out << color;
    int count = 0;
    for (const rankType& element : contents)
    {
        if (count > 0)
        out << ", ";

        out << rankStr.at(element);

        count++;
    }
    if (contents.size() == 13)//$
        out << Y << " [FULL]";

    out << W;

    return out.str();
}
lowFoundation::~lowFoundation()//needed this despite not having pointers. Sets were causing memory leaks
{
    allowed.clear();
    taken.clear();
    contents.clear();
}