
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "abilities.hpp"
#include "abilities_script.hpp"
#include "dice_roller/dice.hpp"

int main() {

    // Introductory message
    std::cout << std::endl << "Welcome to the DnD Stats Generator!" << std::endl
              << "========================================" << std::endl << std::endl;

    // Instantiate abilities class
    auto * ab = new abilities();

    // Determine how the user wants to generate ability scores.
    bool good_input = false;
    int countdown = 3;
    while (!good_input)
    {
        // Prevent infinite looping possibility
        if (countdown == 0)
        {
            std::cout << "Failed to get input after three tries -- aborting program." << std::endl;
            exit(1);
        }

        std::cout << "What method should we use to generate ability scores?" << std::endl
                  << "------------------" << std::endl
                  << "|| 1: " << std::setw(12) << "4d6 ||" << std::endl
                  << "|| 2: " << std::setw(12) << "3d6 ||" << std::endl
                  << "|| 3: " << std::setw(12) << "Point-Buy ||" <<  "  <--  Unimplemented!!!" << std::endl
                  << "------------------" << std::endl
                  << "Choice: ";
        std::string confirm;
        std::getline(std::cin, confirm);
        if (confirm == "1")
        {
            std::cout << "Chosen method: 4d6" << std::endl;
            generate_4d6_drop(ab);
            good_input = true;
        } else if (confirm == "2")
        {
            std::cout << "Chosen method: 3d6" << std::endl;
            generate_3d6(ab);
            good_input = true;
        } else if (confirm == "3")
        {
            //std::cout << "Chosen method: Point-Buy" << std::endl;
            //point_buy(ab);
            std::cout << "This doesn't work yet -- choose another option!" << std::endl;
        } else
        {
            //good_input = false
            std::cout << std::endl;
            countdown--;
        }
    }

    std::cout << std::endl << "Rolled scores: " << ab->print_rolled_scores() << std::endl;

    // Interface with user to assign scores to abilities
    assign_abilities(ab);

    // Print a summary of the final results
    std::string full_summary = ab->print_ability_summary();
    std::cout << full_summary << std::endl;

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
            std::cout << "What should the file be named? (\".txt\" will be appended): ";
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

    // Give exit message and close
    std::cout << std::endl << "========================================" << std::endl
              << "Thanks for using the DnD Stats Generator!" << std::endl;

    return 0;
}
