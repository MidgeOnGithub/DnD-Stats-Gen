#ifndef DND_ABILITIES_HPP
#define DND_ABILITIES_HPP

#include <map>

#include "dice_roller/dice.hpp"

class Abilities {

public:

    Abilities();

    // Script functions
    int method_choice();                               // Get the user's choice of below scripts for value generation
    void generate_3d6(dice_roller::Options &options);  // Dice roll generation method
    void generate_4d6(dice_roller::Options &options);  // Dice roll generation method
	//void point_buy(dice_roller::Options &options);   // Unimplemented generation method
    void assign_abilities();                           // Interface with user to assign rolled scores into dictionary
    // End Script Functions

    int get_ability_score(std::string ability);                  // Returns score assigned to ability
    void set_ability_score(std::string ability, int score = 0);  // Sets ability's score value
    std::string print_ability_scores();                          // Pretty-prints ability scores

    int get_score_modifier(int i);              // Returns score modifier of ability
    void set_score_modifier(int i, int score);  // Sets score modifier of ability

    int get_rolled_score(int i);              // Returns score at index i
    void set_rolled_score(int i, int score);  // Sets index i to score s
    std::string print_rolled_scores();        // Pretty-prints the rolled scores

    std::string get_ability_name(int i);  // Returns ability name (indexed by character sheet order)
                                          // No set_name method since ability names are pre-determined

    std::string print_ability_summary();  // Pretty-prints the ability dictionary

private:

    int generated_scores[6] = {0, 0, 0, 0, 0, 0};  // Stores generated score values
    int score_modifiers[6] = {0, 0, 0, 0, 0, 0};   // Stores ability score modifiers

    // List ability names by order on official character creation sheet
    const std::string names[6] = {"Strength", "Dexterity",
								  "Constitution", "Intelligence",
								  "Wisdom", "Charisma"};

    std::map<std::string, int> score_dict; // Dictionary mapping ability names to active scores

};

#endif //DND_ABILITIES_HPP
