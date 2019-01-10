
#include <iostream>
#include <sstream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>


#include "dice.hpp"

int roll_dice(int d_count, int d_sides, bool verbose, bool slow, int wait)  {

    // Figure out how many of n-sided die shall be rolled
    if (d_count < 1)
    {
        d_count = int_input("Enter the amount of dice to be rolled: ");
    }
    if (d_sides < 1)
    {
        d_sides = int_input("Now enter how many sides each die has: ");
    }

    // Perform and return the roll(s)
    boost::random::random_device dice;
    boost::random::uniform_int_distribution<int> faces(1, d_sides);
    boost::function<int()> roll = boost::bind(faces, boost::ref(dice));

    int r_total = 0;
    int landing = 0;
    for (int i = 1; i <= d_count; i++)
    {
        // Adding 1 allows [1 - d_sides] instead of [0 - (d_sides - 1)]
        landing = roll();
        r_total += landing;

        if (verbose)
        {
            std::cout << "Die " << i << ": " << landing << "\n";

            if (slow)
            {
                boost::this_thread::sleep_for(boost::chrono::milliseconds(wait));  // Stop for a period of milliseconds
            }
        }

    }

    return r_total;
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
