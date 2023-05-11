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

        std::cout << "---Loading Vending Machine---" << std::endl;
        VendingMachine* vender = new VendingMachine(argv[1],argv[2]);

        // Turning on the vending machine
        vender->on();

        //Free all data
        delete vender;
    }
    
}

bool checkInput(int count, char **command) {

    // Will validate
    bool valid = true;

    // Checks the length of argument
    if (count != 3) {
        valid = false;
        throw std::runtime_error("In correct format, example: ./ppd [stock file] [coin file]");
    } 

    // Checking if stock file is accessible
    if (!accessibleFile(command[1])) {
        valid = false;
        throw std::runtime_error("Error: Failed to open file: ");
        std::cout << "\'" << command[1] << "\'" << std::endl;
    }

    // Checking if coin file is accessible
    if (!accessibleFile(command[2])) {
        valid = false;
        throw std::runtime_error("Error: Failed to open file: ");
        std::cout << "\'" << command[2] << "\'" << std::endl;
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



