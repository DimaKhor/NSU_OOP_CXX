set(LIBRARY_NAME CommandState)
set(LIBRARY_HEADERS_DIR include)
set(LIBRARY_SOURCE src/commandState.cpp)

add_library(${LIBRARY_NAME} STATIC  ${LIBRARY_SOURCE})
target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_HEADERS_DIR})
