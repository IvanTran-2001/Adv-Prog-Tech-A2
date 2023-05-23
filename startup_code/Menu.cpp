#ifndef MENU_H
#define MENU_H

#include "Helper.h"
#include "Command.h"

//The invoker
class Menu {

 private:
  std::vector<Command*> commands;

 public:

  // No Need for deconstructor because
  // Commands get deleted right after
  // Execution
  ~Menu() {

  }

  // Getting commands
  void set(Command *command) {
    this->commands.push_back(command);
  }


  void press() {

    // Executes all commands pressed.
    for (Command* c : commands) {
      c->Execute();
    }

    // Once commands executed, delete commands.
    clear();

  }

  void clear() {
    for (Command* c : commands) {
      delete c;
    }
  }
};



#endif  // MENU_H
