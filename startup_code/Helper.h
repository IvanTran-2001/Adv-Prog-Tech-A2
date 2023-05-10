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

class Helper
{
private:
    Helper();

public:

    static void splitString(std::string s, std::vector<std::string>& tokens, std::string delimeter);

    static std::string readInput();

    static bool validStock(std::vector<std::string> stock);

    static bool validCoin(std::vector<std::string> coin);


};

#endif