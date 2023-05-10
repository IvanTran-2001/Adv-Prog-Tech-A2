#include "Coin.h"
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

vector<Coin*> Coin::convertToCoin(std::string fileName)
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

    return coins;
}

string Coin::getChange(vector<Coin*> coins, vector<int>& newChange, int amount){

    string change = ":";

    unsigned coinsCount[8] = {coins[0]->count, coins[1]->count, coins[2]->count, coins[3]->count, coins[4]->count, coins[5]->count, coins[6]->count, coins[7]->count};

    for (std::vector<int>::size_type i = 0; i < newChange.size(); i++){
        if (newChange[i] == 1000){
            coinsCount[0] += 1;
        }
        else if (newChange[i] == 500){
            coinsCount[1] += 1;
        }
        else if (newChange[i] == 200){
            coinsCount[2] += 1;
        }
        else if (newChange[i] == 100){
            coinsCount[3] += 1;
        }
        else if (newChange[i] == 50){
            coinsCount[4] += 1;
        }
        else if (newChange[i] == 20){
            coinsCount[5] += 1;
        }
        else if (newChange[i] == 10){
            coinsCount[6] += 1;
        }
        else if (newChange[i] == 5){
            coinsCount[7] += 1;
        }
    }

    while (amount >= 1000 && coinsCount[0] > 0){
        amount -= 1000;
        coinsCount[0] -= 1;
        change += " $10";
    }
    while (amount >= 500 && coinsCount[1] > 0){
        amount -= 500;
        coinsCount[1] -= 1;
        change += " $5";
    }
    while (amount >= 200 && coinsCount[2] > 0){
        amount -= 200;
        coinsCount[2] -= 1;
        change += " $2";
    }
    while (amount >= 100 && coinsCount[3] > 0){
        amount -= 100;
        coinsCount[3] -= 1;
        change += " $1";
    }
    while (amount >= 50 && coinsCount[4] > 0){
        amount -= 50;
        coinsCount[4] -= 1;
        change += " 50c";
    }
    while (amount >= 20 && coinsCount[5] > 0){
        amount -= 20;
        coinsCount[5] -= 1;
        change += " 20c";
    }
    while (amount >= 10 && coinsCount[6] > 0){
        amount -= 10;
        coinsCount[6] -= 1;
        change += " 10c";
    }
    while (amount >= 5 && coinsCount[7] > 0){
        amount -= 5;
        coinsCount[7] -= 1;
        change += " 5c";
    }
    
    if (amount > 0){
        change = "-1";
    }
    else {
        updateCoins(coinsCount, coins);
    }
    return change;
}

void Coin::updateCoins(unsigned coinsCount[], vector<Coin*> coins){
    
    for (int i = 0; i < 8; i++){
        coins[i]->count = coinsCount[i];
    }

}

void Coin::saveCoinFile(std::string fileName, vector<Coin*> coins) {

    std::ofstream coinsFile(fileName);

    for (Coin* coin : coins) {
        coinsFile << coin->denom << "," << coin->count << std::endl;
    }

    coinsFile.close();
}
