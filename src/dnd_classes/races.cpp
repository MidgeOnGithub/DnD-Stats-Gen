#include <utility>

#include "races.hpp"

Race::Race(const json& race_data) {
  // TODO: Assign values to member variables from json data
}

Race::~Race() = default;

std::string Race::get_name() {
  return name;
}

void Race::set_name(std::string new_name) {
  name = std::move(new_name);
}

bool Race::is_adventure_league_compliant() {
  return adventure_league_compliance;
}

void Race::set_adventure_league_compliance(bool setting) {
  adventure_league_compliance = setting;
}
