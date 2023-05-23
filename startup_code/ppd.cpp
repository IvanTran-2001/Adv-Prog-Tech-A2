/**
 * Author: Ivan Tran,     Andrew Djaja
 * Student No: s3849505,    s3945615
 * Date: 05/05/2023
 * Version: APT Assignment 2
*/

#include "Helper.h"
//Reciever
#include "VendingMachine.h"
//Invoker
#include "Menu.cpp"
//Command
#include "Command.h"

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
bool checkInput(int count, char **command);
bool accessibleFile(std::string filename);
bool command_set_press(VendingMachine* m);

int main(int argc, char **argv)
{
    // Intiating vending machine
    if (checkInput(argc, argv)) {

        std::cout << "\n---Loading Vending Machine---" << std::endl;
        VendingMachine* vender = new VendingMachine(argv[1],argv[2]);

        // Turning on the vending machine
        vender->on();
        bool loop = true;

        // Checks if vender is valid
        if (vender != nullptr) {

            // Prompt
            while (loop) {

                // Menu Options
                vender->optionMenu();
                
                // Command and press by invoker
                loop = command_set_press(vender);

            }
        }

        std::cout << "---Closing Vending Machine---\n" << std::endl;

    }


    return EXIT_SUCCESS;
    
}

bool command_set_press(VendingMachine* m) {

    bool loop = true;

    // The Invoker.
    // No need to make userSelect pointer.
    // Has automatic freeing memory.
    Menu userSelect;
    
    std::string input = Helper::readInput();
    // Removes all whitespace from input
    input.erase(std::remove_if(input.begin(), input.end(), isspace), input.end());

    // If statements will send commands (Command) to the menu (Invoker)
    if (input == DISPLAY_ITEMS){

        //Display items
        userSelect.set(new DisplayItem(m));
                
    } else if (input == PURCHASE_ITEMS){

        //Purchase items
        userSelect.set(new PurchaseItem(m));

    } else if (input == SAVE_EXIT){
        userSelect.set(new Save(m));
        userSelect.set(new Abort(m));
        loop = false;

    } else if (input == ADD_ITEM) {
        userSelect.set(new AddItem(m));

    } else if (input == REMOVE_ITEM) {
        userSelect.set(new RemoveItem(m));

    } else if (input == DISPLAY_COINS) {
        userSelect.set(new DisplayCoins(m));

    } else if (input == RESET_STOCK) {
        userSelect.set(new ResetStock(m));

    } else if (input == RESET_COINS) {
        userSelect.set(new ResetCoins(m));

    } else if (input == ENHANCEMENT) {
        userSelect.set(new ToggleEnhancement(m));

    } else if (input == ABORT) {
        userSelect.set(new Abort(m));
        loop = false;
    }

    // The given command will now be executed
    // The command will be recieved by the vending machine
    // Vending Machine executes the command
    userSelect.press();

    return loop;
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



