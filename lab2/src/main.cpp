#include "gameOfLife.h"
#include <string>

using namespace std;

int main(int argc, char** argv)
{

    int iterations = 0, gameMode = online;
    string inputFile, outputFile;

    gameModeChoice(gameMode, iterations, inputFile, outputFile, argc, argv);

    if (inputFile.empty())
        inputFile = "file.txt";

    GameState mylife(inputFile);

    Field field(mylife);

    gameOfLife(field, gameMode, iterations, outputFile);

    return 0;
}
