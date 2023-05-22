#ifndef LINKEDLIST_DOUBLE_H
#define LINKEDLIST_DOUBLE_H

#include "Helper.h"
#include "LinkedListDouble.h"

/**
 * the node that holds the data about an item stored in memory
 **/
class Node
{
public:

    Node(Stock* stock);
    ~Node();
    // pointer to the data held for the node 
    Stock* data;
    // pointer to the next node in the list 
    Node* next;
    Node* prev;
};


class LinkedList : public LinkedList 
{
public:
    LinkedList();
    ~LinkedList();

    // Print linkedlist in a format
    void printLL();

    // Find an item within list
    Stock* findItem(std::string id);

    // Saving list in a format as a file
    void saveLL(std::string filename);

    // Reset all stock on hand by default value
    void resetStock();

    // Removing a stock by id
    bool remove(std::string id);

    // Adding a stock to the list in proper order
    bool addLL(Stock* stock);

    // Converting stock file to stock list
    bool convertToStock(std::string fileName);

    // freeing memory
    void deleteLL();

    // Get next ID
    std::string getNextAvailableID();

private:

    // the beginning of the list
    Node* head;
    Node* tail;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_DOUBLE_H
