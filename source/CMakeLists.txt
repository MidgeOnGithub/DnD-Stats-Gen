cmake_minimum_required(VERSION 3.13)
project(DnD_Stats_Gen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(DnD_Stats_Gen
        main.cpp
        dice.cpp
        script.cpp
        abilities.cpp
)
