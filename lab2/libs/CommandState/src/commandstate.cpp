
#include "commandstate.h"

int CommandState::readCommand()
{
    std::cin >> currentCommand;

    //Exit command
    if (currentCommand == "exit")
        return this->exit;

    //Dump game field command
    if (currentCommand == "dump")
        return this->dump;

    //Show field after n iteration
    if (currentCommand == "tick")
        return this->tick;

    //Show game reference
    if (currentCommand == "help")
        return this->help;

    return -1;
}