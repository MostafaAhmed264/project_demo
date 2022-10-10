#include "Invoker.h"

Invoker::Invoker()
{
}
Invoker::~Invoker()
{
}
void Invoker::setCommand(Command *command)
{
    std::cout << "command is set\n";
    slot = command;
}
void Invoker::startButtonPressed()
{
    slot->execute();
}