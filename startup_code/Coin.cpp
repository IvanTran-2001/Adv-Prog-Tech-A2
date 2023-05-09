#include "Coin.h"
#include "Helper.h"
using std::string;
using std::vector;

Coin::Coin()
{

}

 // implement functions for managing coins; this may depend on your design.
Coin::Coin(std::string s, std::string amount){
    if (s == "5"){
        this->denom = FIVE_CENTS;
    }
    else if (s == "10"){
        denom = TEN_CENTS;
    }
    else if (s == "20"){
        denom = TWENTY_CENTS;
    }
    else if (s == "50"){
        denom = FIFTY_CENTS;
    }
    else if (s == "100"){
        denom = ONE_DOLLAR;
    }
    else if (s == "200"){
        denom = TWO_DOLLARS;
    }
    else if (s == "500"){
        denom = FIVE_DOLLARS;
    }
    else if (s == "1000"){
        denom = TEN_DOLLARS;
    }

    count = stoul(amount);
}

Coin::~Coin() 
{
    
}


std::string Coin::getDenomination() const {
    
    std::string cents;

    if (denom == FIVE_CENTS) {
        cents = "5";
    }
    else if (denom == TEN_CENTS){
        cents = "10";
    }
    else if (denom == TWENTY_CENTS){
        cents = "20";
    }
    else if (denom == FIFTY_CENTS){
        cents = "50";
    }
    else if (denom == ONE_DOLLAR){
        cents = "100";
    }
    else if (denom == TWO_DOLLARS){
        cents = "200";
    }
    else if (denom == FIVE_DOLLARS){
        cents = "500";
    }
    else if (denom == TEN_DOLLARS){
        cents = "1000";
    }

    return cents;

}

void Coin::convertToCoin(std::string fileName)
{

    string line;
    vector<Coin*> coins;
    vector<string> denom;

    std::ifstream readFile;

    readFile.open(fileName);

    while (getline(readFile, line))
    {
        Helper::splitString(line, denom, ",");
        if (Helper::validCoin(denom)) {
            Coin* coin = new Coin(denom[0], denom[1]);
            coins.push_back(coin);
        }
    }

    readFile.close();

}
