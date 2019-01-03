
#include <chrono>
#include <thread>
#include <iostream>
#include <sstream>
#include <random>

#include "dice.h"

int roll_dice(int dice_count, int die_sides, bool verbose, bool slow, int wait)  {

    // Figure out how many of n-sided die shall be rolled
    if (dice_count < 1)
    {
        dice_count = int_input("Enter the amount of dice to be rolled: ");
    }
    if (die_sides < 1)
    {
        die_sides = int_input("Now enter how many sides each die has: ");
    }

    // Perform and return a pseudo-random roll
    static std::random_device rand;
    static std::default_random_engine roller(rand());
    static std::uniform_int_distribution<int> faces(1, die_sides);

    int roll = 0;
    int landing;
    for (int i = 1; i <= dice_count; i++)
    {
        landing = faces(roller);  // Adding 1 allows [1 - die_sides] instead of [0 - (die_sides - 1)]
        roll += landing;

        if (verbose)
        {
            std::cout << "Die " << i << ": " << landing << "\n";

            if (slow)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(wait));  // Stop for a period of milliseconds
            }
        }

    }

    return roll;
}

int int_input(std::string initial_prompt) {
    int num;
    bool prompt_flag = false;

    // If the user provided an initial prompt, display, else give the generic one
    if (initial_prompt.empty())
    {
        prompt_flag = true;
    } else {
        std::cout << initial_prompt;
    }

    // Loop the user prompt until they get it right
    while (true)
    {

        if (prompt_flag)
        {
            std::cout << "Number: ";
        }

        std::string input;
        getline(std::cin, input);

        std::stringstream check_stream(input);
        if (check_stream >> num && num > 0)
        {
            break;  // Accept if it's an int > 0
        }

        std::cout << "Invalid number -- try again!\n";
        prompt_flag = true;
    }

    std::cout << std::endl;
    return num;
}
