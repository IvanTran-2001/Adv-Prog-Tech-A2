#include <iostream>
#include "LinkedList.h"
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

#include <algorithm> // added to fix sort undefined
#include <cstring> // added to fix splitString()

#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;

void splitString(string s, vector<string>& tokens, string delimiter);
bool purchaseItem(LinkedList* LL, vector<Coin>& coins);
string getChange(vector<Coin>& coins, vector<int>& newChange, int amount);
void updateCoins(unsigned coinsCount[], vector<Coin>& coins);
void menu();
bool remove(LinkedList* LL);


/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
int main(int argc, char **argv)
{
    /* validate command line arguments */
    
    string fileName(argv[1]);
    string line;
    vector<vector<string>> items;
    vector<string> item;
    vector<string> price;
    vector<Coin> coins;
    vector<string> denom;
    

    std::ifstream readFile;
    readFile.open(fileName);

    while (getline(readFile, line)){
        splitString(line, item, "|");

        splitString(item[3], price, ".");
        item.at(3) = price[0];
        item.insert(item.begin() + 4, price[1]);

        items.push_back(item);
    }
    readFile.close();


    fileName = argv[2];
    readFile.open(fileName);
    while(getline(readFile, line)){
        splitString(line, denom, ",");

        Coin coin(denom[0], denom[1]);
  
        coins.push_back(coin);
    }
    readFile.close();


    sort(items.begin(), items.end(), [](const vector<string>& a, const vector<string>& b){return a[1] > b[1];});

    LinkedList* LL = new LinkedList();
    LL->initialiseLL(items);

    items.clear();
    item.clear();
    price.clear();
    denom.clear();

    string input;
    
    do {

        menu();
    
        getline(std::cin, input);

        if (input == "3"){

            // Saving and Exiting
            std::ofstream coinsFile(argv[2]);

            for (Coin& coin : coins) {
                coinsFile << coin.getDenomination() << "," << coin.getQuantity() << endl;
            }

            coinsFile.close();

            LL->saveLL(argv[1]);

            delete LL;

            exit(EXIT_SUCCESS);


            //return EXIT_SUCCESS;
        }
        else if (input == "1"){
            cout << endl;
            LL->printLL();
            cout << endl;
        }
        else if (input == "2"){
            purchaseItem(LL, coins);
        
        } else if (input == "4") {
            cout << "not done" << endl;

        } else if (input == "5") {
            remove(LL);

        } else if (input == "6") {
            cout << "not done" << endl;

        } else if (input == "7") {
            cout << "not done" << endl;

        } else if (input == "8") {
            cout << "not done" << endl;

        } 

    }
    while (input != "9");
}


void splitString(string s, vector<string>& tokens, string delimeter)
{
    tokens.clear();
    char* _s = new char[s.length()+1];
    strcpy(_s, s.c_str());

    char * pch;
    pch = strtok (_s, delimeter.c_str());
    while (pch != NULL)
    {
        tokens.push_back(pch);
        pch = strtok (NULL, delimeter.c_str());
    }
    delete[] _s;
}
bool remove(LinkedList* LL) {
    string input;
    cout << "Enter the item id of the item to remove from the menu: ";
    getline(std::cin, input);
    if (!LL->remove(input)) {
        cout << "Invalid ID" << endl;
    }
}
bool purchaseItem(LinkedList* LL, vector<Coin>& coins){
    string validDenom[8] = {"5", "10", "20", "50", "100", "200", "500", "1000"};
    bool return_value;
    
    cout << "Purchase Item" << endl;
    cout << "-------------" << endl;
    cout << "please enter the id of the item you wish to purchase:" << endl;

    string input;
    
    getline(std::cin, input);

    Stock* item;
    item = LL->findItem(input);

    if (item == nullptr){
        cout << "invalid item" << endl;
        return_value = false;
    }
    else if (item->on_hand < 1){
        cout << "item out of stock" << endl;
        return_value = false;
    }
    else{
        float amount = (100 * item->price.dollars) + item->price.cents;
        vector<int> newChange;
        bool validChange = true;
        string change;
        bool exit = false;

        cout << "You have selected \"" << item->name << " - " << item->description;
        cout << "\". This will cost you $ ";
        cout << std::fixed << std::setprecision(2) << amount * 0.01 << "." << endl;
        cout << "Please hand over the money - type in the value of each note/coins in cents." << endl;
        cout << "Please enter or ctrl-d on a new line to cancel this purchase:" << endl;

        while (amount > 0 && exit == false){
            cout << "You still need to give us $" << amount * 0.01 << ": ";
            
            getline(std::cin, input);
            
            if (input.empty()){
                exit = true;
            }

            if (find(begin(validDenom), end(validDenom), input) != end(validDenom)){
                amount -= stoi(input);
                newChange.push_back(stoi(input));
            }
            else if (exit == false){
                cout << "Error: $" << stoi(input) * 0.01;
                cout << " is not a valid denomination of money. Please try again." << endl;
            }
        }

        if (amount < 0){
            amount *= -1;
            change = getChange(coins, newChange, amount);
            if (change == "-1"){
                validChange = false;
                cout << "insufficient coins available for correct change" << endl;
                return_value = false;
            }
        }
        
        if (validChange && exit == false){
            cout << "Here is your " << item->name << " and your change of $" << amount * 0.01 << change << endl;
            item->on_hand--; // remove one item from stock
            return_value = true;
        }
        
        
    }
    return return_value;

}


string getChange(vector<Coin>& coins, vector<int>& newChange, int amount){
    string change = ":";

    unsigned coinsCount[8] = {coins[0].count, coins[1].count, coins[2].count, coins[3].count, coins[4].count, coins[5].count, coins[6].count, coins[7].count};

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
    else{
        updateCoins(coinsCount, coins);
    }
    return change;
}

void updateCoins(unsigned coinsCount[], vector<Coin>& coins){
    for (int i = 0; i < 8; i++){
        coins[i].count = coinsCount[i];
    }
}

void menu() {
    cout << "Main Menu:" << endl;
    cout << "\t1.Display Items" << endl;
    cout << "\t2.Purchase Items" << endl;
    cout << "\t3.Save and Exit" << endl;
    cout << "Administrator-Only Menu:" << endl;
    cout << "\t4.Add Item" << endl;
    cout << "\t5.Remove Item" << endl;
    cout << "\t6.Display Coins" << endl;
    cout << "\t7.Reset Stock" << endl;
    cout << "\t8.Reset Coins" << endl;
    cout << "\t9.Abort Program" << endl;
    cout << "Select your option (1-9): ";
}