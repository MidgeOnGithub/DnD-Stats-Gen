
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

int dice_roller::int_input(std::string initial_prompt, std::string retry_prompt) {

    int num;

    // Set a generic retry prompt if one was not given
    if (retry_prompt.empty())
        retry_prompt = "Number: ";
    // If the user provided an initial prompt, display, else give the retry prompt
    if (initial_prompt.empty())
        std::cout << retry_prompt;
    else
        std::cout << initial_prompt;
    // Loop user prompts until they get it right
    while (true)
    {
        // Attemot user input
        std::string input;
        getline(std::cin, input);
        std::stringstream check_stream(input);
        if (check_stream >> num && num > 0)
            break;  // Accept if it's an int > 0
        /* Omission of std::endl between retry_prompt and fail message:
         * Assumes user uses "Enter" aka "carriage return" to end input
         * This can be bypassed by someone clever enough */
        std::cout << "Invalid input -- try again!" << std::endl;
        // Ensure user is re-prompted
        std::cout << retry_prompt;
    }
    std::cout << std::endl;

    return num;
}

int dice_roller::roll_die(int num_die, int num_sides, bool verbose, bool slow, int wait_time) {

    // Ensure wait_time works "as intended"
    if (wait_time < 1)
    {
        std::cout << "WARNING -- Given wait time was invalid. Reverting to default." << std::endl;
        wait_time = 750;
    }

    /* If not given in function call:
     * Determine how many n-sided die to roll by input */
    if (num_die < 1)
        num_die = dice_roller::int_input("Enter the amount of dice to be rolled: ", "Die count: ");
    if (num_sides < 1)
        num_sides = dice_roller::int_input("Now enter how many sides each die has: ", "Dice sides: ");
    // Create a generator based on OS-specific non-deterministic RNG
    boost::random::random_device dice;
    // Restrict outputs to a uniform int distribution based on the dice
    boost::random::uniform_int_distribution<int> faces(1, num_sides);
    // Combine the device and distribution into a simply-callable RNG
    boost::function<int()> roll = boost::bind(faces, boost::ref(dice));

    int landing = 0;  // The value of a single dice roll
    int roll_sum = 0;  // The sum of all die landings
    /* Starting iteration from 1 to allow natural counts:
     * [1 to num_sides] instead of [0 to (num_sides - 1)] */
    for (int i = 1; i <= num_die; i++)
    {
        // Roll the die one at a time
        landing = roll();
        // Say each individual roll, pause between if desired
        if (verbose && num_die > 1)
            dice_roller::verbosity(i, landing, slow, wait_time);
        // Add the roll value to sum; continue
        roll_sum += landing;
    }
    // Return the total ndm roll value
    return roll_sum;
}

void dice_roller::verbosity(int which_dice, int landing, bool slow, int wait_time) {

    // Be verbose
    std::cout << "Dice " << which_dice << ": " << landing << std::endl;
    // Pause if desired
    if (slow)
        boost::this_thread::sleep_for(boost::chrono::milliseconds(wait_time));
}
