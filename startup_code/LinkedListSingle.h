#ifndef LINKEDLIST_SINGLE_H
#define LINKEDLIST_SINGLE_H

#include "Helper.h"
#include "LinkedList.h"
/**
 * the node that holds the data about an item stored in memory
 **/
class NodeS : public Node
{
public:

    NodeS(Stock* stock);
    ~NodeS();
    // pointer to the data held for the node 
    Stock* data;
    // pointer to the next node in the list 
    NodeS* next;
};


class LinkedListSingle : public LinkedList
{
public:
    LinkedListSingle();
    virtual ~LinkedListSingle();

    // Print linkedlist in a format
    virtual void printLL();

    // Find an item within list
    virtual Stock* findItem(std::string id);

    // Saving list in a format as a file
    virtual void saveLL(std::string filename);

    // Reset all stock on hand by default value
    virtual void resetStock();

    // Removing a stock by id
    virtual bool remove(std::string id);

    // Adding a stock to the list in proper order
    virtual bool addLL(Stock* stock);

    // Converting stock file to stock list
    virtual bool convertToStock(std::string fileName);

    // freeing memory
    virtual void deleteLL();

    // Get next ID
    virtual std::string getNextAvailableID();

private:

    // the beginning of the list
    NodeS* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_SINGLE_H