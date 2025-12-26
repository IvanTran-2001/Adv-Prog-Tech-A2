#include "VendingMachine.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

VendingMachine::VendingMachine(string s, string c) 
{
    this->coinFile = c;
    this->stockFile = s;
    enhancement = true;

    // Empty List
    this->stockList = new LinkedListDouble();

    // Constructing coin list
    this->coinList = Coin::convertToCoin(coinFile);

    this->priceColor = ColorCode::Red;
    this->titleColor = ColorCode::Blue;
    this->boarderColor = ColorCode::Yellow;

}

VendingMachine::~VendingMachine() 
{
    deleteStockList();
    deleteCoinList();
}

void VendingMachine::on()
{

    // Checking file compatibility
    // Check if coin list empty
    if (!(this->stockList->convertToStock(stockFile)) || \
         (this->coinList.size() == 0)                 ) {

        abort();
    }


}

void VendingMachine::toggleEnhancement() {

    // Save data.
    save();
    // Remove to create new type of list.
    deleteStockList();

    // Will change between single or double linked list
    // Essentially turning off/on enhancements
    if (this->enhancement) {
        stockList = new LinkedListSingle();
        this->enhancement = false;
    } else {
        stockList = new LinkedListDouble();
        this->enhancement = true; 
    }

    this->stockList->convertToStock(stockFile);
}

void VendingMachine::displayItems()
{

    // Check if enhancement turned on
    if (enhancement) {

        string input = "0";
        // User can decide
        //  - Ascending order
        //  - Decending order
        while (input != "3") {

            // Prompt
            cout << ColorOutPut::customString("Display Order:", this->titleColor, this->enhancement) << endl;
            cout << "   1. Ascending" << endl;
            cout << "   2. Descending" << endl;
            cout << "   3. Menu" << endl;
            cout << ColorOutPut::customString("Select your option (1-3): ", this->titleColor, this->enhancement);

            //Getting input
            input = Helper::readInput();
            //removes all whitespace from input
            input.erase(std::remove_if(input.begin(), input.end(), isspace), input.end());

            if (input == "1") {
                // Display Ascending
                this->stockList->printLL(this->enhancement);
                
            } else if (input == "2") {

                // Display Descending
                dynamic_cast<LinkedListDouble*>(this->stockList)->displayReverse(this->enhancement);
            }
        }

    } else {
        this->stockList->printLL(this->enhancement);
    }
}

bool VendingMachine::purchaseItems()
{

    bool return_value;
    
    // Message
    purchaseMsg();

    // Getting input
    string input = Helper::readInput();

    // Finding item of input
    Stock* item = this->stockList->findItem(input);

    // If invalid search
    if (item == nullptr){
        cout << ColorOutPut::customString("Invalid item!!!", ColorCode::Red, this->enhancement) << endl;
        cout << endl;
        return_value = false;
    }

    // If no stock left
    else if (item->on_hand < 1){
        cout << ColorOutPut::customString("item out of stock", ColorCode::Red, this->enhancement) << endl;
        return_value = false;
    }

    // Going through purchase proccess
    else{

        // Convert to cents
        int amount = (100 * item->price.dollars) + item->price.cents;

        // Change amount
        vector<int> newChange;
        string change;
        bool exit = false;

        // Output
        cout << std::fixed << std::setprecision(2);
        cout << "You have selected \"" << item->name << " - " << item->description;
        cout << "\". This will cost you ";
        cout << "$" << ColorOutPut::customPrice(amount * 0.01, this->priceColor, this->enhancement) << "." << endl;
        cout << "Please hand over the money - type in the value of each note/coins in cents." << endl;
        cout << ColorOutPut::customString("Please enter or ctrl-d on a new line to cancel this purchase:", \
        this->titleColor, this->enhancement) << endl;

        // Will exit until price paid or user leaves
        while (amount > 0 && !exit){

            // Informing user money not fully paid.
            cout << ColorOutPut::customString("You still need to give us $ ", this->titleColor, this->enhancement) \
            << ColorOutPut::customPrice((amount * 0.01f), this->priceColor, this->enhancement) + ": ";
            
            // Reading user input
            input = Helper::readInput();
            
            // Will exit if user simply presses enter
            if (input.empty()){
                exit = true;
            }

            // Will confirm if within denomination
            if (find(begin(Coin::coinDenomination),     \
                end(Coin::coinDenomination),            \
                input) != end(Coin::coinDenomination)){

                amount -= stoi(input);
                newChange.push_back(stoi(input));
            }

            //else if not proper denomination and contains non-numbers
            else if (exit == false && input.find_first_not_of("0123456789") != std::string::npos){
                cout << "Error: '" << input;
                cout << "' is not a valid denomination of money. Please try again." << endl;
            }
            //else if not proper denomination
            else if (exit == false){

                cout << "Error: $" << stoi(input) * 0.01;
                cout << " is not a valid denomination of money. Please try again." << endl;
            }
        }

        //if exit is true skip the else statement and return false
        if (exit == true){
            return_value = false;
        }
        else {
            // Calculating change (this will also change the coin List automatically if valid)
            // Updates coinlist
            change = Coin::getChange(coinList, newChange, amount);

            // Checking if possible to give change
            if (change == "-1"){

                cout << ColorOutPut::customString("insufficient coins available for correct change", \
                ColorCode::Red, this->enhancement) << endl;
                return_value = false;
            }

            // Change will be given if appropriate
            else {
                amount *= -1;

                cout << ColorOutPut::customString("Here is your ", ColorCode::Green, this->enhancement) << item->name;
                if (change != ":"){
                    cout << ColorOutPut::customString(" and your change of $", ColorCode::Green, this->enhancement) << \
                    ColorOutPut::customPrice(amount * 0.01, this->priceColor, this->enhancement) << change << endl;
                }
                else {
                    cout << "!" << endl;
                }
                item->on_hand--; 
                return_value = true;
            }
        }       
    }

    // Return if possible
    return return_value;
}

void VendingMachine::save() 
{
    // Saving to a file
    this->stockList->saveLL(stockFile);
    Coin::saveCoinFile(this->coinFile, this->coinList);
}

void VendingMachine::addItem() 
{

    // Creating stock string format [id]|[name]|[desc]|[price]|[count]
    string strStock = this->stockList->getNextAvailableID();
    vector<string> stockSplit;
    string input;
    bool exit = false;


    // display generated new id
    cout << "The id of the new stock will be: " << strStock << endl;

    // prompt and read the item name, description and price.
    cout << "Enter the item name: ";
    input = Helper::readInput();
    if (input.empty()){
        exit = true;
    }

    if (!exit){
        strStock += "|" + input;
        cout << "Enter the item description: ";
        input = Helper::readInput();
        if (input.empty()){
            exit = true;
        }
    }

    if (!exit){
        strStock += "|" + input;
        cout << "Enter the price for the item: ";
        input = Helper::readInput();
        if (input.empty()){
            exit = true;
        }
    }
    
    strStock += "|" + input;

    strStock += "|" + std::to_string(DEFAULT_STOCK_LEVEL);


    if (!exit){
        // Splitting stock format
        Helper::splitString(strStock, stockSplit, "|");
        vector<string> price;

        if (Helper::validStock(stockSplit)) {

            // Initiating stock
            Stock* addStock = new Stock();

            // Conversion for string to Price
            Price split;

            // Splitting the price into dollar and cent
            Helper::splitString(stockSplit[3], price, ".");

            // Conversion
            split.dollars = stoi(price[0]);
            split.cents = stoi(price[1]);

            // Editting stock
            addStock->id = stockSplit[0];
            addStock->name = stockSplit[1];
            addStock->description = stockSplit[2];
            addStock->price = split;
            addStock->on_hand = stoi(stockSplit[4]);

            // Adding to linkedlist
            this->stockList->addLL(addStock);

            //display success message
            cout << "This item \"" << addStock->name << " - " << addStock->description;
            cout << "\" has now been added to the menu." << endl;
        }
        else {
            
            // Invalid inputs
            cout << "Unsuccessful: Invalid stock inputs" << endl;
        }
    }
}

bool VendingMachine::removeItem()
{
    // Removing a file
    cout << "Enter the item id of the item to remove from the menu: ";
    string input = Helper::readInput();
    if (!(this->stockList->remove(input))) {
        cout << "Invalid ID" << endl;
    }

    return true;
}

void VendingMachine::displayCoins()
{
    //string cointaining empty spaces for formatting purposes
    string formatting_spaces[8];
    int count_digits;

    //iterate through every coin
    for (int i = 0; i < 8; i++){
        //get the num of digits for the coin's count
        count_digits = std::to_string(coinList[7-i]->count).length();
        //create a new string of empty spaces depending on the number of digits of Coin.count
        string spaces(10 - count_digits, ' ');
        formatting_spaces[i] = spaces;
    }

    
    //display coins
    cout << ColorOutPut::customString("Coins Summary", this->titleColor, this->enhancement) << endl;
    cout << ColorOutPut::customString("-------------", this->boarderColor, this->enhancement) << endl;
    cout << "Denomination    " << ColorOutPut::customString("|", this->boarderColor, this->enhancement) << "    Count" << endl;
    cout << ColorOutPut::customString("---------------------------", this->boarderColor, this->enhancement) << endl;
    cout << "5 Cents         " << ColorOutPut::customString("|", this->boarderColor, this->enhancement) << formatting_spaces[7] << coinList[0]->count << endl;
    cout << "10 Cents        " << ColorOutPut::customString("|", this->boarderColor, this->enhancement)<< formatting_spaces[6] << coinList[1]->count << endl;
    cout << "20 Cents        " << ColorOutPut::customString("|", this->boarderColor, this->enhancement)<< formatting_spaces[5] << coinList[2]->count << endl;
    cout << "50 Cents        " << ColorOutPut::customString("|", this->boarderColor, this->enhancement)<< formatting_spaces[4] << coinList[3]->count << endl;
    cout << "1 Dollar        " << ColorOutPut::customString("|", this->boarderColor, this->enhancement)<< formatting_spaces[3] << coinList[4]->count << endl;
    cout << "2 Dollars       " << ColorOutPut::customString("|", this->boarderColor, this->enhancement)<< formatting_spaces[2] << coinList[5]->count << endl;
    cout << "5 Dollars       " << ColorOutPut::customString("|", this->boarderColor, this->enhancement)<< formatting_spaces[1] << coinList[6]->count << endl;
    cout << "10 Dollars      " << ColorOutPut::customString("|", this->boarderColor, this->enhancement)<< formatting_spaces[0] << coinList[7]->count << endl;

    // for (Coin* c:this->coinList) {
    //     cout << "denomination: " << c->getDenomination() << ", Amount: " << c->count << std::endl;
    // }
    

}

void VendingMachine::resetStock()
{

    // Reset stock to defualt value
    this->stockList->resetStock();
}

void VendingMachine::resetCoins()
{
    //Reset all coins to default value
    Coin::resetCoins(coinList);
}

void VendingMachine::purchaseMsg()
{
    cout << "Purchase Item" << endl;
    cout << "-------------" << endl;
    cout << "Please enter the id of the item you wish to purchase: ";
}

void VendingMachine::optionMenu()
{
    cout << ColorOutPut::customString("Main Menu:", this->titleColor, this->enhancement) << endl;
    cout << "   1.Display Items" << endl;
    cout << "   2.Purchase Items" << endl;
    cout << "   3.Save and Exit" << endl;
    cout << ColorOutPut::customString("Administrator-Only Menu:", this->titleColor, this->enhancement) << endl;
    cout << "   4.Add Item" << endl;
    cout << "   5.Remove Item" << endl;
    cout << "   6.Display Coins" << endl;
    cout << "   7.Reset Stock" << endl;
    cout << "   8.Reset Coins" << endl;
    if (enhancement) {
        cout << "   9.Enhancement: " << ColorOutPut::customString("On", ColorCode::Green, true)<< endl;
    } else {
        cout << "   9.Enhancement: " << ColorOutPut::customString("Off", ColorCode::Red, true)<< endl;
    }
    cout << "   10.Abort Program" << endl;
    cout << ColorOutPut::customString("Select your option (1-10): ", this->titleColor, this->enhancement);
}

void VendingMachine::deleteStockList()
{
    // Will delete all data in linkedlist
    delete stockList;
}

void VendingMachine::deleteCoinList()
{
    // Loop through
    for (Coin* c: this->coinList) {

        // Delete all data
        delete c;
    }
    
}

 void VendingMachine::abort() 
 {
    delete this;
 }