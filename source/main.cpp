
#include <fstream>
#include <iostream>

#include "abilities.h"
#include "dice.h"
#include "script.h"

int main() {

    std::cout << std::endl << "Welcome to the command-line DnD Stats Generator!" << std::endl
              << "========================================" << std::endl << std::endl;

    // Instantiate abilities class
    abilities* ab = new abilities();

    // Determine if the user would like to generate scores by 3d6, 4d6, or pooling method.
    bool good_input = false;
    while (!good_input)
    {
        std::cout << "Would you like to perform a \"classic\" 3d6 ability score generation?" << std::endl
                  << "Or would you prefer a 4d6 with the lowest roll dropped? (3d6/4d6): ";
        std::string confirm;
        getline(std::cin, confirm);
        if (confirm == "3" || confirm == "3d6")
        {
            std::cout << std::endl;
            generate_3d6(ab);
            good_input = true;
        } else if (confirm == "4" || confirm == "4d6")
        {
            std::cout << std::endl;
            generate_4d6_drop(ab);
            good_input = true;
        } else
        {
            std::cout << std::endl;
            // Implement points-buy assignment system in another "else if"
        }
    }

    std::cout << std::endl << "Rolled scores: " << ab->print_rolled_scores() << std::endl;

    // Interface with user to assign scores to abilities
    assign_abilities(ab);

    // Print a summary of the final results
    std::string full_summary = ab->print_ability_summary();
    std::cout << full_summary;

    // Offer to write out full_summary to a file.
    std::cout << "Would you like to save a character summary to a text file? (y/n): ";
    std::string confirm;
    getline(std::cin, confirm);
    // Get the first letter of confirm for comparison
    std::string letter = confirm.substr(0, 1);
    if (letter == "y" || letter == "Y")
    {

        // Get a name for the file
        std::string f_name;
        while (f_name.empty())
        {
            std::cout << "What should be file be named? (\".txt\" will be appended): ";
            getline(std::cin, f_name);
        }

        // Write full_summary to new file
        std::ofstream file;
        if (file)
        {
            file.open(f_name + ".txt");
            file << full_summary;
            file.close();
        } else
        {
            std::cout << "Sorry, could not successfully open the file!" << std::endl
                      << "Check space, memory, and permissions!" << std::endl;
        }
    }

    // Delete class instances to free memory
    delete ab;

    // Close the program with an exit message
    std::cout << std::endl << "========================================" << std::endl
              << "Thanks for using the DnD Stats Generator!" << std::endl;
    return 0;
}
