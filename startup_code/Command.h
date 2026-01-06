#ifndef COMMAND_H
#define COMMAND_H

#include "VendingMachine.h"

/**
 * @file Command.h
 * @brief Implementation of the Command Pattern for vending machine operations
 * 
 * This file defines the abstract Command class and all concrete command implementations.
 * The Command Pattern encapsulates requests as objects, allowing you to:
 * - Parameterize clients with different requests
 * - Queue requests for later execution
 * - Support undoable operations
 * - Log command history
 * 
 * Architecture:
 * - Command (Abstract Base): Defines execute interface
 * - Concrete Commands: Wrap specific VendingMachine operations
 * - Invoker (Menu): Receives and executes commands
 * - Receiver (VendingMachine): Performs actual operations
 */

/**
 * @class Command
 * @brief Abstract base class for all vending machine commands
 * 
 * Defines the interface that all concrete commands must implement.
 * Each command encapsulates a single operation on the VendingMachine.
 */
class Command {
 public:
  virtual ~Command() {
  }
  
  /**
   * @brief Execute the command
   * 
   * Pure virtual function that concrete commands must override.
   * Called by the Menu (Invoker) to execute the command.
   */
  virtual void Execute() const = 0;
};

/**
 * @class Abort
 * @brief Command to gracefully shutdown the vending machine
 * 
 * Triggers machine shutdown, saving current state and freeing resources.
 */
class Abort : public Command {
 public:
  VendingMachine* machine;  ///< Reference to the vending machine
  
  /**
   * @brief Constructor
   * @param vendingMachine Pointer to the VendingMachine receiver
   */
  Abort(VendingMachine* vendingMachine);
  
  /**
   * @brief Execute the abort/shutdown command
   * 
   * Calls VendingMachine::abort() to perform cleanup and exit
   */
  virtual void Execute() const override;
};

/**
 * @class DisplayItem
 * @brief Command to display available items in the vending machine
 * 
 * Shows all stock items with prices, quantities, and descriptions.
 * Users can choose to display in ascending or descending order (enhancement).
 */
class DisplayItem : public Command {
 public:
  VendingMachine* machine;  ///< Reference to the vending machine
  
  /**
   * @brief Constructor
   * @param vendingMachine Pointer to the VendingMachine receiver
   */
  DisplayItem(VendingMachine* vendingMachine);
  
  /**
   * @brief Execute the display items command
   * 
   * Calls VendingMachine::displayItems() to show inventory
   */
  virtual void Execute() const override;
};

/**
 * @class PurchaseItem
 * @brief Command to purchase an item from the vending machine
 * 
 * Allows customers to select an item and provide payment.
 * Handles change calculation using greedy algorithm.
 */
class PurchaseItem : public Command {
 public:
  VendingMachine* machine;  ///< Reference to the vending machine
  
  /**
   * @brief Constructor
   * @param vendingMachine Pointer to the VendingMachine receiver
   */
  PurchaseItem(VendingMachine* vendingMachine);
  
  /**
   * @brief Execute the purchase command
   * 
   * Calls VendingMachine::purchaseItems() to process transaction
   */
  virtual void Execute() const override;
};

/**
 * @class Save
 * @brief Command to save the current state to files
 * 
 * Persists stock and coin data to stock.dat and coins.dat files.
 */
class Save : public Command {
 public:
  VendingMachine* machine;  ///< Reference to the vending machine
  
  /**
   * @brief Constructor
   * @param vendingMachine Pointer to the VendingMachine receiver
   */
  Save(VendingMachine* vendingMachine);
  
  /**
   * @brief Execute the save command
   * 
   * Calls VendingMachine::save() to persist state to files
   */
  virtual void Execute() const override;
};

/**
 * @class AddItem
 * @brief Command to add a new item to the vending machine
 * 
 * Admin operation allowing new products to be added to inventory
 * with automatic ID assignment and stock level initialization.
 */
class AddItem : public Command {
 public:
  VendingMachine* machine;  ///< Reference to the vending machine
  
  /**
   * @brief Constructor
   * @param vendingMachine Pointer to the VendingMachine receiver
   */
  AddItem(VendingMachine* vendingMachine);
  
  /**
   * @brief Execute the add item command
   * 
   * Calls VendingMachine::addItem() to add product
   */
  virtual void Execute() const override;
};

/**
 * @class RemoveItem
 * @brief Command to remove an item from the vending machine
 * 
 * Admin operation to remove products by ID.
 */
class RemoveItem : public Command {
 public:
  VendingMachine* machine;  ///< Reference to the vending machine
  
  /**
   * @brief Constructor
   * @param vendingMachine Pointer to the VendingMachine receiver
   */
  RemoveItem(VendingMachine* vendingMachine);
  
  /**
   * @brief Execute the remove item command
   * 
   * Calls VendingMachine::removeItem() to delete product
   */
  virtual void Execute() const override;
};

/**
 * @class DisplayCoins
 * @brief Command to display current coin inventory
 * 
 * Shows the count of each coin denomination in the machine.
 */
class DisplayCoins : public Command {
 public:
  VendingMachine* machine;  ///< Reference to the vending machine
  
  /**
   * @brief Constructor
   * @param vendingMachine Pointer to the VendingMachine receiver
   */
  DisplayCoins(VendingMachine* vendingMachine);
  
  /**
   * @brief Execute the display coins command
   * 
   * Calls VendingMachine::displayCoins() to show coin status
   */
  virtual void Execute() const override;
};

/**
 * @class ResetStock
 * @brief Command to reset all stock to default levels
 * 
 * Admin operation to restore inventory to initial state.
 */
class ResetStock : public Command {
 public:
  VendingMachine* machine;  ///< Reference to the vending machine
  
  /**
   * @brief Constructor
   * @param vendingMachine Pointer to the VendingMachine receiver
   */
  ResetStock(VendingMachine* vendingMachine);
  
  /**
   * @brief Execute the reset stock command
   * 
   * Calls VendingMachine::resetStock() to restore inventory
   */
  virtual void Execute() const override;
};

/**
 * @class ResetCoins
 * @brief Command to reset coin supply to default levels
 * 
 * Admin operation to restore coin inventory to initial state.
 */
class ResetCoins : public Command {
 public:
  VendingMachine* machine;  ///< Reference to the vending machine
  
  /**
   * @brief Constructor
   * @param vendingMachine Pointer to the VendingMachine receiver
   */
  ResetCoins(VendingMachine* vendingMachine);
  
  /**
   * @brief Execute the reset coins command
   * 
   * Calls VendingMachine::resetCoins() to restore coin supply
   */
  virtual void Execute() const override;
};

/**
 * @class ToggleEnhancement
 * @brief Command to toggle between singly and doubly-linked lists
 * 
 * Enhancement feature allowing users to switch list implementations at runtime.
 * Singly-linked: Simpler, lower memory footprint
 * Doubly-linked: Allows reverse traversal for ascending/descending display
 */
class ToggleEnhancement : public Command {
 public:
  VendingMachine* machine;  ///< Reference to the vending machine
  
  /**
   * @brief Constructor
   * @param vendingMachine Pointer to the VendingMachine receiver
   */
  ToggleEnhancement(VendingMachine* vendingMachine);
  
  /**
   * @brief Execute the toggle enhancement command
   * 
   * Calls VendingMachine::toggleEnhancement() to switch list implementation
   */
  virtual void Execute() const override;
};

#endif  // COMMAND_H
    virtual void Execute() const override;

};

class AddItem : public Command {

public:

    VendingMachine* machine;
    AddItem(VendingMachine* vendingMachine);
    virtual void Execute() const override;

};

class RemoveItem : public Command {

public:

    VendingMachine* machine;
    RemoveItem(VendingMachine* vendingMachine);
    virtual void Execute() const override;

};

class DisplayCoins : public Command {

public:

    VendingMachine* machine;
    DisplayCoins(VendingMachine* vendingMachine);
    virtual void Execute() const override;

};

class ResetStock : public Command {

public:

    VendingMachine* machine;
    ResetStock(VendingMachine* vendingMachine);
    virtual void Execute() const override;

};

class ResetCoins : public Command {

public:

    VendingMachine* machine;
    ResetCoins(VendingMachine* vendingMachine);
    virtual void Execute() const override;

};

class TurnOnEnhancement : public Command {

public:

    VendingMachine* machine;
    TurnOnEnhancement(VendingMachine* vendingMachine);
    virtual void Execute() const override;

};

class ToggleEnhancement : public Command {

public:

    VendingMachine* machine;
    ToggleEnhancement(VendingMachine* vendingMachine);
    virtual void Execute() const override;

};


#endif  // COMMAND_H