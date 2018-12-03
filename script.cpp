
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <iterator>
#include <stdio.h>

#include "dice.h"
#include "script.h"

void master_script() {

    // Initialize the scores vector
    std::vector<int> scores[6];

    // Determine which script the user would like to run
    std::cout << "Would you like to use a 3d6 random ability score generation? (y/n): ";
    std::string confirm;
    getline(std::cin, confirm);
    if (confirm == "y" || confirm == "yes" || confirm == "Y" || confirm == "Yes")
    {
        abilities_3d6(scores);
    } else {
        // Implement points-pool assignment system
    }

    // Print complete list
    print_ability_scores(*scores);

    // Assign scores to abilities
    std::map<std::string, int> abilities = {
            {"Strength", 0}, {"Dexterity", 0}, {"Constitution", 0}, {"Intelligence", 0}, {"Wisdom", 0}, {"Charisma", 0}
    };
    assign_abilities(scores, abilities);
}

void abilities_3d6(std::vector<int> scores[6]) {

    for (int i = 0; i < 6; i++)
    {
        scores[i] = (roll_dice(3, 6, true, false));
        std::cout << "Roll " << i + 1 << " = " << scores[i] << std::endl;
    }
}

void assign_abilities(std::vector<int> scores[6], std::map<std::string, int> abil) {

    // Copy the input vector to prevent modification
    std::vector<int> s[6];

    for (int i = 0; i < 6; i++)
    {
        scores[i] = abil[i];
    }
}

void print_ability_scores(std::vector<int> scores) {

    // Get a's length
    int length = scores.size();

    // Pretty-printing
    std::cout << std::endl << "List of ability scores: [";
    for (int i : scores)
    {
        std::cout << i

        if (i != length - 1)  // Don't print a comma and space for the last element
        {
            printf(", ");
        }
    }
    std::cout << "]" << std::endl;

}
