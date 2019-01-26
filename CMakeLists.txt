cmake_minimum_required(VERSION 3.12)
project(DND_Stats_Gen)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(source)
add_subdirectory(vendor)

# Place output files outside of source folder
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(DnD-Stats-Gen source/main.cpp)

target_sources(DnD-Stats-Gen
    PRIVATE
        source/abilities.cpp
        source/abilities.hpp
        source/abilities_script.cpp
        source/character.cpp
        source/character.hpp
        source/dice_roller/dice.cpp
        source/dice_roller/dice.hpp
        source/dice_roller/dnd_dice.cpp
        source/dice_roller/dnd_dice.hpp
)

target_link_libraries(DnD-Stats-Gen
    PUBLIC 
        Boost::chrono
        Boost::program_options
        Boost::random
        Boost::thread
)
