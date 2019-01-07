cmake_minimum_required(VERSION 3.13)
project(DND_Stats_Gen)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(source)

add_executable(DND_Stats_Gen
        source/abilities.cpp
        source/abilities.hpp
        source/classes.cpp
        source/classes.hpp
        source/dice.cpp
        source/dice.hpp
        source/main.cpp
        source/script.cpp
        source/script.hpp)

# Place output files outside of source folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
