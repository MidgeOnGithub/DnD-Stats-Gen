#[[
Using https://github.com/Orphis/boost-cmake/tree/master/libs
for easy cross-platform Boost inclusion.
]]
add_subdirectory(boost-cmake)

#[[
Per boost-cmake README.md example:
Link boost libs which need compiled separately from header-only libs,
i.e., libraries which are not header-only.
]]
target_link_libraries(DnD-Stats-Gen
    PUBLIC
        Boost::program_options
        Boost::random
)

# Don't build tests for the json library
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json)
target_link_libraries(DnD-Stats-Gen
    PRIVATE
        nlohmann_json::nlohmann_json
)
