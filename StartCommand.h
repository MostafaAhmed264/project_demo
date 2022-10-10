#ifndef START_COMMAND_H
#define START_COMMAND_H
#include "Command.h"
#include "Receiver.h"

class StartCommand : public Command
{
public:
    ~StartCommand() = default;

    StartCommand(Receiver receiver);
    virtual void execute() override;
};
#endif