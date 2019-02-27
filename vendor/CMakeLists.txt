#### Google's test suite
add_subdirectory(googletest EXCLUDE_FROM_ALL)
#### End GTest section

#### nlohmann's JSON library
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(json)
#### End JSON section
