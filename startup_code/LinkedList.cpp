#include "LinkedList.h"
#include <vector>
#include <iostream>
using std::vector;
using std::string;

LinkedList::LinkedList() {
    head = nullptr;
    count = 0;
}

LinkedList::~LinkedList() {
    // TODO
}

void LinkedList::initialiseLL(vector<vector<string>>& items) {
    

    for (vector<vector<string>>::size_type i = 0; i < items.size(); i++){
        Stock* stock = new Stock;
        Price price;

        unsigned dollars = stoul(items[i][3]);
        unsigned cents = stoul(items[i][4]);
        price.dollars = dollars;
        price.cents = cents;

        stock->id = items[i][0];
        stock->name = items[i][1];
        stock->description = items[i][2];
        stock->price = price;
        stock->on_hand = stoul(items[i][5]);

        
        Node* node = new Node(stock);
        node->next = head;
        head = node;
    }
}

void LinkedList::printLL(){
    std::cout << "Items Menu" << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << "ID   |Name                                    | Available | Price" << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;

    Node* node = head;
    Stock* stock;
    int nameLength;
    int on_handLength;

    while (node != nullptr){
        
        stock = node->data;

        nameLength = stock->name.length();
        string nameSpaces(40 - nameLength, ' ');

        on_handLength = std::to_string(stock->on_hand).length();
        string availSpaces(11 - on_handLength, ' ');

        string price = std::to_string(stock->price.dollars) + "." + std::to_string(stock->price.cents);


        std::cout << stock->id << "|" << stock->name << nameSpaces << "|" << stock->on_hand << availSpaces << "|$ " << price << std::endl;
        
        node = node->next;
    } 
}


Stock* LinkedList::findItem(string id){
    Node* node = head;
    Stock* stock = nullptr;

    while (node != nullptr){
        if (node->data->id == id){
            stock = node->data;
        }
        
        node = node->next;
    }
    
    return stock;
}