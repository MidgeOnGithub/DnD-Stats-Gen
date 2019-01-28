add_executable(DnD-Stats-Gen main.cpp)
target_sources(DnD-Stats-Gen
    PRIVATE
        abilities.cpp
        abilities.hpp
        abilities_script.cpp
        character.cpp
        character.hpp
        races.cpp
        races.hpp
)
add_subdirectory(dice_roller)
