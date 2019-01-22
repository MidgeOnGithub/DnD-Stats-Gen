
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "abilities.hpp"
#include "dice_roller/dice.hpp"
#include "dice_roller/dnd_die.hpp"

void generate_3d6(abilities &ab, bool verbose, bool slow, int wait_time) {

    // Iterating from 0 - 5 because there are 6 abilities
    for (int i = 0; i < 6; i++)
    {
        // Roll a 3d6, add result to rolled_score array
        int roll = dnd_roll(3, 6, verbose, slow, wait_time);
        ab.rolled_scores[i] = roll;
        // Describe the score value (index + 1 for natural counting)
        std::cout << "Roll " << i + 1 << " = "
                  << std::setw(2) << roll << std::endl;
    }
}

void generate_4d6(abilities &ab, bool verbose, bool slow, int wait_time) {

    for (int i = 0; i < 6; i++)
    {
        // Populate an array of 4 rolls
        int rolls[4];
        for (int &r : rolls)
        {
            r = dnd_roll(1, 6, verbose, slow, wait_time);
            if (verbose)
            {
                dice_roller::verbosity(&r - &rolls[0], r, slow, wait_time);
            }
        }

        // Sort by increasing value
        std::sort(std::begin(rolls), std::end(rolls));

        // Sum over the three highest values
        int rolled_score = 0;
        for (int r = 1; r < 4; r++)
        {
            rolled_score += rolls[r];
        }

        // Assign and display roll result
        ab.rolled_scores[i] = rolled_score;
        std::cout << "Roll " << i + 1 << " = "
                  << std::setw(2) << rolled_score << std::endl;
    }
}

void assign_abilities(abilities &ab) {

    // Create a copy of ab's scores array (prevent class calls and modification)
    int rs[6];  // rs = rolled scores
    for (int i = 0; i < 6; i++)
    {
        rs[i] = ab.rolled_scores[i];
    }

    // Create array and helper int which specify which scores have been assigned
    bool assigned[6] = {false, false, false, false, false, false};
    int a_count = 0;
    // Create retry_prompt to use for int_input
    std::string retry_prompt = "Score: ";
    // Flag to determine if available scores should be displayed
    bool first_time_asking = true;

    for (int i = 0; i < 6; i++)
    {
        // Initialize control variables
        int num = 0;
        bool keep_going = true;
        std::string ab_name = ab.names[i];

        // If only one value remains, auto-assign it to the last ability
        if (a_count == 5)
        {
            for (int j = 0; j < 6; j++)
            {
                if (!assigned[j])
                {
                    num = rs[j];
                }
            }
            ab.score_dict[ab_name] = num;
            break;
        }

        // Pretty-print the unassigned abilities
        std::ostringstream scores_left;
        scores_left << "Available scores: [";
        for (int j = 0; j < 6; j++)
        {
            // Skip writing the value if it has already been assigned
            if (assigned[j]) continue;
            scores_left << rs[j];
            if (j != 5)  // Don't print a comma and space for the last element
            {
                for (int k = j + 1; k < 6; k++)  // If remaining indices are assigned, current index is last
                {
                    // If a remaining index is unassigned, current index is not last, thus the comma and space
                    if (!assigned[k])
                    {
                        scores_left << ", ";
                        break;
                    }
                }
            }
        }
        scores_left << "]";

        // Create prompt specific to current ability
        std::string prompt = "Which score would you like to assign to " + ab_name + "? ";
        while (keep_going)
        {
            if (!first_time_asking)
                std::cout << scores_left.str() << std::endl;
            // Set to false to ensure the correct flag upon the second time asking
            first_time_asking = false;

            /* Get an int, num, from user using int_input from dice module
             * num indicates which value the user wants to assign to the prompted ability */
            num = dice_roller::int_input(prompt, retry_prompt);
            for (int j = 0; j < 6; j++)
            {
                /* Check if num is an unassigned score
                 * If not, loop for another input */
                if (num == rs[j] && !assigned[j])
                {
                    assigned[j] = true;
                    a_count += 1;
                    keep_going = false;
                    break;  // Only breaks from for loop
                }
            }

            // If the user puts in an impossible or unavailable value
            if (keep_going)
            {
                std::string msg;
                if (num > 18)
                    msg = "You wish!";
                else if (num < 3)
                    msg = "That's a bit harsh!";
                else
                    msg = "That wasn't an available score!";
                // Print decided message to the user
                std::cout << msg << std::endl;
            }
        }

        ab.score_dict[ab_name] = num;
    }
}