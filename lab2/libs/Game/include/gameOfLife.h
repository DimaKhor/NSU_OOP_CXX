#ifndef gameOfLife_h
#define gameOfLife_h

#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <thread>

const int online = 1;
const int offline = 0;

struct point
{
    point() = default;
    point(bool p_is_life, int xt, int yt);
    bool point_is_life;
    int x = 0;
    int y = 0;
};

void gameModeChoice(int& gameMode, int& iterations, std::string& inputFile, std::string& outputFile, int argc, char** argv);

void gameOfLife(Field field, int gameMode, int iterations, std::string outputFile);

#endif