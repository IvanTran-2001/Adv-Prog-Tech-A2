#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <algorithm> 
#include <cstring> 

#include "ColorOutPut.h"
#include "Node.h"
#include "Coin.h"

/**
 * @file Helper.h
 * @brief Utility functions for vending machine operations
 * 
 * Helper class provides static utility functions for:
 * - String parsing and manipulation
 * - Input/output operations
 * - File validation
 * - Exception handling
 * - Text formatting
 */

/**
 * @class Helper
 * @brief Collection of static utility functions
 * 
 * All methods are static (no instances created).
 * Private constructor prevents instantiation.
 */
class Helper {
 private:
    Helper();  ///< Private constructor - class not meant to be instantiated

 public:
    // ==================== String Operations ====================
    
    /**
     * @brief Split a string by delimiter
     * @param s The string to split
     * @param tokens Output: vector of substrings (cleared then filled)
     * @param delimeter The delimiter to split by
     * 
     * Example:
     * "I001,Donut,Glazed" with delimiter "," produces
     * tokens = ["I001", "Donut", "Glazed"]
     * 
     * Used for parsing stock.dat and coins.dat files.
     */
    static void splitString(std::string s, std::vector<std::string>& tokens, std::string delimeter);

    /**
     * @brief Convert string to lowercase
     * @param c The string to convert
     * @return Lowercase version of the string
     * 
     * Used when inserting items (comparison is case-insensitive).
     * Ensures "Apple" and "apple" are treated the same alphabetically.
     */
    static std::string convertLowerCase(std::string c);

    // ==================== Input/Output ====================
    
    /**
     * @brief Read user input from stdin
     * @return The user-entered string (trimmed)
     * 
     * Reads a line of input from the user.
     * Handles Ctrl-D for EOF gracefully.
     * Used throughout the program for all user prompts.
     */
    static std::string readInput();

    // ==================== File Validation ====================
    
    /**
     * @brief Validate stock file format
     * @param stock Vector of lines from stock.dat
     * @return true if valid, false if malformed
     * 
     * Validates:
     * - Correct number of comma-separated fields per line
     * - Valid price format (dollars and cents)
     * - Valid quantity values
     * - IDs follow format I###
     * 
     * Called during machine initialization to catch file corruption.
     */
    static bool validStock(std::vector<std::string> stock);

    /**
     * @brief Validate coin file format
     * @param coin Vector of lines from coins.dat
     * @return true if valid, false if malformed
     * 
     * Validates:
     * - Correct number of fields per line
     * - Valid denomination values
     * - Valid coin counts (non-negative)
     * 
     * Called during machine initialization to catch file corruption.
     */
    static bool validCoin(std::vector<std::string> coin);

    // ==================== Exception Handling ====================
    
    /**
     * @brief Throw and display an exception message
     * @param e The exception object
     * @param id Context identifier (e.g., item ID that caused error)
     * 
     * Generic exception handler for any exception type.
     * Displays the exception message with context to the user.
     * 
     * Example:
     * throwMessage(some_exception, "I001");
     */
    template<typename ExceptionType>
    static void throwMessage(const ExceptionType& e, std::string id);
};

#endif  // HELPER_H