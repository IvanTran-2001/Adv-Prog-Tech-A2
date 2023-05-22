#ifndef MENU_H
#define MENU_H

#include "Helper.h"
#include "Command.h"

//The invoker
class Menu {

 private:
  Command* command;

 public:
  ~Menu() {
    delete command;
  }

  void SetOnStart(Command *command) {
    this->command = command;
  }


  void DoSomethingImportant() {

    this->command->Execute();

  }
};

#endif  // MENU_H
