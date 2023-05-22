#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Helper.h"


class LinkedList
{
public:

    // Print linkedlist in a format
    virtual void printLL() = 0;

    // Find an item within list
    virtual Stock* findItem(std::string id) = 0;

    // Saving list in a format as a file
    virtual void saveLL(std::string filename) = 0;

    // Reset all stock on hand by default value
    virtual void resetStock() = 0;

    // Removing a stock by id
    virtual bool remove(std::string id) = 0;

    // Adding a stock to the list in proper order
    virtual bool addLL(Stock* stock) = 0;

    // Converting stock file to stock list
    virtual bool convertToStock(std::string fileName) = 0;

    // freeing memory
    virtual void deleteLL() = 0;

    // Get next ID
    std::string getNextAvailableID();

};

#endif  // LINKEDLIST_H
