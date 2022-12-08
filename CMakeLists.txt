cmake_minimum_required(VERSION 3.23)
project(gameOfLife)

set(CMAKE_CXX_STANDARD 14)

add_library(gameOfLife STATIC src/gameOfLife.cpp)
target_include_directories(gameOfLife PUBLIC include)
add_executable(main src/main.cpp)
target_link_libraries(main PUBLIC gameOfLife)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(test test/test.cpp)
target_link_libraries(test PUBLIC gtest_main gameOfLife)