
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

    // Create a copy of ab's scores array so as to prevent class calls and data modification
    int s[6];
    for (int i = 0; i < 6; i++)
    {
        s[i] = ab->get_score(i);
    }

    // Create an array and int which will specify which values have been assigned
    bool assigned[6] = {false, false, false, false, false, false};
    int a_count = 0;

    for (int i = 0; i < 6; i++)
    {
        // Initialize control variables
        int sc = 0;
        bool keep_going = true;
        std::string ab_name = ab->get_name(i);

        // If only one value remains, auto-assign it to the last ability
        if (a_count == 5)
        {
            for (int j = 0; j < 6; j++)
            {
                if (!assigned[j]) sc = s[j];
            }
            ab->set_ability_score(ab_name, sc);
            break;
        }

        // Create the prompt to use for int_input
        std::string prompt = "Which score would you like to assign to " + ab_name + "? ";
        while (keep_going)
        {
            // Print the unassigned abilities
            // Consider placing all printing code into a function for better readability and manipulation
            std::cout << "Available scores: [";
            for (int j = 0; j < 6; j++)
            {
                if (assigned[j]) continue;

                std::cout << s[j];

                if (j != 5)  // Don't print a comma and space for the last element
                {
                    for (int k = j + 1; k < 6; k++)  // If all remaining indices are assigned, current index is last
                    {
                        if (!assigned[k])
                        {
                            std::cout << ", ";
                            break;
                        }
                    }
                }
            }
            std::cout << "]" << std::endl;

            // Take an int from user, check if it is an unassigned score, loop if not
            sc = int_input(prompt);
            for (int i = 0; i < 6; i++)
            {
                if (sc == s[i] && !assigned[i])
                {
                    assigned[i] = true;
                    a_count += 1;
                    keep_going = false;
                    break;
                }
            }
        }

        ab->set_ability_score(ab_name, sc);
    }

}
