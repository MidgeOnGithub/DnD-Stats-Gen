#include <iostream>
#include <sstream>
#include <string>

#include "abilities_scripts.hpp"
#include "character_scripts.hpp"


namespace CharacterScripts {

  std::string name_input() {
    std::string character_name;
    while (character_name.empty()) {
      std::cout << "Please give your character's name: ";
      getline(std::cin, character_name);
    }
    return character_name;
  }

  std::string write_summary(Character& pc) {
    // Use ostringstream as an easy way to format as if using std::cout
    std::ostringstream summary;
    // Basic info
    summary << "Name: " << pc.get_name() << "\n";
    // TODO: summary << race, class, etc.  <-unimplemented
    summary << "Level: 1" << std::endl << "\n";
    // Ability-related info
    Score flag = Score::active;
    summary << AbilitiesScripts::summary_of_all_scores(pc.abilities, flag);
    return summary.str();
  }

}  // namespace CharacterScripts
