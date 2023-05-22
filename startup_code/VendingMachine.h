#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include "Helper.h"
#include "LinkedList.h"
#include "LinkedListSingle.h"
#include "LinkedListDouble.h"
#include "Coin.h"

#define DISPLAY_ITEMS "1"
#define PURCHASE_ITEMS "2"
#define SAVE_EXIT "3"
#define ADD_ITEM "4"
#define REMOVE_ITEM "5"
#define DISPLAY_COINS "6"
#define RESET_STOCK "7" 
#define RESET_COINS "8"
#define ABORT "9"

class VendingMachine
{

private:

    LinkedList* stockList;
    std::vector<Coin*> coinList;

    std::string stockFile;
    std::string coinFile;

    // Displays all stock
    void displayItems();

    // For user to purchase stock
    bool purchaseItems();

    // Save stock and coin data into file
    void saveAndExit();

    // Add stock to vending machine
    void addItem();

    // Remove stock from vending machine
    bool removeItem();

    // Display how much money in vending machine
    void displayCoins();

    // Resetting or restocking vending machine
    void resetStock();

    // Resetting coin list
    void resetCoins();

    // Freeing stock memory
    void deleteStockList();

    // Freeing coin memory
    void deleteCoinList();

    // User prompts
    void optionMenu();
    void purchaseMsg();


public:

    VendingMachine(std::string s, std::string c);
    ~VendingMachine();

    void on();
};


#endif //VENDING_MACHINE_H
