#include "gtest/gtest.h"
#include "gameState.h"

TEST(game_state_tests, game_state_tests)
{
    std::string inputFile = "/Users/dima.khoroshev/CLionProjects/NSU_OOP_labs/lab2/cmake-build-debug/file.txt";
    GameState life(inputFile);

    EXPECT_EQ(life.universeName, "Basic");
    EXPECT_EQ(life.gameRules, "34");
    EXPECT_EQ(life.survivalRules, "23");


    EXPECT_EQ(life.world_h, 10);
    EXPECT_EQ(life.world_w, 10);

}