add_library(DnD-Scripts
    STATIC
    abilities_scripts.cpp
    character_scripts.cpp
    race_scripts.cpp
)

target_link_libraries(DnD-Scripts
    PRIVATE
        DnD-Dice
)
