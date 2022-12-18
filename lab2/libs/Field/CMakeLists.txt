set(LIBRARY_NAME Field)
set(LIBRARY_HEADERS_DIR include)
set(LIBRARY_SOURCE src/field.cpp)

set(TEST_LIBRARY_NAME field_tests)
set(TEST_SOURCE test/field_tests.cpp)

add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SOURCE})
target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_HEADERS_DIR} ${CMAKE_SOURCE_DIR}/libs/GameState/include)
target_link_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_BINARY_DIR}/libs/GameState)
target_link_libraries(${LIBRARY_NAME} PUBLIC GameState)


#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
#)
#FetchContent_MakeAvailable(googletest)
#
#add_executable(${TEST_LIBRARY_NAME} ${TEST_SOURCE})
#target_link_libraries(${TEST_LIBRARY_NAME} gtest_main ${LIBRARY_NAME})