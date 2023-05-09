#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"

#include <vector>

class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    // more functions to be added perhaps...
    void initialiseLL(std::vector<std::vector<std::string>>& items);
    void printLL();
    Stock* findItem(std::string id);
    void saveLL(std::string filename);
    void reset();
    bool remove(std::string id);

private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H
