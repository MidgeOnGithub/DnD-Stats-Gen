#[[Using https://github.com/Orphis/boost-cmake/tree/master/libs
for easy cross-platform Boost inclusion.]]
add_subdirectory(boost-cmake)
#[[Per boost-cmake README.md example:
Link boost libs which need compiled separately from header-only libs,
i.e., libraries which are not header-only.]]
