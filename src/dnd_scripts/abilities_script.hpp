#ifndef ABILITIES_SCRIPT_HPP
#define ABILITIES_SCRIPT_HPP

#include <array>
#include <string>

#include "../dnd_classes/abilities.hpp"
#include "../dice_roller/dice.hpp"
#include "../dice_roller/dnd_dice.hpp"


namespace AbilityScripts {

  int method_choice(); // Get the user's choice of score generation method

  std::array<int, 6> generate_3d6(dice_roller::Options& options);
  std::array<int, 6> generate_4d6(dice_roller::Options& options);
  std::array<int, 6> point_buy(dice_roller::Options &options);
  
  // Interface with user to assign scores to abilities
  void assign_generated_scores(Abilities ab);

  // Pretty-print method
  std::string write_score_summary(Abilities ab, Score flag);

}

#endif  // ABILITIES_SCRIPT_HPP
