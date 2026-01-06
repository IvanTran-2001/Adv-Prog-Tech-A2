#ifndef LINKEDLIST_DOUBLE_H
#define LINKEDLIST_DOUBLE_H

#include "Helper.h"
#include "LinkedList.h"

/**
 * @file LinkedListDouble.h
 * @brief Doubly-linked list implementation for stock inventory
 * 
 * Extends the abstract LinkedList with backward traversal capability.
 * This enables the enhancement feature: displaying items in ascending
 * or descending order.
 */

/**
 * @class LinkedListDouble
 * @brief Doubly-linked list for managing vending machine stock
 * 
 * Features:
 * - Bidirectional traversal (forward via next, backward via prev)
 * - Maintains sorted order (alphabetical by item name)
 * - O(n) insertion and removal
 * - O(1) head and tail access
 * 
 * Key difference from singly-linked:
 * - Allows displayReverse() for descending order viewing
 * - Uses prev pointers (higher memory cost)
 * - Maintains tail pointer for O(1) append operations
 * 
 * Perfect for the enhancement feature that lets users
 * view inventory in ascending or descending order.
 */
class LinkedListDouble : public LinkedList {
 public:
    /**
     * @brief Constructor
     * 
     * Initializes empty doubly-linked list with:
     * - head = nullptr
     * - tail = nullptr
     * - count = 0
     */
    LinkedListDouble();
    
    /**
     * @brief Destructor
     * 
     * Calls deleteLL() to free all nodes and stock data.
     */
    virtual ~LinkedListDouble();

    // ==================== Core Operations ====================
    
    /**
     * @brief Remove a stock item by ID
     * @param id The item ID to remove
     * @return true if removed, false if not found
     * 
     * Finds the node by ID, removes it from the list,
     * and frees its memory. Updates prev/next pointers
     * to maintain list integrity.
     */
    virtual bool remove(std::string id);

    /**
     * @brief Add a stock item maintaining alphabetical order
     * @param stock Pointer to the Stock object to add
     * @return true if added successfully
     * 
     * Finds correct position by comparing item names
     * (case-insensitive) and inserts node there.
     * 
     * Handles three cases:
     * 1. Empty list: Insert at head (and tail)
     * 2. Insert before current head
     * 3. Insert in middle or at end
     */
    virtual bool addLL(Stock* stock);

    // ==================== Enhancement Feature ====================
    
    /**
     * @brief Display inventory in reverse (descending) order
     * @param enhance Whether to use color/formatting
     * 
     * Traverses list backward from tail using prev pointers.
     * Shows items in descending alphabetical order.
     * 
     * Used when user selects "2. Descending" in display menu.
     * Only available in LinkedListDouble, not in singly-linked version.
     */
    virtual void displayReverse(bool enhance);

 private:
    Node* tail;        ///< Pointer to last node (for efficient append)
    unsigned count;    ///< Number of nodes in list (optimization)
};

#endif  // LINKEDLIST_DOUBLE_H