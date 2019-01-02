
#include <fstream>
#include <iostream>

// abilities.h is provided by script.h's #include
#include "dice.h"
#include "script.h"

int main() {

    std::cout << "\nWelcome to the command-line DND Stats Generator!\n========================================\n\n";

    // Instantiate abilities class
    abilities* ab = new abilities();

    // Determine if the user would like to generate scores by 3d6, 4d6, or pooling method.
    bool good_input = false;
    while (!good_input) {
        std::cout << "Would you like to perform a \"classic\" 3d6 ability score generation?" << std::endl
                  << "Or would you prefer a 4d6 with the lowest roll dropped? (3d6/4d6): ";
        std::string confirm;
        getline(std::cin, confirm);
        if (confirm == "3" || confirm == "3d6") {
            std::cout << std::endl;
            generate_3d6(ab);
            good_input = true;
        } else if (confirm == "4" || confirm == "4d6") {
            std::cout << std::endl;
            generate_4d6_drop(ab);
            good_input = true;
        } else {
            std::cout << std::endl;
            // Implement points-buy assignment system in another "else if"
        }
    }

    std::cout << std::endl << "Rolled scores: " << ab->print_scores() << std::endl;

    // Interface with user to assign scores to abilities
    assign_abilities(ab);

    // Print a summary of the final results
    std::string full_summary = ab->print_summary();
    std::cout << full_summary;

    // This is where code to output abilities summary to a file would likely go
    std::cout << "Would you like to save a character summary to a text file? (y/n): ";
    std::string confirm;
    getline(std::cin, confirm);
    if (confirm == "y" || confirm == "Y") {

        // Get a name for the file
        std::string f_name;
        while (f_name.empty()) {
            std::cout << "What should be file be named (\".txt\" will be appended)?: ";
            getline(std::cin, f_name);
        }
        // Write full_summary to new file f
        std::ofstream f;
        f.open(f_name + ".txt");
        f << full_summary;
        f.close();
    }

    // Delete abilities class to free memory
    delete ab;

    // Close the program with an exit message
    std::cout << "\nThanks for using the DND Stats Generator!\n========================================\n";
    return 0;
}
