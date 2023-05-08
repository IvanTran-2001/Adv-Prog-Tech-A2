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

using std::string;
using std::vector;

class Helper
{
private:
    Helper();

public:

    static void splitString(string s, vector<string>& tokens, string delimeter);

    static void readCoinFile(string fileName);
};

#endif