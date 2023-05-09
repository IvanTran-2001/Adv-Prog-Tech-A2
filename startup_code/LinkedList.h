#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Helper.h"

class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    void printLL();
    Stock* findItem(std::string id);
    void saveLL(std::string filename);
    void resetStock();
    bool remove(std::string id);
    bool addLL(Stock* stock);

private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H
