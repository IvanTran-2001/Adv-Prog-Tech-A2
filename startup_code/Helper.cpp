#include "Helper.h"

using std::string;
using std::vector;

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


bool Helper::validStock(vector<string> stock) 
{

    // Valid line
    bool valid = true;
    try
    {
        // Checking size of inputs
        if ((stock.size() != 5)) {
            throw std::runtime_error("Wrong format: [ID] [NAME] [DESC] [PRICE] [COUNT]");

            // Check ID size
        } else if (stock[0].size() != IDLEN) {
            throw std::length_error("ID must be length of 5");

            // Check if ID start with 'I'
        } else if (stock[0][0] != 'I') {
            throw std::invalid_argument("ID must start with \'I\'");

            // Check valid name size
        } else if ((stock[1].size() > NAMELEN)) {
            throw std::length_error("Name length must be within 40");

            // Check for description size
        } else if ((stock[2].size() > DESCLEN)) {      
            throw std::length_error("Description length must be within 255");

        } else {

            int count;
            // Convert to integer
            count = std::stoi(stock[4]);
            // If on hand is in the negatives
            if (count < 0) {
                throw std::domain_error("On hand cannot be negative");
            }

            float price;
            // Convert to float
            price = std::stof(stock[3]);

            // Check if negative
            if (price < 0.00f) {

                throw std::domain_error("Price cannot be negative");
            } else {

                vector<string> decimal;
                splitString(stock[3], decimal, ".");

                // Checking if exactly 2 decimal places
                if (decimal[1].size() != 2) {

                    throw std::invalid_argument("Price not convertible: Unsuitable cents");
                }
            }
        }
         
    // Catch errors
    } 
    catch (const std::invalid_argument& e)
    {
        // False
        valid = false;

        // Print error
        std::cout << "ID-" << stock[0] << ": ";
        std::cout << "Invalid argument error: " << e.what() << std::endl;
    } 
    catch (const std::runtime_error& e)
    {
        // False
        valid = false;

        // Print error
        std::cout << "ID-" << stock[0] << ": ";
        std::cout << "Run time Error: " << e.what() << std::endl;
    } 
    catch (const std::length_error& e)
    {
        // False
        valid = false;

        // Print error
        std::cout << "ID-" << stock[0] << ": ";
        std::cout << "Length Error: " << e.what() << std::endl;
    }  
    catch (const std::domain_error& e)
    {
        // False
        valid = false;

        // Print error
        std::cout << "ID-" << stock[0] << ": ";
        std::cout << "Domain Error: " << e.what() << std::endl;
    } 
    catch (const std::exception& e)
    {
        // False
        valid = false;

        // Print error
        std::cout << "ID-" << stock[0] << ": ";
        std::cout << e.what() << std::endl;
    } 

    return valid;
}

bool Helper::validCoin(std::vector<std::string> coin, int i)
{
    // Used to validate file
    int startingIndex = i;

    try
    {
        // Denominations has 8, must have exactly 8 lines.
        if (coin.size() != 8) {
            throw std::runtime_error("Too many lines");

        } else {

                // Checking if all denomination exist
                while (i < 8) {

                    // Split line by delimiter
                    vector<string> splitCoin;
                    Helper::splitString(coin[i], splitCoin, ",");

                    // Check if only contains 2 inputs
                    if (splitCoin.size() != 2) {
                        throw std::invalid_argument("Invalid Line");
                    }

                    // Checks if all denomination is in file
                    if (Coin::coinDenomination[i] != splitCoin[0]) {
                        throw std::invalid_argument("Missing/wrong Denomination");
                    }

                    // Attempt to convert to integer
                    std::stoi(coin[1]);

                    i += 1;
                }
        }
    }
    catch (const std::invalid_argument& e)
    {

        // Print error
        std::cout << "Invalid argument error: " << e.what() << std::endl;
        validCoin(coin, i + 1);
    } 
    catch (const std::runtime_error& e)
    {

        // Print error
        std::cout << "Run time Error: " << e.what() << std::endl;
        validCoin(coin, i + 1);
    } 
    catch (const std::length_error& e)
    {
        // Print error
        std::cout << "Length Error: " << e.what() << std::endl;
        validCoin(coin, i + 1);
    }  
    catch (const std::domain_error& e)
    {

        // Print error
        std::cout << "Domain Error: " << e.what() << std::endl;
        validCoin(coin, i + 1);
    } 
    catch (const std::exception& e) 
    {

        // Print error
        std::cout << e.what() << std::endl;
        return validCoin(coin, i + 1);
    } 
    
    std::cout << startingIndex << std::endl;
    // If the starting index changed, it means an error occured
    if (startingIndex != 0) {
        return false;
    }

    return true;

}



