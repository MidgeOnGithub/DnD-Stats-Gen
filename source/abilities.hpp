
#ifndef DND_ABILITIES_HPP
#define DND_ABILITIES_HPP

#include <map>

class abilities {

    friend void generate_3d6(abilities &ab, bool verbose = false, bool slow = false, int wait_time = 750);
    friend void generate_4d6(abilities &ab, bool verbose = false, bool slow = false, int wait_time = 750);
    friend void assign_abilities(abilities &ab);

public:

    abilities();  // Constructor

    int get_ability_score(std::string name);  // Returns score assigned to ability (name)
    void set_ability_score(std::string name, int score = 0);  // Sets ability (name) to score s
    std::string print_ability_scores();  // Pretty-prints final ability scores

    int get_rolled_score(int i);  // Returns score at index i
    void set_rolled_score(int i, int score);  // Sets index i to score s
    std::string print_rolled_scores();  // Pretty-prints the rolled scores

    std::string get_ability_name(int i);  // Returns ability name (indexed by character sheet order)
    // No set_name method exists because ability names are pre-determined in DnD

    std::string print_ability_summary();  // Pretty-prints the dictionary

    void index_error(int e_code);  // Prints an error message and exits instead of using garbage memory


private:

    int rolled_scores[6] = {0, 0, 0, 0, 0, 0};  // Stores rolled score values

    // List ability names by order on official character creation sheet
    const std::string names[6] = {"Strength", "Dexterity", "Constitution",
                                  "Intelligence", "Wisdom", "Charisma"};

    std::map<std::string, int> score_dict; // Dictionary mapping ability names to "acting" score

};

#endif //DND_ABILITIES_HPP
