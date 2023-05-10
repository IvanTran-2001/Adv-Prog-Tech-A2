#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include "Helper.h"
#include "LinkedList.h"
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

using std::cout;
using std::endl;

class VendingMachine
{

private:

    LinkedList stockList;
    std::vector<Coin*> coinList;

    void displayItems();

    bool purchaseItems();

    void saveAndExit();

    bool addItem();

    bool removeItem();

    void displayCoins();

    void resetStock();

    void resetCoins();

    void optionMenu();


public:

    VendingMachine(std::string s, std::string c);
    ~VendingMachine();

    void on();
};


#endif //VENDING_MACHINE_H
