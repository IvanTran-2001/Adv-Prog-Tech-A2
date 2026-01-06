#include "Command.h"

/**
 * @file Command.cpp
 * @brief Implementation of Command Pattern classes for vending machine operations
 * 
 * Each command class wraps a specific operation on the VendingMachine receiver.
 * The constructor stores a reference to the machine, and Execute() delegates
 * the actual work to the appropriate machine method.
 */

// ==================== Abort Command ====================
Abort::Abort(VendingMachine* vendingMachine) : machine(vendingMachine) {}

void Abort::Execute() const {
    machine->abort();
}

// ==================== DisplayItem Command ====================
DisplayItem::DisplayItem(VendingMachine* vendingMachine) : machine(vendingMachine) {}

void DisplayItem::Execute() const {
    machine->displayItems();
}

// ==================== PurchaseItem Command ====================
PurchaseItem::PurchaseItem(VendingMachine* vendingMachine) : machine(vendingMachine) {}

void PurchaseItem::Execute() const {
    machine->purchaseItems();
}

// ==================== Save Command ====================
Save::Save(VendingMachine* vendingMachine) : machine(vendingMachine) {}

void Save::Execute() const {
    machine->save();
}

// ==================== AddItem Command ====================
AddItem::AddItem(VendingMachine* vendingMachine) : machine(vendingMachine) {}

void AddItem::Execute() const {
    machine->addItem();
}

// ==================== RemoveItem Command ====================
RemoveItem::RemoveItem(VendingMachine* vendingMachine) : machine(vendingMachine) {}

void RemoveItem::Execute() const {
    machine->removeItem();
}

// ==================== DisplayCoins Command ====================
DisplayCoins::DisplayCoins(VendingMachine* vendingMachine) : machine(vendingMachine) {}

void DisplayCoins::Execute() const {
    machine->displayCoins();
}

// ==================== ResetStock Command ====================
ResetStock::ResetStock(VendingMachine* vendingMachine) : machine(vendingMachine) {}

void ResetStock::Execute() const {
    machine->resetStock();
}

// ==================== ResetCoins Command ====================
ResetCoins::ResetCoins(VendingMachine* vendingMachine) : machine(vendingMachine) {}

void ResetCoins::Execute() const {
    machine->resetCoins();
}

// ==================== ToggleEnhancement Command ====================
ToggleEnhancement::ToggleEnhancement(VendingMachine* vendingMachine) : machine(vendingMachine) {}

void ToggleEnhancement::Execute() const {
    machine->toggleEnhancement();
}


