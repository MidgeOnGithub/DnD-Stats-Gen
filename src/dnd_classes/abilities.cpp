#include <array>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "abilities.hpp"


Abilities::Abilities() = default;

Abilities::Abilities(std::array<int, 6> generated_scores) {
  for (short i = 0; i < 6; ++i) {
    Ability ability = All_Abilities[i];
    set_score(ability, Score::generated, generated_scores[i]);
  };
}

int Abilities::get_score(Ability ability, Score flag) {
  switch (flag) {
    case Score::active :
      return ability_scores[ability].active;
    case Score::generated :
      return ability_scores[ability].generated;
    case Score::modifier :
      return ability_scores[ability].modifier;
  }
}

void Abilities::set_score(Ability ability, Score flag, int value) {
  if (flag == Score::generated) {
    // 18 is the maximum value that may be generated
    value = (value > 18) ? 18 : value;
    value = (value < 03) ? 03 : value;
    ability_scores[ability].generated = value;
  } else {
    ability_scores[ability].modifier = value;
  }
  update_active_score(ability);
}

void Abilities::update_active_score(Ability ability) {
  int value = ability_scores[ability].generated;
  value += ability_scores[ability].modifier;
  // 20 is the maximum active score, 0 is the minimum
  value = (value > 20) ? 20 : value;
  value = (value < 00) ? 00 : value;
  ability_scores[ability].active = value;
}

std::array<int, 6> Abilities::get_all_scores_of_type(Score flag) {
  std::array<int, 6> scores = {};
  for (int i = 0; i < 6; ++i) {
    scores[i] = get_score(All_Abilities[i], flag);
  };
  return scores;
}

void Abilities::set_all_scores_of_type(Score flag,
                                       std::array<int, 6>& scores) {
  for (int i = 0; i < 6; ++i) {
    set_score(All_Abilities[i], flag, scores[i]);
  }
}
