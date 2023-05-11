#ifndef COIN_H
#define COIN_H

#include "Helper.h"

// Coin.h defines the coin structure for managing currency in the system. 
#define DELIM ","  // delimiter 

// enumeration representing the various types of currency available in the system. 
enum Denomination
{
    FIVE_CENTS, TEN_CENTS, TWENTY_CENTS, FIFTY_CENTS, ONE_DOLLAR, 
    TWO_DOLLARS, FIVE_DOLLARS, TEN_DOLLARS
};


// represents a coin type stored in the cash register perhaps. Each demonination
// will have exactly one of these in the cash register.
class Coin
{

public:

    // Denominations
    static const std::vector<std::string> coinDenomination;

    // Construct coin
    Coin(std::string s, std::string amount);

    // the denomination type
    enum Denomination denom;

    // It will convert file into a proper vector of Coin Object
    static std::vector<Coin*> convertToCoin(std::string fileName);

    // When user purchase, this will determine change amount
    static std::string getChange(std::vector<Coin*> coins, std::vector<int>& newChange, int amount);

    // Updates the coin list
    static void updateCoins(unsigned coinsCount[], std::vector<Coin*> coins);

    // Saves coin data into original coin file
    static void saveCoinFile(std::string fileName, std::vector<Coin*> coins);
    
    // the count of how many of these are in the cash register
    unsigned count;

    // Returns a string (denomination to string)
    std::string getDenomination() const;

    static void resetCoins(std::vector<Coin*> coins);
};

#endif // COIN_H
