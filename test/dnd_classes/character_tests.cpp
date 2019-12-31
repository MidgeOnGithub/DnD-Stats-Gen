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
  Character by_builder = Character::Builder().give_name(test_name)
                                           .give_generated_scores(gen_scores)
                                           .give_score_modifiers(mod_scores);
  ASSERT_EQ(builder.pc.get_name(), by_builder.get_name());
  ASSERT_EQ(builder.pc.abilities.get_all_scores_of_type(Score::active),
            by_builder.abilities.get_all_scores_of_type(Score::active));
}

class CharacterLevelerTests: public ::testing::Test {
public:
protected:
  Character character = Character::Builder().give_name("LevelTest")
                                            .give_generated_scores(gen_scores)
                                            .give_score_modifiers(mod_scores);
  CharacterLeveler leveler = CharacterLeveler(character);
};

TEST_F(CharacterLevelerTests, TestLevelAdvancesAtExperienceThresholds) {
  ASSERT_EQ(character.get_level(), 1);
  leveler.give_experience(300);         // Level 02: 300
  ASSERT_EQ(character.get_level(), 2);
  leveler.give_experience(600);         // Level 03: 900
  ASSERT_EQ(character.get_level(), 3);
  leveler.give_experience(1800);        // Level 04: 2700
  ASSERT_EQ(character.get_level(), 4);
  leveler.give_experience(3800);        // Level 05: 6500
  ASSERT_EQ(character.get_level(), 5);
  leveler.give_experience(7500);        // Level 06: 14000
  ASSERT_EQ(character.get_level(), 6);
  leveler.give_experience(9000);        // Level 07: 23000
  ASSERT_EQ(character.get_level(), 7);
  leveler.give_experience(11000);       // Level 08: 34000
  ASSERT_EQ(character.get_level(), 8);
  leveler.give_experience(14000);       // Level 09: 48000
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

TEST_F(CharacterLevelerTests, TestLevelRegressesAtExperienceThresholds) {
  leveler.give_experience(365000);        // Level 20: 355000
  ASSERT_EQ(character.get_level(), 20);
  leveler.remove_experience(10001);       // Level 19: 305000
  ASSERT_EQ(character.get_level(), 19);
  leveler.remove_experience(50000);       // Level 18: 265000
  ASSERT_EQ(character.get_level(), 18);
  leveler.remove_experience(40000);       // Level 17: 225000
  ASSERT_EQ(character.get_level(), 17);
  leveler.remove_experience(40000);       // Level 16: 195000
  ASSERT_EQ(character.get_level(), 16);
  leveler.remove_experience(30000);       // Level 15: 165000
  ASSERT_EQ(character.get_level(), 15);
  leveler.remove_experience(30000);       // Level 14: 140000
  ASSERT_EQ(character.get_level(), 14);
  leveler.remove_experience(25000);       // Level 13: 120000
  ASSERT_EQ(character.get_level(), 13);
  leveler.remove_experience(20000);       // Level 12: 100000
  ASSERT_EQ(character.get_level(), 12);
  leveler.remove_experience(20000);       // Level 11: 85000
  ASSERT_EQ(character.get_level(), 11);
  leveler.remove_experience(15000);       // Level 10: 64000
  ASSERT_EQ(character.get_level(), 10);
  leveler.remove_experience(21000);       // Level 09: 48000
  ASSERT_EQ(character.get_level(), 9);
  leveler.remove_experience(16000);       // Level 08: 34000
  ASSERT_EQ(character.get_level(), 8);
  leveler.remove_experience(14000);       // Level 07: 23000
  ASSERT_EQ(character.get_level(), 7);
  leveler.remove_experience(11000);       // Level 06: 14000
  ASSERT_EQ(character.get_level(), 6);
  leveler.remove_experience(9000);        // Level 05: 6500
  ASSERT_EQ(character.get_level(), 5);
  leveler.remove_experience(7500);        // Level 04: 2700
  ASSERT_EQ(character.get_level(), 4);
  leveler.remove_experience(3800);        // Level 03: 900
  ASSERT_EQ(character.get_level(), 3);
  leveler.remove_experience(1800);        // Level 02: 300
  ASSERT_EQ(character.get_level(), 2);
  leveler.remove_experience(899);         // Level 01: 0
  ASSERT_EQ(character.get_level(), 1);
  leveler.remove_experience(9999999);     // No levels below 1.
  ASSERT_EQ(character.get_level(), 1);
}

TEST_F(CharacterLevelerTests, TestExperiencePersistsAfterLevelingUp) {
  leveler.give_experience(1500); // Level 3: 900.
  leveler.give_experience(2000); // Level 4: 2700.
  leveler.give_experience(3500); // Level 5: 6500.
  ASSERT_EQ(character.get_level(), 5);
  ASSERT_EQ(character.get_experience(), 7000);
}

TEST_F(CharacterLevelerTests, TestExperiencePersistsAfterLevelingDown) {
  leveler.give_experience(7000);   // Level 5: 6500.
  ASSERT_EQ(character.get_level(), 5);
  leveler.remove_experience(4000); // Level 4: 2700.
  leveler.remove_experience(1500); // Level 3: 900.
  ASSERT_EQ(character.get_level(), 3);
  ASSERT_EQ(character.get_experience(), 1500);
}

TEST_F(CharacterLevelerTests, TestExperienceAdvancesMultipleLevelsWhenAppropriate) {
  leveler.give_experience(7000);
  ASSERT_EQ(character.get_level(), 5);  // threshold = 6500
  leveler.give_experience(30000);
  ASSERT_EQ(character.get_level(), 8);  // threshold = 34000
  leveler.give_experience(320000);
  ASSERT_EQ(character.get_level(), 20); // threshold = 355000
}

TEST_F(CharacterLevelerTests, TestExperienceRemovesMultipleLevelsWhenAppropriate) {
  leveler.give_experience(400000);
  ASSERT_EQ(character.get_level(), 20);  // Level 20: 355000
  leveler.remove_experience(200000);
  ASSERT_EQ(character.get_level(), 16);  // Level 16: 195000
  leveler.remove_experience(150000);
  ASSERT_EQ(character.get_level(), 9);   // Level 09: = 48000
}

TEST_F(CharacterLevelerTests, TestDirectlyIncreasingLevelSetsExperienceToThreshold) {
  leveler.increase_level_by(4);  // Now level 5.
  ASSERT_EQ(character.get_experience(), 6500);
  leveler.increase_level_by(2);  // Now level 7.
  ASSERT_EQ(character.get_experience(), 23000);
}

TEST_F(CharacterLevelerTests, TestDirectlyDecreasingLevelSetsExperienceToThreshold) {
  leveler.increase_level_by(19);  // Now level 20.
  ASSERT_EQ(character.get_experience(), 355000);
  leveler.decrease_level_by(4);   // Now level 16.
  ASSERT_EQ(character.get_experience(), 195000);
  leveler.decrease_level_by(4);   // Now level 12.
  ASSERT_EQ(character.get_experience(), 100000);
}

TEST_F(CharacterLevelerTests, TestLevelerReturnsEditedCharacter) {
  leveler.give_experience(300).increase_level_by(3);
  Character new_pc_that_should_be_level_5 = leveler;
  ASSERT_EQ(new_pc_that_should_be_level_5.get_level(), 5);
}

TEST_F(CharacterLevelerTests, TestCharacterMemberIsEquivalent) {
  character.Leveler().give_experience(300).increase_level_by(3);
  ASSERT_EQ(character.get_level(), 5);
  ASSERT_EQ(character.get_experience(), 6500);
}
