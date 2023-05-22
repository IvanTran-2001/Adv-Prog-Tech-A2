#include "Command.h"

Abort::Abort(VendingMachine* vendingMachine) {
    this->machine = vendingMachine;
}

void Abort::Execute() const{
    this->machine->abort();
}

DisplayItem::DisplayItem(VendingMachine* vendingMachine) {
    this->machine = vendingMachine;
}

void DisplayItem::Execute() const{
    this->machine->displayItems();
}

PurchaseItem::PurchaseItem(VendingMachine* vendingMachine) {
    this->machine = vendingMachine;
}

void PurchaseItem::Execute() const{
    this->machine->purchaseItems();
}

Save::Save(VendingMachine* vendingMachine) {
    this->machine = vendingMachine;
}

void Save::Execute() const{
    this->machine->save();
}

AddItem::AddItem(VendingMachine* vendingMachine) {
    this->machine = vendingMachine;
}

void AddItem::Execute() const{
    this->machine->addItem();
}

RemoveItem::RemoveItem(VendingMachine* vendingMachine) {
    this->machine = vendingMachine;
}

void RemoveItem::Execute() const{
    this->machine->removeItem();
}

DisplayCoins::DisplayCoins(VendingMachine* vendingMachine) {
    this->machine = vendingMachine;
}

void DisplayCoins::Execute() const{
    this->machine->displayCoins();
}

ResetStock::ResetStock(VendingMachine* vendingMachine) {
    this->machine = vendingMachine;
}

void ResetStock::Execute() const{
    this->machine->resetStock();
}

ResetCoins::ResetCoins(VendingMachine* vendingMachine) {
    this->machine = vendingMachine;
}

void ResetCoins::Execute() const{
    this->machine->resetCoins();
}

DisplayItem::DisplayItem(VendingMachine* vendingMachine) {
    this->machine = vendingMachine;
}

void DisplayItem::Execute() const{
    this->machine->displayItems();
}

ToggleEnhancement::ToggleEnhancement(VendingMachine* vendingMachine) {
    this->machine = vendingMachine;
}

void ToggleEnhancement::Execute() const{
    this->machine->toggleEnhancement();
}


