#include <iostream>
#include "LinkedList.h"
#include <fstream>
#include <string>
#include <vector>

#include <algorithm> // added to fix sort undefined
#include <cstring> // added to fix Helper::splitString()
#include "helper.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

void menu();


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
        Helper::splitString(line, item, "|");

        Helper::splitString(item[3], price, ".");
        item.at(3) = price[0];
        item.insert(item.begin() + 4, price[1]);

        items.push_back(item);
    }

    readFile.close();

    fileName = argv[2];
    readFile.open(fileName);
    while(getline(readFile, line)){
        Helper::splitString(line, denom, ",");

        Coin coin(denom[0], denom[1]);
  
        coins.push_back(coin);
    }

    readFile.close();

    sort(items.begin(), items.end(), [](const vector<string>& a, const vector<string>& b){return a[1] > b[1];});

    LinkedList* LL = new LinkedList();
    LL->initialiseLL(items);
    
    do {

        menu();

        string input;
    
        getline(std::cin, input);

        if (input == "3"){
            return EXIT_SUCCESS;
        }
        else if (input == "1"){
            cout << endl;
            LL->printLL();
            cout << endl;
        }
        else if (input == "2"){

        }
    }
    while (true);
}

void menu()
{
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
    cout << "Select your option (1-9):" << endl;
}



