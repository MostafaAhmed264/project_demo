/**
 * @file Invoker.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-10-10
 *
 * @copyright Copyright (c) 2022
 * this is a class that is responsible for calling the execution of the commands
 * it also contains a list of the commands to be executed
 */

#ifndef INVOKER_H
#define INVOKER_H
#include "Command.h"
class Invoker
{
public:
    Invoker();
    ~Invoker();
    void setCommand(Command *command);
    // if a button in the gui is pressed
    void startButtonPressed();

private:
    Command *slot;
};

#endif