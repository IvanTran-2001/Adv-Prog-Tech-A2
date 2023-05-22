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

bool LinkedListSingle::convertToStock(std::string fileName) {

    std::cout << "\nLoading Stock File: "<< "\'" << fileName << "\'" << std::endl;
    string line;

    // Used to construct Stock objects
    vector<string> item;
    vector<string> price;

    // Reading file
    std::ifstream readFile;

    // Opening file
    readFile.open(fileName);

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

    std::cout << "Closing Stock File: "<< "\'" << fileName << "\'\n" << std::endl;

    return validFile;
}

bool LinkedListSingle::addLL(Stock* stock) {


    bool add = false;

    // Creating node on the heap
    NodeS* node = new NodeS(stock);

    // Check if empty
    if (head == nullptr) {
        head = node;
        add = true;
    }

    // Used for ordering
    NodeS* beforeNode = nullptr;
    NodeS* tempNode = head;

    // If the head data name is less, it will prepend data.
    if ((!add) && (tempNode->data->name >= node->data->name)) {
        head = node;
        head->next = tempNode;
        add = true;
    }

    // Will insert node in correct spot
    while (!add && (tempNode->next != nullptr)) {

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


Stock* LinkedListSingle::findItem(string id){

    
    NodeS* node = head;
    Stock* stock = nullptr;

    // Looping through list
    while ((stock == nullptr) && (node != nullptr)){

        // Matching ID
        if (node->data->id == id){
            stock = node->data;

        }
        
        node = node->next;
    }
    
    // Will return null
    return stock;
}

void LinkedListSingle::saveLL(std::string filename){


    std::ofstream outfile;
    outfile.open(filename);

    // If file does not open
    NodeS* node = head;
    Stock* stock;

    // Loop through list
    while (node != nullptr) {

        // Getting node data
        stock = node->data;

        // Cents needs to be double digit
        string zeroCent = std::to_string(stock->price.cents);

        if (stock->price.cents < 10) {
            zeroCent = "0"+zeroCent;
        }

        // Formatting and writing data
        outfile << stock->id << "|" << stock->name << "|" \
                << stock->description << "|" << stock->price.dollars << "."
                << zeroCent << "|" << stock->on_hand << std::endl;

        // Next node
        node = node->next;


    }

    // close file
    outfile.close();
}

bool LinkedListSingle::remove(std::string id) {

    NodeS* node = head;
    NodeS* beforeNode = nullptr;
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
    while ((node->next != nullptr) && (!found)){

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


void LinkedListSingle::resetStock() {

    NodeS* node = head;

    // Replacing all "on_hand" variable to default stock level
    while (node != nullptr) {

        node->data->on_hand = DEFAULT_STOCK_LEVEL;

        // Next Node
        node = node->next;
    }

    // Output statement
    std::cout << "All stock has been reset to the default level of " \
              << DEFAULT_STOCK_LEVEL << std::endl;
}

void LinkedListSingle::deleteLL()
{

    NodeS* afterNode;

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

string LinkedListSingle::getNextAvailableID(){

    NodeS* node = head;
    vector<int> sortedID;
    string id;

    // Creating a list of IDs
    while (node != nullptr) {
        id = node->data->id;
        sortedID.push_back(std::stoi(id.substr(1, 4)));
        node = node->next;
    }

    // Sorting the ID
    std::sort(sortedID.begin(), sortedID.end());


    bool found = false;
    int i = 0;
    int beforeID = 0;
    int listLen = sortedID.size();
    int maxID = -1;

    // Will find if there is a gap between IDs
    while ((i < listLen) && !found)
    {
        // Find a gap between ID numbers
        if (sortedID[i] - beforeID > 1) {
            id = std::to_string(beforeID + 1);

            // Will stop Loop
            found = true;
        } else {
            beforeID = sortedID[i];
            if (maxID < sortedID[i]) {
                maxID = sortedID[i];
            }
        }
        i += 1;
    }
    
    // If a gap is found
    if (!found) {
        id = std::to_string(maxID + 1);
    }

    // Find the needed amount of Zeroes
    int num_digits = id.length();
    string zeroes(4 - num_digits, '0');
    
    // Creating ID
    id = "I" + zeroes + id;
    
    return id;
}