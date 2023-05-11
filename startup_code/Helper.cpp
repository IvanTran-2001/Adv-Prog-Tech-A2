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
    try
    {
        // Checking size of inputs
        if ((stock.size() != 5)) {
            throwMessage(std::runtime_error("Run time Error: Wrong format: [ID] [NAME] [DESC] [PRICE] [COUNT]"), line);

            // Check ID size
        } else if (stock[0].size() != IDLEN) {
            throwMessage(std::length_error("Length Error: ID must be length of 5"), line);

            // Check if ID start with 'I'
        } else if (stock[0][0] != 'I') {
            throwMessage(std::invalid_argument("Invalid Argument Error: ID must start with \'I\'"), line);

            // Check valid name size
        } else if ((stock[1].size() > NAMELEN)) {
            throwMessage(std::length_error("Length Error: Name length must be within 40"), line);

            // Check for description size
        } else if ((stock[2].size() > DESCLEN)) {      
            throwMessage(std::length_error("Length Error: Description length must be within 255"), line);
        } else {

            int count;
            // Convert to integer
            count = std::stoi(stock[4]);
            // If on hand is in the negatives
            if (count < 0) {
                throwMessage(std::domain_error("On hand cannot be negative"), line);
            }

            float price;
            // Convert to float
            price = std::stof(stock[3]);

            // Check if negative
            if (price < 0.00) {

                std::cout << 8 << std::endl;
                throwMessage(std::domain_error("Domain Error: Price cannot be negative"), line);
                valid = false;
            } else {

                vector<string> decimal;
                splitString(stock[3], decimal, ".");

                // Checking if exactly 2 decimal places
                if (decimal[1].size() != 2) {

                    std::cout << 9 << std::endl;
                    throwMessage(std::invalid_argument("Price not convertible: Unsuitable cents"), line);
                    valid = false;
                }
            }
        }
         
    }
    catch (const std::exception& e)
    {
        // Print error
        std::cout << e.what() << std::endl;
    }


    return valid;
}

bool Helper::validCoin(std::vector<std::string> coin)
{
    return true;
}

template<typename ExceptionType>
void Helper::throwMessage(const ExceptionType& e, int line) {

    if (line != -1) {
        std::cout << "Line " << line << ": ";
    }

    throw e;
}



