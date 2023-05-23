#include "LinkedListSingle.h"

using std::vector;
using std::string;

NodeS::NodeS(Stock* stock){
    data = stock;
    next = nullptr;
};
NodeS::~NodeS(){
    delete data;
};

LinkedListSingle::LinkedListSingle() {

    // Empty Linkedlist
    head = nullptr;
    count = 0;
}

LinkedListSingle::~LinkedListSingle() {

    // Will release memory
    deleteLL();
}

bool LinkedListSingle::addLL(Stock* stock) {

    bool add = false;

    // Creating node on the heap
    Node* node = new NodeS(stock);

    // Check if empty
    if (head == nullptr) {
        head = node;
        add = true;
    }

    // Used for ordering
    Node* beforeNode = nullptr;
    Node* tempNode = head;

    // If the head data name is less, it will prepend data.
    if ((!add) && (tempNode->data->name >= node->data->name)) {
        head = node;
        head->next = tempNode;
        add = true;
    } 


    // Will insert node in correct spot
    while ((!add) && (tempNode->next != nullptr)) {
        beforeNode = tempNode;
        tempNode = tempNode->next;

        // Comparing in lower case
        if (Helper::convertLowerCase(tempNode->data->name) \
            >= Helper::convertLowerCase(node->data->name)) {

            beforeNode->next = node;
            node->next = tempNode;
            add = true;
        }
    }
    

    if (!add) {
        // Will append node at the back
        tempNode->next = node;
        add = true;
    }

    return add;
}


bool LinkedListSingle::remove(std::string id) {

    Node* node = head;
    Node* beforeNode = nullptr;
    bool found = false;

    // Checking head
    if (node->data->id == id) {
        std::cout << "\"" << id << " - " << node->data->name << " - " <<        \
                     node->data->description << "\" has been removed from the system." << std::endl;
        head = node->next;
        delete node;
        found = true;

    }

    // Looping through list
    while ((!found) && (node->next != nullptr)){

        beforeNode = node;
        node = node->next;

        // Checking node ID
        if (node->data->id == id) {

            // Printing the node data
            std::cout << id << " - " << node->data->name << " - " <<    \
                         node->data->description << std::endl;

            // Confirmation if found
            found = true;

            // Removing node
            beforeNode->next = node->next;

            // Freeing memory
            delete node;
        }
    }

    // boolean
    return found;

}

