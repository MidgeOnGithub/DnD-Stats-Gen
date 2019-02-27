#include "races.hpp"

Race::Race(json race_data)
{
  // TODO: Assign values to member variables from json data
}

std::string Race::get_name()
{
  return name;
}

void Race::set_name(std::string new_name)
{
  name = new_name;
}

bool Race::is_adventure_league_compliant()
{
  return adventure_league_compliance;
}

void Race::set_adventure_league_compliance(bool setting)
{
  adventure_league_compliance = setting;
}
