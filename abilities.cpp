
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
        std::cout << "Argument is not a listed ability." << std::endl;
        exit(1);
    }

    return score_dict[name];
}

void abilities::set_ability_score(std::string name, int score) {

    if (score_dict.find(name) == score_dict.end())
    {
        std::cout << "Argument is not a listed ability." << std::endl;
        exit(1);
    }

    score_dict[name] = score;
}

std::string abilities::get_name(int i) {

    if (i > 5)
    {
        std::cout << "Argument index does not exist." << std::endl;
        exit(2);
    }

    return abilities::names[i];
}

int abilities::get_score(int i) {

    if (i > 5)
    {
        std::cout << "Argument index does not exist." << std::endl;
        exit(2);
    }

    return scores[i];
}

void abilities::set_score(int i, int score) {
    scores[i] = score;
}

void abilities::print_scores(bool names_only) {

    std::cout << std::endl << "List of ability scores: [";
    for (int i = 0; i < 6; i++)
    {
        if (names_only) {
            std::cout << names[i];
        } else {
            get_score(i);
        }

        if (i != 5)  // Don't print a comma and space for the last element
        {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

void abilities::print_summary() {

    std::cout << std::endl << "Assigned ability scores:" << std::endl;
    for (int i = 0; i < 6; i++)
    {
        std::cout << std::setw(18) << std::left << names[i] + ": "
                  << std::setw(2) << scores[i] << std::endl;
    }
}
