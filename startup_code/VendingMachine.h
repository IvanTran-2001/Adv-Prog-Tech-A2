#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include "Helper.h"
#include "LinkedList.h"
#include "LinkedListSingle.h"
#include "LinkedListDouble.h"
#include "Coin.h"

/**
 * @file VendingMachine.h
 * @brief Core vending machine system
 * 
 * VendingMachine is the receiver in the Command Pattern.
 * It manages all operations: stock, coins, file I/O, and transactions.
 * Supports dynamic switching between singly and doubly-linked list implementations.
 */

// Command option codes
#define DISPLAY_ITEMS "1"    ///< Display inventory
#define PURCHASE_ITEMS "2"   ///< Purchase an item
#define SAVE_EXIT "3"        ///< Save and exit
#define ADD_ITEM "4"         ///< Admin: Add item
#define REMOVE_ITEM "5"      ///< Admin: Remove item
#define DISPLAY_COINS "6"    ///< Display coin supply
#define RESET_STOCK "7"      ///< Admin: Reset inventory
#define RESET_COINS "8"      ///< Admin: Reset coins
#define ENHANCEMENT "9"      ///< Toggle list implementation
#define ABORT "10"           ///< Emergency shutdown

/**
 * @class VendingMachine
 * @brief Receiver class in Command Pattern - manages all vending operations
 * 
 * Manages:
 * - Stock inventory (using LinkedList abstraction)
 * - Coin supply and change calculation
 * - File persistence (stock.dat, coins.dat)
 * - User transactions
 * - UI colors and display modes
 */
class VendingMachine {

private:
    // ==================== Data Members ====================
    
    LinkedList* stockList;              ///< Abstraction for singly/doubly-linked list
    std::vector<Coin*> coinList;        ///< Available coin denominations
    
    std::string stockFile;              ///< Path to stock.dat
    std::string coinFile;               ///< Path to coins.dat
    bool enhancement;                   ///< Toggle for doubly-linked (true) vs singly-linked (false)
    
    ColorCode priceColor;               ///< Color for displaying prices
    ColorCode titleColor;               ///< Color for UI titles
    ColorCode numberColor;              ///< Color for numbers
    ColorCode boarderColor;             ///< Color for borders

public:
    // ==================== Lifecycle ====================
    
    /**
     * @brief Constructor
     * @param s Path to stock data file
     * @param c Path to coin data file
     * 
     * Initializes empty stock list (default doubly-linked for enhancement),
     * loads coins, and sets up display colors.
     */
    VendingMachine(std::string s, std::string c);
    
    /**
     * @brief Destructor
     * 
     * Frees all dynamically allocated memory:
     * - Stock list nodes
     * - Coin objects
     */
    ~VendingMachine();

    // ==================== Core Operations ====================
    
    /**
     * @brief Initialize the vending machine
     * 
     * Loads stock from file and validates data.
     * Calls abort() if files are invalid or coins are missing.
     */
    void on();

    /**
     * @brief Display all available items
     * 
     * Shows inventory in ascending or descending order (if enhancement enabled).
     * Allows users to browse products before purchase.
     */
    void displayItems();

    /**
     * @brief Handle a purchase transaction
     * @return true if transaction completed, false if aborted or failed
     * 
     * Process:
     * 1. User selects item ID
     * 2. User provides payment (multiple coin/note entries)
     * 3. Validate sufficient stock and payment
     * 4. Calculate change using greedy algorithm
     * 5. Update stock and coin supplies
     */
    bool purchaseItems();

    /**
     * @brief Save current state to files
     * 
     * Persists:
     * - Stock inventory to stockFile
     * - Coin supply to coinFile
     * 
     * Called before exit or at user request.
     */
    void save();

    // ==================== Admin Operations ====================
    
    /**
     * @brief Add new item to inventory
     * 
     * Prompts for:
     * - Item name
     * - Description
     * - Price (dollars and cents)
     * 
     * Auto-assigns ID and initializes to DEFAULT_STOCK_LEVEL quantity.
     */
    void addItem();

    /**
     * @brief Remove item from inventory by ID
     * @return true if removed, false if not found
     * 
     * Prompts for item ID, removes matching stock and frees memory.
     */
    bool removeItem();

    /**
     * @brief Display current coin supply
     * 
     * Shows count of each coin denomination available for making change.
     */
    void displayCoins();

    /**
     * @brief Reset stock to default levels
     * 
     * Restores all items to DEFAULT_STOCK_LEVEL quantity.
     * Useful for restocking after testing.
     */
    void resetStock();

    /**
     * @brief Reset coin supply to default levels
     * 
     * Restores all coin denominations to DEFAULT_COIN_COUNT.
     * Ensures sufficient coins for change-making operations.
     */
    void resetCoins();

    // ==================== Memory Management ====================
    
    /**
     * @brief Free stock list memory
     * 
     * Deletes all stock nodes and items.
     * Called before switching list implementations or during shutdown.
     */
    void deleteStockList();

    /**
     * @brief Free coin list memory
     * 
     * Deletes all coin objects.
     * Called during shutdown.
     */
    void deleteCoinList();

    // ==================== Enhancement Feature ====================
    
    /**
     * @brief Toggle between singly and doubly-linked list implementations
     * 
     * Enhancement feature allowing runtime switching:
     * - false (Singly-linked): Lower memory, linear traversal
     * - true (Doubly-linked): Can display items in ascending/descending order
     * 
     * Process:
     * 1. Save current data
     * 2. Delete old list
     * 3. Create new list type
     * 4. Reload data from file
     */
    void toggleEnhancement();

    /**
     * @brief Gracefully shutdown the machine
     * 
     * Saves state and exits the program.
     * Called on user request or fatal errors.
     */
    void abort();

    // ==================== UI Methods ====================
    
    /**
     * @brief Display main menu options
     * 
     * Shows all available operations (1-10)
     * with descriptions.
     */
    void optionMenu();
    
    /**
     * @brief Display purchase instruction message
     * 
     * Guides user through payment entry process.
     */
    void purchaseMsg();
};

#endif // VENDING_MACHINE_H
