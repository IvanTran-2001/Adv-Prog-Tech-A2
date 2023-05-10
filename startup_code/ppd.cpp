#include "Helper.h"
#include "VendingMachine.h"

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
int main(int argc, char **argv)
{

    VendingMachine* vender = new VendingMachine(argv[1],argv[2]);
    vender->on();
    
}



