
/* All code here is intended to act based on special die/roll cases
 * Described in the fifth edition "Player's Handbook" [PHB]
 * Pages 6 and 7
 * Nothing from the "Errata" publication applies */

#include <iomanip>
#include <iostream>
#include <sstream>

#include "dice.hpp"
#include "dnd_die.hpp"

int dnd_roll(int num_die, int num_sides, bool verbose, bool slow, int wait_time) {

    /* Check against each special dice (relative to DnD)
     * Based on what kind of dice, call the correct function
     * The functions within this source file call dice_roller::roll_die
     * Or make changes to printed values accordingly */

    // Ensure wait_time works "as intended"
    if (wait_time < 1)
    {
        std::cout << "Given wait time was invalid. Reverting to default." << std::endl;
        wait_time = 750;
    }

    int roll_sum;
    if (num_sides == 100)
        roll_sum = d100_roller(num_die, num_sides, verbose, slow, wait_time);
    else if (num_sides == 10)
        roll_sum = d10_roller(num_die, num_sides, verbose, slow, wait_time);
    else if (num_sides == 3)
        roll_sum = d3_roller(num_die, num_sides, verbose, slow, wait_time);
    else if (num_sides == 2)
        roll_sum = d2_roller(num_die, num_sides, verbose, slow, wait_time);
    else
        roll_sum = dice_roller::roll_die(num_die, num_sides, verbose, slow, wait_time);
    // Return the total ndm roll value
    return roll_sum;
}

int d10_display(int d10_value) {
    /* If the value is 10, the face value should be 0 */
    return (d10_value == 10) ? 0 : d10_value;
}

int d100_roller(int num_die, int num_sides, bool verbose, bool slow, int wait_time) {

    /* Simulate a d100 by rolling a percentile and d10
     * The percentile dice loosely represents the tens place
     * The d10 is idiomatically implemented in this roll */
    int roll_sum = 0;
    for (int i = 1; i <= num_die; i++)
    {
        // First roll a pseudo-percentile, also get its face digit
        int percentile = dice_roller::roll_die(1, 10);
        int percentile_face = d10_display(percentile);
        /* Roll the ones-place d10 dice,
         * Special case here that its face value is its literal value
         * I.e., 0 = 0, not 10 */
        int ones_place = d10_display(dice_roller::roll_die(1, 10));
        // Summarize the two die
        std::cout << "Percentile roll: " << percentile_face << "0" << std::endl
                  << std::setw(18) << std::left << "Ones-Place roll: " << ones_place << std::endl;
        // Now evaluate the roll
        int landing = 0;
        if (percentile == 0 && ones_place == 0)
            // Per PHB, 00 + 0 := 100
            landing += 100;
        else
            landing += (percentile * 10) + ones_place;
        // Say each individual landing, pause between if desired
        if (verbose && num_die > 1)
            dice_roller::verbosity(i, landing, slow, wait_time);
        // Add the roll to sum; continue
        roll_sum += landing;
    }

    return roll_sum;
}

int d10_roller(int num_die, int num_sides, bool verbose, bool slow, int wait_time) {

    /* Represent the 0 face properly in case it's printed
     * Although the values range from 1 to 10
     * Face values range from 0 to 9, where 0 := 10 */
    int roll_sum = 0;
    for (int i = 1; i <= num_die; i++)
    {
        int landing = dice_roller::roll_die(1, 10);
        int face_value = d10_display(landing);
        // Say each individual face_value, pause between if desired
        if (verbose && num_die > 1)
            dice_roller::verbosity(i, face_value, slow, wait_time);
        // Add the roll to sum; continue
        roll_sum += landing;
    }

    return roll_sum;
}

int d3_roller(int num_die, int num_sides, bool verbose, bool slow, int wait_time) {

    /* Per PHB, a d3 roll performance:
     * Roll a d6, divide by 2, round up */
    int roll_sum = 0;
    for (int i = 1; i <= num_die; i++)
    {
        int face_value = dice_roller::roll_die(1, 6);
        int landing;
        if (face_value % 2 == 1)
            landing = (face_value + 1) / 2;
        else
            landing = face_value / 2;
        // Say each individual landing, pause between if desired
        if (verbose && num_die > 1)
        {
            dice_roller::verbosity(i, face_value, slow, wait_time);
            std::cout << "Calculated value: " << landing << std::endl;
        }
        // Add the roll to sum; continue
        roll_sum += landing;
    }

    return roll_sum;
}

int d2_roller(int num_die, int num_sides, bool verbose, bool slow, int wait_time) {

    /* An even number := 2, odd number := 1
     * d6 usage is arbitrary
     * Any dice with even face count would work
     * Also described in the PHB is an alternate method not used here
     * Instead of taking the ceiling of half the roll
     * Define the first half of dice values (1 to 3) as 1
     * And the second half (4 to 6) as 2 */
    int roll_sum = 0;
    for (int i = 1; i <= num_die; i++)
    {
        int face_value = dice_roller::roll_die(1, 6);
        int landing;
        if (face_value % 2 == 0)
            landing = 2;
        else
            landing = 1;
        // Say each individual landing, pause between if desired
        if (verbose && num_die > 1)
        {
            dice_roller::verbosity(i, face_value, slow, wait_time);
            std::cout << "Calculated value: " << landing << std::endl;
        }
        // Add the roll to sum; continue
        roll_sum += landing;
    }

    return roll_sum;
}
