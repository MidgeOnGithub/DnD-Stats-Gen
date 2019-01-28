/* Vocabulary:
 * RNG = Random Number Generator/Generation
 * "Die" is the singular, "dice" is the plural
*/
#include <iostream>
#include <sstream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>

#include "dice.hpp"

int dice_roller::int_input(std::string initial_prompt,
						   std::string retry_prompt)
{
    int num;
    // Set a generic retry prompt if one was not given
    if (retry_prompt.empty())
        retry_prompt = "Number: ";
    // If provided, display initial prompt
    if (initial_prompt.empty())
        std::cout << retry_prompt;
    else
        std::cout << initial_prompt;
    // Loop user prompts until they get it right
    while (true)
    {
        // Attempt user input
        std::string input;
        getline(std::cin, input);
        std::stringstream check_stream(input);
		// Accept if it's an int > 0
        if (check_stream >> num && num > 0)
            break;
        /* Omission of std::endl between retry_prompt and fail message
         * assumes user uses "Enter" aka "carriage return" to end input
         * This can be bypassed by someone but isn't a big concern */
        std::cout << "Invalid input -- try again!" << std::endl;
        // Ensure user is re-prompted
        std::cout << retry_prompt;
    }
    std::cout << std::endl;
    return num;
}

int dice_roller::roll_dice(int num_dice, int num_sides,
						   Options options)
{
    // Ensure wait_time works "as intended"
    if (options.wait_time < 0)
    {
        std::cout << "WARNING -- Given wait time was invalid. "
				  << "Reverting to default." << std::endl;
        options.wait_time = 750;
    }
    /* If not given in function call:
     * Determine how many n-sided dice to roll by input */
    if (num_dice < 1)
        num_dice = dice_roller::int_input("Amount of dice to roll: ",
									      "Dice count: ");
    if (num_sides < 1)
        num_sides = dice_roller::int_input("Sides on each die: ",
										   "Die sides: ");
    // Create a generator based on OS-specific non-deterministic RNG
    boost::random::random_device dice;
    // Restrict outputs to a uniform int distribution based on the dice
    boost::random::uniform_int_distribution<int> faces(1, num_sides);
    // Combine the device and distribution into a simply-callable RNG
    boost::function<int()> roll = boost::bind(faces, boost::ref(dice));
    // Now perform the rolls
    int landing = 0;   // Single dice's value
    int roll_sum = 0;  // The sum of all dice landings
    /* Starting iteration from 1 to allow natural counts:
     * [1 to num_sides] instead of [0 to (num_sides - 1)] */
    for (int i = 1; i <= num_dice; i++)
    {
        // Roll the dice one at a time
        landing = roll();
        // Say each individual roll, pause between if desired
        if (options.verbose && num_dice > 1)
            dice_roller::verbosity(i, landing, options);
        // Add the roll value to sum; continue
        roll_sum += landing;
    }
    // Return the total ndm roll value
    return roll_sum;
}

void dice_roller::verbosity(int which_die, int landing,
							Options options)
{
    // Be verbose
    std::cout << "Dice " << which_die << ": " << landing << std::endl;
    // Pause if desired
    if (options.slow)
        boost::this_thread::sleep_for(boost::chrono::milliseconds(options.wait_time));
}
