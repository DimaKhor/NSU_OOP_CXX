#ifndef commandstate_h
#define commandstate_h

#include <string>
#include <iostream>

class CommandState
{
public:
    ~CommandState() = default;
    int readCommand();

    static int const exit = 1;
    static int const dump = 2;
    static int const tick = 3;
    static int const help = 4;
private:
    std::string currentCommand;
};


#endif
