#include "gtest/gtest.h"
#include "message.h"

TEST(message_tests, help_test)
{
    std::stringstream stream; //откроем файл для выводa
    std::streambuf *coutbuf = std::cout.rdbuf(); //запомним старый буфер
    std::cout.rdbuf(stream.rdbuf()); //и теперь все будет в файл out.txt!

    Message message;
    message.helpMessage();

    EXPECT_EQ(stream.str(), "There are four commands:\n"
                                 "1. help - show game reference.\n"
                                 "2. dump <filename> - save current universe state in file.\n"
                                 "3. exit - end the game.\n"
                                 "4. tick <n> - count game state after n iteration.\n");

};

TEST(message_tests, unknown_test)
{
    std::stringstream stream; //откроем файл для выводa
    std::streambuf *coutbuf = std::cout.rdbuf(); //запомним старый буфер
    std::cout.rdbuf(stream.rdbuf()); //и теперь все будет в файл out.txt!

    Message message;
    message.unknownCommand();

    EXPECT_EQ(stream.str(), "There is no such command!\n");
};

TEST(message_tests, warning_test)
{
    std::stringstream stream; //откроем файл для выводa
    std::streambuf *coutbuf = std::cout.rdbuf(); //запомним старый буфер
    std::cout.rdbuf(stream.rdbuf()); //и теперь все будет в файл out.txt!

    Message message;
    message.warningMessage();

    EXPECT_EQ(stream.str(), "Warning!\n");
};

TEST(message_tests, start_test)
{
    std::stringstream stream; //откроем файл для выводa
    std::streambuf *coutbuf = std::cout.rdbuf(); //запомним старый буфер
    std::cout.rdbuf(stream.rdbuf()); //и теперь все будет в файл out.txt!

    Message message;
    message.startMessage();

    EXPECT_EQ(stream.str(), "Hello in my game of life!:)\n"
                            "There are two mods: offline and online\n"
                            "online mode: you just start program and choose commands\n"
                            "offline mode: start it with -file <input file> -i <number of iterations> -o <output file>\n"
                            "There are such commands in online mode:\n"
                            "1. help - show game reference.\n"
                            "2. dump <filename> - save current universe state in file.\n"
                            "3. exit - end the game.\n"
                            "4. tick <n> - count game state after n iteration.\n");
};