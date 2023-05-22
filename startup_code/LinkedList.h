#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Helper.h"


class LinkedList
{
public:

    virtual ~LinkedList() {}

    // Print linkedlist in a format
    virtual void printLL();

    // Find an item within list
    virtual Stock* findItem(std::string id);

    // Saving list in a format as a file
    virtual void saveLL(std::string filename);

    // Reset all stock on hand by default value
    virtual void resetStock();

    // Removing a stock by id
    virtual bool remove(std::string id) = 0;

    // Adding a stock to the list in proper order
    virtual bool addLL(Stock* stock) = 0;

    // Converting stock file to stock list
    virtual bool convertToStock(std::string fileName);

    // freeing memory
    virtual void deleteLL();

    // Get next ID
    virtual std::string getNextAvailableID() = 0;

    Node* head;

};

#endif  // LINKEDLIST_H
