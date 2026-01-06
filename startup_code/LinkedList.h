#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Helper.h"

/**
 * @file LinkedList.h
 * @brief Abstract base class for linked list implementations
 * 
 * Defines the interface that both singly and doubly-linked list implementations
 * must follow. This abstraction allows the VendingMachine to work with either
 * implementation interchangeably.
 */

/**
 * @class LinkedList
 * @brief Abstract base class for stock inventory management
 * 
 * Provides common functionality for both single and doubly-linked lists:
 * - Sorted insertion (alphabetically by item name)
 * - Search and removal by ID
 * - File I/O and persistence
 * - Display with formatting options
 * - Memory management
 * 
 * Concrete implementations:
 * - LinkedListSingle: Singly-linked version (simpler, less memory)
 * - LinkedListDouble: Doubly-linked version (supports reverse traversal)
 */
class LinkedList {
 public:
    virtual ~LinkedList() {}

    // ==================== Display Operations ====================
    
    /**
     * @brief Print the entire linked list
     * @param enhance Whether to use color/formatting enhancements
     * 
     * Displays all stock items in sorted order with details.
     * If enhance is true, uses formatted colors and alignment.
     */
    virtual void printLL(bool enhance);

    /**
     * @brief Print a single stock item with formatting
     * @param stock The stock item to display
     * @param enhance Whether to use color/formatting
     * @param b Color code for borders/separators
     * 
     * Displays item ID, name, description, price, and quantity.
     * Used by printLL() to format individual items.
     */
    virtual void printOne(Stock& stock, bool enhance, ColorCode b);

    // ==================== Search & Retrieval ====================
    
    /**
     * @brief Find and return a stock item by ID
     * @param id The item ID to search for
     * @return Pointer to the Stock object, or nullptr if not found
     * 
     * Traverses the list comparing item IDs.
     * Used during purchase and admin operations.
     */
    virtual Stock* findItem(std::string id);

    // ==================== File I/O ====================
    
    /**
     * @brief Save the entire inventory to a file
     * @param filename Path to the output file
     * 
     * Writes stock data in format: ID,Name,Description,Price,Quantity
     * Called by VendingMachine::save()
     */
    virtual void saveLL(std::string filename);

    /**
     * @brief Load stock from file and populate the list
     * @param fileName Path to the stock data file
     * @return true if loaded successfully, false on error
     * 
     * Reads file line by line, parses each item, and inserts
     * into the list maintaining alphabetical order.
     * Called during machine initialization.
     * 
     * File format:
     * ID,Name,Description,Price_cents,Quantity
     * I001,Donut,Glazed donut,199,15
     */
    virtual bool convertToStock(std::string fileName);

    // ==================== Modification ====================
    
    /**
     * @brief Remove a stock item by ID
     * @param id The item ID to remove
     * @return true if removed, false if not found
     * 
     * Finds and removes the item, freeing its memory.
     * Pure virtual - must be implemented by subclasses.
     */
    virtual bool remove(std::string id) = 0;

    /**
     * @brief Add a stock item to the list in sorted order
     * @param stock Pointer to the Stock object to add
     * @return true if added successfully
     * 
     * Inserts item maintaining alphabetical order by name.
     * Pure virtual - must be implemented by subclasses.
     */
    virtual bool addLL(Stock* stock) = 0;

    /**
     * @brief Reset all stock quantities to default level
     * 
     * Restores on_hand to DEFAULT_STOCK_LEVEL for all items.
     */
    virtual void resetStock();

    // ==================== Memory Management ====================
    
    /**
     * @brief Delete the entire list and free all memory
     * 
     * Traverses the list and deletes all nodes and their stock data.
     * Called during list switching or shutdown.
     */
    virtual void deleteLL();

    /**
     * @brief Get the next available item ID
     * @return String ID (format: "I###")
     * 
     * Scans existing items and returns next sequential ID.
     * Used when adding new items.
     */
    virtual std::string getNextAvailableID();

    // ==================== Protected Data ====================
    
    Node* head;  ///< Pointer to first node (nullptr if empty)
};

#endif  // LINKEDLIST_H
