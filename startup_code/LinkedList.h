#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Helper.h"
#include "Node.h"

class LinkedList
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

    std::string getNextAvailableID();

private:

    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H
