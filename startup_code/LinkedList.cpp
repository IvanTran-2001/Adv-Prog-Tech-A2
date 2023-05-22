#include "LinkedList.h"
using std::string;

void LinkedList::printLL(){

    // Formatting linked list
    std::cout << "Items Menu" << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << "ID   |Name                                    | Available | Price" << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;

    Node* node = head;
    Stock* stock;
    int nameLength;
    int on_handLength;

    // Loop through list until null
    while (node != nullptr){
        
        // Getting data
        stock = node->data;

        // The rest below is just formatting the data
        nameLength = stock->name.length();
        string nameSpaces(NAMELEN - nameLength, ' ');

        on_handLength = std::to_string(stock->on_hand).length();
        string availSpaces(11 - on_handLength, ' ');

        string price = std::to_string(stock->price.dollars) + "." \
                     + std::to_string(stock->price.cents);

        std::cout << stock->id << "|" << stock->name << nameSpaces << "|" \
                  << stock->on_hand << availSpaces << "|$ " << price << std::endl;
        
        //Next node
        node = node->next;
    } 
}