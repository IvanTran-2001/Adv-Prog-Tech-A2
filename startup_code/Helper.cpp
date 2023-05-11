#include "Helper.h"

using std::string;
using std::vector;
using std::stoi;

Helper::Helper(){}

void Helper::splitString(string s, vector<string>& tokens, string delimeter)
{
    tokens.clear();
    char* _s = new char[s.length()+1];
    strcpy(_s, s.c_str());

    char * pch;
    pch = strtok (_s, delimeter.c_str());
    while (pch != NULL)
    {
        tokens.push_back(pch);
        pch = strtok (NULL, delimeter.c_str());
    }
    delete[] _s;
}


string Helper::readInput()
{

    // Getting user input as line
    string input;
    std::getline(std::cin, input);
    std::cout << std::endl;

    // Return string
    return input;
}


bool Helper::validStock(vector<string> stock, int line) 
{

    // Valid line
    bool valid = true;

        // Checking size of inputs
    if ((stock.size() != 5)) {

        // Too many inputs
        throwMessage(std::runtime_error("Wrong format: [ID] [NAME] [DESC] [PRICE] [COUNT]"), line);

        valid = false;

        // Check ID size
    } else if (stock[0].size() != IDLEN) {

        // Input size too long
        throwMessage(std::length_error("ID must be length of 5"), line);
        valid = false;

        // Check if ID start with 'I'
    } else if (stock[0][0] != 'I') {

        // Invalid Input
        throwMessage(std::invalid_argument("ID must start with \'I\'"), line);
        valid = false;

        // Check valid name size
    } else if ((stock[1].size() != NAMELEN)) {

        // Input size too long
        throwMessage(std::length_error("Name length must be within 40"), line);
        valid = false;

        // Check for description size
    } else if ((stock[2].size() != DESCLEN)) {
        
        // Input size too long        
        throwMessage(std::length_error("Description length must be within 255"), line);
        valid = false;
    }
    
    else {

        try {

            int count;
            // Convert to integer
            count = std::stoi(stock[4]);

            // If on hand is in the negatives
            if (count < 0) {
                
                throwMessage(std::domain_error("On hand cannot be negative"), line);
                valid = false;
            }

            // Will catch if out of range or invalid input
        } catch (const std::exception e) {

            if (line != -1) {
                std::cout << "Line " << line << ": " << std::endl;
            }
            // Tells us what the error is
            std::cout << "Exception caught: " << e.what() << std::endl;
            valid = false;

        }

        try {

            float price;
            // Convert to float
            price = std::stof(stock[3]);

            // Check if negative
            if (price < 0.00) {
                throwMessage(std::domain_error("Price cannot be negative"), line);
                valid = false;
            } else {

                vector<string> decimal;
                splitString(stock[3], decimal, ".");

                // Checking if exactly 2 decimal places
                if (decimal[1].size() != 2) {
                    throwMessage(std::invalid_argument("Price not convertible: Unsuitable cents"), line);
                    valid = false;
                }
            }

        // Will catch out of range or invalid string
        } catch (const std::exception e) {

            if (line != -1) {
                std::cout << "Line " << line << ": " << std::endl;
            }

            // Tells us what the error is
            std::cout << "Exception caught: " << e.what() << std::endl;
            valid = false;

        }

    }


    return valid;
}

bool Helper::validCoin(std::vector<std::string> coin)
{
    return true;
}

void Helper::throwMessage(std::exception& e, int line) {

    if (line != -1) {
        std::cout << "Line " << line << ": " << std::endl;
    }

    throw e;
}



