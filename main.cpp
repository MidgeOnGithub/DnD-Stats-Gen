
#include <iostream>

#include "dice.h"
#include "script.h"

int main() {
    std::cout << "\nWelcome to the command-line DND Stats Generator!\n==============================\n\n";

    int abilities[6];
    master_script(abilities);

    std::cout << "Thanks for using the DND Stats Generator!\n==============================\n";
    return 0;
}
