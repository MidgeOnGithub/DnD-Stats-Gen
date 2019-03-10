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
  std::array<int, 6> point_buy(dice_roller::Options& options);
  
  // Interface with user to assign scores to abilities
  void assign_generated_scores(Abilities& ab);

  // Pretty-print functions
  void print_set_of_scores(const std::array<int, 6>& scores);
  std::string summary_of_all_scores(Abilities& ab, const Score& flag);

}

#endif  // ABILITIES_SCRIPT_HPP
