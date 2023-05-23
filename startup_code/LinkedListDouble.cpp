#include "LinkedListDouble.h"

using std::vector;
using std::string;

NodeD::NodeD(Stock* stock){
    data = stock;
    next = nullptr;
    prev = nullptr;
};
NodeD::~NodeD(){
    delete data;
};

LinkedListDouble::LinkedListDouble() {

    // Empty Linkedlist
    head = nullptr;
    tail = nullptr;
    count = 0;
}

LinkedListDouble::~LinkedListDouble() {

    // Will release memory
    deleteLL();
}

bool LinkedListDouble::addLL(Stock* stock) {

    bool add = false;

    // Creating node on the heap
    Node* node = new NodeD(stock);

    // Check if empty
    if (head == nullptr) {
        head = node;
        tail = node;
        add = true;
    }
    NodeD* tempNode = dynamic_cast<NodeD*>(head);

    // If the head data name is less, it will prepend data.
    if ((!add) && (tempNode->data->name >= node->data->name)) {
        head = node;
        head->next = tempNode;
        tempNode->prev = node;
        add = true;
    } 


    // Will insert node in correct spot
    while ((!add) && (tempNode->next != nullptr)) {

        tempNode = dynamic_cast<NodeD*>(tempNode->next);

        // Comparing in lower case
        if (Helper::convertLowerCase(tempNode->data->name) \
            >= Helper::convertLowerCase(node->data->name)) {
            
            tempNode->prev->next = node;
            node->next = tempNode;
            dynamic_cast<NodeD*>(node)->prev = tempNode->prev;
            tempNode->prev = node;

            add = true;
        }
    }
    

    if (!add) {
        // Will append node at the back
        tempNode->next = node;
        dynamic_cast<NodeD*>(node)->prev = tempNode;
        tail = node;
        add = true;
    }

    return add;
}


bool LinkedListDouble::remove(std::string id) {

    NodeD* node = dynamic_cast<NodeD*>(head);
    bool found = false;

    // Checking head
    if (node->data->id == id) {
        std::cout << "\"" << id << " - " << node->data->name << " - " <<        \
                     node->data->description << "\" has been removed from the system." << std::endl;
        delete head;
        head = node->next;
        found = true;

    }

    // Looping through list
    while ((!found) && (node->next != nullptr)){

        node = dynamic_cast<NodeD*>(node->next);

        // Checking node ID
        if (node->data->id == id) {

            // Printing the node data
            std::cout << "\"" << id << " - " << node->data->name << " - " <<        \
                     node->data->description << "\" has been removed from the system." << std::endl;

            // Removing node from list
            node->prev->next = node->next;

            // Confirmation if found
            found = true;

            

            // Freeing memory
            delete node;
        }
    }

    // boolean
    return found;

}

void LinkedListDouble::displayReverse(bool enhance) {

    ColorCode boarder = ColorCode::Yellow;
    // Formatting linked list
    std::cout << "Items Menu " <<  ColorOutPut::customString("|", boarder, enhance) << " Ascending Order" << std::endl;
    std::cout << ColorOutPut::customString("-------------------------------------------------------------------" , boarder, enhance)<< std::endl;
    std::cout << "ID   " << ColorOutPut::customString("|", boarder, enhance) << "Name                                    " << ColorOutPut::customString("|", boarder, enhance) << " Available "<< \
    ColorOutPut::customString("|", boarder, enhance) << " Price" << std::endl;
    std::cout << ColorOutPut::customString("-------------------------------------------------------------------", boarder, enhance) << std::endl;

    Stock* stock;
    NodeD* node = dynamic_cast<NodeD*>(tail);

    while (node != nullptr){
        
        // Getting data
        stock = node->data;

        printOne(*stock, enhance, boarder);
        
        //Next node
        node = dynamic_cast<NodeD*>(node->prev);
    } 

    std::cout << std::endl;

}
