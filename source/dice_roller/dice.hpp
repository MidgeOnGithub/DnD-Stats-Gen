#ifndef DICE_ROLLER_HPP
#define DICE_ROLLER_HPP

#include <string>

namespace dice_roller
{
    struct Options {
        Options(): verbose(false), slow(false), wait_time(0) {}
        bool verbose;
        bool slow;
        int wait_time;
    };

    int int_input(std::string initial_prompt = "",
				  std::string retry_prompt = "");
    int roll_dice(int num_dice = 0, int num_sides = 0,
				  Options options = Options());
    void verbosity(int which_die, int landing,
		           Options options);
}

#endif //DICE_ROLLER_HPP
