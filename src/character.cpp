#include <iostream>
#include <sstream>

#include "abilities.hpp"
#include "character.hpp"

Character::Character()
{
	Character::set_name("");
}
// Overloaded constructor to set name directly if given
Character::Character(std::string given_name)
{
	Character::set_name(given_name);
}

std::string Character::get_name()
{
	return this->name;
}

void Character::set_name(std::string new_name)
{
	if (new_name.empty())
		this->name = Character::get_name_input();
	else
		this->name = new_name;
}

std::string Character::print_character_summary()
{
	// Use ostringstream as an easy way to format as if using std::cout
	std::ostringstream summary;
	summary << "Name: " << this->get_name() << std::endl;
	//summary << race, class, etc.
	summary << "Level: 1" << std::endl << std::endl;
	summary << this->ab.print_ability_summary() << std::endl;
	return summary.str();
}

std::string Character::get_name_input()
{
	std::string character_name;
	while (character_name.empty())
	{
		std::cout << "Please give your character's name: ";
		getline(std::cin, character_name);
	}
	return character_name;
}
