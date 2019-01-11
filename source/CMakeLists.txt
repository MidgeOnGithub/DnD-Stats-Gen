add_executable(DND_Stats_Gen main.cpp)

add_subdirectory(dice_roller)

target_sources(Stats_Gen_Lib
    PRIVATE
        abilities.cpp
        abilities.hpp
        abilities_script.cpp
        abilities_script.hpp
)

# Need to build symbols/references needed from Boost sub-package
# Set BOOST_ROOT so CMake can find packaged Boost directory
set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/vendor/boost_1_69_0/)
# CMake's find_package adds components to built-in ${Boost_LIBRARIES}
find_package(Boost REQUIRED COMPONENTS chrono random thread)

# Link executable to source and Boost libraries
target_link_libraries(DND_Stats_Gen Stats_Gen_Lib ${Boost_LIBRARIES})
