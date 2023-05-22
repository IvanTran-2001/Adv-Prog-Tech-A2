#ifndef LINKEDLIST_SINGLE_H
#define LINKEDLIST_SINGLE_H

#include "Helper.h"
#include "LinkedList.h"
/**
 * the node that holds the data about an item stored in memory
 **/
class NodeD : public Node
{
public:

    NodeD(Stock* stock);
    ~NodeD();
    // pointer to the data held for the node 
    Stock* data;
    // pointer to the next node in the list 
    NodeD* next;
    NodeD* prev;
};


class LinkedListDouble : public LinkedList
{
public:
    LinkedListDouble();
    virtual ~LinkedListDouble();

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
    NodeD* head;
    NodeD* tail;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_SINGLE_H