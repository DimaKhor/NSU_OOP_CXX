#include "gtest/gtest.h"
#include "field.h"

TEST(field_tests, print_world_test)
{
    std::stringstream stream; //откроем файл для вывод
    std::streambuf *coutbuf = std::cout.rdbuf(); //запомним старый буфер
    std::cout.rdbuf(stream.rdbuf()); //и теперь все будет в файл out.txt!

    std::string inputFile = "/Users/dima.khoroshev/CLionProjects/NSU_OOP_labs/lab2/cmake-build-debug/file.txt";
    GameState life(inputFile);
    Field field(life);
    field.initWorld();
    field.printWorld();

    EXPECT_EQ(stream.str(), "                    \n"
                            "        *           \n"
                            "      *   *         \n"
                            "    *   *   *       \n"
                            "  *   *   *   *     \n"
                            "    *   *   *       \n"
                            "      *   *         \n"
                            "        *           \n"
                            "                    \n"
                            "                    \n");
};

TEST(field_tests, rules_test)
{
    std::stringstream stream; //откроем файл для вывод
    std::streambuf *coutbuf = std::cout.rdbuf(); //запомним старый буфер
    std::cout.rdbuf(stream.rdbuf()); //и теперь все будет в файл out.txt!

    std::string inputFile = "/Users/dima.khoroshev/CLionProjects/NSU_OOP_labs/lab2/cmake-build-debug/file.txt";
    GameState life(inputFile);
    Field field(life);
    field.showRules();

    EXPECT_EQ(stream.str(), "This universe have these Rules: \n"
                            "#N Basic\n"
                            "#R #B34/S23\n"
                            "#S 10 10\n");
};

TEST(field_tests, next_world_test) {
    std::stringstream stream; //откроем файл для вывод
    std::streambuf *coutbuf = std::cout.rdbuf(); //запомним старый буфер
    std::cout.rdbuf(stream.rdbuf()); //и теперь все будет в файл out.txt!

    std::string inputFile = "/Users/dima.khoroshev/CLionProjects/NSU_OOP_labs/lab2/cmake-build-debug/file.txt";
    GameState life(inputFile);
    Field field(life);

    field.initWorld();
    field.nextWorld();
    field.printWorld();

    EXPECT_EQ(stream.str(), "                    \n"
                            "        *           \n"
                            "      * * *         \n"
                            "    * *   * *       \n"
                            "  * *   *   * *     \n"
                            "    * *   * *       \n"
                            "      * * *         \n"
                            "        *           \n"
                            "                    \n"
                            "                    \n");
};
