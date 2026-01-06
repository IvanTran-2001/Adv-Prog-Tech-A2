#ifndef COIN_H
#define COIN_H

#include "Helper.h"

/**
 * @file Coin.h
 * @brief Coin and currency denomination management
 * 
 * Manages currency operations:
 * - 8 coin denominations ($0.01, $0.05, $0.10, $0.20, $0.50, $1.00, $2.00, $5.00)
 * - Change calculation using greedy algorithm
 * - Coin inventory tracking
 * - File persistence for coin data
 */

#define DELIM ","  ///< Delimiter for parsing coin files

/**
 * @enum Denomination
 * @brief Currency denominations available in the system
 * 
 * 8 denominations to provide flexibility in change-making:
 * - FIVE_CENTS (5¢)
 * - TEN_CENTS (10¢)
 * - TWENTY_CENTS (20¢)
 * - FIFTY_CENTS (50¢)
 * - ONE_DOLLAR ($1.00)
 * - TWO_DOLLARS ($2.00)
 * - FIVE_DOLLARS ($5.00)
 * - TEN_DOLLARS ($10.00) [for large denominations]
 * 
 * Ordered by value (smallest to largest) for greedy change algorithm.
 */
enum Denomination {
    FIVE_CENTS,
    TEN_CENTS,
    TWENTY_CENTS,
    FIFTY_CENTS,
    ONE_DOLLAR,
    TWO_DOLLARS,
    FIVE_DOLLARS,
    TEN_DOLLARS
};

/**
 * @class Coin
 * @brief Represents a currency denomination and its inventory count
 * 
 * Each Coin object tracks:
 * - Denomination type (what value coin/note it is)
 * - Count (how many of this denomination are in the machine)
 * 
 * Provides static utility methods for:
 * - Loading coins from file
 * - Change calculation
 * - Coin inventory management
 * - Saving coins back to file
 * 
 * Example:
 * Coin fiveDollarCoin("5", "20"); // 20 five-dollar notes in register
 */
class Coin {

 public:
    // ==================== Static Data ====================
    
    /// Maps denomination enum to string names ("5¢", "$1.00", etc.)
    static const std::vector<std::string> coinDenomination;

    // ==================== Constructor ====================
    
    /**
     * @brief Constructor
     * @param s Denomination string (e.g., "5", "20", "100", "200", "500", "1000", "5000", "10000" in cents)
     * @param amount Count of this denomination in inventory
     */
    Coin(std::string s, std::string amount);

    // ==================== Data ====================
    
    Denomination denom;  ///< The denomination type
    unsigned count;      ///< How many of this coin/note in inventory

    // ==================== File I/O ====================
    
    /**
     * @brief Load coin inventory from file
     * @param fileName Path to coins.dat
     * @return Vector of Coin objects, one per denomination
     * 
     * File format: denomination_value_cents,count (one per line)
     * Example:
     * 5,50        // 50 five-cent coins
     * 10,40       // 40 ten-cent coins
     * 100,25      // 25 one-dollar coins
     */
    static std::vector<Coin*> convertToCoin(std::string fileName);

    /**
     * @brief Save coin inventory back to file
     * @param fileName Path to coins.dat
     * @param coins Vector of Coin objects
     * 
     * Writes current coin counts to file in same format as convertToCoin()
     */
    static void saveCoinFile(std::string fileName, std::vector<Coin*> coins);

    // ==================== Change Calculation ====================
    
    /**
     * @brief Calculate change using greedy algorithm
     * @param coins Available coin denominations
     * @param newChange Output: array of change amounts (modified by this function)
     * @param amount Change needed in cents
     * @return String representation of change breakdown, or error message if insufficient coins
     * 
     * Greedy algorithm:
     * 1. Start with largest denomination
     * 2. Use as many of that denomination as possible
     * 3. Move to next smaller denomination
     * 4. Repeat until change is fully made or coins run out
     * 
     * Example: $2.85 change
     * - Use 1 x $2 = 50¢ remaining
     * - Use 0 x $1 = 50¢ remaining
     * - Use 1 x 20¢ = 30¢ remaining
     * - Use 1 x 10¢ = 20¢ remaining
     * - Use 4 x 5¢ = 0¢ done
     */
    static std::string getChange(std::vector<Coin*> coins, std::vector<int>& newChange, int amount);

    /**
     * @brief Update coin inventory counts
     * @param coinsCount Array of counts indexed by denomination
     * @param coins Vector of Coin objects to update
     * 
     * After transaction, updates coin counts based on what was given as change.
     * Increments machine's coin supply for payment received,
     * decrements for change given out.
     */
    static void updateCoins(unsigned coinsCount[], std::vector<Coin*> coins);

    // ==================== Utility ====================
    
    /**
     * @brief Get string representation of denomination
     * @return String like "5¢", "$1.00", "$5.00", etc.
     */
    std::string getDenomination() const;

    static void resetCoins(std::vector<Coin*> coins);
};

#endif // COIN_H
