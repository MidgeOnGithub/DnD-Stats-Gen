#include <gtest/gtest.h>

#include "../../src/dnd_classes/character.hpp"

class CharacterTests : public ::testing::Test {
public:
protected:
  CharacterBuilder builder = CharacterBuilder();
  std::string test_name = "BuilderTest";
  std::array<int, 6> scores = {3, 4, 5, 6, 7, 8};
  CharacterBuilder with_name = CharacterBuilder(test_name);
};

TEST_F(CharacterTests, TestBuilderFluency) {
  std::string name = "FluentBuilder";
  builder.give_name(name).give_generated_scores(scores);
  ASSERT_EQ(builder.pc.get_name(), name.c_str());
  ASSERT_EQ(builder.pc.ab.get_all_scores_of_type(Score::generated), scores);
}

TEST_F(CharacterTests, TestCharacterCreateMethodIsEquivalent) {
  Character by_create = Character::create().give_name(test_name).give_generated_scores(scores);
  ASSERT_EQ(with_name.pc.get_name(), by_create.get_name());
}
