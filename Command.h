#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include "Receiver.h"
class Command
{
public:
    virtual ~Command() = default;
    // virtual function because it is going to be overridden in the subclass
    virtual void execute() = 0;

protected:
    Receiver receiver;
};
#endif