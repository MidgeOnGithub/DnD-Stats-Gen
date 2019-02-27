add_library(DnD-Dice 
	STATIC
		dice.cpp
		dnd_dice.cpp
)


target_link_libraries(DnD-Dice
    PRIVATE
		Boost::random
)
