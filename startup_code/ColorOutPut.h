#ifndef COLOROUTPUT_H
#define COLOROUTPUT_H

#include <string>
#include <string.h>
#include <map>


enum ColorCode {
        Reset,
        Red,
        Green,
        Yellow
    };

std::map<ColorCode, std::string> colorStrings = {
    {ColorCode::Reset, "\033[0m"},
    {ColorCode::Red, "\033[31m"},
    {ColorCode::Green, "\033[32m"},
    {ColorCode::Yellow, "\033[33m"}
};


// Used for highlighting strings or changing color of strings
class ColorOutPut
{
private:
    ColorOutPut();

public:

    template<typename T>

    static std::string custom(T s, ColorCode code, bool enhance) {

        // The return value
        std::string returnVal = "";

        if (enhance) {

            // Will check if string
            if (std::is_same<T, std::string>::s) {

                // Change color
                returnVal = colorStrings[code] << (s) << colorStrings[Reset];
            } else {
                returnVal = colorStrings[code] << std::to_string(s) << colorStrings[Reset];
            }

        } else {

            if (std::is_same<T, std::string>::s) {

                // Change color
                returnVal = s
            } else {
                returnVal = std::to_string(s);
            }
        }
        
        return returnVal;
    }
    // Custom color related to strings


};

#endif // COLOROUTPUT_H
