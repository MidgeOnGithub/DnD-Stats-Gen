
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <stdio.h>
#include <vector>

#include "dice.h"
#include "script.h"

void master_script(int abilities[6]) {

    // Determine which script the user would like to run
    std::cout << "Would you like to use a 3d6 random ability score generation? (y/n): ";

    std::string confirm;
    getline(std::cin, confirm);

    if (confirm == "y" || confirm == "yes" || confirm == "Y" || confirm == "Yes")
    {
        abilities_3d6(abilities);
    } else {
        // Implement points-pool assignment system
    }

    std::cout << std::endl << "List of ability scores: [";

    for (int i = 0; i < 6; i++)
    {
        printf("%i", abilities[i]);
        if (i != 5)
        {
            printf(", ");
        }
    }

    std::cout << "]" << std::endl;
}

void abilities_3d6(int a[6]) {

    for (int i = 0; i < 6; i++)
    {
        a[i] = roll_dice(3, 6, true, false);
        std::cout << "Roll " << i + 1 << " = " << a[i] << std::endl;
    }
}
