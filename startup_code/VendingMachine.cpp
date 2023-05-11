#include "VendingMachine.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

VendingMachine::VendingMachine(string s, string c) 
{
    this->coinFile = c;
    this->stockFile = s;
    this->coinList = Coin::convertToCoin(coinFile);
}

VendingMachine::~VendingMachine() 
{

}

void VendingMachine::on()
{

    //Input
    string input;

    if ((this->stockList.convertToStock(stockFile))) {
        input = ABORT;
    }


    // Will quit if abort or save and exit
    while ((input != ABORT) && (input != SAVE_EXIT)) {

        // Menu Options
        optionMenu();

        // Reading user input
        input = Helper::readInput();
        
        // Option Executions
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

    std::cout << "---Closing Vending Machine---" << std::endl;

}

void VendingMachine::displayItems()
{
    // Printing the linked list in certain format
    this->stockList.printLL();
}

bool VendingMachine::purchaseItems()
{
    // The denominations
    string validDenom[8] = {"5", "10", "20", "50", "100", "200", "500", "1000"};
    bool return_value;
    
    // Message
    purchaseMsg();

    // Getting input
    string input = Helper::readInput();

    // Finding item of input
    Stock* item = this->stockList.findItem(input);

    // If invalid search
    if (item == nullptr){
        cout << "invalid item" << endl;
        return_value = false;
    }

    // If no stock left
    else if (item->on_hand < 1){
        cout << "item out of stock" << endl;
        return_value = false;
    }

    // Going through purchase proccess
    else{

        // Converting to cents
        // Decimals are flawed
        float amount = (100 * item->price.dollars) + item->price.cents;

        // Change amount
        vector<int> newChange;
        bool validChange = true;
        string change;
        bool exit = false;

        // Output
        cout << "You have selected \"" << item->name << " - " << item->description;
        cout << "\". This will cost you $ ";
        cout << std::fixed << std::setprecision(2) << amount * 0.01 << "." << endl;
        cout << "Please hand over the money - type in the value of each note/coins in cents." << endl;
        cout << "Please enter or ctrl-d on a new line to cancel this purchase:" << endl;

        // Will exit until price paid or user leaves
        while (amount > 0 && !exit){

            // Informing user money not fully paid.
            cout << "You still need to give us $" << amount * 0.01 << ": ";
            
            // Reading user input
            input = Helper::readInput();
            
            // Will exit if user simply presses enter
            if (input.empty()){
                exit = true;
            }

            // Will confirm if within denomination
            if (find(begin(validDenom), end(validDenom), input) != end(validDenom)){

                amount -= stoi(input);
                newChange.push_back(stoi(input));
            }

            // Else will prompt not a proper denomination
            else if (exit == false){

                cout << "Error: $" << stoi(input) * 0.01;
                cout << " is not a valid denomination of money. Please try again." << endl;
            }
        }

        // If amount is in negatives, change needs to be given
        if (amount < 0){

            // Calculating change (this will also change the coin List automatically if valid)
            change = Coin::getChange(coinList, newChange, amount);

            // Checking if possible to give change
            if (change == "-1"){

                validChange = false;
                cout << "insufficient coins available for correct change" << endl;
                return_value = false;
            }
        }

        // Change will be given if appropriate
        if (validChange && exit == false){


            cout << "Here is your " << item->name << " and your change of $" << amount * 0.01 << change << endl;
            item->on_hand--; 
            return_value = true;
        }
        
        
    }

    // Return if possible
    return return_value;
}


void VendingMachine::saveAndExit() 
{
    // Saving to a file
    stockList.saveLL(stockFile);
    Coin::saveCoinFile(this->coinFile, this->coinList);
}

bool VendingMachine::addItem() 
{
    return true;
}

bool VendingMachine::removeItem()
{
    // Removing a file
    cout << "Enter the item id of the item to remove from the menu: ";
    string input = Helper::readInput();
    if (!(this->stockList.remove(input))) {
        cout << "Invalid ID" << endl;
    }

    return true;
}

void VendingMachine::displayCoins()
{
    string formatting_spaces[8];
    int count_digits;

    for (int i = 0; i < 8; i++){
        count_digits = std::to_string(coinList[i]->count).length();
        string spaces(10 - count_digits, ' ');
        formatting_spaces[i] = spaces;
    }
    
    cout << "Coins Summary" << endl;
    cout << "-------------" << endl;
    cout << "Denomination    |    Count" << endl;
    cout << "---------------------------" << endl;
    cout << "5 Cents         |" << formatting_spaces[7] << coinList[7]->count << endl;
    cout << "10 Cents        |" << formatting_spaces[6] << coinList[6]->count << endl;
    cout << "20 Cents        |" << formatting_spaces[5] << coinList[5]->count << endl;
    cout << "50 Cents        |" << formatting_spaces[4] << coinList[4]->count << endl;
    cout << "1 Dollar        |" << formatting_spaces[3] << coinList[3]->count << endl;
    cout << "2 Dollars       |" << formatting_spaces[2] << coinList[2]->count << endl;
    cout << "5 Dollars       |" << formatting_spaces[1] << coinList[1]->count << endl;
    cout << "10 Dollars      |" << formatting_spaces[0] << coinList[0]->count << endl;

}

void VendingMachine::resetStock()
{

    // Reset stock to defualt value
    stockList.resetStock();
}

void VendingMachine::resetCoins()
{

}

void VendingMachine::purchaseMsg()
{
    cout << "Purchase Item" << endl;
    cout << "-------------" << endl;
    cout << "Please enter the id of the item you wish to purchase: ";
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

void VendingMachine::deleteStockList()
{

}

void VendingMachine::deleteCoinList()
{
    
}