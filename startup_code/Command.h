#ifndef COMMAND_H
#define COMMAND_H

#include "VendingMachine.h"

// Each command is an object and is
// used to sent to the reciever
class Command {
 public:
  virtual ~Command() {
  }
  virtual void Execute() const = 0;
};

class Abort : public Command {

public:

    VendingMachine* machine;
    Abort(VendingMachine* vendingMachine);
    virtual void Execute() const override;

};

class DisplayItem : public Command {

public:

    VendingMachine* machine;
    DisplayItem(VendingMachine* vendingMachine);
    virtual void Execute() const override;

};

class PurchaseItem : public Command {

public:

    VendingMachine* machine;
    PurchaseItem(VendingMachine* vendingMachine);
    virtual void Execute() const override;

};

class Save : public Command {

public:

    VendingMachine* machine;
    Save(VendingMachine* vendingMachine);
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