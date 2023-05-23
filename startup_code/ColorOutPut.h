#ifndef COLOROUTPUT_H
#define COLOROUTPUT_H

#include <string>
#include <map>
#include <iostream>

enum ColorCode {
    Reset,
    Red,
    Green,
    Yellow
};

class ColorOutPut {

    public:

        static std::string customString(std::string s, ColorCode code, bool enhance) {
            
            std::map<ColorCode, std::string> colorStrings = {
                {ColorCode::Reset, "\033[0m"},
                {ColorCode::Red, "\033[31m"},
                {ColorCode::Green, "\033[32m"},
                {ColorCode::Yellow, "\033[33m"}
            };

            std::string returnVal = "";

            if (enhance) {
                returnVal += colorStrings[code] + s + colorStrings[Reset];
            } else {
                returnVal += s;
            }

            return returnVal;
        }

        template<typename T>
        static std::string customPrice(T s, ColorCode code, bool enhance) {
            
            std::map<ColorCode, std::string> colorStrings = {
                {ColorCode::Reset, "\033[0m"},
                {ColorCode::Red, "\033[31m"},
                {ColorCode::Green, "\033[32m"},
                {ColorCode::Yellow, "\033[33m"}
            };

            std::string returnVal = "";

            if (enhance) {
                returnVal += colorStrings[code] + convertToTwoDecimalPlaces(s) + colorStrings[Reset];
            } else {
                returnVal += convertToTwoDecimalPlaces(s);
            }

            return returnVal;
        }

    static std::string convertToTwoDecimalPlaces(double value) {
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << value;
        return stream.str();
    }
};

    #endif // COLOROUTPUT_H