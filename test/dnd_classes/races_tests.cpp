#include <gtest/gtest.h>

#include "../../src/dnd_classes/races.hpp"


TEST(RaceTests, CanInstantiateRacesClass) {
  json data = "";
  Race r = Race(data);
}
