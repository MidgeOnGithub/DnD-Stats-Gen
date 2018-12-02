
#include <iostream>

#include "dice.h"

int main() {
    std::cout << "\nWelcome to the command-line DND Stats Generator!\n==============================\n\n";

    int roll = roll_dice(0, 0, true, true);
    std::cout << "Your roll: " << roll << "\n\n";

    std::cout << "Thanks for using the DND Stats Generator!\n==============================\n";
    return 0;
}
