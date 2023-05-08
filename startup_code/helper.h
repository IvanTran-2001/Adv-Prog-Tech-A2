#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>
#include <string.h>
#include <random>

class Helper
{
private:
    Helper();

public:

    void splitString(string s, vector<string>& tokens, string delimeter);

    void readCoinFile();

    void readStockFile();
};

#endif