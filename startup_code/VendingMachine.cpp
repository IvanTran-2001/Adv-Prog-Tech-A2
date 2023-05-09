#include "VendingMachine.h"
#include "Helper.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

VendingMachine::VendingMachine(string s, string c) 
{
    stockList.convertToStock(s);
    
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

        } else if (input == SAVE_EXIT){

        } else if (input == ADD_ITEM) {

        } else if (input == REMOVE_ITEM) {

        } else if (input == DISPLAY_COINS) {

        } else if (input == RESET_STOCK) {

        } else if (input == RESET_COINS) {

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
    return true;
}

void VendingMachine::saveAndExit() 
{

}

bool VendingMachine::addItem() 
{
    return true;
}

bool VendingMachine::removeItem()
{
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

void VendingMachine::abort()
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