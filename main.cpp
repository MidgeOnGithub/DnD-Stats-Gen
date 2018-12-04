
#include <iostream>

// abilities.h is provided by script.h's #include
#include "dice.h"
#include "script.h"

int main() {
    std::cout << "\nWelcome to the command-line DND Stats Generator!\n========================================\n\n";

    master_script();

    // Instantiate abilities class
    abilities* ab = new abilities();

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
