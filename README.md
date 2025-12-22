Pastry Delights - Vending Machine Simulation
Overview

This project is a full-stack simulation of a vending machine, implemented entirely in C++.
It allows users to browse products, purchase items, and receive correct change while ensuring safe memory management using custom data structures (doubly-linked lists).
It also includes backend logic for exception handling, stock management, coin conversion, and change calculation, making it a complete simulation from front-end display to backend functionality.

Tech Stack / Requirements
- Compiler: G++
- C++ Standard: C++14
- Build Tool: Makefile (optional, for compiling easily)
- Memory Testing: Valgrind (recommended)
- Libraries: Standard Template Library (STL), standard C++ libraries

Instructions:
Compilation

Make sure you are using a G++ compiler or WSL terminal.
If using the Makefile, simply run:
make


Alternatively, you can compile manually:

g++ -std=c++14 *.cpp -o ppd

Running the Program

Place the executable in the same folder as your stock.dat and coins.dat files. Then run:

./ppd stock.dat coins.dat


You can also specify your own stock and coin files (must follow same format):

./ppd [stock file] [coins file]

Features
- View available items and prices
- Purchase items and receive correct change
- Admin functions: add/remove items, restock, reset coins
- Memory-safe operations using custom doubly-linked lists
- Exception handling for invalid input and transactions

Testing
- Optionally, run the program with Valgrind to check for memory leaks:
- valgrind ./ppd stock.dat coins.dat

Author

Ivan Tran

