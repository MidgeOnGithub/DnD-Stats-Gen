
#include <iostream>

#include "dice.h"
#include "script.h"

int main() {
    std::cout << "\nWelcome to the command-line DND Stats Generator!\n========================================\n\n";

    master_script();

    abilities* ab = new abilities();

    // Print complete list
    ab->print_summary();

    // Assign scores to abilities

    std::cout << "\nThanks for using the DND Stats Generator!\n========================================\n";
    return 0;
}
