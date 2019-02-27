#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "races_script.hpp"


std::vector<json> process_raw_data(json data) {
  // TODO: Get each race object and push into vector, check this works
  std::vector<json> races;
  for (auto& object : data) {
    races.push_back(object);
  }
  return races;
}

// TODO: Finish after doing process_raw_data
std::string write_race_prompt(json races, bool subraces = false) {
  // Use ostringstream as an easy way to format as if using std::cout
  std::ostringstream prompt;
  for (json& race : races) {
    if (subraces) {
      // TODO: Search for subrace and variant
    } else {
      // TODO: Search for races
    }
  }
  return prompt.str();
}

bool has_subrace_or_variant(json race) {
  // TODO: Check this works
  return (!race["subrace"].empty() && !race["variant"].empty());
}

namespace RaceScripts {
  
  json raw_import_data() {

    json data;
    // Populate return JSON string using an existing json file
    std::ifstream input_file("../data/races.json");
    if (!input_file.is_open()) {
      std::cout << "Failed to open input_file.";
      // TODO: Handle file opening errors better
      exit(3);
    }
    input_file >> data;
    input_file.close();
    return data;
  }

  json race_choice() {
    json data = raw_import_data();
    std::vector<json> races = process_raw_data(data);

    std::string prompt = write_race_prompt(races);
    json chosen_race;
    // TODO: Interface with user to select race (might wanna function out)
    if (has_subrace_or_variant(chosen_race))
      std::string subrace_prompt = write_race_prompt(chosen_race, true);
    // TODO: Interface with user to select subrace (might wanna function out)
    return chosen_race;
  }
  
}
