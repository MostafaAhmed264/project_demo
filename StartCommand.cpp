#include "StartCommand.h"
#include "Receiver.h"
void StartCommand::execute()
{
    std::cout << "executing startCommand\n";
    receiver.start();
}
StartCommand::StartCommand(Receiver receiver)
{
    std::cout << "initializing startCommand\n";
    this->receiver = receiver;
}