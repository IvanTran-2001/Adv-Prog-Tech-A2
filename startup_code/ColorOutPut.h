#ifndef COLOROUTPUT_H
#define COLOROUTPUT_H

#include <string>
#include <map>
#include <iostream>

enum ColorCode {
    Reset,
    Red,
    Green,
    Yellow,
    Blue,
    B_AQUA
};

class ColorOutPut {

    public:

        template<typename T>
        static std::string customString(T s, ColorCode code, bool enhance) {
            
            // To change color of text
            std::map<ColorCode, std::string> colorStrings = {
                {ColorCode::Reset, "\033[0m"},
                {ColorCode::Red, "\033[31m"},
                {ColorCode::Green, "\033[32m"},
                {ColorCode::Yellow, "\033[33m"},
                {ColorCode::Blue, "\033[34m"},
                {ColorCode::B_AQUA, "\033[46m"}
            };

            // Return as string
            std::string returnVal = "";

            // If enhancement is enabled
            if (enhance) {
                returnVal += colorStrings[code] + s + colorStrings[Reset];
            } else {
                returnVal += s;
            }

            return returnVal;
        }

        template<typename T>
        static std::string customPrice(T s, ColorCode code, bool enhance) {
            
            // To change color of text
            std::map<ColorCode, std::string> colorStrings = {
                {ColorCode::Reset, "\033[0m"},
                {ColorCode::Red, "\033[31m"},
                {ColorCode::Green, "\033[32m"},
                {ColorCode::Yellow, "\033[33m"},
                {ColorCode::Blue, "\033[34m"},
                {ColorCode::B_AQUA, "\033[46m"}
            };

            // Return as string
            std::string returnVal = "";

            // If enhancement is enabled
            if (enhance) {

                // The method "convertToTwoDecimalPlaces" insures that output is 2 decimal places
                returnVal += colorStrings[code] + convertToTwoDecimalPlaces(s) + colorStrings[Reset];
            } else {
                returnVal += convertToTwoDecimalPlaces(s);
            }

            return returnVal;
        }

        // Returning exactly 2 decimal places
        static std::string convertToTwoDecimalPlaces(double value) {
            std::ostringstream stream;
            stream << std::fixed << std::setprecision(2) << value;
            return stream.str();
        }
};

    #endif // COLOROUTPUT_H