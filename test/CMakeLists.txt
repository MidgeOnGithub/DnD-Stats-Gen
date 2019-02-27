add_executable(Tests test_main.cpp)

target_sources(Tests
    PRIVATE
        dnd_classes/abilities_tests.cpp
        dnd_classes/character_tests.cpp
        dnd_classes/races_tests.cpp
)

target_link_libraries(Tests
    PRIVATE
        DnD-Classes
        gmock
        gtest
        nlohmann_json::nlohmann_json
)
