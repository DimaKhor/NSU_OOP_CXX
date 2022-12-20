#ifndef gameOfLife_h
#define gameOfLife_h

#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <thread>

#include "field.h"
#include "message.h"
#include "commandState.h"

const int online = 1;
const int offline = 0;

void gameModeChoice(int& gameMode, int& iterations, std::string& inputFile, std::string& outputFile, int argc, char** argv);

void gameOfLife(Field field, int gameMode, int iterations, std::string outputFile);

#endif