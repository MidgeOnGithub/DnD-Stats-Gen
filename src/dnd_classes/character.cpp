#include <iostream>

#include "abilities.hpp"
#include "../dnd_scripts/abilities_script.hpp"
#include "character.hpp"

Character::Character() = default;
Character::~Character() = default;

CharacterBuilder Character::create() {
  return CharacterBuilder();
}

std::string Character::get_name() {
  return name;
}


// CharacterBuilder is a Friend of Character
CharacterBuilder::CharacterBuilder() = default;

CharacterBuilder::CharacterBuilder(std::string name) {
  pc = Character();
  pc.name = std::move(name);
};

CharacterBuilder::~CharacterBuilder() = default;

CharacterBuilder& CharacterBuilder::give_generated_scores(std::array<int, 6> &scores) {
  pc.ab = Abilities(scores);
  return *this;
}

CharacterBuilder& CharacterBuilder::give_name(std::string name) {
  pc.name = std::move(name);
  return *this;
};

CharacterBuilder::operator Character() const {
  Character character = this->pc;
  this->~CharacterBuilder();
  return character;
}
