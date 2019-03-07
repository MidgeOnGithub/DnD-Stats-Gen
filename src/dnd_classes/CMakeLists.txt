add_library(DnD-Classes
    STATIC
        abilities.cpp
        character.cpp
        races.cpp
)

target_link_libraries(DnD-Classes
    PRIVATE
        nlohmann_json::nlohmann_json
)
