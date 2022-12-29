#include "gameOfLife.h"
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    const int online = 1;

    int iterations = 0, gameMode = online;
    string inputFile, outputFile;

    gameModeChoice(gameMode, iterations, inputFile, outputFile, argc, argv);

    if (inputFile.empty())
        inputFile = "../config/file.txt";

    GameState life(inputFile);

    Field field(life);

    gameOfLife(field, gameMode, iterations, outputFile);

    return 0;
}
