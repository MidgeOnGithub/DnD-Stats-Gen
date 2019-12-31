#include <array>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "abilities.hpp"


Abilities::Abilities() = default;

Abilities::Abilities(std::array<int, 6>& generated_scores) {
  set_all_scores_of_type(Score::generated, generated_scores);
}

Abilities::~Abilities() = default;

int Abilities::get_score(const Ability& ability, const Score& flag) {
  if (flag == Score::active)
    return ability_scores[ability].active;
  else if (flag == Score::generated)
    return ability_scores[ability].generated;
  // If not from the above, it must be the modifier
  return ability_scores[ability].modifier;
}

void Abilities::set_score(const Ability& ability, const Score& flag, int value) {
  if (flag == Score::generated) {
    // 18 is the maximum value that may be generated, 3 is the minimum
    value = (value > 18) ? 18 : value;
    value = (value < 03) ? 03 : value;
    ability_scores[ability].generated = value;
  } else if (flag == Score::modifier) {
    ability_scores[ability].modifier = value;
  } else {
    ability_scores[ability].active = value;
  }
  update_active_score(ability);
}

void Abilities::update_active_score(const Ability& ability) {
  auto& score_trio = ability_scores[ability];
  int combined = score_trio.generated + score_trio.modifier;
  // 20 is the maximum active score, 0 is the minimum
  combined = (combined > 20) ? 20 : combined;
  combined = (combined < 00) ? 00 : combined;
  score_trio.active = combined;
}

std::array<int, 6> Abilities::get_all_scores_of_type(const Score& flag) {
  std::array<int, 6> scores = {};
  for (int i = 0; i < 6; ++i) {
    scores[i] = get_score(All_Abilities[i], flag);
  }
  return scores;
}

void Abilities::set_all_scores_of_type(const Score& flag, std::array<int, 6>& scores) {
  for (int i = 0; i < 6; ++i) {
    set_score(All_Abilities[i], flag, scores[i]);
  }
}
