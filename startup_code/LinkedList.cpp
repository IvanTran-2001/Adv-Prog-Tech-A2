#include "LinkedList.h"
using std::string;
using std::vector;

void LinkedList::printLL(bool enhance){

    // Formatting linked list
    std::cout << "Items Menu | Ascending Order" << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << "ID   |Name                                    | Available | Price" << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;

    Node* node = head;
    Stock* stock;
    int nameLength;
    int on_handLength;

    // 2 decimal places
    std::cout << std::fixed << std::setprecision(2);

    // Loop through list until null
    while (node != nullptr) {
        
        // Getting data
        stock = node->data;

        // The rest below is just formatting the data
        nameLength = stock->name.length();
        string nameSpaces(NAMELEN - nameLength, ' ');

        on_handLength = std::to_string(stock->on_hand).length();
        string availSpaces(11 - on_handLength, ' ');

        string price = "";

        if (stock->price.cents < 10) {
            price = std::to_string(stock->price.dollars) + "." \
                     + "0" + std::to_string(stock->price.cents);
        } else {
            price = std::to_string(stock->price.dollars) + "." \
                     + std::to_string(stock->price.cents);
        }

        price = ColorOutPut::customString(price, ColorCode::Red, enhance);

        std::cout << stock->id << "|" << stock->name << nameSpaces << "|" \
                  << stock->on_hand << availSpaces << "|$ " << price << std::endl;
        
        //Next node
        node = node->next;
    } 
    std::cout << std::endl;
}

bool LinkedList::convertToStock(std::string fileName) {

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

void LinkedList::resetStock() {

    Node* node = head;

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

Stock* LinkedList::findItem(string id){

    
    Node* node = head;
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

string LinkedList::getNextAvailableID(){

    Node* node = head;
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