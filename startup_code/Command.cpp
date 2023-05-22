#include "Command.h"

Abort::Abort(VendingMachine* vendingMachine) {
    this->machine = vendingMachine;
}

void Abort::Execute() const override{
    this->machine.abort();
}

DisplayItem::DisplayItem(VendingMachine* vendingMachine) {
    this->machine = vendingMachine;
}

void DisplayItem::Execute() const override{
    this->machine->displayItems();
}


