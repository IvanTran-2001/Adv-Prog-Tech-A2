#include "LinkedList.h"

using std::vector;
using std::string;

LinkedList::LinkedList() {

    // Empty Linkedlist
    head = nullptr;
    count = 0;
}

LinkedList::~LinkedList() {

    // Will release memory
    deleteLL();
}

bool LinkedList::convertToStock(std::string fileName) {

    string line;

    // Used to construct Stock objects
    LinkedList items;
    vector<string> item;
    vector<string> price;

    // Reading file
    std::ifstream readFile;

    // Opening file
    readFile.open(fileName);

    std::cout << "Loading Stock File: "<< "\'" << fileName << "\'" << std::endl;

    // If valid file
    bool validFile = true;

    // Looping for every line
    while (getline(readFile, line))
    {
        
        // Get user input
        Helper::splitString(line, item, "|");

        // If a valid line
        if (Helper::validStock(item)) 
        {
            // Intiating new Stock object on heap
            Stock* addStock = new Stock();

            // Conversion for string to Price
            Price split;

            // Splitting the price into dollar and cent
            Helper::splitString(item[3], price, ".");

            // Conversion
            split.dollars = stoi(price[0]);
            split.cents = stoi(price[1]);

            // Editting stock
            addStock->id = item[0];
            addStock->name = item[1];
            addStock->description = item[2];
            addStock->price = split;
            addStock->on_hand = stoi(item[4]);

            // Adding stock to linkedlist
            addLL(addStock);
        } else {

            validFile = false;
            
        }
    }

    readFile.close();

    return validFile;

}

bool LinkedList::addLL(Stock* stock) {


    bool add = false;

    // Creating node on the heap
    Node* node = new Node(stock);

    // Check if empty
    if (head == nullptr) {
        head = node;
        add = true;
        return add;
    }

    // Used for ordering
    Node* beforeNode = nullptr;
    Node* tempNode = head;

    // If the head data name is less, it will prepend data.
    if (tempNode->data->name >= node->data->name) {
        head = node;
        head->next = tempNode;
        add = true;
        return add;
    }

    // Will insert node in correct spot
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

    // Will append node
    tempNode->next = node;
    add = true;

    return add;
}

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

        string price = std::to_string(stock->price.dollars) + "." + std::to_string(stock->price.cents);


        std::cout << stock->id << "|" << stock->name << nameSpaces << "|" << stock->on_hand << availSpaces << "|$ " << price << std::endl;
        
        //Next node
        node = node->next;
    } 
}


Stock* LinkedList::findItem(string id){

    
    Node* node = head;
    Stock* stock = nullptr;

    // Looping through list
    while (node != nullptr){

        // Matching ID
        if (node->data->id == id){
            stock = node->data;

            // Return data
            return stock;
        }
        
        node = node->next;
    }
    
    // Will return null
    return stock;
}

void LinkedList::saveLL(std::string filename){


    std::ofstream outfile;
    outfile.open(filename);

    // If file does not open
    Node* node = head;
    Stock* stock;

    // Loop through list
    while (node != nullptr) {

        // Getting node data
        stock = node->data;

        // Formatting and writing data
        outfile << stock->id << "|" << stock->name << "|" << stock->description << "|" << stock->price.dollars << "."
                << stock->price.cents << "|" << stock->on_hand << std::endl;

        // Next node
        node = node->next;


    }

    // close file
    outfile.close();
}

bool LinkedList::remove(std::string id) {

    Node* node = head;
    Node* beforeNode = nullptr;
    bool found = false;

    // Checking head
    if (node->data->id == id) {
        std::cout << id << " - " << node->data->name << " - " << node->data->description << std::endl;
        delete head;
        head = node->next;
        found = true;

    }

    // Looping through list
    while ((node->next != nullptr) && (!found)){

        beforeNode = node;
        node = node->next;

        // Checking node ID
        if (node->data->id == id) {

            // Printing the node data
            std::cout << id << " - " << node->data->name << " - " << node->data->description << std::endl;

            // Confirmation if found
            found = true;

            // Removing node
            beforeNode->next = node->next;

            // Freeing memory
            delete node;
            return found;
        }
    }

    // boolean
    return found;

}


void LinkedList::resetStock() {

    Node* node = head;

    // Replacing all "on_hand" variable to default stock level
    while (node != nullptr) {

        node->data->on_hand = DEFAULT_STOCK_LEVEL;

        // Next Node
        node = node->next;
    }

    // Output statement
    std::cout << "All stock has been reset to the default level of " << DEFAULT_STOCK_LEVEL << std::endl;
}

void LinkedList::deleteLL()
{

    Node* afterNode;

    // Checking head exist
    if (head != nullptr) {
        afterNode = head->next;
    }

    // Loop
    while (head != nullptr) {

        // freeing node 
        delete head;

        // next node
        head = afterNode;

        // At the end of the list
        // Prevent null pointer using "next"
        if (afterNode != nullptr) {
            afterNode = head->next;
        }
    }
}