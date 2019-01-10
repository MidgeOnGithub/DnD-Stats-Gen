cmake_minimum_required(VERSION 3.13)
project(DND_Stats_Gen)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Stats_Gen_Lib "")
add_subdirectory(source)
