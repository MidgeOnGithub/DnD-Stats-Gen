add_library(DnD-Scripts
    STATIC
        abilities_script.cpp
        character_script.cpp
        races_script.cpp
)

target_link_libraries(DnD-Scripts
    PRIVATE
        DnD-Dice
        nlohmann_json::nlohmann_json
)
