#include <gtest/gtest.h>

#include "../../src/dnd_classes/character.hpp"

/*
class CharacterTests: public ::testing::Test {
public:
protected:
  Character pc = Character("Name");
};
*/

TEST(CharacterTests, TestDefaultName) {
  Character test = Character();
  std::string default_name = "PC";
  ASSERT_EQ(test.get_name(), default_name.c_str());
}

TEST(CharacterTests, TestOverloadedConstructionName) {
  Character test = Character("Name");
  std::string default_name = "PC";
  ASSERT_NE(test.get_name(), default_name.c_str());
}
