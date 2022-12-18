#ifndef message_h
#define message_h

#include <iostream>
#include <unistd.h>

class Message
{
public:
    void startMessage();
    void warningMessage();
    void unknownCommand();
    void helpMessage();
};

#endif
