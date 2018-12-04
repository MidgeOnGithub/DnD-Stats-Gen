
#include <iostream>

// abilities.h is provided by script.h's #include
#include "dice.h"
#include "script.h"

int main() {

    std::cout << "\nWelcome to the command-line DND Stats Generator!\n========================================\n\n";

    // Instantiate abilities class
    abilities* ab = new abilities();

    // Determine if the user would like to generate scores by 3d6, 4d6, or pooling method.
    std::cout << "Would you like to perform a \"classic\" 3d6 ability score generation?" << std::endl
              << "Or would you prefer a 4d6 with the lowest roll dropped? (3d6/4d6): ";
    std::string confirm;
    getline(std::cin, confirm);
    if (confirm == "3" || confirm == "3d6") {
        generate_3d6(ab);
    } else if (confirm == "4" || confirm == "4d6") {
        generate_4d6_drop(ab);
    } else {
        // Implement points-buy assignment system
    }

    // Assign scores to abilities
    // Having code here would be good

    // At the end, print an abilities summary
    ab->print_summary();

    // This is where code to output abilities summary to a file would likely go

    // Delete abilities class to free memory
    delete ab;

    std::cout << "\nThanks for using the DND Stats Generator!\n========================================\n";
    return 0;
}
