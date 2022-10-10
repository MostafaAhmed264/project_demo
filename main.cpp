/*this is just for testing*/
#include "Command.h"
#include "StartCommand.h"
#include "EndCommand.h"
#include "Receiver.h"
#include "Invoker.h"

int main(void)
{
    Receiver receiver;
    Command *command1 = new StartCommand(receiver);
    Invoker invoker;
    invoker.setCommand(command1);
    invoker.startButtonPressed();
}