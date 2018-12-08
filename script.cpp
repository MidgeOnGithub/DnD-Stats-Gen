
#include <algorithm>
#include <iostream>
#include <stdio.h>

#include "dice.h"
#include "script.h"

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

void assign_abilities(abilities* ab) {

    int s[6];

    for (int i = 0; i < 6; i++)
    {
        s[i] = ab->get_score(i);
    }

    for (int i = 0; i < 6; i++)
    {
        // Create the prompt to use for int_input
        std::string ab_name = ab->get_name(i);
        std::string prompt = "Which score would you like to assign to " + ab_name + "? ";

        // Initialize control variables
        int sc = 0;
        bool keep_going = true;

        while (keep_going)
        {
            // Tell the user what options are left
            std::cout << "Available scores: [";
            for (int i = 0; i < 6; i++)
            {
                std::cout << s[i];

                if (i != 5)  // Don't print a comma and space for the last element
                {
                    std::cout << ", ";
                }
            }
            std::cout << "]" << std::endl;

            // Take an int from user and see if it is within remaining scores, loop if not
            sc = int_input(prompt);

            for (int i = 0; i < 6; i++)
            {
                if (sc == s[i])
                {
                    keep_going = false;  // If the given input matches at least one value in ab->scores, progress
                    break;
                }
            }
        }

        ab->set_ability_score(ab_name, sc);
    }

}
