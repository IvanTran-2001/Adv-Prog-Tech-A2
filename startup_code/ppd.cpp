#include <iostream>
#include "LinkedList.h"
#include <fstream>
#include <string>
#include <vector>

#include <algorithm> // added to fix sort undefined
#include <cstring> // added to fix splitString()

using std::string;
using std::vector;

void splitString(string s, vector<string>& tokens, string delimiter);

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
    
    do {
        std::cout << "Main Menu:" << std::endl;
        std::cout << "\t1.Display Items" << std::endl;
        std::cout << "\t2.Purchase Items" << std::endl;
        std::cout << "\t3.Save and Exit" << std::endl;
        std::cout << "Administrator-Only Menu:" << std::endl;
        std::cout << "\t4.Add Item" << std::endl;
        std::cout << "\t5.Remove Item" << std::endl;
        std::cout << "\t6.Display Coins" << std::endl;
        std::cout << "\t7.Reset Stock" << std::endl;
        std::cout << "\t8.Reset Coins" << std::endl;
        std::cout << "\t9.Abort Program" << std::endl;
        std::cout << "Select your option (1-9):" << std::endl;

        string input;
    
        getline(std::cin, input);

        if (input == "3"){
            return EXIT_SUCCESS;
        }
        else if (input == "1"){
            std::cout << std::endl;
            LL->printLL();
            std::cout << std::endl;
        }
        else if (input == "2"){

        }
    }
    while (true);
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
