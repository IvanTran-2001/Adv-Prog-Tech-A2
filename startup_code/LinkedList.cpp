#include "LinkedList.h"

using std::vector;
using std::string;

LinkedList::LinkedList() {
    head = nullptr;
    count = 0;
}

LinkedList::~LinkedList() {
    // TODO
}

bool LinkedList::addLL(Stock* stock) {

    bool add = false;
    Node* node = new Node(stock);

    if (head == nullptr) {
        head = node;
        add = true;
        return add;
    }

    Node* beforeNode = nullptr;
    Node* tempNode = head;

    if (tempNode->data->name >= node->data->name) {
        head = node;
        head->next = tempNode;
        add = true;
        return add;
    }

    while (!add && (tempNode->next != nullptr)) {

        beforeNode = tempNode;
        tempNode = tempNode->next;

        if (tempNode->data->name >= node->data->name) {
            beforeNode->next = node;
            node->next = tempNode;
            add = true;
            return add;
        }
    }

    return add;
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

void LinkedList::saveLL(std::string filename){
    std::ofstream outfile;
    outfile.open(filename);

    if (!outfile.is_open()){
        std::cout << "Error: could not open file" << std::endl;
    }


    Node* node = head;
    Stock* stock;

    while (node != nullptr) {
        stock = node->data;

        outfile << stock->id << "|" << stock->name << "|" << stock->description << "|" << stock->price.dollars << "."
                << stock->price.cents << "|" << stock->on_hand << std::endl;

        node = node->next;
    }

    outfile.close();
}

bool LinkedList::remove(std::string id) {

    Node* node = head;
    Node* beforeNode = nullptr;
    bool found = false;

    if (node->data->id == id) {
        std::cout << id << " - " << node->data->name << " - " << node->data->description << std::endl;
        delete head->data;
        delete head;
        head = node->next;
        found = true;

    }

    while ((node->next != nullptr) && (!found)){
        beforeNode = node;
        node = node->next;

        if (node->data->id == id) {

            //std::cout << id << " - " << node->data->name << " - " << node->data->description << std::endl;

            found = true;
            beforeNode->next = node->next;
            delete node->data;
            delete node;
        }
    }

    return found;

}

void LinkedList::resetStock() {
    Node* node = head;
    while (node != nullptr) {
        node->data->on_hand = DEFAULT_STOCK_LEVEL;
        node = node->next;
    }

    //std::cout << "All stock has been reset to the default level of " << DEFAULT_STOCK_LEVEL << std::endl;
}