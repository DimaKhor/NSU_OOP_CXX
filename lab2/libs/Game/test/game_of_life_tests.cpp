#include "gtest/gtest.h"
#include "gameOfLife.h"


TEST(game_tests, choice_test)
{
    int iterations = 0, gameMode = online;
    std::string inputFile, outputFile;

    char* argv[] = {"./a.out", "-i", "10", "-o", "out.txt",  "-file", "input.txt"};
    int argc = 6;

    gameModeChoice(gameMode, iterations, inputFile, outputFile, argc, argv);

    EXPECT_EQ(iterations, 10);
    EXPECT_EQ(inputFile, "input.txt");
    EXPECT_EQ(outputFile, "out.txt");
};
