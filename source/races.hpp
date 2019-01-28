#ifndef DND_RACE_HPP
#define DND_RACE_HPP

#include <map>
#include <string>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

// Script functions
json race_choice(); // Get the user's choice of character race
// End script functions

class Race
{

public:
	Race(json stats);

	std::string get_name();
	void set_name(std::string new_name);

	bool is_adventure_league_compliant();
	void set_adventure_league_compliance(bool setting);
	
protected:

	std::string name;
	
	bool adventure_league_compliance;  // Indicates if the race is Adventure League-compliant

	struct Speed {
		int standard;
		int climbing;
		int flying;
		int swimming;
	};

	const std::map<std::string, int> ability_modifiers;

};


#endif //DND_RACE_HPP
