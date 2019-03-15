#ifndef DND_CHARACTER_SCRIPTS_HPP
#define DND_CHARACTER_SCRIPTS_HPP

#include "../dnd_classes/character.hpp"

namespace CharacterScripts {

  std::string name_input();

  std::string write_summary(Character& pc);

}  // namespace CharacterScripts

#endif  // DND_CHARACTER_SCRIPTS_HPP
