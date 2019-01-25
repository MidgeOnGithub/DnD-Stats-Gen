#include "abilities.hpp"
#include "character.hpp"

Character::Character() {}
// Overloaded constructor to set name
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
	this->name = new_name;
}
