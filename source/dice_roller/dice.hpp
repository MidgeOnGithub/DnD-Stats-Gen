#ifndef DICE_ROLLER_HPP
#define DICE_ROLLER_HPP

#include <string>

namespace dice_roller
{
    struct Options {
        bool verbose = false;
        bool slow = false;
        int wait_time;
    };

    int int_input(std::string initial_prompt = "", std::string retry_prompt = "");
    int roll_die(int num_die = 0, int num_sides = 0, dice_roller::Options &options);
    void verbosity(int which_dice, int landing, dice_roller::Options &options);
}

#endif //DICE_ROLLER_HPP
