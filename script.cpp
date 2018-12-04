
#include <iostream>
#include <stdio.h>

#include "dice.h"
#include "script.h"

void master_script() {
    // This function may be deprecated after moving generation choice and class instantiation to main
}

void generate_3d6(abilities* ab) {

    for (int i = 0; i < 6; i++)
    {
        ab->set_score(i, roll_dice(3, 6, true, false));
        std::cout << "Roll " << i + 1 << " = " << ab->get_score(i) << std::endl;
    }
}

void generate_4d6(abilities* ab) {

}

void assign_abilities(int* scores, abilities* ab) {

    /* likely unnecessary with new class
    // Copy the input vector to prevent modification
    int s[6];

    for (int i = 0; i < 6; i++)
    {
        s[i] = scores[i];
    }
    */


}
