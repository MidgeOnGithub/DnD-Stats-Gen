#include <iostream>

#include "abilities.hpp"
#include "../dnd_scripts/abilities_script.hpp"
#include "character.hpp"


Character::Character() = default;
// Overloaded constructor sets name directly if given
Character::Character(const std::string given_name) {
  set_name(given_name);
}

std::string Character::get_name() {
  return name;
}

void Character::set_name(const std::string new_name) {
  name = new_name;
}
