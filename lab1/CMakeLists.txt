 cmake_minimum_required(VERSION 3.23)
 project(bigint)

 set(CMAKE_CXX_STANDARD 14)

 add_library(BigInt STATIC src/bigint.cpp)
 target_include_directories(BigInt PUBLIC include)

 include(FetchContent)
 FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
 )
 FetchContent_MakeAvailable(googletest)

 add_executable(tests test/test.cpp)
 target_link_libraries(tests gtest_main BigInt)
