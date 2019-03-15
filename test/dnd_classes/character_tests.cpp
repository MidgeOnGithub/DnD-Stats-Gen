#include <gtest/gtest.h>

#include <array>

#include "../../src/dnd_classes/character.hpp"

static std::array<int, 6> gen_scores = {3, 4, 5, 6, 7, 8};
static std::array<int, 6> mod_scores = {0, 1, 0, 1, 2, 0};

class CharacterBuilderTests : public ::testing::Test {
public:
protected:
  std::string test_name = "BuilderTest";
  CharacterBuilder builder = CharacterBuilder(test_name).give_generated_scores(gen_scores)
                                                        .give_score_modifiers(mod_scores);
};

TEST_F(CharacterBuilderTests, TestCharacterMemberIsEquivalent) {
  Character by_create = Character::Builder().give_name(test_name)
                                           .give_generated_scores(gen_scores)
                                           .give_score_modifiers(mod_scores);
  ASSERT_EQ(builder.pc.get_name(), by_create.get_name());
  ASSERT_EQ(builder.pc.abilities.get_all_scores_of_type(Score::active),
            by_create.abilities.get_all_scores_of_type(Score::active));
}

class CharacterLevelerTests: public ::testing::Test {
public:
protected:
  Character character = Character::Builder().give_name("LevelTest")
                                            .give_generated_scores(gen_scores)
                                            .give_score_modifiers(mod_scores);
  CharacterLeveler leveler = CharacterLeveler(character);
};

TEST_F(CharacterLevelerTests, TestLevelAdvancesAtThresholds) {
  ASSERT_EQ(character.get_level(), 1);
  leveler.give_experience(300);         // Level 2: 300
  ASSERT_EQ(character.get_level(), 2);
  leveler.give_experience(600);         // Level 3: 900
  ASSERT_EQ(character.get_level(), 3);
  leveler.give_experience(1800);        // Level 4: 2700
  ASSERT_EQ(character.get_level(), 4);
  leveler.give_experience(3800);        // Level 5: 6500
  ASSERT_EQ(character.get_level(), 5);
  leveler.give_experience(7500);        // Level 6: 14000
  ASSERT_EQ(character.get_level(), 6);
  leveler.give_experience(9000);        // Level 7: 23000
  ASSERT_EQ(character.get_level(), 7);
  leveler.give_experience(11000);       // Level 8: 34000
  ASSERT_EQ(character.get_level(), 8);
  leveler.give_experience(14000);       // Level 9: 48000
  ASSERT_EQ(character.get_level(), 9);
  leveler.give_experience(16000);       // Level 10: 64000
  ASSERT_EQ(character.get_level(), 10);
  leveler.give_experience(21000);       // Level 11: 85000
  ASSERT_EQ(character.get_level(), 11);
  leveler.give_experience(15000);       // Level 12: 100000
  ASSERT_EQ(character.get_level(), 12);
  leveler.give_experience(20000);       // Level 13: 120000
  ASSERT_EQ(character.get_level(), 13);
  leveler.give_experience(20000);       // Level 14: 140000
  ASSERT_EQ(character.get_level(), 14);
  leveler.give_experience(25000);       // Level 15: 165000
  ASSERT_EQ(character.get_level(), 15);
  leveler.give_experience(30000);       // Level 16: 195000
  ASSERT_EQ(character.get_level(), 16);
  leveler.give_experience(30000);       // Level 17: 225000
  ASSERT_EQ(character.get_level(), 17);
  leveler.give_experience(40000);       // Level 18: 265000
  ASSERT_EQ(character.get_level(), 18);
  leveler.give_experience(40000);       // Level 19: 305000
  ASSERT_EQ(character.get_level(), 19);
  leveler.give_experience(50000);       // Level 20: 355000
  ASSERT_EQ(character.get_level(), 20);
  leveler.give_experience(100000000);   // No levels beyond 20
  ASSERT_EQ(character.get_level(), 20);
}

TEST_F(CharacterLevelerTests, TestAdvancesMultipleLevelsIfNeeded) {
  leveler.give_experience(355000);
  ASSERT_EQ(character.get_level(), 20);
}

TEST_F(CharacterLevelerTests, TestLevelMethodUpdatesExperienceToThreshold) {
  leveler.increase_level(4);
  ASSERT_EQ(character.get_experience(), 6500);
}

TEST_F(CharacterLevelerTests, TestLevelerReturnsEditedCharacter) {
  leveler.give_experience(300).increase_level(3);
  Character new_pc_that_should_be_level_5 = leveler;
  ASSERT_EQ(new_pc_that_should_be_level_5.get_level(), 5);
}

TEST_F(CharacterLevelerTests, TestCharacterMemberIsEquivalent) {
  character.Leveler().give_experience(300).increase_level(3);
  ASSERT_EQ(character.get_level(), 5);
  ASSERT_EQ(character.get_experience(), 6500);
}
