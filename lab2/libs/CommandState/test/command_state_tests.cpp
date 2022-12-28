#include "gtest/gtest.h"
#include "commandState.h"

TEST(command_state_tests, exit_test)
{
    std::stringstream stream;
    std::cin.rdbuf(stream.rdbuf());

    stream << "exit";

    CommandState com;
    int command = com.readCommand();

    EXPECT_EQ(command, 1);
};

TEST(command_state_tests, dump_test)
{
    std::stringstream stream;
    std::cin.rdbuf(stream.rdbuf());

    stream << "dump";

    CommandState com;
    int command = com.readCommand();

    EXPECT_EQ(command, 2);
};

TEST(command_state_tests, tick_test)
{
    std::stringstream stream;
    std::cin.rdbuf(stream.rdbuf());

    stream << "tick";

    CommandState com;
    int command = com.readCommand();

    EXPECT_EQ(command, 3);
};

TEST(command_state_tests, help_test)
{
    std::stringstream stream;
    std::cin.rdbuf(stream.rdbuf());

    stream << "help";

    CommandState com;
    int command = com.readCommand();

    EXPECT_EQ(command, 4);
};

TEST(command_state_tests, unknown_test)
{
    std::stringstream stream;
    std::cin.rdbuf(stream.rdbuf());

    stream << "miley cyrus";

    CommandState com;
    int command = com.readCommand();

    EXPECT_EQ(command, -1);
};