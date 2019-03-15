#ifndef DND_ABILITIES_HPP
#define DND_ABILITIES_HPP

#include <array>
#include <map>
#include <string>

#include "../dice_roller/dice.hpp"


enum class Ability {
  Strength     = 0,
  Dexterity    = 1,
  Constitution = 2,
  Intelligence = 3,
  Wisdom       = 4,
  Charisma     = 5
};

constexpr std::array<Ability, 6> All_Abilities = {
  Ability::Strength, Ability::Dexterity, Ability::Constitution,
  Ability::Intelligence, Ability::Wisdom, Ability::Charisma
};

enum class Score {
  generated,
  modifier,
  active,
};

struct Ability_Scores {
  int generated = 0;
  int modifier = 0;
  int active = 0;
};

// Ability names indexed by order on official character sheet
const std::array<std::string, 6> ability_names = {
  "Strength", "Dexterity",
  "Constitution", "Intelligence",
  "Wisdom", "Charisma"
};

class Abilities {
public:
  Abilities();
  explicit Abilities(std::array<int, 6>& generated_scores);
  virtual ~Abilities();

  int get_score(const Ability& ability, const Score& flag);
  void set_score(const Ability& ability, const Score& flag,
                 int value);

  std::array<int, 6> get_all_scores_of_type(const Score& flag);
  void set_all_scores_of_type(const Score& flag, std::array<int, 6>& scores);
private:
  // Dictionary mapping ability names to active scores
  std::map<Ability, Ability_Scores> ability_scores;
  void update_active_score(const Ability& ability);
};

#endif  // DND_ABILITIES_HPP
