
#include <algorithm>
#include <iostream>
#include <stdio.h>

#include "dice.h"
#include "script.h"

void master_script() {
    // This function may be deprecated after moving generation choice and class instantiation to main
}

void generate_3d6(abilities* ab) {

    for (int i = 0; i < 6; i++)
    {
        ab->set_score(i, roll_dice(3, 6, false, false));
        std::cout << "Roll " << i + 1 << " = " << ab->get_score(i) << std::endl;
    }
}

void generate_4d6_drop(abilities* ab) {

    for (int i = 0; i < 6; i++)
    {

        // Populate an array of 4 rolls
        int rolls[4];
        for (int j = 0; j < 4; j++)
        {
            rolls[j] = roll_dice(1, 6, false, false);
        }

        // Use only the 3 highest rolls
        std::sort(std::begin(rolls), std::end(rolls));
        int roll_total = 0;
        for (int roll = 1; roll < 4; roll++)
        {
            roll_total += rolls[roll];
        }

        ab->set_score(i, roll_total);
        std::cout << "Roll " << i + 1 << " = " << ab->get_score(i) << std::endl;
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
