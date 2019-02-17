#### Boost dependencies
find_package(Boost 1.65.0 REQUIRED COMPONENTS program_options random)

if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()
# Must explicitly link Boost libraries which require compilation
target_link_libraries(DnD-Stats-Gen
    PUBLIC
        Boost::program_options
        Boost::random
)
#### End Boost section

# Don't build tests for the json library
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json)

# Link everything to our project
target_link_libraries(DnD-Stats-Gen
    PRIVATE
        nlohmann_json::nlohmann_json
)
