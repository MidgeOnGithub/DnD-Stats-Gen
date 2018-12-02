#include <chrono>
#include <thread>

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

int int_input(std::string initial_prompt = "") {
    int num;
    bool prompt_flag = false;

    // If the user provided an initial prompt, display, else give the generic one
    if (initial_prompt.compare("") == 0)
    {
        prompt_flag = true;
    } else
    {
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

    return num;
}

int roll_dice(int die_count = 0, int die_sides = 0, bool verbose = false, bool slow = false, int wait = 250)  {

    // Figure out how many of n-sided die shall be rolled
    if (die_count < 1)
    {
        die_count = int_input("Enter the amount of die to be rolled: ");
    }
    if (die_sides < 1)
    {
        die_sides = int_input("Now enter how many sides each dice has: ");
    }
    std::cout << std::endl;

    // Perform and return a pseudo-random roll
    int roll = 1;
    int landing;
    for (int i = 1; i <= die_count; i++)
    {
        landing = (std::rand() % die_sides) + 1;  // Adding 1 allows [1 - die_sides] instead of [0 - (die_sides - 1)]
        roll += landing;

        if (verbose)
        {
            std::cout << "Roll " << i << ": " << landing << "\n";

            if (slow)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(wait));  // Stop for a period of milliseconds
            }
        }

    }

    return roll;
}

int main() {
    std::cout << "\nWelcome to the command-line DND Stats Generator!\n==============================\n\n";

    int roll = roll_dice(0, 0, true, true);
    std::cout << "Your roll: " << roll << std::endl;

    std::cout << "Thanks for using the DND Stats Generator!\n==============================\n";
    return 0;
}
