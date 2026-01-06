#ifndef NODE_H
#define NODE_H

#include "Helper.h"

/**
 * @file Node.h
 * @brief Data structures for vending machine stock and nodes
 * 
 * Defines the fundamental data types:
 * - Price: Currency representation (avoids floating-point precision issues)
 * - Stock: Product information
 * - Node: Base class for linked list nodes
 * - NodeD: Doubly-linked node with prev pointer
 */

// ==================== Configuration Constants ====================

/// Maximum length of item ID (e.g., "I001")
#define IDLEN 5

/// Maximum length of product name
#define NAMELEN 40

/// Maximum length of product description
#define DESCLEN 255

/// Default coin count when resetting coin supply
#define DEFAULT_COIN_COUNT 20

/// Default stock quantity for new items or restocking
#define DEFAULT_STOCK_LEVEL 20

/// Number of coin denominations in the system (1¢, 5¢, 10¢, 20¢, 50¢, $1, $2, $5)
#define NUM_DENOMS 8

// ==================== Price Data Structure ====================

/**
 * @class Price
 * @brief Represents currency as discrete dollars and cents
 * 
 * Uses integer representation to avoid floating-point precision issues
 * that commonly occur with float/double when handling currency.
 * 
 * Example:
 * Price p; p.dollars = 2; p.cents = 99; // Represents $2.99
 */
class Price {
 public:
    unsigned dollars;  ///< Dollar amount (e.g., 2 for $2.99)
    unsigned cents;    ///< Cents amount (e.g., 99 for $2.99)
};

// ==================== Stock Data Structure ====================

/**
 * @class Stock
 * @brief Represents a product in the vending machine
 * 
 * Contains all information needed to identify, price, and track inventory
 * of a single product. Multiple instances are stored in the linked list.
 * 
 * Example:
 * Stock donut;
 * donut.id = "I001";
 * donut.name = "Donut";
 * donut.description = "Glazed donut";
 * donut.price = {1, 99}; // $1.99
 * donut.on_hand = 15;    // 15 items available
 */
class Stock {
 public:
    std::string id;           ///< Unique identifier (format: I###)
    std::string name;         ///< Product name (max NAMELEN chars)
    std::string description;  ///< Product description (max DESCLEN chars)
    Price price;              ///< Product price (no floating-point)
    unsigned on_hand;         ///< Current quantity in stock
};

// ==================== Node Base Class ====================

/**
 * @class Node
 * @brief Base class for singly-linked list nodes
 * 
 * Contains:
 * - next: Pointer to next node in the list
 * - data: Pointer to the Stock item this node contains
 * 
 * Used as the base class for all node types. Singly-linked nodes
 * only have a next pointer. Doubly-linked nodes extend this with prev.
 */
class Node {
 public:
    Node* next;  ///< Pointer to next node (nullptr if last node)
    Stock* data; ///< Pointer to the stock item stored in this node

    virtual ~Node() {}
};

// ==================== Doubly-Linked Node ====================

/**
 * @class NodeD
 * @brief Extended node for doubly-linked lists
 * 
 * Extends Node with:
 * - prev: Pointer to previous node for reverse traversal
 * 
 * Allows bidirectional traversal and reverse display of items.
 * Used in LinkedListDouble for enhancement feature.
 */
class NodeD : public Node {
 public:
    Node* prev;  ///< Pointer to previous node (nullptr if first node)
    
    /**
     * @brief Constructor
     * @param stock Pointer to the Stock object
     * 
     * Initializes node with stock data and nullptr pointers.
     */
    NodeD(Stock* stock);
    
    /**
     * @brief Destructor
     * 
     * Frees the Stock object (but not the next/prev pointers,
     * as they point to other nodes managed elsewhere).
     */
    ~NodeD();
};

#endif  // NODE_H