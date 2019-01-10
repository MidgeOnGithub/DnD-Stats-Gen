
/* Vocabulary:
 * RNG = Random Number Generator/Generation
 * "Dice" is the singular, "die" is the plural
*/

#include <iostream>
#include <sstream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>

#include "dice.hpp"

int roll_die(int num_die, int num_sides, bool verbose, bool slow, int wait_time) {

    /* If not given in function call:
     * Determine how many n-sided die to roll by input */
    if (num_die < 1)
    {
        num_die = int_input("Enter the amount of dice to be rolled: ");
    }
    if (num_sides < 1)
    {
        num_sides = int_input("Now enter how many sides each die has: ");
    }

    // Prevent a mischievous user from breaking things
    if (wait_time < 1)
    {
        std::cout << "Given wait time was invalid -- reverting to default." << std::endl;
    }

    // Create a generator based on OS-specific non-deterministic RNG
    boost::random::random_device dice;
    // Restrict outputs to a uniform int distribution based on the die
    boost::random::uniform_int_distribution<int> faces(1, num_sides);
    // Combine the generator and range into a simply-callable RNG
    boost::function<int()> roll = boost::bind(faces, boost::ref(dice));

    int landing = 0;  // The value of a single dice roll
    int roll_sum = 0;  // The sum of all die landings
    /* Starting iteration from 1 to allow natural counts:
     * [1 to num_sides] instead of [0 to (num_sides - 1)] */
    for (int i = 1; i <= num_die; i++)
    {
        // Roll the die one at a time
        landing = roll();

        // Say each individual roll and pause between if desired
        if (verbose)
        {
            std::cout << "Die " << i << ": " << landing << std::endl;
            if (slow)
            {
                boost::this_thread::sleep_for(boost::chrono::milliseconds(wait_time));
            }
        }

        roll_sum += landing;
    }

    return roll_sum;
}


int int_input(std::string initial_prompt, std::string retry_prompt) {

    int num;
    bool prompt_flag = false;

    if (retry_prompt.empty())
    {
        retry_prompt = "Number: ";
    }

    // If the user provided an initial prompt, display, else give the generic one
    if (initial_prompt.empty())
    {
        prompt_flag = true;
    } else
    {
        std::cout << initial_prompt;
    }

    // Loop user prompt until they get it right
    while (true)
    {
        if (prompt_flag)
        {
            std::cout << retry_prompt;
        }

        std::string input;
        getline(std::cin, input);
        std::stringstream check_stream(input);
        if (check_stream >> num && num > 0)
        {
            break;  // Accept if it's an int > 0
        }

        /* Omission of std::endl between retry_prompt and fail message:
         * Assumes user uses "Enter" aka "carriage return" to end input
         * This can be bypassed by someone clever enough */
        std::cout << "Invalid input -- try again!" << std::endl;
        prompt_flag = true;  // Ensure user is re-prompted
    }
    std::cout << std::endl;

    return num;
}
