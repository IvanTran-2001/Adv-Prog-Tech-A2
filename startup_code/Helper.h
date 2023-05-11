#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <algorithm> 
#include <cstring> 

#include "Node.h"

class Helper
{
private:
    Helper();

public:

    // Will split string based on delimeter
    static void splitString(std::string s, std::vector<std::string>& tokens, std::string delimeter);

    // User input
    static std::string readInput();

    // Check if the stock file is valid
    static bool validStock(std::vector<std::string> stock, int line);

    // Check if the coin file is valid
    static bool validCoin(std::vector<std::string> coin);

    static void throwMessage(std::exception&& e, int line);



};

#endif