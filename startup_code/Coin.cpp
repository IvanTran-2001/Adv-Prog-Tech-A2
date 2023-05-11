#include "Coin.h"
using std::string;
using std::vector;

const std::vector<std::string> Coin::coinDenomination = {"5", "10", "20", "50", "100", "200", "500", "1000"};
//This class does not require a deconstructor.

Coin::Coin(std::string s, std::string amount){

    // Converts string to denomation
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

    // Stores the amount of cash/coins
    count = stoul(amount);
}

std::string Coin::getDenomination() const {
    
    std::string cents;

    //Converts denomination to string
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

    vector<string> checkValidCoins;

    // Reading file
    std::ifstream readFile;

    // Open file
    readFile.open(fileName);

    while (getline(readFile, line))
    {
        checkValidCoins.push_back(line);

    }

    // Sort list
    std::sort(checkValidCoins.begin(), checkValidCoins.end(), [](const string& a, const string& b) {
        return a < b;
    });


    if (Helper::validCoin(checkValidCoins)) {
        for (string s:checkValidCoins) {
            // Splits string by deliminter
            Helper::splitString(s, denom, DELIM);

            // Representation of string line
            string coinType = denom[0];
            string amount = denom[1];

            // Create coin on the heap
            Coin* coin = new Coin(coinType, amount);

            // Add coin type to the vector
            coins.push_back(coin);
        }
    }

    // Close file
    readFile.close();

    // Return a vector of coin pointers
    return coins;
}



string Coin::getChange(vector<Coin*> coins, vector<int>& newChange, int amount){

    amount *= -1;
    string change = ":";

    unsigned coinsCount[8] = {coins[0]->count, coins[1]->count, coins[2]->count, coins[3]->count, coins[4]->count, coins[5]->count, coins[6]->count, coins[7]->count};

    // Loops through change and convert to denominations
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

    // The while loops will essentially go through
    // the coin list and essentially calculate
    // if we have valid change or not.
    // This is dermined by if amount is 0 or over.
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
    
    // If not 0, means change invalid
    if (amount > 0){
        change = "-1";
    }

    // Will update the coinlist
    else {
        updateCoins(coinsCount, coins);
    }

    //
    return change;
}

void Coin::updateCoins(unsigned coinsCount[], vector<Coin*> coins){
    
    // Essentially replaces the count values for each Coin object
    for (int i = 0; i < 8; i++){
        coins[i]->count = coinsCount[i];
    }

}

void Coin::saveCoinFile(std::string fileName, vector<Coin*> coins) {

    // Creates file for coin list
    std::ofstream coinsFile(fileName);

    // Creating format
    for (Coin* coin : coins) {
        coinsFile << coin->getDenomination() << "," << coin->count << std::endl;
    }

    // Close
    coinsFile.close();
}
