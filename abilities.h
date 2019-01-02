
#ifndef DND_STATS_GEN_ABILITIES_H
#define DND_STATS_GEN_ABILITIES_H
#endif //DND_STATS_GEN_ABILITIES_H

#include <map>

class abilities {

public:

    // Add and construct based on parameter for a score_dict
    abilities();  // Constructor

    int get_ability_score(std::string name);  // Returns score assigned to ability (name)
    void set_ability_score(std::string name, int score = 0);  // Sets ability (name) to score s

    int get_score(int i);  // Returns score at index i
    void set_score(int i, int score);  // Sets index i to score s

    std::string get_name(int i);

    std::string print_scores(bool names_only = false);  // Pretty-prints the array or ability names
    std::string print_summary();  // Pretty-prints the dictionary

    void index_error(int code);  // Prints an error message and exits instead of using garbage memory


private:

    int scores[6] = {0, 0, 0, 0, 0, 0};  // Stores score values

    // List ability names in the order given by the official character creation sheet
    std::string names[6] = {"Strength", "Dexterity", "Constitution",
                             "Intelligence", "Wisdom", "Charisma"};

    std::map<std::string, int> score_dict; // Dictionary mapping the above

};
