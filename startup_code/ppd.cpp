/**
 * Author: Ivan Tran,     Andrew Djaja
 * Student No: s3849505,    s3945615
 * Date: 05/05/2023
 * Version: APT Assignment 2
*/

#include "Helper.h"
#include "VendingMachine.h"

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
bool checkInput(int count, char **command);
bool accessibleFile(std::string filename);

int main(int argc, char **argv)
{
    // Intiating vending machine
    if (checkInput(argc, argv)) {

        std::cout << "\n---Loading Vending Machine---" << std::endl;
        VendingMachine* vender = new VendingMachine(argv[1],argv[2]);

        // Turning on the vending machine
        vender->on();

        std::cout << "---Closing Vending Machine---\n" << std::endl;

        //Free all data
        delete vender;
    }
    
}

bool checkInput(int count, char **command) {

    // Will validate
    bool valid = true;

    try {
        // Checks the length of argument
        if (count != 3) {
            valid = false;
            throw std::runtime_error("Runtime Error: Incorrect format, example: ./ppd [stock file] [coin file]");
        } 

        // Checking if stock file is accessible
        if (!accessibleFile(command[1])) {
            valid = false;
            throw std::runtime_error("Runtime Error: Failed to open file: ");
            std::cout << "\'" << command[1] << "\'" << std::endl;
        }

        // Checking if coin file is accessible
        if (!accessibleFile(command[2])) {
            valid = false;
            throw std::runtime_error("Runtime Error: Failed to open file: ");
            std::cout << "\'" << command[2] << "\'" << std::endl;
        }
    } catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }


    return valid;
}

bool accessibleFile(std::string filename) {

    bool valid = true;

    // Attempting to file
    std::ifstream file(filename);

    // Checking if file is accessible
    if (!file.good()) {
        valid = false;
    }

    return valid;
}



