
#include <iostream>
#include <iomanip>

#include "abilities.h"

abilities::abilities() {

    for (int i = 0; i < 6; i++)
    {
        score_dict[names[i]] = scores[i];  // Initialize a dictionary with names as keys, values of 0 (no arg needed)
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

int abilities::get_score(int i) {

    if (i > 5)
    {
        index_error(3);
    }

    return scores[i];
}

void abilities::set_score(int i, int score) {

    if (i > 5)
    {
        index_error(4);
    }

    scores[i] = score;
}

std::string abilities::get_name(int i) {

    if (i > 5)
    {
        index_error(5);
    }

    return names[i];
}

std::string abilities::print_scores(bool names_only) {

    // Use ostringstream as an easy way to format as if using std::cout
    std::ostringstream scores;
    scores << "[";
    for (int i = 0; i < 6; i++)
    {
        if (names_only) {
            scores << names[i];
        } else {
            scores << get_score(i);
        }

        if (i < 5)  // Don't print a comma and space for the last element
        {
            scores << ", ";
        }
    }
    scores << "]" << std::endl;

    // Return as a string
    return scores.str();
}

std::string abilities::print_summary() {

    // Use ostringstream as an easy way to format as if using std::cout
    std::ostringstream summary;
    summary << "Assigned ability scores:" << std::endl
            << "--------------------" << std::endl;
    for (int i = 0; i < 6; i++)
    {
        std::string ab_name = get_name(i);
        summary << std::setw(18) << std::left << ab_name + ": "
                << std::setw(2) << std::right << score_dict[ab_name] << std::endl;
    }
    summary << "--------------------" << std::endl;

    // Return as a string
    return summary.str();
}

void abilities::index_error(int code) {

    switch(code)
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
