
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
        indexerror(1);
    }

    return score_dict[name];
}

void abilities::set_ability_score(std::string name, int score) {

    if (score_dict.find(name) == score_dict.end())
    {
        indexerror(2);
    }

    score_dict[name] = score;
}

int abilities::get_score(int i) {

    if (i > 5)
    {
        indexerror(3);
    }

    return scores[i];
}

void abilities::set_score(int i, int score) {

    if (i > 5)
    {
        indexerror(4);
    }

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
    for (auto &pair : score_dict)
    {
        std::cout << std::setw(18) << std::left << pair.first + ": "
                  << std::setw(2) << pair.second << std::endl;
    }
}

void abilities::indexerror(int code) {

    std::string message;

    switch(code) {
        case 1 : message = "Name passed to get_ability_score is not an ability.";
                 exit(1);

        case 2 : message = "Name passed to set_ability_score is not an ability.";
                 exit(2);

        case 3 : message = "Index passed to get_score is out of range.";
                 exit(3);

        case 4 : message = "Index passed to set_score is out of range.";
                 exit(4);

        default : message = "Something else went wrong.";
                  exit(9);
    }
}
