add_executable(DnD main.cpp)

#### BOOST Libraries
set(Boost_USE_STATIC_LIBS ON) 
find_package(Boost REQUIRED COMPONENTS program_options random)
#### End BOOST Section

add_subdirectory(dice_roller)  # DnD-Dice Lib
add_subdirectory(dnd_classes)  # DnD-Classes Lib
add_subdirectory(dnd_scripts)  # DnD-Scripts Lib

target_link_libraries(DnD
    PRIVATE
		-static
	    Boost::program_options
        DnD-Dice
        DnD-Classes
        DnD-Scripts
)
