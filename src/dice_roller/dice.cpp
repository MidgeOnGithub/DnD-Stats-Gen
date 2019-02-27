/* Vocabulary:
 * RNG = Random Number Generator/Generation
 * "Die" is the singular, "dice" is the plural
*/
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>

#include "dice.hpp"

namespace dice_roller {

  int int_input(std::string prompt,
                             std::string retry_prompt) {
    int num;
    // If provided, display initial prompt
    std::cout << (prompt.empty() ? retry_prompt : prompt);
    // Loop user prompts until they get it right
    // TODO: Consider refactoring to avoid while (true)
    while (true) {
      std::string input;
      getline(std::cin, input);
      std::stringstream check_stream(input);
      // Accept if it's a natural
      if (check_stream >> num && num > 0)
        break;
      std::cout << "Invalid input -- try again!" << std::endl;
      std::cout << retry_prompt;
    }
    std::cout << std::endl;
    return num;
  }

  void wait_time_adjustment(Options& options) {
    // Ensure wait_time works "as intended"
    if (options.wait_time < 0) {
      std::cout << "WARNING -- Given wait time was invalid.\n"
                << "Reverting to default (750 ms)." << std::endl;
      options.wait_time = 750;
    }
  }

  int roll_dice(Options& options, int dice, int sides) {
    wait_time_adjustment(options);
    // If not given in function call:
    // Determine how many n-sided dice to roll by input
    if (dice < 1)
      dice = int_input("Amount of dice to roll: ",
                       "Dice count: ");
    if (sides < 1)
      sides = int_input("Sides on each die: ",
                        "Die sides: ");

    // Create a generator based on OS-specific non-deterministic RNG
    boost::random::random_device engine;
    // Restrict outputs to a uniform int distribution based on the dice
    boost::random::uniform_int_distribution<int> dist(1, sides);

    int landing;       // Single die's value
    int roll_sum = 0;  // All dice landings
    // Iterate from 1 to allow natural counts
    for (int i = 1; i <= dice; ++i) {
      landing = dist(engine);
      if (options.verbose && dice > 1)
        verbosity(options, i, landing);
      roll_sum += landing;
    }
    // Return the total ndm roll value
    return roll_sum;
  }

  void verbosity(Options &options, int which_die,
                              int landing) {
    std::cout << "Die " << which_die << ": " << landing << std::endl;
    if (options.slow)
      std::this_thread::sleep_for(std::chrono::milliseconds(options.wait_time));
  }

}
