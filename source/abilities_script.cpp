#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "abilities.hpp"
#include "dice_roller/dice.hpp"
#include "dice_roller/dnd_dice.hpp"

int method_choice()
{
    bool good_input = false;
    int choice;
    int countdown = 3;
    while (!good_input)
    {
        // Prevent infinite looping possibility
        if (countdown == 0)
        {
            std::cout << "Failed to get input after three tries.\n"
				         "Terminating program." << std::endl;
            exit(2);
        }
        // Prompt the user and check their response
        // Use ostringstream to format as if using std::cout
        std::ostringstream prompt;
        prompt << "How should we generate ability scores?\n"
               << "------------------\n"
               << "|| 1: " << std::setw(12) << "4d6 ||\n"
               << "|| 2: " << std::setw(12) << "3d6 ||\n"
               << "|| 3: " << std::setw(12) << "Point-Buy ||"
			   << "  <--  Unimplemented!!!\n"
               << "------------------\n"
               << "Choice: ";
        choice = dice_roller::int_input(prompt.str());
        // Update this conditional with future method implementations
        if (choice < 1 || choice > 2)
            countdown--;
        else
            good_input = true;
        // Temporary message while point-buy system is built
        if (choice == 3)
            std::cout << "This doesn't work yet"
					  << " -- choose another option!" << std::endl;
        
    }
    return choice;
}

void Abilities::generate_3d6(dice_roller::Options &options)
{
    // Iterating from 0 - 5 because there are 6 abilities
    for (int i = 0; i < 6; i++)
    {
        // Roll a 3d6, add result to rolled_score array
        int roll = dnd_roll(3, 6, options);
        this->generated_scores[i] = roll;
        // Describe the score value (index + 1 for natural counting)
        std::cout << "Roll " << i + 1 << " = "
                  << std::setw(2) << roll << std::endl;
    }
}

void Abilities::generate_4d6(dice_roller::Options &options)
{
    for (int i = 0; i < 6; i++)
    {
        // Populate an array of 4 rolls
        int rolls[4];
        for (int &r : rolls)
        {
            r = dnd_roll(1, 6, options);
            if (options.verbose)
                dice_roller::verbosity(&r - &rolls[0], r, options);
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
        this->generated_scores[i] = rolled_score;
        std::cout << "Roll " << i + 1 << " = "
                  << std::setw(2) << rolled_score << std::endl;
    }
}

void Abilities::assign_abilities()
{
    // Create a copy of ab's scores array (prevent class calls and modification)
    int rs[6];  // rs = rolled scores
    for (int i = 0; i < 6; i++)
    {
        rs[i] = this->generated_scores[i];
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
        std::string ab_name = this->names[i];
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
            this->score_dict[ab_name] = num;
            break;
        }
        // Pretty-print the unassigned abilities
        // Use ostringstream to format as if using std::cout
        std::ostringstream scores_left;
        scores_left << "Available scores: [";
        for (int j = 0; j < 6; j++)
        {
            // Skip assigning the value if already assigned
            if (assigned[j]) continue;
            scores_left << rs[j];
			// Loop to prevent printing comma and space on last element
			if (j != 5)
            {
				// If remaining indices are assigned
				// current index is last
                for (int k = j + 1; k < 6; k++)
                {
                    // If a remaining index is unassigned, current index
					// is not last, thus the comma and space
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
        std::string prompt = "Choose a score to assign to "
							 + ab_name + ": ";
        while (keep_going)
        {
            if (!first_time_asking)
                std::cout << scores_left.str() << std::endl;
            // Set to false to ensure the correct prompt next time
            first_time_asking = false;
            /* Get choice from user using int_input from dice module
             * num indicates which value the user wants to assign */
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

            // If the user inputs an impossible or unavailable value
            if (keep_going)
            {
                std::string msg;
                if (num > 18)
                    msg = "You wish!";
                else if (num < 3)
                    msg = "That's a bit harsh!";
                else
                    msg = "That wasn't an available score!";
                // Print out to the user
                std::cout << msg << std::endl;
            }
        }
        this->score_dict[ab_name] = num;
    }
}
