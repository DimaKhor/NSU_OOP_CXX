#include "gtest/gtest.h"
#include "gameOfLife.h>
#include <sstream>

TEST(command_line_tests, no_input_test)
{
    std::stringstream stream; //откроем файл для вывод
    std::streambuf *coutbuf = std::cout.rdbuf(); //запомним старый буфер
    std::cout.rdbuf(stream.rdbuf()); //и теперь все будет в файл out.txt!

    int iterations = 0, gameMode = 1;
    string inputFile, outputFile;
    char* argv[] = {"./a.out", "-i", "10", "-o", "out.txt"};
    int argc = sizeof(argv);

    gameModeChoice(gameMode, iterations, inputFile, outputFile, argc, argv);

    if (inputFile.empty())
        inputFile="file.txt";
    GameState mylife(inputFile);

    Field field(mylife);

    gameOfLife(field, gameMode, iterations, outputFile);

    EXPECT_STREQ(stream.c_str(), "* * * * * * * * *  \n"
                                 "* * * * * * * * *  \n"
                                 "*     * * *     * *\n"
                                 "* *           * * *\n"
                                 "                   \n"
                                 "                   \n"
                                 "      * * *        \n"
                                 "    * * * * *      \n"
                                 "  * * * * * * *   *\n"
                                 "* *             * *\n"
                                 "file saved in: out.txt!");
};

TEST(rools_test, exit_test)