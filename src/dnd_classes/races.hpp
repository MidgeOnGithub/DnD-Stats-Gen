#ifndef DND_RACE_HPP
#define DND_RACE_HPP

#include <string>
#include <vector>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "abilities.hpp"


struct Speeds {
  unsigned int standard;
  unsigned int climbing;
  unsigned int flying;
  unsigned int swimming;
};

// Script functions
json race_choice(); // Get the user's choice of character race
// End script functions

class Race {

public:
  explicit Race(const json& race_data);

  virtual ~Race();

  std::string get_name();
  void set_name(std::string new_name);

  bool is_adventure_league_compliant();
  void set_adventure_league_compliance(bool setting);

protected:

  std::string name;
  bool adventure_league_compliance;
  Speeds speeds;

  int height;
  int weight;

  std::vector<short> ability_modifiers;
};


#endif //DND_RACE_HPP
