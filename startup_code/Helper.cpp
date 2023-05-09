#include "helper.h"

using std::string;
using std::vector;
using std::stoi;

Helper::Helper(){}

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

string Helper::readInput()
{
    string input;
    std::getline(std::cin, input);
    std::cout << std::endl;

    return input;
}

LinkedList Helper::convertToStock(std::string fileName)
{
    string line;

    LinkedList items;
    vector<string> item;
    vector<string> price;

    std::ifstream readFile;

    readFile.open(fileName);

    while (getline(readFile, line))
    {
        
        splitString(line, item, "|");

        if (validStock(item)) 
        {
            Stock* addStock = new Stock();
            Price split;

            splitString(item[3], price, ".");
            split.dollars = stoi(price[0]);
            split.cents = stoi(price[1]);

            addStock->id = item[0];
            addStock->name = item[1];
            addStock->description = item[2];
            addStock->price = split;
            addStock->on_hand = stoi(item[4]);
            
            items.addLL(addStock);
        }
    }
    readFile.close();

    return items;
}

bool Helper::validStock(vector<string> stock) 
{
    return true;
}

std::vector<Coin*> Helper::convertToCoin(std::string fileName)
{
    string line;
    vector<Coin*> coins;
    vector<string> denom;

    std::ifstream readFile;

    readFile.open(fileName);

    while (getline(readFile, line))
    {
        splitString(line, denom, ",");
        if (validCoin(denom)) {
            Coin* coin = new Coin(denom[0], denom[1]);
            coins.push_back(coin);
        }
    }

    readFile.close();

    return coins;
}



