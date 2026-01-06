#ifndef LINKEDLIST_SINGLE_H
#define LINKEDLIST_SINGLE_H

#include "Helper.h"
#include "LinkedList.h"

/**
 * @file LinkedListSingle.h
 * @brief Singly-linked list implementation for stock inventory
 * 
 * Simple linked list where each node only points forward (to next).
 * Provides all base LinkedList functionality with minimal memory overhead.
 * 
 * Used when users toggle off the enhancement feature, preferring
 * a simpler, more memory-efficient data structure.
 */

/**
 * @class LinkedListSingle
 * @brief Singly-linked list for managing vending machine stock
 * 
 * Features:
 * - Linear traversal only (forward via next pointers)
 * - Maintains sorted order (alphabetical by item name)
 * - O(n) insertion and removal
 * - Lower memory cost than doubly-linked
 * 
 * Trade-offs:
 * - Cannot traverse backward
 * - No displayReverse() functionality
 * - Slightly faster for forward operations only
 * 
 * Supports the enhancement feature: users can toggle between
 * LinkedListSingle (simpler) and LinkedListDouble (reverse capable).
 */
class LinkedListSingle : public LinkedList {
 public:
    /**
     * @brief Constructor
     * 
     * Initializes empty singly-linked list with:
     * - head = nullptr
     */
    LinkedListSingle();
    
    /**
     * @brief Destructor
     * 
     * Calls deleteLL() to free all nodes and stock data.
     */
    virtual ~LinkedListSingle();

    // ==================== Core Operations ====================
    
    /**
     * @brief Remove a stock item by ID
     * @param id The item ID to remove
     * @return true if removed, false if not found
     * 
     * Traverses list to find matching ID, removes node,
     * updates next pointers, and frees memory.
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
     * 1. Empty list: Insert at head
     * 2. Insert before current head
     * 3. Insert in middle or at end
     */
    virtual bool addLL(Stock* stock);

private:
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_SINGLE_H