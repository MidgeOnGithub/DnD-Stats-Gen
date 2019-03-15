#include "abilities.hpp"
#include "character.hpp"

Character::Character() = default;
Character::~Character() = default;

CharacterBuilder Character::Builder() { return CharacterBuilder(); }
CharacterLeveler Character::Leveler() { return CharacterLeveler(*this); }

std::string Character::get_name() const { return name; }
unsigned int Character::get_level() const { return level; }
unsigned int Character::get_experience() const { return experience; }


// CharacterBuilder is a friend of Character
CharacterBuilder::CharacterBuilder() = default;
CharacterBuilder::CharacterBuilder(std::string name) { pc.name = std::move(name); }
CharacterBuilder::~CharacterBuilder() = default;

CharacterBuilder& CharacterBuilder::give_name(std::string name) {
  pc.name = std::move(name);
  return *this;
};

CharacterBuilder& CharacterBuilder::give_generated_scores(std::array<int, 6>& scores) {
  pc.abilities = Abilities(scores);
  return *this;
}

CharacterBuilder& CharacterBuilder::give_score_modifiers(std::array<int, 6>& modifiers) {
  pc.abilities.set_all_scores_of_type(Score::modifier, modifiers);
  return *this;
}

CharacterBuilder::operator Character() const { return this->pc; }


// CharacterLeveler is a friend of Character
CharacterLeveler::CharacterLeveler(Character& pc) : pc(pc) {}
CharacterLeveler::~CharacterLeveler() = default;

CharacterLeveler::operator Character() const { return this->pc; }

constexpr std::array<unsigned int, 19> level_up_thresholds = {
 300, 900, 2700, 6500, 14000, 23000, 34000, 48000, 64000, 85000,
 100000, 120000, 140000, 165000, 195000, 225000, 265000, 305000, 355000
};

unsigned int appropriate_level(const unsigned int total_experience) {
  unsigned int deserved_level = 1;
  for (auto& needed : level_up_thresholds) {
    if (total_experience < needed)
      break;
    ++deserved_level;
  }
  return deserved_level;
}

CharacterLeveler& CharacterLeveler::give_experience(const unsigned int experience) {
  this->pc.experience += experience;
  unsigned int current_level = pc.level;
  if (current_level < 20) {
    unsigned int deserved_level = appropriate_level(this->pc.experience);
    if (current_level < deserved_level)
      increase_level(deserved_level - current_level);
  }
  return *this;
}

CharacterLeveler& CharacterLeveler::increase_level(const unsigned int how_many) {
  unsigned int current_level = pc.level;
  unsigned int proposed_level = current_level + how_many;
  // Max level is 20
  this->pc.level = (proposed_level > 20) ? current_level : proposed_level;
  // Access level_up_thresholds with (index - 2) because it is only
  // a 19-size array, where index 0 represents level 2's threshold,
  // index 18 represents level 20's threshold, etc.
  this->pc.experience = level_up_thresholds[this->pc.level - 2];
  return *this;
}