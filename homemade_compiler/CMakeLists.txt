# sudo apt install libglfw3 libglew-dev glew-utils libglew2.0 assimp-utils libassimp-dev libassimp3v5 freeglut3-dev

cmake_minimum_required(VERSION 3.2)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra")
project(compiler_assignment)
add_executable(phase1 phase1.cpp ParseTable.cpp Parser.cpp)
# add_executable()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/rules2
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/p3
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.c
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/rules2
#     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


# include_directories(${OPENGL_INCLUDE_DIRS})
# target_link_libraries(parkviewer ${OPENGL_LIBRARIES} glfw GLEW assimp dl)
