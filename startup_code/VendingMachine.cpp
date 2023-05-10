#include "VendingMachine.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

VendingMachine::VendingMachine(string s, string c) 
{
    this->coinFile = c;
    this->stockFile = s;

    this->stockList.convertToStock(stockFile);
    this->coinList = Coin::convertToCoin(coinFile);
}

VendingMachine::~VendingMachine() 
{

}

void VendingMachine::on()
{
    string input;
    do {

        optionMenu();
    
        input = Helper::readInput();
        
        if (input == DISPLAY_ITEMS){
            displayItems();
            
        } else if (input == PURCHASE_ITEMS){
            purchaseItems();

        } else if (input == SAVE_EXIT){
            saveAndExit();

        } else if (input == ADD_ITEM) {
            addItem();

        } else if (input == REMOVE_ITEM) {
            removeItem();

        } else if (input == DISPLAY_COINS) {
            displayCoins();

        } else if (input == RESET_STOCK) {
            resetStock();

        } else if (input == RESET_COINS) {
            resetCoins();

        } 

    }
    while ((input != ABORT) && (input != SAVE_EXIT));
}

void VendingMachine::displayItems()
{
    this->stockList.printLL();
}

bool VendingMachine::purchaseItems()
{
    string validDenom[8] = {"5", "10", "20", "50", "100", "200", "500", "1000"};
    bool return_value;
    
    cout << "Purchase Item" << endl;
    cout << "-------------" << endl;
    cout << "Please enter the id of the item you wish to purchase: ";

    string input;
    
    getline(std::cin, input);

    Stock* item;
    item = this->stockList.findItem(input);

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
            change = Coin::getChange(coinList, newChange, amount);
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

void VendingMachine::saveAndExit() 
{
    stockList.saveLL(stockFile);
    Coin::saveCoinFile(this->coinFile, this->coinList)
}

bool VendingMachine::addItem() 
{
    return true;
}

bool VendingMachine::removeItem()
{
    cout << "Enter the item id of the item to remove from the menu: ";
    string input = Helper::readInput();
    if (!(this->stockList.remove(input))) {
        cout << "Invalid ID" << endl;
    }

    return true;
}

void VendingMachine::displayCoins()
{

}

void VendingMachine::resetStock()
{

}

void VendingMachine::resetCoins()
{

}

void VendingMachine::optionMenu()
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
    cout << "Select your option (1-9): ";
}