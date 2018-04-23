cmake_minimum_required(VERSION 3.2)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra")
project(compiler_assignment)
add_executable(phase1 phase1.cpp ParseTable.cpp Parser.cpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lalr_table
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/grammar
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/input.c
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/input2.c
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
