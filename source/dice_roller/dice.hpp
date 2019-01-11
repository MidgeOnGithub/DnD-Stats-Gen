
#ifndef DICE_ROLLER_HPP
#define DICE_ROLLER_HPP

#include <string>

namespace dice_roller
{
    int int_input(std::string initial_prompt = "", std::string retry_prompt = "");

    int roll_die(int num_die = 0, int num_sides = 0,
                            bool verbose = false, bool slow = false, int wait_time = 750);

    void verbosity(int which_dice, int landing, bool slow, int wait_time = 750);
}

#endif //DICE_ROLLER_HPP
