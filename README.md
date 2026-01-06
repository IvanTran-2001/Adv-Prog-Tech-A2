# Pastry Delights - Vending Machine Simulator

A comprehensive C++14 vending machine simulator demonstrating advanced software engineering principles including design patterns, custom data structures, and robust memory management.

## Overview

This project implements a fully functional vending machine system from the ground up. Users can browse products, make purchases, and receive correct change, while the system manages stock, coins, and file persistence. The implementation emphasizes clean architecture through the **Command Pattern**, custom-built data structures (doubly-linked lists), comprehensive exception handling, and thorough testing.

## Key Features

### User Features
- **Browse Products** - View all available items with prices
- **Purchase Items** - Select and buy items with automatic change calculation
- **Dynamic Display Modes** - View inventory in ascending/descending order (enhancement feature)

### Admin Features
- **Stock Management** - Add, remove, and restock items
- **Coin Management** - Reset coin supplies and view current coin counts
- **Persistence** - All data saved to files for session continuity
- **Safe Shutdown** - Graceful exit with data preservation

### Technical Features
- **Custom Data Structures** - Singly and doubly-linked lists built from scratch (not STL)
- **Command Pattern Architecture** - 8 command classes for operation encapsulation
- **Modular Design** - Easy to extend and maintain
- **Exception Handling** - 4 custom exception types for robust error management
- **Memory Safe** - Verified with Valgrind (zero leaks)
- **16+ Test Suites** - Comprehensive automated testing with edge case coverage

## Architecture

### Design Pattern: Command Pattern
The system uses the Command Pattern to encapsulate all user operations:
- **Invoker**: `Menu` class - Receives commands and executes them
- **Commands**: `DisplayItem`, `PurchaseItem`, `Save`, `AddItem`, `RemoveItem`, `DisplayCoins`, `ResetStock`, `ResetCoins`, `Abort`, `ToggleEnhancement`
- **Receiver**: `VendingMachine` class - Performs the actual operations

This separation allows operations to be:
- Queued and executed
- Logged easily
- Undone/modified with minimal changes
- Tested independently

### Core Classes

**Data Structures:**
- `LinkedList` - Abstract base class defining interface
- `LinkedListSingle` - Singly-linked implementation
- `LinkedListDouble` - Doubly-linked implementation with reverse traversal
- `Node` / `NodeD` - Node types for single and double lists

**System Management:**
- `VendingMachine` - Core system orchestrator
- `Menu` - Command invoker (handles user selections)
- `Command` - Abstract command base with 10 derived command classes
- `Coin` - Currency denomination management
- `Helper` - Utility functions (file I/O, parsing, validation)
- `ColorOutPut` - Terminal color support for enhanced display

**Data Models:**
- `Stock` - Represents a product (id, name, description, price, quantity)
- `Price` - Represents currency accurately (dollars + cents, not float)

### Dynamic List Switching (Enhancement)
Users can toggle between singly and doubly-linked list implementations at runtime:
- Singly-linked: Simpler, uses less memory
- Doubly-linked: Allows reverse traversal
Both maintain identical data and behavior.

## Tech Stack

| Component | Requirement |
|-----------|-------------|
| **Language** | C++14 |
| **Compiler** | G++ (11.0+) or compatible |
| **Build Tool** | Makefile |
| **Testing** | Custom test suites |
| **Memory Verification** | Valgrind |
| **Standard Library** | STL (limited use) |

## Building & Running

### Prerequisites
- G++ compiler (C++14 support)
- Make (optional but recommended)
- WSL/Linux environment or Windows with MinGW

### Compilation

Navigate to the `startup_code` directory:

```bash
cd startup_code
make
```

Or compile directly:
```bash
g++ -std=c++14 -o ppd ppd.cpp VendingMachine.cpp LinkedListDouble.cpp LinkedListSingle.cpp \
    LinkedList.cpp Node.cpp Coin.cpp Command.cpp Menu.cpp Helper.cpp -Wall -Wextra
```

### Running

Basic usage with provided test data:
```bash
./ppd stock.dat coins.dat
```

With custom data files (must follow same format):
```bash
./ppd [stock_file] [coins_file]
```

### Example Data Files

**stock.dat format:**
```
I001,Donut,Glazed donut,199,15
I002,Coffee,Hot coffee,250,20
```

**coins.dat format:**
```
5,50
10,30
20,25
...
```

## Testing

### Memory Safety Verification
Check for memory leaks with Valgrind:
```bash
valgrind --leak-check=full ./ppd stock.dat coins.dat
```

Expected output: "definitely lost: 0 bytes"

### Test Suites
The project includes 16+ automated test suites covering:
- Stock operations (add, remove, display)
- Purchase transactions (valid, invalid, exact change)
- Coin management (display, reset)
- Change calculation accuracy
- Edge cases (empty stock, insufficient funds, invalid input)

Located in: `testFunctionality/` and `testing/` directories

### Manual Testing
The interactive menu allows testing all features:
1. Display items in ascending/descending order
2. Attempt purchases with various coin amounts
3. Admin operations (add/remove stock, reset)
4. Toggle enhancement and verify list behavior

## Implementation Details

### Change Calculation Algorithm
Uses a **greedy algorithm** with 8 coin denominations (1¢, 5¢, 10¢, 20¢, 50¢, $1, $2, $5) to return minimum coin count while ensuring exact change.

### File Persistence
- **stock.dat**: Loaded on startup, updated on save
- **coins.dat**: Tracks coin inventory for change-making
- Both files validated on load with exception handling

### Exception Handling
Custom exceptions for:
1. Invalid stock/coin files
2. Insufficient coins for change
3. Invalid user input
4. Operation failures

### Color-Coded Output
Enhanced terminal display with color support (toggle with enhancement option) for better user experience.

## File Structure

```
startup_code/
├── ppd.cpp                    # Main entry point, command orchestration
├── VendingMachine.h/cpp       # Core system logic
├── LinkedList.h/cpp           # Abstract linked list interface
├── LinkedListSingle.h/cpp     # Singly-linked implementation
├── LinkedListDouble.h/cpp     # Doubly-linked implementation with reverse
├── Node.h/cpp                 # Node data structures
├── Command.h/cpp              # Command pattern implementation (10 commands)
├── Menu.h/cpp                 # Command invoker
├── Coin.h/cpp                 # Coin denomination management
├── Helper.h/cpp               # Utility functions
├── ColorOutPut.h              # Terminal color support
├── stock.dat                  # Sample stock data
├── coins.dat                  # Sample coin data
├── Makefile                   # Build configuration
└── testing/                   # Automated test suites (16+)
```

## Usage Guide

### Customer Operations
1. **Display Items** → View all products with current stock
2. **Purchase Item** → Select item ID and provide payment
3. **Receive Change** → Automatic change calculation

### Admin Operations
4. **Add Item** → Add new product to inventory
5. **Remove Item** → Remove product by ID
6. **Display Coins** → View coin supply
7. **Reset Stock** → Restore stock to default levels
8. **Reset Coins** → Restore coin supply to default levels
9. **Toggle Enhancement** → Switch between list implementations
10. **Exit** → Save and shutdown gracefully

## Development Notes

### Memory Management
- All dynamically allocated objects properly destructed
- No memory leaks (verified with Valgrind)
- Smart use of pointers for polymorphism (LinkedList* implementations)

### Code Quality
- Clear separation of concerns
- Consistent naming conventions
- Comprehensive inline documentation
- Exception safety throughout

### Future Enhancements
- Persistent transaction history
- Discount/promotion system
- Multiple currency support
- Networked vending capabilities
- GUI interface

## Authors

**Implementation**: Ivan Tran  
**Testing**: Andrew Djaja, Ivan Tran  
**Date**: May 2023  
**Course**: Advanced Programming Techniques, RMIT University  

## License

Academic use only - Part of RMIT University coursework

