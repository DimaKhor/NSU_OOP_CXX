#ifndef gameOfLife_h
#define gameOfLife_h

#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <regex>
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

class Message
{
public:
    void startMessage();
    void warningMessage();
    void unknownCommand();
    void helpMessage();
};

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

class GameState
{
public:
    GameState(std::string file_name);
    std::string gameRools;
    std::string survivalRools;

    int world_h;
    int world_w;

    std::string fileName;
    std::string universeName;
    std::vector <point> cellsCoordinates;
};

class Field
{
public:
    Field()= default;
    Field(GameState& _game);
    GameState* game;
    ~Field() = default;
    std::vector< std::vector<point> > world;

    void initWorld();
    void nextWorld();
    void printWorld();
    void showRules();
    void saveField(std::string outputFile);
private:
    bool should_be_born(int x);
    bool should_survive(int x);
};

void gameModeChoice(int& gameMode, int& iterations, std::string& inputFile, std::string& outputFile, int argc, char** argv);

void gameOfLife(Field field, int gameMode, int iterations, std::string outputFile);

#endif