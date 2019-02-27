#include <array>
#include <string>

#include <gtest/gtest.h>

#include "../../src/dnd_classes/abilities.hpp"


class AbilitiesTests : public ::testing::Test {
public:
protected:
  std::array<int, 6> constructor_scores = {1, 19, 57, 2, 8, 13};
  std::array<int, 6> corrected_scores = {3, 18, 18, 3, 8, 13};
  Abilities ab = Abilities(constructor_scores);
  std::string correct_names[6] = {"Strength", "Dexterity",
                                  "Constitution","Intelligence",
                                  "Wisdom", "Charisma"};
};

TEST_F(AbilitiesTests, EnumValuesAreCorrect) {
  ASSERT_EQ(0, int(Ability::Strength));
  ASSERT_EQ(1, int(Ability::Dexterity));
  ASSERT_EQ(2, int(Ability::Constitution));
  ASSERT_EQ(3, int(Ability::Intelligence));
  ASSERT_EQ(4, int(Ability::Wisdom));
  ASSERT_EQ(5, int(Ability::Charisma));
}

TEST_F(AbilitiesTests, NamesInClassAreCorrect) {
  for (short i = 0; i < 6; ++i) {
    std::string correct = correct_names[i];
    std::string name_in_class = ability_names[i];
    ASSERT_STREQ(name_in_class.c_str(), correct.c_str());
  }
}

TEST_F(AbilitiesTests, TestGeneratedScoresNormalization) {
  for (const Ability& ability : All_Abilities) {
    ASSERT_LE(ab.get_score(ability, Score::generated), 18);
    ASSERT_GE(ab.get_score(ability, Score::generated), 03);
  }
}

TEST_F(AbilitiesTests, TestActiveScoreUpdatesAfterSetScore) {
  Ability str = Ability::Strength;
  ab.set_score(str, Score::modifier, 3);
  int str_score = ab.get_score(str, Score::active);
  ASSERT_EQ(str_score, corrected_scores[0] + 3);
}

TEST_F(AbilitiesTests, TestActiveScoresNormalization) {
  ab.set_score(Ability::Wisdom, Score::modifier, 50);
  ASSERT_LE(ab.get_score(Ability::Wisdom, Score::active), 20);
}

TEST_F(AbilitiesTests, TestGetAllScoresOfTypeReturn) {
  std::array<int, 6> scores;
  scores = ab.get_all_scores_of_type(Score::generated);
  for (int i = 0; i < 6; ++i) {
    ASSERT_EQ(scores[i], corrected_scores[i]);
  }
}

TEST_F(AbilitiesTests, TestDefaultConstructorActiveScores) {
  Abilities test = Abilities();
  for (const Ability& ability : All_Abilities) {
    ASSERT_EQ(0, test.get_score(ability, Score::active));
  }
}
