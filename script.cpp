
#include <iostream>
#include <stdio.h>

#include "dice.h"
#include "script.h"

void master_script() {

    // Initialize the scores vector
    int scores[6];

    // Determine if the user would like to generate scores or use the pooling method
    std::cout << "Would you like to perform a 3d6 random ability score generation? (y/n): ";
    std::string confirm;
    getline(std::cin, confirm);
    if (confirm == "y" || confirm == "yes" || confirm == "Y" || confirm == "Yes")
    {
        generate_3d6(scores);
    } else if (confirm == "4d6")
    {
        // Implement 4d6, drop lowest option
    } else
    {
        // Implement points-pool assignment system
    }
}

void generate_3d6(int *scores) {

    for (int i = 0; i < 6; i++)
    {
        scores[i] = (roll_dice(3, 6, true, false));
        std::cout << "Roll " << i + 1 << " = " << scores[i] << std::endl;
    }
}

void assign_abilities(int* scores, abilities* ab) {

    /* likely unnecessary with new class
    // Copy the input vector to prevent modification
    int s[6];

    for (int i = 0; i < 6; i++)
    {
        s[i] = scores[i];
    }
    */


}
