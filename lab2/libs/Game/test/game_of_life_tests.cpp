#include "gtest/gtest.h"
#include "gameOfLife.h"


TEST(game_tests, choice_test)
{
    const int online = 1;

    int iterations = 0, gameMode = online;
    std::string inputFile, outputFile;

    char* argv[] = {"./a.out", "-i", "10", "-o", "out.txt",  "-file", "input.txt"};
    int argc = 6;

    gameModeChoice(gameMode, iterations, inputFile, outputFile, argc, argv);

    EXPECT_EQ(iterations, 10);
    EXPECT_EQ(inputFile, "input.txt");
    EXPECT_EQ(outputFile, "out.txt");
};

TEST(game_tests, offline_test)
{
    std::stringstream streamOut;
    std::cout.rdbuf(streamOut.rdbuf());

    std::string inputFile = "../../../config/file.txt";
    GameState life(inputFile);
    Field field(life);

    const int offline = 0;

    std::string outputFile = "out.txt";

    gameOfLife(field, offline, 1, outputFile);

    EXPECT_EQ(streamOut.str(), "This universe have these Rules: \n"
                               "#N Basic\n"
                               "#R #B34/S23\n"
                               "#S 10 10\n"
                               "                    \n"
                               "        *           \n"
                               "      *   *         \n"
                               "    *   *   *       \n"
                               "  *   *   *   *     \n"
                               "    *   *   *       \n"
                               "      *   *         \n"
                               "        *           \n"
                               "                    \n"
                               "                    \n"
                               "file saved in: out.txt!");

}

TEST(game_tests, exit_test)
{
    std::stringstream streamIn;
    std::cin.rdbuf(streamIn.rdbuf());
    streamIn << "exit";

    std::stringstream streamOut;
    std::cout.rdbuf(streamOut.rdbuf());

    std::string inputFile = "../../../config/file.txt";
    GameState life(inputFile);
    Field field(life);

    const int online = 1;

    std::string outputFile = "out.txt";

    gameOfLife(field, online, 1, outputFile);

    EXPECT_EQ(streamOut.str(), "This universe have these Rules: \n"
                               "#N Basic\n"
                               "#R #B34/S23\n"
                               "#S 10 10\n"
                               "Thank you for playing, can't wait to see you again :)\n");
}

TEST(game_tests, dump_test)
{
    std::stringstream streamIn;
    std::cin.rdbuf(streamIn.rdbuf());
    streamIn << "dump\nout.txt\nexit";

    std::stringstream streamOut;
    std::cout.rdbuf(streamOut.rdbuf());

    std::string inputFile = "../../../config/file.txt";
    GameState life(inputFile);
    Field field(life);

    const int online = 1;

    std::string outputFile = "out.txt";

    gameOfLife(field, online, 1, outputFile);

    EXPECT_EQ(streamOut.str(), "This universe have these Rules: \n"
                               "#N Basic\n"
                               "#R #B34/S23\n"
                               "#S 10 10\n"
                               "file saved in: out.txt!\n"
                               "Thank you for playing, can't wait to see you again :)\n");
}

TEST(game_tests, help_test)
{
    std::stringstream streamIn;
    std::cin.rdbuf(streamIn.rdbuf());
    streamIn << "help\nexit";

    std::stringstream streamOut;
    std::cout.rdbuf(streamOut.rdbuf());

    std::string inputFile = "../../../config/file.txt";
    GameState life(inputFile);
    Field field(life);

    const int online = 1;

    std::string outputFile = "out.txt";

    gameOfLife(field, online, 1, outputFile);

    EXPECT_EQ(streamOut.str(), "This universe have these Rules: \n"
                               "#N Basic\n"
                               "#R #B34/S23\n"
                               "#S 10 10\n"
                               "There are four commands:\n"
                               "1. help - show game reference.\n"
                               "2. dump <filename> - save current universe state in file.\n"
                               "3. exit - end the game.\n"
                               "4. tick <n> - count game state after n iteration.\n"
                               "Thank you for playing, can't wait to see you again :)\n");
}

TEST(game_tests, unknown_message_test)
{
    std::stringstream streamIn;
    std::cin.rdbuf(streamIn.rdbuf());
    streamIn << "dima\nexit";

    std::stringstream streamOut;
    std::cout.rdbuf(streamOut.rdbuf());

    std::string inputFile = "../../../config/file.txt";
    GameState life(inputFile);
    Field field(life);

    const int online = 1;

    std::string outputFile = "out.txt";

    gameOfLife(field, online, 1, outputFile);

    EXPECT_EQ(streamOut.str(), "This universe have these Rules: \n"
                               "#N Basic\n"
                               "#R #B34/S23\n"
                               "#S 10 10\n"
                               "Warning!\n"
                               "There is no such command!\n"
                               "Thank you for playing, can't wait to see you again :)\n");
}

TEST(game_tests, tick_unknown_message_test)
{
    std::stringstream streamIn;
    std::cin.rdbuf(streamIn.rdbuf());
    streamIn << "tick\ndima\nexit";

    std::stringstream streamOut;
    std::cout.rdbuf(streamOut.rdbuf());

    std::string inputFile = "../../../config/file.txt";
    GameState life(inputFile);
    Field field(life);

    const int online = 1;

    std::string outputFile = "out.txt";

    gameOfLife(field, online, 1, outputFile);

    EXPECT_EQ(streamOut.str(), "This universe have these Rules: \n"
                               "#N Basic\n"
                               "#R #B34/S23\n"
                               "#S 10 10\n"
                               "Warning!\n"
                               "There is no such command!\n"
                               "Thank you for playing, can't wait to see you again :)\n");
}

TEST(game_tests, tick_test)
{
    std::stringstream streamIn;
    std::cin.rdbuf(streamIn.rdbuf());
    streamIn << "tick\n1\nexit";

    std::stringstream streamOut;
    std::cout.rdbuf(streamOut.rdbuf());

    std::string inputFile = "../../../config/file.txt";
    GameState life(inputFile);
    Field field(life);

    const int online = 1;

    std::string outputFile = "out.txt";

    gameOfLife(field, online, 1, outputFile);

    EXPECT_EQ(streamOut.str(), "This universe have these Rules: \n"
                               "#N Basic\n"
                               "#R #B34/S23\n"
                               "#S 10 10\n"
                               "                    \n"
                               "        *           \n"
                               "      *   *         \n"
                               "    *   *   *       \n"
                               "  *   *   *   *     \n"
                               "    *   *   *       \n"
                               "      *   *         \n"
                               "        *           \n"
                               "                    \n"
                               "                    \n"
                               "Thank you for playing, can't wait to see you again :)\n");
}

