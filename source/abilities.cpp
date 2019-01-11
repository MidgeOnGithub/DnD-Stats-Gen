
#include <iomanip>
#include <iostream>
#include <sstream>

#include "abilities.hpp"

abilities::abilities() {

    for (int i = 0; i < 6; i++)
    {
        score_dict[names[i]] = rolled_scores[i];  // Initialize a dictionary with names as keys, values of 0 (no arg needed)
    }
}

int abilities::get_ability_score(std::string name) {

    if (score_dict.find(name) == score_dict.end())
    {
        index_error(1);
    }

    return score_dict[name];
}

void abilities::set_ability_score(std::string name, int score) {

    if (score_dict.find(name) == score_dict.end())
    {
        index_error(2);
    }

    score_dict[name] = score;
}

std::string abilities::print_ability_scores() {

    // Use ostringstream as an easy way to format as if using std::cout
    std::ostringstream scores;
    scores << "[";
    for (int i = 0; i < 6; i++)
    {
        std::string name = get_ability_name(i);
        scores << get_ability_score(name);
        if (i < 5)  // Don't print a comma and space for the last element
        {
            scores << ", ";
        }
    }
    scores << "]" << std::endl;

    // Return as a string
    return scores.str();
}

int abilities::get_rolled_score(int i) {

    if (i > 5)
    {
        index_error(3);
    }

    return rolled_scores[i];
}

void abilities::set_rolled_score(int i, int score) {

    if (i > 5)
    {
        index_error(4);
    }

    rolled_scores[i] = score;
}

std::string abilities::print_rolled_scores() {

    // Use ostringstream as an easy way to format as if using std::cout
    std::ostringstream scores;
    scores << "[";
    for (int i = 0; i < 6; i++)
    {
        scores << get_rolled_score(i);

        if (i < 5)  // Don't print a comma and space for the last element
        {
            scores << ", ";
        }
    }
    scores << "]" << std::endl;

    // Return as a string
    return scores.str();
}

std::string abilities::get_ability_name(int i) {

    if (i > 5)
    {
        index_error(5);
    }

    return names[i];
}

std::string abilities::print_ability_summary() {

    // Use ostringstream as an easy way to format as if using std::cout
    std::ostringstream summary;
    summary << "Assigned ability scores:" << std::endl
            << "--------------------" << std::endl;
    for (int i = 0; i < 6; i++)
    {
        std::string ab_name = get_ability_name(i);
        summary << std::setw(18) << std::left << ab_name + ": "
                << std::setw(02) << std::right << score_dict[ab_name] << std::endl;
    }
    summary << "--------------------" << std::endl;

    // Return as a string
    return summary.str();
}

void abilities::index_error(int e_code) {

    switch(e_code)
    {
        case 1 : std::cout << "Name passed to get_ability_score is not an ability.";
                 exit(1);

        case 2 : std::cout << "Name passed to set_ability_score is not an ability.";
                 exit(2);

        case 3 : std::cout << "Index passed to get_score is out of range.";
                 exit(3);

        case 4 : std::cout << "Index passed to set_score is out of range.";
                 exit(4);

        case 5 : std::cout << "Index passed to get_name is out of range.";
                 exit(5);

        default : std::cout << "Unknown index_error while running an abilities class method.";
                  exit(9);
    }
}
