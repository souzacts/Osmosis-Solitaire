#include "game.h"

//=================================================================================================GAME IMPLEMENTATION
//=================================================================================================CONSTR. & DESTR.
game::game()
{
    buildLayout();
    won = false;
    standStill = false;
}
game::~game()
{
    for (int i=0;i<SIZE;i++)
        delete f[i];

    d.clear();
    s.clear();
    f.clear();
}
//=================================================================================================FUNCTIONALITY
void game::buildLayout()
{
    //initialize deck d[0] and waste d[1]//
    //d[0] is built and d[1] is initialized to an empty vec
    std::vector<card> temp;
    d.push_back(temp);

    buildAndShuffle();

    d.push_back(temp);
    
    //initialize stockpiles with created deck, constructor draws from deck and pop_back cards drawn
    for (int i=0;i<SIZE;i++)
        s.push_back(stockpile(d[0]));

    //initialize lead foundation with deck top card and lowFoundations to a default state where only suits are assigned
    f.push_back(new foundation(d[0]));
    for (int i=1;i<SIZE;i++)
        f.push_back(new lowFoundation);
}
void game::buildAndShuffle()
{
    //initializes deck with cards, deck is then shuffled
    for (int suit=HEARTS;suit<=SPADES;suit++)
        for (int rank=ACE;rank<=KING;rank++)
        {
            if (suit == HEARTS)
                d[0].push_back(card(rank, static_cast<suitType>(suit)));
            
            else if (suit == DIAMONDS)
                d[0].push_back(card(rank, static_cast<suitType>(suit)));
            
            else if (suit == CLUBS)
                d[0].push_back(card(rank, static_cast<suitType>(suit)));
            
            else if (suit == SPADES)
                d[0].push_back(card(rank, static_cast<suitType>(suit)));
        }

    std::srand(std::time(NULL));
    int k;
    //shuffle 7 times as the Card Guy recommends
    for (int w=0;w<8;w++)
        for (int i=d[0].size()-1; i>0;i--)//Fisher-Yates shuffle algorithm
            {
                k = std::rand() % (i+1);
                std::swap(d[0][i], d[0][k]);
            }
}
std::string game::printTable() const
{
    //cards left in deck, formated to fit the ascii grid
    std::string dL = (d[0].size() >= TEN) ? std::to_string(d[0].size()) : std::to_string(d[0].size()) + " ";


//------------------------------------------------------------------------SET UP FOR WASTE:

    //cards left in waste, formated to fit the ascii grid
    std::string wL = (d[1].size() >= TEN) ? std::to_string(d[1].size()) : std::to_string(d[1].size()) + " ";

    std::string wS;//waste suit of displayed card
    std::string wT;//waste rank @ top of displayed card
    std::string wB;//waste rank @ bottom of displayed card

    if (!d[1].empty())//if not empty, print top card
    { 
        wS = suitStr.at(d[1].back().getSuit());//waste suit of topcard
        
        //had to do this as rank 10 is the only that takes 2 spaces to print, it was causing misalignment
        wT = d[1].back().getRank() == TEN ? colorfy(d[1].back()) : colorfy(d[1].back()) + " ";
        wB = d[1].back().getRank() == TEN ? colorfy(d[1].back()) : " " + colorfy(d[1].back());
    }
    else
    {
        wS = "*";
        wT = "* ";
        wB = " *";
    }
//------------------------------------------------------------------------SET UP FOR STOCKPILE 1 :
    std::string s1S;//s1 suit to print
    std::string s1T;//s1 rank @ top of displayed card
    std::string s1B;//s1 rank @ bottom of displayed card
 
    if (!s[0].isEmpty())//if not empty, print top card
    {
        s1S = suitStr.at(s[0].getCard().getSuit());
        s1T = s[0].getCard().getRank() == TEN ? colorfy(s[0].getCard()) : colorfy(s[0].getCard()) + " ";
        s1B = s[0].getCard().getRank() == TEN ? colorfy(s[0].getCard()) : " " + colorfy(s[0].getCard());
    }
    else
    {
        s1S = "*";
        s1T = "* ";
        s1B = " *";
    }
//------------------------------------------------------------------------SET UP FOR STOCKPILE 2:

    std::string s2S;//s2 suit to print
    std::string s2T;//s2 rank @ top of displayed card
    std::string s2B;//s2 rank @ bottom of displayed card

    if (!s[1].isEmpty())//if not empty, print top card
    {
        s2S = suitStr.at(s[1].getCard().getSuit());
        s2T = s[1].getCard().getRank() == TEN ? colorfy(s[1].getCard()) : colorfy(s[1].getCard()) + " ";
        s2B = s[1].getCard().getRank() == TEN ? colorfy(s[1].getCard()) : " " + colorfy(s[1].getCard());
    }
    else
    {
        s2S = "*";
        s2T = "* ";
        s2B = " *";
    }
 
 //------------------------------------------------------------------------SET UP FOR STOCKPILE 3:

    std::string s3S;//s3 suit to print
    std::string s3T;//s3 rank @ top of displayed card
    std::string s3B;//s3 rank @ bottom of displayed card
 
    if (!s[2].isEmpty())//if not empty, print top card
    {
        s3S = suitStr.at(s[2].getCard().getSuit());
        s3T = s[2].getCard().getRank() == TEN ? colorfy(s[2].getCard()) : colorfy(s[2].getCard()) + " ";
        s3B = s[2].getCard().getRank() == TEN ? colorfy(s[2].getCard()) : " " + colorfy(s[2].getCard());
    }
    else
    {
        s3S = "*";
        s3T = "* ";
        s3B = " *";
    }

    //------------------------------------------------------------------------SET UP FOR STOCKPILE 4:

    std::string s4S;//s4 suit to print
    std::string s4T;//s4 rank @ top of displayed card
    std::string s4B;//s4 rank @ bottom of displayed card
 
    if (!s[3].isEmpty())//if not empty, print top card
    {
        s4S = suitStr.at(s[3].getCard().getSuit());
        s4T = s[3].getCard().getRank() == TEN ? colorfy(s[3].getCard()) : colorfy(s[3].getCard()) + " ";
        s4B = s[3].getCard().getRank() == TEN ? colorfy(s[3].getCard()) : " " + colorfy(s[3].getCard());
    }
    else
    {
        s4S = "*";
        s4T = "* ";
        s4B = " *";
    }
 

//------------------------------------------------------------------------SET UP FOR FOUNDATIONS :
    std::string f1S = suitStr.at(f[0]->getSuit());
    std::string f2S = suitStr.at(f[1]->getSuit());
    std::string f3S = suitStr.at(f[2]->getSuit());
    std::string f4S = suitStr.at(f[3]->getSuit());

    std::ostringstream out;

    out << 
    "\n\nDeck Cards\n"
    "Left:"<<dL<<"           " + G + "Stockpiles" + W + "        " + Bu + "Foundations" + W + " \n"
    "┌─────────┐       ┌─────────┐      \n"      
    "│ ░░░░░░░ │    "+Y+"[1]"+W+"│ "<<s1T<<"      │       "+Y+"[2]"+W+" F"<<f1S<<" : "<<*f[0]<<"\n"
    "│ ░░░░░░░ │       │         │   \n"
    "│ ░░░░░░░ │       │    "<<s1S<<"    │   \n"
    "│ ░░░░░░░ │       │         │   \n"
    "│ ░░░░░░░ │       │      "<<s1B<<" │   \n"
    "└─────────┘       └─────────┘   \n"
    ""+Y+"[ENTER]"+W+"\n"
    "┌─────────┐       ┌─────────┐          \n"      
    "│ "<<wT<<"      │    "+Y+"[Q]"+W+"│ "<<s2T<<"      │       "+Y+"[W]"+W+" F"<<f2S<<" : "<<*f[1]<<"   \n"
    "│         │       │         │   \n"
    "│    "<<wS<<"    │       │    "<<s2S<<"    │   \n"
    "│         │       │         │   \n"
    "│      "<<wB<<" │       │      "<<s2B<<" │   \n"
    "└─────────┘       └─────────┘   \n"
    "Waste Cards\n"            
    "Left:"<<wL<<"           ┌─────────┐     \n"         
    "               "+Y+"[A]"+W+"│ "<<s3T<<"      │       "+Y+"[S]"+W+" F"<<f3S<<" : "<<*f[2]<<"   \n"
    "                  │         │   \n"
    "                  │    "<<s3S<<"    │   \n"
    "                  │         │   \n"
    "                  │      "<<s3B<<" │   \n"
    "                  └─────────┘   \n\n"
    
    "                  ┌─────────┐          \n"   
    "               "+Y+"[Z]"+W+"│ "<<s4T<<"      │       "+Y+"[X]"+W+" F"<<f4S<<" : "<<*f[3]<<"       \n"
    "                  │         │   \n"
    "                  │    "<<s4S<<"    │   \n"
    "                  │         │   \n"
    "                  │      "<<s4B<<" │   \n"
    "                  └─────────┘   \n"


    "\nLost? Enter " + Y + "help" + W + " or " + Y + "h" + W + " for... well... help!\n"
    "Enter " + R + "quit" + W + " to abandon this game and go back to the main menu." << std::endl;

    return out.str();
}
void game::checkState()
{
    //check is performed only when waste is exhausted and/or redealt into deck or when both are exhausted,
    if (d[1].empty() )
    {
        //first check stockpiles, if any is empty, there's still at least one valid move (play into it)
        //as long as deck has cards to play
        for (int i=0;i<4;i++)
            if(s[i].isEmpty() && !d[0].empty())    
                return;

        //this checks if anything can be played from stockpiles
        for (int i=0;i<4;i++)
        {
            if (!s[i].isEmpty())//make sure its not empty (case deck is empty and there's an empty stockpile)
            {  
                card c = s[i].getCard();//gets top card for checking

                //if any foundation can receive any of the top cards in any stock, valid move is found, return early
                for (int k=0;k<SIZE;k++)
                    if (f[k]->canReceive(c))
                        return;
            }
        }
        //this checks the deck for playable cards to foundations
        //starting from back, check top card(that would be in the waste) in steps of 3
        //there's an offset of 3 to simulate the behavior of the wastepile
        //suppose deck has 35 cards, deck[34](last element of deck) would not be accessible as it would be the bottom card in the waste
        //therefore, deck[32]would be the top card in the waste after a peel, and thats the starting point-> deck.size()-3
        for (int j=d[0].size()-3;j>=0;j-=3)
        {   
            //if iterator < 3, adjust step to first element in deck d[0][0]
            int cardToCheck = (j >= 3) ? j : 0;
            
            //check each card against all foundations, if a valid move is found, return early
            for (int k=0;k<SIZE;k++)
                if (f[k]->canReceive(d[0][cardToCheck]))
                    return;     
        }

        bool stocksEmpty = true;
        bool exhausted = d[0].empty() && d[1].empty();
        //check winning state
        //to win, deck and waste must be exhausted and all stockpiles empty, meaning all cards are in foundation

        if (exhausted)//if deck and waste are empty, check each stock
            for (int i=0;i<SIZE;i++)
                if(!s[i].isEmpty())//if any stock is not empty, allEmpty is set to false
                {
                    stocksEmpty = false;
                    break;
                }

        if (exhausted && stocksEmpty)//if all empty, this must be a win
            won = true;

        //if nothing in the function triggers, there are no valid moves and player hasn't won, then we have a standstill
        //and game over
        if (!won)
            standStill = true;
    }
}
void game::play()
{
    //used to throw when needed
    std::invalid_argument invalidCommand("You entered an invalid command, nothing was done. You may continue playing.");
    std::string input;

    //get user input and format it
    std::getline(std::cin, input);
    toUpper(input);

    //these will print how to play or game rules
    if (input == "HELP" || input == "H")
        throw inGameHelp("H");
    
    else if (input == "MORE HELP" || input == "MH") 
        throw inGameHelp("MH");
    //early exit during game
    else if(input == "QUIT")
        throw input;


    //if user just hit enter, draw
    if (input.empty())
        peel();

    //when only one character is entered, the default is to play from wastepile to the corresponding pile
    if (input.size() == 1 && input[0] != 'H')
    {
        if (!d[1].empty())//waste must have something to be played from 
        {
            switch(input[0])
            {
                case '1':  s[0] + d[1]; break;//to stockpile 1 
                
                case 'Q':  s[1] + d[1]; break;//to stockpile 2
                    
                case 'A':  s[2] + d[1]; break;//to stockpile 3
                    
                case 'Z':  s[3] + d[1]; break;//to stockpile 4

                case '2': *f[0] + d[1]; break;//to foundation 1 (LEAD)

                case 'W': *f[1] + d[1]; break;//to foundation 2

                case 'S': *f[2] + d[1]; break;//to foundation 3

                case 'X': *f[3] + d[1]; break;//to foundation 4

                default: throw invalidCommand;

            }
        }
        else
        {
            if (tags.count(input) == 0)
                throw invalidCommand;

            if (d[0].empty())
                throw std::invalid_argument("\n\n" + R + "!!!WARNING!!!" + W + " The wastepile and deck are exhausted, you can only play from " + G + "stockpiles" + W + " now.");
            else
                throw std::invalid_argument("\n\n" + R + "!!!WARNING!!!" + W + " The wastepile is empty, hit " + Y + "[Enter]" + W + " to draw from deck.");
        }
    }
    else if (input.size() == 2)//when playing from stockpiles to foundations
    {
        switch(input[0])//outter switch checks first character in command, if no match found, default is to throw an invalidCommand
        {
            case '1':
                switch(input[1])//inner switch checks second character and perform operation, if no match found, throw invalidCommand by default
                {
                    case '2': *f[0] + s[0]; break;

                    case 'W': *f[1] + s[0]; break;

                    case 'S': *f[2] + s[0]; break;

                    case 'X': *f[3] + s[0]; break;

                    default: throw invalidCommand;

                }
                break;

            case 'Q':
                switch(input[1])
                {
                    case '2': *f[0] + s[1]; break;

                    case 'W': *f[1] + s[1]; break;

                    case 'S': *f[2] + s[1]; break;

                    case 'X': *f[3] + s[1]; break;

                    default: throw invalidCommand;

                }
                break;

            case 'A':
                switch(input[1])
                {
                    case '2': *f[0] + s[2]; break;

                    case 'W': *f[1] + s[2]; break;

                    case 'S': *f[2] + s[2]; break;

                    case 'X': *f[3] + s[2]; break;

                    default: throw invalidCommand;

                }
                break;

            case 'Z':
                switch(input[1])
                {
                    case '2': *f[0] + s[3]; break;

                    case 'W': *f[1] + s[3]; break;

                    case 'S': *f[2] + s[3]; break;

                    case 'X': *f[3] + s[3]; break;

                    default: throw invalidCommand;

                }
                break;
            
            default: throw invalidCommand;
        }
    }
    else if (!input.empty())//in case nothing triggers and input is not empty, user entered some random command, throw invalidCommand
        throw invalidCommand;
}
void game::peel()
{
    //ajust amount of cards to peel based on deck availability
    int peelAmount = (d[0].size() < 3) ? d[0].size() : 3;

    while (peelAmount != 0)
    {    
        d[1].push_back(d[0].back());
        d[0].pop_back();
        peelAmount--;
    }

    //use this so deck doesnt automatically redeals and peels into waste, leaving waste empty for 1 play
    //allowing the checkstate to check deck for valid moves
    static int cue = 1;
    if (d[0].empty() )
    {
        if (cue % 2 == 0)
            redeal();
        
        cue++;
    }
}
void game::redeal()
{
    //flip order of waste and swap contents, this way it preserves the deck order
    std::reverse(d[1].begin(), d[1].end());
    d[0].swap(d[1]);
}
//=================================================================================================OPERATORS
std::ostream& operator<<(std::ostream& out, const game& g) {return out << g.printTable();}
//=================================================================================================STATIC FUNCTIONS
//Used to read .txt files associated with the game
std::string game::read(std::string option)
{
    std::ostringstream out;
    std::ifstream readFile;

    readFile.open(option + ".txt");

    if (!readFile.is_open())
        std::cerr << "Unable to find " + option + ".txt file" << std::endl;

    std::string line;
    
    while (std::getline(readFile, line))
        out << line << std::endl;

    readFile.close();

    return out.str();
}

//=================================================================================================AID
std::string colorfy(const card& c)
{
    //R, B & W are Red, Black & White are global const string manipulators to change color of text
    std::ostringstream out;

    std::string color = c.getSuit() == HEARTS || c.getSuit() == DIAMONDS ? R : B;

    out << color << rankStr.at(c.getRank()) << W;

    return out.str();
}
void toUpper(std::string& x)
{
    for (auto& c : x)
        c = toupper(c);
}
std::string inGameHelp(std::string input)
{
    std::ostringstream out;

    out << "\n\n" + Y + "How to play:" + W + "\n\n"
        << "Simply press " + Y + "[Enter]" + W + " to draw from deck." << std::endl
        << "To play the card on top of the wastepile enter where you want to play it, use the " + Y + "tags" + W + " for reference." << std::endl
        << "To play from a " + G + "stockpile" + W + " to a " + Bu + "foundation" + W + " enter its " + Y + "tag" + W + " followed by the " + Y + "tag" + W + " of the destination. eg.(1w)" << std::endl
        << "If you end up having a stroke and enter some rubbish, don't worry; nothing will happen. Go on, give it a try." << std::endl << std::endl
        << "Enlarge your terminal until you see both " + Y + "yellow" + W + " lines. The game happens between them." << std::endl
        << "Still kinda lost? Enter " + Y + "more help" + W + " or " + Y + "mh" + W + " for game rules." << std::endl
        << R << "\nPRO TIP:" << W << " Avoid playing more than 2 cards between draws, this way you ensure you will see different cards next time around!" << std::endl;

    if (input[0] == 'M')
        out << "\nCards are peeled from deck to waste pile in groups of 3." << std::endl
            << "You can only play from the waste pile or from " + G + "stockpiles" + W + "." << std::endl
            << "If moves are valid, you may play from waste or " + G + "stockpiles" + W + " until they are exhausted." << std::endl
            << "You may play cards from waste to a " + G + "stockpile" + W + ", as long as it is empty first." << std::endl 
            << "Empty piles are shown with '*' for rank and suit." << std::endl << std::endl
            << "The goal of the game is to play all cards to the " + Bu + "foundations" + W + "." << std::endl
            << "The top " + Bu + "foundation" + W + " is the lead, all other " + Bu + "foundations" + W + " only accept cards present in the lead" << std::endl
            << "On top of that, all " + Bu + "foundations" + W + R + " MUST " + W + "start with the same rank as the top." << std::endl
            << "If you play an illegal move, a " + R + "!!!WARNING!!!" + W + " will show you where you messed up." << std::endl
            << "That's it... Have fun!" << std::endl;

    return out.str();
}
